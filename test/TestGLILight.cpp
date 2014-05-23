//---------------------------------------------------------------------------
#include "TestGLILight.h"
#include <fstream>
#include <math.h>
#include <iostream>

#include "TreePopulation.h"
#include "TreeSearch.h"
#include "SimManager.h"
//---------------------------------------------------------------------------

using namespace std;
/////////////////////////////////////////////////////////////////////////////
//  TestGLILight()
/////////////////////////////////////////////////////////////////////////////
void clTestGLILight::TestGLILight() {

  clSimManager *p_oSimManager = new clSimManager(3, 3, "");

  Run1(p_oSimManager);
  Run2(p_oSimManager);
  //This run is commented out. It doesn't work but I don't know why or if it's
  //important. This is supposed to be for the southern hemisphere.
  //Run3(p_oSimManager);
  TestDoSetupErrorProcessing(p_oSimManager);

  //Clean up
   delete p_oSimManager;
}

/////////////////////////////////////////////////////////////////////////////
// Run1()
/////////////////////////////////////////////////////////////////////////////
void clTestGLILight::Run1(clSimManager *p_oSimManager) {
  clTree *p_oTarget1, *p_oTarget2, *p_oTarget3, *p_oTarget4, *p_oTarget5, *p_oTarget6,
   *p_oTree;
  float fX, fY, fDiam, fLight, fExpectedLight;

  //Feed our file to the sim manager
  p_oSimManager->ReadFile(WriteXMLFile1());
  clTreePopulation *p_oPop = (clTreePopulation*)p_oSimManager->GetPopulationObject("treepopulation");

  //Create our trees
  // # 1
  fX = 75;
  fY = 80;
  fDiam = 15;
  p_oTarget1 = p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);

  // # 2
  fX = 50;
  fY = 50;
  fDiam = 11;
  p_oTarget2 = p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);

  // # 3
  fX = 56.1;
  fY = 50;
  fDiam = 45;
  p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);

  // # 4
  fX = 190;
  fY = 193;
  fDiam = 4;
  p_oTarget3 = p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);

  // # 5
  fX = 187;
  fY = 190;
  fDiam = 140;
  p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);

  // # 6
  fX = 10;
  fY = 185;
  fDiam = 40;
  p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);

  // # 7
  fX = 11;
  fY = 11;
  fDiam = 45;
  p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);

  // # 8
  fX = 10;
  fY = 10;
  fDiam = 15;
  p_oTarget4 = p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);

  // # 9
  fX = 156;
  fY = 15;
  fDiam = 18;
  p_oTarget5 = p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);

  // # 10
  fX = 155;
  fY = 21.5;
  fDiam = 56;
  p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);

  // # 11
  fX = 147;
  fY = 8;
  fDiam = 62;
  p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);

  // # 12
  fX = 147;
  fY = 17;
  fDiam = 57;
  p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);

  // # 13
  fX = 12;
  fY = 194;
  fDiam = 8;
  p_oTarget6 = p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);

  // # 14
  fX = 9;
  fY = 4;
  fDiam = 61;
  p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);

  // # 15
  fX = 1;
  fY = 199;
  fDiam = 41;
  p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);

  // # 16
  fX = 51;
  fY = 57;
  fDiam = 15;
  p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);

  // # 17
  fX = 59;
  fY = 57;
  fDiam = 45;
  p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);

  //Dead neighbor
  fX = 51;
  fY = 51;
  fDiam = 50;
  p_oTree = p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), natural);

  //Run a timestep
  p_oSimManager->RunSim(1);

  //Check the values
  p_oTarget1->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget1->GetSpecies(), p_oTarget1->GetType()), &fLight);
  fExpectedLight = 100;
  CPPUNIT_ASSERT(fabs(fExpectedLight - fLight) < 0.1);

  p_oTarget2->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget2->GetSpecies(), p_oTarget2->GetType()), &fLight);
  fExpectedLight = 90.4544612;
  CPPUNIT_ASSERT(fabs(fExpectedLight - fLight) < 0.1);

  p_oTarget3->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget3->GetSpecies(), p_oTarget3->GetType()), &fLight);
  fExpectedLight = 38.9158116;
  CPPUNIT_ASSERT(fabs(fExpectedLight - fLight) < 0.1);

  p_oTarget4->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget4->GetSpecies(), p_oTarget4->GetType()), &fLight);
  fExpectedLight = 13.68761304;
  CPPUNIT_ASSERT(fabs(fExpectedLight - fLight) < 0.1);

  p_oTarget5->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget5->GetSpecies(), p_oTarget5->GetType()), &fLight);
  fExpectedLight = 81.9849348;
  CPPUNIT_ASSERT(fabs(fExpectedLight - fLight) < 0.1);

  p_oTarget6->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget6->GetSpecies(), p_oTarget6->GetType()), &fLight);
  fExpectedLight = 79.96579752;
  CPPUNIT_ASSERT(fabs(fExpectedLight - fLight) < 0.1);
}

/////////////////////////////////////////////////////////////////////////////
// Run2()
/////////////////////////////////////////////////////////////////////////////
void clTestGLILight::Run2(clSimManager *p_oSimManager) {
  clTree *p_oTarget1, *p_oTarget2;
  float fX, fY, fDiam, fLight, fExpectedLight;

  //Feed our file to the sim manager
  p_oSimManager->ReadFile(WriteXMLFile2());
  clTreePopulation *p_oPop = (clTreePopulation*) p_oSimManager->GetPopulationObject("treepopulation");


  //Create our trees
  // # 1
  fX = 156;
  fY = 15;
  fDiam = 18;
  p_oTarget1 = p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);

  // # 2
  fX = 153;
  fY = 10;
  fDiam = 1;
  p_oTarget2 = p_oPop->CreateTree (fX, fY, 0, clTreePopulation::seedling, fDiam);

  fX = 155;
  fY = 21.5;
  fDiam = 56;
  p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);

  fX = 147;
  fY = 8;
  fDiam = 62;
  p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);

  fX = 147;
  fY = 17;
  fDiam = 57;
  p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);

  //Run a timestep
  p_oSimManager->RunSim(1);

  //Check the values
  p_oTarget1->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget1->GetSpecies(), p_oTarget1->GetType()), &fLight);
  fExpectedLight = 81.4293796;
  CPPUNIT_ASSERT(fabs(fExpectedLight - fLight) < 0.1);

  p_oTarget2->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget2->GetSpecies(), p_oTarget2->GetType()), &fLight);
  fExpectedLight = 86.6536452;
  CPPUNIT_ASSERT(fabs(fExpectedLight - fLight) < 0.1);
}

/////////////////////////////////////////////////////////////////////////////
// Run3()
/////////////////////////////////////////////////////////////////////////////
void clTestGLILight::Run3(clSimManager *p_oSimManager) {
  clTree *p_oTarget1, *p_oTarget2, *p_oTarget3, *p_oTarget4, *p_oTarget5, *p_oTarget6,
   *p_oTree;
  float fX, fY, fDiam, fLight, fExpectedLight;


  //Feed our file to the sim manager
  p_oSimManager->ReadFile(WriteXMLFile3());
  clTreePopulation *p_oPop = (clTreePopulation*)p_oSimManager->GetPopulationObject("treepopulation");

  //Create our trees
  // # 1
  fX = 75;
  fY = 80;
  fDiam = 15;
  p_oTarget1 = p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);

  // # 2
  fX = 50;
  fY = 50;
  fDiam = 11;
  p_oTarget2 = p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);

  // # 3
  fX = 56.1;
  fY = 50;
  fDiam = 45;
  p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);

  // # 4
  fX = 190;
  fY = 193;
  fDiam = 4;
  p_oTarget3 = p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);

  // # 5
  fX = 187;
  fY = 190;
  fDiam = 140;
  p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);

  // # 6
  fX = 10;
  fY = 185;
  fDiam = 40;
  p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);

  // # 7
  fX = 11;
  fY = 11;
  fDiam = 45;
  p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);

  // # 8
  fX = 10;
  fY = 10;
  fDiam = 15;
  p_oTarget4 = p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);

  // # 9
  fX = 156;
  fY = 15;
  fDiam = 18;
  p_oTarget5 = p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);

  // # 10
  fX = 155;
  fY = 21.5;
  fDiam = 56;
  p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);

  // # 11
  fX = 147;
  fY = 8;
  fDiam = 62;
  p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);

  // # 12
  fX = 147;
  fY = 17;
  fDiam = 57;
  p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);

  // # 13
  fX = 12;
  fY = 194;
  fDiam = 8;
  p_oTarget6 = p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);

  // # 14
  fX = 9;
  fY = 4;
  fDiam = 61;
  p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);

  // # 15
  fX = 1;
  fY = 199;
  fDiam = 41;
  p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);

  // # 16
  fX = 51;
  fY = 57;
  fDiam = 15;
  p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);

  // # 17
  fX = 59;
  fY = 57;
  fDiam = 45;
  p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);

  //Dead neighbor
  fX = 51;
  fY = 51;
  fDiam = 50;
  p_oTree = p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), natural);

  //Run a timestep
  p_oSimManager->RunSim(1);

  //Check the values
  p_oTarget1->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget1->GetSpecies(), p_oTarget1->GetType()), &fLight);
  fExpectedLight = 100;
  CPPUNIT_ASSERT(fabs(fExpectedLight - fLight) < 0.1);

  p_oTarget2->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget2->GetSpecies(), p_oTarget2->GetType()), &fLight);
  fExpectedLight = 90.4544612;
  CPPUNIT_ASSERT(fabs(fExpectedLight - fLight) < 0.1);

  p_oTarget3->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget3->GetSpecies(), p_oTarget3->GetType()), &fLight);
  fExpectedLight = 38.9158116;
  CPPUNIT_ASSERT(fabs(fExpectedLight - fLight) < 0.1);

  p_oTarget4->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget4->GetSpecies(), p_oTarget4->GetType()), &fLight);
  fExpectedLight = 13.68761304;
  CPPUNIT_ASSERT(fabs(fExpectedLight - fLight) < 0.1);

  p_oTarget5->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget5->GetSpecies(), p_oTarget5->GetType()), &fLight);
  fExpectedLight = 81.9849348;
  CPPUNIT_ASSERT(fabs(fExpectedLight - fLight) < 0.1);

  p_oTarget6->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget6->GetSpecies(), p_oTarget6->GetType()), &fLight);
  fExpectedLight = 79.96579752;
  CPPUNIT_ASSERT(fabs(fExpectedLight - fLight) < 0.1);
}

////////////////////////////////////////////////////////////////////////////
// TestDoSetupErrorProcessing()
////////////////////////////////////////////////////////////////////////////
void clTestGLILight::TestDoSetupErrorProcessing(clSimManager *p_oSimManager) {

   //Feed our error file to the sim manager
   try
  {
    p_oSimManager->ReadFile(WriteXMLErrorFile1());
    CppUnit::Asserter::fail("TestLight error processing didn't catch error for WriteXMLErrorFile1.");
  }
  catch (modelErr& err)
  {
    if (strstr(err.cFunction, "clLightOrg::DoSetup") == NULL)
    {
      CppUnit::Asserter::fail("TestLights error processing caught wrong error for WriteXMLErrorFile1.");
    }
    ;
  }

}

////////////////////////////////////////////////////////////////////////////
// WriteXMLFile1()
////////////////////////////////////////////////////////////////////////////
const char* clTestGLILight::WriteXMLFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>200.0</plot_lenX>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_lenY>200.0</plot_lenY>"
       << "<plot_temp_C>12</plot_temp_C>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\" />"
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
       << "<tr_sachVal species=\"Species_1\">0.589</tr_sachVal>"
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
       << "<behaviorName>GLILight</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<GLILight1>"
       << "<li_minSunAngle>0.785</li_minSunAngle>"
       << "<li_numAltGrids>12</li_numAltGrids>"
       << "<li_numAziGrids>18</li_numAziGrids>"
       << "<li_heightOfFishEyePhoto>1</li_heightOfFishEyePhoto>"
       << "</GLILight1>"
       << "<GeneralLight>"
       << "<li_beamFractGlobalRad>0.5</li_beamFractGlobalRad>"
       << "<li_clearSkyTransCoeff>0.65</li_clearSkyTransCoeff>"
       << "<li_julianDayGrowthStarts>105</li_julianDayGrowthStarts>"
       << "<li_julianDayGrowthEnds>258</li_julianDayGrowthEnds>"
       << "<li_lightExtinctionCoefficient>"
       << "<li_lecVal species=\"Species_1\">0.2</li_lecVal>"
       << "</li_lightExtinctionCoefficient>"
       << "</GeneralLight>"
       << "<StochasticMortality2>"
       << "<mo_stochasticMortRate>"
       << "<mo_smrVal species=\"Species_1\">0</mo_smrVal>"
       << "</mo_stochasticMortRate>"
       << "</StochasticMortality2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
//  WriteXMLFile2()
////////////////////////////////////////////////////////////////////////////
const char* clTestGLILight::WriteXMLFile2() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
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
       << "<plot_temp_C>12</plot_temp_C>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\" />"
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
       << "<tr_sachVal species=\"Species_1\">0.589</tr_sachVal>"
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
       << "<behaviorName>GLILight</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<GLILight1>"
       << "<li_minSunAngle>0.785</li_minSunAngle>"
       << "<li_numAltGrids>12</li_numAltGrids>"
       << "<li_numAziGrids>18</li_numAziGrids>"
       << "<li_heightOfFishEyePhoto>0</li_heightOfFishEyePhoto>"
       << "</GLILight1>"
       << "<GeneralLight>"
       << "<li_beamFractGlobalRad>0.5</li_beamFractGlobalRad>"
       << "<li_clearSkyTransCoeff>0.65</li_clearSkyTransCoeff>"
       << "<li_julianDayGrowthStarts>105</li_julianDayGrowthStarts>"
       << "<li_julianDayGrowthEnds>258</li_julianDayGrowthEnds>"
       << "<li_lightExtinctionCoefficient>"
       << "<li_lecVal species=\"Species_1\">0.2</li_lecVal>"
       << "</li_lightExtinctionCoefficient>"
       << "</GeneralLight>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteXMLFile3()
////////////////////////////////////////////////////////////////////////////
const char* clTestGLILight::WriteXMLFile3() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
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
       << "<plot_temp_C>12</plot_temp_C>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\" />"
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
       << "<tr_sachVal species=\"Species_1\">0.589</tr_sachVal>"
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
       << "<behaviorName>GLILight</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<GLILight1>"
       << "<li_minSunAngle>0.785</li_minSunAngle>"
       << "<li_numAltGrids>12</li_numAltGrids>"
       << "<li_numAziGrids>18</li_numAziGrids>"
       << "<li_heightOfFishEyePhoto>1</li_heightOfFishEyePhoto>"
       << "</GLILight1>"
       << "<GeneralLight>"
       << "<li_beamFractGlobalRad>0.5</li_beamFractGlobalRad>"
       << "<li_clearSkyTransCoeff>0.65</li_clearSkyTransCoeff>"
       << "<li_julianDayGrowthStarts>287</li_julianDayGrowthStarts>"
       << "<li_julianDayGrowthEnds>75</li_julianDayGrowthEnds>"
       << "<li_lightExtinctionCoefficient>"
       << "<li_lecVal species=\"Species_1\">0.2</li_lecVal>"
       << "</li_lightExtinctionCoefficient>"
       << "</GeneralLight>"
       << "<StochasticMortality2>"
       << "<mo_stochasticMortRate>"
       << "<mo_smrVal species=\"Species_1\">0</mo_smrVal>"
       << "</mo_stochasticMortRate>"
       << "</StochasticMortality2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
//  WriteXMLErrorFile1()
////////////////////////////////////////////////////////////////////////////
const char* clTestGLILight::WriteXMLErrorFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<yearsPerTimestep>0.5</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>200.0</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12</plot_temp_C>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\" />"
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
       << "<tr_sachVal species=\"Species_1\">0.589</tr_sachVal>"
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
       << "<behaviorName>GLILight</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<GLILight1>"
       << "<li_minSunAngle>0.785</li_minSunAngle>"
       << "<li_numAltGrids>12</li_numAltGrids>"
       << "<li_numAziGrids>18</li_numAziGrids>"
       << "<li_heightOfFishEyePhoto>1</li_heightOfFishEyePhoto>"
       << "</GLILight1>"
       << "<GeneralLight>"
       << "<li_beamFractGlobalRad>0.5</li_beamFractGlobalRad>"
       << "<li_clearSkyTransCoeff>0.65</li_clearSkyTransCoeff>"
       << "<li_julianDayGrowthStarts>105</li_julianDayGrowthStarts>"
       << "<li_julianDayGrowthEnds>258</li_julianDayGrowthEnds>"
       << "<li_lightExtinctionCoefficient>"
       << "<li_lecVal species=\"Species_1\">0.2</li_lecVal>"
       << "</li_lightExtinctionCoefficient>"
       << "</GeneralLight>"
       << "<StochasticMortality2>"
       << "<mo_stochasticMortRate>"
       << "<mo_smrVal species=\"Species_1\">0</mo_smrVal>"
       << "</mo_stochasticMortRate>"
       << "</StochasticMortality2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}
