//---------------------------------------------------------------------------
// TestGrids.cpp
//---------------------------------------------------------------------------
#include "TestGrids.h"
#include "Grid.h"
#include "SimManager.h"
#include <math.h>
#include <fstream>

/////////////////////////////////////////////////////////////////////////////
//  TestGrids()
/////////////////////////////////////////////////////////////////////////////
void clTestGrids::TestGrids() {
  clSimManager *p_oSimManager = new clSimManager(3, 3, "");

  //Feed our file to the sim manager
  p_oSimManager->ReadFile(WriteXMLFile1());

  clGrid *p_oGrid = CreateGrid(p_oSimManager);

  TestGetAverage(p_oGrid);

  TestGetCoordinates(p_oGrid);

  //Clean up
  delete p_oSimManager;
}


/////////////////////////////////////////////////////////////////////////////
//  TestGetAverage()
/////////////////////////////////////////////////////////////////////////////
void clTestGrids::TestGetAverage(clGrid *p_oGrid) {


  float fExpectedValue, fActualValue, fFromX, fFromY, fToX, fToY;
  short int iIntCode = p_oGrid->GetIntDataCode("int"),
            iFloatCode = p_oGrid->GetFloatDataCode("float");

  fFromX = 16.0;
  fFromY = 12.0;
  fToX = 20.0-VERY_SMALL_VALUE;
  fToY = 18.0-VERY_SMALL_VALUE;

  fExpectedValue = 6;
  fActualValue = p_oGrid->GetAverageIntValue(fFromX, fFromY, fToX, fToY, iIntCode);
  CPPUNIT_ASSERT(fabs(fActualValue - fExpectedValue) < 0.0001);

  fExpectedValue = 4.2;
  fActualValue = p_oGrid->GetAverageFloatValue(fFromX, fFromY, fToX, fToY, iFloatCode);
  CPPUNIT_ASSERT(fabs(fActualValue - fExpectedValue) < 0.0001);

  fFromX = 40.0;
  fFromY = 60.0;
  fToX = 42.0;
  fToY = 62.0;

  fExpectedValue = 20;
  fActualValue = p_oGrid->GetAverageIntValue(fFromX, fFromY, fToX, fToY, iIntCode);
  CPPUNIT_ASSERT(fabs(fActualValue - fExpectedValue) < 0.0001);

  fExpectedValue = 11;
  fActualValue = p_oGrid->GetAverageFloatValue(fFromX, fFromY, fToX, fToY, iFloatCode);
  CPPUNIT_ASSERT(fabs(fActualValue - fExpectedValue) < 0.0001);

  fFromX = 76.0;
  fFromY = 72.0;
  fToX = 84.0-VERY_SMALL_VALUE;
  fToY = 84.0-VERY_SMALL_VALUE;

  fExpectedValue = 32;
  fActualValue = p_oGrid->GetAverageIntValue(fFromX, fFromY, fToX, fToY, iIntCode);
  CPPUNIT_ASSERT(fabs(fActualValue - fExpectedValue) < 0.0001);

  fExpectedValue = 20.75;
  fActualValue = p_oGrid->GetAverageFloatValue(fFromX, fFromY, fToX, fToY, iFloatCode);
  CPPUNIT_ASSERT(fabs(fActualValue - fExpectedValue) < 0.0001);

  fFromX = 24.3;
  fFromY = 100.4;
  fToX = 56.4;
  fToY = 132.5;

  fExpectedValue = 29;
  fActualValue = p_oGrid->GetAverageIntValue(fFromX, fFromY, fToX, fToY, iIntCode);
  CPPUNIT_ASSERT(fabs(fActualValue - fExpectedValue) < 0.0001);

  fExpectedValue = 11.9;
  fActualValue = p_oGrid->GetAverageFloatValue(fFromX, fFromY, fToX, fToY, iFloatCode);
  CPPUNIT_ASSERT(fabs(fActualValue - fExpectedValue) < 0.0001);

  //Error processing
  try {
    fFromX = 50;
    fFromY = 50;
    fToX = 46;
    fToY = 53;
    fActualValue = p_oGrid->GetAverageFloatValue(fFromX, fFromY, fToX, fToY, iFloatCode);
    CppUnit::Asserter::fail("TestGrid didn't catch bad parameter.");
  } catch (modelErr& err) {
    ;
  }

  try {
    fFromX = 50;
    fFromY = 50;
    fToX = 54;
    fToY = 46;
    fActualValue = p_oGrid->GetAverageFloatValue(fFromX, fFromY, fToX, fToY, iFloatCode);
    CppUnit::Asserter::fail("TestGrid didn't catch bad parameter.");
  } catch (modelErr& err) {
    ;
  }

  try {
    fFromX = -2;
    fFromY = 5;
    fToX = 45;
    fToY = 6;
    fActualValue = p_oGrid->GetAverageFloatValue(fFromX, fFromY, fToX, fToY, iFloatCode);
    CppUnit::Asserter::fail("TestGrid didn't catch bad parameter.");
  } catch (modelErr& err) {
    ;
  }

  try {
    fFromX = 45;
    fFromY = 6;
    fToX = -2;
    fToY = 5;
    fActualValue = p_oGrid->GetAverageFloatValue(fFromX, fFromY, fToX, fToY, iFloatCode);
    CppUnit::Asserter::fail("TestGrid didn't catch bad parameter.");
  } catch (modelErr& err) {
    ;
  }

  try {
    fFromX = 50;
    fFromY = 50;
    fToX = 54;
    fToY = 54;
    fActualValue = p_oGrid->GetAverageFloatValue(fFromX, fFromY, fToX, fToY, 2);
    CppUnit::Asserter::fail("TestGrid didn't catch bad parameter.");
  } catch (modelErr& err) {
    ;
  }

  try {
    fFromX = 50;
    fFromY = 50;
    fToX = 54;
    fToY = 54;
    fActualValue = p_oGrid->GetAverageIntValue(fFromX, fFromY, fToX, fToY, 2);
    CppUnit::Asserter::fail("TestGrid didn't catch bad parameter.");
  } catch (modelErr& err) {
    ;
  }
}


/////////////////////////////////////////////////////////////////////////////
//  TestGetCoordinates()
/////////////////////////////////////////////////////////////////////////////
void clTestGrids::TestGetCoordinates(clGrid *p_oGrid) {
  float fX, fY, fExpectedValue, fActualValue;
  int iNum = 13;

  fExpectedValue = 52;
  fActualValue = p_oGrid->GetOriginXOfCell(iNum);
  CPPUNIT_ASSERT(fabs(fActualValue - fExpectedValue) < 1e-7);

  fExpectedValue = 56-VERY_SMALL_VALUE;
  fActualValue = p_oGrid->GetEndXOfCell(iNum);
  CPPUNIT_ASSERT(fabs(fActualValue - fExpectedValue) < 1e-7);

  fExpectedValue = 78;
  fActualValue = p_oGrid->GetOriginYOfCell(iNum);
  CPPUNIT_ASSERT(fabs(fActualValue - fExpectedValue) < 1e-7);

  fExpectedValue = 84-VERY_SMALL_VALUE;
  fActualValue = p_oGrid->GetEndYOfCell(iNum);
  CPPUNIT_ASSERT(fabs(fActualValue - fExpectedValue) < 1e-7);

  //Just to make me feel better
  CPPUNIT_ASSERT(84 > p_oGrid->GetEndYOfCell(iNum));

  //Test odd-sized end cell
  iNum = 33;
  fExpectedValue = 198;
  fActualValue = p_oGrid->GetOriginYOfCell(iNum);
  CPPUNIT_ASSERT(fabs(fActualValue - fExpectedValue) < 1e-7);
  fExpectedValue = 200-VERY_SMALL_VALUE;
  fActualValue = p_oGrid->GetEndYOfCell(iNum);
  CPPUNIT_ASSERT(fabs(fActualValue - fExpectedValue) < 1e-7);

  //Get the middle point of odd-sized end cell
  p_oGrid->GetPointOfCell (49, 33, &fX, &fY);
  CPPUNIT_ASSERT(fabs(198 - fX) < 1e-7);
  CPPUNIT_ASSERT(fabs(199 - fY) < 1e-7);

  //Error processing
  try {
    p_oGrid->GetOriginXOfCell(-2);
    CppUnit::Asserter::fail("TestGetCoordinates - GetOriginXOfCell didn't catch bad parameter of -2.");
  } catch (modelErr& err) {
    ;
  }

  try {
    p_oGrid->GetOriginYOfCell(-2);
    CppUnit::Asserter::fail("TestGetCoordinates - GetOriginYOfCell didn't catch bad parameter of -2.");
  } catch (modelErr& err) {
    ;
  }

  try {
    p_oGrid->GetOriginXOfCell(354);
    CppUnit::Asserter::fail("TestGetCoordinates - GetOriginXOfCell didn't catch bad parameter of 354.");
  } catch (modelErr& err) {
    ;
  }

  try {
    p_oGrid->GetOriginYOfCell(354);
    CppUnit::Asserter::fail("TestGetCoordinates - GetOriginYOfCell didn't catch bad parameter of 354.");
  } catch (modelErr& err) {
    ;
  }

  try {
    p_oGrid->GetEndXOfCell(-2);
    CppUnit::Asserter::fail("TestGetCoordinates - GetEndXOfCell didn't catch bad parameter of -2.");
  } catch (modelErr& err) {
    ;
  }

  try {
    p_oGrid->GetEndYOfCell(-2);
    CppUnit::Asserter::fail("TestGetCoordinates - GetEndYOfCell didn't catch bad parameter of -2.");
  } catch (modelErr& err) {
    ;
  }

  try {
    p_oGrid->GetEndXOfCell(354);
    CppUnit::Asserter::fail("TestGetCoordinates - GetEndXOfCell didn't catch bad parameter of 354.");
  } catch (modelErr& err) {
    ;
  }

  try {
    p_oGrid->GetEndYOfCell(354);
    CppUnit::Asserter::fail("TestGetCoordinates - GetEndYOfCell didn't catch bad parameter of 354.");
  } catch (modelErr& err) {
    ;
  }
}


/////////////////////////////////////////////////////////////////////////////
//  WriteXMLFile1()
/////////////////////////////////////////////////////////////////////////////
const char* clTestGrids::WriteXMLFile1()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>200.0</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
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
       << "<behavior>"
       << "<behaviorName>ConstantGLI</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<ConstantGLI1>"
       << "<li_constGLI>0</li_constGLI>"
       << "</ConstantGLI1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}


/////////////////////////////////////////////////////////////////////////////
//  CreateGrid()
/////////////////////////////////////////////////////////////////////////////
clGrid* clTestGrids::CreateGrid(clSimManager *p_oSimManager) {
  clGrid *p_oGrid = p_oSimManager->CreateGrid("test",1,1,0,0,4.0,6.0);
  float fVal;
  int iNumXCells = p_oGrid->GetNumberXCells(),
      iNumYCells = p_oGrid->GetNumberYCells(),
      iX, iY, iVal;
  short int iIntCode = p_oGrid->RegisterInt("int"),
            iFloatCode = p_oGrid->RegisterFloat("float");

  for (iX = 0; iX < iNumXCells; iX++) {
    for (iY = 0; iY < iNumYCells; iY++) {
       iVal = iX + iY;
       fVal = (float)iX + ((float)iY/10);

       p_oGrid->SetValueOfCell(iX, iY, iIntCode, iVal);
       p_oGrid->SetValueOfCell(iX, iY, iFloatCode, fVal);
    }
  }

  return p_oGrid;
}
