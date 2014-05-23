//---------------------------------------------------------------------------
// TestAllometricGrowthIncrementer.cpp
//---------------------------------------------------------------------------
#include "TestAllometricGrowthIncrementer.h"
#include <fstream>
#include <math.h>
#include "TreePopulation.h"
#include "SimManager.h"

////////////////////////////////////////////////////////////////////////////
//  TestAllometricGrowthIncrementer()
////////////////////////////////////////////////////////////////////////////
void clTestAllometricGrowthIncrementer::TestAllometricGrowthIncrementer() {
  clSimManager *p_oSimManager = new clSimManager(4, 2, "");

  TestNormalProcessingRun1(p_oSimManager);
  TestNormalProcessingRun2(p_oSimManager);

  delete p_oSimManager;
}

////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun1
////////////////////////////////////////////////////////////////////////////
void clTestAllometricGrowthIncrementer::TestNormalProcessingRun1(clSimManager *p_oSimManager) {

  clTreePopulation * p_oPop;
  clTree *p_oTree1, *p_oTree2, *p_oTree3, *p_oTree4;
  float fDiam, fHeight, fExpectedDiam, fExpectedHeight;

  //Load our test file and get our tree population pointers
  p_oSimManager->ReadFile( WriteXMLFile1() );
  p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

  //Create our four trees and set diameter and height for each
  //Adult, Species 1
  fDiam = 12;
  fHeight = 10;
  p_oTree1 = p_oPop->CreateTree(1, 1, 0, clTreePopulation::adult, fDiam);
  p_oTree1->SetValue(p_oPop->GetHeightCode(p_oTree1->GetSpecies(), p_oTree1->GetType()), fHeight, false, false);

  //Adult, Species 2
  fDiam = 15;
  fHeight = 10;
  p_oTree2 = p_oPop->CreateTree(1, 1, 1, clTreePopulation::adult, fDiam);
  p_oTree2->SetValue(p_oPop->GetHeightCode(p_oTree2->GetSpecies(), p_oTree2->GetType()), fHeight, false, false);

  //Adult, Species 1
  fDiam = 50;
  fHeight = 39;
  p_oTree3 = p_oPop->CreateTree(1, 1, 0, clTreePopulation::adult, fDiam);
  p_oTree3->SetValue(p_oPop->GetHeightCode(p_oTree3->GetSpecies(), p_oTree3->GetType()), fHeight, false, false);

  //Adult, Species 2
  fDiam = 41;
  fHeight = 39.3;
  p_oTree4 = p_oPop->CreateTree(1, 1, 1, clTreePopulation::adult, fDiam);
  p_oTree4->SetValue(p_oPop->GetHeightCode(p_oTree4->GetSpecies(), p_oTree4->GetType()), fHeight, false, false);

  //Run our timestep
  p_oSimManager->RunSim(1);

  //Check our results for each tree

  //Adult, Species 1
  fExpectedDiam = 14.1;
  fExpectedHeight = 11.62094804;
  p_oTree1->GetValue(p_oPop->GetDbhCode(p_oTree1->GetSpecies(), p_oTree1->GetType()), &fDiam);
  p_oTree1->GetValue(p_oPop->GetHeightCode(p_oTree1->GetSpecies(), p_oTree1->GetType()), &fHeight);
  CPPUNIT_ASSERT(fabs(fExpectedDiam - fDiam) < 0.001);
  CPPUNIT_ASSERT(fabs(fExpectedHeight - fHeight) < 0.001);

  //Adult, Species 2
  fExpectedDiam = 17.6;
  fExpectedHeight = 11.61587289;
  p_oTree2->GetValue(p_oPop->GetDbhCode(p_oTree2->GetSpecies(), p_oTree2->GetType()), &fDiam);
  p_oTree2->GetValue(p_oPop->GetHeightCode(p_oTree2->GetSpecies(), p_oTree2->GetType()), &fHeight);
  CPPUNIT_ASSERT(fabs(fExpectedDiam - fDiam) < 0.001);
  CPPUNIT_ASSERT(fabs(fExpectedHeight - fHeight) < 0.001);

  //Adult, Species 1
  fExpectedDiam = 52.1;
  fExpectedHeight = 39.479;
  p_oTree3->GetValue(p_oPop->GetDbhCode(p_oTree3->GetSpecies(), p_oTree3->GetType()), &fDiam);
  p_oTree3->GetValue(p_oPop->GetHeightCode(p_oTree3->GetSpecies(), p_oTree3->GetType()), &fHeight);
  CPPUNIT_ASSERT(fabs(fExpectedDiam - fDiam) < 0.001);
  CPPUNIT_ASSERT(fabs(fExpectedHeight - fHeight) < 0.001);

  //Adult, Species 2
  fExpectedDiam = 41.95121951;
  fExpectedHeight = 39.539;
  p_oTree4->GetValue(p_oPop->GetDbhCode(p_oTree4->GetSpecies(), p_oTree4->GetType()), &fDiam);
  p_oTree4->GetValue(p_oPop->GetHeightCode(p_oTree4->GetSpecies(), p_oTree4->GetType()), &fHeight);
  CPPUNIT_ASSERT(fabs(fExpectedDiam - fDiam) < 0.001);
  CPPUNIT_ASSERT(fabs(fExpectedHeight - fHeight) < 0.001);
}

////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun2
////////////////////////////////////////////////////////////////////////////
void clTestAllometricGrowthIncrementer::TestNormalProcessingRun2(clSimManager *p_oSimManager) {

  clTreePopulation * p_oPop;
  clTree *p_oTree1, *p_oTree2, *p_oTree3, *p_oTree4, *p_oTree5, *p_oTree6;
  float fDiam, fHeight, fExpectedDiam, fExpectedHeight;

  //Load our test file and get our tree population pointers
  p_oSimManager->ReadFile( WriteXMLFile2() );
  p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

  //Create our trees and set diameter and height for each
  //Adult, Species 1
  fDiam = 12;
  fHeight = 10;
  p_oTree1 = p_oPop->CreateTree(1, 1, 0, clTreePopulation::adult, fDiam);
  p_oTree1->SetValue(p_oPop->GetHeightCode(p_oTree1->GetSpecies(), p_oTree1->GetType()), fHeight, false, false);

  //Adult, Species 2
  fDiam = 15;
  fHeight = 10;
  p_oTree2 = p_oPop->CreateTree(1, 1, 1, clTreePopulation::adult, fDiam);
  p_oTree2->SetValue(p_oPop->GetHeightCode(p_oTree2->GetSpecies(), p_oTree2->GetType()), fHeight, false, false);

  //Seedling, Species 1
  fDiam = 1;
  fHeight = 1.2;
  p_oTree3 = p_oPop->CreateTree(1, 1, 0, clTreePopulation::seedling, fDiam);
  p_oTree3->SetValue(p_oPop->GetHeightCode(p_oTree3->GetSpecies(), p_oTree3->GetType()), fHeight, false, false);

  //Seedling, Species 2
  fDiam = 0.1;
  fHeight = 0.45;
  p_oTree4 = p_oPop->CreateTree(1, 1, 1, clTreePopulation::seedling, fDiam);
  p_oTree4->SetValue(p_oPop->GetHeightCode(p_oTree4->GetSpecies(), p_oTree4->GetType()), fHeight, false, false);

  //Sapling, Species 1
  fDiam = 7;
  fHeight = 4;
  p_oTree5 = p_oPop->CreateTree(1, 1, 0, clTreePopulation::sapling, fDiam);
  p_oTree5->SetValue(p_oPop->GetHeightCode(p_oTree5->GetSpecies(), p_oTree5->GetType()), fHeight, false, false);

  //Sapling, Species 2
  fDiam = 6;
  fHeight = 6;
  p_oTree6 = p_oPop->CreateTree(1, 1, 1, clTreePopulation::sapling, fDiam);
  p_oTree6->SetValue(p_oPop->GetHeightCode(p_oTree6->GetSpecies(), p_oTree6->GetType()), fHeight, false, false);

  //Run our timestep
  p_oSimManager->RunSim(1);

  //Check our results for each tree

  //Tree 1
  fExpectedDiam = 12.57319697;
  fExpectedHeight = 10.37831;
  p_oTree1->GetValue(p_oPop->GetDbhCode(p_oTree1->GetSpecies(), p_oTree1->GetType()), &fDiam);
  p_oTree1->GetValue(p_oPop->GetHeightCode(p_oTree1->GetSpecies(), p_oTree1->GetType()), &fHeight);
  CPPUNIT_ASSERT(fabs(fExpectedDiam - fDiam) < 0.001);
  CPPUNIT_ASSERT(fabs(fExpectedHeight - fHeight) < 0.001);

  //Tree 2
  fExpectedDiam = 15.53141463;
  fExpectedHeight = 10.43576;
  p_oTree2->GetValue(p_oPop->GetDbhCode(p_oTree2->GetSpecies(), p_oTree2->GetType()), &fDiam);
  p_oTree2->GetValue(p_oPop->GetHeightCode(p_oTree2->GetSpecies(), p_oTree2->GetType()), &fHeight);
  CPPUNIT_ASSERT(fabs(fExpectedDiam - fDiam) < 0.001);
  CPPUNIT_ASSERT(fabs(fExpectedHeight - fHeight) < 0.001);

  //Tree 3
  fExpectedDiam = 1.394072917;
  fExpectedHeight = 1.57831;
  p_oTree3->GetValue(p_oPop->GetDiam10Code(p_oTree3->GetSpecies(), p_oTree3->GetType()), &fDiam);
  p_oTree3->GetValue(p_oPop->GetHeightCode(p_oTree3->GetSpecies(), p_oTree3->GetType()), &fHeight);
  CPPUNIT_ASSERT(fabs(fExpectedDiam - fDiam) < 0.001);
  CPPUNIT_ASSERT(fabs(fExpectedHeight - fHeight) < 0.001);

  //Tree 4
  fExpectedDiam = 0.589617978;
  fExpectedHeight = 0.88576;
  p_oTree4->GetValue(p_oPop->GetDiam10Code(p_oTree4->GetSpecies(), p_oTree4->GetType()), &fDiam);
  p_oTree4->GetValue(p_oPop->GetHeightCode(p_oTree4->GetSpecies(), p_oTree4->GetType()), &fHeight);
  CPPUNIT_ASSERT(fabs(fExpectedDiam - fDiam) < 0.001);
  CPPUNIT_ASSERT(fabs(fExpectedHeight - fHeight) < 0.001);

  //Tree 5
  fExpectedDiam = 7.310090164;
  fExpectedHeight = 4.37831;
  p_oTree5->GetValue(p_oPop->GetDbhCode(p_oTree5->GetSpecies(), p_oTree5->GetType()), &fDiam);
  p_oTree5->GetValue(p_oPop->GetHeightCode(p_oTree5->GetSpecies(), p_oTree5->GetType()), &fHeight);
  CPPUNIT_ASSERT(fabs(fExpectedDiam - fDiam) < 0.001);
  CPPUNIT_ASSERT(fabs(fExpectedHeight - fHeight) < 0.001);

  //Tree 6
  fExpectedDiam = 6.558666667;
  fExpectedHeight = 6.43576;
  p_oTree6->GetValue(p_oPop->GetDbhCode(p_oTree6->GetSpecies(), p_oTree6->GetType()), &fDiam);
  p_oTree6->GetValue(p_oPop->GetHeightCode(p_oTree6->GetSpecies(), p_oTree6->GetType()), &fHeight);
  CPPUNIT_ASSERT(fabs(fExpectedDiam - fDiam) < 0.001);
  CPPUNIT_ASSERT(fabs(fExpectedHeight - fHeight) < 0.001);
}

////////////////////////////////////////////////////////////////////////////
// WriteXMLFile1()
////////////////////////////////////////////////////////////////////////////
const char* clTestAllometricGrowthIncrementer::WriteXMLFile1() {
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
       << "<yearsPerTimestep>3</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>200.0</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\" />"
       << "<tr_species speciesName=\"Species_2\" />"
       << "</tr_speciesList>"
       << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_2\">10.0</tr_madVal>"
       << "</tr_minAdultDBH>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>"
       << "</trees>"
       << "<allometry>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_2\">39.54</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_2\">0.0614</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">0.5944</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.368</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_2\">0.0269</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_2\">0.0241</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
       << "<tr_whatSeedlingHeightDiam>"
       << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_2\">0</tr_wsehdVal>"
       << "</tr_whatSeedlingHeightDiam>"
       << "<tr_whatSaplingHeightDiam>"
       << "<tr_wsahdVal species=\"Species_1\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_2\">0</tr_wsahdVal>"
       << "</tr_whatSaplingHeightDiam>"
       << "<tr_whatAdultHeightDiam>"
       << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_2\">0</tr_wahdVal>"
       << "</tr_whatAdultHeightDiam>"
       << "<tr_whatAdultCrownRadDiam>"
       << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_2\">0</tr_wacrdVal>"
       << "</tr_whatAdultCrownRadDiam>"
       << "<tr_whatAdultCrownHeightHeight>"
       << "<tr_wachhVal species=\"Species_1\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_2\">0</tr_wachhVal>"
       << "</tr_whatAdultCrownHeightHeight>"
       << "<tr_whatSaplingCrownRadDiam>"
       << "<tr_wscrdVal species=\"Species_1\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_2\">0</tr_wscrdVal>"
       << "</tr_whatSaplingCrownRadDiam>"
       << "<tr_whatSaplingCrownHeightHeight>"
       << "<tr_wschhVal species=\"Species_1\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_2\">0</tr_wschhVal>"
       << "</tr_whatSaplingCrownHeightHeight>"
       << "</allometry>"
       << "<behaviorList>"
       << "<behavior>"
       //Leave in one light so that "Light" will be registerd
       << "<behaviorName>ConstantGLI</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>HeightIncrementer</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>ConstBAGrowth diam only</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>ConstRadialGrowth diam only</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>4</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<ConstantGLI1>"
       << "<li_constGLI>100</li_constGLI>"
       << "</ConstantGLI1>"
       << "<ConstBAGrowth3>"
       << "<gr_adultConstAreaInc>"
       << "<gr_acaiVal species=\"Species_2\">0.13</gr_acaiVal>"
       << "<gr_acaiVal species=\"Species_1\">0.2</gr_acaiVal>"
       << "</gr_adultConstAreaInc>"
       << "</ConstBAGrowth3>"
       << "<ConstRadialGrowth4>"
       << "<gr_adultConstRadialInc>"
       << "<gr_acriVal species=\"Species_1\">3.5</gr_acriVal>"
       << "<gr_acriVal species=\"Species_2\">1.45</gr_acriVal>"
       << "</gr_adultConstRadialInc>"
       << "</ConstRadialGrowth4>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteXMLFile2()
////////////////////////////////////////////////////////////////////////////
const char* clTestAllometricGrowthIncrementer::WriteXMLFile2() {
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
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\" />"
       << "<tr_species speciesName=\"Species_2\" />"
       << "</tr_speciesList>"
       << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_2\">10.0</tr_madVal>"
       << "</tr_minAdultDBH>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>"
       << "</trees>"
       << "<allometry>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_2\">39.54</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_2\">0.0614</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.78</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">0.66</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.368</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_adultLinearSlope>"
       << "<tr_alsVal species=\"Species_1\">0.66</tr_alsVal>"
       << "<tr_alsVal species=\"Species_2\">0.82</tr_alsVal>"
       << "</tr_adultLinearSlope>"
       << "<tr_adultLinearIntercept>"
       << "<tr_aliVal species=\"Species_1\">0.76</tr_aliVal>"
       << "<tr_aliVal species=\"Species_2\">-0.08</tr_aliVal>"
       << "</tr_adultLinearIntercept>"
       << "<tr_saplingLinearSlope>"
       << "<tr_salsVal species=\"Species_1\">1.22</tr_salsVal>"
       << "<tr_salsVal species=\"Species_2\">0.78</tr_salsVal>"
       << "</tr_saplingLinearSlope>"
       << "<tr_saplingLinearIntercept>"
       << "<tr_saliVal species=\"Species_1\">0.84</tr_saliVal>"
       << "<tr_saliVal species=\"Species_2\">0.22</tr_saliVal>"
       << "</tr_saplingLinearIntercept>"
       << "<tr_seedlingLinearSlope>"
       << "<tr_selsVal species=\"Species_1\">0.96</tr_selsVal>"
       << "<tr_selsVal species=\"Species_2\">0.89</tr_selsVal>"
       << "</tr_seedlingLinearSlope>"
       << "<tr_seedlingLinearIntercept>"
       << "<tr_seliVal species=\"Species_1\">-0.258</tr_seliVal>"
       << "<tr_seliVal species=\"Species_2\">-0.33</tr_seliVal>"
       << "</tr_seedlingLinearIntercept>"
       << "<tr_whatSeedlingHeightDiam>"
       << "<tr_wsehdVal species=\"Species_1\">1</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_2\">1</tr_wsehdVal>"
       << "</tr_whatSeedlingHeightDiam>"
       << "<tr_whatSaplingHeightDiam>"
       << "<tr_wsahdVal species=\"Species_1\">1</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_2\">1</tr_wsahdVal>"
       << "</tr_whatSaplingHeightDiam>"
       << "<tr_whatAdultHeightDiam>"
       << "<tr_wahdVal species=\"Species_1\">1</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_2\">1</tr_wahdVal>"
       << "</tr_whatAdultHeightDiam>"
       << "<tr_whatAdultCrownRadDiam>"
       << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_2\">0</tr_wacrdVal>"
       << "</tr_whatAdultCrownRadDiam>"
       << "<tr_whatAdultCrownHeightHeight>"
       << "<tr_wachhVal species=\"Species_1\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_2\">0</tr_wachhVal>"
       << "</tr_whatAdultCrownHeightHeight>"
       << "<tr_whatSaplingCrownRadDiam>"
       << "<tr_wscrdVal species=\"Species_1\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_2\">0</tr_wscrdVal>"
       << "</tr_whatSaplingCrownRadDiam>"
       << "<tr_whatSaplingCrownHeightHeight>"
       << "<tr_wschhVal species=\"Species_1\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_2\">0</tr_wschhVal>"
       << "</tr_whatSaplingCrownHeightHeight>"
       << "</allometry>"
       << "<behaviorList>"
       << "<behavior>"
       //Leave in one light so that "Light" will be registerd
       << "<behaviorName>ConstantGLI</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>DiameterIncrementer</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>SimpleLinearGrowth height only</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<ConstantGLI1>"
       << "<li_constGLI>50</li_constGLI>"
       << "</ConstantGLI1>"
       << "<SimpleLinearGrowth3>"
       << "<gr_heightSimpleLinearSlope>"
       << "<gr_hslsVal species=\"Species_1\">0.75</gr_hslsVal>"
       << "<gr_hslsVal species=\"Species_2\">0.86</gr_hslsVal>"
       << "</gr_heightSimpleLinearSlope>"
       << "<gr_heightSimpleLinearIntercept>"
       << "<gr_hsliVal species=\"Species_1\">0.331</gr_hsliVal>"
       << "<gr_hsliVal species=\"Species_2\">0.576</gr_hsliVal>"
       << "</gr_heightSimpleLinearIntercept>"
       << "</SimpleLinearGrowth3>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

