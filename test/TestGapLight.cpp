//---------------------------------------------------------------------------
// TestGapLight.cpp
//---------------------------------------------------------------------------
#include "TestGapLight.h"
#include "TreePopulation.h"
#include "SimManager.h"
#include "Grid.h"
#include "BehaviorBase.h"
#include <math.h>
#include <fstream>

/////////////////////////////////////////////////////////////////////////////
//  TestGapLight
/////////////////////////////////////////////////////////////////////////////
void clTestGapLight::TestGapLight() {

  //Create the sim manager
  clSimManager *p_oSimManager = new clSimManager(3, 3, "");

  clTree *p_oTarget1, *p_oTarget2, *p_oTarget3, *p_oTarget4, *p_oTarget5,
         *p_oTarget6, *p_oTarget7, *p_oTree;
  float fX, fY, fGLIActual, fGLIExpected, fDiam;
  int iNumXCells, iNumYCells,
      iX, iY,
      iGapCode;
  bool bIsGap;

  //********************************
  // Run 1
  //********************************
  //Feed our file to the sim manager
  p_oSimManager->ReadFile(WriteXMLFile1());
  clPopulationBase *p_oTemp = p_oSimManager->GetPopulationObject("treepopulation");
  clTreePopulation *p_oPop = (clTreePopulation*)p_oTemp;

  //Verify that the grid is correctly set up and all cell values are NON-GAP
  clGrid *p_oGapGrid = p_oSimManager->GetGridObject("Gap Light");
  CPPUNIT_ASSERT(p_oGapGrid != NULL);
  iGapCode = p_oGapGrid->GetBoolDataCode("Is Gap");
  CPPUNIT_ASSERT(iGapCode > -1);
  //Verify the size of the grid cells
  CPPUNIT_ASSERT(8 == p_oGapGrid->GetLengthXCells());
  CPPUNIT_ASSERT(8 == p_oGapGrid->GetLengthYCells());
  //Verify the grid values
  iNumXCells = p_oGapGrid->GetNumberXCells();
  iNumYCells = p_oGapGrid->GetNumberYCells();
  for (iX = 0; iX < iNumXCells; iX++) {
    for (iY = 0; iY < iNumYCells; iY++) {

      p_oGapGrid->GetValueOfCell(iX, iY, iGapCode, &bIsGap);
        CPPUNIT_ASSERT(bIsGap == false);
    }
  }

  //Create the set of seedlings we'll test
  fX = 1;
  fY = 1;
  fDiam = 0.2;
  p_oTarget1 = p_oPop->CreateTree (fX, fY, 0, clTreePopulation::seedling, fDiam);

  fX = 11;
  fY = 8;
  fDiam = 0.2;
  p_oTarget2 = p_oPop->CreateTree (fX, fY, 0, clTreePopulation::seedling, fDiam);

  fX = 60;
  fY = 78;
  fDiam = 0.2;
  p_oTarget3 = p_oPop->CreateTree (fX, fY, 0, clTreePopulation::seedling, fDiam);

  fX = 79;
  fY = 23;
  fDiam = 0.2;
  p_oTarget4 = p_oPop->CreateTree (fX, fY, 0, clTreePopulation::seedling, fDiam);

  fX = 14;
  fY = 53.2;
  fDiam = 0.2;
  p_oTarget5 = p_oPop->CreateTree (fX, fY, 0, clTreePopulation::seedling, fDiam);

  fX = 80;
  fY = 70;
  fDiam = 0.2;
  p_oTarget6 = p_oPop->CreateTree (fX, fY, 0, clTreePopulation::seedling, fDiam);

  fX = 91;
  fY = 91;
  fDiam = 0.2;
  p_oTarget7 = p_oPop->CreateTree (fX, fY, 0, clTreePopulation::seedling, fDiam);


  //>>>>>>>>>>>>>>>>>>>>> Timestep 1 >>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  p_oSimManager->RunSim(1);

  //Test the gap status - all are gap
  for (iX = 0; iX < iNumXCells; iX++) {
    for (iY = 0; iY < iNumYCells; iY++) {

      p_oGapGrid->GetValueOfCell(iX, iY, iGapCode, &bIsGap);
        CPPUNIT_ASSERT(bIsGap == true);
    }
  }

  //Test the GLI values of the trees - all are 100
  fGLIExpected = 100.0;
  p_oTarget1->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget1->GetSpecies(), p_oTarget1->GetType()), &fGLIActual);
  CPPUNIT_ASSERT(fabs(fGLIActual - fGLIExpected) < 0.1);
  p_oTarget2->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget2->GetSpecies(), p_oTarget2->GetType()), &fGLIActual);
  CPPUNIT_ASSERT(fabs(fGLIActual - fGLIExpected) < 0.1);
  p_oTarget3->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget3->GetSpecies(), p_oTarget3->GetType()), &fGLIActual);
  CPPUNIT_ASSERT(fabs(fGLIActual - fGLIExpected) < 0.1);
  p_oTarget4->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget4->GetSpecies(), p_oTarget4->GetType()), &fGLIActual);
  CPPUNIT_ASSERT(fabs(fGLIActual - fGLIExpected) < 0.1);
  p_oTarget5->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget5->GetSpecies(), p_oTarget5->GetType()), &fGLIActual);
  CPPUNIT_ASSERT(fabs(fGLIActual - fGLIExpected) < 0.1);
  p_oTarget6->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget6->GetSpecies(), p_oTarget6->GetType()), &fGLIActual);
  CPPUNIT_ASSERT(fabs(fGLIActual - fGLIExpected) < 0.1);
  p_oTarget7->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget7->GetSpecies(), p_oTarget7->GetType()), &fGLIActual);
  CPPUNIT_ASSERT(fabs(fGLIActual - fGLIExpected) < 0.1);

  //>>>>>>>>>>>>>>>>>>>>> Timestep 2 >>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  //Add a list of adult trees
  p_oPop->CreateTree (0, 0, 0, clTreePopulation::adult, 15);
  p_oPop->CreateTree (10, 10, 0, clTreePopulation::adult, 15);
  p_oPop->CreateTree (15, 54, 0, clTreePopulation::adult, 15);
  p_oPop->CreateTree (14, 52, 0, clTreePopulation::adult, 15);
  p_oTree = p_oPop->CreateTree (90, 90, 0, clTreePopulation::adult, 15);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), natural);

  p_oSimManager->RunSim(1);

  //Test the gap status
  for (iX = 0; iX < iNumXCells; iX++) {
    for (iY = 0; iY < iNumYCells; iY++) {

      p_oGapGrid->GetValueOfCell(iX, iY, iGapCode, &bIsGap);

      if ((iX == 0 && iY == 0) ||
          (iX == 1 && iY == 1) ||
          (iX == 1 && iY == 6))
        CPPUNIT_ASSERT(bIsGap == false);
      else
        CPPUNIT_ASSERT(bIsGap == true);
    }
  }

  //Test the GLI values of the trees
  fGLIExpected = 0.0;
  p_oTarget1->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget1->GetSpecies(), p_oTarget1->GetType()), &fGLIActual);
  CPPUNIT_ASSERT(fabs(fGLIActual - fGLIExpected) < 0.1);
  fGLIExpected = 0.0;
  p_oTarget2->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget2->GetSpecies(), p_oTarget2->GetType()), &fGLIActual);
  CPPUNIT_ASSERT(fabs(fGLIActual - fGLIExpected) < 0.1);
  fGLIExpected = 100.0;
  p_oTarget3->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget3->GetSpecies(), p_oTarget3->GetType()), &fGLIActual);
  CPPUNIT_ASSERT(fabs(fGLIActual - fGLIExpected) < 0.1);
  fGLIExpected = 100.0;
  p_oTarget4->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget4->GetSpecies(), p_oTarget4->GetType()), &fGLIActual);
  CPPUNIT_ASSERT(fabs(fGLIActual - fGLIExpected) < 0.1);
  fGLIExpected = 0.0;
  p_oTarget5->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget5->GetSpecies(), p_oTarget5->GetType()), &fGLIActual);
  CPPUNIT_ASSERT(fabs(fGLIActual - fGLIExpected) < 0.1);
  fGLIExpected = 100.0;
  p_oTarget6->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget6->GetSpecies(), p_oTarget6->GetType()), &fGLIActual);
  CPPUNIT_ASSERT(fabs(fGLIActual - fGLIExpected) < 0.1);
  fGLIExpected = 100.0;
  p_oTarget7->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget7->GetSpecies(), p_oTarget7->GetType()), &fGLIActual);
  CPPUNIT_ASSERT(fabs(fGLIActual - fGLIExpected) < 0.1);

  //>>>>>>>>>>>>>>>>>>>>> Timestep 3 >>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  //Add adult trees to each grid cell
  for (iX = 0; iX < iNumXCells; iX++) {
    for (iY = 0; iY < iNumYCells; iY++) {

      p_oGapGrid->GetPointOfCell(iX, iY, &fX, &fY);
      p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, 15);
    }
  }

  p_oSimManager->RunSim(1);

  //Test the gap status - all are non-gap
  for (iX = 0; iX < iNumXCells; iX++) {
    for (iY = 0; iY < iNumYCells; iY++) {

      p_oGapGrid->GetValueOfCell(iX, iY, iGapCode, &bIsGap);
        CPPUNIT_ASSERT(bIsGap == false);
    }
  }

  //Test the GLI values of the trees
  fGLIExpected = 0.0;
  p_oTarget1->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget1->GetSpecies(), p_oTarget1->GetType()), &fGLIActual);
  CPPUNIT_ASSERT(fabs(fGLIActual - fGLIExpected) < 0.1);
  p_oTarget2->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget2->GetSpecies(), p_oTarget2->GetType()), &fGLIActual);
  CPPUNIT_ASSERT(fabs(fGLIActual - fGLIExpected) < 0.1);
  p_oTarget3->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget3->GetSpecies(), p_oTarget3->GetType()), &fGLIActual);
  CPPUNIT_ASSERT(fabs(fGLIActual - fGLIExpected) < 0.1);
  p_oTarget4->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget4->GetSpecies(), p_oTarget4->GetType()), &fGLIActual);
  CPPUNIT_ASSERT(fabs(fGLIActual - fGLIExpected) < 0.1);
  p_oTarget5->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget5->GetSpecies(), p_oTarget5->GetType()), &fGLIActual);
  CPPUNIT_ASSERT(fabs(fGLIActual - fGLIExpected) < 0.1);
  p_oTarget6->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget6->GetSpecies(), p_oTarget6->GetType()), &fGLIActual);
  CPPUNIT_ASSERT(fabs(fGLIActual - fGLIExpected) < 0.1);
  p_oTarget7->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget7->GetSpecies(), p_oTarget7->GetType()), &fGLIActual);
  CPPUNIT_ASSERT(fabs(fGLIActual - fGLIExpected) < 0.1);

  //>>>>>>>>>>>>>>>>>>>>> Timestep 4 >>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  //Kill all adult trees
  clTreeSearch *p_oAdults = p_oPop->Find("type=3");
  p_oTree = p_oAdults->NextTree();
  while (p_oTree) {
    p_oPop->KillTree(p_oTree, remove_tree);
    p_oTree = p_oAdults->NextTree();
  }

  p_oSimManager->RunSim(1);

  //Test the gap status - all are gap
  for (iX = 0; iX < iNumXCells; iX++) {
    for (iY = 0; iY < iNumYCells; iY++) {

      p_oGapGrid->GetValueOfCell(iX, iY, iGapCode, &bIsGap);
        CPPUNIT_ASSERT(bIsGap == true);
    }
  }

  //Test the GLI values of the trees - all are 100
  fGLIExpected = 100.0;
  p_oTarget1->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget1->GetSpecies(), p_oTarget1->GetType()), &fGLIActual);
  CPPUNIT_ASSERT(fabs(fGLIActual - fGLIExpected) < 0.1);
  p_oTarget2->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget2->GetSpecies(), p_oTarget2->GetType()), &fGLIActual);
  CPPUNIT_ASSERT(fabs(fGLIActual - fGLIExpected) < 0.1);
  p_oTarget3->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget3->GetSpecies(), p_oTarget3->GetType()), &fGLIActual);
  CPPUNIT_ASSERT(fabs(fGLIActual - fGLIExpected) < 0.1);
  p_oTarget4->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget4->GetSpecies(), p_oTarget4->GetType()), &fGLIActual);
  CPPUNIT_ASSERT(fabs(fGLIActual - fGLIExpected) < 0.1);
  p_oTarget5->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget5->GetSpecies(), p_oTarget5->GetType()), &fGLIActual);
  CPPUNIT_ASSERT(fabs(fGLIActual - fGLIExpected) < 0.1);
  p_oTarget6->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget6->GetSpecies(), p_oTarget6->GetType()), &fGLIActual);
  CPPUNIT_ASSERT(fabs(fGLIActual - fGLIExpected) < 0.1);
  p_oTarget7->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget7->GetSpecies(), p_oTarget7->GetType()), &fGLIActual);
  CPPUNIT_ASSERT(fabs(fGLIActual - fGLIExpected) < 0.1);



  //********************************
  // Run 2
  //********************************
  //Feed our file to the sim manager
  p_oSimManager->ReadFile(WriteXMLFile2());
  p_oTemp = p_oSimManager->GetPopulationObject("treepopulation");
  p_oPop = (clTreePopulation*)p_oTemp;

  //Verify that the grid is correctly set up and all cell values are NON-GAP
  p_oGapGrid = p_oSimManager->GetGridObject("Gap Light");
  CPPUNIT_ASSERT(p_oGapGrid != NULL);
  iGapCode = p_oGapGrid->GetBoolDataCode("Is Gap");
  CPPUNIT_ASSERT(iGapCode > -1);
  //Verify the size of the grid cells
  CPPUNIT_ASSERT(2 == p_oGapGrid->GetLengthXCells());
  CPPUNIT_ASSERT(4 == p_oGapGrid->GetLengthYCells());
  //Verify the grid values
  iNumXCells = p_oGapGrid->GetNumberXCells();
  iNumYCells = p_oGapGrid->GetNumberYCells();
  for (iX = 0; iX < iNumXCells; iX++) {
    for (iY = 0; iY < iNumYCells; iY++) {

      p_oGapGrid->GetValueOfCell(iX, iY, iGapCode, &bIsGap);
        CPPUNIT_ASSERT(bIsGap == false);
    }
  }

  //Create the set of seedlings we'll test
  fX = 1;
  fY = 1;
  fDiam = 0.2;
  p_oTarget1 = p_oPop->CreateTree (fX, fY, 0, clTreePopulation::seedling, fDiam);

  fX = 11;
  fY = 8;
  fDiam = 0.2;
  p_oTarget2 = p_oPop->CreateTree (fX, fY, 0, clTreePopulation::seedling, fDiam);

  fX = 60;
  fY = 78;
  fDiam = 0.2;
  p_oTarget3 = p_oPop->CreateTree (fX, fY, 0, clTreePopulation::seedling, fDiam);

  fX = 79;
  fY = 23;
  fDiam = 0.2;
  p_oTarget4 = p_oPop->CreateTree (fX, fY, 0, clTreePopulation::seedling, fDiam);

  fX = 14;
  fY = 53.2;
  fDiam = 0.2;
  p_oTarget5 = p_oPop->CreateTree (fX, fY, 0, clTreePopulation::seedling, fDiam);

  fX = 80;
  fY = 70;
  fDiam = 0.2;
  p_oTarget6 = p_oPop->CreateTree (fX, fY, 0, clTreePopulation::seedling, fDiam);

  fX = 91;
  fY = 91;
  fDiam = 0.2;
  p_oTarget7 = p_oPop->CreateTree (fX, fY, 0, clTreePopulation::seedling, fDiam);

  //>>>>>>>>>>>>>>>>>>>>> Timestep 1 >>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  p_oSimManager->RunSim(1);

  //Test the gap status - all are gap
  for (iX = 0; iX < iNumXCells; iX++) {
    for (iY = 0; iY < iNumYCells; iY++) {

      p_oGapGrid->GetValueOfCell(iX, iY, iGapCode, &bIsGap);
        CPPUNIT_ASSERT(bIsGap == true);
    }
  }

  //Test the GLI values of the trees - all are 100
  fGLIExpected = 100.0;
  p_oTarget1->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget1->GetSpecies(), p_oTarget1->GetType()), &fGLIActual);
  CPPUNIT_ASSERT(fabs(fGLIActual - fGLIExpected) < 0.1);
  p_oTarget2->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget2->GetSpecies(), p_oTarget2->GetType()), &fGLIActual);
  CPPUNIT_ASSERT(fabs(fGLIActual - fGLIExpected) < 0.1);
  p_oTarget3->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget3->GetSpecies(), p_oTarget3->GetType()), &fGLIActual);
  CPPUNIT_ASSERT(fabs(fGLIActual - fGLIExpected) < 0.1);
  p_oTarget4->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget4->GetSpecies(), p_oTarget4->GetType()), &fGLIActual);
  CPPUNIT_ASSERT(fabs(fGLIActual - fGLIExpected) < 0.1);
  p_oTarget5->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget5->GetSpecies(), p_oTarget5->GetType()), &fGLIActual);
  CPPUNIT_ASSERT(fabs(fGLIActual - fGLIExpected) < 0.1);
  p_oTarget6->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget6->GetSpecies(), p_oTarget6->GetType()), &fGLIActual);
  CPPUNIT_ASSERT(fabs(fGLIActual - fGLIExpected) < 0.1);
  p_oTarget7->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget7->GetSpecies(), p_oTarget7->GetType()), &fGLIActual);
  CPPUNIT_ASSERT(fabs(fGLIActual - fGLIExpected) < 0.1);

  //>>>>>>>>>>>>>>>>>>>>> Timestep 2 >>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  //Add a list of adult trees
  p_oPop->CreateTree (0, 0, 0, clTreePopulation::adult, 15);
  p_oPop->CreateTree (10, 10, 0, clTreePopulation::adult, 15);
  p_oPop->CreateTree (15, 54, 0, clTreePopulation::adult, 15);
  p_oPop->CreateTree (14, 52, 0, clTreePopulation::adult, 15);
  p_oTree = p_oPop->CreateTree (90, 90, 0, clTreePopulation::adult, 15);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", p_oTree->GetSpecies(), p_oTree->GetType()), natural);

  p_oSimManager->RunSim(1);

  //Test the gap status
  for (iX = 0; iX < iNumXCells; iX++) {
    for (iY = 0; iY < iNumYCells; iY++) {

      p_oGapGrid->GetValueOfCell(iX, iY, iGapCode, &bIsGap);

      if ((iX == 0 && iY == 0) ||
          (iX == 5 && iY == 2) ||
          (iX == 7 && iY == 13))
        CPPUNIT_ASSERT(bIsGap == false);
      else
        CPPUNIT_ASSERT(bIsGap == true);
    }
  }

  //Test the GLI values of the trees
  fGLIExpected = 0.0;
  p_oTarget1->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget1->GetSpecies(), p_oTarget1->GetType()), &fGLIActual);
  CPPUNIT_ASSERT(fabs(fGLIActual - fGLIExpected) < 0.1);
  fGLIExpected = 0.0;
  p_oTarget2->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget2->GetSpecies(), p_oTarget2->GetType()), &fGLIActual);
  CPPUNIT_ASSERT(fabs(fGLIActual - fGLIExpected) < 0.1);
  fGLIExpected = 100.0;
  p_oTarget3->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget3->GetSpecies(), p_oTarget3->GetType()), &fGLIActual);
  CPPUNIT_ASSERT(fabs(fGLIActual - fGLIExpected) < 0.1);
  fGLIExpected = 100.0;
  p_oTarget4->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget4->GetSpecies(), p_oTarget4->GetType()), &fGLIActual);
  CPPUNIT_ASSERT(fabs(fGLIActual - fGLIExpected) < 0.1);
  fGLIExpected = 0.0;
  p_oTarget5->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget5->GetSpecies(), p_oTarget5->GetType()), &fGLIActual);
  CPPUNIT_ASSERT(fabs(fGLIActual - fGLIExpected) < 0.1);
  fGLIExpected = 100.0;
  p_oTarget6->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget6->GetSpecies(), p_oTarget6->GetType()), &fGLIActual);
  CPPUNIT_ASSERT(fabs(fGLIActual - fGLIExpected) < 0.1);
  fGLIExpected = 100.0;
  p_oTarget7->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget7->GetSpecies(), p_oTarget7->GetType()), &fGLIActual);
  CPPUNIT_ASSERT(fabs(fGLIActual - fGLIExpected) < 0.1);

  //>>>>>>>>>>>>>>>>>>>>> Timestep 3 >>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  //Add adult trees to each grid cell
  for (iX = 0; iX < iNumXCells; iX++) {
    for (iY = 0; iY < iNumYCells; iY++) {

      p_oGapGrid->GetPointOfCell(iX, iY, &fX, &fY);
      p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, 15);
    }
  }

  p_oSimManager->RunSim(1);

  //Test the gap status - all are non-gap
  for (iX = 0; iX < iNumXCells; iX++) {
    for (iY = 0; iY < iNumYCells; iY++) {

      p_oGapGrid->GetValueOfCell(iX, iY, iGapCode, &bIsGap);
        CPPUNIT_ASSERT(bIsGap == false);
    }
  }

  //Test the GLI values of the trees
  fGLIExpected = 0.0;
  p_oTarget1->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget1->GetSpecies(), p_oTarget1->GetType()), &fGLIActual);
  CPPUNIT_ASSERT(fabs(fGLIActual - fGLIExpected) < 0.1);
  p_oTarget2->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget2->GetSpecies(), p_oTarget2->GetType()), &fGLIActual);
  CPPUNIT_ASSERT(fabs(fGLIActual - fGLIExpected) < 0.1);
  p_oTarget3->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget3->GetSpecies(), p_oTarget3->GetType()), &fGLIActual);
  CPPUNIT_ASSERT(fabs(fGLIActual - fGLIExpected) < 0.1);
  p_oTarget4->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget4->GetSpecies(), p_oTarget4->GetType()), &fGLIActual);
  CPPUNIT_ASSERT(fabs(fGLIActual - fGLIExpected) < 0.1);
  p_oTarget5->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget5->GetSpecies(), p_oTarget5->GetType()), &fGLIActual);
  CPPUNIT_ASSERT(fabs(fGLIActual - fGLIExpected) < 0.1);
  p_oTarget6->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget6->GetSpecies(), p_oTarget6->GetType()), &fGLIActual);
  CPPUNIT_ASSERT(fabs(fGLIActual - fGLIExpected) < 0.1);
  p_oTarget7->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget7->GetSpecies(), p_oTarget7->GetType()), &fGLIActual);
  CPPUNIT_ASSERT(fabs(fGLIActual - fGLIExpected) < 0.1);

  //>>>>>>>>>>>>>>>>>>>>> Timestep 4 >>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  //Kill all adult trees
  p_oAdults = p_oPop->Find("type=3");
  p_oTree = p_oAdults->NextTree();
  while (p_oTree) {
    p_oPop->KillTree(p_oTree, remove_tree);
    p_oTree = p_oAdults->NextTree();
  }

  p_oSimManager->RunSim(1);

  //Test the gap status - all are gap
  for (iX = 0; iX < iNumXCells; iX++) {
    for (iY = 0; iY < iNumYCells; iY++) {

      p_oGapGrid->GetValueOfCell(iX, iY, iGapCode, &bIsGap);
        CPPUNIT_ASSERT(bIsGap == true);
    }
  }

  //Test the GLI values of the trees - all are 100
  fGLIExpected = 100.0;
  p_oTarget1->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget1->GetSpecies(), p_oTarget1->GetType()), &fGLIActual);
  CPPUNIT_ASSERT(fabs(fGLIActual - fGLIExpected) < 0.1);
  p_oTarget2->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget2->GetSpecies(), p_oTarget2->GetType()), &fGLIActual);
  CPPUNIT_ASSERT(fabs(fGLIActual - fGLIExpected) < 0.1);
  p_oTarget3->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget3->GetSpecies(), p_oTarget3->GetType()), &fGLIActual);
  CPPUNIT_ASSERT(fabs(fGLIActual - fGLIExpected) < 0.1);
  p_oTarget4->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget4->GetSpecies(), p_oTarget4->GetType()), &fGLIActual);
  CPPUNIT_ASSERT(fabs(fGLIActual - fGLIExpected) < 0.1);
  p_oTarget5->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget5->GetSpecies(), p_oTarget5->GetType()), &fGLIActual);
  CPPUNIT_ASSERT(fabs(fGLIActual - fGLIExpected) < 0.1);
  p_oTarget6->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget6->GetSpecies(), p_oTarget6->GetType()), &fGLIActual);
  CPPUNIT_ASSERT(fabs(fGLIActual - fGLIExpected) < 0.1);
  p_oTarget7->GetValue(p_oPop->GetFloatDataCode("Light", p_oTarget7->GetSpecies(), p_oTarget7->GetType()), &fGLIActual);
  CPPUNIT_ASSERT(fabs(fGLIActual - fGLIExpected) < 0.1);


  delete p_oSimManager;
}

/////////////////////////////////////////////////////////////////////////////
//  WriteXMLFile1()
/////////////////////////////////////////////////////////////////////////////
const char* clTestGapLight::WriteXMLFile1()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>5</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>100.0</plot_lenX>"
       << "<plot_lenY>100.0</plot_lenY>"
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
       << "<behaviorName>GapLight</behaviorName>"
       << "<listPosition>1</listPosition>"
       << "<version>1</version>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<StochasticMortality2>"
       << "<mo_stochasticMortRate>"
       << "<mo_smrVal species=\"Species_1\">0</mo_smrVal>"
       << "</mo_stochasticMortRate>"
       << "</StochasticMortality2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
//  WriteXMLFile2()
/////////////////////////////////////////////////////////////////////////////
const char* clTestGapLight::WriteXMLFile2()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>5</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>100.0</plot_lenX>"
       << "<plot_lenY>100.0</plot_lenY>"
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
       << "<grid gridName=\"Gap Light\">"
       << "<ma_boolCodes>"
       << "<ma_boolCode label=\"Is Gap\">0</ma_boolCode>"
       << "</ma_boolCodes>"
       << "<ma_lengthXCells>2</ma_lengthXCells>"
       << "<ma_lengthYCells>4</ma_lengthYCells>"
       << "</grid>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>GapLight</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<StochasticMortality2>"
       << "<mo_stochasticMortRate>"
       << "<mo_smrVal species=\"Species_1\">0</mo_smrVal>"
       << "</mo_stochasticMortRate>"
       << "</StochasticMortality2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}
