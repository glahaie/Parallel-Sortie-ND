//---------------------------------------------------------------------------
#include <iostream>
#include "Plot.h"
#include "SimManager.h"
#include "ParsingFunctions.h"
//---------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////
// Destructor
////////////////////////////////////////////////////////////////////////////
clPlot::~clPlot()
{
  delete[] mp_fAziTans;
  delete[] mp_iAllowedFileTypes;
  mp_iAllowedFileTypes = NULL;
}


/////////////////////////////////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////////////////////////////////
clPlot::clPlot(clSimManager * p_oSimManager) : clWorkerBase(p_oSimManager)
{
  try
  {
    strcpy(m_cNameString, "plot");

    m_iCellSize = 8;
    strcpy(m_cPlotTitle, "");
    m_iNumXGrids = 0;
    m_iNumYGrids = 0;
    m_fPlotArea = 0;
    m_fPlotLenX = 0;
    m_fPlotLenY = 0;
    m_fLatitude = 0;
    mp_fAziTans = NULL;

    //Allowed file types
    m_iNumAllowedTypes = 2;
    mp_iAllowedFileTypes = new int[m_iNumAllowedTypes];
    mp_iAllowedFileTypes[0] = parfile;
    mp_iAllowedFileTypes[1] = detailed_output;
  }
  catch (modelErr& err)
  {
    throw(err);
  }
  catch (modelMsg & msg)
  {
    throw(msg);
  } //non-fatal error
  catch (...)
  {
    modelErr stcErr;
    stcErr.iErrorCode = UNKNOWN;
    strcpy(stcErr.cFunction, "clPlot::clPlot");
    throw(stcErr);
  }
}


///////////////////////////////////////////////////////////////////////////
// GetData()
//////////////////////////////////////////////////////////////////////////
void clPlot::GetData(DOMDocument * p_oDoc)
{
  try
  {
    DOMNodeList * p_oNodeList;
    DOMNode * p_oDocNode;
    DOMElement * p_oElement;
    XMLCh *sTag;
    char * cData;

    //Get the parent element
    sTag = XMLString::transcode("plot");
    p_oNodeList = p_oDoc->getElementsByTagName(sTag);
    XMLString::release(&sTag);
    if (0 == p_oNodeList->getLength())
    {
      modelErr stcErr;
      stcErr.iErrorCode = DATA_MISSING;
      strcpy(stcErr.cFunction, "clPlot::GetData");
      strcpy(stcErr.cMoreInfo, "plot");
      throw(stcErr);
    }
    p_oDocNode = p_oNodeList->item(0);
    p_oElement = (DOMElement *) p_oDocNode;

    //latitude
    FillSingleValue(p_oElement, "plot_latitude", & m_fLatitude, true);
    //plot length in the x direction
    FillSingleValue(p_oElement, "plot_lenX", & m_fPlotLenX, true);
    //plot length in the y direction
    FillSingleValue(p_oElement, "plot_lenY", & m_fPlotLenY, true);
    //plot mean annual precip, mm
    FillSingleValue(p_oElement, "plot_precip_mm_yr", & m_fMeanAnnualPrecipMm, true);
    //plot mean annual temp, C
    FillSingleValue(p_oElement, "plot_temp_C", & m_fMeanTempC, true);
    //plot title - not required
    sTag = XMLString::transcode("plot_title");
    p_oNodeList = p_oElement->getElementsByTagName(sTag);
    XMLString::release(&sTag);
    if (0 != p_oNodeList->getLength())
    {
      cData = XMLString::transcode(p_oNodeList->item(0)->getFirstChild()->getNodeValue());
      strncpy(m_cPlotTitle, cData, MAX_PLOTTITLE_SIZE - 1);
      //This doesn't always happen with strncpy - make it explicit
      m_cPlotTitle[MAX_PLOTTITLE_SIZE - 1] = '\0';
      delete[] cData;
    }

    //Finish-up calculations
    m_iNumXGrids = (int)ceil(m_fPlotLenX / m_iCellSize);
    m_iNumYGrids = (int)ceil(m_fPlotLenY / m_iCellSize);
    m_fPlotArea = (m_fPlotLenX * m_fPlotLenY) / 10000; //in hectares
    m_fMaxX = m_fPlotLenX - 0.01;
    m_fMaxY = m_fPlotLenY - 0.01;

    PopulateAziTans();
  }
  catch (modelErr& err)
  {
    throw(err);
  }
  catch (modelMsg & msg)
  {
    throw(msg);
  } //non-fatal error
  catch (...)
  {
    modelErr stcErr;
    stcErr.iErrorCode = UNKNOWN;
    strcpy(stcErr.cFunction, "clPlot::GetData");
    throw(stcErr);
  }
}


///////////////////////////////////////////////////////////////////////////
// GetDistance()
//////////////////////////////////////////////////////////////////////////
float clPlot::GetDistance(float fFromX, float fFromY, float fToX, float fToY)
{
  float fXDistance, fYDistance, fDistance1, fDistance2;

  //For each axis, find the shortest distance: with or without torus
  //wrapping.  To torus-wrap, find the smallest coordinate and add the
  //plot length to it.
  if (fToX > fFromX)
  {
    fDistance1 = fToX - fFromX;
    fDistance2 = (fFromX + m_fPlotLenX) - fToX;
    if (fDistance1 < fDistance2) fXDistance = fDistance1;
    else
      fXDistance = fDistance2;
  }
  else
  {
    fDistance1 = fFromX - fToX;
    fDistance2 = (fToX + m_fPlotLenX) - fFromX;
    if (fDistance1 < fDistance2) fXDistance = fDistance1;
    else
      fXDistance = fDistance2;
  }

  if (fToY > fFromY)
  {
    fDistance1 = fToY - fFromY;
    fDistance2 = (fFromY + m_fPlotLenY) - fToY;
    if (fDistance1 < fDistance2) fYDistance = fDistance1;
    else
      fYDistance = fDistance2;
  }
  else
  {
    fDistance1 = fFromY - fToY;
    fDistance2 = (fToY + m_fPlotLenY) - fFromY;
    if (fDistance1 < fDistance2) fYDistance = fDistance1;
    else
      fYDistance = fDistance2;
  }

  return sqrt((fXDistance * fXDistance) + (fYDistance * fYDistance));
}



///////////////////////////////////////////////////////////////////////////
// GetUncorrectedX()
///////////////////////////////////////////////////////////////////////////
float clPlot::GetUncorrectedX(float fFromX, float fAzimuth, float fDistance)
{
  try
  {
     float fAzimuthPrime;

     //Make sure distance is greater than 0, and azimuth is between 0 and 2PI
     if (fDistance < 0) {
       modelErr stcErr;
       stcErr.iErrorCode = BAD_DATA;
       strcpy(stcErr.cFunction, "clPlot::GetUncorrectedX");
       sprintf(stcErr.cMoreInfo, "%s%f", "Distance must be greater than zero.  Is: ", fDistance);
       throw(stcErr);
     }

     if (fAzimuth < 0 || fAzimuth >= 6.283185072) {
      modelErr stcErr;
      stcErr.iErrorCode = BAD_DATA;
      strcpy(stcErr.cFunction, "clPlot::GetUncorrectedX");
      sprintf(stcErr.cMoreInfo, "%s%f", "Azimuth must be between 0 and 2PI.  Is: ", fAzimuth);
      throw(stcErr);
     }

     //Correct the azimuth depending on the quadrant
     if (fAzimuth <= 1.570796326) { //PI/2
       return (sin(fAzimuth) * fDistance) + fFromX;
     }
     else if (fAzimuth > 1.570796326 && fAzimuth <= 3.141592653) {
       fAzimuthPrime = 3.141592653 - fAzimuth; //PI - azimuth
       return (sin(fAzimuthPrime) * fDistance) + fFromX;
     }
     else if (fAzimuth > 3.141592653 && fAzimuth <= 4.71238898) {
       fAzimuthPrime = (4.71238898 - fAzimuth); //3PI/2 - azimuth
       return fFromX - (sin(fAzimuthPrime) * fDistance);
     }
     else {
       fAzimuthPrime = 6.283185072 - fAzimuth; //2PI - azimuth
       return fFromX - (sin(fAzimuthPrime) * fDistance);
     }
  }
  catch (modelErr& err)
  {
    throw(err);
  }
  catch (modelMsg & msg)
  {
    throw(msg);
  } //non-fatal error
  catch (...)
  {
    modelErr stcErr;
    stcErr.iErrorCode = UNKNOWN;
    strcpy(stcErr.cFunction, "clPlot::GetUncorrectedX");
    throw(stcErr);
  }
}


///////////////////////////////////////////////////////////////////////////
// GetUncorrectedY()
///////////////////////////////////////////////////////////////////////////
float clPlot::GetUncorrectedY(float fFromY, float fAzimuth, float fDistance)
{
  try
  {
     float fAzimuthPrime;

     //Make sure distance is greater than 0, and azimuth is between 0 and 2PI
     if (fDistance < 0) {
       modelErr stcErr;
       stcErr.iErrorCode = BAD_DATA;
       strcpy(stcErr.cFunction, "clPlot::GetUncorrectedY");
       sprintf(stcErr.cMoreInfo, "%s%f", "Distance must be greater than zero.  Is: ", fDistance);
       throw(stcErr);
     }

     if (fAzimuth < 0 || fAzimuth >= 6.283185072) {
      modelErr stcErr;
      stcErr.iErrorCode = BAD_DATA;
      strcpy(stcErr.cFunction, "clPlot::GetUncorrectedY");
      sprintf(stcErr.cMoreInfo, "%s%f", "Azimuth must be between 0 and 2PI.  Is: ", fAzimuth);
      throw(stcErr);
     }

     //Correct the azimuth depending on the quadrant
     if (fAzimuth < 1.570796326) { //PI/2
       return (cos(fAzimuth) * fDistance) + fFromY;
     }
     else if (fAzimuth >= 1.570796326 && fAzimuth < 3.141592653) {
       fAzimuthPrime = 3.141592653 - fAzimuth; //PI - azimuth
       return fFromY - (cos(fAzimuthPrime) * fDistance);
     }
     else if (fAzimuth >= 3.141592653 && fAzimuth < 4.71238898) {
       fAzimuthPrime = (4.71238898 - fAzimuth); //3PI/2 - azimuth
       return fFromY - (cos(fAzimuthPrime) * fDistance);
     }
     else {
       fAzimuthPrime = 6.283185072 - fAzimuth; //2PI - azimuth
       return fFromY + (cos(fAzimuthPrime) * fDistance);
     }
  }
  catch (modelErr& err)
  {
    throw(err);
  }
  catch (modelMsg & msg)
  {
    throw(msg);
  } //non-fatal error
  catch (...)
  {
    modelErr stcErr;
    stcErr.iErrorCode = UNKNOWN;
    strcpy(stcErr.cFunction, "clPlot::GetUncorrectedY");
    throw(stcErr);
  }
}


///////////////////////////////////////////////////////////////////////////
// GetAzimuthAngle()
///////////////////////////////////////////////////////////////////////////
float clPlot::GetAzimuthAngle(float fFromX, float fFromY, float fToX, float fToY)
{
  try
  {
    float fDistX = GetXDistance(fFromX, fToX), fDistY = GetYDistance(fFromY, fToY), fAzimuth; //azimuth angle to return

    //Calculate the azimuth - correct for quadrant of "to" relative to "from"
    //(counting clockwise from upper right)
    if ((fDistY > 0) && (fDistX >= 0)) //first quadrant
           fAzimuth = atan((fDistX) / (fDistY));
    if ((fDistX > 0) && (fDistY <= 0)) //second quadrant
           fAzimuth = (M_PI / 2.0) + atan((-1.0 * fDistY) / (fDistX));
    if ((fDistX <= 0) && (fDistY < 0)) //third quadrant
           fAzimuth = M_PI + atan((-1.0 * fDistX) / (-1.0 * fDistY));
    if ((fDistX < 0) && (fDistY >= 0)) //fourth quadrant
           fAzimuth = (1.5 * M_PI) + atan((fDistY) / (-1.0 * fDistX));

    return fAzimuth;
  }
  catch (modelErr& err)
  {
    throw(err);
  }
  catch (modelMsg & msg)
  {
    throw(msg);
  } //non-fatal error
  catch (...)
  {
    modelErr stcErr;
    stcErr.iErrorCode = UNKNOWN;
    strcpy(stcErr.cFunction, "clPlot::GetAzimuthAngle");
    throw(stcErr);
  }
}


////////////////////////////////////////////////////////////////////////////
// GetFastAzimuthAngle()
//////////////////////////////////////////////////////////////////////////
int clPlot::GetFastAzimuthAngle(float fFromX, float fFromY, float fToX, float fToY)
{
  try
  {
    int i, //loop counter
         iAzimuth = -1; //azimuth value to return
    float fDistX = GetXDistance(fFromX, fToX), fDistY = GetYDistance(fFromY, fToY), fTanAzimuth; //tangent of the azimuth angle

    //If the Y distance is 0 - shortcut.  If the X distance is positive, the
    //value is 90; if negative, 270.
    if (fDistY == 0)
    {
      if (fDistX > 0)
        return 90;
      else if (fDistX < 0)
        return 270;
      else
        return 0;
    }
    else if (fDistX == 0)
    {
      if (fDistY > 0)
        return 0;
      else
        return 180;
    }

    //Calculate the tangent of azimuth - correct for quadrant of "to" relative
    //to "from" (counting clockwise from upper right).  Then start looking at
    //tangent values in that quadrant until we find the array bucket where the
    //value fits between its value and the next one

    fTanAzimuth = fDistX / fDistY;
    if (fTanAzimuth > 9999)
      fTanAzimuth = 9999;

    if ((fDistY > 0) && (fDistX >= 0))
    { //first quadrant

      for (i = 0; i < 91; i++)
      {
        if (mp_fAziTans[i] <= fTanAzimuth && mp_fAziTans[i + 1] > fTanAzimuth)
        {
          iAzimuth = i; break;
        }
      }

    }
    else if ((fDistX > 0) && (fDistY <= 0))
    { //second quadrant

      //If very close to 90, the for loop may not catch it
      if (fTanAzimuth < mp_fAziTans[91])
        return 90;

      for (i = 91; i < 180; i++)
      {

        if (mp_fAziTans[i] <= fTanAzimuth && mp_fAziTans[i + 1] > fTanAzimuth)
        {
          iAzimuth = i; break;
        }
      }

    }
    else if ((fDistX <= 0) && (fDistY < 0))
    { //third quadrant

      //If very close to 180, the for loop may not catch it
      if (fTanAzimuth < mp_fAziTans[180])
        return 180;

      for (i = 180; i < 271; i++)
      {
        if (mp_fAziTans[i] <= fTanAzimuth && mp_fAziTans[i + 1] > fTanAzimuth)
        {
          iAzimuth = i; break;
        }
      }

    }
    else if ((fDistX < 0) && (fDistY >= 0))
    { //fourth quadrant

      //If very close to 270, the for loop may not catch it
      if (fTanAzimuth < mp_fAziTans[271])
        return 270;

      for (i = 271; i < 359; i++)
      {
        if (mp_fAziTans[i] <= fTanAzimuth && mp_fAziTans[i + 1] > fTanAzimuth)
        {
          iAzimuth = i; break;
        }
        if (iAzimuth < 0) iAzimuth = 359; //avoid going over the end of the array
      }
    }
    return iAzimuth;
  }
  catch (modelErr& err)
  {
    throw(err);
  }
  catch (modelMsg & msg)
  {
    throw(msg);
  } //non-fatal error
  catch (...)
  {
    modelErr stcErr;
    stcErr.iErrorCode = UNKNOWN;
    strcpy(stcErr.cFunction, "clPlot::GetAzimuthAngle");
    throw(stcErr);
  }
}


///////////////////////////////////////////////////////////////////////////
// PopulateAziTans()
//////////////////////////////////////////////////////////////////////////
void clPlot::PopulateAziTans()
{
  try
  {
    float fAngle;
    short int i; //loop counter
    //Declare the array - sized at 360
    mp_fAziTans = new float[360];

    //For each array bucket, calculate the tangent to the degree that forms its
    //lower bound (array index 0 = 0 degrees, array index 30 = 30 degrees).
    //Watch out for 90 and 270!  Set them to 10000.
    for (i = 0; i < 360; i++)
    {
      if (i == 90 || i == 270)
      {
        mp_fAziTans[i] = 10000;
      }
      else
      {
        //Convert i to radians
        fAngle = i * CONVERT_TO_RADIANS;
        mp_fAziTans[i] = tan(fAngle);
      }
    }
  }
  catch (modelErr& err)
  {
    throw(err);
  }
  catch (modelMsg & msg)
  {
    throw(msg);
  } //non-fatal error
  catch (...)
  {
    modelErr stcErr;
    stcErr.iErrorCode = UNKNOWN;
    strcpy(stcErr.cFunction, "clPlot::PopulateAziTans");
    throw(stcErr);
  }
}


///////////////////////////////////////////////////////////////////////////
// CorrectX()
//////////////////////////////////////////////////////////////////////////
float clPlot::CorrectX(float fX)
{
  try
  {

    //Check for overflow-type conditions so we don't loop too deep
    if (fabs(fX) > 10.0 * m_fPlotLenX)
    {
      modelErr stcErr;
      stcErr.iErrorCode = BAD_DATA;
      strcpy(stcErr.cFunction, "clPlot::CorrectX");
      sprintf(stcErr.cMoreInfo, "%s%g", "Possible uninitialized variable - ", fX);
      throw(stcErr);
    }
    if (fX < 0)
      fX += m_fPlotLenX;
    else if (fX >= m_fMaxX)
      fX -= m_fMaxX;

    //If that wasn't enough to fix it - try again
    if (fX < 0 || fX >= m_fMaxX)
      fX = CorrectX(fX);

    return fX;
  }
  catch (modelErr& err)
  {
    throw(err);
  }
  catch (modelMsg & msg)
  {
    throw(msg);
  } //non-fatal error
  catch (...)
  {
    modelErr stcErr;
    stcErr.iErrorCode = UNKNOWN;
    strcpy(stcErr.cFunction, "clPlot::CorrectX");
    throw(stcErr);
  }
}


///////////////////////////////////////////////////////////////////////////
// CorrectY()
//////////////////////////////////////////////////////////////////////////
float clPlot::CorrectY(float fY)
{
  try
  {

    if (fabs(fY) > 10.0 * m_fPlotLenY)
    {
      modelErr stcErr;
      stcErr.iErrorCode = BAD_DATA;
      strcpy(stcErr.cFunction, "clPlot::CorrectX");
      sprintf(stcErr.cMoreInfo, "%s%g", "Possible uninitialized variable - ", fY);
      throw(stcErr);
    }
    if (fY < 0)
      fY += m_fPlotLenY;
    else if (fY >= m_fMaxY)
      fY -= m_fMaxY;

    //If that wasn't enough to fix it - try again
    if (fY < 0 || fY >= m_fMaxY)
      fY = CorrectY(fY);

    return fY;
  }
  catch (modelErr& err)
  {
    throw(err);
  }
  catch (modelMsg & msg)
  {
    throw(msg);
  } //non-fatal error
  catch (...)
  {
    modelErr stcErr;
    stcErr.iErrorCode = UNKNOWN;
    strcpy(stcErr.cFunction, "clPlot::CorrectY");
    throw(stcErr);
  }
}
