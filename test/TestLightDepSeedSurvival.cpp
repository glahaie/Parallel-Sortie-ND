//---------------------------------------------------------------------------
// TestLightDepSeedSurvival.cpp
//---------------------------------------------------------------------------
#include "TestLightDepSeedSurvival.h"

#include "SimManager.h"
#include "Grid.h"
#include "TreePopulation.h"
#include "BehaviorBase.h"
#include <fstream>

/////////////////////////////////////////////////////////////////////////////
//  TestLightDepSeedSurvival()
/////////////////////////////////////////////////////////////////////////////
void clTestLightDepSeedSurvival::TestLightDepSeedSurvival() {
  clSimManager * p_oSimManager = new clSimManager(3, 3, "");

  TestNormalGLIProcessing(p_oSimManager);
  TestNormalStormLightProcessing(p_oSimManager);
  TestErrorProcessing(p_oSimManager);

  delete p_oSimManager;
}

/////////////////////////////////////////////////////////////////////////////
//  TestNormalGLIProcessing()
/////////////////////////////////////////////////////////////////////////////
void clTestLightDepSeedSurvival::TestNormalGLIProcessing(clSimManager *p_oSimManager) {
  DoNormalGLIRun1(p_oSimManager);
  DoNormalGLIRun2(p_oSimManager);
}

/////////////////////////////////////////////////////////////////////////////
//  TestNormalStormLightProcessing()
/////////////////////////////////////////////////////////////////////////////
void clTestLightDepSeedSurvival::TestNormalStormLightProcessing(clSimManager *p_oSimManager) {
  clTreePopulation * p_oPop;
  clGrid *p_oSeeds, *p_oStormLight;
  clTreeSearch *p_oAllSeedlings;
  clTree *p_oTree;
  float fValue, fX, fY, fXMin, fXMax, fYMin, fYMax;
  int *p_iNumSeedlings = new int[4], i, iLightCode;

  //Set up the run
  p_oSimManager->ReadFile(WriteXMLFile3());
  p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject("treepopulation");

  //Add the seeds to the appropriate grid cells
  p_oSeeds = p_oSimManager->GetGridObject("Dispersed Seeds");
  fValue = 100;
  p_oSeeds->SetValueOfCell(0, 0, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
  fValue = 200;
  p_oSeeds->SetValueOfCell(0, 0, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
  fValue = 300;
  p_oSeeds->SetValueOfCell(0, 0, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);

  fValue = 300;
  p_oSeeds->SetValueOfCell(7, 0, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
  fValue = 100;
  p_oSeeds->SetValueOfCell(7, 0, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
  fValue = 200;
  p_oSeeds->SetValueOfCell(7, 0, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);

  fValue = 100;
  p_oSeeds->SetValueOfCell(14, 0, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
  fValue = 200;
  p_oSeeds->SetValueOfCell(14, 0, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
  fValue = 300;
  p_oSeeds->SetValueOfCell(14, 0, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);

  fValue = 300;
  p_oSeeds->SetValueOfCell(21, 0, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
  fValue = 100;
  p_oSeeds->SetValueOfCell(21, 0, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
  fValue = 200;
  p_oSeeds->SetValueOfCell(21, 0, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);

  fValue = 100;
  p_oSeeds->SetValueOfCell(28, 0, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
  fValue = 200;
  p_oSeeds->SetValueOfCell(28, 0, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
  fValue = 300;
  p_oSeeds->SetValueOfCell(28, 0, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);

  fValue = 200;
  p_oSeeds->SetValueOfCell(35, 0, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
  fValue = 300;
  p_oSeeds->SetValueOfCell(35, 0, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
  fValue = 100;
  p_oSeeds->SetValueOfCell(35, 0, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);

  fValue = 300;
  p_oSeeds->SetValueOfCell(42, 0, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
  fValue = 100;
  p_oSeeds->SetValueOfCell(42, 0, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
  fValue = 200;
  p_oSeeds->SetValueOfCell(42, 0, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);

  fValue = 100;
  p_oSeeds->SetValueOfCell(49, 0, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
  fValue = 200;
  p_oSeeds->SetValueOfCell(49, 0, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
  fValue = 300;
  p_oSeeds->SetValueOfCell(49, 0, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);

  fValue = 200;
  p_oSeeds->SetValueOfCell(56, 0, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
  fValue = 300;
  p_oSeeds->SetValueOfCell(56, 0, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
  fValue = 100;
  p_oSeeds->SetValueOfCell(56, 0, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);

  //Set the values of the storm light grid
  p_oStormLight = p_oSimManager->GetGridObject("Storm Light");
  CPPUNIT_ASSERT(p_oStormLight);
  iLightCode = p_oStormLight->GetFloatDataCode("Light");
  CPPUNIT_ASSERT(-1 != iLightCode);
  fValue = 0;
  p_oStormLight->SetValueOfCell(0, 0, iLightCode, fValue);

  fValue = 100;
  p_oStormLight->SetValueOfCell(7, 0, iLightCode, fValue);

  fValue = 20;
  p_oStormLight->SetValueOfCell(14, 0, iLightCode, fValue);

  fValue = 90;
  p_oStormLight->SetValueOfCell(21, 0, iLightCode, fValue);

  fValue = 50;
  p_oStormLight->SetValueOfCell(28, 0, iLightCode, fValue);

  fValue = 60;
  p_oStormLight->SetValueOfCell(35, 0, iLightCode, fValue);

  fValue = 55.66;
  p_oStormLight->SetValueOfCell(42, 0, iLightCode, fValue);

  fValue = 23;
  p_oStormLight->SetValueOfCell(49, 0, iLightCode, fValue);

  fValue = 87;
  p_oStormLight->SetValueOfCell(56, 0, iLightCode, fValue);

  //Run the run - but don't let storm light go
  for (i = 0; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
    if (strcmp(p_oSimManager->GetBehaviorObject(i)->GetName(), "StormLight") != 0)
      p_oSimManager->GetBehaviorObject(i)->Action();
  }

  //Count the seedlings
  p_oAllSeedlings = p_oPop->Find("type=1");

  //Check our values for cell 0, 0
  for (i = 0; i < 4; i++) {
    p_iNumSeedlings[i] = 0;
  }
  fYMin = 0;
  fYMax = 8;
  fXMin = 0 * 8;
  fXMax = (0 + 1) * 8;
  p_oTree = p_oAllSeedlings->NextTree();
  while (p_oTree) {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
    if (fX >= fXMin && fX <= fXMax && fY >= fYMin && fY <= fYMax) {
      p_iNumSeedlings[p_oTree->GetSpecies()]++;
    }
    p_oTree = p_oAllSeedlings->NextTree();
  }
  CPPUNIT_ASSERT(0 == p_iNumSeedlings[0]);
  CPPUNIT_ASSERT(21 == p_iNumSeedlings[1] || 22 == p_iNumSeedlings[1]);
  CPPUNIT_ASSERT(29 == p_iNumSeedlings[2] || 30 == p_iNumSeedlings[2]);
  CPPUNIT_ASSERT(116 == p_iNumSeedlings[3] || 117 == p_iNumSeedlings[3]);

  //Check our values for cell 7, 0
  for (i = 0; i < 4; i++) {
    p_iNumSeedlings[i] = 0;
  }
  fXMin = 7 * 8;
  fXMax = (7 + 1) * 8;
  p_oAllSeedlings->StartOver();
  p_oTree = p_oAllSeedlings->NextTree();
  while (p_oTree) {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
    if (fX >= fXMin && fX <= fXMax && fY >= fYMin && fY <= fYMax) {
      p_iNumSeedlings[p_oTree->GetSpecies()]++;
    }
    p_oTree = p_oAllSeedlings->NextTree();
  }
  CPPUNIT_ASSERT(0 == p_iNumSeedlings[0]);
  CPPUNIT_ASSERT(246 == p_iNumSeedlings[1] || 247 == p_iNumSeedlings[1]);
  CPPUNIT_ASSERT(87 == p_iNumSeedlings[2] || 88 == p_iNumSeedlings[2]);
  CPPUNIT_ASSERT(93 == p_iNumSeedlings[3] || 94 == p_iNumSeedlings[3]);

  //Check our values for cell 14, 0
  for (i = 0; i < 4; i++) {
    p_iNumSeedlings[i] = 0;
  }
  fXMin = 14 * 8;
  fXMax = (14 + 1) * 8;
  p_oAllSeedlings->StartOver();
  p_oTree = p_oAllSeedlings->NextTree();
  while (p_oTree) {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
    if (fX >= fXMin && fX <= fXMax && fY >= fYMin && fY <= fYMax) {
      p_iNumSeedlings[p_oTree->GetSpecies()]++;
    }
    p_oTree = p_oAllSeedlings->NextTree();
  }
  CPPUNIT_ASSERT(0 == p_iNumSeedlings[0]);
  CPPUNIT_ASSERT(89 == p_iNumSeedlings[1] || 90 == p_iNumSeedlings[1]);
  CPPUNIT_ASSERT(68 == p_iNumSeedlings[2] || 69 == p_iNumSeedlings[2]);
  CPPUNIT_ASSERT(182 == p_iNumSeedlings[3] || 183 == p_iNumSeedlings[3]);

  //Check our values for cell 21, 0
  for (i = 0; i < 4; i++) {
    p_iNumSeedlings[i] = 0;
  }
  fXMin = 21 * 8;
  fXMax = (21 + 1) * 8;
  p_oAllSeedlings->StartOver();
  p_oTree = p_oAllSeedlings->NextTree();
  while (p_oTree) {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
    if (fX >= fXMin && fX <= fXMax && fY >= fYMin && fY <= fYMax) {
      p_iNumSeedlings[p_oTree->GetSpecies()]++;
    }
    p_oTree = p_oAllSeedlings->NextTree();
  }
  CPPUNIT_ASSERT(0 == p_iNumSeedlings[0]);
  CPPUNIT_ASSERT(253 == p_iNumSeedlings[1] || 254 == p_iNumSeedlings[1]);
  CPPUNIT_ASSERT(97 == p_iNumSeedlings[2] || 98 == p_iNumSeedlings[2]);
  CPPUNIT_ASSERT(117 == p_iNumSeedlings[3] || 118 == p_iNumSeedlings[3]);

  //Check our values for cell 28, 0
  for (i = 0; i < 4; i++) {
    p_iNumSeedlings[i] = 0;
  }
  fXMin = 28 * 8;
  fXMax = (28 + 1) * 8;
  p_oAllSeedlings->StartOver();
  p_oTree = p_oAllSeedlings->NextTree();
  while (p_oTree) {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
    if (fX >= fXMin && fX <= fXMax && fY >= fYMin && fY <= fYMax) {
      p_iNumSeedlings[p_oTree->GetSpecies()]++;
    }
    p_oTree = p_oAllSeedlings->NextTree();
  }
  CPPUNIT_ASSERT(0 == p_iNumSeedlings[0]);
  CPPUNIT_ASSERT(93 == p_iNumSeedlings[1] || 94 == p_iNumSeedlings[1]);
  CPPUNIT_ASSERT(127 == p_iNumSeedlings[2] || 128 == p_iNumSeedlings[2]);
  CPPUNIT_ASSERT(281 == p_iNumSeedlings[3] || 282 == p_iNumSeedlings[3]);

  //Check our values for cell 35, 0
  for (i = 0; i < 4; i++) {
    p_iNumSeedlings[i] = 0;
  }
  fXMin = 35 * 8;
  fXMax = (35 + 1) * 8;
  p_oAllSeedlings->StartOver();
  p_oTree = p_oAllSeedlings->NextTree();
  while (p_oTree) {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
    if (fX >= fXMin && fX <= fXMax && fY >= fYMin && fY <= fYMax) {
      p_iNumSeedlings[p_oTree->GetSpecies()]++;
    }
    p_oTree = p_oAllSeedlings->NextTree();
  }
  CPPUNIT_ASSERT(0 == p_iNumSeedlings[0]);
  CPPUNIT_ASSERT(182 == p_iNumSeedlings[1] || 183 == p_iNumSeedlings[1]);
  CPPUNIT_ASSERT(220 == p_iNumSeedlings[2] || 221 == p_iNumSeedlings[2]);
  CPPUNIT_ASSERT(94 == p_iNumSeedlings[3] || 95 == p_iNumSeedlings[3]);

  //Check our values for cell 42, 0
  for (i = 0; i < 4; i++) {
    p_iNumSeedlings[i] = 0;
  }
  fXMin = 42 * 8;
  fXMax = (42 + 1) * 8;
  p_oAllSeedlings->StartOver();
  p_oTree = p_oAllSeedlings->NextTree();
  while (p_oTree) {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
    if (fX >= fXMin && fX <= fXMax && fY >= fYMin && fY <= fYMax) {
      p_iNumSeedlings[p_oTree->GetSpecies()]++;
    }
    p_oTree = p_oAllSeedlings->NextTree();
  }
  CPPUNIT_ASSERT(0 == p_iNumSeedlings[0]);
  CPPUNIT_ASSERT(277 == p_iNumSeedlings[1] || 278 == p_iNumSeedlings[1]);
  CPPUNIT_ASSERT(69 == p_iNumSeedlings[2] || 70 == p_iNumSeedlings[2]);
  CPPUNIT_ASSERT(200 == p_iNumSeedlings[3]);

  //Check our values for cell 49, 0
  for (i = 0; i < 4; i++) {
    p_iNumSeedlings[i] = 0;
  }
  fXMin = 49 * 8;
  fXMax = (49 + 1) * 8;
  p_oAllSeedlings->StartOver();
  p_oTree = p_oAllSeedlings->NextTree();
  while (p_oTree) {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
    if (fX >= fXMin && fX <= fXMax && fY >= fYMin && fY <= fYMax) {
      p_iNumSeedlings[p_oTree->GetSpecies()]++;
    }
    p_oTree = p_oAllSeedlings->NextTree();
  }
  CPPUNIT_ASSERT(0 == p_iNumSeedlings[0]);
  CPPUNIT_ASSERT(100 == p_iNumSeedlings[1]);
  CPPUNIT_ASSERT(74 == p_iNumSeedlings[2] || 75 == p_iNumSeedlings[2]);
  CPPUNIT_ASSERT(192 == p_iNumSeedlings[3] || 193 == p_iNumSeedlings[3]);

  //Check our values for cell 56, 0
  for (i = 0; i < 4; i++) {
    p_iNumSeedlings[i] = 0;
  }
  fXMin = 56 * 8;
  fXMax = (56 + 1) * 8;
  p_oAllSeedlings->StartOver();
  p_oTree = p_oAllSeedlings->NextTree();
  while (p_oTree) {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
    if (fX >= fXMin && fX <= fXMax && fY >= fYMin && fY <= fYMax) {
      p_iNumSeedlings[p_oTree->GetSpecies()]++;
    }
    p_oTree = p_oAllSeedlings->NextTree();
  }
  CPPUNIT_ASSERT(0 == p_iNumSeedlings[0]);
  CPPUNIT_ASSERT(170 == p_iNumSeedlings[1] || 171 == p_iNumSeedlings[1]);
  CPPUNIT_ASSERT(300 == p_iNumSeedlings[2]);
  CPPUNIT_ASSERT(62 == p_iNumSeedlings[3] || 63 == p_iNumSeedlings[3]);

  //Check our values for cell 1, 0
  for (i = 0; i < 4; i++) {
    p_iNumSeedlings[i] = 0;
  }
  fXMin = 1 * 8;
  fXMax = (1 + 1) * 8;
  p_oAllSeedlings->StartOver();
  p_oTree = p_oAllSeedlings->NextTree();
  while (p_oTree) {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
    if (fX >= fXMin && fX <= fXMax && fY >= fYMin && fY <= fYMax) {
      p_iNumSeedlings[p_oTree->GetSpecies()]++;
    }
    p_oTree = p_oAllSeedlings->NextTree();
  }
  CPPUNIT_ASSERT(0 == p_iNumSeedlings[0]);
  CPPUNIT_ASSERT(0 == p_iNumSeedlings[1]);
  CPPUNIT_ASSERT(0 == p_iNumSeedlings[2]);
  CPPUNIT_ASSERT(0 == p_iNumSeedlings[3]);

  delete[] p_iNumSeedlings;
}

/////////////////////////////////////////////////////////////////////////////
//  DoNormalGLIRun1()
/////////////////////////////////////////////////////////////////////////////
void clTestLightDepSeedSurvival::DoNormalGLIRun1(clSimManager *p_oSimManager) {
  clTreePopulation * p_oPop;
  clGrid *p_oSeeds;
  clTreeSearch *p_oAllSeedlings;
  clTree *p_oTree;
  float fValue, fX, fY, fXMin, fXMax, fYMin, fYMax;
  int *p_iNumSeedlings = new int[4], i, iDamage;

  //Set up the run
  p_oSimManager->ReadFile(WriteXMLFile1());
  p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject("treepopulation");

  //Add in our tree neighbors and set the damage level for each
  iDamage = 0;
  p_oTree = p_oPop->CreateTree(4, 4, 3, clTreePopulation::adult, 8);
  p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg",
                                                  p_oTree->GetSpecies(),
                                                  p_oTree->GetType()),
                           iDamage);

  iDamage = 0;
  p_oTree = p_oPop->CreateTree(116, 4, 1, clTreePopulation::adult, 8);
  p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg",
                                              p_oTree->GetSpecies(),
                                              p_oTree->GetType()),
                           iDamage);

  iDamage = 2000;
  p_oTree = p_oPop->CreateTree(168, 2, 1, clTreePopulation::adult, 45);
  p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg",
                                                  p_oTree->GetSpecies(),
                                                  p_oTree->GetType()),
                           iDamage);

  iDamage = 1000;
  p_oTree = p_oPop->CreateTree(228, 4, 2, clTreePopulation::adult, 8);
  p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg",
                                                  p_oTree->GetSpecies(),
                                                  p_oTree->GetType()),
                           iDamage);

  iDamage = 1000;
  p_oTree = p_oPop->CreateTree(284, 4, 3, clTreePopulation::adult, 8);
  p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg",
                                                  p_oTree->GetSpecies(),
                                                  p_oTree->GetType()),
                           iDamage);

  iDamage = 2000;
  p_oTree = p_oPop->CreateTree(340, 4, 3, clTreePopulation::adult, 8);
  p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg",
                                                  p_oTree->GetSpecies(),
                                                  p_oTree->GetType()),
                           iDamage);

  iDamage = 1000;
  p_oTree = p_oPop->CreateTree(396, 4, 1, clTreePopulation::adult, 8);
  p_oTree->SetValue(p_oPop->GetIntDataCode("stm_dmg",
                                                  p_oTree->GetSpecies(),
                                                  p_oTree->GetType()),
                           iDamage);

  //Tree with no storm damage applied
  p_oTree = p_oPop->CreateTree(452, 4, 4, clTreePopulation::adult, 8);

  //Add the seeds to the appropriate grid cells
  p_oSeeds = p_oSimManager->GetGridObject("Dispersed Seeds");
  fValue = 100;
  p_oSeeds->SetValueOfCell(0, 0, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
  fValue = 200;
  p_oSeeds->SetValueOfCell(0, 0, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
  fValue = 300;
  p_oSeeds->SetValueOfCell(0, 0, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);

  fValue = 300;
  p_oSeeds->SetValueOfCell(7, 0, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
  fValue = 100;
  p_oSeeds->SetValueOfCell(7, 0, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
  fValue = 200;
  p_oSeeds->SetValueOfCell(7, 0, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);

  fValue = 100;
  p_oSeeds->SetValueOfCell(14, 0, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
  fValue = 200;
  p_oSeeds->SetValueOfCell(14, 0, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
  fValue = 300;
  p_oSeeds->SetValueOfCell(14, 0, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);

  fValue = 300;
  p_oSeeds->SetValueOfCell(21, 0, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
  fValue = 100;
  p_oSeeds->SetValueOfCell(21, 0, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
  fValue = 200;
  p_oSeeds->SetValueOfCell(21, 0, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);

  fValue = 100;
  p_oSeeds->SetValueOfCell(28, 0, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
  fValue = 200;
  p_oSeeds->SetValueOfCell(28, 0, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
  fValue = 300;
  p_oSeeds->SetValueOfCell(28, 0, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);

  fValue = 200;
  p_oSeeds->SetValueOfCell(35, 0, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
  fValue = 300;
  p_oSeeds->SetValueOfCell(35, 0, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
  fValue = 100;
  p_oSeeds->SetValueOfCell(35, 0, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);

  fValue = 300;
  p_oSeeds->SetValueOfCell(42, 0, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
  fValue = 100;
  p_oSeeds->SetValueOfCell(42, 0, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
  fValue = 200;
  p_oSeeds->SetValueOfCell(42, 0, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);

  fValue = 100;
  p_oSeeds->SetValueOfCell(49, 0, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
  fValue = 200;
  p_oSeeds->SetValueOfCell(49, 0, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
  fValue = 300;
  p_oSeeds->SetValueOfCell(49, 0, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);

  fValue = 200;
  p_oSeeds->SetValueOfCell(56, 0, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
  fValue = 300;
  p_oSeeds->SetValueOfCell(56, 0, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
  fValue = 100;
  p_oSeeds->SetValueOfCell(56, 0, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);

  //Run the run
  p_oSimManager->RunSim(1);

  //Count the seedlings
  p_oAllSeedlings = p_oPop->Find("type=1");

  //Check our values for cell 0, 0
  for (i = 0; i < 4; i++) {
    p_iNumSeedlings[i] = 0;
  }
  fYMin = 0;
  fYMax = 8;
  fXMin = 0 * 8;
  fXMax = (0 + 1) * 8;
  p_oTree = p_oAllSeedlings->NextTree();
  while (p_oTree) {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
    if (fX >= fXMin && fX <= fXMax && fY >= fYMin && fY <= fYMax) {
      p_iNumSeedlings[p_oTree->GetSpecies()]++;
    }
    p_oTree = p_oAllSeedlings->NextTree();
  }
  CPPUNIT_ASSERT(0 == p_iNumSeedlings[0]);
  CPPUNIT_ASSERT(21 == p_iNumSeedlings[1] || 22 == p_iNumSeedlings[1]);
  CPPUNIT_ASSERT(29 == p_iNumSeedlings[2] || 30 == p_iNumSeedlings[2]);
  CPPUNIT_ASSERT(116 == p_iNumSeedlings[3] || 117 == p_iNumSeedlings[3]);

  //Check our values for cell 7, 0
  for (i = 0; i < 4; i++) {
    p_iNumSeedlings[i] = 0;
  }
  fXMin = 7 * 8;
  fXMax = (7 + 1) * 8;
  p_oAllSeedlings->StartOver();
  p_oTree = p_oAllSeedlings->NextTree();
  while (p_oTree) {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
    if (fX >= fXMin && fX <= fXMax && fY >= fYMin && fY <= fYMax) {
      p_iNumSeedlings[p_oTree->GetSpecies()]++;
    }
    p_oTree = p_oAllSeedlings->NextTree();
  }
  CPPUNIT_ASSERT(0 == p_iNumSeedlings[0]);
  CPPUNIT_ASSERT(246 == p_iNumSeedlings[1] || 247 == p_iNumSeedlings[1]);
  CPPUNIT_ASSERT(87 == p_iNumSeedlings[2] || 88 == p_iNumSeedlings[2]);
  CPPUNIT_ASSERT(93 == p_iNumSeedlings[3] || 94 == p_iNumSeedlings[3]);

  //Check our values for cell 14, 0
  for (i = 0; i < 4; i++) {
    p_iNumSeedlings[i] = 0;
  }
  fXMin = 14 * 8;
  fXMax = (14 + 1) * 8;
  p_oAllSeedlings->StartOver();
  p_oTree = p_oAllSeedlings->NextTree();
  while (p_oTree) {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
    if (fX >= fXMin && fX <= fXMax && fY >= fYMin && fY <= fYMax) {
      p_iNumSeedlings[p_oTree->GetSpecies()]++;
    }
    p_oTree = p_oAllSeedlings->NextTree();
  }
  CPPUNIT_ASSERT(0 == p_iNumSeedlings[0]);
  CPPUNIT_ASSERT(89 == p_iNumSeedlings[1] || 90 == p_iNumSeedlings[1]);
  CPPUNIT_ASSERT(68 == p_iNumSeedlings[2] || 69 == p_iNumSeedlings[2]);
  CPPUNIT_ASSERT(182 == p_iNumSeedlings[3] || 183 == p_iNumSeedlings[3]);

  //Check our values for cell 21, 0
  for (i = 0; i < 4; i++) {
    p_iNumSeedlings[i] = 0;
  }
  fXMin = 21 * 8;
  fXMax = (21 + 1) * 8;
  p_oAllSeedlings->StartOver();
  p_oTree = p_oAllSeedlings->NextTree();
  while (p_oTree) {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
    if (fX >= fXMin && fX <= fXMax && fY >= fYMin && fY <= fYMax) {
      p_iNumSeedlings[p_oTree->GetSpecies()]++;
    }
    p_oTree = p_oAllSeedlings->NextTree();
  }
  CPPUNIT_ASSERT(0 == p_iNumSeedlings[0]);
  CPPUNIT_ASSERT(250 == p_iNumSeedlings[1] || 251 == p_iNumSeedlings[1]);
  CPPUNIT_ASSERT(92 == p_iNumSeedlings[2] || 93 == p_iNumSeedlings[2]);
  CPPUNIT_ASSERT(106 == p_iNumSeedlings[3] || 107 == p_iNumSeedlings[3]);

  //Check our values for cell 28, 0
  for (i = 0; i < 4; i++) {
    p_iNumSeedlings[i] = 0;
  }
  fXMin = 28 * 8;
  fXMax = (28 + 1) * 8;
  p_oAllSeedlings->StartOver();
  p_oTree = p_oAllSeedlings->NextTree();
  while (p_oTree) {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
    if (fX >= fXMin && fX <= fXMax && fY >= fYMin && fY <= fYMax) {
      p_iNumSeedlings[p_oTree->GetSpecies()]++;
    }
    p_oTree = p_oAllSeedlings->NextTree();
  }
  CPPUNIT_ASSERT(0 == p_iNumSeedlings[0]);
  CPPUNIT_ASSERT(93 == p_iNumSeedlings[1] || 94 == p_iNumSeedlings[1]);
  CPPUNIT_ASSERT(127 == p_iNumSeedlings[2] || 128 == p_iNumSeedlings[2]);
  CPPUNIT_ASSERT(281 == p_iNumSeedlings[3] || 282 == p_iNumSeedlings[3]);

  //Check our values for cell 35, 0
  for (i = 0; i < 4; i++) {
    p_iNumSeedlings[i] = 0;
  }
  fXMin = 35 * 8;
  fXMax = (35 + 1) * 8;
  p_oAllSeedlings->StartOver();
  p_oTree = p_oAllSeedlings->NextTree();
  while (p_oTree) {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
    if (fX >= fXMin && fX <= fXMax && fY >= fYMin && fY <= fYMax) {
      p_iNumSeedlings[p_oTree->GetSpecies()]++;
    }
    p_oTree = p_oAllSeedlings->NextTree();
  }
  CPPUNIT_ASSERT(0 == p_iNumSeedlings[0]);
  CPPUNIT_ASSERT(182 == p_iNumSeedlings[1] || 183 == p_iNumSeedlings[1]);
  CPPUNIT_ASSERT(220 == p_iNumSeedlings[2] || 221 == p_iNumSeedlings[2]);
  CPPUNIT_ASSERT(94 == p_iNumSeedlings[3] || 95 == p_iNumSeedlings[3]);

  //Check our values for cell 42, 0
  for (i = 0; i < 4; i++) {
    p_iNumSeedlings[i] = 0;
  }
  fXMin = 42 * 8;
  fXMax = (42 + 1) * 8;
  p_oAllSeedlings->StartOver();
  p_oTree = p_oAllSeedlings->NextTree();
  while (p_oTree) {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
    if (fX >= fXMin && fX <= fXMax && fY >= fYMin && fY <= fYMax) {
      p_iNumSeedlings[p_oTree->GetSpecies()]++;
    }
    p_oTree = p_oAllSeedlings->NextTree();
  }
  CPPUNIT_ASSERT(0 == p_iNumSeedlings[0]);
  CPPUNIT_ASSERT(277 == p_iNumSeedlings[1] || 278 == p_iNumSeedlings[1]);
  CPPUNIT_ASSERT(69 == p_iNumSeedlings[2] || 70 == p_iNumSeedlings[2]);
  CPPUNIT_ASSERT(200 == p_iNumSeedlings[3]);

  //Check our values for cell 49, 0
  for (i = 0; i < 4; i++) {
    p_iNumSeedlings[i] = 0;
  }
  fXMin = 49 * 8;
  fXMax = (49 + 1) * 8;
  p_oAllSeedlings->StartOver();
  p_oTree = p_oAllSeedlings->NextTree();
  while (p_oTree) {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
    if (fX >= fXMin && fX <= fXMax && fY >= fYMin && fY <= fYMax) {
      p_iNumSeedlings[p_oTree->GetSpecies()]++;
    }
    p_oTree = p_oAllSeedlings->NextTree();
  }
  CPPUNIT_ASSERT(0 == p_iNumSeedlings[0]);
  CPPUNIT_ASSERT(100 == p_iNumSeedlings[1]);
  CPPUNIT_ASSERT(74 == p_iNumSeedlings[2] || 75 == p_iNumSeedlings[2]);
  CPPUNIT_ASSERT(192 == p_iNumSeedlings[3] || 193 == p_iNumSeedlings[3]);

  //Check our values for cell 56, 0
  for (i = 0; i < 4; i++) {
    p_iNumSeedlings[i] = 0;
  }
  fXMin = 56 * 8;
  fXMax = (56 + 1) * 8;
  p_oAllSeedlings->StartOver();
  p_oTree = p_oAllSeedlings->NextTree();
  while (p_oTree) {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
    if (fX >= fXMin && fX <= fXMax && fY >= fYMin && fY <= fYMax) {
      p_iNumSeedlings[p_oTree->GetSpecies()]++;
    }
    p_oTree = p_oAllSeedlings->NextTree();
  }
  CPPUNIT_ASSERT(0 == p_iNumSeedlings[0]);
  CPPUNIT_ASSERT(170 == p_iNumSeedlings[1] || 171 == p_iNumSeedlings[1]);
  CPPUNIT_ASSERT(300 == p_iNumSeedlings[2]);
  CPPUNIT_ASSERT(62 == p_iNumSeedlings[3] || 63 == p_iNumSeedlings[3]);

  //Check our values for cell 1, 0
  for (i = 0; i < 4; i++) {
    p_iNumSeedlings[i] = 0;
  }
  fXMin = 1 * 8;
  fXMax = (1 + 1) * 8;
  p_oAllSeedlings->StartOver();
  p_oTree = p_oAllSeedlings->NextTree();
  while (p_oTree) {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
    if (fX >= fXMin && fX <= fXMax && fY >= fYMin && fY <= fYMax) {
      p_iNumSeedlings[p_oTree->GetSpecies()]++;
    }
    p_oTree = p_oAllSeedlings->NextTree();
  }
  CPPUNIT_ASSERT(0 == p_iNumSeedlings[0]);
  CPPUNIT_ASSERT(0 == p_iNumSeedlings[1]);
  CPPUNIT_ASSERT(0 == p_iNumSeedlings[2]);
  CPPUNIT_ASSERT(0 == p_iNumSeedlings[3]);

  delete[] p_iNumSeedlings;
}

/////////////////////////////////////////////////////////////////////////////
//  DoNormalGLIRun2()
/////////////////////////////////////////////////////////////////////////////
void clTestLightDepSeedSurvival::DoNormalGLIRun2(clSimManager *p_oSimManager) {
  clTreePopulation * p_oPop;
  clGrid *p_oSeeds;
  clTreeSearch *p_oAllSeedlings;
  clTree *p_oTree;
  float fValue, fX, fY, fXMin, fXMax, fYMin, fYMax;
  int *p_iNumSeedlings = new int[4], i;

  //Set up the run
  p_oSimManager->ReadFile(WriteXMLFile2());
  p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject("treepopulation");

  //Add in our tree neighbors
  p_oTree = p_oPop->CreateTree(4, 4, 3, clTreePopulation::adult, 8);
  p_oTree = p_oPop->CreateTree(116, 4, 1, clTreePopulation::adult, 8);
  p_oTree = p_oPop->CreateTree(168, 2, 1, clTreePopulation::adult, 45);
  p_oTree = p_oPop->CreateTree(228, 4, 2, clTreePopulation::adult, 8);
  p_oTree = p_oPop->CreateTree(284, 4, 3, clTreePopulation::adult, 8);
  p_oTree = p_oPop->CreateTree(340, 4, 3, clTreePopulation::adult, 8);
  p_oTree = p_oPop->CreateTree(396, 4, 1, clTreePopulation::adult, 8);
  p_oTree = p_oPop->CreateTree(452, 4, 2, clTreePopulation::adult, 8);
  p_oTree = p_oPop->CreateTree(174, 5, 1, clTreePopulation::snag, 20);

  //Add the seeds to the appropriate grid cells
  p_oSeeds = p_oSimManager->GetGridObject("Dispersed Seeds");
  fValue = 100;
  p_oSeeds->SetValueOfCell(0, 0, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
  fValue = 200;
  p_oSeeds->SetValueOfCell(0, 0, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
  fValue = 300;
  p_oSeeds->SetValueOfCell(0, 0, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);

  fValue = 300;
  p_oSeeds->SetValueOfCell(7, 0, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
  fValue = 100;
  p_oSeeds->SetValueOfCell(7, 0, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
  fValue = 200;
  p_oSeeds->SetValueOfCell(7, 0, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);

  fValue = 100;
  p_oSeeds->SetValueOfCell(14, 0, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
  fValue = 200;
  p_oSeeds->SetValueOfCell(14, 0, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
  fValue = 300;
  p_oSeeds->SetValueOfCell(14, 0, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);

  fValue = 300;
  p_oSeeds->SetValueOfCell(21, 0, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
  fValue = 100;
  p_oSeeds->SetValueOfCell(21, 0, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
  fValue = 200;
  p_oSeeds->SetValueOfCell(21, 0, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);

  fValue = 100;
  p_oSeeds->SetValueOfCell(28, 0, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
  fValue = 200;
  p_oSeeds->SetValueOfCell(28, 0, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
  fValue = 300;
  p_oSeeds->SetValueOfCell(28, 0, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);

  fValue = 200;
  p_oSeeds->SetValueOfCell(35, 0, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
  fValue = 300;
  p_oSeeds->SetValueOfCell(35, 0, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
  fValue = 100;
  p_oSeeds->SetValueOfCell(35, 0, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);

  fValue = 300;
  p_oSeeds->SetValueOfCell(42, 0, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
  fValue = 100;
  p_oSeeds->SetValueOfCell(42, 0, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
  fValue = 200;
  p_oSeeds->SetValueOfCell(42, 0, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);

  fValue = 100;
  p_oSeeds->SetValueOfCell(49, 0, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
  fValue = 200;
  p_oSeeds->SetValueOfCell(49, 0, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
  fValue = 300;
  p_oSeeds->SetValueOfCell(49, 0, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);

  fValue = 200;
  p_oSeeds->SetValueOfCell(56, 0, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
  fValue = 300;
  p_oSeeds->SetValueOfCell(56, 0, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
  fValue = 100;
  p_oSeeds->SetValueOfCell(56, 0, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);

  //Run the run
  p_oSimManager->RunSim(1);

  //Count the seedlings
  p_oAllSeedlings = p_oPop->Find("type=1");

  //Check our values for cell 0, 0
  for (i = 0; i < 4; i++) {
    p_iNumSeedlings[i] = 0;
  }
  fYMin = 0;
  fYMax = 8;
  fXMin = 0 * 8;
  fXMax = (0 + 1) * 8;
  p_oTree = p_oAllSeedlings->NextTree();
  while (p_oTree) {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
    if (fX >= fXMin && fX <= fXMax && fY >= fYMin && fY <= fYMax) {
      p_iNumSeedlings[p_oTree->GetSpecies()]++;
    }
    p_oTree = p_oAllSeedlings->NextTree();
  }
  CPPUNIT_ASSERT(0 == p_iNumSeedlings[0]);
  CPPUNIT_ASSERT(93 == p_iNumSeedlings[1] || 94 == p_iNumSeedlings[1]);
  CPPUNIT_ASSERT(127 == p_iNumSeedlings[2] || 128 == p_iNumSeedlings[2]);
  CPPUNIT_ASSERT(281 == p_iNumSeedlings[3] || 282 == p_iNumSeedlings[3]);

  //Check our values for cell 7, 0
  for (i = 0; i < 4; i++) {
    p_iNumSeedlings[i] = 0;
  }
  fXMin = 7 * 8;
  fXMax = (7 + 1) * 8;
  p_oAllSeedlings->StartOver();
  p_oTree = p_oAllSeedlings->NextTree();
  while (p_oTree) {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
    if (fX >= fXMin && fX <= fXMax && fY >= fYMin && fY <= fYMax) {
      p_iNumSeedlings[p_oTree->GetSpecies()]++;
    }
    p_oTree = p_oAllSeedlings->NextTree();
  }
  CPPUNIT_ASSERT(0 == p_iNumSeedlings[0]);
  CPPUNIT_ASSERT(246 == p_iNumSeedlings[1] || 247 == p_iNumSeedlings[1]);
  CPPUNIT_ASSERT(87 == p_iNumSeedlings[2] || 88 == p_iNumSeedlings[2]);
  CPPUNIT_ASSERT(93 == p_iNumSeedlings[3] || 94 == p_iNumSeedlings[3]);

  //Check our values for cell 14, 0
  for (i = 0; i < 4; i++) {
    p_iNumSeedlings[i] = 0;
  }
  fXMin = 14 * 8;
  fXMax = (14 + 1) * 8;
  p_oAllSeedlings->StartOver();
  p_oTree = p_oAllSeedlings->NextTree();
  while (p_oTree) {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
    if (fX >= fXMin && fX <= fXMax && fY >= fYMin && fY <= fYMax) {
      p_iNumSeedlings[p_oTree->GetSpecies()]++;
    }
    p_oTree = p_oAllSeedlings->NextTree();
  }
  CPPUNIT_ASSERT(0 == p_iNumSeedlings[0]);
  CPPUNIT_ASSERT(89 == p_iNumSeedlings[1] || 90 == p_iNumSeedlings[1]);
  CPPUNIT_ASSERT(68 == p_iNumSeedlings[2] || 69 == p_iNumSeedlings[2]);
  CPPUNIT_ASSERT(182 == p_iNumSeedlings[3] || 183 == p_iNumSeedlings[3]);

  //Check our values for cell 21, 0
  for (i = 0; i < 4; i++) {
    p_iNumSeedlings[i] = 0;
  }
  fXMin = 21 * 8;
  fXMax = (21 + 1) * 8;
  p_oAllSeedlings->StartOver();
  p_oTree = p_oAllSeedlings->NextTree();
  while (p_oTree) {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
    if (fX >= fXMin && fX <= fXMax && fY >= fYMin && fY <= fYMax) {
      p_iNumSeedlings[p_oTree->GetSpecies()]++;
    }
    p_oTree = p_oAllSeedlings->NextTree();
  }
  CPPUNIT_ASSERT(0 == p_iNumSeedlings[0]);
  CPPUNIT_ASSERT(265 == p_iNumSeedlings[1] || 266 == p_iNumSeedlings[1]);
  CPPUNIT_ASSERT(86 == p_iNumSeedlings[2] || 87 == p_iNumSeedlings[2]);
  CPPUNIT_ASSERT(158 == p_iNumSeedlings[3] || 159 == p_iNumSeedlings[3]);

  //Check our values for cell 28, 0
  for (i = 0; i < 4; i++) {
    p_iNumSeedlings[i] = 0;
  }
  fXMin = 28 * 8;
  fXMax = (28 + 1) * 8;
  p_oAllSeedlings->StartOver();
  p_oTree = p_oAllSeedlings->NextTree();
  while (p_oTree) {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
    if (fX >= fXMin && fX <= fXMax && fY >= fYMin && fY <= fYMax) {
      p_iNumSeedlings[p_oTree->GetSpecies()]++;
    }
    p_oTree = p_oAllSeedlings->NextTree();
  }
  CPPUNIT_ASSERT(0 == p_iNumSeedlings[0]);
  CPPUNIT_ASSERT(85 == p_iNumSeedlings[1] || 86 == p_iNumSeedlings[1]);
  CPPUNIT_ASSERT(200 == p_iNumSeedlings[2]);
  CPPUNIT_ASSERT(187 == p_iNumSeedlings[3] || 188 == p_iNumSeedlings[3]);

  //Check our values for cell 35, 0
  for (i = 0; i < 4; i++) {
    p_iNumSeedlings[i] = 0;
  }
  fXMin = 35 * 8;
  fXMax = (35 + 1) * 8;
  p_oAllSeedlings->StartOver();
  p_oTree = p_oAllSeedlings->NextTree();
  while (p_oTree) {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
    if (fX >= fXMin && fX <= fXMax && fY >= fYMin && fY <= fYMax) {
      p_iNumSeedlings[p_oTree->GetSpecies()]++;
    }
    p_oTree = p_oAllSeedlings->NextTree();
  }
  CPPUNIT_ASSERT(0 == p_iNumSeedlings[0]);
  CPPUNIT_ASSERT(187 == p_iNumSeedlings[1] || 188 == p_iNumSeedlings[1]);
  CPPUNIT_ASSERT(191 == p_iNumSeedlings[2] || 192 == p_iNumSeedlings[2]);
  CPPUNIT_ASSERT(93 == p_iNumSeedlings[3] || 94 == p_iNumSeedlings[3]);

  //Check our values for cell 42, 0
  for (i = 0; i < 4; i++) {
    p_iNumSeedlings[i] = 0;
  }
  fXMin = 42 * 8;
  fXMax = (42 + 1) * 8;
  p_oAllSeedlings->StartOver();
  p_oTree = p_oAllSeedlings->NextTree();
  while (p_oTree) {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
    if (fX >= fXMin && fX <= fXMax && fY >= fYMin && fY <= fYMax) {
      p_iNumSeedlings[p_oTree->GetSpecies()]++;
    }
    p_oTree = p_oAllSeedlings->NextTree();
  }
  CPPUNIT_ASSERT(0 == p_iNumSeedlings[0]);
  CPPUNIT_ASSERT(281 == p_iNumSeedlings[1] || 282 == p_iNumSeedlings[1]);
  CPPUNIT_ASSERT(63 == p_iNumSeedlings[2] || 64 == p_iNumSeedlings[2]);
  CPPUNIT_ASSERT(187 == p_iNumSeedlings[3] || 188 == p_iNumSeedlings[3]);

  //Check our values for cell 49, 0
  for (i = 0; i < 4; i++) {
    p_iNumSeedlings[i] = 0;
  }
  fXMin = 49 * 8;
  fXMax = (49 + 1) * 8;
  p_oAllSeedlings->StartOver();
  p_oTree = p_oAllSeedlings->NextTree();
  while (p_oTree) {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
    if (fX >= fXMin && fX <= fXMax && fY >= fYMin && fY <= fYMax) {
      p_iNumSeedlings[p_oTree->GetSpecies()]++;
    }
    p_oTree = p_oAllSeedlings->NextTree();
  }
  CPPUNIT_ASSERT(0 == p_iNumSeedlings[0]);
  CPPUNIT_ASSERT(89 == p_iNumSeedlings[1] || 90 == p_iNumSeedlings[1]);
  CPPUNIT_ASSERT(68 == p_iNumSeedlings[2] || 69 == p_iNumSeedlings[2]);
  CPPUNIT_ASSERT(182 == p_iNumSeedlings[3] || 183 == p_iNumSeedlings[3]);

  //Check our values for cell 56, 0
  for (i = 0; i < 4; i++) {
    p_iNumSeedlings[i] = 0;
  }
  fXMin = 56 * 8;
  fXMax = (56 + 1) * 8;
  p_oAllSeedlings->StartOver();
  p_oTree = p_oAllSeedlings->NextTree();
  while (p_oTree) {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
    if (fX >= fXMin && fX <= fXMax && fY >= fYMin && fY <= fYMax) {
      p_iNumSeedlings[p_oTree->GetSpecies()]++;
    }
    p_oTree = p_oAllSeedlings->NextTree();
  }
  CPPUNIT_ASSERT(0 == p_iNumSeedlings[0]);
  CPPUNIT_ASSERT(170 == p_iNumSeedlings[1] || 171 == p_iNumSeedlings[1]);
  CPPUNIT_ASSERT(300 == p_iNumSeedlings[2] || 299 == p_iNumSeedlings[2]);
  CPPUNIT_ASSERT(62 == p_iNumSeedlings[3] || 63 == p_iNumSeedlings[3]);

  //Check our values for cell 1, 0
  for (i = 0; i < 4; i++) {
    p_iNumSeedlings[i] = 0;
  }
  fXMin = 1 * 8;
  fXMax = (1 + 1) * 8;
  p_oAllSeedlings->StartOver();
  p_oTree = p_oAllSeedlings->NextTree();
  while (p_oTree) {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
    if (fX >= fXMin && fX <= fXMax && fY >= fYMin && fY <= fYMax) {
      p_iNumSeedlings[p_oTree->GetSpecies()]++;
    }
    p_oTree = p_oAllSeedlings->NextTree();
  }
  CPPUNIT_ASSERT(0 == p_iNumSeedlings[0]);
  CPPUNIT_ASSERT(0 == p_iNumSeedlings[1]);
  CPPUNIT_ASSERT(0 == p_iNumSeedlings[2]);
  CPPUNIT_ASSERT(0 == p_iNumSeedlings[3]);

  delete[] p_iNumSeedlings;
}

////////////////////////////////////////////////////////////////////////////
//  TestErrorProcessing()
////////////////////////////////////////////////////////////////////////////
void clTestLightDepSeedSurvival::TestErrorProcessing(clSimManager *p_oSimManager) {

  try
  {
    p_oSimManager->ReadFile(WriteXMLErrorFile1());
    CppUnit::Asserter::fail("TestLightDepSeedSurvival error processing didn't catch error for WriteXMLErrorFile1.");
  }
  catch (modelErr& err)
  {
    if (strstr(err.cFunction, "clLightDepSeedSurvival::GetParameterFileData") == NULL)
    {
      CppUnit::Asserter::fail("TestLightDepSeedSurvival error processing caught wrong error for WriteXMLErrorFile1.");
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteXMLErrorFile2());
    CppUnit::Asserter::fail("TestLightDepSeedSurvival error processing didn't catch error for WriteXMLErrorFile2.");
  }
  catch (modelErr& err)
  {
    if (strstr(err.cFunction, "clLightDepSeedSurvival::GetParameterFileData") == NULL)
    {
      CppUnit::Asserter::fail("TestLightDepSeedSurvival error processing caught wrong error for WriteXMLErrorFile2.");
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteXMLErrorFile3());
    CppUnit::Asserter::fail("TestLightDepSeedSurvival error processing didn't catch error for WriteXMLErrorFile3.");
  }
  catch (modelErr& err)
  {
    if (strstr(err.cFunction, "clLightDepSeedSurvival::GetParameterFileData") == NULL)
    {
      CppUnit::Asserter::fail("TestLightDepSeedSurvival error processing caught wrong error for WriteXMLErrorFile3.");
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteXMLErrorFile4());
    CppUnit::Asserter::fail("TestLightDepSeedSurvival error processing didn't catch error for WriteXMLErrorFile4.");
  }
  catch (modelErr& err)
  {
    if (strstr(err.cFunction, "clLightDepSeedSurvival::SetupGrid") == NULL)
    {
      CppUnit::Asserter::fail("TestLightDepSeedSurvival error processing caught wrong error for WriteXMLErrorFile4.");
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteXMLErrorFile5());
    CppUnit::Asserter::fail("TestLightDepSeedSurvival error processing didn't catch error for WriteXMLErrorFile5.");
  }
  catch (modelErr& err)
  {
    if (strstr(err.cFunction, "clLightDepSeedSurvival::GetParameterFileData") == NULL)
    {
      CppUnit::Asserter::fail("TestLightDepSeedSurvival error processing caught wrong error for WriteXMLErrorFile5.");
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteXMLErrorFile6());
    CppUnit::Asserter::fail("TestLightDepSeedSurvival error processing didn't catch error for WriteXMLErrorFile6.");
  }
  catch (modelErr& err)
  {
    if (strstr(err.cFunction, "clLightDepSeedSurvival::GetParameterFileData") == NULL)
    {
      CppUnit::Asserter::fail("TestLightDepSeedSurvival error processing caught wrong error for WriteXMLErrorFile6.");
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteXMLErrorFile7());
    CppUnit::Asserter::fail("TestLightDepSeedSurvival error processing didn't catch error for WriteXMLErrorFile7.");
  }
  catch (modelErr& err)
  {
    if (strstr(err.cFunction, "clLightDepSeedSurvival::SetupGrid") == NULL)
    {
      CppUnit::Asserter::fail("TestLightDepSeedSurvival error processing caught wrong error for WriteXMLErrorFile7.");
    }
    ;
  }
}

////////////////////////////////////////////////////////////////////////////
//  WriteXMLFile1()
////////////////////////////////////////////////////////////////////////////
const char* clTestLightDepSeedSurvival::WriteXMLFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  WriteCommonStuff(oOut);

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
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>NonSpatialDisperse</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>4</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>LightDependentSeedSurvival</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>5</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Establishment</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>6</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_3\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<Storm1>"
       << "<st_s1ReturnInterval>1000</st_s1ReturnInterval>"
       << "<st_s2ReturnInterval>1000</st_s2ReturnInterval>"
       << "<st_s3ReturnInterval>1000</st_s3ReturnInterval>"
       << "<st_s4ReturnInterval>1000</st_s4ReturnInterval>"
       << "<st_s5ReturnInterval>1000</st_s5ReturnInterval>"
       << "<st_s6ReturnInterval>1000</st_s6ReturnInterval>"
       << "<st_s7ReturnInterval>1000</st_s7ReturnInterval>"
       << "<st_s8ReturnInterval>1000</st_s8ReturnInterval>"
       << "<st_s9ReturnInterval>1000</st_s9ReturnInterval>"
       << "<st_s10ReturnInterval>1000</st_s10ReturnInterval>"
       << "<st_susceptibility>1</st_susceptibility>"
       << "<st_stochasticity>0</st_stochasticity>"
       << "<st_stmSSTPeriod>1</st_stmSSTPeriod>"
       << "<st_stmSineD>0</st_stmSineD>"
       << "<st_stmSineF>1</st_stmSineF>"
       << "<st_stmSineG>1</st_stmSineG>"
       << "<st_stmTrendSlopeM>0</st_stmTrendSlopeM>"
       << "<st_stmTrendInterceptI>1</st_stmTrendInterceptI>"
       << "</Storm1>"
       << "<StormDamageApplier2>"
       << "<st_minDBH>"
       << "<st_mdVal species=\"Species_1\">5</st_mdVal>"
       << "<st_mdVal species=\"Species_2\">6</st_mdVal>"
       << "<st_mdVal species=\"Species_3\">5</st_mdVal>"
       << "<st_mdVal species=\"Species_4\">6</st_mdVal>"
       << "</st_minDBH>"
       << "<st_stmDmgInterceptMed>"
       << "<st_sdimVal species=\"Species_1\">2.1789601</st_sdimVal>"
       << "<st_sdimVal species=\"Species_2\">2.475987</st_sdimVal>"
       << "<st_sdimVal species=\"Species_3\">2.1789601</st_sdimVal>"
       << "<st_sdimVal species=\"Species_4\">2.475987</st_sdimVal>"
       << "</st_stmDmgInterceptMed>"
       << "<st_stmDmgInterceptFull>"
       << "<st_sdifVal species=\"Species_1\">3.6334169</st_sdifVal>"
       << "<st_sdifVal species=\"Species_2\">3.6331242</st_sdifVal>"
       << "<st_sdifVal species=\"Species_3\">3.6334169</st_sdifVal>"
       << "<st_sdifVal species=\"Species_4\">3.6331242</st_sdifVal>"
       << "</st_stmDmgInterceptFull>"
       << "<st_stmIntensityCoeff>"
       << "<st_sicVal species=\"Species_1\">-0.3545352</st_sicVal>"
       << "<st_sicVal species=\"Species_2\">-1.2289105</st_sicVal>"
       << "<st_sicVal species=\"Species_3\">-0.3545352</st_sicVal>"
       << "<st_sicVal species=\"Species_4\">-1.2289105</st_sicVal>"
       << "</st_stmIntensityCoeff>"
       << "<st_stmDBHCoeff>"
       << "<st_sdcVal species=\"Species_1\">0.8280319</st_sdcVal>"
       << "<st_sdcVal species=\"Species_2\">0.3282479</st_sdcVal>"
       << "<st_sdcVal species=\"Species_3\">0.8280319</st_sdcVal>"
       << "<st_sdcVal species=\"Species_4\">0.3282479</st_sdcVal>"
       << "</st_stmDBHCoeff>"
       << "<st_stmPropDieMedDmg>"
       << "<st_spdmdVal species=\"Species_1\">0</st_spdmdVal>"
       << "<st_spdmdVal species=\"Species_2\">0</st_spdmdVal>"
       << "<st_spdmdVal species=\"Species_3\">0</st_spdmdVal>"
       << "<st_spdmdVal species=\"Species_4\">0</st_spdmdVal>"
       << "</st_stmPropDieMedDmg>"
       << "<st_stmPropDieFullDmg>"
       << "<st_spdfdVal species=\"Species_1\">0</st_spdfdVal>"
       << "<st_spdfdVal species=\"Species_2\">0</st_spdfdVal>"
       << "<st_spdfdVal species=\"Species_3\">0</st_spdfdVal>"
       << "<st_spdfdVal species=\"Species_4\">0</st_spdfdVal>"
       << "</st_stmPropDieFullDmg>"
       << "<st_stmPropTipUpFullDmg>"
       << "<st_sptufdVal species=\"Species_1\">0</st_sptufdVal>"
       << "<st_sptufdVal species=\"Species_2\">0</st_sptufdVal>"
       << "<st_sptufdVal species=\"Species_3\">0</st_sptufdVal>"
       << "<st_sptufdVal species=\"Species_4\">0</st_sptufdVal>"
       << "</st_stmPropTipUpFullDmg>"
       << "<st_numYearsStormSnags>0</st_numYearsStormSnags>"
       << "<st_numYearsToHeal>4</st_numYearsToHeal>"
       << "</StormDamageApplier2>"
       << "<StochasticMortality3>"
       << "<mo_stochasticMortRate>"
       << "<mo_smrVal species=\"Species_1\">0.0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_2\">0.0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_3\">0.0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_4\">0.0</mo_smrVal>"
       << "</mo_stochasticMortRate>"
       << "</StochasticMortality3>";

  oOut << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "<NonSpatialDisperse4>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_4\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_2\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_3\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_nonSpatialSlopeOfLambda>"
       << "<di_nssolVal species=\"Species_4\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_2\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_3\">0</di_nssolVal>"
       << "</di_nonSpatialSlopeOfLambda>"
       << "<di_nonSpatialInterceptOfLambda>"
       << "<di_nsiolVal species=\"Species_4\">0</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_2\">0</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_3\">0</di_nsiolVal>"
       << "</di_nonSpatialInterceptOfLambda>"
       << "</NonSpatialDisperse4>";

  oOut << "<LightDependentSeedSurvival5>"
       << "<es_optimumGLI>"
       << "<es_ogVal species=\"Species_2\">23</es_ogVal>"
       << "<es_ogVal species=\"Species_3\">87</es_ogVal>"
       << "<es_ogVal species=\"Species_4\">55.66</es_ogVal>"
       << "</es_optimumGLI>"
       << "<es_lowSlope>"
       << "<es_lsVal species=\"Species_2\">0.034</es_lsVal>"
       << "<es_lsVal species=\"Species_3\">0.0098</es_lsVal>"
       << "<es_lsVal species=\"Species_4\">0.011</es_lsVal>"
       << "</es_lowSlope>"
       << "<es_highSlope>"
       << "<es_hsVal species=\"Species_2\">0.0023</es_hsVal>"
       << "<es_hsVal species=\"Species_3\">0.0098</es_hsVal>"
       << "<es_hsVal species=\"Species_4\">0.012</es_hsVal>"
       << "</es_highSlope>"
       << "<es_lightHeight>2</es_lightHeight>"
       << "<li_lightExtinctionCoefficient>"
       << "<li_lecVal species=\"Species_1\">0.2</li_lecVal>"
       << "<li_lecVal species=\"Species_2\">0.2</li_lecVal>"
       << "<li_lecVal species=\"Species_3\">0.87</li_lecVal>"
       << "<li_lecVal species=\"Species_4\">0</li_lecVal>"
       << "<li_lecVal species=\"Species_5\">0.87</li_lecVal>"
       << "</li_lightExtinctionCoefficient>"
       << "<es_lightExtCoeffPartDmg>"
       << "<es_lecpdVal species=\"Species_1\">0.2</es_lecpdVal>"
       << "<es_lecpdVal species=\"Species_2\">0.23</es_lecpdVal>"
       << "<es_lecpdVal species=\"Species_3\">0.5</es_lecpdVal>"
       << "<es_lecpdVal species=\"Species_4\">0.6</es_lecpdVal>"
       << "<es_lecpdVal species=\"Species_5\">0.5</es_lecpdVal>"
       << "</es_lightExtCoeffPartDmg>"
       << "<es_lightExtCoeffFullDmg>"
       << "<es_lecfdVal species=\"Species_1\">0.2</es_lecfdVal>"
       << "<es_lecfdVal species=\"Species_2\">0.8</es_lecfdVal>"
       << "<es_lecfdVal species=\"Species_3\">0.9</es_lecfdVal>"
       << "<es_lecfdVal species=\"Species_4\">0.5566</es_lecfdVal>"
       << "<es_lecfdVal species=\"Species_5\">0.9</es_lecfdVal>"
       << "</es_lightExtCoeffFullDmg>"
       << "<li_beamFractGlobalRad>0.5</li_beamFractGlobalRad>"
       << "<li_clearSkyTransCoeff>0.65</li_clearSkyTransCoeff>"
       << "<li_julianDayGrowthStarts>105</li_julianDayGrowthStarts>"
       << "<li_julianDayGrowthEnds>258</li_julianDayGrowthEnds>"
       << "<li_minSunAngle>0.785</li_minSunAngle>"
       << "<li_numAltGrids>12</li_numAltGrids>"
       << "<li_numAziGrids>18</li_numAziGrids>"
       << "</LightDependentSeedSurvival5>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
//  WriteXMLFile2()
////////////////////////////////////////////////////////////////////////////
const char* clTestLightDepSeedSurvival::WriteXMLFile2() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  WriteCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>NonSpatialDisperse</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>LightDependentSeedSurvival</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>WeibullSnagMortality</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Snag\"/>"
       << "<applyTo species=\"Species_2\" type=\"Snag\"/>"
       << "<applyTo species=\"Species_4\" type=\"Snag\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Establishment</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>4</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_3\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>";

  oOut << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "<NonSpatialDisperse1>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_4\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_2\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_3\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_nonSpatialSlopeOfLambda>"
       << "<di_nssolVal species=\"Species_4\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_2\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_3\">0</di_nssolVal>"
       << "</di_nonSpatialSlopeOfLambda>"
       << "<di_nonSpatialInterceptOfLambda>"
       << "<di_nsiolVal species=\"Species_4\">0</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_2\">0</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_3\">0</di_nsiolVal>"
       << "</di_nonSpatialInterceptOfLambda>"
       << "</NonSpatialDisperse1>";

  oOut << "<LightDependentSeedSurvival2>"
       << "<es_optimumGLI>"
       << "<es_ogVal species=\"Species_2\">23</es_ogVal>"
       << "<es_ogVal species=\"Species_3\">87</es_ogVal>"
       << "<es_ogVal species=\"Species_4\">55.66</es_ogVal>"
       << "</es_optimumGLI>"
       << "<es_lowSlope>"
       << "<es_lsVal species=\"Species_2\">0.034</es_lsVal>"
       << "<es_lsVal species=\"Species_3\">0.0098</es_lsVal>"
       << "<es_lsVal species=\"Species_4\">0.011</es_lsVal>"
       << "</es_lowSlope>"
       << "<es_highSlope>"
       << "<es_hsVal species=\"Species_2\">0.0023</es_hsVal>"
       << "<es_hsVal species=\"Species_3\">0.0098</es_hsVal>"
       << "<es_hsVal species=\"Species_4\">0.012</es_hsVal>"
       << "</es_highSlope>"
       << "<es_lightHeight>2</es_lightHeight>"
       << "<li_lightExtinctionCoefficient>"
       << "<li_lecVal species=\"Species_1\">0.2</li_lecVal>"
       << "<li_lecVal species=\"Species_2\">0.2</li_lecVal>"
       << "<li_lecVal species=\"Species_3\">0.87</li_lecVal>"
       << "<li_lecVal species=\"Species_4\">0.5</li_lecVal>"
       << "<li_lecVal species=\"Species_5\">0.87</li_lecVal>"
       << "</li_lightExtinctionCoefficient>"
       << "<li_snag1LightExtinctionCoefficient>"
       << "<li_s1lecVal species=\"Species_1\">0.4</li_s1lecVal>"
       << "<li_s1lecVal species=\"Species_2\">0.4</li_s1lecVal>"
       << "<li_s1lecVal species=\"Species_3\">0.6</li_s1lecVal>"
       << "<li_s1lecVal species=\"Species_4\">0.7</li_s1lecVal>"
       << "<li_s1lecVal species=\"Species_5\">0.4</li_s1lecVal>"
       << "</li_snag1LightExtinctionCoefficient>"
       << "<li_snag2LightExtinctionCoefficient>"
       << "<li_s2lecVal species=\"Species_1\">0.5</li_s2lecVal>"
       << "<li_s2lecVal species=\"Species_2\">0.5</li_s2lecVal>"
       << "<li_s2lecVal species=\"Species_3\">0.7</li_s2lecVal>"
       << "<li_s2lecVal species=\"Species_4\">0.8</li_s2lecVal>"
       << "<li_s2lecVal species=\"Species_5\">0.5</li_s2lecVal>"
       << "</li_snag2LightExtinctionCoefficient>"
       << "<li_snag3LightExtinctionCoefficient>"
       << "<li_s3lecVal species=\"Species_1\">0.1</li_s3lecVal>"
       << "<li_s3lecVal species=\"Species_2\">0.1</li_s3lecVal>"
       << "<li_s3lecVal species=\"Species_3\">0.1</li_s3lecVal>"
       << "<li_s3lecVal species=\"Species_4\">0.1</li_s3lecVal>"
       << "<li_s3lecVal species=\"Species_5\">0.1</li_s3lecVal>"
       << "</li_snag3LightExtinctionCoefficient>"
       << "<li_beamFractGlobalRad>0.5</li_beamFractGlobalRad>"
       << "<li_clearSkyTransCoeff>0.65</li_clearSkyTransCoeff>"
       << "<li_julianDayGrowthStarts>105</li_julianDayGrowthStarts>"
       << "<li_julianDayGrowthEnds>258</li_julianDayGrowthEnds>"
       << "<li_minSunAngle>0.785</li_minSunAngle>"
       << "<li_numAltGrids>12</li_numAltGrids>"
       << "<li_numAziGrids>18</li_numAziGrids>"
       << "<li_snagAgeClass1>12</li_snagAgeClass1>"
       << "<li_snagAgeClass2>15</li_snagAgeClass2>"
       << "</LightDependentSeedSurvival2>"
       << "<WeibullSnagMortality3>"
       << "<mo_snagSizeClass1DBH>"
       << "<mo_sc1dVal species=\"Species_3\">31</mo_sc1dVal>"
       << "<mo_sc1dVal species=\"Species_2\">31</mo_sc1dVal>"
       << "<mo_sc1dVal species=\"Species_4\">12</mo_sc1dVal>"
       << "</mo_snagSizeClass1DBH>"
       << "<mo_snagSizeClass2DBH>"
       << "<mo_sc2dVal species=\"Species_3\">39</mo_sc2dVal>"
       << "<mo_sc2dVal species=\"Species_2\">39</mo_sc2dVal>"
       << "<mo_sc2dVal species=\"Species_4\">30</mo_sc2dVal>"
       << "</mo_snagSizeClass2DBH>"
       << "<mo_snag1WeibullA>"
       << "<mo_s1waVal species=\"Species_3\">0.025</mo_s1waVal>"
       << "<mo_s1waVal species=\"Species_2\">0.025</mo_s1waVal>"
       << "<mo_s1waVal species=\"Species_4\">0.113</mo_s1waVal>"
       << "</mo_snag1WeibullA>"
       << "<mo_snag2WeibullA>"
       << "<mo_s2waVal species=\"Species_3\">0.09</mo_s2waVal>"
       << "<mo_s2waVal species=\"Species_2\">0.09</mo_s2waVal>"
       << "<mo_s2waVal species=\"Species_4\">0.0113</mo_s2waVal>"
       << "</mo_snag2WeibullA>"
       << "<mo_snag3WeibullA>"
       << "<mo_s3waVal species=\"Species_3\">0.0204</mo_s3waVal>"
       << "<mo_s3waVal species=\"Species_2\">0.0204</mo_s3waVal>"
       << "<mo_s3waVal species=\"Species_4\">0.1</mo_s3waVal>"
       << "</mo_snag3WeibullA>"
       << "<mo_snag1WeibullB>"
       << "<mo_s1wbVal species=\"Species_3\">3</mo_s1wbVal>"
       << "<mo_s1wbVal species=\"Species_2\">3</mo_s1wbVal>"
       << "<mo_s1wbVal species=\"Species_4\">3.049</mo_s1wbVal>"
       << "</mo_snag1WeibullB>"
       << "<mo_snag2WeibullB>"
       << "<mo_s2wbVal species=\"Species_3\">2</mo_s2wbVal>"
       << "<mo_s2wbVal species=\"Species_2\">2</mo_s2wbVal>"
       << "<mo_s2wbVal species=\"Species_4\">2.2</mo_s2wbVal>"
       << "</mo_snag2WeibullB>"
       << "<mo_snag3WeibullB>"
       << "<mo_s3wbVal species=\"Species_3\">2.5</mo_s3wbVal>"
       << "<mo_s3wbVal species=\"Species_2\">2.5</mo_s3wbVal>"
       << "<mo_s3wbVal species=\"Species_4\">2.3</mo_s3wbVal>"
       << "</mo_snag3WeibullB>"
       << "</WeibullSnagMortality3>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
//  WriteXMLFile3()
////////////////////////////////////////////////////////////////////////////
const char* clTestLightDepSeedSurvival::WriteXMLFile3() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  WriteCommonStuff(oOut);

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
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
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
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>NonSpatialDisperse</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>5</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StormLightDependentSeedSurvival</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>6</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Establishment</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>7</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_3\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<Storm1>"
       << "<st_s1ReturnInterval>1000</st_s1ReturnInterval>"
       << "<st_s2ReturnInterval>1000</st_s2ReturnInterval>"
       << "<st_s3ReturnInterval>1000</st_s3ReturnInterval>"
       << "<st_s4ReturnInterval>1000</st_s4ReturnInterval>"
       << "<st_s5ReturnInterval>1000</st_s5ReturnInterval>"
       << "<st_s6ReturnInterval>1000</st_s6ReturnInterval>"
       << "<st_s7ReturnInterval>1000</st_s7ReturnInterval>"
       << "<st_s8ReturnInterval>1000</st_s8ReturnInterval>"
       << "<st_s9ReturnInterval>1000</st_s9ReturnInterval>"
       << "<st_s10ReturnInterval>1000</st_s10ReturnInterval>"
       << "<st_susceptibility>1</st_susceptibility>"
       << "<st_stochasticity>0</st_stochasticity>"
       << "<st_stmSSTPeriod>1</st_stmSSTPeriod>"
       << "<st_stmSineD>0</st_stmSineD>"
       << "<st_stmSineF>1</st_stmSineF>"
       << "<st_stmSineG>1</st_stmSineG>"
       << "<st_stmTrendSlopeM>0</st_stmTrendSlopeM>"
       << "<st_stmTrendInterceptI>1</st_stmTrendInterceptI>"
       << "</Storm1>"
       << "<StormDamageApplier2>"
       << "<st_minDBH>"
       << "<st_mdVal species=\"Species_1\">5</st_mdVal>"
       << "<st_mdVal species=\"Species_2\">6</st_mdVal>"
       << "<st_mdVal species=\"Species_3\">5</st_mdVal>"
       << "<st_mdVal species=\"Species_4\">6</st_mdVal>"
       << "</st_minDBH>"
       << "<st_stmDmgInterceptMed>"
       << "<st_sdimVal species=\"Species_1\">2.1789601</st_sdimVal>"
       << "<st_sdimVal species=\"Species_2\">2.475987</st_sdimVal>"
       << "<st_sdimVal species=\"Species_3\">2.1789601</st_sdimVal>"
       << "<st_sdimVal species=\"Species_4\">2.475987</st_sdimVal>"
       << "</st_stmDmgInterceptMed>"
       << "<st_stmDmgInterceptFull>"
       << "<st_sdifVal species=\"Species_1\">3.6334169</st_sdifVal>"
       << "<st_sdifVal species=\"Species_2\">3.6331242</st_sdifVal>"
       << "<st_sdifVal species=\"Species_3\">3.6334169</st_sdifVal>"
       << "<st_sdifVal species=\"Species_4\">3.6331242</st_sdifVal>"
       << "</st_stmDmgInterceptFull>"
       << "<st_stmIntensityCoeff>"
       << "<st_sicVal species=\"Species_1\">-0.3545352</st_sicVal>"
       << "<st_sicVal species=\"Species_2\">-1.2289105</st_sicVal>"
       << "<st_sicVal species=\"Species_3\">-0.3545352</st_sicVal>"
       << "<st_sicVal species=\"Species_4\">-1.2289105</st_sicVal>"
       << "</st_stmIntensityCoeff>"
       << "<st_stmDBHCoeff>"
       << "<st_sdcVal species=\"Species_1\">0.8280319</st_sdcVal>"
       << "<st_sdcVal species=\"Species_2\">0.3282479</st_sdcVal>"
       << "<st_sdcVal species=\"Species_3\">0.8280319</st_sdcVal>"
       << "<st_sdcVal species=\"Species_4\">0.3282479</st_sdcVal>"
       << "</st_stmDBHCoeff>"
       << "<st_stmPropDieMedDmg>"
       << "<st_spdmdVal species=\"Species_1\">0</st_spdmdVal>"
       << "<st_spdmdVal species=\"Species_2\">0</st_spdmdVal>"
       << "<st_spdmdVal species=\"Species_3\">0</st_spdmdVal>"
       << "<st_spdmdVal species=\"Species_4\">0</st_spdmdVal>"
       << "</st_stmPropDieMedDmg>"
       << "<st_stmPropDieFullDmg>"
       << "<st_spdfdVal species=\"Species_1\">0</st_spdfdVal>"
       << "<st_spdfdVal species=\"Species_2\">0</st_spdfdVal>"
       << "<st_spdfdVal species=\"Species_3\">0</st_spdfdVal>"
       << "<st_spdfdVal species=\"Species_4\">0</st_spdfdVal>"
       << "</st_stmPropDieFullDmg>"
       << "<st_stmPropTipUpFullDmg>"
       << "<st_sptufdVal species=\"Species_1\">0</st_sptufdVal>"
       << "<st_sptufdVal species=\"Species_2\">0</st_sptufdVal>"
       << "<st_sptufdVal species=\"Species_3\">0</st_sptufdVal>"
       << "<st_sptufdVal species=\"Species_4\">0</st_sptufdVal>"
       << "</st_stmPropTipUpFullDmg>"
       << "<st_numYearsStormSnags>0</st_numYearsStormSnags>"
       << "<st_numYearsToHeal>4</st_numYearsToHeal>"
       << "</StormDamageApplier2>"
       << "<StormLight3>"
       << "<li_stormLightRadius>15</li_stormLightRadius>"
       << "<li_stormLightSlope>-4</li_stormLightSlope>"
       << "<li_stormLightIntercept>95</li_stormLightIntercept>"
       << "<li_stormLightMaxDmgTime>3</li_stormLightMaxDmgTime>"
       << "<li_stormLightSnagMaxDmgTime>0</li_stormLightSnagMaxDmgTime>"
       << "<li_stormLightStoch>0</li_stormLightStoch>"
       << "<li_stormLightMinFullCanopy>9</li_stormLightMinFullCanopy>"
       << "</StormLight3>"
       << "<StochasticMortality4>"
       << "<mo_stochasticMortRate>"
       << "<mo_smrVal species=\"Species_1\">0.0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_2\">0.0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_3\">0.0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_4\">0.0</mo_smrVal>"
       << "</mo_stochasticMortRate>"
       << "</StochasticMortality4>";

  oOut << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "<NonSpatialDisperse5>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_4\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_2\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_3\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_nonSpatialSlopeOfLambda>"
       << "<di_nssolVal species=\"Species_4\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_2\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_3\">0</di_nssolVal>"
       << "</di_nonSpatialSlopeOfLambda>"
       << "<di_nonSpatialInterceptOfLambda>"
       << "<di_nsiolVal species=\"Species_4\">0</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_2\">0</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_3\">0</di_nsiolVal>"
       << "</di_nonSpatialInterceptOfLambda>"
       << "</NonSpatialDisperse5>";

  oOut << "<LightDependentSeedSurvival6>"
       << "<es_optimumGLI>"
       << "<es_ogVal species=\"Species_2\">23</es_ogVal>"
       << "<es_ogVal species=\"Species_3\">87</es_ogVal>"
       << "<es_ogVal species=\"Species_4\">55.66</es_ogVal>"
       << "</es_optimumGLI>"
       << "<es_lowSlope>"
       << "<es_lsVal species=\"Species_2\">0.034</es_lsVal>"
       << "<es_lsVal species=\"Species_3\">0.0098</es_lsVal>"
       << "<es_lsVal species=\"Species_4\">0.011</es_lsVal>"
       << "</es_lowSlope>"
       << "<es_highSlope>"
       << "<es_hsVal species=\"Species_2\">0.0023</es_hsVal>"
       << "<es_hsVal species=\"Species_3\">0.0098</es_hsVal>"
       << "<es_hsVal species=\"Species_4\">0.012</es_hsVal>"
       << "</es_highSlope>"
       << "</LightDependentSeedSurvival6>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}


////////////////////////////////////////////////////////////////////////////
//  WriteXMLErrorFile1()
////////////////////////////////////////////////////////////////////////////
const char* clTestLightDepSeedSurvival::WriteXMLErrorFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  WriteCommonStuff(oOut);

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
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>NonSpatialDisperse</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>4</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>LightDependentSeedSurvival</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>5</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<Storm1>"
       << "<st_s1ReturnInterval>1000</st_s1ReturnInterval>"
       << "<st_s2ReturnInterval>1000</st_s2ReturnInterval>"
       << "<st_s3ReturnInterval>1000</st_s3ReturnInterval>"
       << "<st_s4ReturnInterval>1000</st_s4ReturnInterval>"
       << "<st_s5ReturnInterval>1000</st_s5ReturnInterval>"
       << "<st_s6ReturnInterval>1000</st_s6ReturnInterval>"
       << "<st_s7ReturnInterval>1000</st_s7ReturnInterval>"
       << "<st_s8ReturnInterval>1000</st_s8ReturnInterval>"
       << "<st_s9ReturnInterval>1000</st_s9ReturnInterval>"
       << "<st_s10ReturnInterval>1000</st_s10ReturnInterval>"
       << "<st_susceptibility>1</st_susceptibility>"
       << "<st_stochasticity>0</st_stochasticity>"
       << "<st_stmSSTPeriod>1</st_stmSSTPeriod>"
       << "<st_stmSineD>0</st_stmSineD>"
       << "<st_stmSineF>1</st_stmSineF>"
       << "<st_stmSineG>1</st_stmSineG>"
       << "<st_stmTrendSlopeM>0</st_stmTrendSlopeM>"
       << "<st_stmTrendInterceptI>1</st_stmTrendInterceptI>"
       << "</Storm1>"
       << "<StormDamageApplier2>"
       << "<st_minDBH>"
       << "<st_mdVal species=\"Species_1\">5</st_mdVal>"
       << "<st_mdVal species=\"Species_2\">6</st_mdVal>"
       << "<st_mdVal species=\"Species_3\">5</st_mdVal>"
       << "<st_mdVal species=\"Species_4\">6</st_mdVal>"
       << "</st_minDBH>"
       << "<st_stmDmgInterceptMed>"
       << "<st_sdimVal species=\"Species_1\">2.1789601</st_sdimVal>"
       << "<st_sdimVal species=\"Species_2\">2.475987</st_sdimVal>"
       << "<st_sdimVal species=\"Species_3\">2.1789601</st_sdimVal>"
       << "<st_sdimVal species=\"Species_4\">2.475987</st_sdimVal>"
       << "</st_stmDmgInterceptMed>"
       << "<st_stmDmgInterceptFull>"
       << "<st_sdifVal species=\"Species_1\">3.6334169</st_sdifVal>"
       << "<st_sdifVal species=\"Species_2\">3.6331242</st_sdifVal>"
       << "<st_sdifVal species=\"Species_3\">3.6334169</st_sdifVal>"
       << "<st_sdifVal species=\"Species_4\">3.6331242</st_sdifVal>"
       << "</st_stmDmgInterceptFull>"
       << "<st_stmIntensityCoeff>"
       << "<st_sicVal species=\"Species_1\">-0.3545352</st_sicVal>"
       << "<st_sicVal species=\"Species_2\">-1.2289105</st_sicVal>"
       << "<st_sicVal species=\"Species_3\">-0.3545352</st_sicVal>"
       << "<st_sicVal species=\"Species_4\">-1.2289105</st_sicVal>"
       << "</st_stmIntensityCoeff>"
       << "<st_stmDBHCoeff>"
       << "<st_sdcVal species=\"Species_1\">0.8280319</st_sdcVal>"
       << "<st_sdcVal species=\"Species_2\">0.3282479</st_sdcVal>"
       << "<st_sdcVal species=\"Species_3\">0.8280319</st_sdcVal>"
       << "<st_sdcVal species=\"Species_4\">0.3282479</st_sdcVal>"
       << "</st_stmDBHCoeff>"
       << "<st_stmPropDieMedDmg>"
       << "<st_spdmdVal species=\"Species_1\">0</st_spdmdVal>"
       << "<st_spdmdVal species=\"Species_2\">0</st_spdmdVal>"
       << "<st_spdmdVal species=\"Species_3\">0</st_spdmdVal>"
       << "<st_spdmdVal species=\"Species_4\">0</st_spdmdVal>"
       << "</st_stmPropDieMedDmg>"
       << "<st_stmPropDieFullDmg>"
       << "<st_spdfdVal species=\"Species_1\">0</st_spdfdVal>"
       << "<st_spdfdVal species=\"Species_2\">0</st_spdfdVal>"
       << "<st_spdfdVal species=\"Species_3\">0</st_spdfdVal>"
       << "<st_spdfdVal species=\"Species_4\">0</st_spdfdVal>"
       << "</st_stmPropDieFullDmg>"
       << "<st_stmPropTipUpFullDmg>"
       << "<st_sptufdVal species=\"Species_1\">0</st_sptufdVal>"
       << "<st_sptufdVal species=\"Species_2\">0</st_sptufdVal>"
       << "<st_sptufdVal species=\"Species_3\">0</st_sptufdVal>"
       << "<st_sptufdVal species=\"Species_4\">0</st_sptufdVal>"
       << "</st_stmPropTipUpFullDmg>"
       << "<st_numYearsStormSnags>0</st_numYearsStormSnags>"
       << "<st_numYearsToHeal>4</st_numYearsToHeal>"
       << "</StormDamageApplier2>"
       << "<StochasticMortality3>"
       << "<mo_stochasticMortRate>"
       << "<mo_smrVal species=\"Species_1\">0.0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_2\">0.0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_3\">0.0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_4\">0.0</mo_smrVal>"
       << "</mo_stochasticMortRate>"
       << "</StochasticMortality3>";

  oOut << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "<NonSpatialDisperse4>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_4\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_2\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_3\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_nonSpatialSlopeOfLambda>"
       << "<di_nssolVal species=\"Species_4\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_2\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_3\">0</di_nssolVal>"
       << "</di_nonSpatialSlopeOfLambda>"
       << "<di_nonSpatialInterceptOfLambda>"
       << "<di_nsiolVal species=\"Species_4\">0</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_2\">0</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_3\">0</di_nsiolVal>"
       << "</di_nonSpatialInterceptOfLambda>"
       << "</NonSpatialDisperse4>";

  oOut << "<LightDependentSeedSurvival5>"
       << "<es_optimumGLI>"
       << "<es_ogVal species=\"Species_2\">23</es_ogVal>"
       << "<es_ogVal species=\"Species_3\">87</es_ogVal>"
       << "<es_ogVal species=\"Species_4\">55.66</es_ogVal>"
       << "</es_optimumGLI>"
       << "<es_lowSlope>"
       << "<es_lsVal species=\"Species_2\">0.034</es_lsVal>"
       << "<es_lsVal species=\"Species_3\">0.0098</es_lsVal>"
       << "<es_lsVal species=\"Species_4\">0.011</es_lsVal>"
       << "</es_lowSlope>"
       << "<es_highSlope>"
       << "<es_hsVal species=\"Species_2\">0.0023</es_hsVal>"
       << "<es_hsVal species=\"Species_3\">0.0098</es_hsVal>"
       << "<es_hsVal species=\"Species_4\">0.012</es_hsVal>"
       << "</es_highSlope>"
       << "<es_lightHeight>2</es_lightHeight>"
       << "<li_lightExtinctionCoefficient>"
       << "<li_lecVal species=\"Species_1\">0.2</li_lecVal>"
       << "<li_lecVal species=\"Species_2\">0.2</li_lecVal>"
       << "<li_lecVal species=\"Species_3\">0.87</li_lecVal>"
       << "<li_lecVal species=\"Species_4\">0</li_lecVal>"
       << "<li_lecVal species=\"Species_5\">0</li_lecVal>"
       << "</li_lightExtinctionCoefficient>"
       << "<es_lightExtCoeffPartDmg>"
       << "<es_lecpdVal species=\"Species_1\">0.2</es_lecpdVal>"
       << "<es_lecpdVal species=\"Species_2\">0.23</es_lecpdVal>"
       << "<es_lecpdVal species=\"Species_3\">0.5</es_lecpdVal>"
       << "<es_lecpdVal species=\"Species_4\">0.6</es_lecpdVal>"
       << "<es_lecpdVal species=\"Species_5\">0.6</es_lecpdVal>"
       << "</es_lightExtCoeffPartDmg>"
       << "<es_lightExtCoeffFullDmg>"
       << "<es_lecfdVal species=\"Species_1\">1.2</es_lecfdVal>"
       << "<es_lecfdVal species=\"Species_2\">0.8</es_lecfdVal>"
       << "<es_lecfdVal species=\"Species_3\">0.9</es_lecfdVal>"
       << "<es_lecfdVal species=\"Species_4\">0.5566</es_lecfdVal>"
       << "<es_lecfdVal species=\"Species_5\">0.5566</es_lecfdVal>"
       << "</es_lightExtCoeffFullDmg>"
       << "<li_beamFractGlobalRad>0.5</li_beamFractGlobalRad>"
       << "<li_clearSkyTransCoeff>0.65</li_clearSkyTransCoeff>"
       << "<li_julianDayGrowthStarts>105</li_julianDayGrowthStarts>"
       << "<li_julianDayGrowthEnds>258</li_julianDayGrowthEnds>"
       << "<li_minSunAngle>0.785</li_minSunAngle>"
       << "<li_numAltGrids>12</li_numAltGrids>"
       << "<li_numAziGrids>18</li_numAziGrids>"
       << "</LightDependentSeedSurvival5>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
//  WriteXMLErrorFile2()
////////////////////////////////////////////////////////////////////////////
const char* clTestLightDepSeedSurvival::WriteXMLErrorFile2() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  WriteCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>NonSpatialDisperse</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>LightDependentSeedSurvival</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>";

  oOut << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "<NonSpatialDisperse1>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_4\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_2\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_3\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_nonSpatialSlopeOfLambda>"
       << "<di_nssolVal species=\"Species_4\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_2\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_3\">0</di_nssolVal>"
       << "</di_nonSpatialSlopeOfLambda>"
       << "<di_nonSpatialInterceptOfLambda>"
       << "<di_nsiolVal species=\"Species_4\">0</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_2\">0</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_3\">0</di_nsiolVal>"
       << "</di_nonSpatialInterceptOfLambda>"
       << "</NonSpatialDisperse1>";

  oOut << "<LightDependentSeedSurvival2>"
       << "<es_optimumGLI>"
       << "<es_ogVal species=\"Species_2\">23</es_ogVal>"
       << "<es_ogVal species=\"Species_3\">87</es_ogVal>"
       << "<es_ogVal species=\"Species_4\">55.66</es_ogVal>"
       << "</es_optimumGLI>"
       << "<es_lowSlope>"
       << "<es_lsVal species=\"Species_2\">0.034</es_lsVal>"
       << "<es_lsVal species=\"Species_3\">0.0098</es_lsVal>"
       << "<es_lsVal species=\"Species_4\">0.011</es_lsVal>"
       << "</es_lowSlope>"
       << "<es_highSlope>"
       << "<es_hsVal species=\"Species_2\">0.0023</es_hsVal>"
       << "<es_hsVal species=\"Species_3\">0.0098</es_hsVal>"
       << "<es_hsVal species=\"Species_4\">0.012</es_hsVal>"
       << "</es_highSlope>"
       << "<es_lightHeight>-2</es_lightHeight>"
       << "<li_lightExtinctionCoefficient>"
       << "<li_lecVal species=\"Species_1\">0.2</li_lecVal>"
       << "<li_lecVal species=\"Species_2\">0.2</li_lecVal>"
       << "<li_lecVal species=\"Species_3\">0.87</li_lecVal>"
       << "<li_lecVal species=\"Species_4\">0</li_lecVal>"
       << "<li_lecVal species=\"Species_5\">0</li_lecVal>"
       << "</li_lightExtinctionCoefficient>"
       << "<li_beamFractGlobalRad>0.5</li_beamFractGlobalRad>"
       << "<li_clearSkyTransCoeff>0.65</li_clearSkyTransCoeff>"
       << "<li_julianDayGrowthStarts>105</li_julianDayGrowthStarts>"
       << "<li_julianDayGrowthEnds>258</li_julianDayGrowthEnds>"
       << "<li_minSunAngle>0.785</li_minSunAngle>"
       << "<li_numAltGrids>12</li_numAltGrids>"
       << "<li_numAziGrids>18</li_numAziGrids>"
       << "</LightDependentSeedSurvival2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
//  WriteXMLErrorFile3()
////////////////////////////////////////////////////////////////////////////
const char* clTestLightDepSeedSurvival::WriteXMLErrorFile3() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  WriteCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>NonSpatialDisperse</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>LightDependentSeedSurvival</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>";

  oOut << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "<NonSpatialDisperse1>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_4\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_2\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_3\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_nonSpatialSlopeOfLambda>"
       << "<di_nssolVal species=\"Species_4\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_2\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_3\">0</di_nssolVal>"
       << "</di_nonSpatialSlopeOfLambda>"
       << "<di_nonSpatialInterceptOfLambda>"
       << "<di_nsiolVal species=\"Species_4\">0</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_2\">0</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_3\">0</di_nsiolVal>"
       << "</di_nonSpatialInterceptOfLambda>"
       << "</NonSpatialDisperse1>";

  oOut << "<LightDependentSeedSurvival2>"
       << "<es_optimumGLI>"
       << "<es_ogVal species=\"Species_2\">23</es_ogVal>"
       << "<es_ogVal species=\"Species_3\">87</es_ogVal>"
       << "<es_ogVal species=\"Species_4\">155.66</es_ogVal>"
       << "</es_optimumGLI>"
       << "<es_lowSlope>"
       << "<es_lsVal species=\"Species_2\">0.034</es_lsVal>"
       << "<es_lsVal species=\"Species_3\">0.0098</es_lsVal>"
       << "<es_lsVal species=\"Species_4\">0.011</es_lsVal>"
       << "</es_lowSlope>"
       << "<es_highSlope>"
       << "<es_hsVal species=\"Species_2\">0.0023</es_hsVal>"
       << "<es_hsVal species=\"Species_3\">0.0098</es_hsVal>"
       << "<es_hsVal species=\"Species_4\">0.012</es_hsVal>"
       << "</es_highSlope>"
       << "<es_lightHeight>2</es_lightHeight>"
       << "<li_lightExtinctionCoefficient>"
       << "<li_lecVal species=\"Species_1\">0.2</li_lecVal>"
       << "<li_lecVal species=\"Species_2\">0.2</li_lecVal>"
       << "<li_lecVal species=\"Species_3\">0.87</li_lecVal>"
       << "<li_lecVal species=\"Species_4\">0</li_lecVal>"
       << "<li_lecVal species=\"Species_5\">0</li_lecVal>"
       << "</li_lightExtinctionCoefficient>"
       << "<li_beamFractGlobalRad>0.5</li_beamFractGlobalRad>"
       << "<li_clearSkyTransCoeff>0.65</li_clearSkyTransCoeff>"
       << "<li_julianDayGrowthStarts>105</li_julianDayGrowthStarts>"
       << "<li_julianDayGrowthEnds>258</li_julianDayGrowthEnds>"
       << "<li_minSunAngle>0.785</li_minSunAngle>"
       << "<li_numAltGrids>12</li_numAltGrids>"
       << "<li_numAziGrids>18</li_numAziGrids>"
       << "</LightDependentSeedSurvival2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
//  WriteXMLErrorFile4()
////////////////////////////////////////////////////////////////////////////
const char* clTestLightDepSeedSurvival::WriteXMLErrorFile4() {
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
       << "<plot_lenX>500.0</plot_lenX>"
       << "<plot_lenY>100.0</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\" />"
       << "<tr_species speciesName=\"Species_2\" />"
       << "<tr_species speciesName=\"Species_3\" />"
       << "<tr_species speciesName=\"Species_4\" />"
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
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_2\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_3\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_4\">0.0299</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
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
       << "<tr_wacrdVal species=\"Species_5\">0</tr_wacrdVal>"
       << "</tr_whatAdultCrownRadDiam>"
       << "<tr_whatAdultCrownHeightHeight>"
       << "<tr_wachhVal species=\"Species_1\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_2\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_3\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_4\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_5\">0</tr_wachhVal>"
       << "</tr_whatAdultCrownHeightHeight>"
       << "<tr_whatSaplingCrownRadDiam>"
       << "<tr_wscrdVal species=\"Species_1\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_2\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_3\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_4\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_5\">0</tr_wscrdVal>"
       << "</tr_whatSaplingCrownRadDiam>"
       << "<tr_whatSaplingCrownHeightHeight>"
       << "<tr_wschhVal species=\"Species_1\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_2\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_3\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_4\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_5\">0</tr_wschhVal>"
       << "</tr_whatSaplingCrownHeightHeight>"
       << "</allometry>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>LightDependentSeedSurvival</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "</behaviorList>";

  oOut << "<LightDependentSeedSurvival1>"
       << "<es_optimumGLI>"
       << "<es_ogVal species=\"Species_2\">23</es_ogVal>"
       << "<es_ogVal species=\"Species_3\">87</es_ogVal>"
       << "<es_ogVal species=\"Species_4\">55.66</es_ogVal>"
       << "</es_optimumGLI>"
       << "<es_lowSlope>"
       << "<es_lsVal species=\"Species_2\">0.034</es_lsVal>"
       << "<es_lsVal species=\"Species_3\">0.0098</es_lsVal>"
       << "<es_lsVal species=\"Species_4\">0.011</es_lsVal>"
       << "</es_lowSlope>"
       << "<es_highSlope>"
       << "<es_hsVal species=\"Species_2\">0.0023</es_hsVal>"
       << "<es_hsVal species=\"Species_3\">0.0098</es_hsVal>"
       << "<es_hsVal species=\"Species_4\">0.012</es_hsVal>"
       << "</es_highSlope>"
       << "<es_lightHeight>2</es_lightHeight>"
       << "<li_lightExtinctionCoefficient>"
       << "<li_lecVal species=\"Species_1\">0.2</li_lecVal>"
       << "<li_lecVal species=\"Species_2\">0.2</li_lecVal>"
       << "<li_lecVal species=\"Species_3\">0.87</li_lecVal>"
       << "<li_lecVal species=\"Species_4\">0</li_lecVal>"
       << "<li_lecVal species=\"Species_5\">0</li_lecVal>"
       << "</li_lightExtinctionCoefficient>"
       << "<li_beamFractGlobalRad>0.5</li_beamFractGlobalRad>"
       << "<li_clearSkyTransCoeff>0.65</li_clearSkyTransCoeff>"
       << "<li_julianDayGrowthStarts>105</li_julianDayGrowthStarts>"
       << "<li_julianDayGrowthEnds>258</li_julianDayGrowthEnds>"
       << "<li_minSunAngle>0.785</li_minSunAngle>"
       << "<li_numAltGrids>12</li_numAltGrids>"
       << "<li_numAziGrids>18</li_numAziGrids>"
       << "</LightDependentSeedSurvival1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
//  WriteXMLErrorFile5()
////////////////////////////////////////////////////////////////////////////
const char* clTestLightDepSeedSurvival::WriteXMLErrorFile5() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  WriteCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>NonSpatialDisperse</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>LightDependentSeedSurvival</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>";

  oOut << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "<NonSpatialDisperse1>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_4\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_2\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_3\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_nonSpatialSlopeOfLambda>"
       << "<di_nssolVal species=\"Species_4\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_2\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_3\">0</di_nssolVal>"
       << "</di_nonSpatialSlopeOfLambda>"
       << "<di_nonSpatialInterceptOfLambda>"
       << "<di_nsiolVal species=\"Species_4\">0</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_2\">0</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_3\">0</di_nsiolVal>"
       << "</di_nonSpatialInterceptOfLambda>"
       << "</NonSpatialDisperse1>";

  oOut << "<LightDependentSeedSurvival2>"
       << "<es_optimumGLI>"
       << "<es_ogVal species=\"Species_2\">23</es_ogVal>"
       << "<es_ogVal species=\"Species_3\">87</es_ogVal>"
       << "<es_ogVal species=\"Species_4\">55.66</es_ogVal>"
       << "</es_optimumGLI>"
       << "<es_lowSlope>"
       << "<es_lsVal species=\"Species_2\">0.034</es_lsVal>"
       << "<es_lsVal species=\"Species_3\">0.0098</es_lsVal>"
       << "<es_lsVal species=\"Species_4\">0.011</es_lsVal>"
       << "</es_lowSlope>"
       << "<es_highSlope>"
       << "<es_hsVal species=\"Species_2\">0.0023</es_hsVal>"
       << "<es_hsVal species=\"Species_3\">0.0098</es_hsVal>"
       << "<es_hsVal species=\"Species_4\">0.012</es_hsVal>"
       << "</es_highSlope>"
       << "<es_lightHeight>2</es_lightHeight>"
       << "<li_lightExtinctionCoefficient>"
       << "<li_lecVal species=\"Species_1\">0.2</li_lecVal>"
       << "<li_lecVal species=\"Species_2\">0.2</li_lecVal>"
       << "<li_lecVal species=\"Species_3\">0.87</li_lecVal>"
       << "<li_lecVal species=\"Species_4\">0</li_lecVal>"
       << "<li_lecVal species=\"Species_5\">0</li_lecVal>"
       << "</li_lightExtinctionCoefficient>"
       << "<li_beamFractGlobalRad>0.5</li_beamFractGlobalRad>"
       << "<li_clearSkyTransCoeff>0.65</li_clearSkyTransCoeff>"
       << "<li_julianDayGrowthStarts>105</li_julianDayGrowthStarts>"
       << "<li_julianDayGrowthEnds>258</li_julianDayGrowthEnds>"
       << "<li_minSunAngle>0.785</li_minSunAngle>"
       << "<li_numAltGrids>0</li_numAltGrids>"
       << "<li_numAziGrids>18</li_numAziGrids>"
       << "</LightDependentSeedSurvival2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
//  WriteXMLErrorFile6()
////////////////////////////////////////////////////////////////////////////
const char* clTestLightDepSeedSurvival::WriteXMLErrorFile6() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  WriteCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>NonSpatialDisperse</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>LightDependentSeedSurvival</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>";

  oOut << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "<NonSpatialDisperse1>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_4\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_2\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_3\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_nonSpatialSlopeOfLambda>"
       << "<di_nssolVal species=\"Species_4\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_2\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_3\">0</di_nssolVal>"
       << "</di_nonSpatialSlopeOfLambda>"
       << "<di_nonSpatialInterceptOfLambda>"
       << "<di_nsiolVal species=\"Species_4\">0</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_2\">0</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_3\">0</di_nsiolVal>"
       << "</di_nonSpatialInterceptOfLambda>"
       << "</NonSpatialDisperse1>";

  oOut << "<LightDependentSeedSurvival2>"
       << "<es_optimumGLI>"
       << "<es_ogVal species=\"Species_2\">23</es_ogVal>"
       << "<es_ogVal species=\"Species_3\">87</es_ogVal>"
       << "<es_ogVal species=\"Species_4\">55.66</es_ogVal>"
       << "</es_optimumGLI>"
       << "<es_lowSlope>"
       << "<es_lsVal species=\"Species_2\">0.034</es_lsVal>"
       << "<es_lsVal species=\"Species_3\">0.0098</es_lsVal>"
       << "<es_lsVal species=\"Species_4\">0.011</es_lsVal>"
       << "</es_lowSlope>"
       << "<es_highSlope>"
       << "<es_hsVal species=\"Species_2\">0.0023</es_hsVal>"
       << "<es_hsVal species=\"Species_3\">0.0098</es_hsVal>"
       << "<es_hsVal species=\"Species_4\">0.012</es_hsVal>"
       << "</es_highSlope>"
       << "<es_lightHeight>2</es_lightHeight>"
       << "<li_lightExtinctionCoefficient>"
       << "<li_lecVal species=\"Species_1\">0.2</li_lecVal>"
       << "<li_lecVal species=\"Species_2\">0.2</li_lecVal>"
       << "<li_lecVal species=\"Species_3\">0.87</li_lecVal>"
       << "<li_lecVal species=\"Species_4\">0</li_lecVal>"
       << "<li_lecVal species=\"Species_5\">0</li_lecVal>"
       << "</li_lightExtinctionCoefficient>"
       << "<li_beamFractGlobalRad>0.5</li_beamFractGlobalRad>"
       << "<li_clearSkyTransCoeff>0.65</li_clearSkyTransCoeff>"
       << "<li_julianDayGrowthStarts>105</li_julianDayGrowthStarts>"
       << "<li_julianDayGrowthEnds>258</li_julianDayGrowthEnds>"
       << "<li_minSunAngle>0.785</li_minSunAngle>"
       << "<li_numAltGrids>12</li_numAltGrids>"
       << "<li_numAziGrids>-18</li_numAziGrids>"
       << "</LightDependentSeedSurvival2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
//  WriteXMLErrorFile7()
////////////////////////////////////////////////////////////////////////////
const char* clTestLightDepSeedSurvival::WriteXMLErrorFile7() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  WriteCommonStuff(oOut);

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
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>NonSpatialDisperse</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>4</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StormLightDependentSeedSurvival</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>5</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Establishment</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>6</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_3\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<Storm1>"
       << "<st_s1ReturnInterval>1000</st_s1ReturnInterval>"
       << "<st_s2ReturnInterval>1000</st_s2ReturnInterval>"
       << "<st_s3ReturnInterval>1000</st_s3ReturnInterval>"
       << "<st_s4ReturnInterval>1000</st_s4ReturnInterval>"
       << "<st_s5ReturnInterval>1000</st_s5ReturnInterval>"
       << "<st_s6ReturnInterval>1000</st_s6ReturnInterval>"
       << "<st_s7ReturnInterval>1000</st_s7ReturnInterval>"
       << "<st_s8ReturnInterval>1000</st_s8ReturnInterval>"
       << "<st_s9ReturnInterval>1000</st_s9ReturnInterval>"
       << "<st_s10ReturnInterval>1000</st_s10ReturnInterval>"
       << "<st_susceptibility>1</st_susceptibility>"
       << "<st_stochasticity>0</st_stochasticity>"
       << "<st_stmSSTPeriod>1</st_stmSSTPeriod>"
       << "<st_stmSineD>0</st_stmSineD>"
       << "<st_stmSineF>1</st_stmSineF>"
       << "<st_stmSineG>1</st_stmSineG>"
       << "<st_stmTrendSlopeM>0</st_stmTrendSlopeM>"
       << "<st_stmTrendInterceptI>1</st_stmTrendInterceptI>"
       << "</Storm1>"
       << "<StormDamageApplier2>"
       << "<st_minDBH>"
       << "<st_mdVal species=\"Species_1\">5</st_mdVal>"
       << "<st_mdVal species=\"Species_2\">6</st_mdVal>"
       << "<st_mdVal species=\"Species_3\">5</st_mdVal>"
       << "<st_mdVal species=\"Species_4\">6</st_mdVal>"
       << "</st_minDBH>"
       << "<st_stmDmgInterceptMed>"
       << "<st_sdimVal species=\"Species_1\">2.1789601</st_sdimVal>"
       << "<st_sdimVal species=\"Species_2\">2.475987</st_sdimVal>"
       << "<st_sdimVal species=\"Species_3\">2.1789601</st_sdimVal>"
       << "<st_sdimVal species=\"Species_4\">2.475987</st_sdimVal>"
       << "</st_stmDmgInterceptMed>"
       << "<st_stmDmgInterceptFull>"
       << "<st_sdifVal species=\"Species_1\">3.6334169</st_sdifVal>"
       << "<st_sdifVal species=\"Species_2\">3.6331242</st_sdifVal>"
       << "<st_sdifVal species=\"Species_3\">3.6334169</st_sdifVal>"
       << "<st_sdifVal species=\"Species_4\">3.6331242</st_sdifVal>"
       << "</st_stmDmgInterceptFull>"
       << "<st_stmIntensityCoeff>"
       << "<st_sicVal species=\"Species_1\">-0.3545352</st_sicVal>"
       << "<st_sicVal species=\"Species_2\">-1.2289105</st_sicVal>"
       << "<st_sicVal species=\"Species_3\">-0.3545352</st_sicVal>"
       << "<st_sicVal species=\"Species_4\">-1.2289105</st_sicVal>"
       << "</st_stmIntensityCoeff>"
       << "<st_stmDBHCoeff>"
       << "<st_sdcVal species=\"Species_1\">0.8280319</st_sdcVal>"
       << "<st_sdcVal species=\"Species_2\">0.3282479</st_sdcVal>"
       << "<st_sdcVal species=\"Species_3\">0.8280319</st_sdcVal>"
       << "<st_sdcVal species=\"Species_4\">0.3282479</st_sdcVal>"
       << "</st_stmDBHCoeff>"
       << "<st_stmPropDieMedDmg>"
       << "<st_spdmdVal species=\"Species_1\">0</st_spdmdVal>"
       << "<st_spdmdVal species=\"Species_2\">0</st_spdmdVal>"
       << "<st_spdmdVal species=\"Species_3\">0</st_spdmdVal>"
       << "<st_spdmdVal species=\"Species_4\">0</st_spdmdVal>"
       << "</st_stmPropDieMedDmg>"
       << "<st_stmPropDieFullDmg>"
       << "<st_spdfdVal species=\"Species_1\">0</st_spdfdVal>"
       << "<st_spdfdVal species=\"Species_2\">0</st_spdfdVal>"
       << "<st_spdfdVal species=\"Species_3\">0</st_spdfdVal>"
       << "<st_spdfdVal species=\"Species_4\">0</st_spdfdVal>"
       << "</st_stmPropDieFullDmg>"
       << "<st_stmPropTipUpFullDmg>"
       << "<st_sptufdVal species=\"Species_1\">0</st_sptufdVal>"
       << "<st_sptufdVal species=\"Species_2\">0</st_sptufdVal>"
       << "<st_sptufdVal species=\"Species_3\">0</st_sptufdVal>"
       << "<st_sptufdVal species=\"Species_4\">0</st_sptufdVal>"
       << "</st_stmPropTipUpFullDmg>"
       << "<st_numYearsStormSnags>0</st_numYearsStormSnags>"
       << "<st_numYearsToHeal>4</st_numYearsToHeal>"
       << "</StormDamageApplier2>"
       << "<StochasticMortality3>"
       << "<mo_stochasticMortRate>"
       << "<mo_smrVal species=\"Species_1\">0.0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_2\">0.0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_3\">0.0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_4\">0.0</mo_smrVal>"
       << "</mo_stochasticMortRate>"
       << "</StochasticMortality3>";

  oOut << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "<NonSpatialDisperse4>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_4\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_2\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_3\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_nonSpatialSlopeOfLambda>"
       << "<di_nssolVal species=\"Species_4\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_2\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_3\">0</di_nssolVal>"
       << "</di_nonSpatialSlopeOfLambda>"
       << "<di_nonSpatialInterceptOfLambda>"
       << "<di_nsiolVal species=\"Species_4\">0</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_2\">0</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_3\">0</di_nsiolVal>"
       << "</di_nonSpatialInterceptOfLambda>"
       << "</NonSpatialDisperse4>";

  oOut << "<LightDependentSeedSurvival5>"
       << "<es_optimumGLI>"
       << "<es_ogVal species=\"Species_2\">23</es_ogVal>"
       << "<es_ogVal species=\"Species_3\">87</es_ogVal>"
       << "<es_ogVal species=\"Species_4\">55.66</es_ogVal>"
       << "</es_optimumGLI>"
       << "<es_lowSlope>"
       << "<es_lsVal species=\"Species_2\">0.034</es_lsVal>"
       << "<es_lsVal species=\"Species_3\">0.0098</es_lsVal>"
       << "<es_lsVal species=\"Species_4\">0.011</es_lsVal>"
       << "</es_lowSlope>"
       << "<es_highSlope>"
       << "<es_hsVal species=\"Species_2\">0.0023</es_hsVal>"
       << "<es_hsVal species=\"Species_3\">0.0098</es_hsVal>"
       << "<es_hsVal species=\"Species_4\">0.012</es_hsVal>"
       << "</es_highSlope>"
       << "</LightDependentSeedSurvival5>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}


/////////////////////////////////////////////////////////////////////////////
//  WriteCommonStuff()
/////////////////////////////////////////////////////////////////////////////
void clTestLightDepSeedSurvival::WriteCommonStuff( std::fstream &oOut )
{
  using namespace std;
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>500.0</plot_lenX>"
       << "<plot_lenY>100.0</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\" />"
       << "<tr_species speciesName=\"Species_2\" />"
       << "<tr_species speciesName=\"Species_3\" />"
       << "<tr_species speciesName=\"Species_4\" />"
       << "<tr_species speciesName=\"Species_5\" />"
       << "</tr_speciesList>"
       << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_2\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_3\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_4\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_5\">10.0</tr_madVal>"
       << "</tr_minAdultDBH>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_3\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_4\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_5\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>"
       << "</trees>"
       << "<allometry>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_2\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_3\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_4\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_5\">39.48</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_2\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_3\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_4\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_5\">0.0549</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_3\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_4\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_5\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_3\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_4\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_5\">0.8008</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_3\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_4\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_5\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.8</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.8</tr_sachVal>"
       << "<tr_sachVal species=\"Species_3\">0.8</tr_sachVal>"
       << "<tr_sachVal species=\"Species_4\">0.8</tr_sachVal>"
       << "<tr_sachVal species=\"Species_5\">0.8</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_3\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_4\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_5\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_2\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_3\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_4\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_5\">0.03418</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_2\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_3\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_4\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_5\">0.0299</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
       << "<tr_whatSeedlingHeightDiam>"
       << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_2\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_3\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_4\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_5\">0</tr_wsehdVal>"
       << "</tr_whatSeedlingHeightDiam>"
       << "<tr_whatSaplingHeightDiam>"
       << "<tr_wsahdVal species=\"Species_1\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_2\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_3\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_4\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_5\">0</tr_wsahdVal>"
       << "</tr_whatSaplingHeightDiam>"
       << "<tr_whatAdultHeightDiam>"
       << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_2\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_3\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_4\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_5\">0</tr_wahdVal>"
       << "</tr_whatAdultHeightDiam>"
       << "<tr_whatAdultCrownRadDiam>"
       << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_2\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_3\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_4\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_5\">0</tr_wacrdVal>"
       << "</tr_whatAdultCrownRadDiam>"
       << "<tr_whatAdultCrownHeightHeight>"
       << "<tr_wachhVal species=\"Species_1\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_2\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_3\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_4\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_5\">0</tr_wachhVal>"
       << "</tr_whatAdultCrownHeightHeight>"
       << "<tr_whatSaplingCrownRadDiam>"
       << "<tr_wscrdVal species=\"Species_1\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_2\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_3\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_4\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_5\">0</tr_wscrdVal>"
       << "</tr_whatSaplingCrownRadDiam>"
       << "<tr_whatSaplingCrownHeightHeight>"
       << "<tr_wschhVal species=\"Species_1\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_2\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_3\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_4\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_5\">0</tr_wschhVal>"
       << "</tr_whatSaplingCrownHeightHeight>"
       << "</allometry>";
}
