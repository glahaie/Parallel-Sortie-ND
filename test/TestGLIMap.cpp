//---------------------------------------------------------------------------
// TestGLIMap.cpp
//---------------------------------------------------------------------------
#include "TestGLIMap.h"
#include <cppunit/TestCaller.h>
#include <fstream>
#include <math.h>
#include "SimManager.h"
#include "Grid.h"
#include "GLIMap.h"
#include "TreePopulation.h"

/////////////////////////////////////////////////////////////////////////////
//  TestGLIMap()
/////////////////////////////////////////////////////////////////////////////
void clTestGLIMap::TestGLIMap() {

  clSimManager *p_oSimManager = new clSimManager(3, 3, "");

  TestGridSetup(p_oSimManager);
  TestParameterSetup(p_oSimManager);
  TestNormalProcessing(p_oSimManager);
  TestErrorProcessing(p_oSimManager);

  //Clean up
  std::cout << "Deleting p_oSimManager" << std::endl;
   delete p_oSimManager;
   p_oSimManager = NULL;
}

/////////////////////////////////////////////////////////////////////////////
//  TestNormalProcessing()
/////////////////////////////////////////////////////////////////////////////
void clTestGLIMap::TestNormalProcessing(clSimManager *p_oSimManager) {

  clTreePopulation *p_oPop;
  clGrid *p_oQuadratGLIGrid, *p_oGLIMapGrid;
  float fX, fY, fDiam, fExpectedGLI, fActualGLI;
  int iNumXCells, iNumYCells, iX, iY, iMapGLICode, iQuadratGLICode, i;

  //Run 1: WriteXMLFile2() does setup.
  p_oSimManager->ReadFile(WriteXMLFile2());

  //Place a seedling in every grid cell of the GLI quadrat grid to force
  //clQuadratLight to perform a GLI calculation for all grid cells.
  p_oPop = (clTreePopulation*) p_oSimManager->GetPopulationObject("treepopulation");
  CPPUNIT_ASSERT(NULL != p_oPop);
  p_oQuadratGLIGrid = p_oSimManager->GetGridObject("Quadrat GLI");
  CPPUNIT_ASSERT(p_oQuadratGLIGrid != NULL);
  iNumXCells = p_oQuadratGLIGrid->GetNumberXCells();
  iNumYCells = p_oQuadratGLIGrid->GetNumberYCells();
  for (iX = 0; iX < iNumXCells; iX++) {
    for (iY = 0; iY < iNumYCells; iY++) {
      fX = p_oQuadratGLIGrid->GetOriginXOfCell(iX);
      fY = p_oQuadratGLIGrid->GetOriginYOfCell(iY);
      p_oPop->CreateTree (fX, fY, 0, clTreePopulation::seedling, 0);
    }
  }

  //Add the list of known neighbors
  fX = 65; fY = 66; fDiam = 25;
  p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);
  fX = 50; fY = 50; fDiam = 11;
  p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);
  fX = 56.1; fY = 50; fDiam = 45;
  p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);
  fX = 56; fY = 56; fDiam = 61;
  p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);
  fX = 51; fY = 57; fDiam = 15;
  p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);
  fX = 59; fY = 57; fDiam = 45;
  p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);

  //Run a timestep - don't let the whole timestep run because
  //clQuadratLight::TimestepCleanup will erase the values in the quadrat
  //grid cell
  for (i = 0; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
    p_oSimManager->GetBehaviorObject(i)->Action();
  }

  //Test the GLIs of two "GLI Map" grid cells, (0, 0) and (5, 5). This verifies
  //that GLI is being calculated.
  p_oGLIMapGrid = p_oSimManager->GetGridObject("GLI Map");
  CPPUNIT_ASSERT(NULL != p_oGLIMapGrid);
  iMapGLICode = p_oGLIMapGrid->GetFloatDataCode("GLI");
  CPPUNIT_ASSERT(-1 != iMapGLICode);

  //0, 0
  fExpectedGLI = 100;
  p_oGLIMapGrid->GetValueOfCell(0, 0, iMapGLICode, &fActualGLI);
  CPPUNIT_ASSERT(fabs(fExpectedGLI - fActualGLI) < 0.1);

  //5, 5
  fExpectedGLI = 62.6762;
  p_oGLIMapGrid->GetValueOfCell(5, 5, iMapGLICode, &fActualGLI);
  CPPUNIT_ASSERT(fabs(fExpectedGLI - fActualGLI) < 0.01);

  //Compare the "GLI Map" and Quadrat GLI grids cell by cell to make sure
  //their values are the same.
  iQuadratGLICode = p_oQuadratGLIGrid->GetFloatDataCode("GLI");
  CPPUNIT_ASSERT(-1 != iQuadratGLICode);
  for (iX = 0; iX < iNumXCells; iX++) {
    for (iY = 0; iY < iNumYCells; iY++) {
      p_oGLIMapGrid->GetValueOfCell(iX, iY, iMapGLICode, &fActualGLI);
      p_oQuadratGLIGrid->GetValueOfCell(iX, iY, iQuadratGLICode, &fExpectedGLI);
      CPPUNIT_ASSERT(fabs(fExpectedGLI - fActualGLI) < 0.01);
    }
  }





  //Run 2: WriteXMLFile3() does setup.
  p_oSimManager->ReadFile(WriteXMLFile3());

  //Place a seedling in every grid cell of the GLI quadrat grid to force
  //clQuadratLight to perform a GLI calculation for all grid cells.
  p_oPop = (clTreePopulation*) p_oSimManager->GetPopulationObject("treepopulation");
  p_oQuadratGLIGrid = p_oSimManager->GetGridObject("Quadrat GLI");
  CPPUNIT_ASSERT(p_oQuadratGLIGrid != NULL);
  iNumXCells = p_oQuadratGLIGrid->GetNumberXCells();
  iNumYCells = p_oQuadratGLIGrid->GetNumberYCells();
  for (iX = 0; iX < iNumXCells; iX++) {
    for (iY = 0; iY < iNumYCells; iY++) {
      fX = p_oQuadratGLIGrid->GetOriginXOfCell(iX);
      fY = p_oQuadratGLIGrid->GetOriginYOfCell(iY);
      p_oPop->CreateTree (fX, fY, 0, clTreePopulation::seedling, 0);
    }
  }

  //Run a timestep - don't let the whole timestep run because
  //clQuadratLight::TimestepCleanup will erase the values in the quadrat
  //grid cell
  for (i = 0; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
    p_oSimManager->GetBehaviorObject(i)->Action();
  }

  //Compare the "GLI Map" and Quadrat GLI grids cell by cell to make sure
  //their values are the same.
  p_oGLIMapGrid = p_oSimManager->GetGridObject("GLI Map");
  CPPUNIT_ASSERT(NULL != p_oGLIMapGrid);
  iMapGLICode = p_oGLIMapGrid->GetFloatDataCode("GLI");
  CPPUNIT_ASSERT(-1 != iMapGLICode);
  iQuadratGLICode = p_oQuadratGLIGrid->GetFloatDataCode("GLI");
  CPPUNIT_ASSERT(-1 != iQuadratGLICode);
  for (iX = 0; iX < iNumXCells; iX++) {
    for (iY = 0; iY < iNumYCells; iY++) {
      p_oGLIMapGrid->GetValueOfCell(iX, iY, iMapGLICode, &fActualGLI);
      p_oQuadratGLIGrid->GetValueOfCell(iX, iY, iQuadratGLICode, &fExpectedGLI);
      if (fabs(fExpectedGLI - fActualGLI) >= 0.01) {
        fExpectedGLI = fExpectedGLI;
      }
      CPPUNIT_ASSERT(fabs(fExpectedGLI - fActualGLI) < 0.01);
    }
  }




  //Run 3:  WriteXMLFile1() does setup.
  p_oSimManager->ReadFile(WriteXMLFile1());
  p_oPop = (clTreePopulation*) p_oSimManager->GetPopulationObject("treepopulation");

  fX = 65; fY = 66; fDiam = 25;
  p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);
  fX = 50; fY = 50; fDiam = 11;
  p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);
  fX = 56.1; fY = 50; fDiam = 45;
  p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);
  fX = 56; fY = 56; fDiam = 61;
  p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);
  fX = 51; fY = 57; fDiam = 15;
  p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);
  fX = 59; fY = 57; fDiam = 45;
  p_oPop->CreateTree (fX, fY, 0, clTreePopulation::adult, fDiam);

  //Run a timestep
  p_oSimManager->RunSim(1);

  //Test the GLIs of two "GLI Map" grid cells, (0, 0) and (6, 6). This verifies
  //that GLI is being calculated correctly.
  p_oGLIMapGrid = p_oSimManager->GetGridObject("GLI Map");
  CPPUNIT_ASSERT(NULL != p_oGLIMapGrid);
  iMapGLICode = p_oGLIMapGrid->GetFloatDataCode("GLI");
  CPPUNIT_ASSERT(-1 != iMapGLICode);

  //0, 0
  fExpectedGLI = 100;
  p_oGLIMapGrid->GetValueOfCell(0, 0, iMapGLICode, &fActualGLI);
  CPPUNIT_ASSERT(fabs(fExpectedGLI - fActualGLI) < 0.1);

  //6, 6
  fExpectedGLI = 78.54049256;
  p_oGLIMapGrid->GetValueOfCell(6, 6, iMapGLICode, &fActualGLI);
  CPPUNIT_ASSERT(fabs(fExpectedGLI - fActualGLI) < 0.01);
}

/////////////////////////////////////////////////////////////////////////////
//  TestGridSetup()
/////////////////////////////////////////////////////////////////////////////
void clTestGLIMap::TestGridSetup(clSimManager *p_oSimManager) {
  clGrid *p_oMapGrid;
  float fGLI;
  int iNumXCells, iNumYCells, iX, iY, iGLICode;

  //Feed in the first parameter file
  p_oSimManager->ReadFile(WriteXMLFile1());

  //Get the grid map
  p_oMapGrid = p_oSimManager->GetGridObject("GLI Map");
  CPPUNIT_ASSERT(NULL != p_oMapGrid);

  //Make sure that the grid resolution is 8 X 8 m
  CPPUNIT_ASSERT(fabs(8 - p_oMapGrid->GetLengthXCells()) < 0.01);
  CPPUNIT_ASSERT(fabs(8 - p_oMapGrid->GetLengthYCells()) < 0.01);

  //Make sure that all the grid values are 0
  iNumXCells = p_oMapGrid->GetNumberXCells();
  iNumYCells = p_oMapGrid->GetNumberYCells();
  iGLICode = p_oMapGrid->GetFloatDataCode("GLI");
  CPPUNIT_ASSERT(-1 != iGLICode);

  for (iX = 0; iX < iNumXCells; iX++) {
    for (iY = 0; iY < iNumYCells; iY++) {
      p_oMapGrid->GetValueOfCell(iX, iY, iGLICode, &fGLI);
      CPPUNIT_ASSERT(fabs(0 - fGLI) < 0.001);
    }
  }

  //Try the second parameter file
  p_oSimManager->ReadFile(WriteXMLFile2());

  //Get the grid map
  p_oMapGrid = p_oSimManager->GetGridObject("GLI Map");
  CPPUNIT_ASSERT(NULL != p_oMapGrid);

  //Make sure that the grid resolution is 10 X 10 m
  CPPUNIT_ASSERT(fabs(10 - p_oMapGrid->GetLengthXCells()) < 0.01);
  CPPUNIT_ASSERT(fabs(10 - p_oMapGrid->GetLengthYCells()) < 0.01);

  //Make sure that all the grid values are 0
  iNumXCells = p_oMapGrid->GetNumberXCells();
  iNumYCells = p_oMapGrid->GetNumberYCells();
  iGLICode = p_oMapGrid->GetFloatDataCode("GLI");
  CPPUNIT_ASSERT(-1 != iGLICode);

  for (iX = 0; iX < iNumXCells; iX++) {
    for (iY = 0; iY < iNumYCells; iY++) {
      p_oMapGrid->GetValueOfCell(iX, iY, iGLICode, &fGLI);
      CPPUNIT_ASSERT(fabs(0 - fGLI) < 0.001);
    }
  }
}

/////////////////////////////////////////////////////////////////////////////
//  TestParameterSetup()
/////////////////////////////////////////////////////////////////////////////
void clTestGLIMap::TestParameterSetup(clSimManager *p_oSimManager) {
  clBehaviorBase *p_oTemp;
  clGLIMap *p_oGLIMap;
  int i, j;

  //Test the following condition: The GLI Map behavior is the only light
  //behavior in the list. WriteXMLFile1() creates the parameter file.  The
  //brightness array is checked to make sure it has non-zero values.
  p_oSimManager->ReadFile(WriteXMLFile1());
  p_oTemp = p_oSimManager->GetBehaviorObject("GLIMapCreator");
  CPPUNIT_ASSERT(NULL != p_oTemp);
  p_oGLIMap = dynamic_cast<clGLIMap *>(p_oTemp);

  CPPUNIT_ASSERT(fabs(p_oGLIMap->m_fLightHeight - 2) < 0.01);
  CPPUNIT_ASSERT(fabs(p_oGLIMap->m_fSinMinSunAng - 0.7068) < 0.01);
  CPPUNIT_ASSERT(fabs(p_oGLIMap->m_fAziChunkConverter - 0.05) < 0.01);
  CPPUNIT_ASSERT(fabs(p_oGLIMap->m_fRcpTanMinAng - 1.00079) < 0.01);
  CPPUNIT_ASSERT(fabs(p_oGLIMap->m_fMinSunAngle - 0.785) < 0.01);
  CPPUNIT_ASSERT(p_oGLIMap->m_iNumAziAng == 18);
  CPPUNIT_ASSERT(p_oGLIMap->m_iNumAltAng == 12);
  CPPUNIT_ASSERT(p_oGLIMap->m_iMinAngRow == 8);
  CPPUNIT_ASSERT(fabs(p_oGLIMap->m_fMaxSearchDistance - 47.509) < 0.01);
  for (i = p_oGLIMap->m_iMinAngRow; i < p_oGLIMap->m_iNumAltAng; i++) {
    for (j = 0; j < p_oGLIMap->m_iNumAziAng; j++) {
      CPPUNIT_ASSERT( p_oGLIMap->mp_fBrightness[i][j] > 0);
    }
  }

  //Test the following condition:  The GLI Map behavior and the Quadrat GLI
  //Light behavior are both in the list, and the Quadrat GLI Light behavior
  //comes first (meaning the GLI Map behavior can borrow brightness array
  //information from it).  WriteXMLFile2() creates the parameter file.  The
  //brightness array has non-zero values. The GLI Map has its correct settings
  //for sky grids.
  p_oSimManager->ReadFile(WriteXMLFile2());
  p_oTemp = p_oSimManager->GetBehaviorObject("GLIMapCreator");
  CPPUNIT_ASSERT(NULL != p_oTemp);
  p_oGLIMap = dynamic_cast<clGLIMap *>(p_oTemp);

  CPPUNIT_ASSERT(fabs(p_oGLIMap->m_fLightHeight - 2) < 0.01);
  CPPUNIT_ASSERT(fabs(p_oGLIMap->m_fSinMinSunAng - 0.7068) < 0.01);
  CPPUNIT_ASSERT(fabs(p_oGLIMap->m_fAziChunkConverter - 0.05) < 0.01);
  CPPUNIT_ASSERT(fabs(p_oGLIMap->m_fRcpTanMinAng - 1.00079) < 0.01);
  CPPUNIT_ASSERT(fabs(p_oGLIMap->m_fMinSunAngle - 0.785) < 0.01);
  CPPUNIT_ASSERT(p_oGLIMap->m_iNumAziAng == 18);
  CPPUNIT_ASSERT(p_oGLIMap->m_iNumAltAng == 12);
  CPPUNIT_ASSERT(p_oGLIMap->m_iMinAngRow == 8);
  CPPUNIT_ASSERT(fabs(p_oGLIMap->m_fMaxSearchDistance - 47.509) < 0.01);
  for (i = p_oGLIMap->m_iMinAngRow; i < p_oGLIMap->m_iNumAltAng; i++) {
    for (j = 0; j < p_oGLIMap->m_iNumAziAng; j++) {
      CPPUNIT_ASSERT( p_oGLIMap->mp_fBrightness[i][j] > 0);
    }
  }

  //Test the following condition: The GLI Map behavior and the Quadrat GLI
  //Light behavior are both in the list, and the Quadrat GLI Light behavior
  //comes second (meaning the GLI Map behavior cannot borrow brightness array
  //information from it). WriteXMLFile3() creates the parameter file.  The
  //brightness array has non-zero values. The GLI Map has its correct settings
  //for sky grids.
  p_oSimManager->ReadFile(WriteXMLFile3());
  p_oTemp = p_oSimManager->GetBehaviorObject("GLIMapCreator");
  CPPUNIT_ASSERT(NULL != p_oTemp);
  p_oGLIMap = dynamic_cast<clGLIMap *>(p_oTemp);

  CPPUNIT_ASSERT(fabs(p_oGLIMap->m_fLightHeight - 0) < 0.01);
  CPPUNIT_ASSERT(fabs(p_oGLIMap->m_fSinMinSunAng - 0.7068) < 0.01);
  CPPUNIT_ASSERT(fabs(p_oGLIMap->m_fAziChunkConverter - 0.05) < 0.01);
  CPPUNIT_ASSERT(fabs(p_oGLIMap->m_fRcpTanMinAng - 1.00079) < 0.01);
  CPPUNIT_ASSERT(fabs(p_oGLIMap->m_fMinSunAngle - 0.785) < 0.01);
  CPPUNIT_ASSERT(p_oGLIMap->m_iNumAziAng == 18);
  CPPUNIT_ASSERT(p_oGLIMap->m_iNumAltAng == 12);
  CPPUNIT_ASSERT(p_oGLIMap->m_iMinAngRow == 8);
  CPPUNIT_ASSERT(fabs(p_oGLIMap->m_fMaxSearchDistance - 49.5114) < 0.01);
  for (i = p_oGLIMap->m_iMinAngRow; i < p_oGLIMap->m_iNumAltAng; i++) {
    for (j = 0; j < p_oGLIMap->m_iNumAziAng; j++) {
      CPPUNIT_ASSERT( p_oGLIMap->mp_fBrightness[i][j] > 0);
    }
  }

  //Test the following condition:  The GLI Map behavior and the GLI Light
  //behavior are both in the list, and the GLI Light behavior comes first
  //(meaning the GLI Map behavior can borrow brightness array information from
  //it).  WriteXMLFile4() creates the parameter file.  The brightness array has
  //non-zero values. The GLI Map has its correct settings for sky grids.
  p_oSimManager->ReadFile(WriteXMLFile4());
  p_oTemp = p_oSimManager->GetBehaviorObject("GLIMapCreator");
  CPPUNIT_ASSERT(NULL != p_oTemp);
  p_oGLIMap = dynamic_cast<clGLIMap *>(p_oTemp);

  CPPUNIT_ASSERT(fabs(p_oGLIMap->m_fLightHeight - 1) < 0.01);
  CPPUNIT_ASSERT(fabs(p_oGLIMap->m_fSinMinSunAng - 0.7068) < 0.01);
  CPPUNIT_ASSERT(fabs(p_oGLIMap->m_fAziChunkConverter - 0.05) < 0.01);
  CPPUNIT_ASSERT(fabs(p_oGLIMap->m_fRcpTanMinAng - 1.00079) < 0.01);
  CPPUNIT_ASSERT(fabs(p_oGLIMap->m_fMinSunAngle - 0.785) < 0.01);
  CPPUNIT_ASSERT(p_oGLIMap->m_iNumAziAng == 18);
  CPPUNIT_ASSERT(p_oGLIMap->m_iNumAltAng == 12);
  CPPUNIT_ASSERT(p_oGLIMap->m_iMinAngRow == 8);
  CPPUNIT_ASSERT(fabs(p_oGLIMap->m_fMaxSearchDistance - 48.511) < 0.01);
  for (i = p_oGLIMap->m_iMinAngRow; i < p_oGLIMap->m_iNumAltAng; i++) {
    for (j = 0; j < p_oGLIMap->m_iNumAziAng; j++) {
      CPPUNIT_ASSERT( p_oGLIMap->mp_fBrightness[i][j] > 0);
    }
  }

  //Test the following conditions:  The GLI Map behavior and the GLI Light
  //behavior are both in the list, and the GLI Light behavior comes second
  //(meaning the GLI Map behavior cannot borrow brightness array information
  //from it).  WriteXMLFile5() creates the parameter file.  The brightness
  //array has non-zero values. The GLI Map has its correct settings for sky
  //grids.
  p_oSimManager->ReadFile(WriteXMLFile5());
  p_oTemp = p_oSimManager->GetBehaviorObject("GLIMapCreator");
  CPPUNIT_ASSERT(NULL != p_oTemp);
  p_oGLIMap = dynamic_cast<clGLIMap *>(p_oTemp);

  CPPUNIT_ASSERT(fabs(p_oGLIMap->m_fLightHeight - 1) < 0.01);
  CPPUNIT_ASSERT(fabs(p_oGLIMap->m_fSinMinSunAng - 0.7068) < 0.01);
  CPPUNIT_ASSERT(fabs(p_oGLIMap->m_fAziChunkConverter - 0.05) < 0.01);
  CPPUNIT_ASSERT(fabs(p_oGLIMap->m_fRcpTanMinAng - 1.00079) < 0.01);
  CPPUNIT_ASSERT(fabs(p_oGLIMap->m_fMinSunAngle - 0.785) < 0.01);
  CPPUNIT_ASSERT(p_oGLIMap->m_iNumAziAng == 18);
  CPPUNIT_ASSERT(p_oGLIMap->m_iNumAltAng == 12);
  CPPUNIT_ASSERT(p_oGLIMap->m_iMinAngRow == 8);
  CPPUNIT_ASSERT(fabs(p_oGLIMap->m_fMaxSearchDistance - 48.511) < 0.01);
  for (i = p_oGLIMap->m_iMinAngRow; i < p_oGLIMap->m_iNumAltAng; i++) {
    for (j = 0; j < p_oGLIMap->m_iNumAziAng; j++) {
      CPPUNIT_ASSERT( p_oGLIMap->mp_fBrightness[i][j] > 0);
    }
  }

  //Test the following conditions:  The GLI Map behavior and the GLI light
  //behavior are both in the list, the GLI Map behavior comes second, and the
  //light settings are different. WriteXMLFile6() creates the parameter file.
  //The GLI Map behavior is of the right size for its sky grids and contains
  //non-zero values.
  p_oSimManager->ReadFile(WriteXMLFile6());
  p_oTemp = p_oSimManager->GetBehaviorObject("GLIMapCreator");
  CPPUNIT_ASSERT(NULL != p_oTemp);
  p_oGLIMap = dynamic_cast<clGLIMap *>(p_oTemp);

  CPPUNIT_ASSERT(fabs(p_oGLIMap->m_fLightHeight - 1) < 0.01);
  CPPUNIT_ASSERT(fabs(p_oGLIMap->m_fSinMinSunAng - 0.7068) < 0.01);
  CPPUNIT_ASSERT(fabs(p_oGLIMap->m_fAziChunkConverter - 0.0555) < 0.01);
  CPPUNIT_ASSERT(fabs(p_oGLIMap->m_fRcpTanMinAng - 1.00079) < 0.01);
  CPPUNIT_ASSERT(fabs(p_oGLIMap->m_fMinSunAngle - 0.785) < 0.01);
  CPPUNIT_ASSERT(p_oGLIMap->m_iNumAziAng == 20);
  CPPUNIT_ASSERT(p_oGLIMap->m_iNumAltAng == 10);
  CPPUNIT_ASSERT(p_oGLIMap->m_iMinAngRow == 7);
  CPPUNIT_ASSERT(fabs(p_oGLIMap->m_fMaxSearchDistance - 48.511) < 0.01);
  for (i = p_oGLIMap->m_iMinAngRow; i < p_oGLIMap->m_iNumAltAng; i++) {
    for (j = 0; j < p_oGLIMap->m_iNumAziAng; j++) {
      CPPUNIT_ASSERT( p_oGLIMap->mp_fBrightness[i][j] > 0);
    }
  }
}

/////////////////////////////////////////////////////////////////////////////
//  TestErrorProcessing()
/////////////////////////////////////////////////////////////////////////////
void clTestGLIMap::TestErrorProcessing(clSimManager *p_oSimManager) {

  try
  {
    p_oSimManager->ReadFile(WriteXMLErrorFile1());
    CppUnit::Asserter::fail("TestGLIMap error processing didn't catch error for WriteXMLErrorFile1.");
  }
  catch (modelErr& err)
  {
    if (strstr(err.cFunction, "clGLIMap::ReadParameterFileData") == NULL)
    {
      CppUnit::Asserter::fail("TestGLIMap error processing caught wrong error for WriteXMLErrorFile1.");
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteXMLErrorFile2());
    CppUnit::Asserter::fail("TestGLIMap error processing didn't catch error for WriteXMLErrorFile2.");
  }
  catch (modelErr& err)
  {
    if (strstr(err.cFunction, "clGLIMap::ReadParameterFileData") == NULL)
    {
      CppUnit::Asserter::fail("TestGLIMap error processing caught wrong error for WriteXMLErrorFile2.");
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteXMLErrorFile3());
    CppUnit::Asserter::fail("TestGLIMap error processing didn't catch error for WriteXMLErrorFile3.");
  }
  catch (modelErr& err)
  {
    if (strstr(err.cFunction, "clGLIMap::ReadParameterFileData") == NULL)
    {
      CppUnit::Asserter::fail("TestGLIMap error processing caught wrong error for WriteXMLErrorFile3.");
    }
    ;
  }
}

////////////////////////////////////////////////////////////////////////////
//  WriteXMLFile1()
////////////////////////////////////////////////////////////////////////////
const char* clTestGLIMap::WriteXMLFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteCommonStuff(oOut);

  //Write file
  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>GLIMapCreator</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "</behaviorList>"
       << "<GeneralLight>"
       << "<li_beamFractGlobalRad>0.5</li_beamFractGlobalRad>"
       << "<li_clearSkyTransCoeff>0.65</li_clearSkyTransCoeff>"
       << "<li_julianDayGrowthStarts>105</li_julianDayGrowthStarts>"
       << "<li_julianDayGrowthEnds>258</li_julianDayGrowthEnds>"
       << "<li_lightExtinctionCoefficient>"
       << "<li_lecVal species=\"Species_1\">0.2</li_lecVal>"
       << "</li_lightExtinctionCoefficient>"
       << "</GeneralLight>"
       << "<GLIMapCreator1>"
       << "<li_minSunAngle>0.785</li_minSunAngle>"
       << "<li_numAltGrids>12</li_numAltGrids>"
       << "<li_numAziGrids>18</li_numAziGrids>"
       << "<li_mapLightHeight>2</li_mapLightHeight>"
       << "</GLIMapCreator1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
//  WriteXMLFile2()
////////////////////////////////////////////////////////////////////////////
const char* clTestGLIMap::WriteXMLFile2() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";
  int iX, iY, iNumX = 10, iNumY = 10;

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteCommonStuff(oOut);

  oOut << "<grid gridName=\"GLI Map\">"
       << "<ma_floatCodes>"
       << "<ma_floatCode label=\"GLI\">0</ma_floatCode>"
       << "</ma_floatCodes>"
       << "<ma_lengthXCells>10</ma_lengthXCells>"
       << "<ma_lengthYCells>10</ma_lengthYCells>";

  for (iX = 0; iX < iNumX; iX++)
  {
    for (iY = 0; iY < iNumY; iY++)
    {
      oOut << "<ma_v x=\"" << iX << "\" y=\"" << iY << "\">"
           << "<fl c=\"0\">" << (iX + iY) << "</fl>"
           << "</ma_v>";
    }
  }
  oOut << "</grid>"
       << "<grid gridName=\"Quadrat GLI\">"
       << "<ma_floatCodes>"
       << "<ma_floatCode label=\"GLI\">0</ma_floatCode>"
       << "</ma_floatCodes>"
       << "<ma_lengthXCells>10</ma_lengthXCells>"
       << "<ma_lengthYCells>10</ma_lengthYCells>"
       << "</grid>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>QuadratLight</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>GLIMapCreator</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "</behavior>"
       << "</behaviorList>"
       << "<GeneralLight>"
       << "<li_beamFractGlobalRad>0.5</li_beamFractGlobalRad>"
       << "<li_clearSkyTransCoeff>0.65</li_clearSkyTransCoeff>"
       << "<li_julianDayGrowthStarts>105</li_julianDayGrowthStarts>"
       << "<li_julianDayGrowthEnds>258</li_julianDayGrowthEnds>"
       << "<li_lightExtinctionCoefficient>"
       << "<li_lecVal species=\"Species_1\">0.2</li_lecVal>"
       << "</li_lightExtinctionCoefficient>"
       << "</GeneralLight>"
       << "<QuadratLight1>"
       << "<li_minSunAngle>0.785</li_minSunAngle>"
       << "<li_numAltGrids>12</li_numAltGrids>"
       << "<li_numAziGrids>18</li_numAziGrids>"
       << "<li_quadratLightHeight>2</li_quadratLightHeight>"
       << "<li_quadratAllGLIs>0</li_quadratAllGLIs>"
       << "</QuadratLight1>"
       << "<GLIMapCreator2>"
       << "<li_minSunAngle>0.785</li_minSunAngle>"
       << "<li_numAltGrids>12</li_numAltGrids>"
       << "<li_numAziGrids>18</li_numAziGrids>"
       << "<li_mapLightHeight>2</li_mapLightHeight>"
       << "</GLIMapCreator2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
//  WriteXMLFile3()
////////////////////////////////////////////////////////////////////////////
const char* clTestGLIMap::WriteXMLFile3() {
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
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
       << "</tr_minAdultDBH>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>";

  oOut << "<tr_sizeClasses>"
       << "<tr_sizeClass sizeKey=\"s15.0\" />"
       << "<tr_sizeClass sizeKey=\"s20.0\" />"
       << "<tr_sizeClass sizeKey=\"s30.0\" />"
       << "</tr_sizeClasses>"
       << "<tr_initialDensities>"
       << "<tr_idVals whatSpecies=\"Species_1\">"
       << "<tr_initialDensity sizeClass=\"s20.0\">50.0</tr_initialDensity>"
       << "</tr_idVals>"
       << "</tr_initialDensities>"
       << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
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
       << "</tr_whatAdultHeightDiam>"
       << "</allometry>";

  oOut << "<grid gridName=\"Quadrat GLI\">"
       << "<ma_floatCodes>"
       << "<ma_floatCode label=\"GLI\">0</ma_floatCode>"
       << "</ma_floatCodes>"
       << "<ma_lengthXCells>8</ma_lengthXCells>"
       << "<ma_lengthYCells>8</ma_lengthYCells>"
       << "</grid>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>GLIMapCreator</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>QuadratLight</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<GeneralLight>"
       << "<li_beamFractGlobalRad>0.5</li_beamFractGlobalRad>"
       << "<li_clearSkyTransCoeff>0.65</li_clearSkyTransCoeff>"
       << "<li_julianDayGrowthStarts>105</li_julianDayGrowthStarts>"
       << "<li_julianDayGrowthEnds>258</li_julianDayGrowthEnds>"
       << "<li_lightExtinctionCoefficient>"
       << "<li_lecVal species=\"Species_1\">0.2</li_lecVal>"
       << "</li_lightExtinctionCoefficient>"
       << "</GeneralLight>"
       << "<QuadratLight2>"
       << "<li_minSunAngle>0.785</li_minSunAngle>"
       << "<li_numAltGrids>12</li_numAltGrids>"
       << "<li_numAziGrids>18</li_numAziGrids>"
       << "<li_quadratLightHeight>0</li_quadratLightHeight>"
       << "<li_quadratAllGLIs>0</li_quadratAllGLIs>"
       << "</QuadratLight2>"
       << "<GLIMapCreator1>"
       << "<li_minSunAngle>0.785</li_minSunAngle>"
       << "<li_numAltGrids>12</li_numAltGrids>"
       << "<li_numAziGrids>18</li_numAziGrids>"
       << "<li_mapLightHeight>0</li_mapLightHeight>"
       << "</GLIMapCreator1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
//  WriteXMLFile4()
////////////////////////////////////////////////////////////////////////////
const char* clTestGLIMap::WriteXMLFile4() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>GLILight</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>GLIMapCreator</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "</behavior>"
       << "</behaviorList>"
       << "<GeneralLight>"
       << "<li_beamFractGlobalRad>0.5</li_beamFractGlobalRad>"
       << "<li_clearSkyTransCoeff>0.65</li_clearSkyTransCoeff>"
       << "<li_julianDayGrowthStarts>105</li_julianDayGrowthStarts>"
       << "<li_julianDayGrowthEnds>258</li_julianDayGrowthEnds>"
       << "<li_lightExtinctionCoefficient>"
       << "<li_lecVal species=\"Species_1\">0.2</li_lecVal>"
       << "</li_lightExtinctionCoefficient>"
       << "</GeneralLight>"
       << "<GLILight1>"
       << "<li_minSunAngle>0.785</li_minSunAngle>"
       << "<li_numAltGrids>12</li_numAltGrids>"
       << "<li_numAziGrids>18</li_numAziGrids>"
       << "</GLILight1>"
       << "<GLIMapCreator2>"
       << "<li_minSunAngle>0.785</li_minSunAngle>"
       << "<li_numAltGrids>12</li_numAltGrids>"
       << "<li_numAziGrids>18</li_numAziGrids>"
       << "<li_mapLightHeight>1</li_mapLightHeight>"
       << "</GLIMapCreator2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
//  WriteXMLFile5()
////////////////////////////////////////////////////////////////////////////
const char* clTestGLIMap::WriteXMLFile5() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>GLILight</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>GLIMapCreator</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "</behavior>"
       << "</behaviorList>"
       << "<GeneralLight>"
       << "<li_beamFractGlobalRad>0.5</li_beamFractGlobalRad>"
       << "<li_clearSkyTransCoeff>0.65</li_clearSkyTransCoeff>"
       << "<li_julianDayGrowthStarts>105</li_julianDayGrowthStarts>"
       << "<li_julianDayGrowthEnds>258</li_julianDayGrowthEnds>"
       << "<li_lightExtinctionCoefficient>"
       << "<li_lecVal species=\"Species_1\">0.2</li_lecVal>"
       << "</li_lightExtinctionCoefficient>"
       << "</GeneralLight>"
       << "<GLILight1>"
       << "<li_minSunAngle>0.785</li_minSunAngle>"
       << "<li_numAltGrids>12</li_numAltGrids>"
       << "<li_numAziGrids>18</li_numAziGrids>"
       << "</GLILight1>"
       << "<GLIMapCreator2>"
       << "<li_minSunAngle>0.785</li_minSunAngle>"
       << "<li_numAltGrids>12</li_numAltGrids>"
       << "<li_numAziGrids>18</li_numAziGrids>"
       << "<li_mapLightHeight>1</li_mapLightHeight>"
       << "</GLIMapCreator2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
//  WriteXMLFile6()
////////////////////////////////////////////////////////////////////////////
const char* clTestGLIMap::WriteXMLFile6() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>GLILight</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>GLIMapCreator</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "</behavior>"
       << "</behaviorList>"
       << "<GeneralLight>"
       << "<li_beamFractGlobalRad>0.5</li_beamFractGlobalRad>"
       << "<li_clearSkyTransCoeff>0.65</li_clearSkyTransCoeff>"
       << "<li_julianDayGrowthStarts>105</li_julianDayGrowthStarts>"
       << "<li_julianDayGrowthEnds>258</li_julianDayGrowthEnds>"
       << "<li_lightExtinctionCoefficient>"
       << "<li_lecVal species=\"Species_1\">0.2</li_lecVal>"
       << "</li_lightExtinctionCoefficient>"
       << "</GeneralLight>"
       << "<GLILight1>"
       << "<li_minSunAngle>0.785</li_minSunAngle>"
       << "<li_numAltGrids>12</li_numAltGrids>"
       << "<li_numAziGrids>18</li_numAziGrids>"
       << "</GLILight1>"
       << "<GLIMapCreator2>"
       << "<li_minSunAngle>0.785</li_minSunAngle>"
       << "<li_numAltGrids>10</li_numAltGrids>"
       << "<li_numAziGrids>20</li_numAziGrids>"
       << "<li_mapLightHeight>1</li_mapLightHeight>"
       << "</GLIMapCreator2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
//  WriteXMLErrorFile1()
////////////////////////////////////////////////////////////////////////////
const char* clTestGLIMap::WriteXMLErrorFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteCommonStuff(oOut);

  //Write file
  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>GLIMapCreator</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "</behaviorList>"
       << "<GeneralLight>"
       << "<li_beamFractGlobalRad>0.5</li_beamFractGlobalRad>"
       << "<li_clearSkyTransCoeff>0.65</li_clearSkyTransCoeff>"
       << "<li_julianDayGrowthStarts>105</li_julianDayGrowthStarts>"
       << "<li_julianDayGrowthEnds>258</li_julianDayGrowthEnds>"
       << "<li_lightExtinctionCoefficient>"
       << "<li_lecVal species=\"Species_1\">0.2</li_lecVal>"
       << "</li_lightExtinctionCoefficient>"
       << "</GeneralLight>"
       << "<GLIMapCreator1>"
       << "<li_minSunAngle>0.785</li_minSunAngle>"
       << "<li_numAltGrids>12</li_numAltGrids>"
       << "<li_numAziGrids>-18</li_numAziGrids>"
       << "<li_mapLightHeight>1</li_mapLightHeight>"
       << "</GLIMapCreator1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
//  WriteXMLErrorFile2()
////////////////////////////////////////////////////////////////////////////
const char* clTestGLIMap::WriteXMLErrorFile2() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteCommonStuff(oOut);

  //Write file
  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>GLIMapCreator</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "</behaviorList>"
       << "<GeneralLight>"
       << "<li_beamFractGlobalRad>0.5</li_beamFractGlobalRad>"
       << "<li_clearSkyTransCoeff>0.65</li_clearSkyTransCoeff>"
       << "<li_julianDayGrowthStarts>105</li_julianDayGrowthStarts>"
       << "<li_julianDayGrowthEnds>258</li_julianDayGrowthEnds>"
       << "<li_lightExtinctionCoefficient>"
       << "<li_lecVal species=\"Species_1\">0.2</li_lecVal>"
       << "</li_lightExtinctionCoefficient>"
       << "</GeneralLight>"
       << "<GLIMapCreator1>"
       << "<li_minSunAngle>0.785</li_minSunAngle>"
       << "<li_numAltGrids>0</li_numAltGrids>"
       << "<li_numAziGrids>18</li_numAziGrids>"
       << "<li_mapLightHeight>1</li_mapLightHeight>"
       << "</GLIMapCreator1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
//  WriteXMLErrorFile3()
////////////////////////////////////////////////////////////////////////////
const char* clTestGLIMap::WriteXMLErrorFile3() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteCommonStuff(oOut);

  //Write file
  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>GLIMapCreator</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "</behaviorList>"
       << "<GeneralLight>"
       << "<li_beamFractGlobalRad>0.5</li_beamFractGlobalRad>"
       << "<li_clearSkyTransCoeff>0.65</li_clearSkyTransCoeff>"
       << "<li_julianDayGrowthStarts>105</li_julianDayGrowthStarts>"
       << "<li_julianDayGrowthEnds>258</li_julianDayGrowthEnds>"
       << "<li_lightExtinctionCoefficient>"
       << "<li_lecVal species=\"Species_1\">0.2</li_lecVal>"
       << "</li_lightExtinctionCoefficient>"
       << "</GeneralLight>"
       << "<GLIMapCreator1>"
       << "<li_minSunAngle>0.785</li_minSunAngle>"
       << "<li_numAltGrids>12</li_numAltGrids>"
       << "<li_numAziGrids>18</li_numAziGrids>"
       << "<li_mapLightHeight>-1</li_mapLightHeight>"
       << "</GLIMapCreator1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
//  WriteCommonStuff()
/////////////////////////////////////////////////////////////////////////////
void clTestGLIMap::WriteCommonStuff( std::fstream &oOut )
{
  using namespace std;
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>1</timesteps>"
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
       << "</allometry>";
}

