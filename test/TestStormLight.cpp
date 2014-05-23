//---------------------------------------------------------------------------
// TestStormLight.cpp
//---------------------------------------------------------------------------
#include "TestStormLight.h"
#include "Grid.h"
#include "SimManager.h"
#include "BehaviorBase.h"
#include "TreePopulation.h"
#include <math.h>
#include <fstream>

/////////////////////////////////////////////////////////////////////////////
//  TestStormLight()
/////////////////////////////////////////////////////////////////////////////
void clTestStormLight::TestStormLight()
{

  clSimManager * p_oSimManager = new clSimManager(3, 3, "");

  NormalProcessingRun1(p_oSimManager);
  NormalProcessingRun2(p_oSimManager);
  TestErrorProcessing(p_oSimManager);

  //Clean up
  delete p_oSimManager;
}

////////////////////////////////////////////////////////////////////////////
//  TestErrorProcessing()
////////////////////////////////////////////////////////////////////////////
void clTestStormLight::TestErrorProcessing( clSimManager * p_oSimManager )
{

  try
  {
    p_oSimManager->ReadFile( WriteXMLErrorFile1() );
    CppUnit::Asserter::fail( "TestStormLight error processing didn't catch error for WriteXMLErrorFile1." );
  }
  catch ( modelErr& err )
  {
    if ( strstr( err.cFunction, "clStormLight::GetData" ) == NULL )
    {
      CppUnit::Asserter::fail( "TestStormLight error processing caught wrong error for WriteXMLErrorFile1." );
    }
    ;
  }
}

/////////////////////////////////////////////////////////////////////////////
//  NormalProcessingRun1()
/////////////////////////////////////////////////////////////////////////////
void clTestStormLight::NormalProcessingRun1(clSimManager *p_oSimManager)
{
  clTreePopulation *p_oPop;
  clGrid *p_oLightGrid;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;
  float fActualLight, fExpectedLight, fX, fY;
  int iLightCode, iDmg, i;


  //Feed our file to the sim manager
  p_oSimManager->ReadFile(WriteXMLFile1());
  p_oPop = (clTreePopulation*) p_oSimManager->GetPopulationObject("treepopulation");

  //Add the trees
  fX = 20;
  fY = 20;
  iDmg = 2002;
  p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::sapling, 5 );
  p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iDmg);

  fX = 21;
  fY = 21;
  iDmg = 0;
  p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, 20 );
  p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iDmg);

  fX = 22.5;
  fY = 22.5;
  p_oTree = p_oPop->CreateTree( fX, fY, 1, clTreePopulation::adult, 20 );

  fX = 22;
  fY = 22;
  iDmg = 1002;
  p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, 20 );
  p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iDmg);

  fX = 23;
  fY = 24;
  p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, 20 );

  fX = 23;
  fY = 23;
  iDmg = 1001;
  p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::snag, 20 );
  p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iDmg);

  fX = 24;
  fY = 24;
  iDmg = 2003;
  p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, 20 );
  p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iDmg);

  fX = 21;
  fY = 24;
  iDmg = 2002;
  p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::snag, 20 );
  p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iDmg);

  fX = 22;
  fY = 24;
  iDmg = 2000;
  p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, 20 );
  p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iDmg);

  fX = 23;
  fY = 24;
  iDmg = 2001;
  p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::snag, 20 );
  p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iDmg);

  fX = 1;
  fY = 80;
  iDmg = 0;
  p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, 20 );
  p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iDmg);

  fX = 2;
  fY = 81;
  iDmg = 6; //actually age
  p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::snag, 20 );
  p_oTree->SetValue( p_oPop->GetIntDataCode( "Age", p_oTree->GetSpecies(), p_oTree->GetType() ), iDmg);

  fX = 80;
  fY = 80;
  iDmg = 2000;
  for (i = 0; i < 200; i++) {
    p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, 20 );
    p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iDmg);
  }

  fX = 160;
  fY = 160;
  iDmg = 2002;
  p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, 20 );
  p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iDmg);

  fX = 152;
  fY = 164;
  iDmg = 2001;
  p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::snag, 20 );
  p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iDmg);

  fX = 162;
  fY = 162;
  iDmg = 1000;
  p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::snag, 20 );
  p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iDmg);

  fX = 163;
  fY = 163;
  iDmg = 2000;
  for (i = 0; i < 10; i++) {
    p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, 20 );
    p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iDmg);
  }

  fX = 164;
  fY = 180;
  iDmg = 2000;
  p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, 20 );
  p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iDmg);

  fX = 164;
  fY = 164;
  p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::seedling, 0.2 );

  fX = 80;
  fY = 164;
  for (i = 0; i < 10; i++) {
    p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, 20 );
  }

  fX = 160;
  fY = 80;
  iDmg = 2001;
  for (i = 0; i < 3; i++) {
    p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, 20 );
    p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iDmg);
  }

  fX = 161;
  fY = 80;
  iDmg = 4; //actually age
  p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::snag, 20 );
  p_oTree->SetValue( p_oPop->GetIntDataCode( "Age", p_oTree->GetSpecies(), p_oTree->GetType() ), iDmg);

  fX = 162;
  fY = 80;
  iDmg = 0; //actually age
  for (i = 0; i < 3; i++) {
    p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::snag, 20 );
    p_oTree->SetValue( p_oPop->GetIntDataCode( "Age", p_oTree->GetSpecies(), p_oTree->GetType() ), iDmg);
  }

  fX = 120;
  fY = 120;
  for (i = 0; i < 9; i++) {
    p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, 20 );
  }

  //Run our behavior - running the storm damage applier would mess up our
  //storm counts
  for (i = 0; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
    if (strcmp(p_oSimManager->GetBehaviorObject(i)->GetName(), "StormLight") == 0)
      p_oSimManager->GetBehaviorObject(i)->Action();
  }

  p_oLightGrid = p_oSimManager->GetGridObject("Storm Light");
  iLightCode = p_oLightGrid->GetFloatDataCode("Light");

  //Grid 0, 0
  fExpectedLight = 98.74;
  p_oLightGrid->GetValueOfCell(0, 0, iLightCode, & fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight)/fExpectedLight < 0.001);

  //Grid 0, 10
  fExpectedLight = 76.51777778;
  p_oLightGrid->GetValueOfCell(0, 10, iLightCode, & fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight)/fExpectedLight < 0.001);

  //Grid 3, 3
  fExpectedLight = 22.21833333;
  p_oLightGrid->GetValueOfCell(3, 3, iLightCode, & fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight)/fExpectedLight < 0.001);

  //Grid 10, 10
  fExpectedLight = 69.175;
  p_oLightGrid->GetValueOfCell(10, 10, iLightCode, & fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.001);

  //Grid 20, 20
  fExpectedLight = 69.175;
  p_oLightGrid->GetValueOfCell(20, 20, iLightCode, & fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight)/fExpectedLight < 0.001);

  //Grid 10, 20
  fExpectedLight = 0;
  p_oLightGrid->GetValueOfCell(10, 20, iLightCode, & fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.001);

  //Grid 20, 10
  fExpectedLight = 81.33507937;
  p_oLightGrid->GetValueOfCell(20, 10, iLightCode, & fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight)/fExpectedLight < 0.001);

  //Grid 15, 15
  fExpectedLight = 0;
  p_oLightGrid->GetValueOfCell(15, 15, iLightCode, & fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.001);

  //Kill all the trees, run another timestep, verify that all the cells
  //are properly re-initialized
  p_oAllTrees = p_oPop->Find("all");
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {
    p_oPop->KillTree(p_oTree, remove_tree);
    p_oTree = p_oAllTrees->NextTree();
  }

  p_oSimManager->RunSim(1);
  int iNumXCells = p_oLightGrid->GetNumberXCells(),
      iNumYCells = p_oLightGrid->GetNumberYCells(), iX, iY;

  fExpectedLight = 98.74;
  for (iX = 0; iX < iNumXCells; iX++) {
    for (iY = 0; iY < iNumYCells; iY++) {
      p_oLightGrid->GetValueOfCell(iX, iY, iLightCode, & fActualLight);
      CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight)/fExpectedLight < 0.001);
    }
  }
}

/////////////////////////////////////////////////////////////////////////////
//  NormalProcessingRun2()
/////////////////////////////////////////////////////////////////////////////
void clTestStormLight::NormalProcessingRun2(clSimManager *p_oSimManager)
{
  clTreePopulation *p_oPop;
  clGrid *p_oLightGrid;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;
  float fActualLight, fExpectedLight, fX, fY;
  int iLightCode, iDmg, i;

  //Feed our file to the sim manager
  p_oSimManager->ReadFile(WriteXMLFile2());
  p_oPop = (clTreePopulation*) p_oSimManager->GetPopulationObject("treepopulation");

  //Add the trees
  fX = 20;
  fY = 20;
  p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::sapling, 5 );

  fX = 21;
  fY = 21;
  iDmg = 0;
  p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, 20 );
  p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iDmg);

  fX = 22.5;
  fY = 22.5;
  p_oTree = p_oPop->CreateTree( fX, fY, 1, clTreePopulation::adult, 20 );

  fX = 22;
  fY = 22;
  iDmg = 1002;
  p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, 20 );
  p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iDmg);

  fX = 23;
  fY = 23;
  iDmg = 1002;
  p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, 20 );
  p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iDmg);

  fX = 24;
  fY = 24;
  iDmg = 2003;
  p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, 20 );
  p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iDmg);

  fX = 21;
  fY = 24;
  p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::sapling, 5 );

  fX = 22;
  fY = 24;
  iDmg = 2000;
  p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, 20 );
  p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iDmg);

  fX = 23;
  fY = 24;
  iDmg = 2001;
  p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, 20 );
  p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iDmg);

  fX = 1;
  fY = 80;
  iDmg = 0;
  p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, 20 );
  p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iDmg);

  fX = 2;
  fY = 81;
  p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::sapling, 5 );

  fX = 80;
  fY = 80;
  iDmg = 2000;
  for (i = 0; i < 200; i++) {
    p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, 20 );
    p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iDmg);
  }

  fX = 160;
  fY = 160;
  iDmg = 2002;
  p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, 20 );
  p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iDmg);

  fX = 152;
  fY = 164;
  iDmg = 2002;
  p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, 20 );
  p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iDmg);

  fX = 162;
  fY = 162;
  iDmg = 1002;
  p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, 20 );
  p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iDmg);

  fX = 163;
  fY = 163;
  iDmg = 2000;
  for (i = 0; i < 10; i++) {
    p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, 20 );
    p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iDmg);
  }

  fX = 164;
  fY = 180;
  iDmg = 2000;
  p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::adult, 20 );
  p_oTree->SetValue( p_oPop->GetIntDataCode( "stm_dmg", p_oTree->GetSpecies(), p_oTree->GetType() ), iDmg);

  fX = 164;
  fY = 164;
  p_oTree = p_oPop->CreateTree( fX, fY, 0, clTreePopulation::seedling, 0.2 );

  //Run our behavior - running the storm damage applier would mess up our
  //storm counts
  for (i = 0; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
    if (strcmp(p_oSimManager->GetBehaviorObject(i)->GetName(), "StormLight") == 0)
      p_oSimManager->GetBehaviorObject(i)->Action();
  }

  p_oLightGrid = p_oSimManager->GetGridObject("Storm Light");
  iLightCode = p_oLightGrid->GetFloatDataCode("Light");

  //Grid 0, 0
  fExpectedLight = 98.74;
  p_oLightGrid->GetValueOfCell(0, 0, iLightCode, & fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.001);

  //Grid 0, 16
  fExpectedLight = 87.62888889;
  p_oLightGrid->GetValueOfCell(0, 16, iLightCode, & fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.001);

  //Grid 4, 4
  fExpectedLight = 41.08650794;
  p_oLightGrid->GetValueOfCell(4, 4, iLightCode, & fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight)/fExpectedLight < 0.001);

  //Grid 16, 16
  fExpectedLight = 69.175;
  p_oLightGrid->GetValueOfCell(16, 16, iLightCode, & fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.001);

  //Grid 32, 32
  fExpectedLight = 63.75692308;
  p_oLightGrid->GetValueOfCell(32, 32, iLightCode, & fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight)/fExpectedLight < 0.001);

  //Kill all the trees, run another timestep, verify that all the cells
  //are properly re-initialized
  p_oAllTrees = p_oPop->Find("all");
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {
    p_oPop->KillTree(p_oTree, remove_tree);
    p_oTree = p_oAllTrees->NextTree();
  }

  p_oSimManager->RunSim(1);
  int iNumXCells = p_oLightGrid->GetNumberXCells(),
      iNumYCells = p_oLightGrid->GetNumberYCells(), iX, iY;

  fExpectedLight = 98.74;
  for (iX = 0; iX < iNumXCells; iX++) {
    for (iY = 0; iY < iNumYCells; iY++) {
      p_oLightGrid->GetValueOfCell(iX, iY, iLightCode, & fActualLight);
      CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight)/fExpectedLight < 0.001);
    }
  }
}

/////////////////////////////////////////////////////////////////////////////
//  WriteXMLFile1()
/////////////////////////////////////////////////////////////////////////////
const char* clTestStormLight::WriteXMLFile1()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>5</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>";

  oOut << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>200</plot_lenX>"
       << "<plot_lenY>200</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\"/>"
       << "<tr_species speciesName=\"Species_2\"/>"
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
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_2\">0.0299</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_2\">39.48</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_2\">0.0549</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">0.8008</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.389</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_2\">0.03418</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
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
       << "</allometry>";

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>Storm</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StormDamageApplier</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Snag\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StormLight</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>4</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Snag\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<StormLight3>"
       << "<li_stormLightRadius>15</li_stormLightRadius>"
       << "<li_stormLightSlope>70.435</li_stormLightSlope>"
       << "<li_stormLightIntercept>-1.26</li_stormLightIntercept>"
       << "<li_stormLightMaxDmgTime>3</li_stormLightMaxDmgTime>"
       << "<li_stormLightSnagMaxDmgTime>2</li_stormLightSnagMaxDmgTime>"
       << "<li_stormLightStoch>0</li_stormLightStoch>"
       << "<li_stormLightMinFullCanopy>9</li_stormLightMinFullCanopy>"
       << "</StormLight3>"
       << "<StochasticMortality4>"
       << "<mo_stochasticMortRate>"
       << "<mo_smrVal species=\"Species_1\">0.0</mo_smrVal>"
       << "</mo_stochasticMortRate>"
       << "</StochasticMortality4>";

  oOut << "<Storm1>"
       << "<st_s1ReturnInterval>100000</st_s1ReturnInterval>"
       << "<st_s2ReturnInterval>100000</st_s2ReturnInterval>"
       << "<st_s3ReturnInterval>100000</st_s3ReturnInterval>"
       << "<st_s4ReturnInterval>100000</st_s4ReturnInterval>"
       << "<st_s5ReturnInterval>100000</st_s5ReturnInterval>"
       << "<st_s6ReturnInterval>100000</st_s6ReturnInterval>"
       << "<st_s7ReturnInterval>100000</st_s7ReturnInterval>"
       << "<st_s8ReturnInterval>100000</st_s8ReturnInterval>"
       << "<st_s9ReturnInterval>100000</st_s9ReturnInterval>"
       << "<st_s10ReturnInterval>100000</st_s10ReturnInterval>"
       << "<st_stmSSTPeriod>1</st_stmSSTPeriod>"
       << "<st_stmSineD>0</st_stmSineD>"
       << "<st_stmSineF>1</st_stmSineF>"
       << "<st_stmSineG>1</st_stmSineG>"
       << "<st_stmTrendSlopeM>0</st_stmTrendSlopeM>"
       << "<st_stmTrendInterceptI>1</st_stmTrendInterceptI>"
       << "<st_susceptibility>1</st_susceptibility>"
       << "<st_stochasticity>0</st_stochasticity>"
       << "</Storm1>"
       << "<StormDamageApplier2>"
       << "<st_minDBH>"
       << "<st_mdVal species=\"Species_1\">5</st_mdVal>"
       << "</st_minDBH>"
       << "<st_stmDmgInterceptMed>"
       << "<st_sdimVal species=\"Species_1\">2.1789601</st_sdimVal>"
       << "</st_stmDmgInterceptMed>"
       << "<st_stmDmgInterceptFull>"
       << "<st_sdifVal species=\"Species_1\">3.6334169</st_sdifVal>"
       << "</st_stmDmgInterceptFull>"
       << "<st_stmIntensityCoeff>"
       << "<st_sicVal species=\"Species_1\">-0.3545352</st_sicVal>"
       << "</st_stmIntensityCoeff>"
       << "<st_stmDBHCoeff>"
       << "<st_sdcVal species=\"Species_1\">0.8280319</st_sdcVal>"
       << "</st_stmDBHCoeff>"
       << "<st_stmPropDieMedDmg>"
       << "<st_spdmdVal species=\"Species_1\">0</st_spdmdVal>"
       << "</st_stmPropDieMedDmg>"
       << "<st_stmPropDieFullDmg>"
       << "<st_spdfdVal species=\"Species_1\">0</st_spdfdVal>"
       << "</st_stmPropDieFullDmg>"
       << "<st_stmPropTipUpFullDmg>"
       << "<st_sptufdVal species=\"Species_1\">0</st_sptufdVal>"
       << "</st_stmPropTipUpFullDmg>"
       << "<st_numYearsStormSnags>10</st_numYearsStormSnags>"
       << "<st_numYearsToHeal>10</st_numYearsToHeal>"
       << "</StormDamageApplier2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;

}

/////////////////////////////////////////////////////////////////////////////
//  WriteXMLFile2()
/////////////////////////////////////////////////////////////////////////////
const char* clTestStormLight::WriteXMLFile2()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>5</timesteps>"
       << "<yearsPerTimestep>2</yearsPerTimestep>";

  oOut << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>200</plot_lenX>"
       << "<plot_lenY>200</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\"/>"
       << "<tr_species speciesName=\"Species_2\"/>"
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
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_2\">0.0299</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_2\">39.48</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_2\">0.0549</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">0.8008</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.389</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_2\">0.03418</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
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
       << "</allometry>";

  oOut << "<grid gridName=\"Storm Light\">"
       << "<ma_floatCodes>"
       << "<ma_floatCode label=\"Light\">0</ma_floatCode>"
       << "</ma_floatCodes>"
       << "<ma_lengthXCells>5</ma_lengthXCells>"
       << "<ma_lengthYCells>5</ma_lengthYCells>"
       << "</grid>";

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>Storm</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StormDamageApplier</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StormLight</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>4</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<StormLight3>"
       << "<li_stormLightRadius>15</li_stormLightRadius>"
       << "<li_stormLightSlope>70.435</li_stormLightSlope>"
       << "<li_stormLightIntercept>-1.26</li_stormLightIntercept>"
       << "<li_stormLightMaxDmgTime>3</li_stormLightMaxDmgTime>"
       << "<li_stormLightSnagMaxDmgTime>0</li_stormLightSnagMaxDmgTime>"
       << "<li_stormLightStoch>0</li_stormLightStoch>"
       << "<li_stormLightMinFullCanopy>9</li_stormLightMinFullCanopy>"
       << "</StormLight3>"
       << "<StochasticMortality4>"
       << "<mo_stochasticMortRate>"
       << "<mo_smrVal species=\"Species_1\">0.0</mo_smrVal>"
       << "</mo_stochasticMortRate>"
       << "</StochasticMortality4>";

  oOut << "<Storm1>"
       << "<st_s1ReturnInterval>100000</st_s1ReturnInterval>"
       << "<st_s2ReturnInterval>100000</st_s2ReturnInterval>"
       << "<st_s3ReturnInterval>100000</st_s3ReturnInterval>"
       << "<st_s4ReturnInterval>100000</st_s4ReturnInterval>"
       << "<st_s5ReturnInterval>100000</st_s5ReturnInterval>"
       << "<st_s6ReturnInterval>100000</st_s6ReturnInterval>"
       << "<st_s7ReturnInterval>100000</st_s7ReturnInterval>"
       << "<st_s8ReturnInterval>100000</st_s8ReturnInterval>"
       << "<st_s9ReturnInterval>100000</st_s9ReturnInterval>"
       << "<st_s10ReturnInterval>100000</st_s10ReturnInterval>"
       << "<st_susceptibility>1</st_susceptibility>"
       << "<st_stmSSTPeriod>1</st_stmSSTPeriod>"
       << "<st_stmSineD>0</st_stmSineD>"
       << "<st_stmSineF>1</st_stmSineF>"
       << "<st_stmSineG>1</st_stmSineG>"
       << "<st_stmTrendSlopeM>0</st_stmTrendSlopeM>"
       << "<st_stmTrendInterceptI>1</st_stmTrendInterceptI>"
       << "<st_stochasticity>0</st_stochasticity>"
       << "</Storm1>"
       << "<StormDamageApplier2>"
       << "<st_minDBH>"
       << "<st_mdVal species=\"Species_1\">5</st_mdVal>"
       << "</st_minDBH>"
       << "<st_stmDmgInterceptMed>"
       << "<st_sdimVal species=\"Species_1\">2.1789601</st_sdimVal>"
       << "</st_stmDmgInterceptMed>"
       << "<st_stmDmgInterceptFull>"
       << "<st_sdifVal species=\"Species_1\">3.6334169</st_sdifVal>"
       << "</st_stmDmgInterceptFull>"
       << "<st_stmIntensityCoeff>"
       << "<st_sicVal species=\"Species_1\">-0.3545352</st_sicVal>"
       << "</st_stmIntensityCoeff>"
       << "<st_stmDBHCoeff>"
       << "<st_sdcVal species=\"Species_1\">0.8280319</st_sdcVal>"
       << "</st_stmDBHCoeff>"
       << "<st_stmPropDieMedDmg>"
       << "<st_spdmdVal species=\"Species_1\">0</st_spdmdVal>"
       << "</st_stmPropDieMedDmg>"
       << "<st_stmPropDieFullDmg>"
       << "<st_spdfdVal species=\"Species_1\">0</st_spdfdVal>"
       << "</st_stmPropDieFullDmg>"
       << "<st_stmPropTipUpFullDmg>"
       << "<st_sptufdVal species=\"Species_1\">0</st_sptufdVal>"
       << "</st_stmPropTipUpFullDmg>"
       << "<st_numYearsStormSnags>10</st_numYearsStormSnags>"
       << "<st_numYearsToHeal>10</st_numYearsToHeal>"
       << "</StormDamageApplier2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
//  WriteXMLErrorFile1()
/////////////////////////////////////////////////////////////////////////////
const char* clTestStormLight::WriteXMLErrorFile1()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>5</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>";

  oOut << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>200</plot_lenX>"
       << "<plot_lenY>200</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\"/>"
       << "<tr_species speciesName=\"Species_2\"/>"
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
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_2\">0.0299</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_2\">39.48</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_2\">0.0549</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">0.8008</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.389</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_2\">0.03418</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
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
       << "</allometry>";

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>Storm</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StormDamageApplier</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Snag\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StormLight</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>4</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Snag\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<StormLight3>"
       << "<li_stormLightRadius>15</li_stormLightRadius>"
       << "<li_stormLightSlope>-4</li_stormLightSlope>"
       << "<li_stormLightIntercept>95</li_stormLightIntercept>"
       << "<li_stormLightMaxDmgTime>3</li_stormLightMaxDmgTime>"
       << "<li_stormLightSnagMaxDmgTime>2</li_stormLightSnagMaxDmgTime>"
       << "<li_stormLightStoch>0</li_stormLightStoch>"
       << "<li_stormLightMinFullCanopy>-9</li_stormLightMinFullCanopy>"
       << "</StormLight3>"
       << "<StochasticMortality4>"
       << "<mo_stochasticMortRate>"
       << "<mo_smrVal species=\"Species_1\">0.0</mo_smrVal>"
       << "</mo_stochasticMortRate>"
       << "</StochasticMortality4>";

  oOut << "<Storm1>"
       << "<st_s1ReturnInterval>100000</st_s1ReturnInterval>"
       << "<st_s2ReturnInterval>100000</st_s2ReturnInterval>"
       << "<st_s3ReturnInterval>100000</st_s3ReturnInterval>"
       << "<st_s4ReturnInterval>100000</st_s4ReturnInterval>"
       << "<st_s5ReturnInterval>100000</st_s5ReturnInterval>"
       << "<st_s6ReturnInterval>100000</st_s6ReturnInterval>"
       << "<st_s7ReturnInterval>100000</st_s7ReturnInterval>"
       << "<st_s8ReturnInterval>100000</st_s8ReturnInterval>"
       << "<st_s9ReturnInterval>100000</st_s9ReturnInterval>"
       << "<st_s10ReturnInterval>100000</st_s10ReturnInterval>"
       << "<st_susceptibility>1</st_susceptibility>"
       << "<st_stmSSTPeriod>1</st_stmSSTPeriod>"
       << "<st_stmSineD>0</st_stmSineD>"
       << "<st_stmSineF>1</st_stmSineF>"
       << "<st_stmSineG>1</st_stmSineG>"
       << "<st_stmTrendSlopeM>0</st_stmTrendSlopeM>"
       << "<st_stmTrendInterceptI>1</st_stmTrendInterceptI>"
       << "<st_stochasticity>0</st_stochasticity>"
       << "</Storm1>"
       << "<StormDamageApplier2>"
       << "<st_minDBH>"
       << "<st_mdVal species=\"Species_1\">5</st_mdVal>"
       << "</st_minDBH>"
       << "<st_stmDmgInterceptMed>"
       << "<st_sdimVal species=\"Species_1\">2.1789601</st_sdimVal>"
       << "</st_stmDmgInterceptMed>"
       << "<st_stmDmgInterceptFull>"
       << "<st_sdifVal species=\"Species_1\">3.6334169</st_sdifVal>"
       << "</st_stmDmgInterceptFull>"
       << "<st_stmIntensityCoeff>"
       << "<st_sicVal species=\"Species_1\">-0.3545352</st_sicVal>"
       << "</st_stmIntensityCoeff>"
       << "<st_stmDBHCoeff>"
       << "<st_sdcVal species=\"Species_1\">0.8280319</st_sdcVal>"
       << "</st_stmDBHCoeff>"
       << "<st_stmPropDieMedDmg>"
       << "<st_spdmdVal species=\"Species_1\">0</st_spdmdVal>"
       << "</st_stmPropDieMedDmg>"
       << "<st_stmPropDieFullDmg>"
       << "<st_spdfdVal species=\"Species_1\">0</st_spdfdVal>"
       << "</st_stmPropDieFullDmg>"
       << "<st_stmPropTipUpFullDmg>"
       << "<st_sptufdVal species=\"Species_1\">0</st_sptufdVal>"
       << "</st_stmPropTipUpFullDmg>"
       << "<st_numYearsStormSnags>10</st_numYearsStormSnags>"
       << "<st_numYearsToHeal>10</st_numYearsToHeal>"
       << "</StormDamageApplier2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;

}
