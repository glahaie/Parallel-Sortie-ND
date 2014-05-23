//---------------------------------------------------------------------------
// TestBasalAreaLight.cpp
//---------------------------------------------------------------------------
#include "TestBasalAreaLight.h"
#include "Grid.h"
#include "SimManager.h"
#include "BehaviorBase.h"
#include "TreePopulation.h"
#include "BasalAreaLight.h"
#include <math.h>
#include <fstream>

/////////////////////////////////////////////////////////////////////////////
//  TestBasalAreaLight()
/////////////////////////////////////////////////////////////////////////////
void clTestBasalAreaLight::TestBasalAreaLight()
{

  clSimManager * p_oSimManager = new clSimManager(3, 3, "");

  TestErrorProcessing(p_oSimManager);
  NormalProcessingRun1(p_oSimManager);
  NormalProcessingRun2(p_oSimManager);
  NormalProcessingRun3(p_oSimManager);
  NormalProcessingRun4(p_oSimManager);
  NormalProcessingRun5(p_oSimManager);

  //Clean up
  delete p_oSimManager;
}

////////////////////////////////////////////////////////////////////////////
//  TestErrorProcessing()
////////////////////////////////////////////////////////////////////////////
void clTestBasalAreaLight::TestErrorProcessing( clSimManager * p_oSimManager )
{

  try
  {
    p_oSimManager->ReadFile( WriteXMLErrorFile1() );
    CppUnit::Asserter::fail( "TestBasalAreaLight error processing didn't catch error for WriteXMLErrorFile1." );
  }
  catch ( modelErr& err )
  {
    if ( strstr( err.cFunction, "clBasalAreaLight::DoShellSetup" ) == NULL )
    {
      CppUnit::Asserter::fail( "TestBasalAreaLight error processing caught wrong error for WriteXMLErrorFile1." );
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile( WriteXMLErrorFile2() );
    CppUnit::Asserter::fail( "TestBasalAreaLight error processing didn't catch error for WriteXMLErrorFile2." );
  }
  catch ( modelErr& err )
  {
    if ( strstr( err.cFunction, "clBasalAreaLight::DoShellSetup" ) == NULL )
    {
      CppUnit::Asserter::fail( "TestBasalAreaLight error processing caught wrong error for WriteXMLErrorFile2." );
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile( WriteXMLErrorFile3() );
    CppUnit::Asserter::fail( "TestBasalAreaLight error processing didn't catch error for WriteXMLErrorFile3." );
  }
  catch ( modelErr& err )
  {
    if ( strstr( err.cFunction, "clBasalAreaLight::DoShellSetup" ) == NULL )
    {
      CppUnit::Asserter::fail( "TestBasalAreaLight error processing caught wrong error for WriteXMLErrorFile3." );
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile( WriteXMLErrorFile4() );
    CppUnit::Asserter::fail( "TestBasalAreaLight error processing didn't catch error for WriteXMLErrorFile4." );
  }
  catch ( modelErr& err )
  {
    if ( strstr( err.cFunction, "clBasalAreaLight::DoShellSetup" ) == NULL )
    {
      CppUnit::Asserter::fail( "TestBasalAreaLight error processing caught wrong error for WriteXMLErrorFile4." );
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile( WriteXMLErrorFile5() );
    CppUnit::Asserter::fail( "TestBasalAreaLight error processing didn't catch error for WriteXMLErrorFile5." );
  }
  catch ( modelErr& err )
  {
    if ( strstr( err.cFunction, "clBasalAreaLight::DoShellSetup" ) == NULL )
    {
      CppUnit::Asserter::fail( "TestBasalAreaLight error processing caught wrong error for WriteXMLErrorFile5." );
    }
    ;
  }
}

/////////////////////////////////////////////////////////////////////////////
// NormalProcessingRun1()
/////////////////////////////////////////////////////////////////////////////
void clTestBasalAreaLight::NormalProcessingRun1(clSimManager *p_oSimManager)
{
  clTreePopulation *p_oPop;
  clBehaviorBase *p_oTemp;
  clBasalAreaLight *p_oLightBeh;
  clGrid *p_oLightGrid;
  clTree *p_oTree1, *p_oTree2, *p_oTree3, *p_oTree4, *p_oTree5, *p_oTree6,
         *p_oTree7, *p_oTree8, *p_oTree9, *p_oTree10, *p_oTree11, *p_oTree12,
         *p_oTree13, *p_oTree14, *p_oTree15, *p_oTree16, *p_oTree17,
         *p_oTree18, *p_oTree19, *p_oTree20, *p_oTree21, *p_oTree22,
         *p_oTree23, *p_oTree24, *p_oTree25, *p_oTree26, *p_oTree27,
         *p_oTree28, *p_oTree29, *p_oTree30, *p_oTree31, *p_oTree32;
  float fActualLight, //Light level calculated by SORTIE
        fExpectedLight, //Light level we're expecting
        fExpConBA, //Conifer basal area we're expecting
        fExpAngBA, //Angiosperm basal area we're expecting
        fActualConBA, //Conifer basal area calculated by SORTIE
        fActualAngBA, //Angiosperm basal area calculated by SORTIE
        fDiam, fX, fY, //For creating trees
        //For stashing light levels between timesteps
        fLight1, fLight2, fLight3, fLight4, fLight5, fLight6, fLight7;
  int iLightCode, iConBACode, iAngBACode, iX, iY, iNumXCells, iSpecies,
      iNumYCells;


  //Feed our file to the sim manager
  p_oSimManager->ReadFile(WriteXMLFile1());
  p_oPop = (clTreePopulation*) p_oSimManager->GetPopulationObject("treepopulation");

  //Add trees to three grid cells
  //Grid Cell 0,1: 1 conifer
  fX = 4; fY = 12;
  iSpecies = 2; fDiam = 50;
  p_oTree1 = p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDiam );

  //Grid cell 0,2: 1 angiosperm.
  fX = 4; fY = 20;
  iSpecies = 1; fDiam = 45;
  p_oTree2 = p_oPop->CreateTree(  fX, fY, iSpecies, clTreePopulation::adult, fDiam );

  //Grid cell 0,3: 3 conifers, plus more too small
  fX = 4; fY = 28;
  iSpecies = 0; fDiam = 45;
  p_oTree3 = p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDiam );
  iSpecies = 2; fDiam = 24;
  p_oTree4 = p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDiam );
  iSpecies = 2; fDiam = 70;
  p_oTree5 = p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDiam );
  iSpecies = 0; fDiam = 8;
  p_oTree6 = p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::sapling, fDiam );
  iSpecies = 2; fDiam = 9;
  p_oTree7 = p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::sapling, fDiam );

  //Grid cell 0,4: 5 angiosperms, plus more too small.
  fX = 4; fY = 36;
  iSpecies = 3; fDiam = 45;
  p_oTree8 = p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDiam );
  iSpecies = 1; fDiam = 24;
  p_oTree9 = p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDiam );
  iSpecies = 1; fDiam = 70;
  p_oTree10 = p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDiam );
  iSpecies = 3; fDiam = 18;
  p_oTree11 = p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDiam );
  iSpecies = 1; fDiam = 31;
  p_oTree12 = p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDiam );
  iSpecies = 3; fDiam = 6;
  p_oTree13 = p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::sapling, fDiam );
  iSpecies = 1; fDiam = 4;
  p_oTree14 = p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::sapling, fDiam );

  //Grid cell 0,5: 6 trees, mixed conifer and angiosperm, plus more too small,
  //and snags
  fX = 4; fY = 44;
  iSpecies = 3; fDiam = 45;
  p_oTree15 = p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDiam );
  iSpecies = 1; fDiam = 24;
  p_oTree16 = p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDiam );
  iSpecies = 1; fDiam = 70;
  p_oTree17 = p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDiam );
  iSpecies = 3; fDiam = 18;
  p_oTree18 = p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDiam );
  iSpecies = 1; fDiam = 31;
  p_oTree19 = p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDiam );
  iSpecies = 3; fDiam = 6;
  p_oTree20 = p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::sapling, fDiam );
  iSpecies = 1; fDiam = 4;
  p_oTree21 = p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::sapling, fDiam );
  iSpecies = 0; fDiam = 45;
  p_oTree22 = p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDiam );
  iSpecies = 2; fDiam = 24;
  p_oTree23 = p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDiam );
  iSpecies = 1; fDiam = 70;
  p_oTree24 = p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDiam );
  iSpecies = 0; fDiam = 8;
  p_oTree25 = p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::sapling, fDiam );
  iSpecies = 2; fDiam = 9;
  p_oTree26 = p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::sapling, fDiam );
  iSpecies = 0; fDiam = 100;
  p_oTree27 = p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::snag, fDiam );

  //Grid cell 0,6: Several trees, all too small.
  fX = 4; fY = 52;
  iSpecies = 3; fDiam = 3;
  p_oTree28 = p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::sapling, fDiam );
  iSpecies = 0; fDiam = 6;
  p_oTree29 = p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::sapling, fDiam );
  iSpecies = 2; fDiam = 3;
  p_oTree30 = p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::sapling, fDiam );
  iSpecies = 1; fDiam = 9;
  p_oTree31 = p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::sapling, fDiam );

  //Check the mean GLI calculations directly for several values
  p_oTemp = p_oSimManager->GetBehaviorObject("basalarealightshell");
  p_oLightBeh = dynamic_cast<clBasalAreaLight*>(p_oTemp);

  fExpectedLight = 12.4;
  fActualConBA = 0;
  fActualAngBA = 0;
  fActualLight = p_oLightBeh->GetMeanGLI(fActualConBA, fActualAngBA);
  CPPUNIT_ASSERT(fabs(fExpectedLight - fActualLight) < 0.0001);

  fExpectedLight = 12.22827861;
  fActualConBA = 0.196349541;
  fActualAngBA = 0;
  fActualLight = p_oLightBeh->GetMeanGLI(fActualConBA, fActualAngBA);
  CPPUNIT_ASSERT(fabs(fExpectedLight - fActualLight) < 0.0001);

  fExpectedLight = 12.3998466;
  fActualConBA = 0;
  fActualAngBA = 0.159043128;
  fActualLight = p_oLightBeh->GetMeanGLI(fActualConBA, fActualAngBA);
  CPPUNIT_ASSERT(fabs(fExpectedLight - fActualLight) < 0.0001);

  fExpectedLight = 11.25757809;
  fActualConBA = 0.589127162;
  fActualAngBA = 0;
  fActualLight = p_oLightBeh->GetMeanGLI(fActualConBA, fActualAngBA);
  CPPUNIT_ASSERT(fabs(fExpectedLight - fActualLight) < 0.0001);

  fExpectedLight = 12.35778669;
  fActualConBA = 0;
  fActualAngBA = 0.690050826;
  fActualLight = p_oLightBeh->GetMeanGLI(fActualConBA, fActualAngBA);
  CPPUNIT_ASSERT(fabs(fExpectedLight - fActualLight) < 0.0001);

  fExpectedLight = 11.99536365;
  fActualConBA = 0.204282062;
  fActualAngBA = 1.074895926;
  fActualLight = p_oLightBeh->GetMeanGLI(fActualConBA, fActualAngBA);
  CPPUNIT_ASSERT(fabs(fExpectedLight - fActualLight) < 0.0001);



  //Run one timestep
  p_oSimManager->RunSim(1);

  p_oLightGrid = p_oSimManager->GetGridObject("Basal Area Light");
  iLightCode = p_oLightGrid->GetFloatDataCode("Light");
  CPPUNIT_ASSERT(-1 < iLightCode);
  iConBACode = p_oLightGrid->GetFloatDataCode("Con BA");
  CPPUNIT_ASSERT(-1 < iConBACode);
  iAngBACode = p_oLightGrid->GetFloatDataCode("Ang BA");
  CPPUNIT_ASSERT(-1 < iAngBACode);

  //Check to make sure the basal area totals are correct
  //Grid 0, 0
  fExpConBA = 0;
  fExpAngBA = 0;
  p_oLightGrid->GetValueOfCell(0, 0, iConBACode, &fActualConBA);
  p_oLightGrid->GetValueOfCell(0, 0, iAngBACode, &fActualAngBA);
  CPPUNIT_ASSERT(fabs(fExpConBA - fActualConBA) < 0.001);
  CPPUNIT_ASSERT(fabs(fExpAngBA - fActualAngBA) < 0.001);

  //Grid 0, 1
  fExpConBA = 0.196349541;
  fExpAngBA = 0;
  p_oLightGrid->GetValueOfCell(0, 1, iConBACode, &fActualConBA);
  p_oLightGrid->GetValueOfCell(0, 1, iAngBACode, &fActualAngBA);
  CPPUNIT_ASSERT(fabs(fExpConBA - fActualConBA) < 0.001);
  CPPUNIT_ASSERT(fabs(fExpAngBA - fActualAngBA) < 0.001);

  //Grid 0, 2
  fExpConBA = 0;
  fExpAngBA = 0.159043128;
  p_oLightGrid->GetValueOfCell(0, 2, iConBACode, &fActualConBA);
  p_oLightGrid->GetValueOfCell(0, 2, iAngBACode, &fActualAngBA);
  CPPUNIT_ASSERT(fabs(fExpConBA - fActualConBA) < 0.001);
  CPPUNIT_ASSERT(fabs(fExpAngBA - fActualAngBA) < 0.001);

  //Grid 0, 3
  fExpConBA = 0.589127162;
  fExpAngBA = 0;
  p_oLightGrid->GetValueOfCell(0, 3, iConBACode, &fActualConBA);
  p_oLightGrid->GetValueOfCell(0, 3, iAngBACode, &fActualAngBA);
  CPPUNIT_ASSERT(fabs(fExpConBA - fActualConBA) < 0.001);
  CPPUNIT_ASSERT(fabs(fExpAngBA - fActualAngBA) < 0.001);

  //Grid 0, 4
  fExpConBA = 0;
  fExpAngBA = 0.690050826;
  p_oLightGrid->GetValueOfCell(0, 4, iConBACode, &fActualConBA);
  p_oLightGrid->GetValueOfCell(0, 4, iAngBACode, &fActualAngBA);
  CPPUNIT_ASSERT(fabs(fExpConBA - fActualConBA) < 0.001);
  CPPUNIT_ASSERT(fabs(fExpAngBA - fActualAngBA) < 0.001);

  //Grid 0, 5
  fExpConBA = 0.204282062;
  fExpAngBA = 1.074895926;
  p_oLightGrid->GetValueOfCell(0, 5, iConBACode, &fActualConBA);
  p_oLightGrid->GetValueOfCell(0, 5, iAngBACode, &fActualAngBA);
  CPPUNIT_ASSERT(fabs(fExpConBA - fActualConBA) < 0.001);
  CPPUNIT_ASSERT(fabs(fExpAngBA - fActualAngBA) < 0.001);

  //Grid 0, 6
  fExpConBA = 0;
  fExpAngBA = 0;
  p_oLightGrid->GetValueOfCell(0, 6, iConBACode, &fActualConBA);
  p_oLightGrid->GetValueOfCell(0, 6, iAngBACode, &fActualAngBA);
  CPPUNIT_ASSERT(fabs(fExpConBA - fActualConBA) < 0.001);
  CPPUNIT_ASSERT(fabs(fExpAngBA - fActualAngBA) < 0.001);

  //Make sure that all cells got a light level
  iNumXCells = p_oLightGrid->GetNumberXCells();
  iNumYCells = p_oLightGrid->GetNumberYCells();
  for (iX = 0; iX < iNumXCells; iX++) {
    for (iY = 0; iY < iNumYCells; iY++) {
      p_oLightGrid->GetValueOfCell(iX, iY, iLightCode, &fActualLight);
      CPPUNIT_ASSERT(fActualLight > 0);
    }
  }

  //Save the light values for the seven grid cells to check for density changes
  p_oLightGrid->GetValueOfCell(0, 0, iLightCode, &fLight1);
  p_oLightGrid->GetValueOfCell(0, 1, iLightCode, &fLight2);
  p_oLightGrid->GetValueOfCell(0, 2, iLightCode, &fLight3);
  p_oLightGrid->GetValueOfCell(0, 3, iLightCode, &fLight4);
  p_oLightGrid->GetValueOfCell(0, 4, iLightCode, &fLight5);
  p_oLightGrid->GetValueOfCell(0, 5, iLightCode, &fLight6);
  p_oLightGrid->GetValueOfCell(0, 6, iLightCode, &fLight7);

  //Make sure that the species two trees got light values matching their
  //grids, and nobody else
  //Grid 0,1 trees
  CPPUNIT_ASSERT(p_oPop->GetFloatDataCode("Light", p_oTree1->GetSpecies(), p_oTree1->GetType()) == -1);

  //Grid 0,2 trees
  p_oTree2->GetValue(p_oPop->GetFloatDataCode("Light", p_oTree2->GetSpecies(), p_oTree2->GetType()), &fActualLight);
  CPPUNIT_ASSERT(fActualLight == fLight3);

  //Grid 0,3 trees
  CPPUNIT_ASSERT(p_oPop->GetFloatDataCode("Light", p_oTree3->GetSpecies(), p_oTree3->GetType()) == -1);
  CPPUNIT_ASSERT(p_oPop->GetFloatDataCode("Light", p_oTree4->GetSpecies(), p_oTree4->GetType()) == -1);
  CPPUNIT_ASSERT(p_oPop->GetFloatDataCode("Light", p_oTree5->GetSpecies(), p_oTree5->GetType()) == -1);
  CPPUNIT_ASSERT(p_oPop->GetFloatDataCode("Light", p_oTree6->GetSpecies(), p_oTree6->GetType()) == -1);
  CPPUNIT_ASSERT(p_oPop->GetFloatDataCode("Light", p_oTree7->GetSpecies(), p_oTree7->GetType()) == -1);

  //Grid 0,4 trees
  CPPUNIT_ASSERT(p_oPop->GetFloatDataCode("Light", p_oTree8->GetSpecies(), p_oTree8->GetType()) == -1);
  p_oTree9->GetValue(p_oPop->GetFloatDataCode("Light", p_oTree9->GetSpecies(), p_oTree9->GetType()), &fActualLight);
  CPPUNIT_ASSERT(fActualLight == fLight5);
  p_oTree10->GetValue(p_oPop->GetFloatDataCode("Light", p_oTree10->GetSpecies(), p_oTree10->GetType()), &fActualLight);
  CPPUNIT_ASSERT(fActualLight == fLight5);
  CPPUNIT_ASSERT(p_oPop->GetFloatDataCode("Light", p_oTree11->GetSpecies(), p_oTree11->GetType()) == -1);
  p_oTree12->GetValue(p_oPop->GetFloatDataCode("Light", p_oTree12->GetSpecies(), p_oTree12->GetType()), &fActualLight);
  CPPUNIT_ASSERT(fActualLight == fLight5);
  CPPUNIT_ASSERT(p_oPop->GetFloatDataCode("Light", p_oTree13->GetSpecies(), p_oTree13->GetType()) == -1);
  p_oTree14->GetValue(p_oPop->GetFloatDataCode("Light", p_oTree14->GetSpecies(), p_oTree14->GetType()), &fActualLight);
  CPPUNIT_ASSERT(fActualLight == fLight5);

  //Grid 0,5 trees
  CPPUNIT_ASSERT(p_oPop->GetFloatDataCode("Light", p_oTree15->GetSpecies(), p_oTree15->GetType()) == -1);
  p_oTree16->GetValue(p_oPop->GetFloatDataCode("Light", p_oTree16->GetSpecies(), p_oTree16->GetType()), &fActualLight);
  CPPUNIT_ASSERT(fActualLight == fLight6);
  p_oTree17->GetValue(p_oPop->GetFloatDataCode("Light", p_oTree17->GetSpecies(), p_oTree17->GetType()), &fActualLight);
  CPPUNIT_ASSERT(fActualLight == fLight6);
  CPPUNIT_ASSERT(p_oPop->GetFloatDataCode("Light", p_oTree18->GetSpecies(), p_oTree18->GetType()) == -1);
  p_oTree19->GetValue(p_oPop->GetFloatDataCode("Light", p_oTree19->GetSpecies(), p_oTree19->GetType()), &fActualLight);
  CPPUNIT_ASSERT(fActualLight == fLight6);
  CPPUNIT_ASSERT(p_oPop->GetFloatDataCode("Light", p_oTree20->GetSpecies(), p_oTree20->GetType()) == -1);
  p_oTree21->GetValue(p_oPop->GetFloatDataCode("Light", p_oTree21->GetSpecies(), p_oTree21->GetType()), &fActualLight);
  CPPUNIT_ASSERT(fActualLight == fLight6);
  CPPUNIT_ASSERT(p_oPop->GetFloatDataCode("Light", p_oTree22->GetSpecies(), p_oTree22->GetType()) == -1);
  CPPUNIT_ASSERT(p_oPop->GetFloatDataCode("Light", p_oTree23->GetSpecies(), p_oTree23->GetType()) == -1);
  p_oTree24->GetValue(p_oPop->GetFloatDataCode("Light", p_oTree24->GetSpecies(), p_oTree24->GetType()), &fActualLight);
  CPPUNIT_ASSERT(p_oPop->GetFloatDataCode("Light", p_oTree25->GetSpecies(), p_oTree25->GetType()) == -1);
  CPPUNIT_ASSERT(fActualLight == fLight6);
  CPPUNIT_ASSERT(p_oPop->GetFloatDataCode("Light", p_oTree26->GetSpecies(), p_oTree26->GetType()) == -1);
  //Snag - has light but doesn't match
  p_oTree27->GetValue(p_oPop->GetFloatDataCode("Light", p_oTree27->GetSpecies(), p_oTree27->GetType()), &fActualLight);
  CPPUNIT_ASSERT(fActualLight != fLight6);

  //Grid 0,6 trees
  CPPUNIT_ASSERT(p_oPop->GetFloatDataCode("Light", p_oTree28->GetSpecies(), p_oTree28->GetType()) == -1);
  CPPUNIT_ASSERT(p_oPop->GetFloatDataCode("Light", p_oTree29->GetSpecies(), p_oTree29->GetType()) == -1);
  CPPUNIT_ASSERT(p_oPop->GetFloatDataCode("Light", p_oTree30->GetSpecies(), p_oTree30->GetType()) == -1);
  p_oTree31->GetValue(p_oPop->GetFloatDataCode("Light", p_oTree31->GetSpecies(), p_oTree31->GetType()), &fActualLight);
  CPPUNIT_ASSERT(fActualLight == fLight7);


  //Change the number of trees to trigger basal area changes

  //Grid cell 0, 0 - Add one tree of DBH 25 (total BA 0.049)
  p_oTree32 = p_oPop->CreateTree( 4, 4, 1, clTreePopulation::adult, 25 );

  //Grid cell 0, 1 - Do nothing

  //Grid cell 0, 2 - Add two trees of DBH 25, one each conifer and
  //angiosperm (total BA 0.098)
  fX = 4; fY = 20; fDiam = 25;
  iSpecies = 1;
  p_oPop->CreateTree(  fX, fY, iSpecies, clTreePopulation::adult, fDiam );
  iSpecies = 2;
  p_oPop->CreateTree(  fX, fY, iSpecies, clTreePopulation::adult, fDiam );

  //Grid cell 0, 3 - Subtract the tree with DBH 45 (total BA 0.15)
  p_oPop->KillTree(p_oTree3, natural);

  //Grid cell 0, 4 - Add three trees too small
  fX = 4; fY = 36;
  iSpecies = 3; fDiam = 6;
  p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::sapling, fDiam );
  p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::sapling, fDiam );
  p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::sapling, fDiam );

  //Grid cell 0, 5 - Subtract 2 trees too small
  p_oPop->KillTree(p_oTree25, natural);
  p_oPop->KillTree(p_oTree26, natural);

  //Grid cell 0, 6 - Do nothing


  //Run another timestep
  p_oSimManager->RunSim(1);

  //Check to make sure that the basal areas are correct
  //Grid 0, 0
  fExpConBA = 0;
  fExpAngBA = 0;
  p_oLightGrid->GetValueOfCell(0, 0, iConBACode, &fActualConBA);
  p_oLightGrid->GetValueOfCell(0, 0, iAngBACode, &fActualAngBA);
  CPPUNIT_ASSERT(fabs(fExpConBA - fActualConBA) < 0.001);
  CPPUNIT_ASSERT(fabs(fExpAngBA - fActualAngBA) < 0.001);

  //Grid 0, 1
  fExpConBA = 0.196349541;
  fExpAngBA = 0;
  p_oLightGrid->GetValueOfCell(0, 1, iConBACode, &fActualConBA);
  p_oLightGrid->GetValueOfCell(0, 1, iAngBACode, &fActualAngBA);
  CPPUNIT_ASSERT(fabs(fExpConBA - fActualConBA) < 0.001);
  CPPUNIT_ASSERT(fabs(fExpAngBA - fActualAngBA) < 0.001);

  //Grid 0, 2
  fExpConBA = 0.049087385;
  fExpAngBA = 0.208130513;
  p_oLightGrid->GetValueOfCell(0, 2, iConBACode, &fActualConBA);
  p_oLightGrid->GetValueOfCell(0, 2, iAngBACode, &fActualAngBA);
  CPPUNIT_ASSERT(fabs(fExpConBA - fActualConBA) < 0.001);
  CPPUNIT_ASSERT(fabs(fExpAngBA - fActualAngBA) < 0.001);

  //Grid 0, 3
  fExpConBA = 0.43008403;
  fExpAngBA = 0;
  p_oLightGrid->GetValueOfCell(0, 3, iConBACode, &fActualConBA);
  p_oLightGrid->GetValueOfCell(0, 3, iAngBACode, &fActualAngBA);
  CPPUNIT_ASSERT(fabs(fExpConBA - fActualConBA) < 0.001);
  CPPUNIT_ASSERT(fabs(fExpAngBA - fActualAngBA) < 0.001);

  //Grid 0, 4
  fExpConBA = 0;
  fExpAngBA = 0.690050826;
  p_oLightGrid->GetValueOfCell(0, 4, iConBACode, &fActualConBA);
  p_oLightGrid->GetValueOfCell(0, 4, iAngBACode, &fActualAngBA);
  CPPUNIT_ASSERT(fabs(fExpConBA - fActualConBA) < 0.001);
  CPPUNIT_ASSERT(fabs(fExpAngBA - fActualAngBA) < 0.001);

  //Grid 0, 5
  fExpConBA = 0.204282062;
  fExpAngBA = 1.074895926;
  p_oLightGrid->GetValueOfCell(0, 5, iConBACode, &fActualConBA);
  p_oLightGrid->GetValueOfCell(0, 5, iAngBACode, &fActualAngBA);
  CPPUNIT_ASSERT(fabs(fExpConBA - fActualConBA) < 0.001);
  CPPUNIT_ASSERT(fabs(fExpAngBA - fActualAngBA) < 0.001);

  //Grid 0, 6
  fExpConBA = 0;
  fExpAngBA = 0;
  p_oLightGrid->GetValueOfCell(0, 6, iConBACode, &fActualConBA);
  p_oLightGrid->GetValueOfCell(0, 6, iAngBACode, &fActualAngBA);
  CPPUNIT_ASSERT(fabs(fExpConBA - fActualConBA) < 0.001);
  CPPUNIT_ASSERT(fabs(fExpAngBA - fActualAngBA) < 0.001);

  //Make sure that the light levels for the third and fourth cells
  //change and the rest stay the same
  p_oLightGrid->GetValueOfCell(0, 0, iLightCode, &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fLight1) < 0.00001);
  p_oLightGrid->GetValueOfCell(0, 1, iLightCode, &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fLight2) < 0.00001);
  p_oLightGrid->GetValueOfCell(0, 2, iLightCode, &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fLight3) > 0.1);
  p_oLightGrid->GetValueOfCell(0, 3, iLightCode, &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fLight4) > 0.1);
  p_oLightGrid->GetValueOfCell(0, 4, iLightCode, &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fLight5) < 0.00001);
  p_oLightGrid->GetValueOfCell(0, 5, iLightCode, &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fLight6) < 0.00001);
  p_oLightGrid->GetValueOfCell(0, 6, iLightCode, &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fLight7) < 0.00001);

  //Check tree values
  p_oLightGrid->GetValueOfCell(0, 0, iLightCode, &fLight1);
  p_oLightGrid->GetValueOfCell(0, 1, iLightCode, &fLight2);
  p_oLightGrid->GetValueOfCell(0, 2, iLightCode, &fLight3);
  p_oLightGrid->GetValueOfCell(0, 3, iLightCode, &fLight4);
  p_oLightGrid->GetValueOfCell(0, 4, iLightCode, &fLight5);
  p_oLightGrid->GetValueOfCell(0, 5, iLightCode, &fLight6);
  p_oLightGrid->GetValueOfCell(0, 6, iLightCode, &fLight7);

  //Make sure that the species two trees got light values matching their
  //grids, and nobody else
  //Grid 0,0 trees
  p_oTree32->GetValue(p_oPop->GetFloatDataCode("Light", p_oTree32->GetSpecies(), p_oTree32->GetType()), &fActualLight);
  CPPUNIT_ASSERT(fActualLight == fLight1);

  //Grid 0,1 trees
  CPPUNIT_ASSERT(p_oPop->GetFloatDataCode("Light", p_oTree1->GetSpecies(), p_oTree1->GetType()) == -1);

  //Grid 0,2 trees
  p_oTree2->GetValue(p_oPop->GetFloatDataCode("Light", p_oTree2->GetSpecies(), p_oTree2->GetType()), &fActualLight);
  CPPUNIT_ASSERT(fActualLight == fLight3);

  //Grid 0,3 trees
  CPPUNIT_ASSERT(p_oPop->GetFloatDataCode("Light", p_oTree4->GetSpecies(), p_oTree4->GetType()) == -1);
  CPPUNIT_ASSERT(p_oPop->GetFloatDataCode("Light", p_oTree5->GetSpecies(), p_oTree5->GetType()) == -1);
  CPPUNIT_ASSERT(p_oPop->GetFloatDataCode("Light", p_oTree6->GetSpecies(), p_oTree6->GetType()) == -1);
  CPPUNIT_ASSERT(p_oPop->GetFloatDataCode("Light", p_oTree7->GetSpecies(), p_oTree7->GetType()) == -1);

  //Grid 0,4 trees
  CPPUNIT_ASSERT(p_oPop->GetFloatDataCode("Light", p_oTree8->GetSpecies(), p_oTree8->GetType()) == -1);
  p_oTree9->GetValue(p_oPop->GetFloatDataCode("Light", p_oTree9->GetSpecies(), p_oTree9->GetType()), &fActualLight);
  CPPUNIT_ASSERT(fActualLight == fLight5);
  p_oTree10->GetValue(p_oPop->GetFloatDataCode("Light", p_oTree10->GetSpecies(), p_oTree10->GetType()), &fActualLight);
  CPPUNIT_ASSERT(fActualLight == fLight5);
  CPPUNIT_ASSERT(p_oPop->GetFloatDataCode("Light", p_oTree11->GetSpecies(), p_oTree11->GetType()) == -1);
  p_oTree12->GetValue(p_oPop->GetFloatDataCode("Light", p_oTree12->GetSpecies(), p_oTree12->GetType()), &fActualLight);
  CPPUNIT_ASSERT(fActualLight == fLight5);
  CPPUNIT_ASSERT(p_oPop->GetFloatDataCode("Light", p_oTree13->GetSpecies(), p_oTree13->GetType()) == -1);
  p_oTree14->GetValue(p_oPop->GetFloatDataCode("Light", p_oTree14->GetSpecies(), p_oTree14->GetType()), &fActualLight);
  CPPUNIT_ASSERT(fActualLight == fLight5);

  //Grid 0,5 trees
  CPPUNIT_ASSERT(p_oPop->GetFloatDataCode("Light", p_oTree15->GetSpecies(), p_oTree15->GetType()) == -1);
  p_oTree16->GetValue(p_oPop->GetFloatDataCode("Light", p_oTree16->GetSpecies(), p_oTree16->GetType()), &fActualLight);
  CPPUNIT_ASSERT(fActualLight == fLight6);
  p_oTree17->GetValue(p_oPop->GetFloatDataCode("Light", p_oTree17->GetSpecies(), p_oTree17->GetType()), &fActualLight);
  CPPUNIT_ASSERT(fActualLight == fLight6);
  CPPUNIT_ASSERT(p_oPop->GetFloatDataCode("Light", p_oTree18->GetSpecies(), p_oTree18->GetType()) == -1);
  p_oTree19->GetValue(p_oPop->GetFloatDataCode("Light", p_oTree19->GetSpecies(), p_oTree19->GetType()), &fActualLight);
  CPPUNIT_ASSERT(fActualLight == fLight6);
  CPPUNIT_ASSERT(p_oPop->GetFloatDataCode("Light", p_oTree20->GetSpecies(), p_oTree20->GetType()) == -1);
  p_oTree21->GetValue(p_oPop->GetFloatDataCode("Light", p_oTree21->GetSpecies(), p_oTree21->GetType()), &fActualLight);
  CPPUNIT_ASSERT(fActualLight == fLight6);
  CPPUNIT_ASSERT(p_oPop->GetFloatDataCode("Light", p_oTree22->GetSpecies(), p_oTree22->GetType()) == -1);
  CPPUNIT_ASSERT(p_oPop->GetFloatDataCode("Light", p_oTree23->GetSpecies(), p_oTree23->GetType()) == -1);
  p_oTree24->GetValue(p_oPop->GetFloatDataCode("Light", p_oTree24->GetSpecies(), p_oTree24->GetType()), &fActualLight);
  CPPUNIT_ASSERT(fActualLight == fLight6);
  //Snag - has light but doesn't match
  p_oTree27->GetValue(p_oPop->GetFloatDataCode("Light", p_oTree27->GetSpecies(), p_oTree27->GetType()), &fActualLight);
  CPPUNIT_ASSERT(fActualLight != fLight6);

  //Grid 0,6 trees
  CPPUNIT_ASSERT(p_oPop->GetFloatDataCode("Light", p_oTree28->GetSpecies(), p_oTree28->GetType()) == -1);
  CPPUNIT_ASSERT(p_oPop->GetFloatDataCode("Light", p_oTree29->GetSpecies(), p_oTree29->GetType()) == -1);
  CPPUNIT_ASSERT(p_oPop->GetFloatDataCode("Light", p_oTree30->GetSpecies(), p_oTree30->GetType()) == -1);
  p_oTree31->GetValue(p_oPop->GetFloatDataCode("Light", p_oTree31->GetSpecies(), p_oTree31->GetType()), &fActualLight);
  CPPUNIT_ASSERT(fActualLight == fLight7);
}

/////////////////////////////////////////////////////////////////////////////
// NormalProcessingRun2()
/////////////////////////////////////////////////////////////////////////////
void clTestBasalAreaLight::NormalProcessingRun2(clSimManager *p_oSimManager)
{
  clBehaviorBase *p_oTemp;
  clBasalAreaLight *p_oLightBeh;
  float fActualLight, fExpectedLight, fConBA, fAngBA;

  //Feed our file to the sim manager
  p_oSimManager->ReadFile(WriteXMLFile2());

  //Check the mean GLI calculations directly for 4 values
  p_oTemp = p_oSimManager->GetBehaviorObject("basalarealightshell");
  p_oLightBeh = dynamic_cast<clBasalAreaLight*>(p_oTemp);

  fExpectedLight = 12.4;
  fConBA = 0;
  fAngBA = 0;
  fActualLight = p_oLightBeh->GetMeanGLI(fConBA, fAngBA);
  CPPUNIT_ASSERT(fabs(fExpectedLight - fActualLight) < 0.0001);

  fExpectedLight = 4.677703256;
  fConBA = 1;
  fAngBA = 6;
  fActualLight = p_oLightBeh->GetMeanGLI(fConBA, fAngBA);
  CPPUNIT_ASSERT(fabs(fExpectedLight - fActualLight) < 0.0001);

  fExpectedLight = 100;
  fConBA = 5;
  fAngBA = 0;
  fActualLight = p_oLightBeh->GetMeanGLI(fConBA, fAngBA);
  CPPUNIT_ASSERT(fabs(fExpectedLight - fActualLight) < 0.0001);

  fExpectedLight = 0;
  fConBA = 6;
  fAngBA = 0;
  fActualLight = p_oLightBeh->GetMeanGLI(fConBA, fAngBA);
  CPPUNIT_ASSERT(fabs(fExpectedLight - fActualLight) < 0.0001);

  fExpectedLight = 0;
  fConBA = 100;
  fAngBA = 0;
  fActualLight = p_oLightBeh->GetMeanGLI(fConBA, fAngBA);
  CPPUNIT_ASSERT(fabs(fExpectedLight - fActualLight) < 0.0001);
}

/////////////////////////////////////////////////////////////////////////////
// NormalProcessingRun3()
/////////////////////////////////////////////////////////////////////////////
void clTestBasalAreaLight::NormalProcessingRun3(clSimManager *p_oSimManager)
{
  using namespace std;
  clTreePopulation *p_oPop;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;
  clGrid *p_oLightGrid;
  int p_iCount[101];
  float fLight;
  int iX, iY, iLightCode;

  //Feed our file to the sim manager
  p_oSimManager->ReadFile(WriteXMLFile3());

  //Verify the grid cell size
  p_oLightGrid = p_oSimManager->GetGridObject("Basal Area Light");
  iLightCode = p_oLightGrid->GetFloatDataCode("Light");
  CPPUNIT_ASSERT(-1 < iLightCode);
  CPPUNIT_ASSERT(10 == p_oLightGrid->GetLengthXCells());
  CPPUNIT_ASSERT(10 == p_oLightGrid->GetLengthYCells());

  //Put 3 trees in each grid cell
  p_oPop = (clTreePopulation*) p_oSimManager->GetPopulationObject("treepopulation");
  for (iX = 0; iX < p_oLightGrid->GetNumberXCells(); iX++) {
    for (iY = 0; iY < p_oLightGrid->GetNumberYCells(); iY++) {
      p_oPop->CreateTree( (iX * 10) + 5, (iY * 10) + 5, 0, clTreePopulation::adult, 45 );
      p_oPop->CreateTree( (iX * 10) + 5, (iY * 10) + 5, 1, clTreePopulation::adult, 24 );
      p_oPop->CreateTree( (iX * 10) + 5, (iY * 10) + 5, 2, clTreePopulation::adult, 70 );
    }
  }

  //Run one timestep
  p_oSimManager->RunSim(1);

  //Count up the light levels and put them in buckets
  for (iX = 0; iX < 101; iX++)
    p_iCount[iX] = 0;

  for (iX = 0; iX < p_oLightGrid->GetNumberXCells(); iX++) {
    for (iY = 0; iY < p_oLightGrid->GetNumberYCells(); iY++) {
      p_oLightGrid->GetValueOfCell(iX, iY, iLightCode, &fLight);
      p_iCount[(int)fLight]++;
    }
  }

  //Write out the results
  std::fstream oOut;
  oOut.open( "Basal Area Light Distribution.txt", ios::out | ios::trunc );
  oOut << "Basal Area Light Distribution\n";
  oOut << "Number of grid values falling into each GLI bucket (BA = 0.59):\n";
  oOut << "0";
  for (iX = 1; iX < 101; iX++)
    oOut << "\t" << iX;
  oOut << "\n" << p_iCount[0];
  for (iX = 1; iX < 101; iX++)
    oOut << "\t" << p_iCount[iX];
  oOut << "\n";

  //Count up the tree values and write that distribution as well
  for (iX = 0; iX < 101; iX++)
    p_iCount[iX] = 0;
  p_oAllTrees = p_oPop->Find("all");
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {
    p_oTree->GetValue(p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType()), &fLight);
    p_iCount[(int)fLight]++;
    p_oTree = p_oAllTrees->NextTree();
  }

  oOut << "Number of tree values falling into each GLI bucket (BA = 0.59):\n";
  oOut << "0";
  for (iX = 1; iX < 101; iX++)
    oOut << "\t" << iX;
  oOut << "\n" << p_iCount[0];
  for (iX = 1; iX < 101; iX++)
    oOut << "\t" << p_iCount[iX];
  oOut << "\n";

  oOut.close();
}

/////////////////////////////////////////////////////////////////////////////
// NormalProcessingRun4()
/////////////////////////////////////////////////////////////////////////////
void clTestBasalAreaLight::NormalProcessingRun4(clSimManager *p_oSimManager)
{
  clGrid *p_oLightGrid;
  float fActualLight, fExpectedLight = 95, fExpConBA = 0.03, fExpAngBA = 0,
        fActualConBA, fActualAngBA;
  int iLightCode, iConBACode, iAngBACode, iX, iY,
      iNumXCells, iNumYCells;


  //Feed our file to the sim manager
  p_oSimManager->ReadFile(WriteXMLFile4());

  //Run one timestep
  p_oSimManager->RunSim(1);

  p_oLightGrid = p_oSimManager->GetGridObject("Basal Area Light");
  iLightCode = p_oLightGrid->GetFloatDataCode("Light");
  CPPUNIT_ASSERT(-1 < iLightCode);
  iConBACode = p_oLightGrid->GetFloatDataCode("Con BA");
  CPPUNIT_ASSERT(-1 < iConBACode);
  iAngBACode = p_oLightGrid->GetFloatDataCode("Ang BA");
  CPPUNIT_ASSERT(-1 < iAngBACode);

  //Make sure that all cells got a light level
  iNumXCells = p_oLightGrid->GetNumberXCells();
  iNumYCells = p_oLightGrid->GetNumberYCells();
  for (iX = 0; iX < iNumXCells; iX++) {
    for (iY = 0; iY < iNumYCells; iY++) {
      p_oLightGrid->GetValueOfCell(iX, iY, iLightCode, &fActualLight);
      p_oLightGrid->GetValueOfCell(iX, iY, iConBACode, &fActualConBA);
      p_oLightGrid->GetValueOfCell(iX, iY, iAngBACode, &fActualAngBA);
      CPPUNIT_ASSERT(fExpectedLight == fActualLight);
      CPPUNIT_ASSERT(fExpConBA == fActualConBA);
      CPPUNIT_ASSERT(fExpAngBA == fActualAngBA);
    }
  }
}

/////////////////////////////////////////////////////////////////////////////
// NormalProcessingRun5()
/////////////////////////////////////////////////////////////////////////////
void clTestBasalAreaLight::NormalProcessingRun5(clSimManager *p_oSimManager)
{
  clTreePopulation *p_oPop;
  clGrid *p_oLightGrid;
  float fExpConBA, //Conifer basal area we're expecting
        fExpAngBA, //Angiosperm basal area we're expecting
        fActualConBA, //Conifer basal area calculated by SORTIE
        fActualAngBA, //Angiosperm basal area calculated by SORTIE
        fDiam, fX, fY; //For creating trees
        //For stashing light levels between timesteps
  int iLightCode, iConBACode, iAngBACode, iSpecies;


  //Feed our file to the sim manager
  p_oSimManager->ReadFile(WriteXMLFile5());
  p_oPop = (clTreePopulation*) p_oSimManager->GetPopulationObject("treepopulation");

  //Add trees
  fX = 29.38; fY = 34.87; iSpecies = 0; fDiam = 74.50;
  p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDiam );

  fX = 23.44; fY = 35.27; iSpecies = 2; fDiam = 95.05;
  p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDiam );

  fX = 30.70; fY = 28.31; iSpecies = 1; fDiam = 78.92;
  p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDiam );

  fX = 25.69; fY = 27.20; iSpecies = 3; fDiam = 69.95;
  p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDiam );

  fX = 25.34; fY = 38.52; iSpecies = 0; fDiam = 74.06;
  p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDiam );

  fX = 30.11; fY = 38.41; iSpecies = 3; fDiam = 93.52;
  p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDiam );

  fX = 24.55; fY = 25.90; iSpecies = 1; fDiam = 67.81;
  p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDiam );

  fX = 20.73; fY = 36.66; iSpecies = 2; fDiam = 40.47;
  p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDiam );

  fX = 19.64; fY = 31.49; iSpecies = 3; fDiam = 92.60;
  p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDiam );

  fX = 24.82; fY = 25.12; iSpecies = 0; fDiam = 35.49;
  p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDiam );

  fX = 35.63; fY = 33.87; iSpecies = 1; fDiam = 71.42;
  p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDiam );

  fX = 27.03; fY = 24.10; iSpecies = 3; fDiam = 63.52;
  p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDiam );

  fX = 36.08; fY = 31.00; iSpecies = 3; fDiam = 59.44;
  p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDiam );

  fX = 20.41; fY = 27.57; iSpecies = 2; fDiam = 51.39;
  p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDiam );

  fX = 20.83; fY = 25.51; iSpecies = 2; fDiam = 95.57;
  p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDiam );

  fX = 38.26; fY = 32.18; iSpecies = 0; fDiam = 34.70;
  p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDiam );

  fX = 38.56; fY = 35.23; iSpecies = 3; fDiam = 60.03;
  p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDiam );

  fX = 35.73; fY = 24.74; iSpecies = 2; fDiam = 62.12;
  p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDiam );

  fX = 38.55; fY = 29.70; iSpecies = 0; fDiam = 31.72;
  p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDiam );

  fX = 38.71; fY = 29.89; iSpecies = 2; fDiam = 78.87;
  p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDiam );

  fX = 37.34; fY = 38.96; iSpecies = 3; fDiam = 83.99;
  p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDiam );

  fX = 36.84; fY = 23.88; iSpecies = 0; fDiam = 52.87;
  p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDiam );

  fX = 35.42; fY = 22.05; iSpecies = 1; fDiam = 31.12;
  p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDiam );

  fX = 38.84; fY = 24.81; iSpecies = 0; fDiam = 41.15;
  p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDiam );

  fX = 23.09; fY = 18.10; iSpecies = 1; fDiam = 49.68;
  p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDiam );

  fX = 29.13; fY = 17.01; iSpecies = 3; fDiam = 18.39;
  p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDiam );

  fX = 25.42; fY = 15.83; iSpecies = 2; fDiam = 96.25;
  p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDiam );

  fX = 27.92; fY = 15.67; iSpecies = 0; fDiam = 40.37;
  p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDiam );

  fX = 25.23; fY = 15.28; iSpecies = 1; fDiam = 24.07;
  p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDiam );

  fX = 34.72; fY = 16.18; iSpecies = 1; fDiam = 44.42;
  p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDiam );

  fX = 36.12; fY = 16.65; iSpecies = 2; fDiam = 99.04;
  p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDiam );

  fX = 39.98; fY = 15.98; iSpecies = 1; fDiam = 45.91;
  p_oPop->CreateTree( fX, fY, iSpecies, clTreePopulation::adult, fDiam );

  //Run one timestep
  p_oSimManager->RunSim(1);

  p_oLightGrid = p_oSimManager->GetGridObject("Basal Area Light");
  iLightCode = p_oLightGrid->GetFloatDataCode("Light");
  CPPUNIT_ASSERT(-1 < iLightCode);
  iConBACode = p_oLightGrid->GetFloatDataCode("Con BA");
  CPPUNIT_ASSERT(-1 < iConBACode);
  iAngBACode = p_oLightGrid->GetFloatDataCode("Ang BA");
  CPPUNIT_ASSERT(-1 < iAngBACode);

  //Check to make sure the basal area totals are correct
  //Grid 5, 5
  fExpConBA = 1.459611208;
  fExpAngBA = 1.551503445;
  p_oLightGrid->GetValueOfCell(5, 5, iConBACode, &fActualConBA);
  p_oLightGrid->GetValueOfCell(5, 5, iAngBACode, &fActualAngBA);
  CPPUNIT_ASSERT(fabs(fExpConBA - fActualConBA) < 0.001);
  CPPUNIT_ASSERT(fabs(fExpAngBA - fActualAngBA) < 0.001);

  //Grid 5, 6
  fExpConBA = 1.803823734;
  fExpAngBA = 3.31248918;
  p_oLightGrid->GetValueOfCell(5, 6, iConBACode, &fActualConBA);
  p_oLightGrid->GetValueOfCell(5, 6, iAngBACode, &fActualAngBA);
  CPPUNIT_ASSERT(fabs(fExpConBA - fActualConBA) < 0.001);
  CPPUNIT_ASSERT(fabs(fExpAngBA - fActualAngBA) < 0.001);

  //Grid 6, 5
  fExpConBA = 1.852594769;
  fExpAngBA = 2.305672952;
  p_oLightGrid->GetValueOfCell(6, 5, iConBACode, &fActualConBA);
  p_oLightGrid->GetValueOfCell(6, 5, iAngBACode, &fActualAngBA);
  CPPUNIT_ASSERT(fabs(fExpConBA - fActualConBA) < 0.001);
  CPPUNIT_ASSERT(fabs(fExpAngBA - fActualAngBA) < 0.001);
}

/////////////////////////////////////////////////////////////////////////////
//  WriteXMLFile1()
/////////////////////////////////////////////////////////////////////////////
const char* clTestBasalAreaLight::WriteXMLFile1()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>3</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>96</plot_lenX>"
       << "<plot_lenY>96</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "</plot>";

  WriteCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>BasalAreaLight</behaviorName>"
       << "<applyTo species=\"Species_2\" type=\"Adult\" />"
       << "<applyTo species=\"Species_2\" type=\"Sapling\" />"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>ConstantGLI</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Snag\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<ConstantGLI2>"
       << "<li_constGLI>100</li_constGLI>"
       << "</ConstantGLI2>"
       << "<BasalAreaLight1>"
       << "<li_baLightA>12.4</li_baLightA>"
       << "<li_baConiferLightB>1.8</li_baConiferLightB>"
       << "<li_baConiferLightC>2.1</li_baConiferLightC>"
       << "<li_baAngiospermLightB>3.83</li_baAngiospermLightB>"
       << "<li_baAngiospermLightC>3.04</li_baAngiospermLightC>"
       << "<li_baLightSigma>0.82</li_baLightSigma>"
       << "<li_baLightChangeThreshold>0.05</li_baLightChangeThreshold>"
       << "<li_baLightMinDBH>10</li_baLightMinDBH>"
       << "<li_baLightSearchRadius>4</li_baLightSearchRadius>"
       << "<li_baTreeType>"
       << "<li_bttVal species=\"Species_1\">1</li_bttVal>"
       << "<li_bttVal species=\"Species_2\">0</li_bttVal>"
       << "<li_bttVal species=\"Species_3\">1</li_bttVal>"
       << "<li_bttVal species=\"Species_4\">0</li_bttVal>"
       << "</li_baTreeType>"
       << "</BasalAreaLight1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
//  WriteXMLFile2()
/////////////////////////////////////////////////////////////////////////////
const char* clTestBasalAreaLight::WriteXMLFile2()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>3</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>96</plot_lenX>"
       << "<plot_lenY>96</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "</plot>";

  WriteCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>BasalAreaLight</behaviorName>"
       << "<applyTo species=\"Species_2\" type=\"Adult\" />"
       << "<applyTo species=\"Species_2\" type=\"Sapling\" />"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "</behaviorList>"
       << "<BasalAreaLight1>"
       << "<li_baLightA>12.4</li_baLightA>"
       << "<li_baConiferLightB>1</li_baConiferLightB>"
       << "<li_baConiferLightC>-5.17921</li_baConiferLightC>"
       << "<li_baAngiospermLightB>0.9</li_baAngiospermLightB>"
       << "<li_baAngiospermLightC>3.04</li_baAngiospermLightC>"
       << "<li_baLightSigma>0.82</li_baLightSigma>"
       << "<li_baLightChangeThreshold>0.05</li_baLightChangeThreshold>"
       << "<li_baLightMinDBH>10</li_baLightMinDBH>"
       << "<li_baLightSearchRadius>10</li_baLightSearchRadius>"
       << "<li_baTreeType>"
       << "<li_bttVal species=\"Species_1\">1</li_bttVal>"
       << "<li_bttVal species=\"Species_2\">0</li_bttVal>"
       << "<li_bttVal species=\"Species_3\">1</li_bttVal>"
       << "<li_bttVal species=\"Species_4\">0</li_bttVal>"
       << "</li_baTreeType>"
       << "</BasalAreaLight1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
//  WriteXMLFile3()
/////////////////////////////////////////////////////////////////////////////
const char* clTestBasalAreaLight::WriteXMLFile3()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>3</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>1000</plot_lenX>"
       << "<plot_lenY>1000</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "</plot>";

  WriteCommonStuff(oOut);

  oOut << "<grid gridName=\"Basal Area Light\">"
       << "<ma_floatCodes>"
       << "<ma_floatCode label=\"Light\">0</ma_floatCode>"
       << "<ma_floatCode label=\"Con BA\">1</ma_floatCode>"
       << "<ma_floatCode label=\"Ang BA\">2</ma_floatCode>"
       << "</ma_floatCodes>"
       << "<ma_lengthXCells>10</ma_lengthXCells>"
       << "<ma_lengthYCells>10</ma_lengthYCells>"
       << "</grid>";

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>BasalAreaLight</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Adult\" />"
       << "<applyTo species=\"Species_1\" type=\"Adult\" />"
       << "<applyTo species=\"Species_3\" type=\"Adult\" />"
       << "<applyTo species=\"Species_4\" type=\"Adult\" />"
       << "</behavior>"
       << "</behaviorList>"
       << "<BasalAreaLight1>"
       << "<li_baLightA>12.4</li_baLightA>"
       << "<li_baConiferLightB>1.8</li_baConiferLightB>"
       << "<li_baConiferLightC>2.1</li_baConiferLightC>"
       << "<li_baAngiospermLightB>3.83</li_baAngiospermLightB>"
       << "<li_baAngiospermLightC>3.04</li_baAngiospermLightC>"
       << "<li_baLightSigma>0.82</li_baLightSigma>"
       << "<li_baLightChangeThreshold>0.05</li_baLightChangeThreshold>"
       << "<li_baLightMinDBH>10</li_baLightMinDBH>"
       << "<li_baLightSearchRadius>10</li_baLightSearchRadius>"
       << "<li_baTreeType>"
       << "<li_bttVal species=\"Species_1\">1</li_bttVal>"
       << "<li_bttVal species=\"Species_2\">0</li_bttVal>"
       << "<li_bttVal species=\"Species_3\">1</li_bttVal>"
       << "<li_bttVal species=\"Species_4\">0</li_bttVal>"
       << "</li_baTreeType>"
       << "</BasalAreaLight1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
//  WriteXMLFile4()
/////////////////////////////////////////////////////////////////////////////
const char* clTestBasalAreaLight::WriteXMLFile4()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";
  float fLight = 95, fConBA = 0.03;
  int iX, iY, iNumXCells = 10, iNumYCells = 10;

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>3</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>100</plot_lenX>"
       << "<plot_lenY>100</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "</plot>";

  WriteCommonStuff(oOut);

  oOut << "<grid gridName=\"Basal Area Light\">"
       << "<ma_floatCodes>"
       << "<ma_floatCode label=\"Light\">0</ma_floatCode>"
       << "<ma_floatCode label=\"Con BA\">1</ma_floatCode>"
       << "<ma_floatCode label=\"Ang BA\">2</ma_floatCode>"
       << "</ma_floatCodes>"
       << "<ma_lengthXCells>10</ma_lengthXCells>"
       << "<ma_lengthYCells>10</ma_lengthYCells>";

  for (iX = 0; iX < iNumXCells; iX++) {
    for (iY = 0; iY < iNumYCells; iY++) {
      oOut << "<ma_v x=\"" << iX << "\" y=\"" << iY << "\">"
           << "<fl c=\"0\">" << fLight << "</fl>"
           << "<fl c=\"1\">" << fConBA << "</fl>"
           << "</ma_v>";
    }
  }

  oOut << "</grid>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>BasalAreaLight</behaviorName>"
       << "<listPosition>1</listPosition>"
       << "<version>1</version>"
       << "</behavior>"
       << "</behaviorList>"
       << "<BasalAreaLight1>"
       << "<li_baLightA>12.4</li_baLightA>"
       << "<li_baConiferLightB>1.8</li_baConiferLightB>"
       << "<li_baConiferLightC>2.1</li_baConiferLightC>"
       << "<li_baAngiospermLightB>3.83</li_baAngiospermLightB>"
       << "<li_baAngiospermLightC>3.04</li_baAngiospermLightC>"
       << "<li_baLightSigma>0.82</li_baLightSigma>"
       << "<li_baLightChangeThreshold>0.05</li_baLightChangeThreshold>"
       << "<li_baLightMinDBH>10</li_baLightMinDBH>"
       << "<li_baLightSearchRadius>10</li_baLightSearchRadius>"
       << "<li_baTreeType>"
       << "<li_bttVal species=\"Species_1\">1</li_bttVal>"
       << "<li_bttVal species=\"Species_2\">0</li_bttVal>"
       << "<li_bttVal species=\"Species_3\">1</li_bttVal>"
       << "<li_bttVal species=\"Species_4\">0</li_bttVal>"
       << "</li_baTreeType>"
       << "</BasalAreaLight1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
//  WriteXMLFile5()
/////////////////////////////////////////////////////////////////////////////
const char* clTestBasalAreaLight::WriteXMLFile5()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>3</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>100</plot_lenX>"
       << "<plot_lenY>100</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "</plot>";

  WriteCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>BasalAreaLight</behaviorName>"
       << "<applyTo species=\"Species_2\" type=\"Adult\" />"
       << "<applyTo species=\"Species_2\" type=\"Sapling\" />"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>ConstantGLI</behaviorName>"
       << "<version>1</version>"
       << "<applyTo species=\"Species_1\" type=\"Snag\"/>"
       << "<listPosition>2</listPosition>"
       << "</behavior>"
       << "</behaviorList>"
       << "<grid gridName=\"Basal Area Light\">"
       << "<ma_floatCodes>"
       << "<ma_floatCode label=\"Light\">0</ma_floatCode>"
       << "<ma_floatCode label=\"Con BA\">1</ma_floatCode>"
       << "<ma_floatCode label=\"Ang BA\">2</ma_floatCode>"
       << "</ma_floatCodes>"
       << "<ma_lengthXCells>5</ma_lengthXCells>"
       << "<ma_lengthYCells>5</ma_lengthYCells>"
       << "</grid>"
       << "<ConstantGLI2>"
       << "<li_constGLI>100</li_constGLI>"
       << "</ConstantGLI2>"
       << "<BasalAreaLight1>"
       << "<li_baLightA>12.4</li_baLightA>"
       << "<li_baConiferLightB>1.8</li_baConiferLightB>"
       << "<li_baConiferLightC>2.1</li_baConiferLightC>"
       << "<li_baAngiospermLightB>3.83</li_baAngiospermLightB>"
       << "<li_baAngiospermLightC>3.04</li_baAngiospermLightC>"
       << "<li_baLightSigma>0.82</li_baLightSigma>"
       << "<li_baLightChangeThreshold>0.05</li_baLightChangeThreshold>"
       << "<li_baLightMinDBH>10</li_baLightMinDBH>"
       << "<li_baLightSearchRadius>8.46</li_baLightSearchRadius>"
       << "<li_baTreeType>"
       << "<li_bttVal species=\"Species_1\">1</li_bttVal>"
       << "<li_bttVal species=\"Species_2\">0</li_bttVal>"
       << "<li_bttVal species=\"Species_3\">1</li_bttVal>"
       << "<li_bttVal species=\"Species_4\">0</li_bttVal>"
       << "</li_baTreeType>"
       << "</BasalAreaLight1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
//  WriteXMLErrorFile1()
/////////////////////////////////////////////////////////////////////////////
const char* clTestBasalAreaLight::WriteXMLErrorFile1()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>3</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>96</plot_lenX>"
       << "<plot_lenY>96</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "</plot>";

  WriteCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>BasalAreaLight</behaviorName>"
       << "<applyTo species=\"Species_2\" type=\"Adult\" />"
       << "<applyTo species=\"Species_2\" type=\"Sapling\" />"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "</behaviorList>"
       << "<BasalAreaLight1>"
       << "<li_baLightA>12.4</li_baLightA>"
       << "<li_baConiferLightB>1.8</li_baConiferLightB>"
       << "<li_baConiferLightC>0</li_baConiferLightC>"
       << "<li_baAngiospermLightB>3.83</li_baAngiospermLightB>"
       << "<li_baAngiospermLightC>3.04</li_baAngiospermLightC>"
       << "<li_baLightSigma>0.82</li_baLightSigma>"
       << "<li_baLightChangeThreshold>0.05</li_baLightChangeThreshold>"
       << "<li_baLightMinDBH>10</li_baLightMinDBH>"
       << "<li_baLightSearchRadius>10</li_baLightSearchRadius>"
       << "<li_baTreeType>"
       << "<li_bttVal species=\"Species_1\">1</li_bttVal>"
       << "<li_bttVal species=\"Species_2\">0</li_bttVal>"
       << "<li_bttVal species=\"Species_3\">1</li_bttVal>"
       << "<li_bttVal species=\"Species_4\">0</li_bttVal>"
       << "</li_baTreeType>"
       << "</BasalAreaLight1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
//  WriteXMLErrorFile2()
/////////////////////////////////////////////////////////////////////////////
const char* clTestBasalAreaLight::WriteXMLErrorFile2()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>3</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>96</plot_lenX>"
       << "<plot_lenY>96</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "</plot>";

  WriteCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>BasalAreaLight</behaviorName>"
       << "<applyTo species=\"Species_2\" type=\"Adult\" />"
       << "<applyTo species=\"Species_2\" type=\"Sapling\" />"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "</behaviorList>"
       << "<BasalAreaLight1>"
       << "<li_baLightA>12.4</li_baLightA>"
       << "<li_baConiferLightB>1.8</li_baConiferLightB>"
       << "<li_baConiferLightC>2.1</li_baConiferLightC>"
       << "<li_baAngiospermLightB>3.83</li_baAngiospermLightB>"
       << "<li_baAngiospermLightC>0</li_baAngiospermLightC>"
       << "<li_baLightSigma>0.82</li_baLightSigma>"
       << "<li_baLightChangeThreshold>0.05</li_baLightChangeThreshold>"
       << "<li_baLightMinDBH>10</li_baLightMinDBH>"
       << "<li_baLightSearchRadius>10</li_baLightSearchRadius>"
       << "<li_baTreeType>"
       << "<li_bttVal species=\"Species_1\">1</li_bttVal>"
       << "<li_bttVal species=\"Species_2\">0</li_bttVal>"
       << "<li_bttVal species=\"Species_3\">1</li_bttVal>"
       << "<li_bttVal species=\"Species_4\">0</li_bttVal>"
       << "</li_baTreeType>"
       << "</BasalAreaLight1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
//  WriteXMLErrorFile3()
/////////////////////////////////////////////////////////////////////////////
const char* clTestBasalAreaLight::WriteXMLErrorFile3()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>3</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>96</plot_lenX>"
       << "<plot_lenY>96</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "</plot>";

  WriteCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>BasalAreaLight</behaviorName>"
       << "<applyTo species=\"Species_2\" type=\"Adult\" />"
       << "<applyTo species=\"Species_2\" type=\"Sapling\" />"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "</behaviorList>"
       << "<BasalAreaLight1>"
       << "<li_baLightA>12.4</li_baLightA>"
       << "<li_baConiferLightB>1.8</li_baConiferLightB>"
       << "<li_baConiferLightC>2.1</li_baConiferLightC>"
       << "<li_baAngiospermLightB>3.83</li_baAngiospermLightB>"
       << "<li_baAngiospermLightC>3.04</li_baAngiospermLightC>"
       << "<li_baLightSigma>0.82</li_baLightSigma>"
       << "<li_baLightChangeThreshold>-0.05</li_baLightChangeThreshold>"
       << "<li_baLightMinDBH>10</li_baLightMinDBH>"
       << "<li_baLightSearchRadius>10</li_baLightSearchRadius>"
       << "<li_baTreeType>"
       << "<li_bttVal species=\"Species_1\">1</li_bttVal>"
       << "<li_bttVal species=\"Species_2\">0</li_bttVal>"
       << "<li_bttVal species=\"Species_3\">1</li_bttVal>"
       << "<li_bttVal species=\"Species_4\">0</li_bttVal>"
       << "</li_baTreeType>"
       << "</BasalAreaLight1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
//  WriteXMLErrorFile4()
/////////////////////////////////////////////////////////////////////////////
const char* clTestBasalAreaLight::WriteXMLErrorFile4()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>3</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>96</plot_lenX>"
       << "<plot_lenY>96</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "</plot>";

  WriteCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>BasalAreaLight</behaviorName>"
       << "<applyTo species=\"Species_2\" type=\"Adult\" />"
       << "<applyTo species=\"Species_2\" type=\"Sapling\" />"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "</behaviorList>"
       << "<BasalAreaLight1>"
       << "<li_baLightA>12.4</li_baLightA>"
       << "<li_baConiferLightB>1.8</li_baConiferLightB>"
       << "<li_baConiferLightC>2.1</li_baConiferLightC>"
       << "<li_baAngiospermLightB>3.83</li_baAngiospermLightB>"
       << "<li_baAngiospermLightC>3.04</li_baAngiospermLightC>"
       << "<li_baLightSigma>0.82</li_baLightSigma>"
       << "<li_baLightChangeThreshold>0.05</li_baLightChangeThreshold>"
       << "<li_baLightMinDBH>-10</li_baLightMinDBH>"
       << "<li_baLightSearchRadius>10</li_baLightSearchRadius>"
       << "<li_baTreeType>"
       << "<li_bttVal species=\"Species_1\">1</li_bttVal>"
       << "<li_bttVal species=\"Species_2\">0</li_bttVal>"
       << "<li_bttVal species=\"Species_3\">1</li_bttVal>"
       << "<li_bttVal species=\"Species_4\">0</li_bttVal>"
       << "</li_baTreeType>"
       << "</BasalAreaLight1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteXMLErrorFile5()
/////////////////////////////////////////////////////////////////////////////
const char* clTestBasalAreaLight::WriteXMLErrorFile5()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>3</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>100</plot_lenX>"
       << "<plot_lenY>100</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "</plot>";

  WriteCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>BasalAreaLight</behaviorName>"
       << "<applyTo species=\"Species_2\" type=\"Adult\" />"
       << "<applyTo species=\"Species_2\" type=\"Sapling\" />"
       << "<listPosition>1</listPosition>"
       << "<version>1</version>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>ConstantGLI</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Snag\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<ConstantGLI2>"
       << "<li_constGLI>100</li_constGLI>"
       << "</ConstantGLI2>"
       << "<BasalAreaLight1>"
       << "<li_baLightA>12.4</li_baLightA>"
       << "<li_baConiferLightB>1.8</li_baConiferLightB>"
       << "<li_baConiferLightC>2.1</li_baConiferLightC>"
       << "<li_baAngiospermLightB>3.83</li_baAngiospermLightB>"
       << "<li_baAngiospermLightC>3.04</li_baAngiospermLightC>"
       << "<li_baLightSigma>0.82</li_baLightSigma>"
       << "<li_baLightChangeThreshold>0.05</li_baLightChangeThreshold>"
       << "<li_baLightMinDBH>10</li_baLightMinDBH>"
       << "<li_baLightSearchRadius>-10</li_baLightSearchRadius>"
       << "<li_baTreeType>"
       << "<li_bttVal species=\"Species_1\">1</li_bttVal>"
       << "<li_bttVal species=\"Species_2\">0</li_bttVal>"
       << "<li_bttVal species=\"Species_3\">1</li_bttVal>"
       << "<li_bttVal species=\"Species_4\">0</li_bttVal>"
       << "</li_baTreeType>"
       << "</BasalAreaLight1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteCommonStuff()
/////////////////////////////////////////////////////////////////////////////
void clTestBasalAreaLight::WriteCommonStuff( std::fstream &oOut )
{
  using namespace std;
  oOut << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\"/>"
       << "<tr_species speciesName=\"Species_2\"/>"
       << "<tr_species speciesName=\"Species_3\"/>"
       << "<tr_species speciesName=\"Species_4\"/>"
       << "</tr_speciesList>"
       << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_2\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_3\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_4\">10.0</tr_madVal>"
       << "</tr_minAdultDBH>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_3\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_4\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>"
       << "</trees>"
       << "<allometry>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_2\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_3\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_4\">0.0299</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_2\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_3\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_4\">39.48</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_2\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_3\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_4\">0.0549</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_3\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_4\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_3\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_4\">0.8008</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_3\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_4\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_3\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_4\">0.389</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_3\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_4\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_2\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_3\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_4\">0.03418</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "<tr_whatSeedlingHeightDiam>"
       << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_2\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_3\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_4\">0</tr_wsehdVal>"
       << "</tr_whatSeedlingHeightDiam>"
       << "<tr_whatSaplingHeightDiam>"
       << "<tr_wsahdVal species=\"Species_1\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_2\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_3\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_4\">0</tr_wsahdVal>"
       << "</tr_whatSaplingHeightDiam>"
       << "<tr_whatAdultHeightDiam>"
       << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_2\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_3\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_4\">0</tr_wahdVal>"
       << "</tr_whatAdultHeightDiam>"
       << "<tr_whatAdultCrownRadDiam>"
       << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_2\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_3\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_4\">0</tr_wacrdVal>"
       << "</tr_whatAdultCrownRadDiam>"
       << "<tr_whatAdultCrownHeightHeight>"
       << "<tr_wachhVal species=\"Species_1\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_2\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_3\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_4\">0</tr_wachhVal>"
       << "</tr_whatAdultCrownHeightHeight>"
       << "<tr_whatSaplingCrownRadDiam>"
       << "<tr_wscrdVal species=\"Species_1\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_2\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_3\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_4\">0</tr_wscrdVal>"
       << "</tr_whatSaplingCrownRadDiam>"
       << "<tr_whatSaplingCrownHeightHeight>"
       << "<tr_wschhVal species=\"Species_1\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_2\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_3\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_4\">0</tr_wschhVal>"
       << "</tr_whatSaplingCrownHeightHeight>"
       << "</allometry>";
}
