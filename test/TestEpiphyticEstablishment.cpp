//---------------------------------------------------------------------------
// TestEpiphyticEstablishment.cpp
//---------------------------------------------------------------------------
#include "TestEpiphyticEstablishment.h"
#include <cppunit/TestCaller.h>
#include <fstream>
#include <math.h>
#include "SimManager.h"
#include "TreePopulation.h"

/////////////////////////////////////////////////////////////////////////////
//  TestEpiphyticEstablishment()
/////////////////////////////////////////////////////////////////////////////
void clTestEpiphyticEstablishment::TestEpiphyticEstablishment() {

  clSimManager *p_oSimManager = new clSimManager(3, 3, "");

  TestNormalProcessingRun1(p_oSimManager);
  TestNormalProcessingRun2(p_oSimManager);
  TestErrorProcessing(p_oSimManager);

  //Clean up
   delete p_oSimManager;
}

/////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun1()
/////////////////////////////////////////////////////////////////////////////
void clTestEpiphyticEstablishment::TestNormalProcessingRun1(clSimManager *p_oSimManager) {

  clTreePopulation *p_oPop;
  clTree *p_oTree;
  clTreeSearch *p_oSeedlings;
  float fX, fY, fDiam, fHeight, fExpectedHeight;
  int iNum1Seedlings = 0, iNum2Seedlings = 0, i, iSp;

  //Run 1: WriteXMLFile1() does setup.
  p_oSimManager->ReadFile(WriteXMLFile1());
  p_oPop = (clTreePopulation *)p_oSimManager->GetPopulationObject("treepopulation");

  //Add the substrate trees
  fX = 1; fY = 1; fDiam = 10; fHeight = 1.5; iSp = 0;
  for (i = 0; i < 1000; i++) {
    p_oTree = p_oPop->CreateTree (fX, fY, iSp, clTreePopulation::adult, fDiam);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), fHeight, true, true);
  }
  fX = 22; fY = 22; fDiam = 12; fHeight = 1.7; iSp = 2;
  for (i = 0; i < 1000; i++) {
    p_oTree = p_oPop->CreateTree (fX, fY, iSp, clTreePopulation::adult, fDiam);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), fHeight, true, true);
  }
  fX = 55; fY = 55; fDiam = 9; fHeight = 1.3; iSp = 2;
  for (i = 0; i < 1000; i++) {
    p_oTree = p_oPop->CreateTree (fX, fY, iSp, clTreePopulation::sapling, fDiam);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), fHeight, true, true);
  }
  fX = 77; fY = 77; fDiam = 8; fHeight = 1.1; iSp = 0;
  for (i = 0; i < 1000; i++) {
    p_oTree = p_oPop->CreateTree (fX, fY, iSp, clTreePopulation::sapling, fDiam);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), fHeight, true, true);
  }

  //Run a timestep
  p_oSimManager->RunSim(1);

  //Count the resulting seedlings
  p_oSeedlings = p_oPop->Find("all");
  p_oTree = p_oSeedlings->NextTree();
  while (p_oTree) {
    if (p_oTree->GetSpecies() == 1) {
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
      if (fX == 1) {
        p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
        fExpectedHeight = 0.5343;
        CPPUNIT_ASSERT(fabs(fHeight - fExpectedHeight) < 0.01);
        iNum1Seedlings++;
      }
      else if (fX == 22) {
        p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
        //CPPUNIT_ASSERT(p_oTree->GetType() == clTreePopulation::sapling);
        fExpectedHeight = 1.73292;
        CPPUNIT_ASSERT(fabs(fHeight - fExpectedHeight) < 0.01);
        iNum2Seedlings++;
      } else {
        CppUnit::Asserter::fail( "Seedling in unexpected location." );
      }
    }
    p_oTree = p_oSeedlings->NextTree();
  }

  CPPUNIT_ASSERT(fabs(iNum1Seedlings - 236) < 20);
  CPPUNIT_ASSERT(fabs(iNum2Seedlings - 392) < 20);
}


/////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun2()
/////////////////////////////////////////////////////////////////////////////
void clTestEpiphyticEstablishment::TestNormalProcessingRun2(clSimManager *p_oSimManager) {

  clTreePopulation *p_oPop;
  clTree *p_oTree;
  clTreeSearch *p_oSeedlings;
  float fX, fY, fDiam, fHeight, fExpectedHeight;
  int i, iSp, iNum1Seedlings = 0;

  //Run 1: WriteXMLFile2() does setup.
  p_oSimManager->ReadFile(WriteXMLFile2());
  p_oPop = (clTreePopulation *)p_oSimManager->GetPopulationObject("treepopulation");

  //Add the list of known neighbors for GLI
  iSp = 1;
  fX = 65; fY = 66; fDiam = 25;
  p_oPop->CreateTree (fX, fY, iSp, clTreePopulation::adult, fDiam);
  fX = 50; fY = 50; fDiam = 11;
  p_oPop->CreateTree (fX, fY, iSp, clTreePopulation::adult, fDiam);
  fX = 56.1; fY = 50; fDiam = 45;
  p_oPop->CreateTree (fX, fY, iSp, clTreePopulation::adult, fDiam);
  fX = 56; fY = 56; fDiam = 61;
  p_oPop->CreateTree (fX, fY, iSp, clTreePopulation::adult, fDiam);
  fX = 51; fY = 57; fDiam = 15;
  p_oPop->CreateTree (fX, fY, iSp, clTreePopulation::adult, fDiam);
  fX = 59; fY = 57; fDiam = 45;
  p_oPop->CreateTree (fX, fY, iSp, clTreePopulation::adult, fDiam);

  //Add the substrate trees
  fX = 55; fY = 55; fDiam = 12; fHeight = 8; iSp = 0;
  for (i = 0; i < 1000; i++) {
    p_oTree = p_oPop->CreateTree (fX, fY, iSp, clTreePopulation::adult, fDiam);
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), fHeight, true, true);
  }

  //Run a timestep
  p_oSimManager->RunSim(1);

  //Count the resulting seedlings
  p_oSeedlings = p_oPop->Find("all");
  p_oTree = p_oSeedlings->NextTree();
  while (p_oTree) {
    if (p_oTree->GetSpecies() == 2) {
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
      CPPUNIT_ASSERT(fX == 55);
      p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fHeight);
      fExpectedHeight = 0.8287;
      CPPUNIT_ASSERT(fabs(fHeight - fExpectedHeight) < 0.01);
      iNum1Seedlings++;
    }

    p_oTree = p_oSeedlings->NextTree();
  }

  CPPUNIT_ASSERT(fabs(iNum1Seedlings - 851) < 40);

}

/////////////////////////////////////////////////////////////////////////////
//  TestErrorProcessing()
/////////////////////////////////////////////////////////////////////////////
void clTestEpiphyticEstablishment::TestErrorProcessing(clSimManager *p_oSimManager) {

  try
  {
    p_oSimManager->ReadFile(WriteXMLErrorFile1());
    CppUnit::Asserter::fail("TestEpiphyticEstablishment error processing didn't catch error for WriteXMLErrorFile1.");
  }
  catch (modelErr& err)
  {
    if (strstr(err.cFunction, "clEpiphyticEstablishment::GetParameterFileData") == NULL)
    {
      CppUnit::Asserter::fail("TestEpiphyticEstablishment error processing caught wrong error for WriteXMLErrorFile1.");
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteXMLErrorFile2());
    CppUnit::Asserter::fail("TestEpiphyticEstablishment error processing didn't catch error for WriteXMLErrorFile2.");
  }
  catch (modelErr& err)
  {
    if (strstr(err.cFunction, "clEpiphyticEstablishment::GetParameterFileData") == NULL)
    {
      CppUnit::Asserter::fail("TestEpiphyticEstablishment error processing caught wrong error for WriteXMLErrorFile2.");
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteXMLErrorFile3());
    CppUnit::Asserter::fail("TestEpiphyticEstablishment error processing didn't catch error for WriteXMLErrorFile3.");
  }
  catch (modelErr& err)
  {
    if (strstr(err.cFunction, "clEpiphyticEstablishment::GetTreeDataMemberCodes") == NULL)
    {
      CppUnit::Asserter::fail("TestEpiphyticEstablishment error processing caught wrong error for WriteXMLErrorFile3.");
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteXMLErrorFile3());
    CppUnit::Asserter::fail("TestEpiphyticEstablishment error processing didn't catch error for WriteXMLErrorFile3.");
  }
  catch (modelErr& err)
  {
    if (strstr(err.cFunction, "clEpiphyticEstablishment::GetTreeDataMemberCodes") == NULL)
    {
      CppUnit::Asserter::fail("TestEpiphyticEstablishment error processing caught wrong error for WriteXMLErrorFile3.");
    }
    ;
  }
}

////////////////////////////////////////////////////////////////////////////
//  WriteXMLFile1()
////////////////////////////////////////////////////////////////////////////
const char* clTestEpiphyticEstablishment::WriteXMLFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>3</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>100.0</plot_lenX>"
       << "<plot_lenY>100.0</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12</plot_temp_C>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\" />"
       << "<tr_species speciesName=\"Species_2\" />"
       << "<tr_species speciesName=\"Species_3\" />"
       << "</tr_speciesList>"
       << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_2\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_3\">10.0</tr_madVal>"
       << "</tr_minAdultDBH>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"Species_1\">1</tr_mshVal>"
       << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_3\">1</tr_mshVal>"
       << "</tr_maxSeedlingHeight>"
       << "</trees>"
       << "<allometry>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_2\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_3\">39.48</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_2\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_3\">0.0549</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_3\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">1</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">1</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_3\">1</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_3\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_whatSeedlingHeightDiam>"
       << "<tr_wsehdVal species=\"Species_1\">1</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_2\">1</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_3\">1</tr_wsehdVal>"
       << "</tr_whatSeedlingHeightDiam>"
       << "<tr_whatSaplingHeightDiam>"
       << "<tr_wsahdVal species=\"Species_1\">1</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_2\">1</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_3\">1</tr_wsahdVal>"
       << "</tr_whatSaplingHeightDiam>"
       << "<tr_whatAdultHeightDiam>"
       << "<tr_wahdVal species=\"Species_1\">1</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_2\">1</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_3\">1</tr_wahdVal>"
       << "</tr_whatAdultHeightDiam>"
       << "<tr_whatAdultCrownRadDiam>"
       << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_2\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_3\">0</tr_wacrdVal>"
       << "</tr_whatAdultCrownRadDiam>"
       << "<tr_whatAdultCrownHeightHeight>"
       << "<tr_wachhVal species=\"Species_1\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_2\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_3\">0</tr_wachhVal>"
       << "</tr_whatAdultCrownHeightHeight>"
       << "<tr_whatSaplingCrownRadDiam>"
       << "<tr_wscrdVal species=\"Species_1\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_2\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_3\">0</tr_wscrdVal>"
       << "</tr_whatSaplingCrownRadDiam>"
       << "<tr_whatSaplingCrownHeightHeight>"
       << "<tr_wschhVal species=\"Species_1\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_2\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_3\">0</tr_wschhVal>"
       << "</tr_whatSaplingCrownHeightHeight>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.589</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.589</tr_sachVal>"
       << "<tr_sachVal species=\"Species_3\">0.589</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_3\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_adultLinearSlope>"
       << "<tr_alsVal species=\"Species_1\">0.1299</tr_alsVal>"
       << "<tr_alsVal species=\"Species_2\">0.1299</tr_alsVal>"
       << "<tr_alsVal species=\"Species_3\">0.1299</tr_alsVal>"
       << "</tr_adultLinearSlope>"
       << "<tr_adultLinearIntercept>"
       << "<tr_aliVal species=\"Species_1\">0.1</tr_aliVal>"
       << "<tr_aliVal species=\"Species_2\">0.1</tr_aliVal>"
       << "<tr_aliVal species=\"Species_3\">0.1</tr_aliVal>"
       << "</tr_adultLinearIntercept>"
       << "<tr_saplingLinearSlope>"
       << "<tr_salsVal species=\"Species_1\">0.1299</tr_salsVal>"
       << "<tr_salsVal species=\"Species_2\">0.1299</tr_salsVal>"
       << "<tr_salsVal species=\"Species_3\">0.1299</tr_salsVal>"
       << "</tr_saplingLinearSlope>"
       << "<tr_saplingLinearIntercept>"
       << "<tr_saliVal species=\"Species_1\">0.1</tr_saliVal>"
       << "<tr_saliVal species=\"Species_2\">0.1</tr_saliVal>"
       << "<tr_saliVal species=\"Species_3\">0.1</tr_saliVal>"
       << "</tr_saplingLinearIntercept>"
       << "<tr_seedlingLinearSlope>"
       << "<tr_selsVal species=\"Species_1\">0.1299</tr_selsVal>"
       << "<tr_selsVal species=\"Species_2\">0.1299</tr_selsVal>"
       << "<tr_selsVal species=\"Species_3\">0.1299</tr_selsVal>"
       << "</tr_seedlingLinearSlope>"
       << "<tr_seedlingLinearIntercept>"
       << "<tr_seliVal species=\"Species_1\">0.1</tr_seliVal>"
       << "<tr_seliVal species=\"Species_2\">0.1</tr_seliVal>"
       << "<tr_seliVal species=\"Species_3\">0.1</tr_seliVal>"
       << "</tr_seedlingLinearIntercept>"
       << "</allometry>";

  //Write file
  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>EpiphyticEstablishment</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RemoveDead</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>4</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<EpiphyticEstablishment3>"
       << "<li_beamFractGlobalRad>0.5</li_beamFractGlobalRad>"
       << "<li_clearSkyTransCoeff>0.65</li_clearSkyTransCoeff>"
       << "<li_julianDayGrowthStarts>105</li_julianDayGrowthStarts>"
       << "<li_julianDayGrowthEnds>258</li_julianDayGrowthEnds>"
       << "<li_minSunAngle>0.785</li_minSunAngle>"
       << "<li_numAltGrids>12</li_numAltGrids>"
       << "<li_numAziGrids>18</li_numAziGrids>"
       << "<li_lightExtinctionCoefficient>"
       << "<li_lecVal species=\"Species_1\">1</li_lecVal>"
       << "<li_lecVal species=\"Species_2\">1</li_lecVal>"
       << "<li_lecVal species=\"Species_3\">1</li_lecVal>"
       << "</li_lightExtinctionCoefficient>"
       << "<ep_epiphyticA>"
       << "<ep_eaVal species=\"Species_1\">-3.6482</ep_eaVal>"
       << "<ep_eaVal species=\"Species_3\">-6.1567</ep_eaVal>"
       << "</ep_epiphyticA>"
       << "<ep_epiphyticB>"
       << "<ep_ebVal species=\"Species_1\">0.5442</ep_ebVal>"
       << "<ep_ebVal species=\"Species_3\">1.0008</ep_ebVal>"
       << "</ep_epiphyticB>"
       << "<ep_epiphyticC>"
       << "<ep_ecVal species=\"Species_1\">0.016595</ep_ecVal>"
       << "<ep_ecVal species=\"Species_3\">0.040162</ep_ecVal>"
       << "</ep_epiphyticC>"
       << "<ep_epiphyticM>"
       << "<ep_emVal species=\"Species_1\">-27.21</ep_emVal>"
       << "<ep_emVal species=\"Species_3\">-16.87</ep_emVal>"
       << "</ep_epiphyticM>"
       << "<ep_epiphyticN>"
       << "<ep_enVal species=\"Species_1\">53.76</ep_enVal>"
       << "<ep_enVal species=\"Species_3\">111.86</ep_enVal>"
       << "</ep_epiphyticN>"
       << "<ep_epiphyticSeedlingSpecies>1</ep_epiphyticSeedlingSpecies>"
       << "</EpiphyticEstablishment3>"
       << "<StochasticMortality1>"
       << "<mo_stochasticMortRate>"
       << "<mo_smrVal species=\"Species_1\">1</mo_smrVal>"
       << "<mo_smrVal species=\"Species_3\">1</mo_smrVal>"
       << "</mo_stochasticMortRate>"
       << "</StochasticMortality1>"
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
const char* clTestEpiphyticEstablishment::WriteXMLFile2() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>3</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>100.0</plot_lenX>"
       << "<plot_lenY>100.0</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12</plot_temp_C>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\" />"
       << "<tr_species speciesName=\"Species_2\" />"
       << "<tr_species speciesName=\"Species_3\" />"
       << "</tr_speciesList>"
       << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_2\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_3\">10.0</tr_madVal>"
       << "</tr_minAdultDBH>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"Species_1\">1</tr_mshVal>"
       << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_3\">1</tr_mshVal>"
       << "</tr_maxSeedlingHeight>"
       << "</trees>"
       << "<allometry>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_2\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_3\">39.48</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_2\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_3\">0.0549</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_3\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">1</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">1</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_3\">1</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_3\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.5</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.589</tr_sachVal>"
       << "<tr_sachVal species=\"Species_3\">0.589</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_3\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_2\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_3\">0.03418</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_2\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_3\">0.0299</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
       << "<tr_whatSeedlingHeightDiam>"
       << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_2\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_3\">0</tr_wsehdVal>"
       << "</tr_whatSeedlingHeightDiam>"
       << "<tr_whatSaplingHeightDiam>"
       << "<tr_wsahdVal species=\"Species_1\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_2\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_3\">0</tr_wsahdVal>"
       << "</tr_whatSaplingHeightDiam>"
       << "<tr_whatAdultHeightDiam>"
       << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_2\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_3\">0</tr_wahdVal>"
       << "</tr_whatAdultHeightDiam>"
       << "<tr_whatAdultCrownRadDiam>"
       << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_2\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_3\">0</tr_wacrdVal>"
       << "</tr_whatAdultCrownRadDiam>"
       << "<tr_whatAdultCrownHeightHeight>"
       << "<tr_wachhVal species=\"Species_1\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_2\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_3\">0</tr_wachhVal>"
       << "</tr_whatAdultCrownHeightHeight>"
       << "<tr_whatSaplingCrownRadDiam>"
       << "<tr_wscrdVal species=\"Species_1\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_2\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_3\">0</tr_wscrdVal>"
       << "</tr_whatSaplingCrownRadDiam>"
       << "<tr_whatSaplingCrownHeightHeight>"
       << "<tr_wschhVal species=\"Species_1\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_2\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_3\">0</tr_wschhVal>"
       << "</tr_whatSaplingCrownHeightHeight>"
       << "</allometry>";

  //Write file
  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>EpiphyticEstablishment</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RemoveDead</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<EpiphyticEstablishment2>"
       << "<li_beamFractGlobalRad>0.5</li_beamFractGlobalRad>"
       << "<li_clearSkyTransCoeff>0.65</li_clearSkyTransCoeff>"
       << "<li_julianDayGrowthStarts>105</li_julianDayGrowthStarts>"
       << "<li_julianDayGrowthEnds>258</li_julianDayGrowthEnds>"
       << "<li_minSunAngle>0.785</li_minSunAngle>"
       << "<li_numAltGrids>12</li_numAltGrids>"
       << "<li_numAziGrids>18</li_numAziGrids>"
       << "<li_lightExtinctionCoefficient>"
       << "<li_lecVal species=\"Species_1\">0.2</li_lecVal>"
       << "<li_lecVal species=\"Species_2\">0.2</li_lecVal>"
       << "<li_lecVal species=\"Species_3\">0.2</li_lecVal>"
       << "</li_lightExtinctionCoefficient>"
       << "<ep_epiphyticA>"
       << "<ep_eaVal species=\"Species_1\">-3.6482</ep_eaVal>"
       << "</ep_epiphyticA>"
       << "<ep_epiphyticB>"
       << "<ep_ebVal species=\"Species_1\">0.5442</ep_ebVal>"
       << "</ep_epiphyticB>"
       << "<ep_epiphyticC>"
       << "<ep_ecVal species=\"Species_1\">0.016595</ep_ecVal>"
       << "</ep_epiphyticC>"
       << "<ep_epiphyticM>"
       << "<ep_emVal species=\"Species_1\">-27.21</ep_emVal>"
       << "</ep_epiphyticM>"
       << "<ep_epiphyticN>"
       << "<ep_enVal species=\"Species_1\">13.76</ep_enVal>"
       << "</ep_epiphyticN>"
       << "<ep_epiphyticSeedlingSpecies>2</ep_epiphyticSeedlingSpecies>"
       << "</EpiphyticEstablishment2>"
       << "<StochasticMortality1>"
       << "<mo_stochasticMortRate>"
       << "<mo_smrVal species=\"Species_1\">1</mo_smrVal>"
       << "</mo_stochasticMortRate>"
       << "</StochasticMortality1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
//  WriteErrorCommonStuff()
////////////////////////////////////////////////////////////////////////////
void clTestEpiphyticEstablishment::WriteErrorCommonStuff(std::fstream &oOut) {
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>3</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>100.0</plot_lenX>"
       << "<plot_lenY>100.0</plot_lenY>"
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
       << "<tr_mshVal species=\"Species_1\">1</tr_mshVal>"
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
       << "<tr_cdtdVal species=\"Species_1\">1</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_whatSeedlingHeightDiam>"
       << "<tr_wsehdVal species=\"Species_1\">1</tr_wsehdVal>"
       << "</tr_whatSeedlingHeightDiam>"
       << "<tr_whatSaplingHeightDiam>"
       << "<tr_wsahdVal species=\"Species_1\">1</tr_wsahdVal>"
       << "</tr_whatSaplingHeightDiam>"
       << "<tr_whatAdultHeightDiam>"
       << "<tr_wahdVal species=\"Species_1\">1</tr_wahdVal>"
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
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.589</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_adultLinearSlope>"
       << "<tr_alsVal species=\"Species_1\">0.1299</tr_alsVal>"
       << "</tr_adultLinearSlope>"
       << "<tr_adultLinearIntercept>"
       << "<tr_aliVal species=\"Species_1\">0.1</tr_aliVal>"
       << "</tr_adultLinearIntercept>"
       << "<tr_saplingLinearSlope>"
       << "<tr_salsVal species=\"Species_1\">0.1299</tr_salsVal>"
       << "</tr_saplingLinearSlope>"
       << "<tr_saplingLinearIntercept>"
       << "<tr_saliVal species=\"Species_1\">0.1</tr_saliVal>"
       << "</tr_saplingLinearIntercept>"
       << "<tr_seedlingLinearSlope>"
       << "<tr_selsVal species=\"Species_1\">0.1299</tr_selsVal>"
       << "</tr_seedlingLinearSlope>"
       << "<tr_seedlingLinearIntercept>"
       << "<tr_seliVal species=\"Species_1\">0.1</tr_seliVal>"
       << "</tr_seedlingLinearIntercept>"
       << "</allometry>";

}

////////////////////////////////////////////////////////////////////////////
// WriteXMLErrorFile1()
////////////////////////////////////////////////////////////////////////////
const char* clTestEpiphyticEstablishment::WriteXMLErrorFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteErrorCommonStuff(oOut);

  //Write file
  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>EpiphyticEstablishment</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RemoveDead</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<EpiphyticEstablishment2>"
       << "<li_beamFractGlobalRad>0.5</li_beamFractGlobalRad>"
       << "<li_clearSkyTransCoeff>0.65</li_clearSkyTransCoeff>"
       << "<li_julianDayGrowthStarts>105</li_julianDayGrowthStarts>"
       << "<li_julianDayGrowthEnds>258</li_julianDayGrowthEnds>"
       << "<li_minSunAngle>0.785</li_minSunAngle>"
       << "<li_numAltGrids>-12</li_numAltGrids>"
       << "<li_numAziGrids>18</li_numAziGrids>"
       << "<li_lightExtinctionCoefficient>"
       << "<li_lecVal species=\"Species_1\">0</li_lecVal>"
       << "</li_lightExtinctionCoefficient>"
       << "<ep_epiphyticA>"
       << "<ep_eaVal species=\"Species_1\">-3.6482</ep_eaVal>"
       << "</ep_epiphyticA>"
       << "<ep_epiphyticB>"
       << "<ep_ebVal species=\"Species_1\">0.5442</ep_ebVal>"
       << "</ep_epiphyticB>"
       << "<ep_epiphyticC>"
       << "<ep_ecVal species=\"Species_1\">0.016595</ep_ecVal>"
       << "</ep_epiphyticC>"
       << "<ep_epiphyticM>"
       << "<ep_emVal species=\"Species_1\">-27.21</ep_emVal>"
       << "</ep_epiphyticM>"
       << "<ep_epiphyticN>"
       << "<ep_enVal species=\"Species_1\">53.76</ep_enVal>"
       << "</ep_epiphyticN>"
       << "<ep_epiphyticSeedlingSpecies>2</ep_epiphyticSeedlingSpecies>"
       << "</EpiphyticEstablishment2>"
       << "<StochasticMortality1>"
       << "<mo_stochasticMortRate>"
       << "<mo_smrVal species=\"Species_1\">1</mo_smrVal>"
       << "</mo_stochasticMortRate>"
       << "</StochasticMortality1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteXMLErrorFile2()
////////////////////////////////////////////////////////////////////////////
const char* clTestEpiphyticEstablishment::WriteXMLErrorFile2() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteErrorCommonStuff(oOut);

  //Write file
  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>EpiphyticEstablishment</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RemoveDead</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<EpiphyticEstablishment2>"
       << "<li_beamFractGlobalRad>0.5</li_beamFractGlobalRad>"
       << "<li_clearSkyTransCoeff>0.65</li_clearSkyTransCoeff>"
       << "<li_julianDayGrowthStarts>105</li_julianDayGrowthStarts>"
       << "<li_julianDayGrowthEnds>258</li_julianDayGrowthEnds>"
       << "<li_minSunAngle>0.785</li_minSunAngle>"
       << "<li_numAltGrids>12</li_numAltGrids>"
       << "<li_numAziGrids>-18</li_numAziGrids>"
       << "<li_lightExtinctionCoefficient>"
       << "<li_lecVal species=\"Species_1\">0</li_lecVal>"
       << "</li_lightExtinctionCoefficient>"
       << "<ep_epiphyticA>"
       << "<ep_eaVal species=\"Species_1\">-3.6482</ep_eaVal>"
       << "</ep_epiphyticA>"
       << "<ep_epiphyticB>"
       << "<ep_ebVal species=\"Species_1\">0.5442</ep_ebVal>"
       << "</ep_epiphyticB>"
       << "<ep_epiphyticC>"
       << "<ep_ecVal species=\"Species_1\">0.016595</ep_ecVal>"
       << "</ep_epiphyticC>"
       << "<ep_epiphyticM>"
       << "<ep_emVal species=\"Species_1\">-27.21</ep_emVal>"
       << "</ep_epiphyticM>"
       << "<ep_epiphyticN>"
       << "<ep_enVal species=\"Species_1\">53.76</ep_enVal>"
       << "</ep_epiphyticN>"
       << "<ep_epiphyticSeedlingSpecies>2</ep_epiphyticSeedlingSpecies>"
       << "</EpiphyticEstablishment2>"
       << "<StochasticMortality1>"
       << "<mo_stochasticMortRate>"
       << "<mo_smrVal species=\"Species_1\">1</mo_smrVal>"
       << "</mo_stochasticMortRate>"
       << "</StochasticMortality1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteXMLErrorFile3()
////////////////////////////////////////////////////////////////////////////
const char* clTestEpiphyticEstablishment::WriteXMLErrorFile3() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteErrorCommonStuff(oOut);

  //Write file
  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>EpiphyticEstablishment</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RemoveDead</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<EpiphyticEstablishment2>"
       << "<li_beamFractGlobalRad>0.5</li_beamFractGlobalRad>"
       << "<li_clearSkyTransCoeff>0.65</li_clearSkyTransCoeff>"
       << "<li_julianDayGrowthStarts>105</li_julianDayGrowthStarts>"
       << "<li_julianDayGrowthEnds>258</li_julianDayGrowthEnds>"
       << "<li_minSunAngle>0.785</li_minSunAngle>"
       << "<li_numAltGrids>12</li_numAltGrids>"
       << "<li_numAziGrids>18</li_numAziGrids>"
       << "<li_lightExtinctionCoefficient>"
       << "<li_lecVal species=\"Species_1\">0</li_lecVal>"
       << "</li_lightExtinctionCoefficient>"
       << "<ep_epiphyticA>"
       << "<ep_eaVal species=\"Species_1\">-3.6482</ep_eaVal>"
       << "</ep_epiphyticA>"
       << "<ep_epiphyticB>"
       << "<ep_ebVal species=\"Species_1\">0.5442</ep_ebVal>"
       << "</ep_epiphyticB>"
       << "<ep_epiphyticC>"
       << "<ep_ecVal species=\"Species_1\">0.016595</ep_ecVal>"
       << "</ep_epiphyticC>"
       << "<ep_epiphyticM>"
       << "<ep_emVal species=\"Species_1\">-27.21</ep_emVal>"
       << "</ep_epiphyticM>"
       << "<ep_epiphyticN>"
       << "<ep_enVal species=\"Species_1\">53.76</ep_enVal>"
       << "</ep_epiphyticN>"
       << "<ep_epiphyticSeedlingSpecies>2</ep_epiphyticSeedlingSpecies>"
       << "</EpiphyticEstablishment2>"
       << "<StochasticMortality1>"
       << "<mo_stochasticMortRate>"
       << "<mo_smrVal species=\"Species_1\">1</mo_smrVal>"
       << "</mo_stochasticMortRate>"
       << "</StochasticMortality1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteXMLErrorFile4()
////////////////////////////////////////////////////////////////////////////
const char* clTestEpiphyticEstablishment::WriteXMLErrorFile4() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteErrorCommonStuff(oOut);

  //Write file
  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>EpiphyticEstablishment</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RemoveDead</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<EpiphyticEstablishment2>"
       << "<li_beamFractGlobalRad>0.5</li_beamFractGlobalRad>"
       << "<li_clearSkyTransCoeff>0.65</li_clearSkyTransCoeff>"
       << "<li_julianDayGrowthStarts>105</li_julianDayGrowthStarts>"
       << "<li_julianDayGrowthEnds>258</li_julianDayGrowthEnds>"
       << "<li_minSunAngle>0.785</li_minSunAngle>"
       << "<li_numAltGrids>12</li_numAltGrids>"
       << "<li_numAziGrids>18</li_numAziGrids>"
       << "<li_lightExtinctionCoefficient>"
       << "<li_lecVal species=\"Species_1\">0</li_lecVal>"
       << "</li_lightExtinctionCoefficient>"
       << "<ep_epiphyticA>"
       << "<ep_eaVal species=\"Species_1\">-3.6482</ep_eaVal>"
       << "</ep_epiphyticA>"
       << "<ep_epiphyticB>"
       << "<ep_ebVal species=\"Species_1\">0.5442</ep_ebVal>"
       << "</ep_epiphyticB>"
       << "<ep_epiphyticC>"
       << "<ep_ecVal species=\"Species_1\">0.016595</ep_ecVal>"
       << "</ep_epiphyticC>"
       << "<ep_epiphyticM>"
       << "<ep_emVal species=\"Species_1\">-27.21</ep_emVal>"
       << "</ep_epiphyticM>"
       << "<ep_epiphyticN>"
       << "<ep_enVal species=\"Species_1\">53.76</ep_enVal>"
       << "</ep_epiphyticN>"
       << "<ep_epiphyticSeedlingSpecies>2</ep_epiphyticSeedlingSpecies>"
       << "</EpiphyticEstablishment2>"
       << "<StochasticMortality1>"
       << "<mo_stochasticMortRate>"
       << "<mo_smrVal species=\"Species_1\">1</mo_smrVal>"
       << "</mo_stochasticMortRate>"
       << "</StochasticMortality1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}
