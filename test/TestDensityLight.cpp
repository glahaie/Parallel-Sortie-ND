//---------------------------------------------------------------------------
// TestDensityLight.cpp
//---------------------------------------------------------------------------
#include "TestDensityLight.h"
#include "Grid.h"
#include "SimManager.h"
#include "BehaviorBase.h"
#include "TreePopulation.h"
#include "DensityLight.h"
#include <math.h>
#include <fstream>

/////////////////////////////////////////////////////////////////////////////
//  TestDensityLight()
/////////////////////////////////////////////////////////////////////////////
void clTestDensityLight::TestDensityLight()
{

  clSimManager * p_oSimManager = new clSimManager(3, 3, "");

  TestErrorProcessing(p_oSimManager);
  NormalProcessingRun1(p_oSimManager);
  NormalProcessingRun2(p_oSimManager);
  NormalProcessingRun3(p_oSimManager);
  NormalProcessingRun4(p_oSimManager);

  //Clean up
  delete p_oSimManager;
}

////////////////////////////////////////////////////////////////////////////
//  TestErrorProcessing()
////////////////////////////////////////////////////////////////////////////
void clTestDensityLight::TestErrorProcessing( clSimManager * p_oSimManager )
{

  try
  {
    p_oSimManager->ReadFile( WriteXMLErrorFile1() );
    CppUnit::Asserter::fail( "TestDensityLight error processing didn't catch error for WriteXMLErrorFile1." );
  }
  catch ( modelErr& err )
  {
    if ( strstr( err.cFunction, "clDensityLight::GetData" ) == NULL )
    {
      CppUnit::Asserter::fail( "TestDensityLight error processing caught wrong error for WriteXMLErrorFile1." );
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile( WriteXMLErrorFile2() );
    CppUnit::Asserter::fail( "TestDensityLight error processing didn't catch error for WriteXMLErrorFile2." );
  }
  catch ( modelErr& err )
  {
    if ( strstr( err.cFunction, "clDensityLight::GetData" ) == NULL )
    {
      CppUnit::Asserter::fail( "TestDensityLight error processing caught wrong error for WriteXMLErrorFile2." );
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile( WriteXMLErrorFile3() );
    CppUnit::Asserter::fail( "TestDensityLight error processing didn't catch error for WriteXMLErrorFile3." );
  }
  catch ( modelErr& err )
  {
    if ( strstr( err.cFunction, "clDensityLight::GetData" ) == NULL )
    {
      CppUnit::Asserter::fail( "TestDensityLight error processing caught wrong error for WriteXMLErrorFile3." );
    }
    ;
  }
}

/////////////////////////////////////////////////////////////////////////////
// NormalProcessingRun1()
/////////////////////////////////////////////////////////////////////////////
void clTestDensityLight::NormalProcessingRun1(clSimManager *p_oSimManager)
{
  clTreePopulation *p_oPop;
  clBehaviorBase *p_oTemp;
  clDensityLight *p_oLightBeh;
  clGrid *p_oLightGrid;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree1, *p_oTree2, *p_oTree3, *p_oTree4, *p_oTree5, *p_oTree6,
         *p_oTree7, *p_oTree8, *p_oTree9, *p_oTree10, *p_oTree11, *p_oTree12;
  float fActualLight, fExpectedLight,
        fLight1, fLight2, fLight3, fLight4;
  int iLightCode, iCountCode, iExpectedCount, iActualCount, iX, iY, iNumXCells,
      iNumYCells;


  //Feed our file to the sim manager
  p_oSimManager->ReadFile(WriteXMLFile1());
  p_oPop = (clTreePopulation*) p_oSimManager->GetPopulationObject("treepopulation");

  //Add trees to three grid cells
  //Grid cell 0, 1 - one tree
  p_oTree1 = p_oPop->CreateTree( 4, 12, 1, clTreePopulation::adult, 10 );

  //Grid cell 0, 2 - five trees
  p_oTree2 = p_oPop->CreateTree( 4, 20, 0, clTreePopulation::adult, 11 );
  p_oTree3 = p_oPop->CreateTree( 4, 20, 1, clTreePopulation::adult, 11 );
  p_oTree4 = p_oPop->CreateTree( 4, 20, 0, clTreePopulation::adult, 11 );
  p_oTree5 = p_oPop->CreateTree( 4, 20, 1, clTreePopulation::adult, 11 );
  p_oTree6 = p_oPop->CreateTree( 4, 20, 0, clTreePopulation::adult, 11 );

  //Grid cell 0, 3 - six trees less than the minimum DBH
  p_oTree7 = p_oPop->CreateTree( 4, 28, 1, clTreePopulation::sapling, 8 );
  p_oTree8 = p_oPop->CreateTree( 4, 28, 0, clTreePopulation::sapling, 8 );
  p_oTree9 = p_oPop->CreateTree( 4, 28, 1, clTreePopulation::sapling, 8 );
  p_oTree10 = p_oPop->CreateTree( 4, 28, 0, clTreePopulation::sapling, 8 );
  p_oTree11 = p_oPop->CreateTree( 4, 28, 1, clTreePopulation::sapling, 8 );
  p_oTree12 = p_oPop->CreateTree( 4, 28, 0, clTreePopulation::sapling, 8 );

  //Check the mean GLI calculations directly for 3 values
  p_oTemp = p_oSimManager->GetBehaviorObject("densitylightshell");
  p_oLightBeh = dynamic_cast<clDensityLight*>(p_oTemp);

  fExpectedLight = 12.40809;
  fActualLight = p_oLightBeh->GetMeanGLI(0);
  CPPUNIT_ASSERT(fabs(fExpectedLight - fActualLight) < 0.0001);

  fExpectedLight = 12.29169285;
  fActualLight = p_oLightBeh->GetMeanGLI(1);
  CPPUNIT_ASSERT(fabs(fExpectedLight - fActualLight) < 0.0001);

  fExpectedLight = 10.24114228;
  fActualLight = p_oLightBeh->GetMeanGLI(5);
  CPPUNIT_ASSERT(fabs(fExpectedLight - fActualLight) < 0.0001);

  fExpectedLight = 0.178092533;
  fActualLight = p_oLightBeh->GetMeanGLI(100);
  CPPUNIT_ASSERT(fabs(fExpectedLight - fActualLight) < 0.0001);

  //Run one timestep
  p_oSimManager->RunSim(1);

  p_oLightGrid = p_oSimManager->GetGridObject("Density Light");
  iLightCode = p_oLightGrid->GetFloatDataCode("Light");
  CPPUNIT_ASSERT(-1 < iLightCode);
  iCountCode = p_oLightGrid->GetIntDataCode("Count");
  CPPUNIT_ASSERT(-1 < iCountCode);

  //Check to make sure the density counts are correct
  //Grid 0, 0
  iExpectedCount = 0;
  p_oLightGrid->GetValueOfCell(0, 0, iCountCode, &iActualCount);
  CPPUNIT_ASSERT(iActualCount == iExpectedCount);

  //Grid 0, 1
  iExpectedCount = 1;
  p_oLightGrid->GetValueOfCell(0, 1, iCountCode, &iActualCount);
  CPPUNIT_ASSERT(iActualCount == iExpectedCount);

  //Grid 0, 2
  iExpectedCount = 5;
  p_oLightGrid->GetValueOfCell(0, 2, iCountCode, &iActualCount);
  CPPUNIT_ASSERT(iActualCount == iExpectedCount);

  //Grid 0, 3
  iExpectedCount = 0;
  p_oLightGrid->GetValueOfCell(0, 3, iCountCode, &iActualCount);
  CPPUNIT_ASSERT(iActualCount == iExpectedCount);

  //Make sure that all cells got a light level
  iNumXCells = p_oLightGrid->GetNumberXCells();
  iNumYCells = p_oLightGrid->GetNumberYCells();
  for (iX = 0; iX < iNumXCells; iX++) {
    for (iY = 0; iY < iNumYCells; iY++) {
      p_oLightGrid->GetValueOfCell(iX, iY, iLightCode, &fActualLight);
      CPPUNIT_ASSERT(fActualLight > 0);
    }
  }

  //Save the light values for the four grid cells to check for density changes
  p_oLightGrid->GetValueOfCell(0, 0, iLightCode, &fLight1);
  p_oLightGrid->GetValueOfCell(0, 1, iLightCode, &fLight2);
  p_oLightGrid->GetValueOfCell(0, 2, iLightCode, &fLight3);
  p_oLightGrid->GetValueOfCell(0, 3, iLightCode, &fLight4);

  //Make sure that the species two trees got light values matching their
  //grids
  p_oTree1->GetValue(p_oPop->GetFloatDataCode("Light", p_oTree1->GetSpecies(), p_oTree1->GetType()), &fActualLight);
  CPPUNIT_ASSERT(fActualLight == fLight2);
  CPPUNIT_ASSERT(p_oPop->GetFloatDataCode("Light", p_oTree2->GetSpecies(), p_oTree2->GetType()) == -1);
  p_oTree3->GetValue(p_oPop->GetFloatDataCode("Light", p_oTree3->GetSpecies(), p_oTree3->GetType()), &fActualLight);
  CPPUNIT_ASSERT(fActualLight == fLight3);
  CPPUNIT_ASSERT(p_oPop->GetFloatDataCode("Light", p_oTree4->GetSpecies(), p_oTree4->GetType()) == -1);
  p_oTree5->GetValue(p_oPop->GetFloatDataCode("Light", p_oTree5->GetSpecies(), p_oTree5->GetType()), &fActualLight);
  CPPUNIT_ASSERT(fActualLight == fLight3);
  CPPUNIT_ASSERT(p_oPop->GetFloatDataCode("Light", p_oTree6->GetSpecies(), p_oTree6->GetType()) == -1);
  p_oTree7->GetValue(p_oPop->GetFloatDataCode("Light", p_oTree7->GetSpecies(), p_oTree7->GetType()), &fActualLight);
  CPPUNIT_ASSERT(fActualLight == fLight4);
  CPPUNIT_ASSERT(p_oPop->GetFloatDataCode("Light", p_oTree8->GetSpecies(), p_oTree8->GetType()) == -1);
  p_oTree9->GetValue(p_oPop->GetFloatDataCode("Light", p_oTree9->GetSpecies(), p_oTree9->GetType()), &fActualLight);
  CPPUNIT_ASSERT(fActualLight == fLight4);
  CPPUNIT_ASSERT(p_oPop->GetFloatDataCode("Light", p_oTree10->GetSpecies(), p_oTree10->GetType()) == -1);
  p_oTree11->GetValue(p_oPop->GetFloatDataCode("Light", p_oTree11->GetSpecies(), p_oTree11->GetType()), &fActualLight);
  CPPUNIT_ASSERT(fActualLight == fLight4);
  CPPUNIT_ASSERT(p_oPop->GetFloatDataCode("Light", p_oTree12->GetSpecies(), p_oTree12->GetType()) == -1);


  //Change the number of trees to trigger density changes
  //It's easier to just kill everything and start over
  p_oAllTrees = p_oPop->Find("all");
  p_oTree1 = p_oAllTrees->NextTree();
  while (p_oTree1) {
    p_oPop->KillTree(p_oTree1, remove_tree);
    p_oTree1 = p_oAllTrees->NextTree();
  }

  //Grid cell 0, 0 - one tree
  p_oTree1 = p_oPop->CreateTree( 4, 4, 1, clTreePopulation::adult, 18 );

  //Grid cell 0, 1 - one tree
  p_oTree2 = p_oPop->CreateTree( 4, 12, 0, clTreePopulation::adult, 10 );

  //Grid cell 0, 2 - two trees
  p_oTree3 = p_oPop->CreateTree( 4, 20, 1, clTreePopulation::adult, 11 );
  p_oTree4 = p_oPop->CreateTree( 4, 20, 0, clTreePopulation::adult, 11 );

  //Grid cell 0, 3 - six trees less than the minimum DBH and four greater
  p_oTree5 = p_oPop->CreateTree( 4, 28, 1, clTreePopulation::adult, 8 );
  p_oTree6 = p_oPop->CreateTree( 4, 28, 0, clTreePopulation::adult, 8 );
  p_oTree7 = p_oPop->CreateTree( 4, 28, 1, clTreePopulation::adult, 8 );
  p_oTree8 = p_oPop->CreateTree( 4, 28, 0, clTreePopulation::adult, 8 );
  p_oTree9 = p_oPop->CreateTree( 4, 28, 1, clTreePopulation::adult, 8 );
  p_oTree10 = p_oPop->CreateTree( 4, 28, 0, clTreePopulation::adult, 8 );
  p_oTree11 = p_oPop->CreateTree( 4, 28, 1, clTreePopulation::adult, 30 );
  p_oTree12 = p_oPop->CreateTree( 4, 28, 0, clTreePopulation::adult, 30 );
  p_oPop->CreateTree( 4, 28, 0, clTreePopulation::adult, 30 );
  p_oPop->CreateTree( 4, 28, 0, clTreePopulation::adult, 30 );

  //Run another timestep
  p_oSimManager->RunSim(1);

  //Check to make sure that the densities are correct
  //Grid 0, 0
  iExpectedCount = 0;
  p_oLightGrid->GetValueOfCell(0, 0, iCountCode, &iActualCount);
  CPPUNIT_ASSERT(iExpectedCount == iActualCount);

  //Grid 0, 1
  iExpectedCount = 1;
  p_oLightGrid->GetValueOfCell(0, 1, iCountCode, &iActualCount);
  CPPUNIT_ASSERT(iExpectedCount == iActualCount);

  //Grid 0, 2
  iExpectedCount = 2;
  p_oLightGrid->GetValueOfCell(0, 2, iCountCode, &iActualCount);
  CPPUNIT_ASSERT(iExpectedCount == iActualCount);

  //Grid 0, 3
  iExpectedCount = 4;
  p_oLightGrid->GetValueOfCell(0, 3, iCountCode, &iActualCount);
  CPPUNIT_ASSERT(iExpectedCount == iActualCount);

  //Make sure that the first two grid cells have the same light values and
  //the last two change
  p_oLightGrid->GetValueOfCell(0, 0, iLightCode, &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fLight1) < 0.00001);
  p_oLightGrid->GetValueOfCell(0, 1, iLightCode, &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fLight2) < 0.00001);
  p_oLightGrid->GetValueOfCell(0, 2, iLightCode, &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fLight3) > 0.1);
  p_oLightGrid->GetValueOfCell(0, 3, iLightCode, &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fLight4) > 0.1);

  //Check tree values
  p_oLightGrid->GetValueOfCell(0, 0, iLightCode, &fLight1);
  p_oLightGrid->GetValueOfCell(0, 1, iLightCode, &fLight2);
  p_oLightGrid->GetValueOfCell(0, 2, iLightCode, &fLight3);
  p_oLightGrid->GetValueOfCell(0, 3, iLightCode, &fLight4);

  p_oTree1->GetValue(p_oPop->GetFloatDataCode("Light", p_oTree1->GetSpecies(), p_oTree1->GetType()), &fActualLight);
  CPPUNIT_ASSERT(fActualLight == fLight1);
  CPPUNIT_ASSERT(p_oPop->GetFloatDataCode("Light", p_oTree2->GetSpecies(), p_oTree2->GetType()) == -1);
  p_oTree3->GetValue(p_oPop->GetFloatDataCode("Light", p_oTree3->GetSpecies(), p_oTree3->GetType()), &fActualLight);
  CPPUNIT_ASSERT(fActualLight == fLight3);
  CPPUNIT_ASSERT(p_oPop->GetFloatDataCode("Light", p_oTree4->GetSpecies(), p_oTree4->GetType()) == -1);
  p_oTree5->GetValue(p_oPop->GetFloatDataCode("Light", p_oTree5->GetSpecies(), p_oTree5->GetType()), &fActualLight);
  CPPUNIT_ASSERT(fActualLight == fLight4);
  CPPUNIT_ASSERT(p_oPop->GetFloatDataCode("Light", p_oTree6->GetSpecies(), p_oTree6->GetType()) == -1);
  p_oTree7->GetValue(p_oPop->GetFloatDataCode("Light", p_oTree7->GetSpecies(), p_oTree7->GetType()), &fActualLight);
  CPPUNIT_ASSERT(fActualLight == fLight4);
  CPPUNIT_ASSERT(p_oPop->GetFloatDataCode("Light", p_oTree8->GetSpecies(), p_oTree8->GetType()) == -1);
  p_oTree9->GetValue(p_oPop->GetFloatDataCode("Light", p_oTree9->GetSpecies(), p_oTree9->GetType()), &fActualLight);
  CPPUNIT_ASSERT(fActualLight == fLight4);
  CPPUNIT_ASSERT(p_oPop->GetFloatDataCode("Light", p_oTree10->GetSpecies(), p_oTree10->GetType()) == -1);
  p_oTree11->GetValue(p_oPop->GetFloatDataCode("Light", p_oTree11->GetSpecies(), p_oTree11->GetType()), &fActualLight);
  CPPUNIT_ASSERT(fActualLight == fLight4);
  CPPUNIT_ASSERT(p_oPop->GetFloatDataCode("Light", p_oTree12->GetSpecies(), p_oTree12->GetType()) == -1);
}

/////////////////////////////////////////////////////////////////////////////
// NormalProcessingRun2()
/////////////////////////////////////////////////////////////////////////////
void clTestDensityLight::NormalProcessingRun2(clSimManager *p_oSimManager)
{
  clBehaviorBase *p_oTemp;
  clDensityLight *p_oLightBeh;
  float fActualLight, fExpectedLight;

  //Feed our file to the sim manager
  p_oSimManager->ReadFile(WriteXMLFile2());

  //Check the mean GLI calculations directly for 4 values
  p_oTemp = p_oSimManager->GetBehaviorObject("densitylightshell");
  p_oLightBeh = dynamic_cast<clDensityLight*>(p_oTemp);

  fExpectedLight = 12.40809;
  fActualLight = p_oLightBeh->GetMeanGLI(0);
  CPPUNIT_ASSERT(fabs(fExpectedLight - fActualLight) < 0.0001);

  fExpectedLight = 15.37709371;
  fActualLight = p_oLightBeh->GetMeanGLI(1);
  CPPUNIT_ASSERT(fabs(fExpectedLight - fActualLight) < 0.0001);

  fExpectedLight = 100;
  fActualLight = p_oLightBeh->GetMeanGLI(5);
  CPPUNIT_ASSERT(fabs(fExpectedLight - fActualLight) < 0.0001);

  fExpectedLight = 0;
  fActualLight = p_oLightBeh->GetMeanGLI(6);
  CPPUNIT_ASSERT(fabs(fExpectedLight - fActualLight) < 0.0001);
}

/////////////////////////////////////////////////////////////////////////////
// NormalProcessingRun3()
/////////////////////////////////////////////////////////////////////////////
void clTestDensityLight::NormalProcessingRun3(clSimManager *p_oSimManager)
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
  p_oLightGrid = p_oSimManager->GetGridObject("Density Light");
  iLightCode = p_oLightGrid->GetFloatDataCode("Light");
  CPPUNIT_ASSERT(-1 < iLightCode);
  CPPUNIT_ASSERT(10 == p_oLightGrid->GetLengthXCells());
  CPPUNIT_ASSERT(10 == p_oLightGrid->GetLengthYCells());

  //Put 2 trees in each grid cell
  p_oPop = (clTreePopulation*) p_oSimManager->GetPopulationObject("treepopulation");
  for (iX = 0; iX < p_oLightGrid->GetNumberXCells(); iX++) {
    for (iY = 0; iY < p_oLightGrid->GetNumberYCells(); iY++) {
      p_oPop->CreateTree( (iX * 10) + 5, (iY * 10) + 5, 0, clTreePopulation::adult, 30 );
      p_oPop->CreateTree( (iX * 10) + 5, (iY * 10) + 5, 0, clTreePopulation::adult, 30 );
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
  oOut.open( "Density Light Distribution.txt", ios::out | ios::trunc );
  oOut << "Density Light Distribution\n";
  oOut << "Number of grid values falling into each GLI bucket (density = 2):\n";
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

  oOut << "Number of tree values falling into each GLI bucket (density = 2):\n";
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
void clTestDensityLight::NormalProcessingRun4(clSimManager *p_oSimManager)
{
  clGrid *p_oLightGrid;
  float fActualLight, fExpectedLight = 95;
  int iLightCode, iCountCode, iExpectedCount = 1, iActualCount, iX, iY,
      iNumXCells, iNumYCells;


  //Feed our file to the sim manager
  p_oSimManager->ReadFile(WriteXMLFile4());

  //Run one timestep
  p_oSimManager->RunSim(1);

  p_oLightGrid = p_oSimManager->GetGridObject("Density Light");
  iLightCode = p_oLightGrid->GetFloatDataCode("Light");
  CPPUNIT_ASSERT(-1 < iLightCode);
  iCountCode = p_oLightGrid->GetIntDataCode("Count");
  CPPUNIT_ASSERT(-1 < iCountCode);

  //Make sure that all cells got a light level
  iNumXCells = p_oLightGrid->GetNumberXCells();
  iNumYCells = p_oLightGrid->GetNumberYCells();
  for (iX = 0; iX < iNumXCells; iX++) {
    for (iY = 0; iY < iNumYCells; iY++) {
      p_oLightGrid->GetValueOfCell(iX, iY, iLightCode, &fActualLight);
      p_oLightGrid->GetValueOfCell(iX, iY, iCountCode, &iActualCount);
      if (fExpectedLight != fActualLight)
        fExpectedLight = fExpectedLight;
      CPPUNIT_ASSERT(fExpectedLight == fActualLight);
      CPPUNIT_ASSERT(iExpectedCount == iActualCount);
    }
  }
}

/////////////////////////////////////////////////////////////////////////////
//  WriteXMLFile1()
/////////////////////////////////////////////////////////////////////////////
const char* clTestDensityLight::WriteXMLFile1()
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
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>";

  WriteCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>Density Light</behaviorName>"
       << "<applyTo species=\"Species_2\" type=\"Adult\" />"
       << "<applyTo species=\"Species_2\" type=\"Sapling\" />"
       << "<version>1</version>"
       << "</behavior>"
       << "</behaviorList>"
       << "<lightOther>"
       << "<li_densLightA>12.40809</li_densLightA>"
       << "<li_densLightB>1.930225</li_densLightB>"
       << "<li_densLightC>11.17921</li_densLightC>"
       << "<li_densLightSigma>1.078382</li_densLightSigma>"
       << "<li_densLightChangeThreshold>2</li_densLightChangeThreshold>"
       << "<li_densLightMinDBH>10</li_densLightMinDBH>"
       << "</lightOther>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
//  WriteXMLFile2()
/////////////////////////////////////////////////////////////////////////////
const char* clTestDensityLight::WriteXMLFile2()
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
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>";

  WriteCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>Density Light</behaviorName>"
       << "<version>1</version>"
       << "<applyTo species=\"Species_2\" type=\"Adult\" />"
       << "<applyTo species=\"Species_2\" type=\"Sapling\" />"
       << "</behavior>"
       << "</behaviorList>"
       << "<lightOther>"
       << "<li_densLightA>12.40809</li_densLightA>"
       << "<li_densLightB>1</li_densLightB>"
       << "<li_densLightC>-5.17921</li_densLightC>"
       << "<li_densLightSigma>1.078382</li_densLightSigma>"
       << "<li_densLightChangeThreshold>2</li_densLightChangeThreshold>"
       << "<li_densLightMinDBH>10</li_densLightMinDBH>"
       << "</lightOther>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
//  WriteXMLFile3()
/////////////////////////////////////////////////////////////////////////////
const char* clTestDensityLight::WriteXMLFile3()
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
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>";

  WriteCommonStuff(oOut);

  oOut << "<grid gridName=\"Density Light\">"
       << "<ma_floatCodes>"
       << "<ma_floatCode label=\"Light\">0</ma_floatCode>"
       << "</ma_floatCodes>"
       << "<ma_intCodes>"
       << "<ma_intCode label=\"Count\">0</ma_intCode>"
       << "</ma_intCodes>"
       << "<ma_lengthXCells>10</ma_lengthXCells>"
       << "<ma_lengthYCells>10</ma_lengthYCells>"
       << "</grid>";

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>Density Light</behaviorName>"
       << "<version>1</version>"
       << "<applyTo species=\"Species_2\" type=\"Adult\" />"
       << "<applyTo species=\"Species_2\" type=\"Sapling\" />"
       << "<applyTo species=\"Species_1\" type=\"Adult\" />"
       << "<applyTo species=\"Species_1\" type=\"Sapling\" />"
       << "</behavior>"
       << "</behaviorList>"
       << "<lightOther>"
       << "<li_densLightA>12.40809</li_densLightA>"
       << "<li_densLightB>1.930225</li_densLightB>"
       << "<li_densLightC>11.17921</li_densLightC>"
       << "<li_densLightSigma>1.078382</li_densLightSigma>"
       << "<li_densLightChangeThreshold>2</li_densLightChangeThreshold>"
       << "<li_densLightMinDBH>10</li_densLightMinDBH>"
       << "</lightOther>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
//  WriteXMLFile4()
/////////////////////////////////////////////////////////////////////////////
const char* clTestDensityLight::WriteXMLFile4()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";
  float fLight = 95;
  int iX, iY, iNumXCells = 10, iNumYCells = 10, iCount = 1;

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
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>";

  WriteCommonStuff(oOut);

  oOut << "<grid gridName=\"Density Light\">"
       << "<ma_floatCodes>"
       << "<ma_floatCode label=\"Light\">0</ma_floatCode>"
       << "</ma_floatCodes>"
       << "<ma_intCodes>"
       << "<ma_intCode label=\"Count\">0</ma_intCode>"
       << "</ma_intCodes>"
       << "<ma_lengthXCells>10</ma_lengthXCells>"
       << "<ma_lengthYCells>10</ma_lengthYCells>";

  for (iX = 0; iX < iNumXCells; iX++) {
    for (iY = 0; iY < iNumYCells; iY++) {
      oOut << "<ma_v x=\"" << iX << "\" y=\"" << iY << "\">"
           << "<fl c=\"0\">" << fLight << "</fl>"
           << "<int c=\"0\">" << iCount << "</int>"
           << "</ma_v>";
    }
  }

  oOut << "</grid>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>Density Light</behaviorName>"
       << "<version>1</version>"
       << "</behavior>"
       << "</behaviorList>"
       << "<lightOther>"
       << "<li_densLightA>12.40809</li_densLightA>"
       << "<li_densLightB>1.930225</li_densLightB>"
       << "<li_densLightC>11.17921</li_densLightC>"
       << "<li_densLightSigma>1.078382</li_densLightSigma>"
       << "<li_densLightChangeThreshold>2</li_densLightChangeThreshold>"
       << "<li_densLightMinDBH>10</li_densLightMinDBH>"
       << "</lightOther>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
//  WriteXMLErrorFile1()
/////////////////////////////////////////////////////////////////////////////
const char* clTestDensityLight::WriteXMLErrorFile1()
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
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>";

  WriteCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>Density Light</behaviorName>"
       << "<version>1</version>"
       << "</behavior>"
       << "</behaviorList>"
       << "<lightOther>"
       << "<li_densLightA>12.40809</li_densLightA>"
       << "<li_densLightB>1.930225</li_densLightB>"
       << "<li_densLightC>0</li_densLightC>"
       << "<li_densLightSigma>1.078382</li_densLightSigma>"
       << "<li_densLightChangeThreshold>2</li_densLightChangeThreshold>"
       << "<li_densLightMinDBH>10</li_densLightMinDBH>"
       << "</lightOther>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
//  WriteXMLErrorFile2()
/////////////////////////////////////////////////////////////////////////////
const char* clTestDensityLight::WriteXMLErrorFile2()
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
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>";

  WriteCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>Density Light</behaviorName>"
       << "<version>1</version>"
       << "</behavior>"
       << "</behaviorList>"
       << "<lightOther>"
       << "<li_densLightA>12.40809</li_densLightA>"
       << "<li_densLightB>1.930225</li_densLightB>"
       << "<li_densLightC>11.17921</li_densLightC>"
       << "<li_densLightSigma>1.078382</li_densLightSigma>"
       << "<li_densLightChangeThreshold>-2</li_densLightChangeThreshold>"
       << "<li_densLightMinDBH>10</li_densLightMinDBH>"
       << "</lightOther>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
//  WriteXMLErrorFile3()
/////////////////////////////////////////////////////////////////////////////
const char* clTestDensityLight::WriteXMLErrorFile3()
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
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>";

  WriteCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>Density Light</behaviorName>"
       << "<version>1</version>"
       << "</behavior>"
       << "</behaviorList>"
       << "<lightOther>"
       << "<li_densLightA>12.40809</li_densLightA>"
       << "<li_densLightB>1.930225</li_densLightB>"
       << "<li_densLightC>11.17921</li_densLightC>"
       << "<li_densLightSigma>1.078382</li_densLightSigma>"
       << "<li_densLightChangeThreshold>2</li_densLightChangeThreshold>"
       << "<li_densLightMinDBH>-10</li_densLightMinDBH>"
       << "</lightOther>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
//  WriteXMLErrorFile4()
/////////////////////////////////////////////////////////////////////////////
const char* clTestDensityLight::WriteXMLErrorFile4()
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
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>";

  WriteCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>Density Light</behaviorName>"
       << "<version>1</version>"
       << "</behavior>"
       << "</behaviorList>"
       << "<lightOther>"
       << "<li_densLightA>12.40809</li_densLightA>"
       << "<li_densLightB>1.930225</li_densLightB>"
       << "<li_densLightC>11.17921</li_densLightC>"
       << "<li_densLightSigma>1.078382</li_densLightSigma>"
       << "<li_densLightChangeThreshold>2</li_densLightChangeThreshold>"
       << "<li_densLightMinDBH>10</li_densLightMinDBH>"
       << "</lightOther>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteCommonStuff()
/////////////////////////////////////////////////////////////////////////////
void clTestDensityLight::WriteCommonStuff( std::fstream &oOut )
{
  using namespace std;
  oOut << "<trees>"
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
}
