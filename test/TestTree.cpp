//---------------------------------------------------------------------------
// TestTree.cpp
//---------------------------------------------------------------------------
#include "TestTree.h"
#include "TreePopulation.h"
#include "SimManager.h"
#include <fstream>
#include <math.h>

/////////////////////////////////////////////////////////////////////////////
// TestTree()
/////////////////////////////////////////////////////////////////////////////
void clTestTree::TestTree()
{

  clSimManager *p_oSimManager = new clSimManager(2, 4, "");

  TestAllometryUpdating(p_oSimManager);
  TestClone(p_oSimManager);

  delete p_oSimManager;
}


/////////////////////////////////////////////////////////////////////////////
// TestAllometryUpdating()
/////////////////////////////////////////////////////////////////////////////
void clTestTree::TestAllometryUpdating(clSimManager *p_oSimManager)
{
  clTreePopulation * p_oPop;
  clTree *p_oTree;
  float fDiam, fDBH, fHeight, fTemp;
  int iSp, iTp;

  //Set up our run and get the tree popluation pointer
  p_oSimManager->ReadFile( WriteXMLFile1() );
  p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

  //*************************
  //Create a seedling
  //*************************
  fDiam = 0.1;
  p_oTree = p_oPop->CreateTree(1, 1, 0, clTreePopulation::seedling, fDiam);
  iSp = p_oTree->GetSpecies();
  iTp = p_oTree->GetType();

  //Change the diameter at 10 cm and allow the allometry to update
  fDiam = 0.2;
  fHeight = 0.304380631;
  p_oTree->SetValue(p_oPop->GetDiam10Code(iSp, iTp), fDiam, true, true);
  p_oTree->GetValue(p_oPop->GetHeightCode(iSp, iTp), &fTemp);
  CPPUNIT_ASSERT(fabs(fHeight - fTemp) < 0.001);

  //Change the height and allow the allometry to update
  fHeight = 0.7;
  fDiam = 0.59106809;
  p_oTree->SetValue(p_oPop->GetHeightCode(iSp, iTp), fHeight);
  p_oTree->GetValue(p_oPop->GetDiam10Code(iSp, iTp), &fTemp);
  CPPUNIT_ASSERT(fabs(fDiam - fTemp) < 0.001);

  //Change the diameter at 10 cm and do not allow the allometry to update
  fDiam = 1.0;
  fHeight = 0.7;
  p_oTree->SetValue(p_oPop->GetDiam10Code(iSp, iTp), fDiam, true, false);
  p_oTree->GetValue(p_oPop->GetHeightCode(iSp, iTp), &fTemp);
  CPPUNIT_ASSERT(fabs(fHeight - fTemp) < 0.001);

  //Change the height and do not allow the allometry to update
  fHeight = 1.2;
  fDiam = 1.0;
  p_oTree->SetValue(p_oPop->GetHeightCode(iSp, iTp), fHeight, true, false);
  p_oTree->GetValue(p_oPop->GetDiam10Code(iSp, iTp), &fTemp);
  CPPUNIT_ASSERT(fabs(fDiam - fTemp) < 0.001);

  //*************************
  //Create a sapling
  //*************************
  fDiam = 5.0;
  p_oTree = p_oPop->CreateTree(1, 1, 0, clTreePopulation::sapling, fDiam);
  iSp = p_oTree->GetSpecies();
  iTp = p_oTree->GetType();

  //Change the diameter at 10 cm and allow the allometry to update
  fDiam = 7.8;
  fHeight = 7.845800505;
  fDBH = 6.24624;
  p_oTree->SetValue(p_oPop->GetDiam10Code(iSp, iTp), fDiam, true, true);
  p_oTree->GetValue(p_oPop->GetHeightCode(iSp, iTp), &fTemp);
  CPPUNIT_ASSERT(fabs(fHeight - fTemp) < 0.001);
  p_oTree->GetValue(p_oPop->GetDbhCode(iSp, iTp), &fTemp);
  CPPUNIT_ASSERT(fabs(fDBH - fTemp) < 0.001);

  //Change the DBH and allow the allometry to update
  fDBH = 5.0;
  fDiam = 6.243756244;
  fHeight = 6.644791358;

  p_oTree->SetValue(p_oPop->GetDbhCode(iSp, iTp), fDBH, true, true);
  p_oTree->GetValue(p_oPop->GetHeightCode(iSp, iTp), &fTemp);
  CPPUNIT_ASSERT(fabs(fHeight - fTemp) < 0.001);
  p_oTree->GetValue(p_oPop->GetDiam10Code(iSp, iTp), &fTemp);
  CPPUNIT_ASSERT(fabs(fDiam - fTemp) < 0.001);

  //Change the height and allow the allometry to update
  fHeight = 8.0;
  fDBH = 6.40966389;
  fDiam = 8.004075787;

  p_oTree->SetValue(p_oPop->GetHeightCode(iSp, iTp), fHeight);
  p_oTree->GetValue(p_oPop->GetDbhCode(iSp, iTp), &fTemp);
  CPPUNIT_ASSERT(fabs(fDBH - fTemp) < 0.001);
  p_oTree->GetValue(p_oPop->GetDiam10Code(iSp, iTp), &fTemp);
  CPPUNIT_ASSERT(fabs(fDiam - fTemp) < 0.001);

  //Change the diameter at 10 cm and do not allow the allometry to update
  fDiam = 3.0;
  fHeight = 8.0;
  fDBH = 2.4024;
  p_oTree->SetValue(p_oPop->GetDiam10Code(iSp, iTp), fDiam, true, false);
  p_oTree->GetValue(p_oPop->GetHeightCode(iSp, iTp), &fTemp);
  CPPUNIT_ASSERT(fabs(fHeight - fTemp) < 0.001);
  p_oTree->GetValue(p_oPop->GetDbhCode(iSp, iTp), &fTemp);
  CPPUNIT_ASSERT(fabs(fDBH - fTemp) < 0.001);

  //Change the DBH and do not allow the allometry to update
  fDBH = 5.0;
  fDiam = 6.243756244;
  fHeight = 8.0;
  p_oTree->SetValue(p_oPop->GetDbhCode(iSp, iTp), fDBH, true, false);
  p_oTree->GetValue(p_oPop->GetHeightCode(iSp, iTp), &fTemp);
  CPPUNIT_ASSERT(fabs(fHeight - fTemp) < 0.001);
  p_oTree->GetValue(p_oPop->GetDiam10Code(iSp, iTp), &fTemp);
  CPPUNIT_ASSERT(fabs(fDiam - fTemp) < 0.001);

  //Change the height and do not allow the allometry to update
  fHeight = 9.0;
  fDBH = 5.0;
  fDiam = 6.243756244;
  p_oTree->SetValue(p_oPop->GetHeightCode(iSp, iTp), fHeight, true, false);
  p_oTree->GetValue(p_oPop->GetDbhCode(iSp, iTp), &fTemp);
  CPPUNIT_ASSERT(fabs(fDBH - fTemp) < 0.001);
  p_oTree->GetValue(p_oPop->GetDiam10Code(iSp, iTp), &fTemp);
  CPPUNIT_ASSERT(fabs(fDiam - fTemp) < 0.001);

  //*************************
  //Create an adult
  //*************************
  fDiam = 15.0;
  p_oTree = p_oPop->CreateTree(1, 1, 0, clTreePopulation::adult, fDiam);
  iSp = p_oTree->GetSpecies();
  iTp = p_oTree->GetType();

  //Change the DBH and allow the allometry to update
  fDBH = 17.0;
  fHeight = 16.54414575;

  p_oTree->SetValue(p_oPop->GetDbhCode(iSp, iTp), fDBH);
  p_oTree->GetValue(p_oPop->GetHeightCode(iSp, iTp), &fTemp);
  CPPUNIT_ASSERT(fabs(fHeight - fTemp) < 0.001);

  //Change the height and allow the allometry to update
  fHeight = 18.0;
  fDBH = 19.19328108;

  p_oTree->SetValue(p_oPop->GetHeightCode(iSp, iTp), fHeight);
  p_oTree->GetValue(p_oPop->GetDbhCode(iSp, iTp), &fTemp);
  CPPUNIT_ASSERT(fabs(fDBH - fTemp) < 0.001);

  //Change the DBH and do not allow the allometry to update
  fDBH = 27.0;
  fHeight = 18.0;

  p_oTree->SetValue(p_oPop->GetDbhCode(iSp, iTp), fDBH, true, false);
  p_oTree->GetValue(p_oPop->GetHeightCode(iSp, iTp), &fTemp);
  CPPUNIT_ASSERT(fabs(fHeight - fTemp) < 0.001);

  //Change the height and do not allow the allometry to update
  fDBH = 37.0;
  fHeight = 18.0;

  p_oTree->SetValue(p_oPop->GetDbhCode(iSp, iTp), fDBH, true, false);
  p_oTree->GetValue(p_oPop->GetHeightCode(iSp, iTp), &fTemp);
  CPPUNIT_ASSERT(fabs(fHeight - fTemp) < 0.001);

  //*************************
  //Create a snag
  //*************************

  fDiam = 15.0;
  p_oTree = p_oPop->CreateTree(1, 1, 0, clTreePopulation::snag, fDiam);
  iSp = p_oTree->GetSpecies();
  iTp = p_oTree->GetType();

  //Change the DBH and allow the allometry to update
  fDBH = 17.0;
  fHeight = 16.54414575;

  p_oTree->SetValue(p_oPop->GetDbhCode(iSp, iTp), fDBH, true, true);
  p_oTree->GetValue(p_oPop->GetHeightCode(iSp, iTp), &fTemp);
  CPPUNIT_ASSERT(fabs(fHeight - fTemp) < 0.001);

  //Change the height and allow the allometry to update
  fHeight = 18.0;
  fDBH = 19.19328108;

  p_oTree->SetValue(p_oPop->GetHeightCode(iSp, iTp), fHeight, true, true);
  p_oTree->GetValue(p_oPop->GetDbhCode(iSp, iTp), &fTemp);
  CPPUNIT_ASSERT(fabs(fDBH - fTemp) < 0.001);

  //Change the DBH and do not allow the allometry to update
  fDBH = 27.0;
  fHeight = 18.0;

  p_oTree->SetValue(p_oPop->GetDbhCode(iSp, iTp), fDBH, true, false);
  p_oTree->GetValue(p_oPop->GetHeightCode(iSp, iTp), &fTemp);
  CPPUNIT_ASSERT(fabs(fHeight - fTemp) < 0.001);

  //Change the height and do not allow the allometry to update
  fDBH = 37.0;
  fHeight = 18.0;

  p_oTree->SetValue(p_oPop->GetDbhCode(iSp, iTp), fDBH, true, false);
  p_oTree->GetValue(p_oPop->GetHeightCode(iSp, iTp), &fTemp);
  CPPUNIT_ASSERT(fabs(fHeight - fTemp) < 0.001);

  //*************************
  //Seedling to sapling transition
  //*************************
  fDiam = 0.1;
  p_oTree = p_oPop->CreateTree(1, 1, 0, clTreePopulation::seedling, fDiam);
  iSp = p_oTree->GetSpecies();
  iTp = p_oTree->GetType();
  CPPUNIT_ASSERT(clTreePopulation::seedling == iTp);

  //Allowing allometry to update - push diam10 over the limit
  fDiam = 5.0;
  fHeight = 5.652239774;
  fDBH = 4.004;

  p_oTree->SetValue(p_oPop->GetDiam10Code(iSp, iTp), fDiam, true, true);
  iTp = p_oTree->GetType();
  iSp = p_oTree->GetSpecies();
  CPPUNIT_ASSERT(clTreePopulation::sapling == iTp);
  p_oTree->GetValue(p_oPop->GetHeightCode(iSp, iTp), &fTemp);
  CPPUNIT_ASSERT(fabs(fHeight - fTemp) < 0.001);
  p_oTree->GetValue(p_oPop->GetDbhCode(iSp, iTp), &fTemp);
  CPPUNIT_ASSERT(fabs(fDBH - fTemp) < 0.001);

  //Allowing allometry to update - make sure the seedling uses its own max
  //height to assess sapling transition; this one shouldn't push it over
  //the limit
  fDiam = 0.1;
  p_oTree = p_oPop->CreateTree(1, 1, 1, clTreePopulation::seedling, fDiam);
  iSp = p_oTree->GetSpecies();
  iTp = p_oTree->GetType();
  CPPUNIT_ASSERT(clTreePopulation::seedling == iTp);

  fDiam = 1.4;
  fHeight = 1.50175416;
  p_oTree->SetValue(p_oPop->GetDiam10Code(iSp, iTp), fDiam, true, true);
  iTp = p_oTree->GetType();
  CPPUNIT_ASSERT(clTreePopulation::seedling == iTp);
  p_oTree->GetValue(p_oPop->GetHeightCode(iSp, iTp), &fTemp);
  CPPUNIT_ASSERT(fabs(fHeight - fTemp) < 0.001);

  //Now this one should cause the transition
  fDiam = 0.1;
  p_oTree = p_oPop->CreateTree(1, 1, 1, clTreePopulation::seedling, fDiam);
  iSp = p_oTree->GetSpecies();
  iTp = p_oTree->GetType();
  CPPUNIT_ASSERT(clTreePopulation::seedling == iTp);

  fDiam = 5.0;
  fHeight = 5.652239774;
  fDBH = 4.004;

  p_oTree->SetValue(p_oPop->GetDiam10Code(iSp, iTp), fDiam, true, true);
  iTp = p_oTree->GetType();
  CPPUNIT_ASSERT(clTreePopulation::sapling == iTp);
  p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), iTp), &fTemp);
  CPPUNIT_ASSERT(fabs(fHeight - fTemp) < 0.001);
  p_oTree->GetValue(p_oPop->GetDbhCode(iSp, iTp), &fTemp);
  CPPUNIT_ASSERT(fabs(fDBH - fTemp) < 0.001);

  //Allowing allometry to update - push height over the limit
  fDiam = 0.1;
  p_oTree = p_oPop->CreateTree(1, 1, 0, clTreePopulation::seedling, fDiam);
  iSp = p_oTree->GetSpecies();
  iTp = p_oTree->GetType();
  CPPUNIT_ASSERT(clTreePopulation::seedling == iTp);

  fHeight = 2.0;
  fDiam = 0.718091127;
  fDBH = 0.575047375;

  p_oTree->SetValue(p_oPop->GetHeightCode(iSp, iTp), fHeight, true, true);
  iTp = p_oTree->GetType();
  CPPUNIT_ASSERT(clTreePopulation::sapling == iTp);
  p_oTree->GetValue(p_oPop->GetDiam10Code(iSp, iTp), &fTemp);
  CPPUNIT_ASSERT(fabs(fDiam - fTemp) < 0.001);
  p_oTree->GetValue(p_oPop->GetDbhCode(iSp, iTp), &fTemp);
  CPPUNIT_ASSERT(fabs(fDBH - fTemp) < 0.001);

  //Allowing allometry to update - make sure that the seedling uses its own
  //max height - this one should not transition
  fDiam = 0.1;
  p_oTree = p_oPop->CreateTree(1, 1, 1, clTreePopulation::seedling, fDiam);
  iSp = p_oTree->GetSpecies();
  iTp = p_oTree->GetType();
  CPPUNIT_ASSERT(clTreePopulation::seedling == iTp);

  fHeight = 1.5;
  fDiam = 1.398205496;

  p_oTree->SetValue(p_oPop->GetHeightCode(iSp, iTp), fHeight, true, true);
  iTp = p_oTree->GetType();
  CPPUNIT_ASSERT(clTreePopulation::seedling == iTp);
  p_oTree->GetValue(p_oPop->GetDiam10Code(iSp, iTp), &fTemp);
  CPPUNIT_ASSERT(fabs(fDiam - fTemp) < 0.001);

  //Now this should push it over the transition
  fHeight = 2.0;
  fDiam = 0.718091127;
  fDBH = 0.575047375;

  p_oTree->SetValue(p_oPop->GetHeightCode(iSp, iTp), fHeight, true, true);
  iTp = p_oTree->GetType();
  CPPUNIT_ASSERT(clTreePopulation::sapling == iTp);
  p_oTree->GetValue(p_oPop->GetDiam10Code(iSp, iTp), &fTemp);
  CPPUNIT_ASSERT(fabs(fDiam - fTemp) < 0.001);
  p_oTree->GetValue(p_oPop->GetDbhCode(iSp, iTp), &fTemp);
  CPPUNIT_ASSERT(fabs(fDBH - fTemp) < 0.001);

  //Not allowing allometry to update - push diam10 over the limit - it should
  //not transition to sapling
  fDiam = 0.1;
  p_oTree = p_oPop->CreateTree(1, 1, 0, clTreePopulation::seedling, fDiam);
  iSp = p_oTree->GetSpecies();
  iTp = p_oTree->GetType();
  CPPUNIT_ASSERT(clTreePopulation::seedling == iTp);

  fDiam = 5.0;
  fHeight = 0.202364959;

  p_oTree->SetValue(p_oPop->GetDiam10Code(iSp, iTp), fDiam, true, false);
  iTp = p_oTree->GetType();
  CPPUNIT_ASSERT(clTreePopulation::seedling == iTp);
  p_oTree->GetValue(p_oPop->GetHeightCode(iSp, iTp), &fTemp);
  CPPUNIT_ASSERT(fabs(fHeight - fTemp) < 0.001);

  //Not allowing allometry to update - push height over the limit - it should
  //transition but diam10 should be the same
  fDiam = 0.1;
  p_oTree = p_oPop->CreateTree(1, 1, 0, clTreePopulation::seedling, fDiam);
  iSp = p_oTree->GetSpecies();
  iTp = p_oTree->GetType();
  CPPUNIT_ASSERT(clTreePopulation::seedling == iTp);

  fHeight = 3.0;
  fDiam = 0.1;
  fDBH = 0.08008;

  p_oTree->SetValue(p_oPop->GetHeightCode(iSp, iTp), fHeight, true, false);
  iTp = p_oTree->GetType();
  CPPUNIT_ASSERT(clTreePopulation::sapling == iTp);
  p_oTree->GetValue(p_oPop->GetDiam10Code(iSp, iTp), &fTemp);
  CPPUNIT_ASSERT(fabs(fDiam - fTemp) < 0.001);
  p_oTree->GetValue(p_oPop->GetDbhCode(iSp, iTp), &fTemp);
  CPPUNIT_ASSERT(fabs(fDBH - fTemp) < 0.001);

  //*************************
  //Sapling to adult transition
  //*************************

  //Allowing allometry to update - push diam10 over the limit
  fDiam = 5.0;
  p_oTree = p_oPop->CreateTree(1, 1, 0, clTreePopulation::sapling, fDiam);
  iSp = p_oTree->GetSpecies();
  iTp = p_oTree->GetType();
  CPPUNIT_ASSERT(clTreePopulation::sapling == iTp);

  fDiam = 13.0;
  fDBH = 10.4104;
  fHeight = 11.54918907;

  p_oTree->SetValue(p_oPop->GetDiam10Code(iSp, iTp), fDiam, true, true);
  iTp = p_oTree->GetType();
  CPPUNIT_ASSERT(clTreePopulation::adult == iTp);
  p_oTree->GetValue(p_oPop->GetHeightCode(iSp, iTp), &fTemp);
  CPPUNIT_ASSERT(fabs(fHeight - fTemp) < 0.001);
  p_oTree->GetValue(p_oPop->GetDbhCode(iSp, iTp), &fTemp);
  CPPUNIT_ASSERT(fabs(fDBH - fTemp) < 0.001);

  //Allowing allometry to update - push DBH over the limit
  fDiam = 5.0;
  p_oTree = p_oPop->CreateTree(1, 1, 0, clTreePopulation::sapling, fDiam);
  iSp = p_oTree->GetSpecies();
  iTp = p_oTree->GetType();
  CPPUNIT_ASSERT(clTreePopulation::sapling == iTp);

  fDBH = 15;
  fHeight = 15.13074207;

  p_oTree->SetValue(p_oPop->GetDbhCode(iSp, iTp), fDBH, true, true);
  iTp = p_oTree->GetType();
  CPPUNIT_ASSERT(clTreePopulation::adult == iTp);
  p_oTree->GetValue(p_oPop->GetHeightCode(iSp, iTp), &fTemp);
  CPPUNIT_ASSERT(fabs(fHeight - fTemp) < 0.001);

  //Allowing allometry to update - push height over the limit
  fDiam = 5.0;
  p_oTree = p_oPop->CreateTree(1, 1, 0, clTreePopulation::sapling, fDiam);
  iSp = p_oTree->GetSpecies();
  iTp = p_oTree->GetType();
  CPPUNIT_ASSERT(clTreePopulation::sapling == iTp);

  fHeight = 20;
  fDBH = 22.46197577;

  p_oTree->SetValue(p_oPop->GetHeightCode(iSp, iTp), fHeight, true, true);
  iTp = p_oTree->GetType();
  CPPUNIT_ASSERT(clTreePopulation::adult == iTp);
  p_oTree->GetValue(p_oPop->GetDbhCode(iSp, iTp), &fTemp);
  CPPUNIT_ASSERT(fabs(fDBH - fTemp) < 0.001);

  //Not allowing allometry to update - push diam10 over the limit - it should
  //transition to adult
  fDiam = 5.0;
  p_oTree = p_oPop->CreateTree(1, 1, 0, clTreePopulation::sapling, fDiam);
  iSp = p_oTree->GetSpecies();
  iTp = p_oTree->GetType();
  CPPUNIT_ASSERT(clTreePopulation::sapling == iTp);

  fDiam = 13.0;
  fDBH = 10.4104;
  fHeight = 6.644791358;

  p_oTree->SetValue(p_oPop->GetDiam10Code(iSp, iTp), fDiam, true, false);
  iTp = p_oTree->GetType();
  CPPUNIT_ASSERT(clTreePopulation::adult == iTp);
  p_oTree->GetValue(p_oPop->GetHeightCode(iSp, iTp), &fTemp);
  CPPUNIT_ASSERT(fabs(fHeight - fTemp) < 0.001);
  p_oTree->GetValue(p_oPop->GetDbhCode(iSp, iTp), &fTemp);
  CPPUNIT_ASSERT(fabs(fDBH - fTemp) < 0.001);

  //Allowing allometry to update - push DBH over the limit - it should
  //transition to adult with diam10 and height the same
  fDiam = 5.0;
  p_oTree = p_oPop->CreateTree(1, 1, 0, clTreePopulation::sapling, fDiam);
  iSp = p_oTree->GetSpecies();
  iTp = p_oTree->GetType();
  CPPUNIT_ASSERT(clTreePopulation::sapling == iTp);

  fDBH = 15;
  fHeight = 6.644791358;

  p_oTree->SetValue(p_oPop->GetDbhCode(iSp, iTp), fDBH, true, false);
  iTp = p_oTree->GetType();
  CPPUNIT_ASSERT(clTreePopulation::adult == iTp);
  p_oTree->GetValue(p_oPop->GetHeightCode(iSp, iTp), &fTemp);
  CPPUNIT_ASSERT(fabs(fHeight - fTemp) < 0.001);

  //Not allowing allometry to update - push height over the limit - it should
  //not transition to adult
  fDiam = 5.0;
  p_oTree = p_oPop->CreateTree(1, 1, 0, clTreePopulation::sapling, fDiam);
  iSp = p_oTree->GetSpecies();
  iTp = p_oTree->GetType();
  CPPUNIT_ASSERT(clTreePopulation::sapling == iTp);

  fHeight = 20;
  fDBH = 5.0;

  p_oTree->SetValue(p_oPop->GetHeightCode(iSp, iTp), fHeight, true, false);
  iTp = p_oTree->GetType();
  CPPUNIT_ASSERT(clTreePopulation::sapling == iTp);
  p_oTree->GetValue(p_oPop->GetDbhCode(iSp, iTp), &fTemp);
  CPPUNIT_ASSERT(fabs(fDBH - fTemp) < 0.001);
}

/////////////////////////////////////////////////////////////////////////////
// TestClone()
/////////////////////////////////////////////////////////////////////////////
void clTestTree::TestClone(clSimManager *p_oSimManager)
{
 /* clTreePopulation * p_oPop;
  clTree *p_oTree, *p_oClone;
  float fDiam, fDBH, fHeight, fGLI, fTemp;
  int iSp, iTp, iDead, iYrsInfested, iTemp;

  //Set up our run and get the tree popluation pointer
  p_oSimManager->ReadFile( WriteXMLFile2() );
  p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

  //Create some trees so there will be taller-shorter pointers
  p_oTree = p_oPop->CreateTree(1, 1, 0, clTreePopulation::sapling, 8);
  p_oTree = p_oPop->CreateTree(1, 1, 0, clTreePopulation::sapling, 2);

  //Create a tree
  fDiam = 7.8;
  fHeight = 7.845800505;
  fDBH = 6.24624;
  fGLI = 56;
  iDead = fire;
  iYrsInfested = 3;
  p_oTree = p_oPop->CreateTree(1, 1, 0, clTreePopulation::sapling, fDBH);
  iSp = p_oTree->GetSpecies();
  iTp = p_oTree->GetType();
  p_oTree->GetValue(p_oPop->GetDiam10Code(iSp, iTp), &fTemp);
  CPPUNIT_ASSERT(fabs(fDiam - fTemp) < 0.001);
  p_oTree->GetValue(p_oPop->GetHeightCode(iSp, iTp), &fTemp);
  CPPUNIT_ASSERT(fabs(fHeight - fTemp) < 0.001);
  p_oTree->GetValue(p_oPop->GetDbhCode(iSp, iTp), &fTemp);
  CPPUNIT_ASSERT(fabs(fDBH - fTemp) < 0.001);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  p_oTree->SetValue(p_oPop->GetIntDataCode("YearsInfested", iSp, iTp), iYrsInfested);

  p_oClone = p_oTree->Clone();

  CPPUNIT_ASSERT(NULL == p_oClone->GetShorter());
  CPPUNIT_ASSERT(NULL == p_oClone->GetTaller());
  p_oClone->GetValue(p_oPop->GetDiam10Code(iSp, iTp), &fTemp);
  CPPUNIT_ASSERT(fabs(fDiam - fTemp) < 0.001);
  p_oClone->GetValue(p_oPop->GetHeightCode(iSp, iTp), &fTemp);
  CPPUNIT_ASSERT(fabs(fHeight - fTemp) < 0.001);
  p_oClone->GetValue(p_oPop->GetDbhCode(iSp, iTp), &fTemp);
  CPPUNIT_ASSERT(fabs(fDBH - fTemp) < 0.001);
  p_oClone->GetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), &iTemp);
  CPPUNIT_ASSERT(iTemp == iDead);
  p_oClone->GetValue(p_oPop->GetIntDataCode("YearsInfested", iSp, iTp), &iTemp);
  CPPUNIT_ASSERT(iTemp == iYrsInfested);*/
}

/////////////////////////////////////////////////////////////////////////////
//  WriteXMLFile1()
/////////////////////////////////////////////////////////////////////////////
const char* clTestTree::WriteXMLFile1()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">" << "<plot>"
       << "<timesteps>3</timesteps>"
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
       << "<tr_species speciesName=\"Species_1\"/>"
       << "<tr_species speciesName=\"Species_2\"/>"
       << "</tr_speciesList>"
       << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"Species_1\">10</tr_madVal>"
       << "<tr_madVal species=\"Species_2\">10</tr_madVal>"
       << "</tr_minAdultDBH>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_2\">1.6</tr_mshVal>"
       << "</tr_maxSeedlingHeight>"
       << "</trees>"
       << "<allometry>"
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
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_2\">0.0299</tr_soahVal>"
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
       << "<behaviorName>ConstantGLI</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\" />"
       << "</behavior>"
       << "</behaviorList>"
       << "<ConstantGLI1>"
       << "<li_constGLI>100</li_constGLI>"
       << "</ConstantGLI1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteXMLFile2()
/////////////////////////////////////////////////////////////////////////////
const char* clTestTree::WriteXMLFile2()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">" << "<plot>"
       << "<timesteps>3</timesteps>"
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
       << "<tr_species speciesName=\"Species_1\"/>"
       << "</tr_speciesList>"
       << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"Species_1\">10</tr_madVal>"
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
       << "<tr_wsahdVal species=\"Species_2\">0</tr_wsahdVal>"
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
       << "<behaviorName>ConstantGLI</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>InsectInfestation</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<ConstantGLI1>"
       << "<li_constGLI>100</li_constGLI>"
       << "</ConstantGLI1>"
       << "<disturbanceOther>"
       << "<di_insectIntercept>"
       << "<di_iiVal species=\"Species_1\">0.01</di_iiVal>"
       << "</di_insectIntercept>"
       << "<di_insectMaxInfestation>"
       << "<di_imiVal species=\"Species_1\">1</di_imiVal>"
       << "</di_insectMaxInfestation>"
       << "<di_insectX0>"
       << "<di_ix0Val species=\"Species_1\">5</di_ix0Val>"
       << "</di_insectX0>"
       << "<di_insectXb>"
       << "<di_ixbVal species=\"Species_1\">-4</di_ixbVal>"
       << "</di_insectXb>"
       << "<di_insectMinDBH>"
       << "<di_imdVal species=\"Species_1\">2.2</di_imdVal>"
       << "</di_insectMinDBH>"
       << "<di_insectStartTimestep>1</di_insectStartTimestep>"
       << "</disturbanceOther>"
       << "<StochasticMortality2>"
       << "<mo_stochasticMortRate>"
       << "<mo_smrVal species=\"Species_1\">0.1</mo_smrVal>"
       << "</mo_stochasticMortRate>"
       << "</StochasticMortality2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}
