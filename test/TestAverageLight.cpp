//---------------------------------------------------------------------------
// TestAverageLight.cpp
//---------------------------------------------------------------------------
#include "TestAverageLight.h"
#include "Grid.h"
#include "SimManager.h"
#include "BehaviorBase.h"
#include "TreePopulation.h"
#include "BasalAreaLight.h"
#include <math.h>
#include <fstream>

/////////////////////////////////////////////////////////////////////////////
//  TestAverageLight()
/////////////////////////////////////////////////////////////////////////////
void clTestAverageLight::TestAverageLight()
{

  clSimManager * p_oSimManager = new clSimManager(6, 6, "");

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
void clTestAverageLight::TestErrorProcessing( clSimManager * p_oSimManager )
{

  try
  {
    p_oSimManager->ReadFile( WriteXMLErrorFile1() );
    CppUnit::Asserter::fail( "TestAverageLight error processing didn't catch error for WriteXMLErrorFile1." );
  }
  catch ( modelErr& err )
  {
    if ( strstr( err.cFunction, "clAverageLight::DoShellSetup" ) == NULL )
    {
      CppUnit::Asserter::fail( "TestAverageLight error processing caught wrong error for WriteXMLErrorFile1." );
    }
    ;
  }
}

/////////////////////////////////////////////////////////////////////////////
// NormalProcessingRun1()
/////////////////////////////////////////////////////////////////////////////
void clTestAverageLight::NormalProcessingRun1(clSimManager *p_oSimManager)
{
  clTreePopulation *p_oPop;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;
  clGrid *p_oGrid; //Average light grid
  float fActualLight, //Light level calculated by SORTIE
        fExpectedLight; //Light level we're expecting
  int iSpecies1, iSpecies2, iType1 = clTreePopulation::sapling,
      iType2 = clTreePopulation::adult, iSp, iTp;

  //Feed our file to the sim manager
  p_oSimManager->ReadFile(WriteXMLFile1());
  p_oPop = (clTreePopulation*) p_oSimManager->GetPopulationObject("treepopulation");
  p_oGrid = p_oSimManager->GetGridObject("Average Light");

  //Run one timestep
  p_oSimManager->RunSim(1);
  fExpectedLight = 43.59010122;

  //Check the grid value
  CPPUNIT_ASSERT(1 == p_oGrid->GetNumberXCells());
  CPPUNIT_ASSERT(1 == p_oGrid->GetNumberYCells());
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);

  //Get the target species
  iSpecies1 = p_oPop->TranslateSpeciesNameToCode("BEAL");
  iSpecies2 = p_oPop->TranslateSpeciesNameToCode("ACRU");

  p_oAllTrees = p_oPop->Find("all");
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {

    //Is this one of the species with the average light behavior?
    iTp = p_oTree->GetType();
    iSp = p_oTree->GetSpecies();
    p_oTree->GetValue(p_oPop->GetFloatDataCode("Light", iSp, iTp), &fActualLight);
    if ((iSp == iSpecies1 && iTp == iType1) ||
        (iSp == iSpecies2 && iTp == iType2)) {
      //Yes
      CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
    }
    else {
      //No - make sure this tree does NOT have the expected light
      CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) > 0.5);
    }

    p_oTree = p_oAllTrees->NextTree();
  }

  //Run another timestep
  p_oSimManager->RunSim(1);

  //This time, make sure everybody's light is different
  //Check the grid value
  CPPUNIT_ASSERT(1 == p_oGrid->GetNumberXCells());
  CPPUNIT_ASSERT(1 == p_oGrid->GetNumberYCells());
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) > 0.1);

  p_oAllTrees = p_oPop->Find("all");
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {

    iTp = p_oTree->GetType();
    iSp = p_oTree->GetSpecies();
    p_oTree->GetValue(p_oPop->GetFloatDataCode("Light", iSp, iTp), &fActualLight);

    CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) > 0.1);

    p_oTree = p_oAllTrees->NextTree();
  }
}

/////////////////////////////////////////////////////////////////////////////
// NormalProcessingRun2()
/////////////////////////////////////////////////////////////////////////////
void clTestAverageLight::NormalProcessingRun2(clSimManager *p_oSimManager)
{
  clTreePopulation *p_oPop;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;
  clGrid *p_oGrid; //Average Light grid
  float fActualLight, //Light level calculated by SORTIE
        fExpectedLight; //Light level we're expecting
  int iSp, iTp;

  //Feed our file to the sim manager
  p_oSimManager->ReadFile(WriteXMLFile2());
  p_oPop = (clTreePopulation*) p_oSimManager->GetPopulationObject("treepopulation");

  //Make some seedlings
  for (iSp = 0; iSp < 3; iSp++)
    p_oPop->CreateTree(10, 10, iSp, clTreePopulation::seedling, 1.0);

  //Run one timestep
  p_oSimManager->RunSim(1);
  p_oGrid = p_oSimManager->GetGridObject("Average Light");
  fExpectedLight = 99.99;

  //Check the grid value
  CPPUNIT_ASSERT(1 == p_oGrid->GetNumberXCells());
  CPPUNIT_ASSERT(1 == p_oGrid->GetNumberYCells());
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);

  p_oAllTrees = p_oPop->Find("all");
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {

    iSp = p_oTree->GetSpecies();
    iTp = p_oTree->GetType();
//    CPPUNIT_ASSERT(clTreePopulation::seedling == iTp);
    p_oTree->GetValue(p_oPop->GetFloatDataCode("Light", iSp, iTp), &fActualLight);
    CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);

    p_oTree = p_oAllTrees->NextTree();
  }
}

/////////////////////////////////////////////////////////////////////////////
// NormalProcessingRun3()
/////////////////////////////////////////////////////////////////////////////
void clTestAverageLight::NormalProcessingRun3(clSimManager *p_oSimManager)
{
  clTreePopulation *p_oPop;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;
  clGrid *p_oGrid; //Average light grid
  float fActualLight, //Light level calculated by SORTIE
        fExpectedLight, //Light level we're expecting
        fLengthXCells, fLengthYCells, fX, fY;
  int iNumXCells, iNumYCells, iX, iY;

  //Feed our file to the sim manager
  p_oSimManager->ReadFile(WriteXMLFile3());
  p_oPop = (clTreePopulation*) p_oSimManager->GetPopulationObject("treepopulation");
  p_oGrid = p_oSimManager->GetGridObject("Average Light");
  CPPUNIT_ASSERT(13 == p_oGrid->GetNumberXCells());
  CPPUNIT_ASSERT(7 == p_oGrid->GetNumberYCells());

  //Set a seedling in each Average Light grid cell
  iNumXCells = p_oGrid->GetNumberXCells();
  iNumYCells = p_oGrid->GetNumberYCells();
  fLengthXCells = p_oGrid->GetLengthXCells();
  fLengthYCells = p_oGrid->GetLengthYCells();
  for (iX = 0; iX < iNumXCells; iX++) {
    fX = (iX * fLengthXCells) + 1;
    for (iY = 0; iY < iNumYCells; iY++) {
      fY = (iY * fLengthYCells) + 1;
      p_oPop->CreateTree(fX, fY, 0, clTreePopulation::seedling, 0);
    }
  }

  //Run one timestep
  p_oSimManager->RunSim(1);

  //Check the grid values
  fExpectedLight = 60.38699913;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 69.324049;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 76.34815216;
  p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 59.17479897;
  p_oGrid->GetValueOfCell(0, 3, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 52.20565033;
  p_oGrid->GetValueOfCell(0, 4, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 38.39035034;
  p_oGrid->GetValueOfCell(0, 5, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 62.47299957;
  p_oGrid->GetValueOfCell(0, 6, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);

  fExpectedLight = 64.58029938;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 68.40789986;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 71.50594711;
  p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 61.11585236;
  p_oGrid->GetValueOfCell(1, 3, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 38.60919952;
  p_oGrid->GetValueOfCell(1, 4, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 43.49344826;
  p_oGrid->GetValueOfCell(1, 5, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 63.11650085;
  p_oGrid->GetValueOfCell(1, 6, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);

  fExpectedLight = 67.47014999;
  p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 38.93785;
  p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 64.53174973;
  p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 57.43745041;
  p_oGrid->GetValueOfCell(2, 3, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 37.92894936;
  p_oGrid->GetValueOfCell(2, 4, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 47.19504929;
  p_oGrid->GetValueOfCell(2, 5, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 58.9319000;
  p_oGrid->GetValueOfCell(2, 6, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);

  fExpectedLight = 55.55750084;
  p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 22.43755007;
  p_oGrid->GetValueOfCell(3, 1, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 50.67210007;
  p_oGrid->GetValueOfCell(3, 2, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 32.27323461;
  p_oGrid->GetValueOfCell(3, 3, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 36.00485039;
  p_oGrid->GetValueOfCell(3, 4, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 41.17555046;
  p_oGrid->GetValueOfCell(3, 5, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 45.30899811;
  p_oGrid->GetValueOfCell(3, 6, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);

  fExpectedLight = 50.42110062;
  p_oGrid->GetValueOfCell(4, 0, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 34.05419922;
  p_oGrid->GetValueOfCell(4, 1, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 34.45949936;
  p_oGrid->GetValueOfCell(4, 2, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 42.61190033;
  p_oGrid->GetValueOfCell(4, 3, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 35.93470001;
  p_oGrid->GetValueOfCell(4, 4, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 34.88349915;
  p_oGrid->GetValueOfCell(4, 5, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 45.58280182;
  p_oGrid->GetValueOfCell(4, 6, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);

  fExpectedLight = 46.12594986;
  p_oGrid->GetValueOfCell(5, 0, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 16.52029526;
  p_oGrid->GetValueOfCell(5, 1, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 16.83988416;
  p_oGrid->GetValueOfCell(5, 2, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 42.62344933;
  p_oGrid->GetValueOfCell(5, 3, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 38.89259911;
  p_oGrid->GetValueOfCell(5, 4, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 20.97870016;
  p_oGrid->GetValueOfCell(5, 5, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 41.57740021;
  p_oGrid->GetValueOfCell(5, 6, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);

  fExpectedLight = 43.48215103;
  p_oGrid->GetValueOfCell(6, 0, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 23.80674934;
  p_oGrid->GetValueOfCell(6, 1, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 20.85045004;
  p_oGrid->GetValueOfCell(6, 2, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 46.55455017;
  p_oGrid->GetValueOfCell(6, 3, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 38.13809967;
  p_oGrid->GetValueOfCell(6, 4, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 22.35580063;
  p_oGrid->GetValueOfCell(6, 5, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 42.2098999;
  p_oGrid->GetValueOfCell(6, 6, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);

  fExpectedLight = 35.30064964;
  p_oGrid->GetValueOfCell(7, 0, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 25.30890036;
  p_oGrid->GetValueOfCell(7, 1, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 19.76926994;
  p_oGrid->GetValueOfCell(7, 2, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 20.44433045;
  p_oGrid->GetValueOfCell(7, 3, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 39.99809837;
  p_oGrid->GetValueOfCell(7, 4, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 50.06304932;
  p_oGrid->GetValueOfCell(7, 5, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 46.55039978;
  p_oGrid->GetValueOfCell(7, 6, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);

  fExpectedLight = 15.73940039;
  p_oGrid->GetValueOfCell(8, 0, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 31.43349934;
  p_oGrid->GetValueOfCell(8, 1, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 35.89275074;
  p_oGrid->GetValueOfCell(8, 2, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 21.0635004;
  p_oGrid->GetValueOfCell(8, 3, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 48.67160034;
  p_oGrid->GetValueOfCell(8, 4, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 47.26420021;
  p_oGrid->GetValueOfCell(8, 5, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 47.7179985;
  p_oGrid->GetValueOfCell(8, 6, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);

  fExpectedLight = 26.85165024;
  p_oGrid->GetValueOfCell(9, 0, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 42.50694847;
  p_oGrid->GetValueOfCell(9, 1, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 47.07250023;
  p_oGrid->GetValueOfCell(9, 2, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 11.88940477;
  p_oGrid->GetValueOfCell(9, 3, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 54.53019905;
  p_oGrid->GetValueOfCell(9, 4, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 52.90049934;
  p_oGrid->GetValueOfCell(9, 5, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 57.1855011;
  p_oGrid->GetValueOfCell(9, 6, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);

  fExpectedLight = 22.04295015;
  p_oGrid->GetValueOfCell(10, 0, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 44.45619965;
  p_oGrid->GetValueOfCell(10, 1, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 54.04654884;
  p_oGrid->GetValueOfCell(10, 2, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 12.36381483;
  p_oGrid->GetValueOfCell(10, 3, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 49.79330063;
  p_oGrid->GetValueOfCell(10, 4, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 26.89037597;
  p_oGrid->GetValueOfCell(10, 5, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 39.55899811;
  p_oGrid->GetValueOfCell(10, 6, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);

  fExpectedLight = 39.72920036;
  p_oGrid->GetValueOfCell(11, 0, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 62.15245247;
  p_oGrid->GetValueOfCell(11, 1, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 63.66015053;
  p_oGrid->GetValueOfCell(11, 2, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 45.09325027;
  p_oGrid->GetValueOfCell(11, 3, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 52.67409897;
  p_oGrid->GetValueOfCell(11, 4, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 38.22665024;
  p_oGrid->GetValueOfCell(11, 5, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 55.25839996;
  p_oGrid->GetValueOfCell(11, 6, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);

  fExpectedLight = 58.89039993;
  p_oGrid->GetValueOfCell(12, 0, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 67.32585144;
  p_oGrid->GetValueOfCell(12, 1, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 73.8539505;
  p_oGrid->GetValueOfCell(12, 2, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 51.5964489;
  p_oGrid->GetValueOfCell(12, 3, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 54.99550056;
  p_oGrid->GetValueOfCell(12, 4, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 41.61429977;
  p_oGrid->GetValueOfCell(12, 5, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 59.64709854;
  p_oGrid->GetValueOfCell(12, 6, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);

  //Check the seedlings were correctly assigned
  p_oAllTrees = p_oPop->Find("type=1::species=0");
  p_oTree = p_oAllTrees->NextTree();
  CPPUNIT_ASSERT(p_oTree != NULL);
  while (p_oTree) {

    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
    p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
    iX = (int)floor(fX / fLengthXCells);
    iY = (int)floor(fY / fLengthYCells);

    if (0 == iX && 0 == iY)
      fExpectedLight = 60.38699913;
    else if (0 == iX && 1 == iY)
      fExpectedLight = 69.324049;
    else if (0 == iX && 2 == iY)
      fExpectedLight = 76.34815216;
    else if (0 == iX && 3 == iY)
      fExpectedLight = 59.17479897;
    else if (0 == iX && 4 == iY)
      fExpectedLight = 52.20565033;
    else if (0 == iX && 5 == iY)
      fExpectedLight = 38.39035034;
    else if (0 == iX && 6 == iY)
      fExpectedLight = 62.47299957;

    else if (1 == iX && 0 == iY)
      fExpectedLight = 64.58029938;
    else if (1 == iX && 1 == iY)
      fExpectedLight = 68.40789986;
    else if (1 == iX && 2 == iY)
      fExpectedLight = 71.50594711;
    else if (1 == iX && 3 == iY)
      fExpectedLight = 61.11585236;
    else if (1 == iX && 4 == iY)
      fExpectedLight = 38.60919952;
    else if (1 == iX && 5 == iY)
      fExpectedLight = 43.49344826;
    else if (1 == iX && 6 == iY)
      fExpectedLight = 63.11650085;

    else if (2 == iX && 0 == iY)
      fExpectedLight = 67.47014999;
    else if (2 == iX && 1 == iY)
      fExpectedLight = 38.93785;
    else if (2 == iX && 2 == iY)
      fExpectedLight = 64.53174973;
    else if (2 == iX && 3 == iY)
      fExpectedLight = 57.43745041;
    else if (2 == iX && 4 == iY)
      fExpectedLight = 37.92894936;
    else if (2 == iX && 5 == iY)
      fExpectedLight = 47.19504929;
    else if (2 == iX && 6 == iY)
      fExpectedLight = 58.9319000;

    else if (3 == iX && 0 == iY)
      fExpectedLight = 55.55750084;
    else if (3 == iX && 1 == iY)
      fExpectedLight = 22.43755007;
    else if (3 == iX && 2 == iY)
      fExpectedLight = 50.67210007;
    else if (3 == iX && 3 == iY)
      fExpectedLight = 32.27323461;
    else if (3 == iX && 4 == iY)
      fExpectedLight = 36.00485039;
    else if (3 == iX && 5 == iY)
      fExpectedLight = 41.17555046;
    else if (3 == iX && 6 == iY)
      fExpectedLight = 45.30899811;

    else if (4 == iX && 0 == iY)
      fExpectedLight = 50.42110062;
    else if (4 == iX && 1 == iY)
      fExpectedLight = 34.05419922;
    else if (4 == iX && 2 == iY)
      fExpectedLight = 34.45949936;
    else if (4 == iX && 3 == iY)
      fExpectedLight = 42.61190033;
    else if (4 == iX && 4 == iY)
      fExpectedLight = 35.93470001;
    else if (4 == iX && 5 == iY)
      fExpectedLight = 34.88349915;
    else if (4 == iX && 6 == iY)
      fExpectedLight = 45.58280182;

    else if (5 == iX && 0 == iY)
      fExpectedLight = 46.12594986;
    else if (5 == iX && 1 == iY)
      fExpectedLight = 16.52029526;
    else if (5 == iX && 2 == iY)
      fExpectedLight = 16.83988416;
    else if (5 == iX && 3 == iY)
      fExpectedLight = 42.62344933;
    else if (5 == iX && 4 == iY)
      fExpectedLight = 38.89259911;
    else if (5 == iX && 5 == iY)
      fExpectedLight = 20.97870016;
    else if (5 == iX && 6 == iY)
      fExpectedLight = 41.57740021;

    else if (6 == iX && 0 == iY)
      fExpectedLight = 43.48215103;
    else if (6 == iX && 1 == iY)
      fExpectedLight = 23.80674934;
    else if (6 == iX && 2 == iY)
      fExpectedLight = 20.85045004;
    else if (6 == iX && 3 == iY)
      fExpectedLight = 46.55455017;
    else if (6 == iX && 4 == iY)
      fExpectedLight = 38.13809967;
    else if (6 == iX && 5 == iY)
      fExpectedLight = 22.35580063;
    else if (6 == iX && 6 == iY)
      fExpectedLight = 42.2098999;

    else if (7 == iX && 0 == iY)
      fExpectedLight = 35.30064964;
    else if (7 == iX && 1 == iY)
      fExpectedLight = 25.30890036;
    else if (7 == iX && 2 == iY)
      fExpectedLight = 19.76926994;
    else if (7 == iX && 3 == iY)
      fExpectedLight = 20.44433045;
    else if (7 == iX && 4 == iY)
      fExpectedLight = 39.99809837;
    else if (7 == iX && 5 == iY)
      fExpectedLight = 50.06304932;
    else if (7 == iX && 6 == iY)
      fExpectedLight = 46.55039978;

    else if (8 == iX && 0 == iY)
      fExpectedLight = 15.73940039;
    else if (8 == iX && 1 == iY)
      fExpectedLight = 31.43349934;
    else if (8 == iX && 2 == iY)
      fExpectedLight = 35.89275074;
    else if (8 == iX && 3 == iY)
      fExpectedLight = 21.0635004;
    else if (8 == iX && 4 == iY)
      fExpectedLight = 48.67160034;
    else if (8 == iX && 5 == iY)
      fExpectedLight = 47.26420021;
    else if (8 == iX && 6 == iY)
      fExpectedLight = 47.7179985;

    else if (9 == iX && 0 == iY)
      fExpectedLight = 26.85165024;
    else if (9 == iX && 1 == iY)
      fExpectedLight = 42.50694847;
    else if (9 == iX && 2 == iY)
      fExpectedLight = 47.07250023;
    else if (9 == iX && 3 == iY)
      fExpectedLight = 11.88940477;
    else if (9 == iX && 4 == iY)
      fExpectedLight = 54.53019905;
    else if (9 == iX && 5 == iY)
      fExpectedLight = 52.90049934;
    else if (9 == iX && 6 == iY)
      fExpectedLight = 57.1855011;

    else if (10 == iX && 0 == iY)
      fExpectedLight = 22.04295015;
    else if (10 == iX && 1 == iY)
      fExpectedLight = 44.45619965;
    else if (10 == iX && 2 == iY)
      fExpectedLight = 54.04654884;
    else if (10 == iX && 3 == iY)
      fExpectedLight = 12.36381483;
    else if (10 == iX && 4 == iY)
      fExpectedLight = 49.79330063;
    else if (10 == iX && 5 == iY)
      fExpectedLight = 26.89037597;
    else if (10 == iX && 6 == iY)
      fExpectedLight = 39.55899811;

    else if (11 == iX && 0 == iY)
      fExpectedLight = 39.72920036;
    else if (11 == iX && 1 == iY)
      fExpectedLight = 62.15245247;
    else if (11 == iX && 2 == iY)
      fExpectedLight = 63.66015053;
    else if (11 == iX && 3 == iY)
      fExpectedLight = 45.09325027;
    else if (11 == iX && 4 == iY)
      fExpectedLight = 52.67409897;
    else if (11 == iX && 5 == iY)
      fExpectedLight = 38.22665024;
    else if (11 == iX && 6 == iY)
      fExpectedLight = 55.25839996;

    else if (12 == iX && 0 == iY)
      fExpectedLight = 58.89039993;
    else if (12 == iX && 1 == iY)
      fExpectedLight = 67.32585144;
    else if (12 == iX && 2 == iY)
      fExpectedLight = 73.8539505;
    else if (12 == iX && 3 == iY)
      fExpectedLight = 51.5964489;
    else if (12 == iX && 4 == iY)
      fExpectedLight = 54.99550056;
    else if (12 == iX && 5 == iY)
      fExpectedLight = 41.61429977;
    else if (12 == iX && 6 == iY)
      fExpectedLight = 59.64709854;

    p_oTree = p_oAllTrees->NextTree();
  }
}

/////////////////////////////////////////////////////////////////////////////
// NormalProcessingRun4()
/////////////////////////////////////////////////////////////////////////////
void clTestAverageLight::NormalProcessingRun4(clSimManager *p_oSimManager)
{
  clGrid *p_oGrid; //Average light grid
  float fActualLight, //Light level calculated by SORTIE
        fExpectedLight; //Light level we're expecting

  //Feed our file to the sim manager
  p_oSimManager->ReadFile(WriteXMLFile4());
  p_oGrid = p_oSimManager->GetGridObject("Average Light");

  //Run one timestep
  p_oSimManager->RunSim(1);

  //Check the grid value
  CPPUNIT_ASSERT(10 == p_oGrid->GetNumberXCells());
  CPPUNIT_ASSERT(10 == p_oGrid->GetNumberYCells());
  fExpectedLight = 62.48364925;
  p_oGrid->GetValueOfCell(0, 0, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 60.91800022;
  p_oGrid->GetValueOfCell(0, 1, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 68.86597443;
  p_oGrid->GetValueOfCell(0, 2, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 73.89792442;
  p_oGrid->GetValueOfCell(0, 3, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 71.82087517;
  p_oGrid->GetValueOfCell(0, 4, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 60.14532566;
  p_oGrid->GetValueOfCell(0, 5, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 49.54767513;
  p_oGrid->GetValueOfCell(0, 6, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 45.40742493;
  p_oGrid->GetValueOfCell(0, 7, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 40.9418993;
  p_oGrid->GetValueOfCell(0, 8, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 53.37062454;
  p_oGrid->GetValueOfCell(0, 9, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);

  fExpectedLight = 66.02522469;
  p_oGrid->GetValueOfCell(1, 0, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 55.16762495;
  p_oGrid->GetValueOfCell(1, 1, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 53.67287493;
  p_oGrid->GetValueOfCell(1, 2, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 62.80292416;
  p_oGrid->GetValueOfCell(1, 3, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 69.76280022;
  p_oGrid->GetValueOfCell(1, 4, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 59.27665138;
  p_oGrid->GetValueOfCell(1, 5, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 43.90100002;
  p_oGrid->GetValueOfCell(1, 6, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 38.26907444;
  p_oGrid->GetValueOfCell(1, 7, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 45.34424877;
  p_oGrid->GetValueOfCell(1, 8, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 54.60147476;
  p_oGrid->GetValueOfCell(1, 9, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);

  fExpectedLight = 61.51382542;
  p_oGrid->GetValueOfCell(2, 0, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 41.97999978;
  p_oGrid->GetValueOfCell(2, 1, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 30.68770003;
  p_oGrid->GetValueOfCell(2, 2, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 45.999475;
  p_oGrid->GetValueOfCell(2, 3, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 63.17479992;
  p_oGrid->GetValueOfCell(2, 4, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 44.85534251;
  p_oGrid->GetValueOfCell(2, 5, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 27.63256705;
  p_oGrid->GetValueOfCell(2, 6, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 36.96689987;
  p_oGrid->GetValueOfCell(2, 7, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 44.18529987;
  p_oGrid->GetValueOfCell(2, 8, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 48.83839989;
  p_oGrid->GetValueOfCell(2, 9, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);

  fExpectedLight = 52.98930073;
  p_oGrid->GetValueOfCell(3, 0, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 44.59530044;
  p_oGrid->GetValueOfCell(3, 1, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 28.24587464;
  p_oGrid->GetValueOfCell(3, 2, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 32.06492472;
  p_oGrid->GetValueOfCell(3, 3, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 48.4592247;
  p_oGrid->GetValueOfCell(3, 4, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 37.44256747;
  p_oGrid->GetValueOfCell(3, 5, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 27.73376715;
  p_oGrid->GetValueOfCell(3, 6, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 35.9697752;
  p_oGrid->GetValueOfCell(3, 7, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 38.0295248;
  p_oGrid->GetValueOfCell(3, 8, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 42.80910015;
  p_oGrid->GetValueOfCell(3, 9, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);

  fExpectedLight = 44.80405045;
  p_oGrid->GetValueOfCell(4, 0, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 41.14302444;
  p_oGrid->GetValueOfCell(4, 1, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 20.1635223;
  p_oGrid->GetValueOfCell(4, 2, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 7.054265022;
  p_oGrid->GetValueOfCell(4, 3, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 37.99034929;
  p_oGrid->GetValueOfCell(4, 4, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 44.58899975;
  p_oGrid->GetValueOfCell(4, 5, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 42.75092506;
  p_oGrid->GetValueOfCell(4, 6, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 38.51534939;
  p_oGrid->GetValueOfCell(4, 7, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 21.66725039;
  p_oGrid->GetValueOfCell(4, 8, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 36.64752531;
  p_oGrid->GetValueOfCell(4, 9, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);

  fExpectedLight = 39.39140034;
  p_oGrid->GetValueOfCell(5, 0, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 39.20907497;
  p_oGrid->GetValueOfCell(5, 1, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 24.55782485;
  p_oGrid->GetValueOfCell(5, 2, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 11.60023499;
  p_oGrid->GetValueOfCell(5, 3, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 35.40967512;
  p_oGrid->GetValueOfCell(5, 4, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 33.49944031;
  p_oGrid->GetValueOfCell(5, 5, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 31.86223996;
  p_oGrid->GetValueOfCell(5, 6, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 39.06809902;
  p_oGrid->GetValueOfCell(5, 7, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 36.20942497;
  p_oGrid->GetValueOfCell(5, 8, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 43.07739973;
  p_oGrid->GetValueOfCell(5, 9, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);

  fExpectedLight = 25.52002501;
  p_oGrid->GetValueOfCell(6, 0, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 29.25399995;
  p_oGrid->GetValueOfCell(6, 1, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 28.37119985;
  p_oGrid->GetValueOfCell(6, 2, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 20.77593493;
  p_oGrid->GetValueOfCell(6, 3, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 32.16790056;
  p_oGrid->GetValueOfCell(6, 4, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 20.75391543;
  p_oGrid->GetValueOfCell(6, 5, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 23.43268979;
  p_oGrid->GetValueOfCell(6, 6, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 44.33484936;
  p_oGrid->GetValueOfCell(6, 7, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 48.66362476;
  p_oGrid->GetValueOfCell(6, 8, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 46.44789886;
  p_oGrid->GetValueOfCell(6, 9, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);

  fExpectedLight = 21.29552531;
  p_oGrid->GetValueOfCell(7, 0, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 27.43634915;
  p_oGrid->GetValueOfCell(7, 1, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 36.9702239;
  p_oGrid->GetValueOfCell(7, 2, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 38.55779934;
  p_oGrid->GetValueOfCell(7, 3, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 29.28950334;
  p_oGrid->GetValueOfCell(7, 4, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 16.47645259;
  p_oGrid->GetValueOfCell(7, 5, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 29.08599997;
  p_oGrid->GetValueOfCell(7, 6, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 51.6008997;
  p_oGrid->GetValueOfCell(7, 7, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 50.08234978;
  p_oGrid->GetValueOfCell(7, 8, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 49.92569923;
  p_oGrid->GetValueOfCell(7, 9, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);

  fExpectedLight = 30.88607526;
  p_oGrid->GetValueOfCell(8, 0, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 39.23800039;
  p_oGrid->GetValueOfCell(8, 1, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 53.30432606;
  p_oGrid->GetValueOfCell(8, 2, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 58.21725082;
  p_oGrid->GetValueOfCell(8, 3, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 45.20960689;
  p_oGrid->GetValueOfCell(8, 4, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 28.72853255;
  p_oGrid->GetValueOfCell(8, 5, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 37.15177536;
  p_oGrid->GetValueOfCell(8, 6, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 51.2336998;
  p_oGrid->GetValueOfCell(8, 7, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 32.5585131;
  p_oGrid->GetValueOfCell(8, 8, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 48.12370014;
  p_oGrid->GetValueOfCell(8, 9, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);

  fExpectedLight = 49.30980015;
  p_oGrid->GetValueOfCell(9, 0, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 50.81772614;
  p_oGrid->GetValueOfCell(9, 1, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 64.73915195;
  p_oGrid->GetValueOfCell(9, 2, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 70.58922672;
  p_oGrid->GetValueOfCell(9, 3, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 64.58332443;
  p_oGrid->GetValueOfCell(9, 4, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 48.34484959;
  p_oGrid->GetValueOfCell(9, 5, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 43.61769962;
  p_oGrid->GetValueOfCell(9, 6, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 53.83479977;
  p_oGrid->GetValueOfCell(9, 7, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 39.92047501;
  p_oGrid->GetValueOfCell(9, 8, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
  fExpectedLight = 51.6772995;
  p_oGrid->GetValueOfCell(9, 9, p_oGrid->GetFloatDataCode("GLI"), &fActualLight);
  CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
}

/////////////////////////////////////////////////////////////////////////////
// NormalProcessingRun5()
/////////////////////////////////////////////////////////////////////////////
void clTestAverageLight::NormalProcessingRun5(clSimManager *p_oSimManager)
{
  clGrid *p_oMapGrid, //GLI Map grid
             *p_oAvgGrid; //Average Light grid
  float fActualLight, //Light level calculated by SORTIE
        fExpectedLight; //Light level we're expecting
  int iNumXCells, iNumYCells, iX, iY, iMapGLI, iAvgGLI;

  //Feed our file to the sim manager
  p_oSimManager->ReadFile(WriteXMLFile5());
  p_oAvgGrid = p_oSimManager->GetGridObject("Average Light");
  p_oMapGrid = p_oSimManager->GetGridObject("GLI Map");
  CPPUNIT_ASSERT(NULL != p_oAvgGrid);
  CPPUNIT_ASSERT(NULL != p_oMapGrid);

  //Run one timestep
  p_oSimManager->RunSim(1);

  //Check the grid values match
  iMapGLI = p_oMapGrid->GetFloatDataCode("GLI");
  iAvgGLI = p_oAvgGrid->GetFloatDataCode("GLI");
  iNumXCells = p_oAvgGrid->GetNumberXCells();
  iNumYCells = p_oAvgGrid->GetNumberYCells();
  CPPUNIT_ASSERT(iNumXCells == p_oMapGrid->GetNumberXCells());
  CPPUNIT_ASSERT(iNumYCells == p_oMapGrid->GetNumberYCells());
  for (iX = 0; iX < iNumXCells; iX++) {
    for (iY = 0; iY < iNumYCells; iY++) {
      p_oMapGrid->GetValueOfCell(iX, iY, iMapGLI, &fExpectedLight);
      p_oAvgGrid->GetValueOfCell(iX, iY, iAvgGLI, &fActualLight);
      CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.01);
    }
  }
}

/////////////////////////////////////////////////////////////////////////////
//  WriteXMLFile1()
/////////////////////////////////////////////////////////////////////////////
const char* clTestAverageLight::WriteXMLFile1()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06060101\">"       << "<plot>"       << "<timesteps>3</timesteps>"
       << "<randomSeed>0</randomSeed>"       << "<yearsPerTimestep>5.0</yearsPerTimestep>"       << "<plot_lenX>100.0</plot_lenX>"       << "<plot_lenY>100.0</plot_lenY>"       << "<plot_latitude>41.92</plot_latitude>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"       << "<plot_title>Default parameter file-use for testing only</plot_title>"       << "</plot>"
       << "<trees>"       << "<tr_speciesList>"       << "<tr_species speciesName=\"ACRU\"/>"       << "<tr_species speciesName=\"ACSA\"/>"       << "<tr_species speciesName=\"BEAL\"/>"       << "<tr_species speciesName=\"FAGR\"/>"       << "<tr_species speciesName=\"TSCA\"/>"       << "<tr_species speciesName=\"FRAM\"/>"       << "<tr_species speciesName=\"PIST\"/>"       << "<tr_species speciesName=\"PRSE\"/>"       << "<tr_species speciesName=\"QURU\"/>"       << "</tr_speciesList>"       << "<tr_seedDiam10Cm>0.2</tr_seedDiam10Cm>"       << "<tr_minAdultDBH>"       << "<tr_madVal species=\"ACRU\">10.0</tr_madVal>"       << "<tr_madVal species=\"ACSA\">10.0</tr_madVal>"       << "<tr_madVal species=\"BEAL\">10.0</tr_madVal>"       << "<tr_madVal species=\"FAGR\">10.0</tr_madVal>"       << "<tr_madVal species=\"TSCA\">10.0</tr_madVal>"       << "<tr_madVal species=\"FRAM\">10.0</tr_madVal>"       << "<tr_madVal species=\"PIST\">10.0</tr_madVal>"       << "<tr_madVal species=\"PRSE\">10.0</tr_madVal>"       << "<tr_madVal species=\"QURU\">10.0</tr_madVal>"       << "</tr_minAdultDBH>"       << "<tr_maxSeedlingHeight>"       << "<tr_mshVal species=\"ACRU\">1.35</tr_mshVal>"       << "<tr_mshVal species=\"ACSA\">1.35</tr_mshVal>"       << "<tr_mshVal species=\"BEAL\">1.35</tr_mshVal>"       << "<tr_mshVal species=\"FAGR\">1.35</tr_mshVal>"       << "<tr_mshVal species=\"TSCA\">1.35</tr_mshVal>"       << "<tr_mshVal species=\"FRAM\">1.35</tr_mshVal>"       << "<tr_mshVal species=\"PIST\">1.35</tr_mshVal>"       << "<tr_mshVal species=\"PRSE\">1.35</tr_mshVal>"       << "<tr_mshVal species=\"QURU\">1.35</tr_mshVal>"       << "</tr_maxSeedlingHeight>";

  WriteTreeFile(oOut);  oOut << "</trees>"
       << "<grid gridName=\"Average Light\">"
       << "<ma_floatCodes>"
       << "<ma_floatCode label=\"GLI\">0</ma_floatCode>"
       << "</ma_floatCodes>"
       << "<ma_lengthXCells>100</ma_lengthXCells>"
       << "<ma_lengthYCells>100</ma_lengthYCells>"
       << "</grid>"       << "<behaviorList>"       << "<behavior>"       << "<behaviorName>GLIMapCreator</behaviorName>"       << "<version>1.0</version>"       << "<listPosition>1</listPosition>"
       << "</behavior>"       << "<behavior>"       << "<behaviorName>GLILight</behaviorName>"       << "<version>1.0</version>"       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"ACRU\" type=\"Sapling\"/>"       << "<applyTo species=\"ACSA\" type=\"Sapling\"/>"       << "<applyTo species=\"FAGR\" type=\"Sapling\"/>"       << "<applyTo species=\"TSCA\" type=\"Sapling\"/>"       << "<applyTo species=\"FRAM\" type=\"Sapling\"/>"       << "<applyTo species=\"PIST\" type=\"Sapling\"/>"       << "<applyTo species=\"PRSE\" type=\"Sapling\"/>"       << "<applyTo species=\"QURU\" type=\"Sapling\"/>"       << "<applyTo species=\"ACSA\" type=\"Adult\"/>"       << "<applyTo species=\"BEAL\" type=\"Adult\"/>"       << "<applyTo species=\"FAGR\" type=\"Adult\"/>"       << "<applyTo species=\"TSCA\" type=\"Adult\"/>"       << "<applyTo species=\"FRAM\" type=\"Adult\"/>"       << "<applyTo species=\"PIST\" type=\"Adult\"/>"       << "<applyTo species=\"PRSE\" type=\"Adult\"/>"       << "<applyTo species=\"QURU\" type=\"Adult\"/>"       << "</behavior>"       << "<behavior>"       << "<behaviorName>QuadratLight</behaviorName>"       << "<version>1.0</version>"       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"ACRU\" type=\"Seedling\"/>"       << "<applyTo species=\"ACSA\" type=\"Seedling\"/>"       << "<applyTo species=\"BEAL\" type=\"Seedling\"/>"       << "<applyTo species=\"FAGR\" type=\"Seedling\"/>"       << "<applyTo species=\"TSCA\" type=\"Seedling\"/>"       << "<applyTo species=\"FRAM\" type=\"Seedling\"/>"       << "<applyTo species=\"PIST\" type=\"Seedling\"/>"       << "<applyTo species=\"PRSE\" type=\"Seedling\"/>"       << "<applyTo species=\"QURU\" type=\"Seedling\"/>"       << "</behavior>"       << "<behavior>"       << "<behaviorName>AverageLight</behaviorName>"       << "<version>1.0</version>"       << "<listPosition>4</listPosition>"
       << "<applyTo species=\"ACRU\" type=\"Adult\"/>"       << "<applyTo species=\"BEAL\" type=\"Sapling\"/>"       << "</behavior>"       << "<behavior>"       << "<behaviorName>RelUnlimGrowth</behaviorName>"       << "<version>1.1</version>"       << "<listPosition>5</listPosition>"
       << "<applyTo species=\"ACRU\" type=\"Seedling\"/>"       << "<applyTo species=\"ACSA\" type=\"Seedling\"/>"       << "<applyTo species=\"BEAL\" type=\"Seedling\"/>"       << "<applyTo species=\"FAGR\" type=\"Seedling\"/>"       << "<applyTo species=\"TSCA\" type=\"Seedling\"/>"       << "<applyTo species=\"FRAM\" type=\"Seedling\"/>"       << "<applyTo species=\"PIST\" type=\"Seedling\"/>"       << "<applyTo species=\"PRSE\" type=\"Seedling\"/>"       << "<applyTo species=\"QURU\" type=\"Seedling\"/>"       << "<applyTo species=\"ACRU\" type=\"Sapling\"/>"       << "<applyTo species=\"ACSA\" type=\"Sapling\"/>"       << "<applyTo species=\"BEAL\" type=\"Sapling\"/>"       << "<applyTo species=\"FAGR\" type=\"Sapling\"/>"       << "<applyTo species=\"TSCA\" type=\"Sapling\"/>"       << "<applyTo species=\"FRAM\" type=\"Sapling\"/>"       << "<applyTo species=\"PIST\" type=\"Sapling\"/>"       << "<applyTo species=\"PRSE\" type=\"Sapling\"/>"       << "<applyTo species=\"QURU\" type=\"Sapling\"/>"       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>ConstRadialGrowth</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>6</listPosition>"
       << "<applyTo species=\"ACRU\" type=\"Adult\"/>"
       << "<applyTo species=\"ACSA\" type=\"Adult\"/>"
       << "<applyTo species=\"BEAL\" type=\"Adult\"/>"
       << "<applyTo species=\"FAGR\" type=\"Adult\"/>"
       << "<applyTo species=\"TSCA\" type=\"Adult\"/>"
       << "<applyTo species=\"FRAM\" type=\"Adult\"/>"
       << "<applyTo species=\"PIST\" type=\"Adult\"/>"
       << "<applyTo species=\"PRSE\" type=\"Adult\"/>"
       << "<applyTo species=\"QURU\" type=\"Adult\"/>"
       << "</behavior>"       << "</behaviorList>"       << "<allometry>"       << "<tr_whatAdultHeightDiam>"       << "<tr_wahdVal species=\"ACRU\">0</tr_wahdVal>"       << "<tr_wahdVal species=\"ACSA\">0</tr_wahdVal>"       << "<tr_wahdVal species=\"BEAL\">0</tr_wahdVal>"       << "<tr_wahdVal species=\"FAGR\">0</tr_wahdVal>"       << "<tr_wahdVal species=\"TSCA\">0</tr_wahdVal>"       << "<tr_wahdVal species=\"FRAM\">0</tr_wahdVal>"       << "<tr_wahdVal species=\"PIST\">0</tr_wahdVal>"       << "<tr_wahdVal species=\"PRSE\">0</tr_wahdVal>"       << "<tr_wahdVal species=\"QURU\">0</tr_wahdVal>"       << "</tr_whatAdultHeightDiam>"       << "<tr_whatSaplingHeightDiam>"       << "<tr_wsahdVal species=\"ACRU\">0</tr_wsahdVal>"       << "<tr_wsahdVal species=\"ACSA\">0</tr_wsahdVal>"       << "<tr_wsahdVal species=\"BEAL\">0</tr_wsahdVal>"       << "<tr_wsahdVal species=\"FAGR\">0</tr_wsahdVal>"       << "<tr_wsahdVal species=\"TSCA\">0</tr_wsahdVal>"       << "<tr_wsahdVal species=\"FRAM\">0</tr_wsahdVal>"       << "<tr_wsahdVal species=\"PIST\">0</tr_wsahdVal>"       << "<tr_wsahdVal species=\"PRSE\">0</tr_wsahdVal>"       << "<tr_wsahdVal species=\"QURU\">0</tr_wsahdVal>"       << "</tr_whatSaplingHeightDiam>"       << "<tr_whatSeedlingHeightDiam>"       << "<tr_wsehdVal species=\"ACRU\">0</tr_wsehdVal>"       << "<tr_wsehdVal species=\"ACSA\">0</tr_wsehdVal>"       << "<tr_wsehdVal species=\"BEAL\">0</tr_wsehdVal>"       << "<tr_wsehdVal species=\"FAGR\">0</tr_wsehdVal>"       << "<tr_wsehdVal species=\"TSCA\">0</tr_wsehdVal>"       << "<tr_wsehdVal species=\"FRAM\">0</tr_wsehdVal>"       << "<tr_wsehdVal species=\"PIST\">0</tr_wsehdVal>"       << "<tr_wsehdVal species=\"PRSE\">0</tr_wsehdVal>"       << "<tr_wsehdVal species=\"QURU\">0</tr_wsehdVal>"       << "</tr_whatSeedlingHeightDiam>"       << "<tr_whatAdultCrownRadDiam>"       << "<tr_wacrdVal species=\"ACRU\">0</tr_wacrdVal>"       << "<tr_wacrdVal species=\"ACSA\">0</tr_wacrdVal>"       << "<tr_wacrdVal species=\"BEAL\">0</tr_wacrdVal>"       << "<tr_wacrdVal species=\"FAGR\">0</tr_wacrdVal>"       << "<tr_wacrdVal species=\"TSCA\">0</tr_wacrdVal>"       << "<tr_wacrdVal species=\"FRAM\">0</tr_wacrdVal>"       << "<tr_wacrdVal species=\"PIST\">0</tr_wacrdVal>"       << "<tr_wacrdVal species=\"PRSE\">0</tr_wacrdVal>"       << "<tr_wacrdVal species=\"QURU\">0</tr_wacrdVal>"       << "</tr_whatAdultCrownRadDiam>"       << "<tr_whatSaplingCrownRadDiam>"       << "<tr_wscrdVal species=\"ACRU\">0</tr_wscrdVal>"       << "<tr_wscrdVal species=\"ACSA\">0</tr_wscrdVal>"       << "<tr_wscrdVal species=\"BEAL\">0</tr_wscrdVal>"       << "<tr_wscrdVal species=\"FAGR\">0</tr_wscrdVal>"       << "<tr_wscrdVal species=\"TSCA\">0</tr_wscrdVal>"       << "<tr_wscrdVal species=\"FRAM\">0</tr_wscrdVal>"       << "<tr_wscrdVal species=\"PIST\">0</tr_wscrdVal>"       << "<tr_wscrdVal species=\"PRSE\">0</tr_wscrdVal>"       << "<tr_wscrdVal species=\"QURU\">0</tr_wscrdVal>"       << "</tr_whatSaplingCrownRadDiam>"       << "<tr_whatAdultCrownHeightHeight>"       << "<tr_wachhVal species=\"ACRU\">0</tr_wachhVal>"       << "<tr_wachhVal species=\"ACSA\">0</tr_wachhVal>"       << "<tr_wachhVal species=\"BEAL\">0</tr_wachhVal>"       << "<tr_wachhVal species=\"FAGR\">0</tr_wachhVal>"       << "<tr_wachhVal species=\"TSCA\">0</tr_wachhVal>"       << "<tr_wachhVal species=\"FRAM\">0</tr_wachhVal>"       << "<tr_wachhVal species=\"PIST\">0</tr_wachhVal>"       << "<tr_wachhVal species=\"PRSE\">0</tr_wachhVal>"       << "<tr_wachhVal species=\"QURU\">0</tr_wachhVal>"       << "</tr_whatAdultCrownHeightHeight>"       << "<tr_whatSaplingCrownHeightHeight>"       << "<tr_wschhVal species=\"ACRU\">0</tr_wschhVal>"       << "<tr_wschhVal species=\"ACSA\">0</tr_wschhVal>"       << "<tr_wschhVal species=\"BEAL\">0</tr_wschhVal>"       << "<tr_wschhVal species=\"FAGR\">0</tr_wschhVal>"       << "<tr_wschhVal species=\"TSCA\">0</tr_wschhVal>"       << "<tr_wschhVal species=\"FRAM\">0</tr_wschhVal>"       << "<tr_wschhVal species=\"PIST\">0</tr_wschhVal>"       << "<tr_wschhVal species=\"PRSE\">0</tr_wschhVal>"       << "<tr_wschhVal species=\"QURU\">0</tr_wschhVal>"       << "</tr_whatSaplingCrownHeightHeight>"       << "<tr_canopyHeight>"       << "<tr_chVal species=\"ACRU\">30.0</tr_chVal>"       << "<tr_chVal species=\"ACSA\">30.0</tr_chVal>"       << "<tr_chVal species=\"BEAL\">30.0</tr_chVal>"       << "<tr_chVal species=\"FAGR\">30.0</tr_chVal>"       << "<tr_chVal species=\"TSCA\">30.0</tr_chVal>"       << "<tr_chVal species=\"FRAM\">30.0</tr_chVal>"       << "<tr_chVal species=\"PIST\">30.0</tr_chVal>"       << "<tr_chVal species=\"PRSE\">30.0</tr_chVal>"       << "<tr_chVal species=\"QURU\">30.0</tr_chVal>"       << "</tr_canopyHeight>"       << "<tr_stdAsympCrownRad>"       << "<tr_sacrVal species=\"ACRU\">0.108</tr_sacrVal>"       << "<tr_sacrVal species=\"ACSA\">0.107</tr_sacrVal>"       << "<tr_sacrVal species=\"BEAL\">0.109</tr_sacrVal>"       << "<tr_sacrVal species=\"FAGR\">0.152</tr_sacrVal>"       << "<tr_sacrVal species=\"TSCA\">0.1</tr_sacrVal>"       << "<tr_sacrVal species=\"FRAM\">0.095</tr_sacrVal>"       << "<tr_sacrVal species=\"PIST\">0.087</tr_sacrVal>"       << "<tr_sacrVal species=\"PRSE\">0.116</tr_sacrVal>"       << "<tr_sacrVal species=\"QURU\">0.119</tr_sacrVal>"       << "</tr_stdAsympCrownRad>"       << "<tr_stdCrownRadExp>"       << "<tr_screVal species=\"ACRU\">1.0</tr_screVal>"       << "<tr_screVal species=\"ACSA\">1.0</tr_screVal>"       << "<tr_screVal species=\"BEAL\">1.0</tr_screVal>"       << "<tr_screVal species=\"FAGR\">1.0</tr_screVal>"       << "<tr_screVal species=\"TSCA\">1.0</tr_screVal>"       << "<tr_screVal species=\"FRAM\">1.0</tr_screVal>"       << "<tr_screVal species=\"PIST\">1.0</tr_screVal>"       << "<tr_screVal species=\"PRSE\">1.0</tr_screVal>"       << "<tr_screVal species=\"QURU\">1.0</tr_screVal>"       << "</tr_stdCrownRadExp>"       << "<tr_stdAsympCrownHt>"       << "<tr_sachVal species=\"ACRU\">0.49</tr_sachVal>"       << "<tr_sachVal species=\"ACSA\">0.58</tr_sachVal>"       << "<tr_sachVal species=\"BEAL\">0.54</tr_sachVal>"       << "<tr_sachVal species=\"FAGR\">0.664</tr_sachVal>"       << "<tr_sachVal species=\"TSCA\">0.846</tr_sachVal>"       << "<tr_sachVal species=\"FRAM\">0.319</tr_sachVal>"       << "<tr_sachVal species=\"PIST\">0.413</tr_sachVal>"       << "<tr_sachVal species=\"PRSE\">0.37</tr_sachVal>"       << "<tr_sachVal species=\"QURU\">0.413</tr_sachVal>"       << "</tr_stdAsympCrownHt>"       << "<tr_stdCrownHtExp>"       << "<tr_scheVal species=\"ACRU\">1.0</tr_scheVal>"       << "<tr_scheVal species=\"ACSA\">1.0</tr_scheVal>"       << "<tr_scheVal species=\"BEAL\">1.0</tr_scheVal>"       << "<tr_scheVal species=\"FAGR\">1.0</tr_scheVal>"       << "<tr_scheVal species=\"TSCA\">1.0</tr_scheVal>"       << "<tr_scheVal species=\"FRAM\">1.0</tr_scheVal>"       << "<tr_scheVal species=\"PIST\">1.0</tr_scheVal>"       << "<tr_scheVal species=\"PRSE\">1.0</tr_scheVal>"       << "<tr_scheVal species=\"QURU\">1.0</tr_scheVal>"       << "</tr_stdCrownHtExp>"       << "<tr_conversionDiam10ToDBH>"       << "<tr_cdtdVal species=\"ACRU\">0.75</tr_cdtdVal>"       << "<tr_cdtdVal species=\"ACSA\">0.75</tr_cdtdVal>"       << "<tr_cdtdVal species=\"BEAL\">0.75</tr_cdtdVal>"       << "<tr_cdtdVal species=\"FAGR\">0.75</tr_cdtdVal>"       << "<tr_cdtdVal species=\"TSCA\">0.75</tr_cdtdVal>"       << "<tr_cdtdVal species=\"FRAM\">0.75</tr_cdtdVal>"       << "<tr_cdtdVal species=\"PIST\">0.75</tr_cdtdVal>"       << "<tr_cdtdVal species=\"PRSE\">0.75</tr_cdtdVal>"       << "<tr_cdtdVal species=\"QURU\">0.75</tr_cdtdVal>"       << "</tr_conversionDiam10ToDBH>"       << "<tr_interceptDiam10ToDBH>"       << "<tr_idtdVal species=\"ACRU\">0.0</tr_idtdVal>"       << "<tr_idtdVal species=\"ACSA\">0.0</tr_idtdVal>"       << "<tr_idtdVal species=\"BEAL\">0.0</tr_idtdVal>"       << "<tr_idtdVal species=\"FAGR\">0.0</tr_idtdVal>"       << "<tr_idtdVal species=\"TSCA\">0.0</tr_idtdVal>"       << "<tr_idtdVal species=\"FRAM\">0.0</tr_idtdVal>"       << "<tr_idtdVal species=\"PIST\">0.0</tr_idtdVal>"       << "<tr_idtdVal species=\"PRSE\">0.0</tr_idtdVal>"       << "<tr_idtdVal species=\"QURU\">0.0</tr_idtdVal>"       << "</tr_interceptDiam10ToDBH>"       << "<tr_slopeOfAsymHeight>"       << "<tr_soahVal species=\"ACRU\">0.063</tr_soahVal>"       << "<tr_soahVal species=\"ACSA\">0.062333334</tr_soahVal>"       << "<tr_soahVal species=\"BEAL\">0.063</tr_soahVal>"       << "<tr_soahVal species=\"FAGR\">0.03533333</tr_soahVal>"       << "<tr_soahVal species=\"TSCA\">0.024333334</tr_soahVal>"       << "<tr_soahVal species=\"FRAM\">0.055999998</tr_soahVal>"       << "<tr_soahVal species=\"PIST\">0.033333335</tr_soahVal>"       << "<tr_soahVal species=\"PRSE\">0.045</tr_soahVal>"       << "<tr_soahVal species=\"QURU\">0.042</tr_soahVal>"       << "</tr_slopeOfAsymHeight>"       << "<tr_slopeOfHeight-Diam10>"       << "<tr_sohdVal species=\"ACRU\">0.03</tr_sohdVal>"       << "<tr_sohdVal species=\"ACSA\">0.03</tr_sohdVal>"       << "<tr_sohdVal species=\"BEAL\">0.03</tr_sohdVal>"       << "<tr_sohdVal species=\"FAGR\">0.03</tr_sohdVal>"       << "<tr_sohdVal species=\"TSCA\">0.03</tr_sohdVal>"       << "<tr_sohdVal species=\"FRAM\">0.03</tr_sohdVal>"       << "<tr_sohdVal species=\"PIST\">0.03</tr_sohdVal>"       << "<tr_sohdVal species=\"PRSE\">0.03</tr_sohdVal>"       << "<tr_sohdVal species=\"QURU\">0.03</tr_sohdVal>"       << "</tr_slopeOfHeight-Diam10>"       << "</allometry>"       << "<GLILight2>"       << "<li_heightOfFishEyePhoto>0</li_heightOfFishEyePhoto>"       << "<li_beamFractGlobalRad>0.5</li_beamFractGlobalRad>"       << "<li_clearSkyTransCoeff>0.65</li_clearSkyTransCoeff>"       << "<li_julianDayGrowthStarts>120</li_julianDayGrowthStarts>"       << "<li_julianDayGrowthEnds>270</li_julianDayGrowthEnds>"       << "<li_minSunAngle>0.779</li_minSunAngle>"       << "<li_numAltGrids>12</li_numAltGrids>"       << "<li_numAziGrids>18</li_numAziGrids>"       << "<li_lightExtinctionCoefficient>"       << "<li_lecVal species=\"ACRU\">0.399</li_lecVal>"       << "<li_lecVal species=\"ACSA\">0.399</li_lecVal>"       << "<li_lecVal species=\"BEAL\">0.399</li_lecVal>"       << "<li_lecVal species=\"FAGR\">0.064</li_lecVal>"       << "<li_lecVal species=\"TSCA\">0.064</li_lecVal>"       << "<li_lecVal species=\"FRAM\">0.399</li_lecVal>"       << "<li_lecVal species=\"PIST\">0.399</li_lecVal>"       << "<li_lecVal species=\"PRSE\">0.399</li_lecVal>"       << "<li_lecVal species=\"QURU\">0.566</li_lecVal>"       << "</li_lightExtinctionCoefficient>"       << "<li_snagAgeClass1>0</li_snagAgeClass1>"       << "<li_snagAgeClass2>0</li_snagAgeClass2>"       << "</GLILight2>"       << "<QuadratLight3>"       << "<li_minSunAngle>0.779</li_minSunAngle>"       << "<li_numAltGrids>12</li_numAltGrids>"       << "<li_numAziGrids>18</li_numAziGrids>"       << "<li_quadratLightHeight>0.675</li_quadratLightHeight>"
       << "<li_quadratAllGLIs>0</li_quadratAllGLIs>"       << "</QuadratLight3>"       << "<GLIMapCreator1>"       << "<li_minSunAngle>0.779</li_minSunAngle>"       << "<li_numAltGrids>12</li_numAltGrids>"       << "<li_numAziGrids>18</li_numAziGrids>"       << "<li_mapLightHeight>0.0</li_mapLightHeight>"       << "</GLIMapCreator1>"       << "<ConstRadialGrowth6>"
       << "<gr_adultConstRadialInc>"
       << "<gr_acriVal species=\"ACRU\">3</gr_acriVal>"
       << "<gr_acriVal species=\"ACSA\">3</gr_acriVal>"
       << "<gr_acriVal species=\"BEAL\">3</gr_acriVal>"
       << "<gr_acriVal species=\"FAGR\">3</gr_acriVal>"
       << "<gr_acriVal species=\"TSCA\">3</gr_acriVal>"
       << "<gr_acriVal species=\"FRAM\">3</gr_acriVal>"
       << "<gr_acriVal species=\"PIST\">3</gr_acriVal>"
       << "<gr_acriVal species=\"PRSE\">3</gr_acriVal>"
       << "<gr_acriVal species=\"QURU\">3</gr_acriVal>"
       << "</gr_adultConstRadialInc>"       << "</ConstRadialGrowth6>"
       << "<RelUnlimGrowth5>"
       << "<gr_asympDiameterGrowth>"       << "<gr_adgVal species=\"ACRU\">0.167</gr_adgVal>"       << "<gr_adgVal species=\"ACSA\">0.125</gr_adgVal>"       << "<gr_adgVal species=\"BEAL\">0.169</gr_adgVal>"       << "<gr_adgVal species=\"FAGR\">0.152</gr_adgVal>"       << "<gr_adgVal species=\"TSCA\">0.229</gr_adgVal>"       << "<gr_adgVal species=\"FRAM\">0.226</gr_adgVal>"       << "<gr_adgVal species=\"PIST\">0.23</gr_adgVal>"       << "<gr_adgVal species=\"PRSE\">0.249</gr_adgVal>"       << "<gr_adgVal species=\"QURU\">0.266</gr_adgVal>"       << "</gr_asympDiameterGrowth>"       << "<gr_slopeGrowthResponse>"       << "<gr_sgrVal species=\"ACRU\">0.027</gr_sgrVal>"       << "<gr_sgrVal species=\"ACSA\">0.159</gr_sgrVal>"       << "<gr_sgrVal species=\"BEAL\">0.137</gr_sgrVal>"       << "<gr_sgrVal species=\"FAGR\">0.075</gr_sgrVal>"       << "<gr_sgrVal species=\"TSCA\">0.051</gr_sgrVal>"       << "<gr_sgrVal species=\"FRAM\">0.025</gr_sgrVal>"       << "<gr_sgrVal species=\"PIST\">0.019</gr_sgrVal>"       << "<gr_sgrVal species=\"PRSE\">0.064</gr_sgrVal>"       << "<gr_sgrVal species=\"QURU\">0.022</gr_sgrVal>"       << "</gr_slopeGrowthResponse>"       << "<gr_relGrowthDiamExp>"       << "<gr_rgdeVal species=\"ACRU\">1.0</gr_rgdeVal>"       << "<gr_rgdeVal species=\"ACSA\">1.0</gr_rgdeVal>"       << "<gr_rgdeVal species=\"BEAL\">1.0</gr_rgdeVal>"       << "<gr_rgdeVal species=\"FAGR\">1.0</gr_rgdeVal>"       << "<gr_rgdeVal species=\"TSCA\">1.0</gr_rgdeVal>"       << "<gr_rgdeVal species=\"FRAM\">1.0</gr_rgdeVal>"       << "<gr_rgdeVal species=\"PIST\">1.0</gr_rgdeVal>"       << "<gr_rgdeVal species=\"PRSE\">1.0</gr_rgdeVal>"       << "<gr_rgdeVal species=\"QURU\">1.0</gr_rgdeVal>"       << "</gr_relGrowthDiamExp>"       << "</RelUnlimGrowth5>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteXMLFile2()
/////////////////////////////////////////////////////////////////////////////
const char* clTestAverageLight::WriteXMLFile2()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06060101\">"
       << "<plot>"
       << "<timesteps>3</timesteps>"
       << "<randomSeed>0</randomSeed>"
       << "<yearsPerTimestep>5.0</yearsPerTimestep>"
       << "<plot_lenX>100.0</plot_lenX>"
       << "<plot_lenY>100.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>41.92</plot_latitude>"
       << "<plot_title>Default parameter file-use for testing only</plot_title>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\"/>"
       << "<tr_species speciesName=\"Species_2\"/>"
       << "<tr_species speciesName=\"Species_3\"/>"
       << "</tr_speciesList>"
       << "<tr_seedDiam10Cm>0.2</tr_seedDiam10Cm>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_2\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_3\">10.0</tr_madVal>"
       << "</tr_minAdultDBH>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_3\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>"
       << "</trees>"
       << "<grid gridName=\"Average Light\">"
       << "<ma_floatCodes>"
       << "<ma_floatCode label=\"GLI\">0</ma_floatCode>"
       << "</ma_floatCodes>"
       << "<ma_lengthXCells>100</ma_lengthXCells>"
       << "<ma_lengthYCells>100</ma_lengthYCells>"
       << "</grid>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>GLIMapCreator</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>GLILight</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>AverageLight</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RelBAGrowth</behaviorName>"
       << "<version>1.1</version>"
       << "<listPosition>4</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RelUnlimGrowth</behaviorName>"
       << "<version>1.1</version>"
       << "<listPosition>5</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<allometry>"
       << "<tr_whatAdultHeightDiam>"
       << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_2\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_3\">0</tr_wahdVal>"
       << "</tr_whatAdultHeightDiam>"
       << "<tr_whatSaplingHeightDiam>"
       << "<tr_wsahdVal species=\"Species_1\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_2\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_3\">0</tr_wsahdVal>"
       << "</tr_whatSaplingHeightDiam>"
       << "<tr_whatSeedlingHeightDiam>"
       << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_2\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_3\">0</tr_wsehdVal>"
       << "</tr_whatSeedlingHeightDiam>"
       << "<tr_whatAdultCrownRadDiam>"
       << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_2\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_3\">0</tr_wacrdVal>"
       << "</tr_whatAdultCrownRadDiam>"
       << "<tr_whatSaplingCrownRadDiam>"
       << "<tr_wscrdVal species=\"Species_1\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_2\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_3\">0</tr_wscrdVal>"
       << "</tr_whatSaplingCrownRadDiam>"
       << "<tr_whatAdultCrownHeightHeight>"
       << "<tr_wachhVal species=\"Species_1\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_2\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_3\">0</tr_wachhVal>"
       << "</tr_whatAdultCrownHeightHeight>"
       << "<tr_whatSaplingCrownHeightHeight>"
       << "<tr_wschhVal species=\"Species_1\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_2\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_3\">0</tr_wschhVal>"
       << "</tr_whatSaplingCrownHeightHeight>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">30.0</tr_chVal>"
       << "<tr_chVal species=\"Species_2\">30.0</tr_chVal>"
       << "<tr_chVal species=\"Species_3\">30.0</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.108</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_2\">0.107</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_3\">0.109</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_3\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.49</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.58</tr_sachVal>"
       << "<tr_sachVal species=\"Species_3\">0.54</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_3\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.75</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">0.75</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_3\">0.75</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0.0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0.0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_3\">0.0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.063</tr_soahVal>"
       << "<tr_soahVal species=\"Species_2\">0.062333334</tr_soahVal>"
       << "<tr_soahVal species=\"Species_3\">0.063</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_2\">0.03</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_3\">0.03</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "</allometry>"
       << "<GLILight2>"
       << "<li_heightOfFishEyePhoto>0</li_heightOfFishEyePhoto>"
       << "<li_beamFractGlobalRad>0.5</li_beamFractGlobalRad>"
       << "<li_clearSkyTransCoeff>0.65</li_clearSkyTransCoeff>"
       << "<li_julianDayGrowthStarts>120</li_julianDayGrowthStarts>"
       << "<li_julianDayGrowthEnds>270</li_julianDayGrowthEnds>"
       << "<li_minSunAngle>0.779</li_minSunAngle>"
       << "<li_numAltGrids>12</li_numAltGrids>"
       << "<li_numAziGrids>18</li_numAziGrids>"
       << "<li_lightExtinctionCoefficient>"
       << "<li_lecVal species=\"Species_1\">0.399</li_lecVal>"
       << "<li_lecVal species=\"Species_2\">0.399</li_lecVal>"
       << "<li_lecVal species=\"Species_3\">0.399</li_lecVal>"
       << "</li_lightExtinctionCoefficient>"
       << "<li_snagAgeClass1>0</li_snagAgeClass1>"
       << "<li_snagAgeClass2>0</li_snagAgeClass2>"
       << "</GLILight2>"
       << "<GLIMapCreator1>"
       << "<li_minSunAngle>0.779</li_minSunAngle>"
       << "<li_numAltGrids>12</li_numAltGrids>"
       << "<li_numAziGrids>18</li_numAziGrids>"
       << "<li_mapLightHeight>0.0</li_mapLightHeight>"
       << "</GLIMapCreator1>"
       << "<RelBAGrowth4>"
       << "<gr_adultConstAreaInc>"
       << "<gr_acaiVal species=\"Species_1\">0.3</gr_acaiVal>"
       << "<gr_acaiVal species=\"Species_2\">0.3</gr_acaiVal>"
       << "<gr_acaiVal species=\"Species_3\">0.3</gr_acaiVal>"
       << "</gr_adultConstAreaInc>"
       << "<gr_asympDiameterGrowth>"
       << "<gr_adgVal species=\"Species_1\">0.167</gr_adgVal>"
       << "<gr_adgVal species=\"Species_2\">0.125</gr_adgVal>"
       << "<gr_adgVal species=\"Species_3\">0.169</gr_adgVal>"
       << "</gr_asympDiameterGrowth>"
       << "<gr_slopeGrowthResponse>"
       << "<gr_sgrVal species=\"Species_1\">0.027</gr_sgrVal>"
       << "<gr_sgrVal species=\"Species_2\">0.159</gr_sgrVal>"
       << "<gr_sgrVal species=\"Species_3\">0.137</gr_sgrVal>"
       << "</gr_slopeGrowthResponse>"
       << "<gr_relGrowthDiamExp>"
       << "<gr_rgdeVal species=\"Species_1\">1.0</gr_rgdeVal>"
       << "<gr_rgdeVal species=\"Species_2\">1.0</gr_rgdeVal>"
       << "<gr_rgdeVal species=\"Species_3\">1.0</gr_rgdeVal>"
       << "</gr_relGrowthDiamExp>"
       << "</RelBAGrowth4>"
       << "<RelUnlimGrowth5>"
       << "<gr_asympDiameterGrowth>"
       << "<gr_adgVal species=\"Species_1\">0.167</gr_adgVal>"
       << "<gr_adgVal species=\"Species_2\">0.125</gr_adgVal>"
       << "<gr_adgVal species=\"Species_3\">0.169</gr_adgVal>"
       << "</gr_asympDiameterGrowth>"
       << "<gr_slopeGrowthResponse>"
       << "<gr_sgrVal species=\"Species_1\">0.027</gr_sgrVal>"
       << "<gr_sgrVal species=\"Species_2\">0.159</gr_sgrVal>"
       << "<gr_sgrVal species=\"Species_3\">0.137</gr_sgrVal>"
       << "</gr_slopeGrowthResponse>"
       << "<gr_relGrowthDiamExp>"
       << "<gr_rgdeVal species=\"Species_1\">1.0</gr_rgdeVal>"
       << "<gr_rgdeVal species=\"Species_2\">1.0</gr_rgdeVal>"
       << "<gr_rgdeVal species=\"Species_3\">1.0</gr_rgdeVal>"
       << "</gr_relGrowthDiamExp>"
       << "</RelUnlimGrowth5>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
//  WriteXMLFile3()
/////////////////////////////////////////////////////////////////////////////
const char* clTestAverageLight::WriteXMLFile3()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06060101\">"
       << "<plot>"
       << "<timesteps>3</timesteps>"
       << "<randomSeed>0</randomSeed>"
       << "<yearsPerTimestep>5.0</yearsPerTimestep>"
       << "<plot_lenX>100.0</plot_lenX>"
       << "<plot_lenY>100.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>41.92</plot_latitude>"
       << "<plot_title>Default parameter file-use for testing only</plot_title>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"ACRU\"/>"
       << "<tr_species speciesName=\"ACSA\"/>"
       << "<tr_species speciesName=\"BEAL\"/>"
       << "<tr_species speciesName=\"FAGR\"/>"
       << "<tr_species speciesName=\"TSCA\"/>"
       << "<tr_species speciesName=\"FRAM\"/>"
       << "<tr_species speciesName=\"PIST\"/>"
       << "<tr_species speciesName=\"PRSE\"/>"
       << "<tr_species speciesName=\"QURU\"/>"
       << "</tr_speciesList>"
       << "<tr_seedDiam10Cm>0.2</tr_seedDiam10Cm>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"ACRU\">10.0</tr_madVal>"
       << "<tr_madVal species=\"ACSA\">10.0</tr_madVal>"
       << "<tr_madVal species=\"BEAL\">10.0</tr_madVal>"
       << "<tr_madVal species=\"FAGR\">10.0</tr_madVal>"
       << "<tr_madVal species=\"TSCA\">10.0</tr_madVal>"
       << "<tr_madVal species=\"FRAM\">10.0</tr_madVal>"
       << "<tr_madVal species=\"PIST\">10.0</tr_madVal>"
       << "<tr_madVal species=\"PRSE\">10.0</tr_madVal>"
       << "<tr_madVal species=\"QURU\">10.0</tr_madVal>"
       << "</tr_minAdultDBH>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"ACRU\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"ACSA\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"BEAL\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"FAGR\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"TSCA\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"FRAM\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"PIST\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"PRSE\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"QURU\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>";

  WriteTreeFile(oOut);

  oOut << "</trees>"
       << "<grid gridName=\"Average Light\">"
       << "<ma_floatCodes>"
       << "<ma_floatCode label=\"GLI\">0</ma_floatCode>"
       << "</ma_floatCodes>"
       << "<ma_lengthXCells>8</ma_lengthXCells>"
       << "<ma_lengthYCells>16</ma_lengthYCells>"
       << "</grid>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>GLIMapCreator</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>GLILight</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"ACRU\" type=\"Sapling\"/>"
       << "<applyTo species=\"ACSA\" type=\"Sapling\"/>"
       << "<applyTo species=\"FAGR\" type=\"Sapling\"/>"
       << "<applyTo species=\"TSCA\" type=\"Sapling\"/>"
       << "<applyTo species=\"FRAM\" type=\"Sapling\"/>"
       << "<applyTo species=\"PIST\" type=\"Sapling\"/>"
       << "<applyTo species=\"PRSE\" type=\"Sapling\"/>"
       << "<applyTo species=\"QURU\" type=\"Sapling\"/>"
       << "<applyTo species=\"ACSA\" type=\"Adult\"/>"
       << "<applyTo species=\"BEAL\" type=\"Adult\"/>"
       << "<applyTo species=\"FAGR\" type=\"Adult\"/>"
       << "<applyTo species=\"TSCA\" type=\"Adult\"/>"
       << "<applyTo species=\"FRAM\" type=\"Adult\"/>"
       << "<applyTo species=\"PIST\" type=\"Adult\"/>"
       << "<applyTo species=\"PRSE\" type=\"Adult\"/>"
       << "<applyTo species=\"QURU\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>QuadratLight</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"ACRU\" type=\"Adult\"/>"
       << "<applyTo species=\"ACSA\" type=\"Seedling\"/>"
       << "<applyTo species=\"BEAL\" type=\"Seedling\"/>"
       << "<applyTo species=\"FAGR\" type=\"Seedling\"/>"
       << "<applyTo species=\"TSCA\" type=\"Seedling\"/>"
       << "<applyTo species=\"FRAM\" type=\"Seedling\"/>"
       << "<applyTo species=\"PIST\" type=\"Seedling\"/>"
       << "<applyTo species=\"PRSE\" type=\"Seedling\"/>"
       << "<applyTo species=\"QURU\" type=\"Seedling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>AverageLight</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>4</listPosition>"
       << "<applyTo species=\"ACRU\" type=\"Seedling\"/>"
       << "<applyTo species=\"BEAL\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RelUnlimGrowth</behaviorName>"
       << "<version>1.1</version>"
       << "<listPosition>5</listPosition>"
       << "<applyTo species=\"ACRU\" type=\"Seedling\"/>"
       << "<applyTo species=\"ACSA\" type=\"Seedling\"/>"
       << "<applyTo species=\"BEAL\" type=\"Seedling\"/>"
       << "<applyTo species=\"FAGR\" type=\"Seedling\"/>"
       << "<applyTo species=\"TSCA\" type=\"Seedling\"/>"
       << "<applyTo species=\"FRAM\" type=\"Seedling\"/>"
       << "<applyTo species=\"PIST\" type=\"Seedling\"/>"
       << "<applyTo species=\"PRSE\" type=\"Seedling\"/>"
       << "<applyTo species=\"QURU\" type=\"Seedling\"/>"
       << "<applyTo species=\"ACRU\" type=\"Sapling\"/>"
       << "<applyTo species=\"ACSA\" type=\"Sapling\"/>"
       << "<applyTo species=\"BEAL\" type=\"Sapling\"/>"
       << "<applyTo species=\"FAGR\" type=\"Sapling\"/>"
       << "<applyTo species=\"TSCA\" type=\"Sapling\"/>"
       << "<applyTo species=\"FRAM\" type=\"Sapling\"/>"
       << "<applyTo species=\"PIST\" type=\"Sapling\"/>"
       << "<applyTo species=\"PRSE\" type=\"Sapling\"/>"
       << "<applyTo species=\"QURU\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>ConstRadialGrowth</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>6</listPosition>"
       << "<applyTo species=\"ACRU\" type=\"Adult\"/>"
       << "<applyTo species=\"ACSA\" type=\"Adult\"/>"
       << "<applyTo species=\"BEAL\" type=\"Adult\"/>"
       << "<applyTo species=\"FAGR\" type=\"Adult\"/>"
       << "<applyTo species=\"TSCA\" type=\"Adult\"/>"
       << "<applyTo species=\"FRAM\" type=\"Adult\"/>"
       << "<applyTo species=\"PIST\" type=\"Adult\"/>"
       << "<applyTo species=\"PRSE\" type=\"Adult\"/>"
       << "<applyTo species=\"QURU\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<allometry>"
       << "<tr_whatAdultHeightDiam>"
       << "<tr_wahdVal species=\"ACRU\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"ACSA\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"BEAL\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"FAGR\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"TSCA\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"FRAM\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"PIST\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"PRSE\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"QURU\">0</tr_wahdVal>"
       << "</tr_whatAdultHeightDiam>"
       << "<tr_whatSaplingHeightDiam>"
       << "<tr_wsahdVal species=\"ACRU\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"ACSA\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"BEAL\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"FAGR\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"TSCA\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"FRAM\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"PIST\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"PRSE\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"QURU\">0</tr_wsahdVal>"
       << "</tr_whatSaplingHeightDiam>"
       << "<tr_whatSeedlingHeightDiam>"
       << "<tr_wsehdVal species=\"ACRU\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"ACSA\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"BEAL\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"FAGR\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"TSCA\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"FRAM\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"PIST\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"PRSE\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"QURU\">0</tr_wsehdVal>"
       << "</tr_whatSeedlingHeightDiam>"
       << "<tr_whatAdultCrownRadDiam>"
       << "<tr_wacrdVal species=\"ACRU\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"ACSA\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"BEAL\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"FAGR\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"TSCA\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"FRAM\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"PIST\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"PRSE\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"QURU\">0</tr_wacrdVal>"
       << "</tr_whatAdultCrownRadDiam>"
       << "<tr_whatSaplingCrownRadDiam>"
       << "<tr_wscrdVal species=\"ACRU\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"ACSA\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"BEAL\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"FAGR\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"TSCA\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"FRAM\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"PIST\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"PRSE\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"QURU\">0</tr_wscrdVal>"
       << "</tr_whatSaplingCrownRadDiam>"
       << "<tr_whatAdultCrownHeightHeight>"
       << "<tr_wachhVal species=\"ACRU\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"ACSA\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"BEAL\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"FAGR\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"TSCA\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"FRAM\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"PIST\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"PRSE\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"QURU\">0</tr_wachhVal>"
       << "</tr_whatAdultCrownHeightHeight>"
       << "<tr_whatSaplingCrownHeightHeight>"
       << "<tr_wschhVal species=\"ACRU\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"ACSA\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"BEAL\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"FAGR\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"TSCA\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"FRAM\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"PIST\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"PRSE\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"QURU\">0</tr_wschhVal>"
       << "</tr_whatSaplingCrownHeightHeight>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"ACRU\">30.0</tr_chVal>"
       << "<tr_chVal species=\"ACSA\">30.0</tr_chVal>"
       << "<tr_chVal species=\"BEAL\">30.0</tr_chVal>"
       << "<tr_chVal species=\"FAGR\">30.0</tr_chVal>"
       << "<tr_chVal species=\"TSCA\">30.0</tr_chVal>"
       << "<tr_chVal species=\"FRAM\">30.0</tr_chVal>"
       << "<tr_chVal species=\"PIST\">30.0</tr_chVal>"
       << "<tr_chVal species=\"PRSE\">30.0</tr_chVal>"
       << "<tr_chVal species=\"QURU\">30.0</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"ACRU\">0.108</tr_sacrVal>"
       << "<tr_sacrVal species=\"ACSA\">0.107</tr_sacrVal>"
       << "<tr_sacrVal species=\"BEAL\">0.109</tr_sacrVal>"
       << "<tr_sacrVal species=\"FAGR\">0.152</tr_sacrVal>"
       << "<tr_sacrVal species=\"TSCA\">0.1</tr_sacrVal>"
       << "<tr_sacrVal species=\"FRAM\">0.095</tr_sacrVal>"
       << "<tr_sacrVal species=\"PIST\">0.087</tr_sacrVal>"
       << "<tr_sacrVal species=\"PRSE\">0.116</tr_sacrVal>"
       << "<tr_sacrVal species=\"QURU\">0.119</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"ACRU\">1.0</tr_screVal>"
       << "<tr_screVal species=\"ACSA\">1.0</tr_screVal>"
       << "<tr_screVal species=\"BEAL\">1.0</tr_screVal>"
       << "<tr_screVal species=\"FAGR\">1.0</tr_screVal>"
       << "<tr_screVal species=\"TSCA\">1.0</tr_screVal>"
       << "<tr_screVal species=\"FRAM\">1.0</tr_screVal>"
       << "<tr_screVal species=\"PIST\">1.0</tr_screVal>"
       << "<tr_screVal species=\"PRSE\">1.0</tr_screVal>"
       << "<tr_screVal species=\"QURU\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"ACRU\">0.49</tr_sachVal>"
       << "<tr_sachVal species=\"ACSA\">0.58</tr_sachVal>"
       << "<tr_sachVal species=\"BEAL\">0.54</tr_sachVal>"
       << "<tr_sachVal species=\"FAGR\">0.664</tr_sachVal>"
       << "<tr_sachVal species=\"TSCA\">0.846</tr_sachVal>"
       << "<tr_sachVal species=\"FRAM\">0.319</tr_sachVal>"
       << "<tr_sachVal species=\"PIST\">0.413</tr_sachVal>"
       << "<tr_sachVal species=\"PRSE\">0.37</tr_sachVal>"
       << "<tr_sachVal species=\"QURU\">0.413</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"ACRU\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"ACSA\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"BEAL\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"FAGR\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"TSCA\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"FRAM\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"PIST\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"PRSE\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"QURU\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"ACRU\">0.75</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"ACSA\">0.75</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"BEAL\">0.75</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"FAGR\">0.75</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"TSCA\">0.75</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"FRAM\">0.75</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"PIST\">0.75</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"PRSE\">0.75</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"QURU\">0.75</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"ACRU\">0.0</tr_idtdVal>"
       << "<tr_idtdVal species=\"ACSA\">0.0</tr_idtdVal>"
       << "<tr_idtdVal species=\"BEAL\">0.0</tr_idtdVal>"
       << "<tr_idtdVal species=\"FAGR\">0.0</tr_idtdVal>"
       << "<tr_idtdVal species=\"TSCA\">0.0</tr_idtdVal>"
       << "<tr_idtdVal species=\"FRAM\">0.0</tr_idtdVal>"
       << "<tr_idtdVal species=\"PIST\">0.0</tr_idtdVal>"
       << "<tr_idtdVal species=\"PRSE\">0.0</tr_idtdVal>"
       << "<tr_idtdVal species=\"QURU\">0.0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"ACRU\">0.063</tr_soahVal>"
       << "<tr_soahVal species=\"ACSA\">0.062333334</tr_soahVal>"
       << "<tr_soahVal species=\"BEAL\">0.063</tr_soahVal>"
       << "<tr_soahVal species=\"FAGR\">0.03533333</tr_soahVal>"
       << "<tr_soahVal species=\"TSCA\">0.024333334</tr_soahVal>"
       << "<tr_soahVal species=\"FRAM\">0.055999998</tr_soahVal>"
       << "<tr_soahVal species=\"PIST\">0.033333335</tr_soahVal>"
       << "<tr_soahVal species=\"PRSE\">0.045</tr_soahVal>"
       << "<tr_soahVal species=\"QURU\">0.042</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"ACRU\">0.03</tr_sohdVal>"
       << "<tr_sohdVal species=\"ACSA\">0.03</tr_sohdVal>"
       << "<tr_sohdVal species=\"BEAL\">0.03</tr_sohdVal>"
       << "<tr_sohdVal species=\"FAGR\">0.03</tr_sohdVal>"
       << "<tr_sohdVal species=\"TSCA\">0.03</tr_sohdVal>"
       << "<tr_sohdVal species=\"FRAM\">0.03</tr_sohdVal>"
       << "<tr_sohdVal species=\"PIST\">0.03</tr_sohdVal>"
       << "<tr_sohdVal species=\"PRSE\">0.03</tr_sohdVal>"
       << "<tr_sohdVal species=\"QURU\">0.03</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "</allometry>"
       << "<GLILight2>"
       << "<li_heightOfFishEyePhoto>0</li_heightOfFishEyePhoto>"
       << "<li_beamFractGlobalRad>0.5</li_beamFractGlobalRad>"
       << "<li_clearSkyTransCoeff>0.65</li_clearSkyTransCoeff>"
       << "<li_julianDayGrowthStarts>120</li_julianDayGrowthStarts>"
       << "<li_julianDayGrowthEnds>270</li_julianDayGrowthEnds>"
       << "<li_minSunAngle>0.779</li_minSunAngle>"
       << "<li_numAltGrids>12</li_numAltGrids>"
       << "<li_numAziGrids>18</li_numAziGrids>"
       << "<li_lightExtinctionCoefficient>"
       << "<li_lecVal species=\"ACRU\">0.399</li_lecVal>"
       << "<li_lecVal species=\"ACSA\">0.399</li_lecVal>"
       << "<li_lecVal species=\"BEAL\">0.399</li_lecVal>"
       << "<li_lecVal species=\"FAGR\">0.064</li_lecVal>"
       << "<li_lecVal species=\"TSCA\">0.064</li_lecVal>"
       << "<li_lecVal species=\"FRAM\">0.399</li_lecVal>"
       << "<li_lecVal species=\"PIST\">0.399</li_lecVal>"
       << "<li_lecVal species=\"PRSE\">0.399</li_lecVal>"
       << "<li_lecVal species=\"QURU\">0.566</li_lecVal>"
       << "</li_lightExtinctionCoefficient>"
       << "<li_snagAgeClass1>0</li_snagAgeClass1>"
       << "<li_snagAgeClass2>0</li_snagAgeClass2>"
       << "</GLILight2>"
       << "<QuadratLight3>"
       << "<li_minSunAngle>0.779</li_minSunAngle>"
       << "<li_numAltGrids>12</li_numAltGrids>"
       << "<li_numAziGrids>18</li_numAziGrids>"
       << "<li_quadratLightHeight>0.675</li_quadratLightHeight>"
       << "<li_quadratAllGLIs>0</li_quadratAllGLIs>"
       << "</QuadratLight3>"
       << "<GLIMapCreator1>"
       << "<li_minSunAngle>0.779</li_minSunAngle>"
       << "<li_numAltGrids>12</li_numAltGrids>"
       << "<li_numAziGrids>18</li_numAziGrids>"
       << "<li_mapLightHeight>0.0</li_mapLightHeight>"
       << "</GLIMapCreator1>"
       << "<ConstRadialGrowth6>"
       << "<gr_adultConstRadialInc>"
       << "<gr_acriVal species=\"ACRU\">3</gr_acriVal>"
       << "<gr_acriVal species=\"ACSA\">3</gr_acriVal>"
       << "<gr_acriVal species=\"BEAL\">3</gr_acriVal>"
       << "<gr_acriVal species=\"FAGR\">3</gr_acriVal>"
       << "<gr_acriVal species=\"TSCA\">3</gr_acriVal>"
       << "<gr_acriVal species=\"FRAM\">3</gr_acriVal>"
       << "<gr_acriVal species=\"PIST\">3</gr_acriVal>"
       << "<gr_acriVal species=\"PRSE\">3</gr_acriVal>"
       << "<gr_acriVal species=\"QURU\">3</gr_acriVal>"
       << "</gr_adultConstRadialInc>"
       << "</ConstRadialGrowth6>"
       << "<RelUnlimGrowth5>"
       << "<gr_asympDiameterGrowth>"
       << "<gr_adgVal species=\"ACRU\">0.167</gr_adgVal>"
       << "<gr_adgVal species=\"ACSA\">0.125</gr_adgVal>"
       << "<gr_adgVal species=\"BEAL\">0.169</gr_adgVal>"
       << "<gr_adgVal species=\"FAGR\">0.152</gr_adgVal>"
       << "<gr_adgVal species=\"TSCA\">0.229</gr_adgVal>"
       << "<gr_adgVal species=\"FRAM\">0.226</gr_adgVal>"
       << "<gr_adgVal species=\"PIST\">0.23</gr_adgVal>"
       << "<gr_adgVal species=\"PRSE\">0.249</gr_adgVal>"
       << "<gr_adgVal species=\"QURU\">0.266</gr_adgVal>"
       << "</gr_asympDiameterGrowth>"
       << "<gr_slopeGrowthResponse>"
       << "<gr_sgrVal species=\"ACRU\">0.027</gr_sgrVal>"
       << "<gr_sgrVal species=\"ACSA\">0.159</gr_sgrVal>"
       << "<gr_sgrVal species=\"BEAL\">0.137</gr_sgrVal>"
       << "<gr_sgrVal species=\"FAGR\">0.075</gr_sgrVal>"
       << "<gr_sgrVal species=\"TSCA\">0.051</gr_sgrVal>"
       << "<gr_sgrVal species=\"FRAM\">0.025</gr_sgrVal>"
       << "<gr_sgrVal species=\"PIST\">0.019</gr_sgrVal>"
       << "<gr_sgrVal species=\"PRSE\">0.064</gr_sgrVal>"
       << "<gr_sgrVal species=\"QURU\">0.022</gr_sgrVal>"
       << "</gr_slopeGrowthResponse>"
       << "<gr_relGrowthDiamExp>"
       << "<gr_rgdeVal species=\"ACRU\">1.0</gr_rgdeVal>"
       << "<gr_rgdeVal species=\"ACSA\">1.0</gr_rgdeVal>"
       << "<gr_rgdeVal species=\"BEAL\">1.0</gr_rgdeVal>"
       << "<gr_rgdeVal species=\"FAGR\">1.0</gr_rgdeVal>"
       << "<gr_rgdeVal species=\"TSCA\">1.0</gr_rgdeVal>"
       << "<gr_rgdeVal species=\"FRAM\">1.0</gr_rgdeVal>"
       << "<gr_rgdeVal species=\"PIST\">1.0</gr_rgdeVal>"
       << "<gr_rgdeVal species=\"PRSE\">1.0</gr_rgdeVal>"
       << "<gr_rgdeVal species=\"QURU\">1.0</gr_rgdeVal>"
       << "</gr_relGrowthDiamExp>"
       << "</RelUnlimGrowth5>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
//  WriteXMLFile4()
/////////////////////////////////////////////////////////////////////////////
const char* clTestAverageLight::WriteXMLFile4()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06060101\">"
       << "<plot>"
       << "<timesteps>3</timesteps>"
       << "<randomSeed>0</randomSeed>"
       << "<yearsPerTimestep>5.0</yearsPerTimestep>"
       << "<plot_lenX>100.0</plot_lenX>"
       << "<plot_lenY>100.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>41.92</plot_latitude>"
       << "<plot_title>Default parameter file-use for testing only</plot_title>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"ACRU\"/>"
       << "<tr_species speciesName=\"ACSA\"/>"
       << "<tr_species speciesName=\"BEAL\"/>"
       << "<tr_species speciesName=\"FAGR\"/>"
       << "<tr_species speciesName=\"TSCA\"/>"
       << "<tr_species speciesName=\"FRAM\"/>"
       << "<tr_species speciesName=\"PIST\"/>"
       << "<tr_species speciesName=\"PRSE\"/>"
       << "<tr_species speciesName=\"QURU\"/>"
       << "</tr_speciesList>"
       << "<tr_seedDiam10Cm>0.2</tr_seedDiam10Cm>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"ACRU\">10.0</tr_madVal>"
       << "<tr_madVal species=\"ACSA\">10.0</tr_madVal>"
       << "<tr_madVal species=\"BEAL\">10.0</tr_madVal>"
       << "<tr_madVal species=\"FAGR\">10.0</tr_madVal>"
       << "<tr_madVal species=\"TSCA\">10.0</tr_madVal>"
       << "<tr_madVal species=\"FRAM\">10.0</tr_madVal>"
       << "<tr_madVal species=\"PIST\">10.0</tr_madVal>"
       << "<tr_madVal species=\"PRSE\">10.0</tr_madVal>"
       << "<tr_madVal species=\"QURU\">10.0</tr_madVal>"
       << "</tr_minAdultDBH>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"ACRU\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"ACSA\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"BEAL\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"FAGR\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"TSCA\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"FRAM\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"PIST\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"PRSE\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"QURU\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>";

  WriteTreeFile(oOut);

  oOut << "</trees>"
       << "<grid gridName=\"Average Light\">"
       << "<ma_floatCodes>"
       << "<ma_floatCode label=\"GLI\">0</ma_floatCode>"
       << "</ma_floatCodes>"
       << "<ma_lengthXCells>10</ma_lengthXCells>"
       << "<ma_lengthYCells>10</ma_lengthYCells>"
       << "</grid>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>GLIMapCreator</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>GLILight</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"ACRU\" type=\"Sapling\"/>"
       << "<applyTo species=\"ACSA\" type=\"Sapling\"/>"
       << "<applyTo species=\"FAGR\" type=\"Sapling\"/>"
       << "<applyTo species=\"TSCA\" type=\"Sapling\"/>"
       << "<applyTo species=\"FRAM\" type=\"Sapling\"/>"
       << "<applyTo species=\"PIST\" type=\"Sapling\"/>"
       << "<applyTo species=\"PRSE\" type=\"Sapling\"/>"
       << "<applyTo species=\"QURU\" type=\"Sapling\"/>"
       << "<applyTo species=\"ACSA\" type=\"Adult\"/>"
       << "<applyTo species=\"BEAL\" type=\"Adult\"/>"
       << "<applyTo species=\"FAGR\" type=\"Adult\"/>"
       << "<applyTo species=\"TSCA\" type=\"Adult\"/>"
       << "<applyTo species=\"FRAM\" type=\"Adult\"/>"
       << "<applyTo species=\"PIST\" type=\"Adult\"/>"
       << "<applyTo species=\"PRSE\" type=\"Adult\"/>"
       << "<applyTo species=\"QURU\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>QuadratLight</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"ACRU\" type=\"Seedling\"/>"
       << "<applyTo species=\"ACSA\" type=\"Seedling\"/>"
       << "<applyTo species=\"BEAL\" type=\"Seedling\"/>"
       << "<applyTo species=\"FAGR\" type=\"Seedling\"/>"
       << "<applyTo species=\"TSCA\" type=\"Seedling\"/>"
       << "<applyTo species=\"FRAM\" type=\"Seedling\"/>"
       << "<applyTo species=\"PIST\" type=\"Seedling\"/>"
       << "<applyTo species=\"PRSE\" type=\"Seedling\"/>"
       << "<applyTo species=\"QURU\" type=\"Seedling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>AverageLight</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>4</listPosition>"
       << "<applyTo species=\"ACRU\" type=\"Adult\"/>"
       << "<applyTo species=\"BEAL\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RelUnlimGrowth</behaviorName>"
       << "<version>1.1</version>"
       << "<listPosition>5</listPosition>"
       << "<applyTo species=\"ACRU\" type=\"Seedling\"/>"
       << "<applyTo species=\"ACSA\" type=\"Seedling\"/>"
       << "<applyTo species=\"BEAL\" type=\"Seedling\"/>"
       << "<applyTo species=\"FAGR\" type=\"Seedling\"/>"
       << "<applyTo species=\"TSCA\" type=\"Seedling\"/>"
       << "<applyTo species=\"FRAM\" type=\"Seedling\"/>"
       << "<applyTo species=\"PIST\" type=\"Seedling\"/>"
       << "<applyTo species=\"PRSE\" type=\"Seedling\"/>"
       << "<applyTo species=\"QURU\" type=\"Seedling\"/>"
       << "<applyTo species=\"ACRU\" type=\"Sapling\"/>"
       << "<applyTo species=\"ACSA\" type=\"Sapling\"/>"
       << "<applyTo species=\"BEAL\" type=\"Sapling\"/>"
       << "<applyTo species=\"FAGR\" type=\"Sapling\"/>"
       << "<applyTo species=\"TSCA\" type=\"Sapling\"/>"
       << "<applyTo species=\"FRAM\" type=\"Sapling\"/>"
       << "<applyTo species=\"PIST\" type=\"Sapling\"/>"
       << "<applyTo species=\"PRSE\" type=\"Sapling\"/>"
       << "<applyTo species=\"QURU\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>ConstRadialGrowth</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>6</listPosition>"
       << "<applyTo species=\"ACRU\" type=\"Adult\"/>"
       << "<applyTo species=\"ACSA\" type=\"Adult\"/>"
       << "<applyTo species=\"BEAL\" type=\"Adult\"/>"
       << "<applyTo species=\"FAGR\" type=\"Adult\"/>"
       << "<applyTo species=\"TSCA\" type=\"Adult\"/>"
       << "<applyTo species=\"FRAM\" type=\"Adult\"/>"
       << "<applyTo species=\"PIST\" type=\"Adult\"/>"
       << "<applyTo species=\"PRSE\" type=\"Adult\"/>"
       << "<applyTo species=\"QURU\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<allometry>"
       << "<tr_whatAdultHeightDiam>"
       << "<tr_wahdVal species=\"ACRU\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"ACSA\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"BEAL\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"FAGR\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"TSCA\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"FRAM\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"PIST\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"PRSE\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"QURU\">0</tr_wahdVal>"
       << "</tr_whatAdultHeightDiam>"
       << "<tr_whatSaplingHeightDiam>"
       << "<tr_wsahdVal species=\"ACRU\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"ACSA\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"BEAL\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"FAGR\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"TSCA\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"FRAM\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"PIST\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"PRSE\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"QURU\">0</tr_wsahdVal>"
       << "</tr_whatSaplingHeightDiam>"
       << "<tr_whatSeedlingHeightDiam>"
       << "<tr_wsehdVal species=\"ACRU\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"ACSA\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"BEAL\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"FAGR\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"TSCA\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"FRAM\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"PIST\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"PRSE\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"QURU\">0</tr_wsehdVal>"
       << "</tr_whatSeedlingHeightDiam>"
       << "<tr_whatAdultCrownRadDiam>"
       << "<tr_wacrdVal species=\"ACRU\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"ACSA\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"BEAL\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"FAGR\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"TSCA\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"FRAM\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"PIST\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"PRSE\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"QURU\">0</tr_wacrdVal>"
       << "</tr_whatAdultCrownRadDiam>"
       << "<tr_whatSaplingCrownRadDiam>"
       << "<tr_wscrdVal species=\"ACRU\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"ACSA\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"BEAL\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"FAGR\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"TSCA\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"FRAM\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"PIST\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"PRSE\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"QURU\">0</tr_wscrdVal>"
       << "</tr_whatSaplingCrownRadDiam>"
       << "<tr_whatAdultCrownHeightHeight>"
       << "<tr_wachhVal species=\"ACRU\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"ACSA\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"BEAL\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"FAGR\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"TSCA\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"FRAM\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"PIST\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"PRSE\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"QURU\">0</tr_wachhVal>"
       << "</tr_whatAdultCrownHeightHeight>"
       << "<tr_whatSaplingCrownHeightHeight>"
       << "<tr_wschhVal species=\"ACRU\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"ACSA\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"BEAL\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"FAGR\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"TSCA\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"FRAM\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"PIST\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"PRSE\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"QURU\">0</tr_wschhVal>"
       << "</tr_whatSaplingCrownHeightHeight>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"ACRU\">30.0</tr_chVal>"
       << "<tr_chVal species=\"ACSA\">30.0</tr_chVal>"
       << "<tr_chVal species=\"BEAL\">30.0</tr_chVal>"
       << "<tr_chVal species=\"FAGR\">30.0</tr_chVal>"
       << "<tr_chVal species=\"TSCA\">30.0</tr_chVal>"
       << "<tr_chVal species=\"FRAM\">30.0</tr_chVal>"
       << "<tr_chVal species=\"PIST\">30.0</tr_chVal>"
       << "<tr_chVal species=\"PRSE\">30.0</tr_chVal>"
       << "<tr_chVal species=\"QURU\">30.0</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"ACRU\">0.108</tr_sacrVal>"
       << "<tr_sacrVal species=\"ACSA\">0.107</tr_sacrVal>"
       << "<tr_sacrVal species=\"BEAL\">0.109</tr_sacrVal>"
       << "<tr_sacrVal species=\"FAGR\">0.152</tr_sacrVal>"
       << "<tr_sacrVal species=\"TSCA\">0.1</tr_sacrVal>"
       << "<tr_sacrVal species=\"FRAM\">0.095</tr_sacrVal>"
       << "<tr_sacrVal species=\"PIST\">0.087</tr_sacrVal>"
       << "<tr_sacrVal species=\"PRSE\">0.116</tr_sacrVal>"
       << "<tr_sacrVal species=\"QURU\">0.119</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"ACRU\">1.0</tr_screVal>"
       << "<tr_screVal species=\"ACSA\">1.0</tr_screVal>"
       << "<tr_screVal species=\"BEAL\">1.0</tr_screVal>"
       << "<tr_screVal species=\"FAGR\">1.0</tr_screVal>"
       << "<tr_screVal species=\"TSCA\">1.0</tr_screVal>"
       << "<tr_screVal species=\"FRAM\">1.0</tr_screVal>"
       << "<tr_screVal species=\"PIST\">1.0</tr_screVal>"
       << "<tr_screVal species=\"PRSE\">1.0</tr_screVal>"
       << "<tr_screVal species=\"QURU\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"ACRU\">0.49</tr_sachVal>"
       << "<tr_sachVal species=\"ACSA\">0.58</tr_sachVal>"
       << "<tr_sachVal species=\"BEAL\">0.54</tr_sachVal>"
       << "<tr_sachVal species=\"FAGR\">0.664</tr_sachVal>"
       << "<tr_sachVal species=\"TSCA\">0.846</tr_sachVal>"
       << "<tr_sachVal species=\"FRAM\">0.319</tr_sachVal>"
       << "<tr_sachVal species=\"PIST\">0.413</tr_sachVal>"
       << "<tr_sachVal species=\"PRSE\">0.37</tr_sachVal>"
       << "<tr_sachVal species=\"QURU\">0.413</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"ACRU\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"ACSA\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"BEAL\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"FAGR\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"TSCA\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"FRAM\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"PIST\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"PRSE\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"QURU\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"ACRU\">0.75</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"ACSA\">0.75</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"BEAL\">0.75</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"FAGR\">0.75</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"TSCA\">0.75</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"FRAM\">0.75</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"PIST\">0.75</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"PRSE\">0.75</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"QURU\">0.75</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"ACRU\">0.0</tr_idtdVal>"
       << "<tr_idtdVal species=\"ACSA\">0.0</tr_idtdVal>"
       << "<tr_idtdVal species=\"BEAL\">0.0</tr_idtdVal>"
       << "<tr_idtdVal species=\"FAGR\">0.0</tr_idtdVal>"
       << "<tr_idtdVal species=\"TSCA\">0.0</tr_idtdVal>"
       << "<tr_idtdVal species=\"FRAM\">0.0</tr_idtdVal>"
       << "<tr_idtdVal species=\"PIST\">0.0</tr_idtdVal>"
       << "<tr_idtdVal species=\"PRSE\">0.0</tr_idtdVal>"
       << "<tr_idtdVal species=\"QURU\">0.0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"ACRU\">0.063</tr_soahVal>"
       << "<tr_soahVal species=\"ACSA\">0.062333334</tr_soahVal>"
       << "<tr_soahVal species=\"BEAL\">0.063</tr_soahVal>"
       << "<tr_soahVal species=\"FAGR\">0.03533333</tr_soahVal>"
       << "<tr_soahVal species=\"TSCA\">0.024333334</tr_soahVal>"
       << "<tr_soahVal species=\"FRAM\">0.055999998</tr_soahVal>"
       << "<tr_soahVal species=\"PIST\">0.033333335</tr_soahVal>"
       << "<tr_soahVal species=\"PRSE\">0.045</tr_soahVal>"
       << "<tr_soahVal species=\"QURU\">0.042</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"ACRU\">0.03</tr_sohdVal>"
       << "<tr_sohdVal species=\"ACSA\">0.03</tr_sohdVal>"
       << "<tr_sohdVal species=\"BEAL\">0.03</tr_sohdVal>"
       << "<tr_sohdVal species=\"FAGR\">0.03</tr_sohdVal>"
       << "<tr_sohdVal species=\"TSCA\">0.03</tr_sohdVal>"
       << "<tr_sohdVal species=\"FRAM\">0.03</tr_sohdVal>"
       << "<tr_sohdVal species=\"PIST\">0.03</tr_sohdVal>"
       << "<tr_sohdVal species=\"PRSE\">0.03</tr_sohdVal>"
       << "<tr_sohdVal species=\"QURU\">0.03</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "</allometry>"
       << "<GLILight2>"
       << "<li_heightOfFishEyePhoto>0</li_heightOfFishEyePhoto>"
       << "<li_beamFractGlobalRad>0.5</li_beamFractGlobalRad>"
       << "<li_clearSkyTransCoeff>0.65</li_clearSkyTransCoeff>"
       << "<li_julianDayGrowthStarts>120</li_julianDayGrowthStarts>"
       << "<li_julianDayGrowthEnds>270</li_julianDayGrowthEnds>"
       << "<li_minSunAngle>0.779</li_minSunAngle>"
       << "<li_numAltGrids>12</li_numAltGrids>"
       << "<li_numAziGrids>18</li_numAziGrids>"
       << "<li_lightExtinctionCoefficient>"
       << "<li_lecVal species=\"ACRU\">0.399</li_lecVal>"
       << "<li_lecVal species=\"ACSA\">0.399</li_lecVal>"
       << "<li_lecVal species=\"BEAL\">0.399</li_lecVal>"
       << "<li_lecVal species=\"FAGR\">0.064</li_lecVal>"
       << "<li_lecVal species=\"TSCA\">0.064</li_lecVal>"
       << "<li_lecVal species=\"FRAM\">0.399</li_lecVal>"
       << "<li_lecVal species=\"PIST\">0.399</li_lecVal>"
       << "<li_lecVal species=\"PRSE\">0.399</li_lecVal>"
       << "<li_lecVal species=\"QURU\">0.566</li_lecVal>"
       << "</li_lightExtinctionCoefficient>"
       << "<li_snagAgeClass1>0</li_snagAgeClass1>"
       << "<li_snagAgeClass2>0</li_snagAgeClass2>"
       << "</GLILight2>"
       << "<QuadratLight3>"
       << "<li_minSunAngle>0.779</li_minSunAngle>"
       << "<li_numAltGrids>12</li_numAltGrids>"
       << "<li_numAziGrids>18</li_numAziGrids>"
       << "<li_quadratLightHeight>0.675</li_quadratLightHeight>"
       << "<li_quadratAllGLIs>0</li_quadratAllGLIs>"
       << "</QuadratLight3>"
       << "<GLIMapCreator1>"
       << "<li_minSunAngle>0.779</li_minSunAngle>"
       << "<li_numAltGrids>12</li_numAltGrids>"
       << "<li_numAziGrids>18</li_numAziGrids>"
       << "<li_mapLightHeight>0.0</li_mapLightHeight>"
       << "</GLIMapCreator1>"
       << "<ConstRadialGrowth6>"
       << "<gr_adultConstRadialInc>"
       << "<gr_acriVal species=\"ACRU\">3</gr_acriVal>"
       << "<gr_acriVal species=\"ACSA\">3</gr_acriVal>"
       << "<gr_acriVal species=\"BEAL\">3</gr_acriVal>"
       << "<gr_acriVal species=\"FAGR\">3</gr_acriVal>"
       << "<gr_acriVal species=\"TSCA\">3</gr_acriVal>"
       << "<gr_acriVal species=\"FRAM\">3</gr_acriVal>"
       << "<gr_acriVal species=\"PIST\">3</gr_acriVal>"
       << "<gr_acriVal species=\"PRSE\">3</gr_acriVal>"
       << "<gr_acriVal species=\"QURU\">3</gr_acriVal>"
       << "</gr_adultConstRadialInc>"
       << "</ConstRadialGrowth6>"
       << "<RelUnlimGrowth5>"
       << "<gr_asympDiameterGrowth>"
       << "<gr_adgVal species=\"ACRU\">0.167</gr_adgVal>"
       << "<gr_adgVal species=\"ACSA\">0.125</gr_adgVal>"
       << "<gr_adgVal species=\"BEAL\">0.169</gr_adgVal>"
       << "<gr_adgVal species=\"FAGR\">0.152</gr_adgVal>"
       << "<gr_adgVal species=\"TSCA\">0.229</gr_adgVal>"
       << "<gr_adgVal species=\"FRAM\">0.226</gr_adgVal>"
       << "<gr_adgVal species=\"PIST\">0.23</gr_adgVal>"
       << "<gr_adgVal species=\"PRSE\">0.249</gr_adgVal>"
       << "<gr_adgVal species=\"QURU\">0.266</gr_adgVal>"
       << "</gr_asympDiameterGrowth>"
       << "<gr_slopeGrowthResponse>"
       << "<gr_sgrVal species=\"ACRU\">0.027</gr_sgrVal>"
       << "<gr_sgrVal species=\"ACSA\">0.159</gr_sgrVal>"
       << "<gr_sgrVal species=\"BEAL\">0.137</gr_sgrVal>"
       << "<gr_sgrVal species=\"FAGR\">0.075</gr_sgrVal>"
       << "<gr_sgrVal species=\"TSCA\">0.051</gr_sgrVal>"
       << "<gr_sgrVal species=\"FRAM\">0.025</gr_sgrVal>"
       << "<gr_sgrVal species=\"PIST\">0.019</gr_sgrVal>"
       << "<gr_sgrVal species=\"PRSE\">0.064</gr_sgrVal>"
       << "<gr_sgrVal species=\"QURU\">0.022</gr_sgrVal>"
       << "</gr_slopeGrowthResponse>"
       << "<gr_relGrowthDiamExp>"
       << "<gr_rgdeVal species=\"ACRU\">1.0</gr_rgdeVal>"
       << "<gr_rgdeVal species=\"ACSA\">1.0</gr_rgdeVal>"
       << "<gr_rgdeVal species=\"BEAL\">1.0</gr_rgdeVal>"
       << "<gr_rgdeVal species=\"FAGR\">1.0</gr_rgdeVal>"
       << "<gr_rgdeVal species=\"TSCA\">1.0</gr_rgdeVal>"
       << "<gr_rgdeVal species=\"FRAM\">1.0</gr_rgdeVal>"
       << "<gr_rgdeVal species=\"PIST\">1.0</gr_rgdeVal>"
       << "<gr_rgdeVal species=\"PRSE\">1.0</gr_rgdeVal>"
       << "<gr_rgdeVal species=\"QURU\">1.0</gr_rgdeVal>"
       << "</gr_relGrowthDiamExp>"
       << "</RelUnlimGrowth5>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
//  WriteXMLFile5()
/////////////////////////////////////////////////////////////////////////////
const char* clTestAverageLight::WriteXMLFile5()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06060101\">"
       << "<plot>"
       << "<timesteps>3</timesteps>"
       << "<randomSeed>0</randomSeed>"
       << "<yearsPerTimestep>5.0</yearsPerTimestep>"
       << "<plot_lenX>100.0</plot_lenX>"
       << "<plot_lenY>100.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>41.92</plot_latitude>"
       << "<plot_title>Default parameter file-use for testing only</plot_title>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"ACRU\"/>"
       << "<tr_species speciesName=\"ACSA\"/>"
       << "<tr_species speciesName=\"BEAL\"/>"
       << "<tr_species speciesName=\"FAGR\"/>"
       << "<tr_species speciesName=\"TSCA\"/>"
       << "<tr_species speciesName=\"FRAM\"/>"
       << "<tr_species speciesName=\"PIST\"/>"
       << "<tr_species speciesName=\"PRSE\"/>"
       << "<tr_species speciesName=\"QURU\"/>"
       << "</tr_speciesList>"
       << "<tr_seedDiam10Cm>0.2</tr_seedDiam10Cm>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"ACRU\">10.0</tr_madVal>"
       << "<tr_madVal species=\"ACSA\">10.0</tr_madVal>"
       << "<tr_madVal species=\"BEAL\">10.0</tr_madVal>"
       << "<tr_madVal species=\"FAGR\">10.0</tr_madVal>"
       << "<tr_madVal species=\"TSCA\">10.0</tr_madVal>"
       << "<tr_madVal species=\"FRAM\">10.0</tr_madVal>"
       << "<tr_madVal species=\"PIST\">10.0</tr_madVal>"
       << "<tr_madVal species=\"PRSE\">10.0</tr_madVal>"
       << "<tr_madVal species=\"QURU\">10.0</tr_madVal>"
       << "</tr_minAdultDBH>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"ACRU\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"ACSA\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"BEAL\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"FAGR\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"TSCA\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"FRAM\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"PIST\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"PRSE\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"QURU\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>";

  WriteTreeFile(oOut);

  oOut << "</trees>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>GLIMapCreator</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>GLILight</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"ACRU\" type=\"Sapling\"/>"
       << "<applyTo species=\"ACSA\" type=\"Sapling\"/>"
       << "<applyTo species=\"FAGR\" type=\"Sapling\"/>"
       << "<applyTo species=\"TSCA\" type=\"Sapling\"/>"
       << "<applyTo species=\"FRAM\" type=\"Sapling\"/>"
       << "<applyTo species=\"PIST\" type=\"Sapling\"/>"
       << "<applyTo species=\"PRSE\" type=\"Sapling\"/>"
       << "<applyTo species=\"QURU\" type=\"Sapling\"/>"
       << "<applyTo species=\"ACSA\" type=\"Adult\"/>"
       << "<applyTo species=\"BEAL\" type=\"Adult\"/>"
       << "<applyTo species=\"FAGR\" type=\"Adult\"/>"
       << "<applyTo species=\"TSCA\" type=\"Adult\"/>"
       << "<applyTo species=\"FRAM\" type=\"Adult\"/>"
       << "<applyTo species=\"PIST\" type=\"Adult\"/>"
       << "<applyTo species=\"PRSE\" type=\"Adult\"/>"
       << "<applyTo species=\"QURU\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>QuadratLight</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"ACRU\" type=\"Seedling\"/>"
       << "<applyTo species=\"ACSA\" type=\"Seedling\"/>"
       << "<applyTo species=\"BEAL\" type=\"Seedling\"/>"
       << "<applyTo species=\"FAGR\" type=\"Seedling\"/>"
       << "<applyTo species=\"TSCA\" type=\"Seedling\"/>"
       << "<applyTo species=\"FRAM\" type=\"Seedling\"/>"
       << "<applyTo species=\"PIST\" type=\"Seedling\"/>"
       << "<applyTo species=\"PRSE\" type=\"Seedling\"/>"
       << "<applyTo species=\"QURU\" type=\"Seedling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>AverageLight</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>4</listPosition>"
       << "<applyTo species=\"ACRU\" type=\"Adult\"/>"
       << "<applyTo species=\"BEAL\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RelUnlimGrowth</behaviorName>"
       << "<version>1.1</version>"
       << "<listPosition>5</listPosition>"
       << "<applyTo species=\"ACRU\" type=\"Seedling\"/>"
       << "<applyTo species=\"ACSA\" type=\"Seedling\"/>"
       << "<applyTo species=\"BEAL\" type=\"Seedling\"/>"
       << "<applyTo species=\"FAGR\" type=\"Seedling\"/>"
       << "<applyTo species=\"TSCA\" type=\"Seedling\"/>"
       << "<applyTo species=\"FRAM\" type=\"Seedling\"/>"
       << "<applyTo species=\"PIST\" type=\"Seedling\"/>"
       << "<applyTo species=\"PRSE\" type=\"Seedling\"/>"
       << "<applyTo species=\"QURU\" type=\"Seedling\"/>"
       << "<applyTo species=\"ACRU\" type=\"Sapling\"/>"
       << "<applyTo species=\"ACSA\" type=\"Sapling\"/>"
       << "<applyTo species=\"BEAL\" type=\"Sapling\"/>"
       << "<applyTo species=\"FAGR\" type=\"Sapling\"/>"
       << "<applyTo species=\"TSCA\" type=\"Sapling\"/>"
       << "<applyTo species=\"FRAM\" type=\"Sapling\"/>"
       << "<applyTo species=\"PIST\" type=\"Sapling\"/>"
       << "<applyTo species=\"PRSE\" type=\"Sapling\"/>"
       << "<applyTo species=\"QURU\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>ConstRadialGrowth</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>6</listPosition>"
       << "<applyTo species=\"ACRU\" type=\"Adult\"/>"
       << "<applyTo species=\"ACSA\" type=\"Adult\"/>"
       << "<applyTo species=\"BEAL\" type=\"Adult\"/>"
       << "<applyTo species=\"FAGR\" type=\"Adult\"/>"
       << "<applyTo species=\"TSCA\" type=\"Adult\"/>"
       << "<applyTo species=\"FRAM\" type=\"Adult\"/>"
       << "<applyTo species=\"PIST\" type=\"Adult\"/>"
       << "<applyTo species=\"PRSE\" type=\"Adult\"/>"
       << "<applyTo species=\"QURU\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<allometry>"
       << "<tr_whatAdultHeightDiam>"
       << "<tr_wahdVal species=\"ACRU\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"ACSA\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"BEAL\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"FAGR\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"TSCA\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"FRAM\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"PIST\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"PRSE\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"QURU\">0</tr_wahdVal>"
       << "</tr_whatAdultHeightDiam>"
       << "<tr_whatSaplingHeightDiam>"
       << "<tr_wsahdVal species=\"ACRU\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"ACSA\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"BEAL\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"FAGR\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"TSCA\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"FRAM\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"PIST\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"PRSE\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"QURU\">0</tr_wsahdVal>"
       << "</tr_whatSaplingHeightDiam>"
       << "<tr_whatSeedlingHeightDiam>"
       << "<tr_wsehdVal species=\"ACRU\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"ACSA\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"BEAL\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"FAGR\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"TSCA\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"FRAM\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"PIST\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"PRSE\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"QURU\">0</tr_wsehdVal>"
       << "</tr_whatSeedlingHeightDiam>"
       << "<tr_whatAdultCrownRadDiam>"
       << "<tr_wacrdVal species=\"ACRU\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"ACSA\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"BEAL\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"FAGR\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"TSCA\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"FRAM\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"PIST\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"PRSE\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"QURU\">0</tr_wacrdVal>"
       << "</tr_whatAdultCrownRadDiam>"
       << "<tr_whatSaplingCrownRadDiam>"
       << "<tr_wscrdVal species=\"ACRU\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"ACSA\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"BEAL\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"FAGR\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"TSCA\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"FRAM\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"PIST\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"PRSE\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"QURU\">0</tr_wscrdVal>"
       << "</tr_whatSaplingCrownRadDiam>"
       << "<tr_whatAdultCrownHeightHeight>"
       << "<tr_wachhVal species=\"ACRU\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"ACSA\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"BEAL\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"FAGR\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"TSCA\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"FRAM\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"PIST\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"PRSE\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"QURU\">0</tr_wachhVal>"
       << "</tr_whatAdultCrownHeightHeight>"
       << "<tr_whatSaplingCrownHeightHeight>"
       << "<tr_wschhVal species=\"ACRU\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"ACSA\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"BEAL\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"FAGR\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"TSCA\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"FRAM\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"PIST\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"PRSE\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"QURU\">0</tr_wschhVal>"
       << "</tr_whatSaplingCrownHeightHeight>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"ACRU\">30.0</tr_chVal>"
       << "<tr_chVal species=\"ACSA\">30.0</tr_chVal>"
       << "<tr_chVal species=\"BEAL\">30.0</tr_chVal>"
       << "<tr_chVal species=\"FAGR\">30.0</tr_chVal>"
       << "<tr_chVal species=\"TSCA\">30.0</tr_chVal>"
       << "<tr_chVal species=\"FRAM\">30.0</tr_chVal>"
       << "<tr_chVal species=\"PIST\">30.0</tr_chVal>"
       << "<tr_chVal species=\"PRSE\">30.0</tr_chVal>"
       << "<tr_chVal species=\"QURU\">30.0</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"ACRU\">0.108</tr_sacrVal>"
       << "<tr_sacrVal species=\"ACSA\">0.107</tr_sacrVal>"
       << "<tr_sacrVal species=\"BEAL\">0.109</tr_sacrVal>"
       << "<tr_sacrVal species=\"FAGR\">0.152</tr_sacrVal>"
       << "<tr_sacrVal species=\"TSCA\">0.1</tr_sacrVal>"
       << "<tr_sacrVal species=\"FRAM\">0.095</tr_sacrVal>"
       << "<tr_sacrVal species=\"PIST\">0.087</tr_sacrVal>"
       << "<tr_sacrVal species=\"PRSE\">0.116</tr_sacrVal>"
       << "<tr_sacrVal species=\"QURU\">0.119</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"ACRU\">1.0</tr_screVal>"
       << "<tr_screVal species=\"ACSA\">1.0</tr_screVal>"
       << "<tr_screVal species=\"BEAL\">1.0</tr_screVal>"
       << "<tr_screVal species=\"FAGR\">1.0</tr_screVal>"
       << "<tr_screVal species=\"TSCA\">1.0</tr_screVal>"
       << "<tr_screVal species=\"FRAM\">1.0</tr_screVal>"
       << "<tr_screVal species=\"PIST\">1.0</tr_screVal>"
       << "<tr_screVal species=\"PRSE\">1.0</tr_screVal>"
       << "<tr_screVal species=\"QURU\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"ACRU\">0.49</tr_sachVal>"
       << "<tr_sachVal species=\"ACSA\">0.58</tr_sachVal>"
       << "<tr_sachVal species=\"BEAL\">0.54</tr_sachVal>"
       << "<tr_sachVal species=\"FAGR\">0.664</tr_sachVal>"
       << "<tr_sachVal species=\"TSCA\">0.846</tr_sachVal>"
       << "<tr_sachVal species=\"FRAM\">0.319</tr_sachVal>"
       << "<tr_sachVal species=\"PIST\">0.413</tr_sachVal>"
       << "<tr_sachVal species=\"PRSE\">0.37</tr_sachVal>"
       << "<tr_sachVal species=\"QURU\">0.413</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"ACRU\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"ACSA\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"BEAL\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"FAGR\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"TSCA\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"FRAM\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"PIST\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"PRSE\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"QURU\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"ACRU\">0.75</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"ACSA\">0.75</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"BEAL\">0.75</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"FAGR\">0.75</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"TSCA\">0.75</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"FRAM\">0.75</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"PIST\">0.75</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"PRSE\">0.75</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"QURU\">0.75</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"ACRU\">0.0</tr_idtdVal>"
       << "<tr_idtdVal species=\"ACSA\">0.0</tr_idtdVal>"
       << "<tr_idtdVal species=\"BEAL\">0.0</tr_idtdVal>"
       << "<tr_idtdVal species=\"FAGR\">0.0</tr_idtdVal>"
       << "<tr_idtdVal species=\"TSCA\">0.0</tr_idtdVal>"
       << "<tr_idtdVal species=\"FRAM\">0.0</tr_idtdVal>"
       << "<tr_idtdVal species=\"PIST\">0.0</tr_idtdVal>"
       << "<tr_idtdVal species=\"PRSE\">0.0</tr_idtdVal>"
       << "<tr_idtdVal species=\"QURU\">0.0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"ACRU\">0.063</tr_soahVal>"
       << "<tr_soahVal species=\"ACSA\">0.062333334</tr_soahVal>"
       << "<tr_soahVal species=\"BEAL\">0.063</tr_soahVal>"
       << "<tr_soahVal species=\"FAGR\">0.03533333</tr_soahVal>"
       << "<tr_soahVal species=\"TSCA\">0.024333334</tr_soahVal>"
       << "<tr_soahVal species=\"FRAM\">0.055999998</tr_soahVal>"
       << "<tr_soahVal species=\"PIST\">0.033333335</tr_soahVal>"
       << "<tr_soahVal species=\"PRSE\">0.045</tr_soahVal>"
       << "<tr_soahVal species=\"QURU\">0.042</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"ACRU\">0.03</tr_sohdVal>"
       << "<tr_sohdVal species=\"ACSA\">0.03</tr_sohdVal>"
       << "<tr_sohdVal species=\"BEAL\">0.03</tr_sohdVal>"
       << "<tr_sohdVal species=\"FAGR\">0.03</tr_sohdVal>"
       << "<tr_sohdVal species=\"TSCA\">0.03</tr_sohdVal>"
       << "<tr_sohdVal species=\"FRAM\">0.03</tr_sohdVal>"
       << "<tr_sohdVal species=\"PIST\">0.03</tr_sohdVal>"
       << "<tr_sohdVal species=\"PRSE\">0.03</tr_sohdVal>"
       << "<tr_sohdVal species=\"QURU\">0.03</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "</allometry>"
       << "<GLILight2>"
       << "<li_heightOfFishEyePhoto>0</li_heightOfFishEyePhoto>"
       << "<li_beamFractGlobalRad>0.5</li_beamFractGlobalRad>"
       << "<li_clearSkyTransCoeff>0.65</li_clearSkyTransCoeff>"
       << "<li_julianDayGrowthStarts>120</li_julianDayGrowthStarts>"
       << "<li_julianDayGrowthEnds>270</li_julianDayGrowthEnds>"
       << "<li_minSunAngle>0.779</li_minSunAngle>"
       << "<li_numAltGrids>12</li_numAltGrids>"
       << "<li_numAziGrids>18</li_numAziGrids>"
       << "<li_lightExtinctionCoefficient>"
       << "<li_lecVal species=\"ACRU\">0.399</li_lecVal>"
       << "<li_lecVal species=\"ACSA\">0.399</li_lecVal>"
       << "<li_lecVal species=\"BEAL\">0.399</li_lecVal>"
       << "<li_lecVal species=\"FAGR\">0.064</li_lecVal>"
       << "<li_lecVal species=\"TSCA\">0.064</li_lecVal>"
       << "<li_lecVal species=\"FRAM\">0.399</li_lecVal>"
       << "<li_lecVal species=\"PIST\">0.399</li_lecVal>"
       << "<li_lecVal species=\"PRSE\">0.399</li_lecVal>"
       << "<li_lecVal species=\"QURU\">0.566</li_lecVal>"
       << "</li_lightExtinctionCoefficient>"
       << "<li_snagAgeClass1>0</li_snagAgeClass1>"
       << "<li_snagAgeClass2>0</li_snagAgeClass2>"
       << "</GLILight2>"
       << "<QuadratLight3>"
       << "<li_minSunAngle>0.779</li_minSunAngle>"
       << "<li_numAltGrids>12</li_numAltGrids>"
       << "<li_numAziGrids>18</li_numAziGrids>"
       << "<li_quadratLightHeight>0.675</li_quadratLightHeight>"
       << "<li_quadratAllGLIs>0</li_quadratAllGLIs>"
       << "</QuadratLight3>"
       << "<GLIMapCreator1>"
       << "<li_minSunAngle>0.779</li_minSunAngle>"
       << "<li_numAltGrids>12</li_numAltGrids>"
       << "<li_numAziGrids>18</li_numAziGrids>"
       << "<li_mapLightHeight>0.0</li_mapLightHeight>"
       << "</GLIMapCreator1>"
       << "<ConstRadialGrowth6>"
       << "<gr_adultConstRadialInc>"
       << "<gr_acriVal species=\"ACRU\">3</gr_acriVal>"
       << "<gr_acriVal species=\"ACSA\">3</gr_acriVal>"
       << "<gr_acriVal species=\"BEAL\">3</gr_acriVal>"
       << "<gr_acriVal species=\"FAGR\">3</gr_acriVal>"
       << "<gr_acriVal species=\"TSCA\">3</gr_acriVal>"
       << "<gr_acriVal species=\"FRAM\">3</gr_acriVal>"
       << "<gr_acriVal species=\"PIST\">3</gr_acriVal>"
       << "<gr_acriVal species=\"PRSE\">3</gr_acriVal>"
       << "<gr_acriVal species=\"QURU\">3</gr_acriVal>"
       << "</gr_adultConstRadialInc>"
       << "</ConstRadialGrowth6>"
       << "<RelUnlimGrowth5>"
       << "<gr_asympDiameterGrowth>"
       << "<gr_adgVal species=\"ACRU\">0.167</gr_adgVal>"
       << "<gr_adgVal species=\"ACSA\">0.125</gr_adgVal>"
       << "<gr_adgVal species=\"BEAL\">0.169</gr_adgVal>"
       << "<gr_adgVal species=\"FAGR\">0.152</gr_adgVal>"
       << "<gr_adgVal species=\"TSCA\">0.229</gr_adgVal>"
       << "<gr_adgVal species=\"FRAM\">0.226</gr_adgVal>"
       << "<gr_adgVal species=\"PIST\">0.23</gr_adgVal>"
       << "<gr_adgVal species=\"PRSE\">0.249</gr_adgVal>"
       << "<gr_adgVal species=\"QURU\">0.266</gr_adgVal>"
       << "</gr_asympDiameterGrowth>"
       << "<gr_slopeGrowthResponse>"
       << "<gr_sgrVal species=\"ACRU\">0.027</gr_sgrVal>"
       << "<gr_sgrVal species=\"ACSA\">0.159</gr_sgrVal>"
       << "<gr_sgrVal species=\"BEAL\">0.137</gr_sgrVal>"
       << "<gr_sgrVal species=\"FAGR\">0.075</gr_sgrVal>"
       << "<gr_sgrVal species=\"TSCA\">0.051</gr_sgrVal>"
       << "<gr_sgrVal species=\"FRAM\">0.025</gr_sgrVal>"
       << "<gr_sgrVal species=\"PIST\">0.019</gr_sgrVal>"
       << "<gr_sgrVal species=\"PRSE\">0.064</gr_sgrVal>"
       << "<gr_sgrVal species=\"QURU\">0.022</gr_sgrVal>"
       << "</gr_slopeGrowthResponse>"
       << "<gr_relGrowthDiamExp>"
       << "<gr_rgdeVal species=\"ACRU\">1.0</gr_rgdeVal>"
       << "<gr_rgdeVal species=\"ACSA\">1.0</gr_rgdeVal>"
       << "<gr_rgdeVal species=\"BEAL\">1.0</gr_rgdeVal>"
       << "<gr_rgdeVal species=\"FAGR\">1.0</gr_rgdeVal>"
       << "<gr_rgdeVal species=\"TSCA\">1.0</gr_rgdeVal>"
       << "<gr_rgdeVal species=\"FRAM\">1.0</gr_rgdeVal>"
       << "<gr_rgdeVal species=\"PIST\">1.0</gr_rgdeVal>"
       << "<gr_rgdeVal species=\"PRSE\">1.0</gr_rgdeVal>"
       << "<gr_rgdeVal species=\"QURU\">1.0</gr_rgdeVal>"
       << "</gr_relGrowthDiamExp>"
       << "</RelUnlimGrowth5>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteXMLErrorFile1()
/////////////////////////////////////////////////////////////////////////////
const char* clTestAverageLight::WriteXMLErrorFile1()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06060101\">"
       << "<plot>"
       << "<timesteps>3</timesteps>"
       << "<randomSeed>0</randomSeed>"
       << "<yearsPerTimestep>5.0</yearsPerTimestep>"
       << "<plot_lenX>100.0</plot_lenX>"
       << "<plot_lenY>100.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>41.92</plot_latitude>"
       << "<plot_title>Default parameter file-use for testing only</plot_title>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\"/>"
       << "<tr_species speciesName=\"Species_2\"/>"
       << "<tr_species speciesName=\"Species_3\"/>"
       << "</tr_speciesList>"
       << "<tr_seedDiam10Cm>0.2</tr_seedDiam10Cm>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_2\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_3\">10.0</tr_madVal>"
       << "</tr_minAdultDBH>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_3\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>"
       << "</trees>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>GLILight</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>AverageLight</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RelBAGrowth</behaviorName>"
       << "<version>1.1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RelUnlimGrowth</behaviorName>"
       << "<version>1.1</version>"
       << "<listPosition>4</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<allometry>"
       << "<tr_whatAdultHeightDiam>"
       << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_2\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_3\">0</tr_wahdVal>"
       << "</tr_whatAdultHeightDiam>"
       << "<tr_whatSaplingHeightDiam>"
       << "<tr_wsahdVal species=\"Species_1\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_2\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_3\">0</tr_wsahdVal>"
       << "</tr_whatSaplingHeightDiam>"
       << "<tr_whatSeedlingHeightDiam>"
       << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_2\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_3\">0</tr_wsehdVal>"
       << "</tr_whatSeedlingHeightDiam>"
       << "<tr_whatAdultCrownRadDiam>"
       << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_2\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_3\">0</tr_wacrdVal>"
       << "</tr_whatAdultCrownRadDiam>"
       << "<tr_whatSaplingCrownRadDiam>"
       << "<tr_wscrdVal species=\"Species_1\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_2\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_3\">0</tr_wscrdVal>"
       << "</tr_whatSaplingCrownRadDiam>"
       << "<tr_whatAdultCrownHeightHeight>"
       << "<tr_wachhVal species=\"Species_1\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_2\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_3\">0</tr_wachhVal>"
       << "</tr_whatAdultCrownHeightHeight>"
       << "<tr_whatSaplingCrownHeightHeight>"
       << "<tr_wschhVal species=\"Species_1\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_2\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_3\">0</tr_wschhVal>"
       << "</tr_whatSaplingCrownHeightHeight>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">30.0</tr_chVal>"
       << "<tr_chVal species=\"Species_2\">30.0</tr_chVal>"
       << "<tr_chVal species=\"Species_3\">30.0</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.108</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_2\">0.107</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_3\">0.109</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_3\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.49</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.58</tr_sachVal>"
       << "<tr_sachVal species=\"Species_3\">0.54</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_3\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.75</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">0.75</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_3\">0.75</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0.0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0.0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_3\">0.0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.063</tr_soahVal>"
       << "<tr_soahVal species=\"Species_2\">0.062333334</tr_soahVal>"
       << "<tr_soahVal species=\"Species_3\">0.063</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_2\">0.03</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_3\">0.03</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "</allometry>"
       << "<GLILight1>"
       << "<li_heightOfFishEyePhoto>0</li_heightOfFishEyePhoto>"
       << "<li_beamFractGlobalRad>0.5</li_beamFractGlobalRad>"
       << "<li_clearSkyTransCoeff>0.65</li_clearSkyTransCoeff>"
       << "<li_julianDayGrowthStarts>120</li_julianDayGrowthStarts>"
       << "<li_julianDayGrowthEnds>270</li_julianDayGrowthEnds>"
       << "<li_minSunAngle>0.779</li_minSunAngle>"
       << "<li_numAltGrids>12</li_numAltGrids>"
       << "<li_numAziGrids>18</li_numAziGrids>"
       << "<li_lightExtinctionCoefficient>"
       << "<li_lecVal species=\"Species_1\">0.399</li_lecVal>"
       << "<li_lecVal species=\"Species_2\">0.399</li_lecVal>"
       << "<li_lecVal species=\"Species_3\">0.399</li_lecVal>"
       << "</li_lightExtinctionCoefficient>"
       << "<li_snagAgeClass1>0</li_snagAgeClass1>"
       << "<li_snagAgeClass2>0</li_snagAgeClass2>"
       << "</GLILight1>"
       << "<RelBAGrowth3>"
       << "<gr_adultConstAreaInc>"
       << "<gr_acaiVal species=\"Species_1\">0.3</gr_acaiVal>"
       << "<gr_acaiVal species=\"Species_2\">0.3</gr_acaiVal>"
       << "<gr_acaiVal species=\"Species_3\">0.3</gr_acaiVal>"
       << "</gr_adultConstAreaInc>"
       << "</RelBAGrowth3>"
       << "<RelUnlimGrowth4>"
       << "<gr_asympDiameterGrowth>"
       << "<gr_adgVal species=\"Species_1\">0.167</gr_adgVal>"
       << "<gr_adgVal species=\"Species_2\">0.125</gr_adgVal>"
       << "<gr_adgVal species=\"Species_3\">0.169</gr_adgVal>"
       << "</gr_asympDiameterGrowth>"
       << "<gr_slopeGrowthResponse>"
       << "<gr_sgrVal species=\"Species_1\">0.027</gr_sgrVal>"
       << "<gr_sgrVal species=\"Species_2\">0.159</gr_sgrVal>"
       << "<gr_sgrVal species=\"Species_3\">0.137</gr_sgrVal>"
       << "</gr_slopeGrowthResponse>"
       << "<gr_relGrowthDiamExp>"
       << "<gr_rgdeVal species=\"Species_1\">1.0</gr_rgdeVal>"
       << "<gr_rgdeVal species=\"Species_2\">1.0</gr_rgdeVal>"
       << "<gr_rgdeVal species=\"Species_3\">1.0</gr_rgdeVal>"
       << "</gr_relGrowthDiamExp>"
       << "</RelUnlimGrowth4>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
//  WriteTreeFile()
/////////////////////////////////////////////////////////////////////////////
void clTestAverageLight::WriteTreeFile(std::fstream &oOut) {
  oOut << "<tr_treemap>"
       << "<tm_speciesList>"
       << "<tm_species speciesName=\"ACRU\"/>"
       << "<tm_species speciesName=\"ACSA\"/>"
       << "<tm_species speciesName=\"BEAL\"/>"
       << "<tm_species speciesName=\"FAGR\"/>"
       << "<tm_species speciesName=\"TSCA\"/>"
       << "<tm_species speciesName=\"FRAM\"/>"
       << "<tm_species speciesName=\"PIST\"/>"
       << "<tm_species speciesName=\"PRSE\"/>"
       << "<tm_species speciesName=\"QURU\"/>"
       << "</tm_speciesList>"
       << "<tm_treeSettings sp=\"ACRU\" tp=\"2\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">3</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"ACRU\" tp=\"3\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"ACSA\" tp=\"2\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">3</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"ACSA\" tp=\"3\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"BEAL\" tp=\"2\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">3</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"BEAL\" tp=\"3\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"FAGR\" tp=\"2\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">3</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"FAGR\" tp=\"3\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"TSCA\" tp=\"2\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">3</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"TSCA\" tp=\"3\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"FRAM\" tp=\"2\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">3</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"FRAM\" tp=\"3\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"PIST\" tp=\"2\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">3</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"PIST\" tp=\"3\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"PRSE\" tp=\"2\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">3</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"PRSE\" tp=\"3\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"QURU\" tp=\"2\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">3</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"QURU\" tp=\"3\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tree sp=\"5\" tp=\"3\">"
       << "<fl c=\"0\">6.94001</fl>"
       << "<fl c=\"1\">61.6497</fl>"
       << "<fl c=\"2\">35.7447</fl>"
       << "</tree>"
       << "<tree sp=\"5\" tp=\"3\">"
       << "<fl c=\"0\">2.79305</fl>"
       << "<fl c=\"1\">71.5869</fl>"
       << "<fl c=\"2\">41.7205</fl>"
       << "</tree>"
       << "<tree sp=\"7\" tp=\"3\">"
       << "<fl c=\"0\">0.706059</fl>"
       << "<fl c=\"1\">91.4912</fl>"
       << "<fl c=\"2\">37.706</fl>"
       << "</tree>"
       << "<tree sp=\"7\" tp=\"3\">"
       << "<fl c=\"0\">8.73021</fl>"
       << "<fl c=\"1\">11.9445</fl>"
       << "<fl c=\"2\">40.8461</fl>"
       << "</tree>"
       << "<tree sp=\"8\" tp=\"3\">"
       << "<fl c=\"0\">9.55841</fl>"
       << "<fl c=\"1\">53.6293</fl>"
       << "<fl c=\"2\">36.8159</fl>"
       << "</tree>"
       << "<tree sp=\"0\" tp=\"3\">"
       << "<fl c=\"0\">10.1847</fl>"
       << "<fl c=\"1\">79.0627</fl>"
       << "<fl c=\"2\">38.1902</fl>"
       << "</tree>"
       << "<tree sp=\"0\" tp=\"3\">"
       << "<fl c=\"0\">10.9825</fl>"
       << "<fl c=\"1\">78.7426</fl>"
       << "<fl c=\"2\">38.9011</fl>"
       << "</tree>"
       << "<tree sp=\"6\" tp=\"3\">"
       << "<fl c=\"0\">8.42503</fl>"
       << "<fl c=\"1\">85.9924</fl>"
       << "<fl c=\"2\">35.6076</fl>"
       << "</tree>"
       << "<tree sp=\"1\" tp=\"3\">"
       << "<fl c=\"0\">21.1924</fl>"
       << "<fl c=\"1\">23.661</fl>"
       << "<fl c=\"2\">38.7421</fl>"
       << "</tree>"
       << "<tree sp=\"6\" tp=\"3\">"
       << "<fl c=\"0\">19.7454</fl>"
       << "<fl c=\"1\">58.7072</fl>"
       << "<fl c=\"2\">35.6213</fl>"
       << "</tree>"
       << "<tree sp=\"4\" tp=\"3\">"
       << "<fl c=\"0\">23.2721</fl>"
       << "<fl c=\"1\">69.5294</fl>"
       << "<fl c=\"2\">35.7358</fl>"
       << "</tree>"
       << "<tree sp=\"5\" tp=\"3\">"
       << "<fl c=\"0\">18.2349</fl>"
       << "<fl c=\"1\">79.7752</fl>"
       << "<fl c=\"2\">35.5312</fl>"
       << "</tree>"
       << "<tree sp=\"1\" tp=\"3\">"
       << "<fl c=\"0\">29.8387</fl>"
       << "<fl c=\"1\">1.19124</fl>"
       << "<fl c=\"2\">38.8344</fl>"
       << "</tree>"
       << "<tree sp=\"3\" tp=\"3\">"
       << "<fl c=\"0\">24.6955</fl>"
       << "<fl c=\"1\">18.4796</fl>"
       << "<fl c=\"2\">39.4821</fl>"
       << "</tree>"
       << "<tree sp=\"1\" tp=\"3\">"
       << "<fl c=\"0\">30.6937</fl>"
       << "<fl c=\"1\">28.1659</fl>"
       << "<fl c=\"2\">32.7762</fl>"
       << "</tree>"
       << "<tree sp=\"8\" tp=\"3\">"
       << "<fl c=\"0\">25.2745</fl>"
       << "<fl c=\"1\">39.4905</fl>"
       << "<fl c=\"2\">37.7963</fl>"
       << "</tree>"
       << "<tree sp=\"4\" tp=\"3\">"
       << "<fl c=\"0\">28.9947</fl>"
       << "<fl c=\"1\">57.5213</fl>"
       << "<fl c=\"2\">41.4548</fl>"
       << "</tree>"
       << "<tree sp=\"0\" tp=\"3\">"
       << "<fl c=\"0\">28.6714</fl>"
       << "<fl c=\"1\">79.9464</fl>"
       << "<fl c=\"2\">36.2864</fl>"
       << "</tree>"
       << "<tree sp=\"7\" tp=\"3\">"
       << "<fl c=\"0\">34.3315</fl>"
       << "<fl c=\"1\">14.1544</fl>"
       << "<fl c=\"2\">35.6912</fl>"
       << "</tree>"
       << "<tree sp=\"0\" tp=\"3\">"
       << "<fl c=\"0\">36.8375</fl>"
       << "<fl c=\"1\">45.9022</fl>"
       << "<fl c=\"2\">36.1958</fl>"
       << "</tree>"
       << "<tree sp=\"2\" tp=\"3\">"
       << "<fl c=\"0\">39.3185</fl>"
       << "<fl c=\"1\">62.673</fl>"
       << "<fl c=\"2\">36.3104</fl>"
       << "</tree>"
       << "<tree sp=\"2\" tp=\"3\">"
       << "<fl c=\"0\">34.9471</fl>"
       << "<fl c=\"1\">77.9384</fl>"
       << "<fl c=\"2\">39.6614</fl>"
       << "</tree>"
       << "<tree sp=\"8\" tp=\"2\">"
       << "<fl c=\"0\">35.8307</fl>"
       << "<fl c=\"1\">99.4842</fl>"
       << "<fl c=\"3\">1.13303</fl>"
       << "</tree>"
       << "<tree sp=\"8\" tp=\"3\">"
       << "<fl c=\"0\">39.6656</fl>"
       << "<fl c=\"1\">98.5885</fl>"
       << "<fl c=\"2\">40.6102</fl>"
       << "</tree>"
       << "<tree sp=\"3\" tp=\"3\">"
       << "<fl c=\"0\">44.7669</fl>"
       << "<fl c=\"1\">23.2299</fl>"
       << "<fl c=\"2\">33.1079</fl>"
       << "</tree>"
       << "<tree sp=\"3\" tp=\"3\">"
       << "<fl c=\"0\">42.5601</fl>"
       << "<fl c=\"1\">25.7284</fl>"
       << "<fl c=\"2\">39.9132</fl>"
       << "</tree>"
       << "<tree sp=\"4\" tp=\"3\">"
       << "<fl c=\"0\">43.1891</fl>"
       << "<fl c=\"1\">35.6714</fl>"
       << "<fl c=\"2\">37.8012</fl>"
       << "</tree>"
       << "<tree sp=\"0\" tp=\"3\">"
       << "<fl c=\"0\">47.7189</fl>"
       << "<fl c=\"1\">38.9228</fl>"
       << "<fl c=\"2\">35.5278</fl>"
       << "</tree>"
       << "<tree sp=\"5\" tp=\"3\">"
       << "<fl c=\"0\">42.7538</fl>"
       << "<fl c=\"1\">59.2957</fl>"
       << "<fl c=\"2\">35.5183</fl>"
       << "</tree>"
       << "<tree sp=\"2\" tp=\"3\">"
       << "<fl c=\"0\">46.5669</fl>"
       << "<fl c=\"1\">73.7716</fl>"
       << "<fl c=\"2\">35.5199</fl>"
       << "</tree>"
       << "<tree sp=\"0\" tp=\"3\">"
       << "<fl c=\"0\">46.267</fl>"
       << "<fl c=\"1\">75.1451</fl>"
       << "<fl c=\"2\">37.2203</fl>"
       << "</tree>"
       << "<tree sp=\"4\" tp=\"3\">"
       << "<fl c=\"0\">44.7447</fl>"
       << "<fl c=\"1\">80.4319</fl>"
       << "<fl c=\"2\">35.5656</fl>"
       << "</tree>"
       << "<tree sp=\"7\" tp=\"3\">"
       << "<fl c=\"0\">42.2</fl>"
       << "<fl c=\"1\">84.309</fl>"
       << "<fl c=\"2\">41.4726</fl>"
       << "</tree>"
       << "<tree sp=\"2\" tp=\"3\">"
       << "<fl c=\"0\">44.2417</fl>"
       << "<fl c=\"1\">85.229</fl>"
       << "<fl c=\"2\">38.7471</fl>"
       << "</tree>"
       << "<tree sp=\"6\" tp=\"3\">"
       << "<fl c=\"0\">44.0492</fl>"
       << "<fl c=\"1\">89.616</fl>"
       << "<fl c=\"2\">35.5333</fl>"
       << "</tree>"
       << "<tree sp=\"8\" tp=\"3\">"
       << "<fl c=\"0\">44.9645</fl>"
       << "<fl c=\"1\">93.2166</fl>"
       << "<fl c=\"2\">35.5976</fl>"
       << "</tree>"
       << "<tree sp=\"7\" tp=\"3\">"
       << "<fl c=\"0\">54.9019</fl>"
       << "<fl c=\"1\">21.3681</fl>"
       << "<fl c=\"2\">37.9293</fl>"
       << "</tree>"
       << "<tree sp=\"1\" tp=\"3\">"
       << "<fl c=\"0\">54.2186</fl>"
       << "<fl c=\"1\">26.5928</fl>"
       << "<fl c=\"2\">37.3198</fl>"
       << "</tree>"
       << "<tree sp=\"8\" tp=\"3\">"
       << "<fl c=\"0\">55.6728</fl>"
       << "<fl c=\"1\">41.6254</fl>"
       << "<fl c=\"2\">41.8556</fl>"
       << "</tree>"
       << "<tree sp=\"0\" tp=\"3\">"
       << "<fl c=\"0\">50.7043</fl>"
       << "<fl c=\"1\">44.4005</fl>"
       << "<fl c=\"2\">38.8187</fl>"
       << "</tree>"
       << "<tree sp=\"6\" tp=\"3\">"
       << "<fl c=\"0\">55.9431</fl>"
       << "<fl c=\"1\">61.2759</fl>"
       << "<fl c=\"2\">41.2865</fl>"
       << "</tree>"
       << "<tree sp=\"6\" tp=\"3\">"
       << "<fl c=\"0\">51.1525</fl>"
       << "<fl c=\"1\">78.5749</fl>"
       << "<fl c=\"2\">36.7979</fl>"
       << "</tree>"
       << "<tree sp=\"3\" tp=\"3\">"
       << "<fl c=\"0\">51.2924</fl>"
       << "<fl c=\"1\">81.9323</fl>"
       << "<fl c=\"2\">37.9659</fl>"
       << "</tree>"
       << "<tree sp=\"5\" tp=\"3\">"
       << "<fl c=\"0\">55.7425</fl>"
       << "<fl c=\"1\">89.5188</fl>"
       << "<fl c=\"2\">39.199</fl>"
       << "</tree>"
       << "<tree sp=\"5\" tp=\"3\">"
       << "<fl c=\"0\">62.8047</fl>"
       << "<fl c=\"1\">17.0403</fl>"
       << "<fl c=\"2\">36.5724</fl>"
       << "</tree>"
       << "<tree sp=\"2\" tp=\"3\">"
       << "<fl c=\"0\">62.5284</fl>"
       << "<fl c=\"1\">16.9467</fl>"
       << "<fl c=\"2\">36.7782</fl>"
       << "</tree>"
       << "<tree sp=\"0\" tp=\"3\">"
       << "<fl c=\"0\">63.7137</fl>"
       << "<fl c=\"1\">20.9261</fl>"
       << "<fl c=\"2\">40.3972</fl>"
       << "</tree>"
       << "<tree sp=\"3\" tp=\"3\">"
       << "<fl c=\"0\">62.4231</fl>"
       << "<fl c=\"1\">30.7094</fl>"
       << "<fl c=\"2\">35.9739</fl>"
       << "</tree>"
       << "<tree sp=\"7\" tp=\"3\">"
       << "<fl c=\"0\">61.9509</fl>"
       << "<fl c=\"1\">33.0336</fl>"
       << "<fl c=\"2\">35.7851</fl>"
       << "</tree>"
       << "<tree sp=\"0\" tp=\"3\">"
       << "<fl c=\"0\">58.2752</fl>"
       << "<fl c=\"1\">32.8153</fl>"
       << "<fl c=\"2\">35.6105</fl>"
       << "</tree>"
       << "<tree sp=\"8\" tp=\"3\">"
       << "<fl c=\"0\">59.4163</fl>"
       << "<fl c=\"1\">49.0438</fl>"
       << "<fl c=\"2\">41.4912</fl>"
       << "</tree>"
       << "<tree sp=\"4\" tp=\"3\">"
       << "<fl c=\"0\">61.5472</fl>"
       << "<fl c=\"1\">60.235</fl>"
       << "<fl c=\"2\">36.2706</fl>"
       << "</tree>"
       << "<tree sp=\"5\" tp=\"3\">"
       << "<fl c=\"0\">62.1364</fl>"
       << "<fl c=\"1\">74.8853</fl>"
       << "<fl c=\"2\">38.7365</fl>"
       << "</tree>"
       << "<tree sp=\"7\" tp=\"2\">"
       << "<fl c=\"0\">61.6763</fl>"
       << "<fl c=\"1\">86.5007</fl>"
       << "<fl c=\"3\">1.22224</fl>"
       << "</tree>"
       << "<tree sp=\"6\" tp=\"3\">"
       << "<fl c=\"0\">61.4557</fl>"
       << "<fl c=\"1\">97.2432</fl>"
       << "<fl c=\"2\">37.6656</fl>"
       << "</tree>"
       << "<tree sp=\"7\" tp=\"3\">"
       << "<fl c=\"0\">59.5335</fl>"
       << "<fl c=\"1\">98.9239</fl>"
       << "<fl c=\"2\">37.3063</fl>"
       << "</tree>"
       << "<tree sp=\"3\" tp=\"3\">"
       << "<fl c=\"0\">67.3887</fl>"
       << "<fl c=\"1\">8.33352</fl>"
       << "<fl c=\"2\">42.1272</fl>"
       << "</tree>"
       << "<tree sp=\"2\" tp=\"3\">"
       << "<fl c=\"0\">69.7747</fl>"
       << "<fl c=\"1\">25.2441</fl>"
       << "<fl c=\"2\">38.0961</fl>"
       << "</tree>"
       << "<tree sp=\"6\" tp=\"3\">"
       << "<fl c=\"0\">66.5705</fl>"
       << "<fl c=\"1\">53.1052</fl>"
       << "<fl c=\"2\">42.4801</fl>"
       << "</tree>"
       << "<tree sp=\"2\" tp=\"3\">"
       << "<fl c=\"0\">68.7879</fl>"
       << "<fl c=\"1\">55.8026</fl>"
       << "<fl c=\"2\">37.3056</fl>"
       << "</tree>"
       << "<tree sp=\"7\" tp=\"3\">"
       << "<fl c=\"0\">65.668</fl>"
       << "<fl c=\"1\">65.4943</fl>"
       << "<fl c=\"2\">37.6502</fl>"
       << "</tree>"
       << "<tree sp=\"1\" tp=\"3\">"
       << "<fl c=\"0\">69.3609</fl>"
       << "<fl c=\"1\">99.4097</fl>"
       << "<fl c=\"2\">33.7639</fl>"
       << "</tree>"
       << "<tree sp=\"6\" tp=\"3\">"
       << "<fl c=\"0\">73.4231</fl>"
       << "<fl c=\"1\">4.14097</fl>"
       << "<fl c=\"2\">35.5271</fl>"
       << "</tree>"
       << "<tree sp=\"3\" tp=\"3\">"
       << "<fl c=\"0\">79.2244</fl>"
       << "<fl c=\"1\">48.9532</fl>"
       << "<fl c=\"2\">37.3432</fl>"
       << "</tree>"
       << "<tree sp=\"3\" tp=\"3\">"
       << "<fl c=\"0\">73.8198</fl>"
       << "<fl c=\"1\">54.1996</fl>"
       << "<fl c=\"2\">38.9536</fl>"
       << "</tree>"
       << "<tree sp=\"6\" tp=\"3\">"
       << "<fl c=\"0\">78.3373</fl>"
       << "<fl c=\"1\">80.1159</fl>"
       << "<fl c=\"2\">37.5921</fl>"
       << "</tree>"
       << "<tree sp=\"3\" tp=\"3\">"
       << "<fl c=\"0\">83.1831</fl>"
       << "<fl c=\"1\">1.67473</fl>"
       << "<fl c=\"2\">35.5834</fl>"
       << "</tree>"
       << "<tree sp=\"1\" tp=\"3\">"
       << "<fl c=\"0\">84.44</fl>"
       << "<fl c=\"1\">3.05137</fl>"
       << "<fl c=\"2\">41.3448</fl>"
       << "</tree>"
       << "<tree sp=\"1\" tp=\"3\">"
       << "<fl c=\"0\">86.7589</fl>"
       << "<fl c=\"1\">27.668</fl>"
       << "<fl c=\"2\">37.7336</fl>"
       << "</tree>"
       << "<tree sp=\"2\" tp=\"3\">"
       << "<fl c=\"0\">86.5927</fl>"
       << "<fl c=\"1\">31.3187</fl>"
       << "<fl c=\"2\">40.1813</fl>"
       << "</tree>"
       << "<tree sp=\"4\" tp=\"3\">"
       << "<fl c=\"0\">86.2437</fl>"
       << "<fl c=\"1\">53.9114</fl>"
       << "<fl c=\"2\">40.5544</fl>"
       << "</tree>"
       << "<tree sp=\"8\" tp=\"3\">"
       << "<fl c=\"0\">81.3769</fl>"
       << "<fl c=\"1\">48.2936</fl>"
       << "<fl c=\"2\">29.787</fl>"
       << "</tree>"
       << "<tree sp=\"4\" tp=\"3\">"
       << "<fl c=\"0\">84.4191</fl>"
       << "<fl c=\"1\">82.3401</fl>"
       << "<fl c=\"2\">39.2333</fl>"
       << "</tree>"
       << "<tree sp=\"7\" tp=\"3\">"
       << "<fl c=\"0\">83.1531</fl>"
       << "<fl c=\"1\">80.1739</fl>"
       << "<fl c=\"2\">35.9268</fl>"
       << "</tree>"
       << "<tree sp=\"4\" tp=\"3\">"
       << "<fl c=\"0\">89.2881</fl>"
       << "<fl c=\"1\">13.4158</fl>"
       << "<fl c=\"2\">35.5179</fl>"
       << "</tree>"
       << "<tree sp=\"8\" tp=\"2\">"
       << "<fl c=\"0\">95.3465</fl>"
       << "<fl c=\"1\">17.932</fl>"
       << "<fl c=\"3\">1.11565</fl>"
       << "</tree>"
       << "<tree sp=\"7\" tp=\"3\">"
       << "<fl c=\"0\">92.7765</fl>"
       << "<fl c=\"1\">48.2488</fl>"
       << "<fl c=\"2\">35.5337</fl>"
       << "</tree>"
       << "<tree sp=\"1\" tp=\"3\">"
       << "<fl c=\"0\">90.5021</fl>"
       << "<fl c=\"1\">79.8542</fl>"
       << "<fl c=\"2\">35.6764</fl>"
       << "</tree>"
       << "<tree sp=\"8\" tp=\"3\">"
       << "<fl c=\"0\">91.461</fl>"
       << "<fl c=\"1\">99.1527</fl>"
       << "<fl c=\"2\">38.5726</fl>"
       << "</tree>"
       << "<tree sp=\"2\" tp=\"3\">"
       << "<fl c=\"0\">96.2619</fl>"
       << "<fl c=\"1\">58.3628</fl>"
       << "<fl c=\"2\">36.8363</fl>"
       << "</tree>"
       << "<tree sp=\"2\" tp=\"3\">"
       << "<fl c=\"0\">97.7965</fl>"
       << "<fl c=\"1\">74.7219</fl>"
       << "<fl c=\"2\">38.5316</fl>"
       << "</tree>"
       << "</tr_treemap>";
}
