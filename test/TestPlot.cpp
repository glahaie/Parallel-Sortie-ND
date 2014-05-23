//---------------------------------------------------------------------------
// TestPlot.cpp
//---------------------------------------------------------------------------
#include "TestPlot.h"
#include "Plot.h"
#include "SimManager.h"
#include <fstream>
#include <math.h>

/////////////////////////////////////////////////////////////////////////////
//  TestPlot()
////////////////////////////////////////////////////////////////////////////
void clTestPlot::TestPlot() {
  clSimManager * p_oSimManager = new clSimManager(3, 3, "");
  clPlot *p_oPlot;

  p_oSimManager->ReadFile(WriteXMLFile1());

  p_oPlot = p_oSimManager->GetPlotObject();

  TestPlotGetters(p_oPlot);

  TestGetAzimuth(p_oPlot);

  TestGetDistance(p_oPlot);

  TestGetFastAzimuthAngle(p_oPlot);

  delete p_oSimManager;
}

/////////////////////////////////////////////////////////////////////////////
//  TestPlotGetters()
////////////////////////////////////////////////////////////////////////////
void clTestPlot::TestPlotGetters(clPlot *p_oPlot) {
  float fExpectedResult, fActualResult;
  int iExpectedResult, iActualResult;

  fExpectedResult = 55.37;
  fActualResult = p_oPlot->GetLatitude();
  CPPUNIT_ASSERT(fabs(fExpectedResult - fActualResult) < 0.0001);

  fExpectedResult = 162.0;
  fActualResult = p_oPlot->GetXPlotLength();
  CPPUNIT_ASSERT(fabs(fExpectedResult - fActualResult) < 0.0001);

  fExpectedResult = 203.0;
  fActualResult = p_oPlot->GetYPlotLength();
  CPPUNIT_ASSERT(fabs(fExpectedResult - fActualResult) < 0.0001);

  fExpectedResult = 3.2886;
  fActualResult = p_oPlot->GetPlotArea();
  CPPUNIT_ASSERT(fabs(fExpectedResult - fActualResult) < 0.0001);

  char cExpectedResult[] = "Test Plot 2";
  char cActualResult[50];
  strcpy(cActualResult, p_oPlot->GetPlotTitle());
  CPPUNIT_ASSERT(strcmp(cExpectedResult, cActualResult) == 0);

  iExpectedResult = 21;
  iActualResult = p_oPlot->GetNumXGrids();
  CPPUNIT_ASSERT(iExpectedResult == iActualResult);

  iExpectedResult = 26;
  iActualResult = p_oPlot->GetNumYGrids();
  CPPUNIT_ASSERT(iExpectedResult == iActualResult);

  fExpectedResult = 64.0;
  fActualResult = p_oPlot->GetGridCellArea();
  CPPUNIT_ASSERT(fabs(fExpectedResult - fActualResult) < 0.0001);

  fExpectedResult = 8.0;
  fActualResult = p_oPlot->GetGridCellSize();
  CPPUNIT_ASSERT(fabs(fExpectedResult - fActualResult) < 0.0001);

  strcpy(cExpectedResult, "plot");
  strcpy(cActualResult, p_oPlot->GetName());
  CPPUNIT_ASSERT(strcmp(cExpectedResult, cActualResult) == 0);
}

/////////////////////////////////////////////////////////////////////////////
//  TestGetDistance()
////////////////////////////////////////////////////////////////////////////
void clTestPlot::TestGetDistance(clPlot *p_oPlot) {

  float fFromX, fFromY, fToX, fToY, fExpectedResult, fActualResult;

  fFromX = 24.55; fFromY = 78.24; fToX = 16.46; fToY = 55.35;
  fExpectedResult = 24.27756578;
  fActualResult = p_oPlot->GetDistance(fFromX, fFromY, fToX, fToY);
  CPPUNIT_ASSERT(fabs(fExpectedResult - fActualResult) < 0.0001);

  fFromX = 156.3; fFromY = 153.45; fToX = 30.547; fToY = 175.78;
  fExpectedResult = 42.57315949;
  fActualResult = p_oPlot->GetDistance(fFromX, fFromY, fToX, fToY);
  CPPUNIT_ASSERT(fabs(fExpectedResult - fActualResult) < 0.0001);

  fFromX = 10.36; fFromY = 2.365; fToX = 135.346; fToY = 6.343;
  fExpectedResult = 37.22714977;
  fActualResult = p_oPlot->GetDistance(fFromX, fFromY, fToX, fToY);
  CPPUNIT_ASSERT(fabs(fExpectedResult - fActualResult) < 0.0001);

  fFromX = 83.45; fFromY = 28.48; fToX = 2.45; fToY = 73.8;
  fExpectedResult = 92.81649853;
  fActualResult = p_oPlot->GetDistance(fFromX, fFromY, fToX, fToY);
  CPPUNIT_ASSERT(fabs(fExpectedResult - fActualResult) < 0.0001);

  fFromX = 80.483; fFromY = 176.665; fToX = 108.884; fToY = 24.445;
  fExpectedResult = 58.18268816;
  fActualResult = p_oPlot->GetDistance(fFromX, fFromY, fToX, fToY);
  CPPUNIT_ASSERT(fabs(fExpectedResult - fActualResult) < 0.0001);

  fFromX = 128.23; fFromY = 40.5; fToX = 144.54; fToY = 195.87;
  fExpectedResult = 50.34513879;
  fActualResult = p_oPlot->GetDistance(fFromX, fFromY, fToX, fToY);
  CPPUNIT_ASSERT(fabs(fExpectedResult - fActualResult) < 0.0001);

  fFromX = 30.87; fFromY = 90.75; fToX = 132.37; fToY = 100.7;
  fExpectedResult = 61.31274337;
  fActualResult = p_oPlot->GetDistance(fFromX, fFromY, fToX, fToY);
  CPPUNIT_ASSERT(fabs(fExpectedResult - fActualResult) < 0.0001);

  fFromX = 116.5; fFromY = 128.556; fToX = 0.554; fToY = 8.94;
  fExpectedResult = 95.25682323;
  fActualResult = p_oPlot->GetDistance(fFromX, fFromY, fToX, fToY);
  CPPUNIT_ASSERT(fabs(fExpectedResult - fActualResult) < 0.0001);

  fFromX = 16.843; fFromY = 30.7; fToX = 130.2; fToY = 158.87;
  fExpectedResult = 89.25060419;
  fActualResult = p_oPlot->GetDistance(fFromX, fFromY, fToX, fToY);
  CPPUNIT_ASSERT(fabs(fExpectedResult - fActualResult) < 0.0001);

  fFromX = 140.83; fFromY = 58.72; fToX = 38.42; fToY = 203.0;
  fExpectedResult = 83.66006514;
  fActualResult = p_oPlot->GetDistance(fFromX, fFromY, fToX, fToY);
  CPPUNIT_ASSERT(fabs(fExpectedResult - fActualResult) < 0.0001);

  fFromX = 20.75; fFromY = 190.7; fToX = 162; fToY = 10.78;
  fExpectedResult = 31.03625138;
  fActualResult = p_oPlot->GetDistance(fFromX, fFromY, fToX, fToY);
  CPPUNIT_ASSERT(fabs(fExpectedResult - fActualResult) < 0.0001);

  fFromX = 14.84; fFromY = 45.84; fToX = 78.4; fToY = 45.84;
  fExpectedResult = 63.56;
  fActualResult = p_oPlot->GetDistance(fFromX, fFromY, fToX, fToY);
  CPPUNIT_ASSERT(fabs(fExpectedResult - fActualResult) < 0.0001);

  fFromX = 75.02; fFromY = 136.7; fToX = 75.02; fToY = 0.485;
  fExpectedResult = 66.785;
  fActualResult = p_oPlot->GetDistance(fFromX, fFromY, fToX, fToY);
  CPPUNIT_ASSERT(fabs(fExpectedResult - fActualResult) < 0.0001);
}

/////////////////////////////////////////////////////////////////////////////
//  TestGetAzimuth()
////////////////////////////////////////////////////////////////////////////
void clTestPlot::TestGetAzimuth(clPlot *p_oPlot) {

  float fFromX, fFromY, fToX, fToY, fExpectedResult, fActualResult;

  fFromX = 24.55; fFromY = 78.24; fToX = 16.46; fToY = 55.35;
  fExpectedResult = 3.481319385;
  fActualResult = p_oPlot->GetAzimuthAngle(fFromX, fFromY, fToX, fToY);
  CPPUNIT_ASSERT(fabs(fExpectedResult - fActualResult) < 0.0001);

  fFromX = 156.3; fFromY = 153.45; fToX = 30.547; fToY = 175.78;
  fExpectedResult = 1.018658157;
  fActualResult = p_oPlot->GetAzimuthAngle(fFromX, fFromY, fToX, fToY);
  CPPUNIT_ASSERT(fabs(fExpectedResult - fActualResult) < 0.0001);

  fFromX = 10.36; fFromY = 2.365; fToX = 135.346; fToY = 6.343;
  fExpectedResult = 4.819450887;
  fActualResult = p_oPlot->GetAzimuthAngle(fFromX, fFromY, fToX, fToY);
  CPPUNIT_ASSERT(fabs(fExpectedResult - fActualResult) < 0.0001);

  fFromX = 80.483; fFromY = 176.665; fToX = 108.884; fToY = 24.445;
  fExpectedResult = 0.509951466;
  fActualResult = p_oPlot->GetAzimuthAngle(fFromX, fFromY, fToX, fToY);
  CPPUNIT_ASSERT(fabs(fExpectedResult - fActualResult) < 0.0001);

  fFromX = 128.23; fFromY = 40.5; fToX = 144.54; fToY = 195.87;
  fExpectedResult = 2.811676452;
  fActualResult = p_oPlot->GetAzimuthAngle(fFromX, fFromY, fToX, fToY);
  CPPUNIT_ASSERT(fabs(fExpectedResult - fActualResult) < 0.0001);

  fFromX = 116.5; fFromY = 128.556; fToX = 0.554; fToY = 8.94;
  fExpectedResult = 0.504616675;
  fActualResult = p_oPlot->GetAzimuthAngle(fFromX, fFromY, fToX, fToY);
  CPPUNIT_ASSERT(fabs(fExpectedResult - fActualResult) < 0.0001);

  fFromX = 16.843; fFromY = 30.7; fToX = 130.2; fToY = 158.87;
  fExpectedResult = 3.718000754;
  fActualResult = p_oPlot->GetAzimuthAngle(fFromX, fFromY, fToX, fToY);
  CPPUNIT_ASSERT(fabs(fExpectedResult - fActualResult) < 0.0001);

  fFromX = 103.35; fFromY = 63.78; fToX = 103.35; fToY = 113.85;
  fExpectedResult = 0.0;
  fActualResult = p_oPlot->GetAzimuthAngle(fFromX, fFromY, fToX, fToY);
  CPPUNIT_ASSERT(fabs(fExpectedResult - fActualResult) < 0.0001);

  fFromX = 14.84; fFromY = 45.84; fToX = 78.4; fToY = 45.84;
  fExpectedResult = 1.5707963;
  fActualResult = p_oPlot->GetAzimuthAngle(fFromX, fFromY, fToX, fToY);
  CPPUNIT_ASSERT(fabs(fExpectedResult - fActualResult) < 0.0001);

  fFromX = 75.02; fFromY = 0.485; fToX = 75.02; fToY = 136.7;
  fExpectedResult = 3.1415927;
  fActualResult = p_oPlot->GetAzimuthAngle(fFromX, fFromY, fToX, fToY);
  CPPUNIT_ASSERT(fabs(fExpectedResult - fActualResult) < 0.0001);

  fFromX = 50.23; fFromY = 100.35; fToX = 34.62; fToY = 100.35;
  fExpectedResult = 4.712389;
  fActualResult = p_oPlot->GetAzimuthAngle(fFromX, fFromY, fToX, fToY);
  CPPUNIT_ASSERT(fabs(fExpectedResult - fActualResult) < 0.0001);
}

/////////////////////////////////////////////////////////////////////////////
//  TestGetUncorrectedXandY()
////////////////////////////////////////////////////////////////////////////
void clTestPlot::TestGetUncorrectedXandY(clPlot *p_oPlot) {

  float fAzimuth, fDistance, fFromX, fFromY, fExpectedX, fExpectedY, fActual;

  //Angle is 0
  fFromX = 100;
  fFromY = 100;
  fExpectedX = 100;
  fExpectedY = 107;
  fAzimuth = 0;
  fDistance = 7;
  fActual = p_oPlot->GetUncorrectedX(fFromX, fAzimuth, fDistance);
  CPPUNIT_ASSERT(fabs(fExpectedX - fActual) < 0.0001);
  fActual = p_oPlot->GetUncorrectedY(fFromY, fAzimuth, fDistance);
  CPPUNIT_ASSERT(fabs(fExpectedY - fActual) < 0.0001);

  //Angle is between 0 and PI/2
  fFromX = 100;
  fFromY = 100;
  fExpectedX = 115;
  fExpectedY = 124;
  fAzimuth = 0.558599315;
  fDistance = 28.3019434;
  fActual = p_oPlot->GetUncorrectedX(fFromX, fAzimuth, fDistance);
  CPPUNIT_ASSERT(fabs(fExpectedX - fActual) < 0.0001);
  fActual = p_oPlot->GetUncorrectedY(fFromY, fAzimuth, fDistance);
  CPPUNIT_ASSERT(fabs(fExpectedY - fActual) < 0.0001);

  //Angle is PI/2
  fFromX = 100;
  fFromY = 100;
  fExpectedX = 108;
  fExpectedY = 100;
  fAzimuth = 1.570796327;
  fDistance = 8;
  fActual = p_oPlot->GetUncorrectedX(fFromX, fAzimuth, fDistance);
  CPPUNIT_ASSERT(fabs(fExpectedX - fActual) < 0.0001);
  fActual = p_oPlot->GetUncorrectedY(fFromY, fAzimuth, fDistance);
  CPPUNIT_ASSERT(fabs(fExpectedY - fActual) < 0.0001);

  //Angle is between PI/2 and PI
  fFromX = 100;
  fFromY = 100;
  fExpectedX = 105;
  fExpectedY = 84;
  fAzimuth = 2.838707785;
  fDistance = 16.76305461;
  fActual = p_oPlot->GetUncorrectedX(fFromX, fAzimuth, fDistance);
  CPPUNIT_ASSERT(fabs(fExpectedX - fActual) < 0.0001);
  fActual = p_oPlot->GetUncorrectedY(fFromY, fAzimuth, fDistance);
  CPPUNIT_ASSERT(fabs(fExpectedY - fActual) < 0.0001);

  //Angle is PI
  fFromX = 100;
  fFromY = 100;
  fExpectedX = 100;
  fExpectedY = 57;
  fAzimuth = 3.141592654;
  fDistance = 43;
  fActual = p_oPlot->GetUncorrectedX(fFromX, fAzimuth, fDistance);
  CPPUNIT_ASSERT(fabs(fExpectedX - fActual) < 0.0001);
  fActual = p_oPlot->GetUncorrectedY(fFromY, fAzimuth, fDistance);
  CPPUNIT_ASSERT(fabs(fExpectedY - fActual) < 0.0001);

  //Angle is between PI and 1.5PI
  fFromX = 100;
  fFromY = 100;
  fExpectedX = 25;
  fExpectedY = 14;
  fAzimuth = 3.85877385;
  fDistance = 114.1095964;
  fActual = p_oPlot->GetUncorrectedX(fFromX, fAzimuth, fDistance);
  CPPUNIT_ASSERT(fabs(fExpectedX - fActual) < 0.0001);
  fActual = p_oPlot->GetUncorrectedY(fFromY, fAzimuth, fDistance);
  CPPUNIT_ASSERT(fabs(fExpectedY - fActual) < 0.0001);

  //Angle is 1.5PI
  fFromX = 100;
  fFromY = 100;
  fExpectedX = 13;
  fExpectedY = 100;
  fAzimuth = 4.71238898;
  fDistance = 87;
  fActual = p_oPlot->GetUncorrectedX(fFromX, fAzimuth, fDistance);
  CPPUNIT_ASSERT(fabs(fExpectedX - fActual) < 0.0001);
  fActual = p_oPlot->GetUncorrectedY(fFromY, fAzimuth, fDistance);
  CPPUNIT_ASSERT(fabs(fExpectedY - fActual) < 0.0001);

  //Angle is between 1.5PI and 2PI
  fFromX = 100;
  fFromY = 100;
  fExpectedX = 68;
  fExpectedY = 123;
  fAzimuth = 5.33558831;
  fDistance = 39.40812099;
  fActual = p_oPlot->GetUncorrectedX(fFromX, fAzimuth, fDistance);
  CPPUNIT_ASSERT(fabs(fExpectedX - fActual) < 0.0001);
  fActual = p_oPlot->GetUncorrectedY(fFromY, fAzimuth, fDistance);
  CPPUNIT_ASSERT(fabs(fExpectedY - fActual) < 0.0001);

  //Wrapping to the north
  fFromY = 189;
  fExpectedY = 213;
  fAzimuth = 0.12435499;
  fDistance = 24.18677324;
  fActual = p_oPlot->GetUncorrectedY(fFromY, fAzimuth, fDistance);
  CPPUNIT_ASSERT(fabs(fExpectedY - fActual) < 0.0001);

  //Wrapping to the south
  fFromY = 24;
  fExpectedY = -14;
  fAzimuth = 3.010765258;
  fDistance = 38.32753579;
  fActual = p_oPlot->GetUncorrectedY(fFromY, fAzimuth, fDistance);
  CPPUNIT_ASSERT(fabs(fExpectedY - fActual) < 0.0001);

  //Wrapping to the east
  fFromX = 157;
  fExpectedX = 175;
  fAzimuth = 1.405647649;
  fDistance = 18.24828759;
  fActual = p_oPlot->GetUncorrectedX(fFromX, fAzimuth, fDistance);
  CPPUNIT_ASSERT(fabs(fExpectedX - fActual) < 0.0001);

  //Wrapping to the west
  fFromX = 8;
  fExpectedX = -24;
  fAzimuth = 4.805865762;
  fDistance = 32.14031736;
  fActual = p_oPlot->GetUncorrectedX(fFromX, fAzimuth, fDistance);
  CPPUNIT_ASSERT(fabs(fExpectedX - fActual) < 0.0001);
}

/////////////////////////////////////////////////////////////////////////////
//  TestGetFastAzimuthAngle()
/////////////////////////////////////////////////////////////////////////////
void clTestPlot::TestGetFastAzimuthAngle(clPlot *p_oPlot) {
  float fFromX, fFromY, fToX, fToY;
  int iAzi, iExpectedAzi;

  //Angle is 0
  fFromX = 100;
  fFromY = 100;
  fToX = 100;
  fToY = 107;
  iExpectedAzi = 0;
  iAzi = p_oPlot->GetFastAzimuthAngle(fFromX, fFromY, fToX, fToY);
  CPPUNIT_ASSERT(iAzi == iExpectedAzi);

  //Angle is between 0 and 90
  fFromX = 100;
  fFromY = 100;
  fToX = 115;
  fToY = 124;
  iExpectedAzi = 32;
  iAzi = p_oPlot->GetFastAzimuthAngle(fFromX, fFromY, fToX, fToY);
  CPPUNIT_ASSERT(iAzi == iExpectedAzi);

  //Angle is 90
  fFromX = 100;
  fFromY = 100;
  fToX = 108;
  fToY = 100;
  iExpectedAzi = 90;
  iAzi = p_oPlot->GetFastAzimuthAngle(fFromX, fFromY, fToX, fToY);
  CPPUNIT_ASSERT(iAzi == iExpectedAzi);

  //Angle is between 90 and 180
  fFromX = 100;
  fFromY = 100;
  fToX = 105;
  fToY = 84;
  iExpectedAzi = 162;
  iAzi = p_oPlot->GetFastAzimuthAngle(fFromX, fFromY, fToX, fToY);
  CPPUNIT_ASSERT(iAzi == iExpectedAzi);

  //Angle is 180
  fFromX = 100;
  fFromY = 100;
  fToX = 100;
  fToY = 57;
  iExpectedAzi = 180;
  iAzi = p_oPlot->GetFastAzimuthAngle(fFromX, fFromY, fToX, fToY);
  CPPUNIT_ASSERT(iAzi == iExpectedAzi);

  //Angle is between 180 and 270
  fFromX = 100;
  fFromY = 100;
  fToX = 25;
  fToY = 14;
  iExpectedAzi = 221;
  iAzi = p_oPlot->GetFastAzimuthAngle(fFromX, fFromY, fToX, fToY);
  CPPUNIT_ASSERT(iAzi == iExpectedAzi);

  //Angle is 270
  fFromX = 100;
  fFromY = 100;
  fToX = 87;
  fToY = 100;
  iExpectedAzi = 270;
  iAzi = p_oPlot->GetFastAzimuthAngle(fFromX, fFromY, fToX, fToY);
  CPPUNIT_ASSERT(iAzi == iExpectedAzi);

  //Angle is between 270 and 360
  fFromX = 100;
  fFromY = 100;
  fToX = 68;
  fToY = 123;
  iExpectedAzi = 305;
  iAzi = p_oPlot->GetFastAzimuthAngle(fFromX, fFromY, fToX, fToY);
  CPPUNIT_ASSERT(iAzi == iExpectedAzi);

  //Angle just after 0
  fFromX = 100;
  fFromY = 100;
  fToX = 100.00001;
  fToY = 107;
  iExpectedAzi = 0;
  iAzi = p_oPlot->GetFastAzimuthAngle(fFromX, fFromY, fToX, fToY);
  CPPUNIT_ASSERT(iAzi == iExpectedAzi);

  //Angle just before 90
  fFromX = 100;
  fFromY = 100;
  fToX = 134;
  fToY = 100.000001;
  iExpectedAzi = 90;
  iAzi = p_oPlot->GetFastAzimuthAngle(fFromX, fFromY, fToX, fToY);
  CPPUNIT_ASSERT(iAzi == iExpectedAzi);

  //Angle just after 90
  fFromX = 100;
  fFromY = 100;
  fToX = 108;
  fToY = 99.9999;
  iExpectedAzi = 90;
  iAzi = p_oPlot->GetFastAzimuthAngle(fFromX, fFromY, fToX, fToY);
  CPPUNIT_ASSERT(iAzi == iExpectedAzi);

  //Angle just before 180
  fFromX = 100;
  fFromY = 100;
  fToX = 100.00001;
  fToY = 57;
  iExpectedAzi = 179;
  iAzi = p_oPlot->GetFastAzimuthAngle(fFromX, fFromY, fToX, fToY);
  CPPUNIT_ASSERT(iAzi == iExpectedAzi);

  //Angle just after 180
  fFromX = 100;
  fFromY = 100;
  fToX = 99.9999;
  fToY = 57;
  iExpectedAzi = 180;
  iAzi = p_oPlot->GetFastAzimuthAngle(fFromX, fFromY, fToX, fToY);
  CPPUNIT_ASSERT(iAzi == iExpectedAzi);

  //Angle just before 270
  fFromX = 100;
  fFromY = 100;
  fToX = 87;
  fToY = 99.9999;
  iExpectedAzi = 269;
  iAzi = p_oPlot->GetFastAzimuthAngle(fFromX, fFromY, fToX, fToY);
  CPPUNIT_ASSERT(iAzi == iExpectedAzi);

  //Angle just after 270
  fFromX = 100;
  fFromY = 100;
  fToX = 87;
  fToY = 100.000001;
  iExpectedAzi = 270;
  iAzi = p_oPlot->GetFastAzimuthAngle(fFromX, fFromY, fToX, fToY);
  CPPUNIT_ASSERT(iAzi == iExpectedAzi);

  //Angle just before 360
  fFromX = 100;
  fFromY = 100;
  fToX = 99.9999;
  fToY = 146;
  iExpectedAzi = 359;
  iAzi = p_oPlot->GetFastAzimuthAngle(fFromX, fFromY, fToX, fToY);
  CPPUNIT_ASSERT(iAzi == iExpectedAzi);
}

/////////////////////////////////////////////////////////////////////////////
//  WriteXMLFile1()
/////////////////////////////////////////////////////////////////////////////
const char* clTestPlot::WriteXMLFile1()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">" << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>162.0</plot_lenX>"
       << "<plot_lenY>203.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_title>Test Plot 2</plot_title>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\"/>"
       << "</tr_speciesList>"
       << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
       << "</tr_minAdultDBH>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>"
       << "</trees>"
       << "<allometry>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
       << "<tr_whatSeedlingHeightDiam>"
       << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
       << "</tr_whatSeedlingHeightDiam>"
       << "<tr_whatSaplingHeightDiam>"
       << "<tr_wsahdVal species=\"Species_1\">0</tr_wsahdVal>"
       << "</tr_whatSaplingHeightDiam>"
       << "<tr_whatAdultHeightDiam>"
       << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
       << "</tr_whatAdultHeightDiam>"
       << "<tr_whatAdultCrownRadDiam>"
       << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
       << "</tr_whatAdultCrownRadDiam>"
       << "<tr_whatAdultCrownHeightHeight>"
       << "<tr_wachhVal species=\"Species_1\">0</tr_wachhVal>"
       << "</tr_whatAdultCrownHeightHeight>"
       << "<tr_whatSaplingCrownRadDiam>"
       << "<tr_wscrdVal species=\"Species_1\">0</tr_wscrdVal>"
       << "</tr_whatSaplingCrownRadDiam>"
       << "<tr_whatSaplingCrownHeightHeight>"
       << "<tr_wschhVal species=\"Species_1\">0</tr_wschhVal>"
       << "</tr_whatSaplingCrownHeightHeight>"
       << "</allometry>"
       << "<behaviorList>"
       //Have to have any old behavior
       << "<behavior>"
       << "<behaviorName>ConstantGLI</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<ConstantGLI1>"
       << "<li_constGLI>100</li_constGLI>"
       << "</ConstantGLI1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}
