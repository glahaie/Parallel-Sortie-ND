//---------------------------------------------------------------------------
// TestTreePopulation.cpp
//---------------------------------------------------------------------------
#include "TestTreePopulation.h"
#include "SimManager.h"
#include "TreePopulation.h"
#include <fstream>
#include <math.h>

/////////////////////////////////////////////////////////////////////////////
// TestTreePopulation()
/////////////////////////////////////////////////////////////////////////////
void clTestTreePopulation::TestTreePopulation()
{
  clSimManager * p_oSimManager = new clSimManager( 3, 3, "" );

  TestTreeSetters( p_oSimManager);
  TestSnagAges( p_oSimManager );
  TestKillTree( p_oSimManager );
  TestGetters( p_oSimManager );
  TestHashTable( p_oSimManager );
  TestHashTableNoAllomUpdate(p_oSimManager);
  TestTreeSearching( p_oSimManager );

  delete p_oSimManager;
}

/////////////////////////////////////////////////////////////////////////////
// TestSnagAges()
/////////////////////////////////////////////////////////////////////////////
void clTestTreePopulation::TestSnagAges( clSimManager * p_oSimManager )
{
  clPopulationBase * p_oTemp;
  clTreePopulation * p_oPop;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;
  int iTreeCount = 0, iAge;

  //Read in the parameter file
  p_oSimManager->ReadFile(WriteXMLFile4());
  p_oTemp = p_oSimManager->GetPopulationObject( "treepopulation" );
  p_oPop = ( clTreePopulation * ) p_oTemp;

  //Kill all adults
  p_oAllTrees = p_oPop->Find("all");
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {

    if (clTreePopulation::adult == p_oTree->GetType()) {
      p_oPop->KillTree(p_oTree, natural);
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Check the ages of each snag - should all be 0
  p_oAllTrees = p_oPop->Find("all");
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {

    if (clTreePopulation::snag == p_oTree->GetType()) {

       iTreeCount++;
       p_oTree->GetValue(p_oPop->GetAgeCode(p_oTree->GetSpecies()), &iAge);
       CPPUNIT_ASSERT(0 == iAge);
    }

    p_oTree = p_oAllTrees->NextTree();
  }
  CPPUNIT_ASSERT(4 == iTreeCount);

  //Run a timestep and check the ages again - should all be 1
  p_oSimManager->RunSim(1);
  iTreeCount = 0;
  p_oAllTrees = p_oPop->Find("all");
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {

    if (clTreePopulation::snag == p_oTree->GetType()) {

       iTreeCount++;
       p_oTree->GetValue(p_oPop->GetAgeCode(p_oTree->GetSpecies()), &iAge);
       CPPUNIT_ASSERT(1 == iAge);
    }

    p_oTree = p_oAllTrees->NextTree();
  }
  CPPUNIT_ASSERT(4 == iTreeCount);

  p_oSimManager->RunSim(1);
  iTreeCount = 0;
  p_oAllTrees = p_oPop->Find("all");
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {

    if (clTreePopulation::snag == p_oTree->GetType()) {

       iTreeCount++;
       p_oTree->GetValue(p_oPop->GetAgeCode(p_oTree->GetSpecies()), &iAge);
       CPPUNIT_ASSERT(2 == iAge);
    }

    p_oTree = p_oAllTrees->NextTree();
  }
  CPPUNIT_ASSERT(4 == iTreeCount);


  //Repeat with WriteXMLFile5()
  iTreeCount = 0;
  //Read in the parameter file
  p_oSimManager->ReadFile(WriteXMLFile5());
  p_oTemp = p_oSimManager->GetPopulationObject( "treepopulation" );
  p_oPop = ( clTreePopulation * ) p_oTemp;

  //Kill all adults
  p_oAllTrees = p_oPop->Find("all");
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {

    if (clTreePopulation::adult == p_oTree->GetType()) {
      p_oPop->KillTree(p_oTree, natural);
    }
    p_oTree = p_oAllTrees->NextTree();
  }

  //Check the ages of each snag - should all be 0
  p_oAllTrees = p_oPop->Find("all");
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {

    if (clTreePopulation::snag == p_oTree->GetType()) {

       iTreeCount++;
       p_oTree->GetValue(p_oPop->GetAgeCode(p_oTree->GetSpecies()), &iAge);
       CPPUNIT_ASSERT(0 == iAge);
    }

    p_oTree = p_oAllTrees->NextTree();
  }
  CPPUNIT_ASSERT(4 == iTreeCount);

  //Run a timestep and check the ages again - should all be 3
  p_oSimManager->RunSim(1);
  iTreeCount = 0;
  p_oAllTrees = p_oPop->Find("all");
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {

    if (clTreePopulation::snag == p_oTree->GetType()) {

       iTreeCount++;
       p_oTree->GetValue(p_oPop->GetAgeCode(p_oTree->GetSpecies()), &iAge);
       CPPUNIT_ASSERT(3 == iAge);
    }

    p_oTree = p_oAllTrees->NextTree();
  }
  CPPUNIT_ASSERT(4 == iTreeCount);
  p_oSimManager->RunSim(1);
  iTreeCount = 0;
  p_oAllTrees = p_oPop->Find("all");
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {

    if (clTreePopulation::snag == p_oTree->GetType()) {

       iTreeCount++;
       p_oTree->GetValue(p_oPop->GetAgeCode(p_oTree->GetSpecies()), &iAge);
       CPPUNIT_ASSERT(6 == iAge);
    }

    p_oTree = p_oAllTrees->NextTree();
  }
  CPPUNIT_ASSERT(4 == iTreeCount);

}

/////////////////////////////////////////////////////////////////////////////
//  TestKillTree()
/////////////////////////////////////////////////////////////////////////////
void clTestTreePopulation::TestKillTree( clSimManager * p_oSimManager )
{
  clPopulationBase * p_oTemp;
  clTreePopulation * p_oPop;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;
  float fTemp;
  int *p_iTreeList;
  int iNumTrees = 8, i, iTemp, iTreeCount;

  p_oSimManager->ReadFile( WriteXMLFile3() );
  p_oTemp = p_oSimManager->GetPopulationObject( "treepopulation" );
  p_oPop = ( clTreePopulation * ) p_oTemp;

  //The trees are identified by number, which corresponds to their X and Y
  //coordinates.  Tree 1 is a seedling of Species 1; tree 2 is a seedling of
  //species 2; tree 3 is a sapling of species 1; etc.  Species 1 stumps,
  //species 2 does not.  The p_iTreeList will hold the type number for each
  //tree, or -1 if the tree does not exist.  Declare that array and initialize
  //to all -1

  p_iTreeList = new int[iNumTrees];
  for (i = 0; i < iNumTrees; i++) p_iTreeList[i] = -1;

  //Just to make sure, do a search and verify that our initial conditions are
  //the way we expect them
  p_oAllTrees = p_oPop->Find("all");
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {

    //Get the tree's X coordinate, which equals the tree number
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);

    //Set the tree's type
    p_iTreeList[(int)fTemp - 1] = p_oTree->GetType();

    p_oTree = p_oAllTrees->NextTree();
  }

  //Repeat with stumps
  p_oTree = p_oPop->GetFirstStump();
  while ( p_oTree )
  {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
    //Set the tree's type
    p_iTreeList[(int)fTemp - 1] = p_oTree->GetType();
    p_oTree = p_oTree->GetTaller();
  }

  CPPUNIT_ASSERT(p_iTreeList[0] == clTreePopulation::seedling);
  CPPUNIT_ASSERT(p_iTreeList[1] == clTreePopulation::seedling);
  CPPUNIT_ASSERT(p_iTreeList[2] == clTreePopulation::sapling);
  CPPUNIT_ASSERT(p_iTreeList[3] == clTreePopulation::sapling);
  CPPUNIT_ASSERT(p_iTreeList[4] == clTreePopulation::adult);
  CPPUNIT_ASSERT(p_iTreeList[5] == clTreePopulation::adult);
  CPPUNIT_ASSERT(p_iTreeList[6] == clTreePopulation::snag);
  CPPUNIT_ASSERT(p_iTreeList[7] == clTreePopulation::snag);

  //**************************************************
  //Kill all the trees due to natural cause - no snags
  //**************************************************
  p_oAllTrees->StartOver();
  for (i = 0; i < iNumTrees; i++) p_iTreeList[i] = -1;
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {
    p_oPop->KillTree(p_oTree, natural);
    p_oTree = p_oAllTrees->NextTree();
  }

  //Collect the flags again
  p_oAllTrees = p_oPop->Find("all");
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {

    //Get the tree's X coordinate, which equals the tree number
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);

    //Set the tree's type
    p_iTreeList[(int)fTemp - 1] = p_oTree->GetType();

    p_oTree = p_oAllTrees->NextTree();
  }

  //Repeat with stumps
  p_oTree = p_oPop->GetFirstStump();
  while ( p_oTree )
  {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
    //Set the tree's type
    p_iTreeList[(int)fTemp - 1] = p_oTree->GetType();
    p_oTree = p_oTree->GetTaller();
  }

  //All trees should be gone
  for (i = 0; i < iNumTrees; i++) {
    CPPUNIT_ASSERT(p_iTreeList[i] == -1);
  }

  //**************************************************
  //Kill all the trees due to disease - no snags
  //**************************************************
  p_oSimManager->ReadFile( WriteXMLFile3() );
  p_oTemp = p_oSimManager->GetPopulationObject( "treepopulation" );
  p_oPop = ( clTreePopulation * ) p_oTemp;
  for (i = 0; i < iNumTrees; i++) p_iTreeList[i] = -1;

  p_oAllTrees = p_oPop->Find("all");
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {
    p_oPop->KillTree(p_oTree, disease);
    p_oTree = p_oAllTrees->NextTree();
  }

  //Collect the flags
  p_oAllTrees = p_oPop->Find("all");
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {

    //Get the tree's X coordinate, which equals the tree number
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);

    //Set the tree's type
    p_iTreeList[(int)fTemp - 1] = p_oTree->GetType();

    p_oTree = p_oAllTrees->NextTree();
  }

  //Repeat with stumps
  p_oTree = p_oPop->GetFirstStump();
  while ( p_oTree )
  {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
    //Set the tree's type
    p_iTreeList[(int)fTemp - 1] = p_oTree->GetType();
    p_oTree = p_oTree->GetTaller();
  }

  //All trees should be gone
  for (i = 0; i < iNumTrees; i++) {
    CPPUNIT_ASSERT(p_iTreeList[i] == -1);
  }

  //**************************************************
  //Kill all the trees due to insects - no snags
  //**************************************************
  p_oSimManager->ReadFile( WriteXMLFile3() );
  p_oTemp = p_oSimManager->GetPopulationObject( "treepopulation" );
  p_oPop = ( clTreePopulation * ) p_oTemp;
  for (i = 0; i < iNumTrees; i++) p_iTreeList[i] = -1;

  p_oAllTrees = p_oPop->Find("all");
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {
    p_oPop->KillTree(p_oTree, insects);
    p_oTree = p_oAllTrees->NextTree();
  }

  //Collect the flags
  p_oAllTrees = p_oPop->Find("all");
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {

    //Get the tree's X coordinate, which equals the tree number
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);

    //Set the tree's type
    p_iTreeList[(int)fTemp - 1] = p_oTree->GetType();

    p_oTree = p_oAllTrees->NextTree();
  }

  //Repeat with stumps
  p_oTree = p_oPop->GetFirstStump();
  while ( p_oTree )
  {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
    //Set the tree's type
    p_iTreeList[(int)fTemp - 1] = p_oTree->GetType();
    p_oTree = p_oTree->GetTaller();
  }

  //All trees should be gone
  for (i = 0; i < iNumTrees; i++) {
    CPPUNIT_ASSERT(p_iTreeList[i] == -1);
  }

  //**************************************************
  //Kill all the trees due to fire - no snags
  //**************************************************
  p_oSimManager->ReadFile( WriteXMLFile3() );
  p_oTemp = p_oSimManager->GetPopulationObject( "treepopulation" );
  p_oPop = ( clTreePopulation * ) p_oTemp;
  for (i = 0; i < iNumTrees; i++) p_iTreeList[i] = -1;

  p_oAllTrees = p_oPop->Find("all");
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {
    p_oPop->KillTree(p_oTree, fire);
    p_oTree = p_oAllTrees->NextTree();
  }

  //Collect the flags
  p_oAllTrees = p_oPop->Find("all");
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {

    //Get the tree's X coordinate, which equals the tree number
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);

    //Set the tree's type
    p_iTreeList[(int)fTemp - 1] = p_oTree->GetType();

    p_oTree = p_oAllTrees->NextTree();
  }

  //Repeat with stumps
  p_oTree = p_oPop->GetFirstStump();
  while ( p_oTree )
  {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
    //Set the tree's type
    p_iTreeList[(int)fTemp - 1] = p_oTree->GetType();
    p_oTree = p_oTree->GetTaller();
  }

  //All trees should be gone
  for (i = 0; i < iNumTrees; i++) {
    CPPUNIT_ASSERT(p_iTreeList[i] == -1);
  }

  //**************************************************
  //Kill all the trees due to harvest - no snags
  //**************************************************
  p_oSimManager->ReadFile( WriteXMLFile3() );
  p_oTemp = p_oSimManager->GetPopulationObject( "treepopulation" );
  p_oPop = ( clTreePopulation * ) p_oTemp;
  for (i = 0; i < iNumTrees; i++) p_iTreeList[i] = -1;

  p_oAllTrees = p_oPop->Find("all");
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {
    p_oPop->KillTree(p_oTree, harvest);
    p_oTree = p_oAllTrees->NextTree();
  }

  //Collect the flags
  p_oAllTrees = p_oPop->Find("all");
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {

    //Get the tree's X coordinate, which equals the tree number
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);

    //Set the tree's type
    p_iTreeList[(int)fTemp - 1] = p_oTree->GetType();

    p_oTree = p_oAllTrees->NextTree();
  }

  //Make sure that the adults are gone before we go through the stumps - trees 5 & 6
  CPPUNIT_ASSERT(p_iTreeList[4] == -1);
  CPPUNIT_ASSERT(p_iTreeList[5] == -1);

  //Repeat with stumps
  p_oTree = p_oPop->GetFirstStump();
  while ( p_oTree )
  {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
    //Set the tree's type
    p_iTreeList[(int)fTemp - 1] = p_oTree->GetType();
    p_oTree = p_oTree->GetTaller();
  }

  //All trees should be gone except the sapling (#3) and adult (# 5) of
  //species 1, which should be stumps
  for (i = 0; i < iNumTrees; i++) {
    if (i == 4 || i == 2)
      CPPUNIT_ASSERT(p_iTreeList[i] == clTreePopulation::stump);
    else
      CPPUNIT_ASSERT(p_iTreeList[i] == -1);
  }

  //**************************************************
  //Kill all the trees with forced removal - no snags
  //**************************************************
  p_oSimManager->ReadFile( WriteXMLFile3() );
  p_oTemp = p_oSimManager->GetPopulationObject( "treepopulation" );
  p_oPop = ( clTreePopulation * ) p_oTemp;
  for (i = 0; i < iNumTrees; i++) p_iTreeList[i] = -1;

  p_oAllTrees = p_oPop->Find("all");
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {
    p_oPop->KillTree(p_oTree, remove_tree);
    p_oTree = p_oAllTrees->NextTree();
  }

  //Collect the flags
  p_oAllTrees = p_oPop->Find("all");
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {

    //Get the tree's X coordinate, which equals the tree number
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);

    //Set the tree's type
    p_iTreeList[(int)fTemp - 1] = p_oTree->GetType();

    p_oTree = p_oAllTrees->NextTree();
  }

  //Repeat with stumps
  p_oTree = p_oPop->GetFirstStump();
  while ( p_oTree )
  {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
    //Set the tree's type
    p_iTreeList[(int)fTemp - 1] = p_oTree->GetType();
    p_oTree = p_oTree->GetTaller();
  }

  //All trees should be gone
  for (i = 0; i < iNumTrees; i++) {
    CPPUNIT_ASSERT(p_iTreeList[i] == -1);
  }

  //**************************************************
  //Redo everything with snags this time
  //**************************************************
  //Test our initial conditions
  p_oSimManager->ReadFile( WriteXMLFile4() );
  p_oTemp = p_oSimManager->GetPopulationObject( "treepopulation" );
  p_oPop = ( clTreePopulation * ) p_oTemp;
  for (i = 0; i < iNumTrees; i++) p_iTreeList[i] = -1;
  p_oAllTrees = p_oPop->Find("all");
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {

    //Get the tree's X coordinate, which equals the tree number
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);

    //Set the tree's type
    p_iTreeList[(int)fTemp - 1] = p_oTree->GetType();

    p_oTree = p_oAllTrees->NextTree();
  }

  //Repeat with stumps
  p_oTree = p_oPop->GetFirstStump();
  while ( p_oTree )
  {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
    //Set the tree's type
    p_iTreeList[(int)fTemp - 1] = p_oTree->GetType();
    p_oTree = p_oTree->GetTaller();
  }
  CPPUNIT_ASSERT(p_iTreeList[0] == clTreePopulation::seedling);
  CPPUNIT_ASSERT(p_iTreeList[1] == clTreePopulation::seedling);
  CPPUNIT_ASSERT(p_iTreeList[2] == clTreePopulation::sapling);
  CPPUNIT_ASSERT(p_iTreeList[3] == clTreePopulation::sapling);
  CPPUNIT_ASSERT(p_iTreeList[4] == clTreePopulation::adult);
  CPPUNIT_ASSERT(p_iTreeList[5] == clTreePopulation::adult);
  CPPUNIT_ASSERT(p_iTreeList[6] == clTreePopulation::snag);
  CPPUNIT_ASSERT(p_iTreeList[7] == clTreePopulation::snag);

  //**************************************************
  //Kill all the trees due to natural cause - with snags
  //**************************************************
  p_oAllTrees->StartOver();
  for (i = 0; i < iNumTrees; i++) p_iTreeList[i] = -1;
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {
    p_oPop->KillTree(p_oTree, natural);
    p_oTree = p_oAllTrees->NextTree();
  }

  //Collect the flags again
  p_oAllTrees = p_oPop->Find("all");
  p_oTree = p_oAllTrees->NextTree();
  iTreeCount = 0;
  while (p_oTree) {

    //Get the tree's X coordinate, which equals the tree number
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
    i = (int)fTemp - 1;
    //Trees 5 & 6 should be snags - all others should be gone
    CPPUNIT_ASSERT(i == 4 || i == 5);
    CPPUNIT_ASSERT(p_oTree->GetType() == clTreePopulation::snag);
    //Make sure the reason code is right
    p_oTree->GetValue(p_oPop->GetWhyDeadCode(p_oTree->GetSpecies()), &iTemp);
    CPPUNIT_ASSERT(natural == iTemp);
    //Make sure the snags are the same size as the adults were
    p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
    CPPUNIT_ASSERT(fTemp == 33.0);

    iTreeCount++;

    p_oTree = p_oAllTrees->NextTree();
  }
  CPPUNIT_ASSERT(2 == iTreeCount);

  //Repeat with stumps
  p_oTree = p_oPop->GetFirstStump();
  CPPUNIT_ASSERT(NULL == p_oTree);

  //**************************************************
  //Kill all the trees due to disease - with snags
  //**************************************************
  p_oSimManager->ReadFile( WriteXMLFile4() );
  p_oTemp = p_oSimManager->GetPopulationObject( "treepopulation" );
  p_oPop = ( clTreePopulation * ) p_oTemp;
  for (i = 0; i < iNumTrees; i++) p_iTreeList[i] = -1;

  p_oAllTrees = p_oPop->Find("all");
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {
    p_oPop->KillTree(p_oTree, disease);
    p_oTree = p_oAllTrees->NextTree();
  }

  //Collect the flags
  p_oAllTrees = p_oPop->Find("all");
  p_oTree = p_oAllTrees->NextTree();
  iTreeCount = 0;
    while (p_oTree) {

      //Get the tree's X coordinate, which equals the tree number
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
      i = (int)fTemp - 1;
      //Trees 5 & 6 should be snags - all others should be gone
      CPPUNIT_ASSERT(i == 4 || i == 5);
      CPPUNIT_ASSERT(p_oTree->GetType() == clTreePopulation::snag);
      //Make sure the reason code is right
      p_oTree->GetValue(p_oPop->GetWhyDeadCode(p_oTree->GetSpecies()), &iTemp);
      CPPUNIT_ASSERT(disease == iTemp);
      //Make sure the snags are the same size as the adults were
      p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
      CPPUNIT_ASSERT(fTemp == 33.0);

      iTreeCount++;

      p_oTree = p_oAllTrees->NextTree();
    }
    CPPUNIT_ASSERT(2 == iTreeCount);

    //Repeat with stumps
    p_oTree = p_oPop->GetFirstStump();
    CPPUNIT_ASSERT(NULL == p_oTree);

  //**************************************************
  //Kill all the trees due to insects - with snags
  //**************************************************
  p_oSimManager->ReadFile( WriteXMLFile4() );
  p_oTemp = p_oSimManager->GetPopulationObject( "treepopulation" );
  p_oPop = ( clTreePopulation * ) p_oTemp;
  for (i = 0; i < iNumTrees; i++) p_iTreeList[i] = -1;

  p_oAllTrees = p_oPop->Find("all");
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {
    p_oPop->KillTree(p_oTree, insects);
    p_oTree = p_oAllTrees->NextTree();
  }

  //Collect the flags
  p_oAllTrees = p_oPop->Find("all");
  p_oTree = p_oAllTrees->NextTree();
  iTreeCount = 0;
  while (p_oTree) {

    //Get the tree's X coordinate, which equals the tree number
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
    i = (int)fTemp - 1;
    //Trees 5 & 6 should be snags - all others should be gone
    CPPUNIT_ASSERT(i == 4 || i == 5);
    CPPUNIT_ASSERT(p_oTree->GetType() == clTreePopulation::snag);
    //Make sure the reason code is right
    p_oTree->GetValue(p_oPop->GetWhyDeadCode(p_oTree->GetSpecies()), &iTemp);
    CPPUNIT_ASSERT(insects == iTemp);
    //Make sure the snags are the same size as the adults were
    p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
    CPPUNIT_ASSERT(fTemp == 33.0);

    iTreeCount++;

    p_oTree = p_oAllTrees->NextTree();
  }
  CPPUNIT_ASSERT(2 == iTreeCount);

  //Repeat with stumps
  p_oTree = p_oPop->GetFirstStump();
  CPPUNIT_ASSERT(NULL == p_oTree);

  //**************************************************
  //Kill all the trees due to fire - with snags
  //**************************************************
  p_oSimManager->ReadFile( WriteXMLFile4() );
  p_oTemp = p_oSimManager->GetPopulationObject( "treepopulation" );
  p_oPop = ( clTreePopulation * ) p_oTemp;
  for (i = 0; i < iNumTrees; i++) p_iTreeList[i] = -1;

  p_oAllTrees = p_oPop->Find("all");
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {
    p_oPop->KillTree(p_oTree, fire);
    p_oTree = p_oAllTrees->NextTree();
  }

  //Collect the flags
  p_oAllTrees = p_oPop->Find("all");
  p_oTree = p_oAllTrees->NextTree();
  iTreeCount = 0;
  while (p_oTree) {

    //Get the tree's X coordinate, which equals the tree number
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
    i = (int)fTemp - 1;
    //Trees 5 & 6 should be snags - all others should be gone
    CPPUNIT_ASSERT(i == 4 || i == 5);
    CPPUNIT_ASSERT(p_oTree->GetType() == clTreePopulation::snag);
    //Make sure the reason code is right
    p_oTree->GetValue(p_oPop->GetWhyDeadCode(p_oTree->GetSpecies()), &iTemp);
    CPPUNIT_ASSERT(fire == iTemp);
    //Make sure the snags are the same size as the adults were
    p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
    CPPUNIT_ASSERT(fTemp == 33.0);

    iTreeCount++;

    p_oTree = p_oAllTrees->NextTree();
  }
  CPPUNIT_ASSERT(2 == iTreeCount);

  //Repeat with stumps
  p_oTree = p_oPop->GetFirstStump();
  CPPUNIT_ASSERT(NULL == p_oTree);


  //**************************************************
  //Kill all the trees due to harvest - with snags
  //**************************************************
  p_oSimManager->ReadFile( WriteXMLFile4() );
  p_oTemp = p_oSimManager->GetPopulationObject( "treepopulation" );
  p_oPop = ( clTreePopulation * ) p_oTemp;
  for (i = 0; i < iNumTrees; i++) p_iTreeList[i] = -1;

  p_oAllTrees = p_oPop->Find("all");
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {
    p_oPop->KillTree(p_oTree, harvest);
    p_oTree = p_oAllTrees->NextTree();
  }

  //Collect the flags
  p_oAllTrees = p_oPop->Find("all");
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {

    //Get the tree's X coordinate, which equals the tree number
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);

    //Set the tree's type
    p_iTreeList[(int)fTemp - 1] = p_oTree->GetType();

    p_oTree = p_oAllTrees->NextTree();
  }

  //Make sure that the adults are gone before we go through the stumps - trees 5 & 6
  CPPUNIT_ASSERT(p_iTreeList[4] == -1);
  CPPUNIT_ASSERT(p_iTreeList[5] == -1);

  //Repeat with stumps
  p_oTree = p_oPop->GetFirstStump();
  while ( p_oTree )
  {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
    //Set the tree's type
    p_iTreeList[(int)fTemp - 1] = p_oTree->GetType();
    p_oTree = p_oTree->GetTaller();
  }

  //All trees should be gone except the sapling (#3) and adult (# 5) of
  //species 1, which should be stumps
  for (i = 0; i < iNumTrees; i++) {
    if (i == 4 || i == 2)
      CPPUNIT_ASSERT(p_iTreeList[i] == clTreePopulation::stump);
    else
      CPPUNIT_ASSERT(p_iTreeList[i] == -1);
  }

  //**************************************************
  //Kill all the trees with forced removal - with snags
  //**************************************************
  p_oSimManager->ReadFile( WriteXMLFile4() );
  p_oTemp = p_oSimManager->GetPopulationObject( "treepopulation" );
  p_oPop = ( clTreePopulation * ) p_oTemp;
  for (i = 0; i < iNumTrees; i++) p_iTreeList[i] = -1;

  p_oAllTrees = p_oPop->Find("all");
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {
    p_oPop->KillTree(p_oTree, remove_tree);
    p_oTree = p_oAllTrees->NextTree();
  }

  //Collect the flags
  p_oAllTrees = p_oPop->Find("all");
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {

    //Get the tree's X coordinate, which equals the tree number
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);

    //Set the tree's type
    p_iTreeList[(int)fTemp - 1] = p_oTree->GetType();

    p_oTree = p_oAllTrees->NextTree();
  }

  //Repeat with stumps
  p_oTree = p_oPop->GetFirstStump();
  while ( p_oTree )
  {
    p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fTemp);
    //Set the tree's type
    p_iTreeList[(int)fTemp - 1] = p_oTree->GetType();
    p_oTree = p_oTree->GetTaller();
  }

  //All trees should be gone
  for (i = 0; i < iNumTrees; i++) {
    CPPUNIT_ASSERT(p_iTreeList[i] == -1);
  }

  delete[] p_iTreeList;
}

/////////////////////////////////////////////////////////////////////////////
// TestTreeSearching()
/////////////////////////////////////////////////////////////////////////////
void clTestTreePopulation::TestTreeSearching( clSimManager * p_oSimManager )
{
  clTreePopulation * p_oPop;
  clTreeSearch *p_oAllTrees;
  clTree * * p_oTreeSet, *p_oTree;
  int iNumTrees;

  p_oSimManager->ReadFile( WriteXMLFile2() );
  p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

  iNumTrees = 80;
  p_oTreeSet = new clTree * [iNumTrees];

  LoadTrees1( p_oPop, NULL, NULL, NULL, NULL, p_oTreeSet, 0, 0, false, false );
  LoadTrees2( p_oPop, p_oTreeSet, true );
  DoSet1Searches( p_oPop, p_oTreeSet );
  DoSet2Searches( p_oPop, p_oTreeSet );
  DoSet3Searches( p_oPop );
  delete[] p_oTreeSet;

  //This is in response to a bug found - this tests distance-height searches
  //when the plot has odd-sized cells at the end
  p_oSimManager->ReadFile( WriteXMLFile6() );
  p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
  //Create a list of trees
  p_oPop->CreateTree(95.0, 95.0, 0, clTreePopulation::adult, 20.0);
  p_oPop->CreateTree(98.0, 97.0, 0, clTreePopulation::adult, 20.0);
  p_oPop->CreateTree(4.0, 95.0, 0, clTreePopulation::adult, 20.0);
  p_oPop->CreateTree(95.0, 4.0, 0, clTreePopulation::adult, 20.0);
  p_oPop->CreateTree(0.0, 0.0, 0, clTreePopulation::adult, 20.0);
  p_oPop->CreateTree(96.0, 97.0, 0, clTreePopulation::adult, 20.0);
  p_oPop->CreateTree(4.0, 97.0, 0, clTreePopulation::adult, 20.0);
  p_oPop->CreateTree(0.0, 95.0, 0, clTreePopulation::adult, 20.0);
  p_oPop->CreateTree(95.0, 3.0, 0, clTreePopulation::adult, 20.0);
  p_oPop->CreateTree(0.0, 97.0, 0, clTreePopulation::adult, 20.0);
  p_oPop->CreateTree(98.0, 1.0, 0, clTreePopulation::adult, 20.0);
  //Do a search and make sure that all trees were found
  iNumTrees = 0;
  p_oAllTrees = p_oPop->Find("distance=10.0 FROM x=1.0,y=97.0::height=0.0");
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {
    iNumTrees++;
    p_oTree = p_oAllTrees->NextTree();
  }
  CPPUNIT_ASSERT(11 == iNumTrees);
}



/////////////////////////////////////////////////////////////////////////////
// TestTreeSetters()
/////////////////////////////////////////////////////////////////////////////
void clTestTreePopulation::TestTreeSetters( clSimManager * p_oSimManager )
{
  clTreePopulation * p_oPop;
  clTree *p_oTree;
  float fExpectedResult, fActualResult;

  p_oSimManager->ReadFile( WriteXMLFile1() );
  p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

  //Seedling
  p_oTree = p_oPop->CreateTree( 4.0, 4.0, 0, clTreePopulation::seedling, 0.2 );

  //Reset the diameter
  fExpectedResult = 0.3;
  p_oTree->SetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()),fExpectedResult);
  p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()),&fActualResult);
  CPPUNIT_ASSERT( fabs( fActualResult - fExpectedResult ) < 0.0001 );

  //Reset the height
  fExpectedResult = 1.15;
  p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()),fExpectedResult);
  p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()),&fActualResult);
  CPPUNIT_ASSERT( fabs( fActualResult - fExpectedResult ) < 0.0001 );

  //Error processing - no diameter smaller than the minimum
  fExpectedResult = 0;
  try {
    p_oTree->SetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()),fExpectedResult);
    CppUnit::Asserter::fail("Tree population didn't catch seedling diam10 less than the minimum.");
  }
  catch (modelErr& err) {;}

  //Error processing - no negative heights
  fExpectedResult = -1.0;
  try {
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()),fExpectedResult);
    CppUnit::Asserter::fail("Tree population didn't catch negative seedling height.");
  }
  catch (modelErr& err) {;}

  /////////////////////////////////
  //Sapling
  p_oTree = p_oPop->CreateTree( 4.0, 4.0, 0, clTreePopulation::sapling, 5.0 );

  //Reset the diameter
  fExpectedResult = 3.0;
  p_oTree->SetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()),fExpectedResult);
  p_oTree->GetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()),&fActualResult);
  CPPUNIT_ASSERT( fabs( fActualResult - fExpectedResult ) < 0.0001 );

  //Reset the height
  fExpectedResult = 3.0;
  p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()),fExpectedResult);
  p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()),&fActualResult);
  CPPUNIT_ASSERT( fabs( fActualResult - fExpectedResult ) < 0.0001 );

  //Error processing - no negative diameter
  fExpectedResult = -3.0;
  try {
    p_oTree->SetValue(p_oPop->GetDiam10Code(p_oTree->GetSpecies(), p_oTree->GetType()),fExpectedResult);
    CppUnit::Asserter::fail("Tree population didn't catch negative sapling diam10.");
  }
  catch (modelErr& err) {;}
  try {
    p_oTree->SetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()),fExpectedResult);
    CppUnit::Asserter::fail("Tree population didn't catch negative sapling DBH.");
  }
  catch (modelErr& err) {;}

  //Error processing - no negative heights
  fExpectedResult = -3.0;
  try {
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()),fExpectedResult);
    CppUnit::Asserter::fail("Tree population didn't catch negative sapling height.");
  }
  catch (modelErr& err) {;}

  /////////////////////////////////
  //Adult
  p_oTree = p_oPop->CreateTree( 4.0, 4.0, 0, clTreePopulation::adult, 5.0 );

  //Reset the diameter
  fExpectedResult = 12.0;
  p_oTree->SetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()),fExpectedResult);
  p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()),&fActualResult);
  CPPUNIT_ASSERT( fabs( fActualResult - fExpectedResult ) < 0.0001 );

  //Reset the height
  fExpectedResult = 13.0;
  p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()),fExpectedResult);
  p_oTree->GetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()),&fActualResult);
  CPPUNIT_ASSERT( fabs( fActualResult - fExpectedResult ) < 0.0001 );

  //Error processing - no negative diameter
  fExpectedResult = -3.0;
  try {
    p_oTree->SetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()),fExpectedResult);
    CppUnit::Asserter::fail("Tree population didn't catch negative adult DBH.");
  }
  catch (modelErr& err) {;}

  //Error processing - no negative heights
  fExpectedResult = -3.0;
  try {
    p_oTree->SetValue(p_oPop->GetHeightCode(p_oTree->GetSpecies(), p_oTree->GetType()),fExpectedResult);
    CppUnit::Asserter::fail("Tree population didn't catch negative adult height.");
  }
  catch (modelErr& err) {;}

}

/////////////////////////////////////////////////////////////////////////////
//  TestGetters()
/////////////////////////////////////////////////////////////////////////////
void clTestTreePopulation::TestGetters( clSimManager * p_oSimManager )
{
  clTreePopulation * p_oPop;
  char cActualResult[17];
  float fExpectedResult, fActualResult;
  int iExpectedResult, iActualResult;
  short int iSpecies;

  p_oSimManager->ReadFile( WriteXMLFile1() );
  p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

  //***********************************************************
  //Test GetNumberOfSpecies
  //***********************************************************
  iExpectedResult = 3;
  iActualResult = p_oPop->GetNumberOfSpecies();
  CPPUNIT_ASSERT( iActualResult == iExpectedResult );

  //***********************************************************
  //Test GetGridCellSize
  //***********************************************************
  iExpectedResult = 8;
  iActualResult = p_oPop->GetGridCellSize();
  CPPUNIT_ASSERT( iActualResult == iExpectedResult );

  //***********************************************************
  //Test GetNumXCells
  //***********************************************************
  iExpectedResult = 20;
  iActualResult = p_oPop->GetNumXCells();
  CPPUNIT_ASSERT( iActualResult == iExpectedResult );

  //***********************************************************
  //Test GetNumYCells
  //***********************************************************
  iExpectedResult = 25;
  iActualResult = p_oPop->GetNumYCells();
  CPPUNIT_ASSERT( iActualResult == iExpectedResult );

  //***********************************************************
  //Test GetName
  //***********************************************************
  strcpy( cActualResult, p_oPop->GetName() );
  CPPUNIT_ASSERT( strcmp( cActualResult, "treepopulation" ) == 0 );

  //***********************************************************
  //Test TranslateSpeciesNameToCode
  //***********************************************************
  iExpectedResult = 0;
  iActualResult = p_oPop->TranslateSpeciesNameToCode( "Species_1" );
  CPPUNIT_ASSERT( iActualResult == iExpectedResult );

  iExpectedResult = 1;
  iActualResult = p_oPop->TranslateSpeciesNameToCode( "Species_2" );
  CPPUNIT_ASSERT( iActualResult == iExpectedResult );

  iExpectedResult = 2;
  iActualResult = p_oPop->TranslateSpeciesNameToCode( "Species_3" );
  CPPUNIT_ASSERT( iActualResult == iExpectedResult );

  //***********************************************************
  //Test TranslateSpeciesCodeToName
  //***********************************************************
  iSpecies = 0;
  strcpy( cActualResult, p_oPop->TranslateSpeciesCodeToName( iSpecies ) );
  CPPUNIT_ASSERT( strcmp( cActualResult, "Species_1" ) == 0 );

  iSpecies = 1;
  strcpy( cActualResult, p_oPop->TranslateSpeciesCodeToName( iSpecies ) );
  CPPUNIT_ASSERT( strcmp( cActualResult, "Species_2" ) == 0 );

  iSpecies = 2;
  strcpy( cActualResult, p_oPop->TranslateSpeciesCodeToName( iSpecies ) );
  CPPUNIT_ASSERT( strcmp( cActualResult, "Species_3" ) == 0 );


  //***********************************************************
  //Test max sapling height and minimum adult height
  //***********************************************************
  fExpectedResult = 9.528708288;
  fActualResult = p_oPop->m_fMinAdultHeight;
  CPPUNIT_ASSERT( fabs( fActualResult - fExpectedResult ) < 0.0001 );

  fExpectedResult = 11.53255141917;
  fActualResult = p_oPop->m_fMaxSaplingHeight;
  CPPUNIT_ASSERT( fabs( fActualResult - fExpectedResult ) < 0.0001 );

}

/////////////////////////////////////////////////////////////////////////////
//  TestHashTable()
/////////////////////////////////////////////////////////////////////////////
void clTestTreePopulation::TestHashTable( clSimManager * p_oSimManager )
{
  clPopulationBase * p_oTemp;
  clTreePopulation * p_oPop;
  clTree * * p_oTreeSet, /** <The list of trees to work with */
  * * * * p_oShortestHD, /** <Tallest links in fake hash table */
  * * * * p_oTallestHD;
  /** <Shortest links in fake hash table */
  clFakeLinkedList * * * p_oShort, /** <For checking previous/next links */
  * * * p_oTall,
  * p_oRec, * p_oNextRec, * p_oPrevRec;
  /** <For checking previous/next links */
  int iNumXCells, iNumYCells, iNumTrees, i, j, k;

  p_oSimManager->ReadFile( WriteXMLFile1() );
  p_oTemp = p_oSimManager->GetPopulationObject( "treepopulation" );
  p_oPop = ( clTreePopulation * ) p_oTemp;

  //********************************************************************
  //  Load a set of trees one at a time and make sure that each lands in the
  //  correct place in the hash table.  Then, update a bunch of trees so that
  //  they move around in the hash table, and check them each as they are
  //  updated.  Then, delete the trees one at a time to make sure the hash
  //  table is updated correctly.
  //********************************************************************

  //Verify the number of X and Y cells
  iNumXCells = p_oPop->GetNumXCells();
  iNumYCells = p_oPop->GetNumYCells();
  CPPUNIT_ASSERT( iNumXCells == 20 );
  CPPUNIT_ASSERT( iNumYCells == 25 );

  //Allocate the hash tables and linked lists
  iNumTrees = 77;
  p_oTreeSet = new clTree * [iNumTrees];
  p_oShortestHD = new clTree * * * [iNumXCells];
  p_oTallestHD = new clTree * * * [iNumXCells];
  p_oShort = new clFakeLinkedList * * [iNumXCells];
  p_oTall = new clFakeLinkedList * * [iNumXCells];
  for ( i = 0; i < iNumXCells; i++ )
  {
    p_oShortestHD[i] = new clTree * * [iNumYCells];
    p_oTallestHD[i] = new clTree * * [iNumYCells];
    p_oShort[i] = new clFakeLinkedList * [iNumYCells];
    p_oTall[i] = new clFakeLinkedList * [iNumYCells];
    for ( j = 0; j < iNumYCells; j++ )
    {
      p_oShortestHD[i] [j] = new clTree * [11]; //height divs
      p_oTallestHD[i] [j] = new clTree * [11];
      p_oShort[i] [j] = NULL;
      p_oTall[i] [j] = NULL;
      for ( k = 0; k < 11; k++ )
      {
        p_oShortestHD[i] [j] [k] = NULL;
        p_oTallestHD[i] [j] [k] = NULL;
      }
    }
  }

  LoadTrees1( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, p_oTreeSet, iNumXCells, iNumYCells, true, true );
  UpdateHashTableTrees( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, p_oTreeSet, iNumXCells, iNumYCells, true, true, true );
  DeleteHashTableTrees( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, p_oTreeSet, iNumXCells, iNumYCells);

  //Free memory for the next round
  EmptyFakeHashTable( p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
  for (i = 0; i < iNumXCells; i++) {
    for (j = 0; j < iNumYCells; j++) {
      p_oRec = p_oShort[i][j];
      while (p_oRec) {
        p_oNextRec = p_oRec->nextLink;
        delete p_oRec;
        p_oRec = p_oNextRec;
      }
      delete[] p_oShortestHD[i][j];
      delete[] p_oTallestHD[i][j];
    }
    delete[] p_oShortestHD[i];
    delete[] p_oTallestHD[i];
    delete[] p_oShort[i];
    delete[] p_oTall[i];
  }
  delete[] p_oShortestHD;
  delete[] p_oTallestHD;
  delete[] p_oShort;
  delete[] p_oTall;
  delete[] p_oTreeSet; p_oTreeSet = NULL;

  //********************************************************************
  //  Load a set of trees one at a time and make sure that each lands in the
  //  correct place in the hash table.  This time, make it so that the plot
  //  lengths are not even multiples of 8.
  //********************************************************************
  p_oSimManager->ReadFile( WriteXMLFile2() );
  p_oTemp = p_oSimManager->GetPopulationObject( "treepopulation" );
  p_oPop = ( clTreePopulation * ) p_oTemp;

  iNumTrees = 80;
  iNumXCells = p_oPop->GetNumXCells();
  iNumYCells = p_oPop->GetNumYCells();
  CPPUNIT_ASSERT( iNumXCells == 21 );
  CPPUNIT_ASSERT( iNumYCells == 26 );
  p_oTreeSet = new clTree * [iNumTrees];
  p_oShortestHD = new clTree * * * [iNumXCells];
  p_oTallestHD = new clTree * * * [iNumXCells];
  p_oShort = new clFakeLinkedList * * [iNumXCells];
  p_oTall = new clFakeLinkedList * * [iNumXCells];
  for ( i = 0; i < iNumXCells; i++ )
  {
    p_oShortestHD[i] = new clTree * * [iNumYCells];
    p_oTallestHD[i] = new clTree * * [iNumYCells];
    p_oShort[i] = new clFakeLinkedList * [iNumYCells];
    p_oTall[i] = new clFakeLinkedList * [iNumYCells];
    for ( j = 0; j < iNumYCells; j++ )
    {
      p_oShortestHD[i] [j] = new clTree * [11]; //height divs
      p_oTallestHD[i] [j] = new clTree * [11];
      p_oShort[i] [j] = NULL;
      p_oTall[i] [j] = NULL;
      for ( k = 0; k < 11; k++ )
      {
        p_oShortestHD[i] [j] [k] = NULL;
        p_oTallestHD[i] [j] [k] = NULL;
      }
    }
  }

  LoadTrees1( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, p_oTreeSet, iNumXCells, iNumYCells, true, true );
  LoadTrees2( p_oPop, p_oTreeSet, true );

  //********************************************************************
  //  Make sure the hash table empties correctly
  //********************************************************************
  p_oPop->EmptyHashTable();
  p_oPop->EmptyHashTable(); //empty an empty table
  //Sort the empty hash table
  p_oPop->SortHashTable(); //sort an empty table
  EmptyFakeHashTable( p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
  CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  //Free memory for the next round
  for (i = 0; i < iNumXCells; i++) {
    for (j = 0; j < iNumYCells; j++) {
      p_oRec = p_oShort[i][j];
      while (p_oRec) {
        p_oNextRec = p_oRec->nextLink;
        delete p_oRec;
        p_oRec = p_oNextRec;
      }
      delete[] p_oShortestHD[i][j];
      delete[] p_oTallestHD[i][j];
    }
    delete[] p_oShortestHD[i];
    delete[] p_oTallestHD[i];
    delete[] p_oShort[i];
    delete[] p_oTall[i];
  }
  delete[] p_oShortestHD;
  delete[] p_oTallestHD;
  delete[] p_oShort;
  delete[] p_oTall;
  delete[] p_oTreeSet; p_oTreeSet = NULL;
  delete[] p_oTreeSet; p_oTreeSet = NULL;

  //********************************************************************
  //  Load the trees again, then update them without re-sorting the hash table
  //  after each update.  Then sort them all at once at the end to test a more
  //  complex sort job
  //********************************************************************
  //Allocate the hash tables and linked lists
  p_oSimManager->ReadFile( WriteXMLFile1() );
  p_oTemp = p_oSimManager->GetPopulationObject( "treepopulation" );
  p_oPop = ( clTreePopulation * ) p_oTemp;
  iNumXCells = p_oPop->GetNumXCells();
  iNumYCells = p_oPop->GetNumYCells();
  iNumTrees = 77;
  p_oTreeSet = new clTree * [iNumTrees];
  p_oShortestHD = new clTree * * * [iNumXCells];
  p_oTallestHD = new clTree * * * [iNumXCells];
  p_oShort = new clFakeLinkedList * * [iNumXCells];
  p_oTall = new clFakeLinkedList * * [iNumXCells];
  for ( i = 0; i < iNumXCells; i++ )
  {
    p_oShortestHD[i] = new clTree * * [iNumYCells];
    p_oTallestHD[i] = new clTree * * [iNumYCells];
    p_oShort[i] = new clFakeLinkedList * [iNumYCells];
    p_oTall[i] = new clFakeLinkedList * [iNumYCells];
    for ( j = 0; j < iNumYCells; j++ )
    {
      p_oShortestHD[i] [j] = new clTree * [11]; //height divs
      p_oTallestHD[i] [j] = new clTree * [11];
      p_oShort[i] [j] = NULL;
      p_oTall[i] [j] = NULL;
      for ( k = 0; k < 11; k++ )
      {
        p_oShortestHD[i] [j] [k] = NULL;
        p_oTallestHD[i] [j] [k] = NULL;
      }
    }
  }
  LoadTrees1( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, p_oTreeSet, iNumXCells, iNumYCells, false, true );
  UpdateHashTableTrees( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, p_oTreeSet, iNumXCells, iNumYCells, false, false, true );
  //p_oPop->SortHashTable();
  p_oPop->DoDataUpdates();
  //Quick change to the fake hash tables to reflect the fact that all-at-
  //once sorting produces different results from one-at-a-time updating
  //when two trees are the same height - this prevents us from getting a
  //log error
  //Get the rec for tree 6 and swap with its next
  p_oRec = p_oTall[14] [7];
  while ( p_oRec )
  {
    if ( p_oRec->thisTree == p_oTreeSet[5] ) break;
    else
      p_oRec = p_oRec->prevLink;
  }
  p_oNextRec = p_oRec->nextLink;
  p_oPrevRec = p_oRec->prevLink;
  p_oNextRec->nextLink->prevLink = p_oRec; p_oNextRec->nextLink->prev = p_oRec->thisTree;
  p_oRec->nextLink = p_oNextRec->nextLink; p_oRec->next = p_oNextRec->next;
  p_oRec->prevLink = p_oNextRec; p_oRec->prev = p_oNextRec->thisTree;
  p_oNextRec->nextLink = p_oRec; p_oNextRec->next = p_oRec->thisTree;
  p_oNextRec->prevLink = p_oPrevRec; p_oNextRec->prev = p_oPrevRec->thisTree;
  p_oPrevRec->nextLink = p_oNextRec; p_oPrevRec->next = p_oNextRec->thisTree;
  p_oShortestHD[14] [7] [5] = p_oTreeSet[1];
  CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  p_oPop->SortHashTable(); //sort a sorted table
  CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );


  EmptyFakeHashTable( p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
  for (i = 0; i < iNumXCells; i++) {
    for (j = 0; j < iNumYCells; j++) {
      p_oRec = p_oShort[i][j];
      while (p_oRec) {
        p_oNextRec = p_oRec->nextLink;
        delete p_oRec;
        p_oRec = p_oNextRec;
      }
      delete[] p_oShortestHD[i][j];
      delete[] p_oTallestHD[i][j];
    }
    delete[] p_oShortestHD[i];
    delete[] p_oTallestHD[i];
    delete[] p_oShort[i];
    delete[] p_oTall[i];
  }
  delete[] p_oShortestHD;
  delete[] p_oTallestHD;
  delete[] p_oShort;
  delete[] p_oTall;
  delete[] p_oTreeSet; p_oTreeSet = NULL;

  delete[] p_oTreeSet; p_oTreeSet = NULL;

}

/////////////////////////////////////////////////////////////////////////////
//  TestHashTableNoAllomUpdate()
/////////////////////////////////////////////////////////////////////////////
void clTestTreePopulation::TestHashTableNoAllomUpdate( clSimManager * p_oSimManager )
{
  clPopulationBase * p_oTemp;
  clTreePopulation * p_oPop;
  clTree * * p_oTreeSet, /** <The list of trees to work with */
  * * * * p_oShortestHD, /** <Tallest links in fake hash table */
  * * * * p_oTallestHD;
  /** <Shortest links in fake hash table */
  clFakeLinkedList * * * p_oShort, /** <For checking previous/next links */
  * * * p_oTall,
  * p_oRec, * p_oNextRec, * p_oPrevRec;
  /** <For checking previous/next links */
  int iNumXCells, iNumYCells, iNumTrees, i, j, k;

  p_oSimManager->ReadFile( WriteXMLFile1() );
  p_oTemp = p_oSimManager->GetPopulationObject( "treepopulation" );
  p_oPop = ( clTreePopulation * ) p_oTemp;

  //********************************************************************
  //  Load a set of trees one at a time and make sure that each lands in the
  //  correct place in the hash table.  Then, update a bunch of trees so that
  //  they move around in the hash table, and check them each as they are
  //  updated.  Then, delete the trees one at a time to make sure the hash
  //  table is updated correctly.
  //********************************************************************

  //Verify the number of X and Y cells
  iNumXCells = p_oPop->GetNumXCells();
  iNumYCells = p_oPop->GetNumYCells();
  CPPUNIT_ASSERT( iNumXCells == 20 );
  CPPUNIT_ASSERT( iNumYCells == 25 );

  //Allocate the hash tables and linked lists
  iNumTrees = 77;
  p_oTreeSet = new clTree * [iNumTrees];
  p_oShortestHD = new clTree * * * [iNumXCells];
  p_oTallestHD = new clTree * * * [iNumXCells];
  p_oShort = new clFakeLinkedList * * [iNumXCells];
  p_oTall = new clFakeLinkedList * * [iNumXCells];
  for ( i = 0; i < iNumXCells; i++ )
  {
    p_oShortestHD[i] = new clTree * * [iNumYCells];
    p_oTallestHD[i] = new clTree * * [iNumYCells];
    p_oShort[i] = new clFakeLinkedList * [iNumYCells];
    p_oTall[i] = new clFakeLinkedList * [iNumYCells];
    for ( j = 0; j < iNumYCells; j++ )
    {
      p_oShortestHD[i] [j] = new clTree * [11]; //height divs
      p_oTallestHD[i] [j] = new clTree * [11];
      p_oShort[i] [j] = NULL;
      p_oTall[i] [j] = NULL;
      for ( k = 0; k < 11; k++ )
      {
        p_oShortestHD[i] [j] [k] = NULL;
        p_oTallestHD[i] [j] [k] = NULL;
      }
    }
  }

  LoadTrees1( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, p_oTreeSet, iNumXCells, iNumYCells, true, true );
  UpdateHashTableTrees( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, p_oTreeSet, iNumXCells, iNumYCells, true, true, false );
  DeleteHashTableTrees( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, p_oTreeSet, iNumXCells, iNumYCells);

  //Free memory for the next round
  EmptyFakeHashTable( p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
  for (i = 0; i < iNumXCells; i++) {
    for (j = 0; j < iNumYCells; j++) {
      p_oRec = p_oShort[i][j];
      while (p_oRec) {
        p_oNextRec = p_oRec->nextLink;
        delete p_oRec;
        p_oRec = p_oNextRec;
      }
      delete[] p_oShortestHD[i][j];
      delete[] p_oTallestHD[i][j];
    }
    delete[] p_oShortestHD[i];
    delete[] p_oTallestHD[i];
    delete[] p_oShort[i];
    delete[] p_oTall[i];
  }
  delete[] p_oShortestHD;
  delete[] p_oTallestHD;
  delete[] p_oShort;
  delete[] p_oTall;
  delete[] p_oTreeSet; p_oTreeSet = NULL;

  //********************************************************************
  //  Load a set of trees one at a time and make sure that each lands in the
  //  correct place in the hash table.  This time, make it so that the plot
  //  lengths are not even multiples of 8.
  //********************************************************************
  p_oSimManager->ReadFile( WriteXMLFile2() );
  p_oTemp = p_oSimManager->GetPopulationObject( "treepopulation" );
  p_oPop = ( clTreePopulation * ) p_oTemp;

  iNumTrees = 80;
  iNumXCells = p_oPop->GetNumXCells();
  iNumYCells = p_oPop->GetNumYCells();
  CPPUNIT_ASSERT( iNumXCells == 21 );
  CPPUNIT_ASSERT( iNumYCells == 26 );
  p_oTreeSet = new clTree * [iNumTrees];
  p_oShortestHD = new clTree * * * [iNumXCells];
  p_oTallestHD = new clTree * * * [iNumXCells];
  p_oShort = new clFakeLinkedList * * [iNumXCells];
  p_oTall = new clFakeLinkedList * * [iNumXCells];
  for ( i = 0; i < iNumXCells; i++ )
  {
    p_oShortestHD[i] = new clTree * * [iNumYCells];
    p_oTallestHD[i] = new clTree * * [iNumYCells];
    p_oShort[i] = new clFakeLinkedList * [iNumYCells];
    p_oTall[i] = new clFakeLinkedList * [iNumYCells];
    for ( j = 0; j < iNumYCells; j++ )
    {
      p_oShortestHD[i] [j] = new clTree * [11]; //height divs
      p_oTallestHD[i] [j] = new clTree * [11];
      p_oShort[i] [j] = NULL;
      p_oTall[i] [j] = NULL;
      for ( k = 0; k < 11; k++ )
      {
        p_oShortestHD[i] [j] [k] = NULL;
        p_oTallestHD[i] [j] [k] = NULL;
      }
    }
  }

  LoadTrees1( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, p_oTreeSet, iNumXCells, iNumYCells, true, true );
  LoadTrees2( p_oPop, p_oTreeSet, true );

  //********************************************************************
  //  Make sure the hash table empties correctly
  //********************************************************************
  p_oPop->EmptyHashTable();
  p_oPop->EmptyHashTable(); //empty an empty table
  //Sort the empty hash table
  p_oPop->SortHashTable(); //sort an empty table
  EmptyFakeHashTable( p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
  CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  //Free memory for the next round
  for (i = 0; i < iNumXCells; i++) {
    for (j = 0; j < iNumYCells; j++) {
      p_oRec = p_oShort[i][j];
      while (p_oRec) {
        p_oNextRec = p_oRec->nextLink;
        delete p_oRec;
        p_oRec = p_oNextRec;
      }
      delete[] p_oShortestHD[i][j];
      delete[] p_oTallestHD[i][j];
    }
    delete[] p_oShortestHD[i];
    delete[] p_oTallestHD[i];
    delete[] p_oShort[i];
    delete[] p_oTall[i];
  }
  delete[] p_oShortestHD;
  delete[] p_oTallestHD;
  delete[] p_oShort;
  delete[] p_oTall;
  delete[] p_oTreeSet; p_oTreeSet = NULL;
  delete[] p_oTreeSet; p_oTreeSet = NULL;

  //********************************************************************
  //  Load the trees again, then update them without re-sorting the hash table
  //  after each update.  Then sort them all at once at the end to test a more
  //  complex sort job
  //********************************************************************
  //Allocate the hash tables and linked lists
  p_oSimManager->ReadFile( WriteXMLFile1() );
  p_oTemp = p_oSimManager->GetPopulationObject( "treepopulation" );
  p_oPop = ( clTreePopulation * ) p_oTemp;
  iNumXCells = p_oPop->GetNumXCells();
  iNumYCells = p_oPop->GetNumYCells();
  iNumTrees = 77;
  p_oTreeSet = new clTree * [iNumTrees];
  p_oShortestHD = new clTree * * * [iNumXCells];
  p_oTallestHD = new clTree * * * [iNumXCells];
  p_oShort = new clFakeLinkedList * * [iNumXCells];
  p_oTall = new clFakeLinkedList * * [iNumXCells];
  for ( i = 0; i < iNumXCells; i++ )
  {
    p_oShortestHD[i] = new clTree * * [iNumYCells];
    p_oTallestHD[i] = new clTree * * [iNumYCells];
    p_oShort[i] = new clFakeLinkedList * [iNumYCells];
    p_oTall[i] = new clFakeLinkedList * [iNumYCells];
    for ( j = 0; j < iNumYCells; j++ )
    {
      p_oShortestHD[i] [j] = new clTree * [11]; //height divs
      p_oTallestHD[i] [j] = new clTree * [11];
      p_oShort[i] [j] = NULL;
      p_oTall[i] [j] = NULL;
      for ( k = 0; k < 11; k++ )
      {
        p_oShortestHD[i] [j] [k] = NULL;
        p_oTallestHD[i] [j] [k] = NULL;
      }
    }
  }
  LoadTrees1( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, p_oTreeSet, iNumXCells, iNumYCells, false, true );
  UpdateHashTableTrees( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, p_oTreeSet, iNumXCells, iNumYCells, false, false, false );
  //p_oPop->SortHashTable();
  p_oPop->DoDataUpdates();
  //Quick change to the fake hash tables to reflect the fact that all-at-
  //once sorting produces different results from one-at-a-time updating
  //when two trees are the same height - this prevents us from getting a
  //log error
  //Get the rec for tree 6 and swap with its next
  p_oRec = p_oTall[14] [7];
  while ( p_oRec )
  {
    if ( p_oRec->thisTree == p_oTreeSet[5] ) break;
    else
      p_oRec = p_oRec->prevLink;
  }
  p_oNextRec = p_oRec->nextLink;
  p_oPrevRec = p_oRec->prevLink;
  p_oNextRec->nextLink->prevLink = p_oRec; p_oNextRec->nextLink->prev = p_oRec->thisTree;
  p_oRec->nextLink = p_oNextRec->nextLink; p_oRec->next = p_oNextRec->next;
  p_oRec->prevLink = p_oNextRec; p_oRec->prev = p_oNextRec->thisTree;
  p_oNextRec->nextLink = p_oRec; p_oNextRec->next = p_oRec->thisTree;
  p_oNextRec->prevLink = p_oPrevRec; p_oNextRec->prev = p_oPrevRec->thisTree;
  p_oPrevRec->nextLink = p_oNextRec; p_oPrevRec->next = p_oNextRec->thisTree;
  p_oShortestHD[14] [7] [5] = p_oTreeSet[1];
  CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  p_oPop->SortHashTable(); //sort a sorted table
  CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );


  EmptyFakeHashTable( p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
  for (i = 0; i < iNumXCells; i++) {
    for (j = 0; j < iNumYCells; j++) {
      p_oRec = p_oShort[i][j];
      while (p_oRec) {
        p_oNextRec = p_oRec->nextLink;
        delete p_oRec;
        p_oRec = p_oNextRec;
      }
      delete[] p_oShortestHD[i][j];
      delete[] p_oTallestHD[i][j];
    }
    delete[] p_oShortestHD[i];
    delete[] p_oTallestHD[i];
    delete[] p_oShort[i];
    delete[] p_oTall[i];
  }
  delete[] p_oShortestHD;
  delete[] p_oTallestHD;
  delete[] p_oShort;
  delete[] p_oTall;
  delete[] p_oTreeSet; p_oTreeSet = NULL;

  delete[] p_oTreeSet; p_oTreeSet = NULL;

}

//////////////////////////////////////////////////////////////////////////////
// DeleteHashTableTrees()
//////////////////////////////////////////////////////////////////////////////
void clTestTreePopulation::DeleteHashTableTrees(clTreePopulation * p_oPop, clTree * * * * p_oShortestHD,
clTree * * * * p_oTallestHD, clFakeLinkedList * * * p_oShort, clFakeLinkedList * * * p_oTall, clTree * * p_oTreeSet,
int iNumXCells, int iNumYCells) {
  clFakeLinkedList *p_oRec, *p_oNextRec, *p_oHolderRec;
  short int i, j, k; //loop counters
  deadCode iDeadReason = natural;

  //****************************************
  //Delete tree 38
  //****************************************
  //Delete the tree and NULL out the record
  p_oPop->KillTree(p_oTreeSet[37], iDeadReason); p_oTreeSet[37] = NULL;
  delete p_oShort[19][24];
  p_oShort[19][24] = NULL;
  p_oTall[19][24] = NULL;
  p_oShortestHD[19][24][0] = NULL;
  p_oTallestHD[19][24][0] = NULL;
  CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  //****************************************
  //Delete tree 37
  //****************************************
  //Get the rec for this tree
  p_oRec = p_oTall[0][0];
  //Delete the record
  delete p_oRec;
  p_oPop->KillTree(p_oTreeSet[36], iDeadReason); p_oTreeSet[36] = NULL;
  p_oShort[0][0] = NULL;
  p_oTall[0][0] = NULL;
  p_oShortestHD[0][0][9] = NULL;
  p_oTallestHD[0][0][9] = NULL;
  CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  //****************************************
  //Delete tree 1
  //****************************************
  //Get the rec for this tree
  p_oRec = p_oTall[3][5];
  //Delete the record
  delete p_oRec;
  p_oPop->KillTree(p_oTreeSet[0], iDeadReason); p_oTreeSet[0] = NULL;
  p_oShort[3][5] = NULL;
  p_oTall[3][5] = NULL;
  p_oShortestHD[3][5][3] = NULL;
  p_oTallestHD[3][5][3] = NULL;
  CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  //****************************************
  //Delete tree 17
  //****************************************
  //Get the rec for this tree
  p_oRec = p_oShort[15][8];
  p_oRec->nextLink->prevLink = NULL; p_oRec->nextLink->prev = NULL;
  //Delete the record
  delete p_oRec;
  p_oPop->KillTree(p_oTreeSet[16], iDeadReason); p_oTreeSet[16] = NULL;
  p_oShort[15][8] = p_oTall[15][8];
  p_oShortestHD[15][8][0] = NULL;
  p_oTallestHD[15][8][0] = NULL;
  CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  //****************************************
  //Delete tree 14
  //****************************************
  //Get the rec for this tree
  p_oRec = p_oTall[14][7];
  while (p_oRec) {
    if (p_oRec->thisTree == p_oTreeSet[13]) break;
    else p_oRec = p_oRec->prevLink;
  }
  //Close the gap
  p_oNextRec = p_oRec->nextLink;
  p_oRec->prevLink->nextLink = p_oNextRec; p_oRec->prevLink->next = p_oNextRec->thisTree;
  p_oNextRec->prevLink = p_oRec->prevLink; p_oNextRec->prev = p_oRec->prev;
  //Delete the record
  delete p_oRec;
  p_oPop->KillTree(p_oTreeSet[13], iDeadReason); p_oTreeSet[13] = NULL;
  p_oShortestHD[14][7][3] = NULL;
  p_oTallestHD[14][7][3] = NULL;
  CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  //****************************************
  //Delete tree 33
  //****************************************
  //Get the rec for this tree
  p_oRec = p_oTall[5][20];
  //Close the gap
  p_oRec->prevLink->nextLink = NULL; p_oRec->prevLink->next = NULL;
  p_oTall[5][20] = p_oRec->prevLink;
  //Delete the record
  delete p_oRec;
  p_oPop->KillTree(p_oTreeSet[32], iDeadReason); p_oTreeSet[32] = NULL;
  p_oShortestHD[5][20][9] = NULL;
  p_oTallestHD[5][20][9] = NULL;
  CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  //****************************************
  //Delete tree 44
  //****************************************
  //Get the rec for this tree
  p_oRec = p_oShort[2][0];
  //Close the gap
  p_oRec->nextLink->prevLink = NULL; p_oRec->nextLink->prev = NULL;
  p_oRec = p_oRec->nextLink;
  delete p_oShort[2][0];
  p_oShort[2][0] = p_oRec;
  p_oPop->KillTree(p_oTreeSet[43], iDeadReason); p_oTreeSet[43] = NULL;
  p_oShortestHD[2][0][0] = p_oTreeSet[42];
  CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  //****************************************
  //Delete tree 60
  //****************************************
  //Get the rec for this tree
  p_oRec = p_oTall[2][0];
  while (p_oRec) {
    if (p_oRec->thisTree == p_oTreeSet[59]) break;
    else p_oRec = p_oRec->prevLink;
  }
  //Close the gap
  p_oNextRec = p_oRec->nextLink;
  p_oRec->prevLink->nextLink = p_oNextRec; p_oRec->prevLink->next = p_oNextRec->thisTree;
  p_oNextRec->prevLink = p_oRec->prevLink; p_oNextRec->prev = p_oRec->prev;
  //Delete the record
  delete p_oRec;
  p_oPop->KillTree(p_oTreeSet[59], iDeadReason); p_oTreeSet[59] = NULL;
  p_oShortestHD[2][0][5] = p_oTreeSet[53];
  CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  //****************************************
  //Delete tree 76
  //****************************************
  //Get the rec for this tree
  p_oRec = p_oTall[2][0];
  while (p_oRec) {
    if (p_oRec->thisTree == p_oTreeSet[75]) break;
    else p_oRec = p_oRec->prevLink;
  }
  //Close the gap
  p_oNextRec = p_oRec->nextLink;
  p_oRec->prevLink->nextLink = p_oNextRec; p_oRec->prevLink->next = p_oNextRec->thisTree;
  p_oNextRec->prevLink = p_oRec->prevLink; p_oNextRec->prev = p_oRec->prev;
  //Delete the record
  delete p_oRec;
  p_oPop->KillTree(p_oTreeSet[75], iDeadReason); p_oTreeSet[75] = NULL;
  p_oShortestHD[2][0][9] = p_oTreeSet[76];
  CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  //****************************************
  //Delete tree 74
  //****************************************
  //Get the rec for this tree
  p_oRec = p_oTall[2][0];
  //Close the gap
  p_oRec->prevLink->nextLink = NULL; p_oRec->prevLink->next = NULL;
  p_oTall[2][0] = p_oRec->prevLink;
  //Delete the record
  delete p_oRec;
  p_oPop->KillTree(p_oTreeSet[73], iDeadReason); p_oTreeSet[73] = NULL;
  p_oTallestHD[2][0][9] = p_oTreeSet[76];
  CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  //****************************************
  //Delete tree 62
  //****************************************
  //Get the rec for this tree
  p_oRec = p_oTall[2][0];
  while (p_oRec) {
    if (p_oRec->thisTree == p_oTreeSet[61]) break;
    else p_oRec = p_oRec->prevLink;
  }
  //Close the gap
  p_oNextRec = p_oRec->nextLink;
  p_oRec->prevLink->nextLink = p_oNextRec; p_oRec->prevLink->next = p_oNextRec->thisTree;
  p_oNextRec->prevLink = p_oRec->prevLink; p_oNextRec->prev = p_oRec->prev;
  //Delete the record
  delete p_oRec;
  p_oPop->KillTree(p_oTreeSet[61], iDeadReason); p_oTreeSet[61] = NULL;
  p_oTallestHD[2][0][5] = p_oTreeSet[60];
  CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  //****************************************
  //Delete tree 45
  //****************************************
  //Get the rec for this tree
  p_oRec = p_oShort[2][0];
  while (p_oRec) {
    if (p_oRec->thisTree == p_oTreeSet[44]) break;
    else p_oRec = p_oRec->nextLink;
  }
  //Close the gap
  p_oNextRec = p_oRec->nextLink;
  p_oRec->prevLink->nextLink = p_oNextRec; p_oRec->prevLink->next = p_oNextRec->thisTree;
  p_oNextRec->prevLink = p_oRec->prevLink; p_oNextRec->prev = p_oRec->prev;
  //Delete the record
  delete p_oRec;
  p_oPop->KillTree(p_oTreeSet[44], iDeadReason); p_oTreeSet[44] = NULL;
  p_oTallestHD[2][0][0] = p_oTreeSet[42];
  CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  //****************************************
  //Delete tree 30
  //****************************************
  //Get the rec for this tree
  p_oRec = p_oShort[5][20];
  //Close the gap
  p_oRec->nextLink->prevLink = NULL; p_oRec->nextLink->prev = NULL;
  p_oShort[5][20] = p_oRec->nextLink;
  //Delete the record
  delete p_oRec;
  p_oPop->KillTree(p_oTreeSet[29], iDeadReason); p_oTreeSet[29] = NULL;
  p_oShortestHD[5][20][3] = p_oTallestHD[5][20][3];
  CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  //****************************************
  //Delete tree 29
  //****************************************
  //Get the rec for this tree
  p_oRec = p_oShort[5][20];
  while (p_oRec) {
    if (p_oRec->thisTree == p_oTreeSet[28]) break;
    else p_oRec = p_oRec->nextLink;
  }
  //Close the gap
  p_oNextRec = p_oRec->nextLink;
  p_oRec->prevLink->nextLink = p_oNextRec; p_oRec->prevLink->next = p_oNextRec->thisTree;
  p_oNextRec->prevLink = p_oRec->prevLink; p_oNextRec->prev = p_oRec->prev;
  //Delete the record
  delete p_oRec;
  p_oPop->KillTree(p_oTreeSet[28], iDeadReason); p_oTreeSet[28] = NULL;
  p_oShortestHD[5][20][5] = p_oTallestHD[5][20][5];
  CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  //****************************************
  //Delete tree 32
  //****************************************
  //Get the rec for this tree
  p_oRec = p_oTall[5][20];
  //Close the gap
  p_oRec->prevLink->nextLink = NULL; p_oRec->prevLink->next = NULL;
  p_oTall[5][20] = p_oRec->prevLink;
  //Delete the record
  delete p_oRec;
  p_oPop->KillTree(p_oTreeSet[31], iDeadReason); p_oTreeSet[31] = NULL;
  p_oTallestHD[5][20][8] = p_oShortestHD[5][20][8];
  CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  //****************************************
  //Delete tree 28
  //****************************************
  //Get the rec for this tree
  p_oRec = p_oTall[5][20];
  while (p_oRec) {
    if (p_oRec->thisTree == p_oTreeSet[27]) break;
    else p_oRec = p_oRec->prevLink;
  }
  //Close the gap
  p_oNextRec = p_oRec->nextLink;
  p_oRec->prevLink->nextLink = p_oNextRec; p_oRec->prevLink->next = p_oNextRec->thisTree;
  p_oNextRec->prevLink = p_oRec->prevLink; p_oNextRec->prev = p_oRec->prev;
  //Delete the record
  delete p_oRec;
  p_oPop->KillTree(p_oTreeSet[27], iDeadReason); p_oTreeSet[27] = NULL;
  p_oTallestHD[5][20][6] = p_oShortestHD[5][20][6];
  CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  //****************************************
  //Delete tree 50
  //****************************************
  //Get the rec for this tree
  p_oRec = p_oTall[2][0];
  while (p_oRec) {
    if (p_oRec->thisTree == p_oTreeSet[49]) break;
    else p_oRec = p_oRec->prevLink;
  }
  //Close the gap
  p_oNextRec = p_oRec->nextLink;
  p_oRec->prevLink->nextLink = p_oNextRec; p_oRec->prevLink->next = p_oNextRec->thisTree;
  p_oNextRec->prevLink = p_oRec->prevLink; p_oNextRec->prev = p_oRec->prev;
  //Delete the record
  delete p_oRec;
  p_oPop->KillTree(p_oTreeSet[49], iDeadReason); p_oTreeSet[49] = NULL;
  CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  //****************************************
  //Delete rest of the trees except 69
  //****************************************
  //Grab the record for tree 69
  p_oNextRec = p_oTall[2][0];
  while (p_oNextRec) {
    if (p_oNextRec->thisTree == p_oTreeSet[68]) break;
    else p_oNextRec = p_oNextRec->prevLink;
  }
  p_oHolderRec = p_oNextRec;

  for (i = 0; i < 68; i++)
    if (p_oTreeSet[i] != NULL)
      p_oPop->KillTree(p_oTreeSet[i], iDeadReason);
  for (i = 69; i < 77; i++)
    if (p_oTreeSet[i] != NULL)
      p_oPop->KillTree(p_oTreeSet[i], iDeadReason);

  //Update the links
  for (i = 0; i < 2; i++)
    for (j = 0; j < iNumYCells; j++) {
      p_oRec = p_oShort[i][j];
      while (p_oRec) {
        p_oNextRec = p_oRec->nextLink;
        delete p_oRec;
        p_oRec = p_oNextRec;
      }
      p_oShort[i][j] = NULL;
      p_oTall[i][j] = NULL;
      for (k = 0; k < 11; k++) {
        p_oShortestHD[i][j][k] = NULL;
        p_oTallestHD[i][j][k] = NULL;
      }
    }
  for (j = 1; j < iNumYCells; j++) {
    p_oRec = p_oShort[2][j];
    while (p_oRec) {
      p_oNextRec = p_oRec->nextLink;
      delete p_oRec;
      p_oRec = p_oNextRec;
    }
    p_oShort[2][j] = NULL;
    p_oTall[2][j] = NULL;
    for (k = 0; k < 11; k++) {
      p_oShortestHD[2][j][k] = NULL;
      p_oTallestHD[2][j][k] = NULL;
    }
  }
  for (i = 3; i < iNumXCells; i++)
    for (j = 0; j < iNumYCells; j++) {
      p_oRec = p_oShort[i][j];
      while (p_oRec) {
        p_oNextRec = p_oRec->nextLink;
        delete p_oRec;
        p_oRec = p_oNextRec;
      }
      p_oShort[i][j] = NULL;
      p_oTall[i][j] = NULL;
      for (k = 0; k < 11; k++) {
        p_oShortestHD[i][j][k] = NULL;
        p_oTallestHD[i][j][k] = NULL;
      }
    }
  p_oRec = p_oShort[2][0];
  while (p_oRec) {
    p_oNextRec = p_oRec->nextLink;
    if (p_oRec != p_oHolderRec)
      delete p_oRec;
    p_oRec = p_oNextRec;
  }
  for (k = 0; k < 11; k++) {
        p_oShortestHD[2][0][k] = NULL;
        p_oTallestHD[2][0][k] = NULL;
  }
  p_oShort[2][0] = p_oHolderRec;
  p_oTall[2][0] = p_oHolderRec;
  p_oHolderRec->nextLink = NULL; p_oHolderRec->next = NULL;
  p_oHolderRec->prevLink = NULL; p_oHolderRec->prev = NULL;
  p_oShortestHD[2][0][6] = p_oTreeSet[68];
  p_oTallestHD[2][0][6] = p_oTreeSet[68];
  CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  //****************************************
  //Delete tree 69
  //****************************************
  p_oPop->KillTree(p_oTreeSet[68], iDeadReason);
  delete p_oHolderRec;
  p_oShort[2][0] = NULL; p_oTall[2][0] = NULL;
  p_oShortestHD[2][0][6] = NULL; p_oTallestHD[2][0][6] = NULL;
  CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
}
//---------------------------------------------------------------------------


/////////////////////////////////////////////////////////////////////////////
// DoSet1Searches()
/////////////////////////////////////////////////////////////////////////////
void clTestTreePopulation::DoSet1Searches( clTreePopulation * p_oPop, clTree * * p_oTreeSet )
{
  using namespace std;
  short int iNumTrees = 79, //number of trees in this plot
       i; //loop counter
  struct treeResults * p_expected; //expected results list for all trees
  clTreeSearch * p_oResults; //tree search object
  stringstream query; //query string for searches

  p_expected = new struct treeResults[iNumTrees];
  //Load the trees into the results
  for ( i = 0; i < iNumTrees; i++ )
    p_expected[i].p_oTree = p_oTreeSet[i];

  //*******************************************
  //Set up search 0
  //******************************************
  query.str( "" );
  //Do the search
  p_oResults = p_oPop->Find( ( char * ) query.str().c_str() );
  //Special case - this should be NULL
  CPPUNIT_ASSERT( NULL == p_oResults );

  //*******************************************
  //Set up search 1
  //*******************************************
  //Do the search
  query.str( "" );
  query << "all";
  p_oResults = p_oPop->Find( ( char * ) query.str().c_str() );
  //Set up the expected results
  for ( i = 0; i < iNumTrees; i++ )
    p_expected[i].bShouldBe = true;
  //Validate
  CheckTreeSearch( p_expected, iNumTrees, p_oResults, p_oTreeSet[36] );

  //*******************************************
  //Set up search 2
  //*******************************************
  //Do the search
  query.str( "" );
  query << "distance=40 FROM x=16,y=18::height=9.6";
  p_oResults = p_oPop->Find( ( char * ) query.str().c_str() );
  //Set up the expected results
  for ( i = 0; i < iNumTrees; i++ )
    p_expected[i].bShouldBe = false;
  p_expected[0].bShouldBe = true; p_expected[17].bShouldBe = true;
  p_expected[19].bShouldBe = true; p_expected[37].bShouldBe = true;
  p_expected[49].bShouldBe = true; p_expected[50].bShouldBe = true;
  p_expected[51].bShouldBe = true; p_expected[52].bShouldBe = true;
  p_expected[53].bShouldBe = true; p_expected[54].bShouldBe = true;
  p_expected[55].bShouldBe = true; p_expected[56].bShouldBe = true;
  p_expected[57].bShouldBe = true; p_expected[58].bShouldBe = true;
  p_expected[59].bShouldBe = true; p_expected[60].bShouldBe = true;
  p_expected[61].bShouldBe = true; p_expected[62].bShouldBe = true;
  p_expected[63].bShouldBe = true; p_expected[64].bShouldBe = true;
  p_expected[65].bShouldBe = true; p_expected[66].bShouldBe = true;
  p_expected[67].bShouldBe = true; p_expected[68].bShouldBe = true;
  p_expected[69].bShouldBe = true; p_expected[70].bShouldBe = true;
  p_expected[71].bShouldBe = true; p_expected[72].bShouldBe = true;
  p_expected[73].bShouldBe = true; p_expected[74].bShouldBe = true;
  p_expected[75].bShouldBe = true; p_expected[76].bShouldBe = true;
  p_expected[78].bShouldBe = true;
  //Validate
  CheckTreeSearch( p_expected, iNumTrees, p_oResults, p_oTreeSet[37] );

  //*******************************************
  //Set up search 3
  //*******************************************
  //Do the search
  query.str( "" );
  query << "distance=30.0 FROM x=16,y=178::height=11.0942183444878";
  p_oResults = p_oPop->Find( ( char * ) query.str().c_str() );
  //Set up the expected results
  for ( i = 0; i < iNumTrees; i++ )
    p_expected[i].bShouldBe = false;
  p_expected[32].bShouldBe = true; p_expected[34].bShouldBe = true;
  p_expected[49].bShouldBe = true; p_expected[51].bShouldBe = true;
  p_expected[52].bShouldBe = true; p_expected[53].bShouldBe = true;
  p_expected[54].bShouldBe = true; p_expected[55].bShouldBe = true;
  p_expected[56].bShouldBe = true; p_expected[57].bShouldBe = true;
  p_expected[58].bShouldBe = true; p_expected[59].bShouldBe = true;
  p_expected[60].bShouldBe = true; p_expected[61].bShouldBe = true;
  //Validate
  CheckTreeSearch( p_expected, iNumTrees, p_oResults, p_oTreeSet[34] );

  //*******************************************
  //Set up search 4
  //*******************************************
  //Do the search
  query.str( "" );
  query << "distance=30.9061288973902 FROM x=10.0,y=32.0::height=10";
  p_oResults = p_oPop->Find( ( char * ) query.str().c_str() );
  //Set up the expected results
  for ( i = 0; i < iNumTrees; i++ )
    p_expected[i].bShouldBe = false;
  p_expected[0].bShouldBe = true; p_expected[50].bShouldBe = true;
  p_expected[51].bShouldBe = true; p_expected[52].bShouldBe = true;
  p_expected[53].bShouldBe = true; p_expected[54].bShouldBe = true;
  p_expected[55].bShouldBe = true; p_expected[56].bShouldBe = true;
  p_expected[57].bShouldBe = true; p_expected[58].bShouldBe = true;
  p_expected[59].bShouldBe = true; p_expected[60].bShouldBe = true;
  p_expected[61].bShouldBe = true; p_expected[62].bShouldBe = true;
  p_expected[63].bShouldBe = true; p_expected[64].bShouldBe = true;
  p_expected[65].bShouldBe = true; p_expected[66].bShouldBe = true;
  p_expected[67].bShouldBe = true; p_expected[68].bShouldBe = true;
  p_expected[69].bShouldBe = true; p_expected[70].bShouldBe = true;
  p_expected[71].bShouldBe = true; p_expected[72].bShouldBe = true;
  p_expected[73].bShouldBe = true; p_expected[74].bShouldBe = true;
  p_expected[75].bShouldBe = true; p_expected[76].bShouldBe = true;
  //Validate
  CheckTreeSearch( p_expected, iNumTrees, p_oResults, p_oTreeSet[50] );

  //*******************************************
  //Set up search 5
  //*******************************************
  //Do the search
  query.str( "" );
  query << "distance=45.0 FROM x=44.0,y=0.0::height=33.2810957906073";
  p_oResults = p_oPop->Find( ( char * ) query.str().c_str() );
  //Set up the expected results
  for ( i = 0; i < iNumTrees; i++ )
    p_expected[i].bShouldBe = false;
  p_expected[17].bShouldBe = true; p_expected[18].bShouldBe = true;
  p_expected[31].bShouldBe = true; p_expected[32].bShouldBe = true;
  p_expected[70].bShouldBe = true; p_expected[71].bShouldBe = true;
  p_expected[73].bShouldBe = true; p_expected[74].bShouldBe = true;
  p_expected[75].bShouldBe = true; p_expected[76].bShouldBe = true;
  //Validate
  CheckTreeSearch( p_expected, iNumTrees, p_oResults, p_oTreeSet[31] );

  //*******************************************
  //Set up search 6
  //*******************************************
  //Do the search
  query.str( "" );
  query << "distance=0.0 FROM x=96.0,y=25.0::height=10.0";
  p_oResults = p_oPop->Find( ( char * ) query.str().c_str() );
  //Set up the expected results
  for ( i = 0; i < iNumTrees; i++ )
    p_expected[i].bShouldBe = false;
  //Validate
  CheckTreeSearch( p_expected, iNumTrees, p_oResults, NULL );

  //*******************************************
  //Set up search 7
  //*******************************************
  //Do the search
  query.str( "" );
  query << "distance=64.62197769 FROM x=158.0,y=0.0::height=12";
  p_oResults = p_oPop->Find( ( char * ) query.str().c_str() );
  //Set up the expected results
  for ( i = 0; i < iNumTrees; i++ )
    p_expected[i].bShouldBe = false;
  p_expected[0].bShouldBe = true; p_expected[17].bShouldBe = true;
  p_expected[23].bShouldBe = true; p_expected[27].bShouldBe = true;
  p_expected[28].bShouldBe = true; p_expected[29].bShouldBe = true;
  p_expected[30].bShouldBe = true; p_expected[31].bShouldBe = true;
  p_expected[32].bShouldBe = true; p_expected[33].bShouldBe = true;
  p_expected[34].bShouldBe = true; p_expected[35].bShouldBe = true;
  p_expected[52].bShouldBe = true; p_expected[53].bShouldBe = true;
  p_expected[54].bShouldBe = true; p_expected[55].bShouldBe = true;
  p_expected[56].bShouldBe = true; p_expected[57].bShouldBe = true;
  p_expected[58].bShouldBe = true; p_expected[59].bShouldBe = true;
  p_expected[60].bShouldBe = true; p_expected[61].bShouldBe = true;
  p_expected[62].bShouldBe = true; p_expected[63].bShouldBe = true;
  p_expected[64].bShouldBe = true; p_expected[65].bShouldBe = true;
  p_expected[66].bShouldBe = true; p_expected[67].bShouldBe = true;
  p_expected[68].bShouldBe = true; p_expected[69].bShouldBe = true;
  p_expected[70].bShouldBe = true; p_expected[71].bShouldBe = true;
  p_expected[72].bShouldBe = true; p_expected[73].bShouldBe = true;
  p_expected[74].bShouldBe = true; p_expected[75].bShouldBe = true;
  p_expected[76].bShouldBe = true;

  //Validate
  CheckTreeSearch( p_expected, iNumTrees, p_oResults, p_oTreeSet[29] );

  //*******************************************
  //Set up search 8
  //*******************************************
  //Do the search
  query.str( "" );
  query << "distance=40.0 FROM x=23.0,y=45.0::height=45.0";
  p_oResults = p_oPop->Find( ( char * ) query.str().c_str() );
  //Set up the expected results
  for ( i = 0; i < iNumTrees; i++ )
    p_expected[i].bShouldBe = false;
  //Validate
  CheckTreeSearch( p_expected, iNumTrees, p_oResults, NULL );

  //*******************************************
  //Set up search 9
  //*******************************************
  //Do the search
  query.str( "" );
  query << "distance=84.0 FROM x=4.0,y=50.0::height=30";
  p_oResults = p_oPop->Find( ( char * ) query.str().c_str() );
  //Set up the expected results
  for ( i = 0; i < iNumTrees; i++ )
    p_expected[i].bShouldBe = false;
  p_expected[11].bShouldBe = true; p_expected[12].bShouldBe = true;
  p_expected[17].bShouldBe = true; p_expected[18].bShouldBe = true;
  p_expected[24].bShouldBe = true; p_expected[65].bShouldBe = true;
  p_expected[67].bShouldBe = true; p_expected[69].bShouldBe = true;
  p_expected[70].bShouldBe = true; p_expected[71].bShouldBe = true;
  p_expected[72].bShouldBe = true; p_expected[73].bShouldBe = true;
  p_expected[74].bShouldBe = true; p_expected[75].bShouldBe = true;
  p_expected[76].bShouldBe = true;
  //Validate
  CheckTreeSearch( p_expected, iNumTrees, p_oResults, p_oTreeSet[67] );

  //*******************************************
  //Set up search 10
  //*******************************************
  //Do the search
  query.str( "" );
  query << "distance=114.0 FROM x=120.0,y=113.0::height=25";
  p_oResults = p_oPop->Find( ( char * ) query.str().c_str() );
  //Set up the expected results
  for ( i = 0; i < iNumTrees; i++ )
    p_expected[i].bShouldBe = false;
  p_expected[4].bShouldBe = true; p_expected[11].bShouldBe = true;
  p_expected[12].bShouldBe = true; p_expected[17].bShouldBe = true;
  p_expected[18].bShouldBe = true; p_expected[24].bShouldBe = true;
  p_expected[26].bShouldBe = true; p_expected[27].bShouldBe = true;
  p_expected[30].bShouldBe = true; p_expected[31].bShouldBe = true;
  p_expected[32].bShouldBe = true; p_expected[33].bShouldBe = true;
  p_expected[62].bShouldBe = true; p_expected[77].bShouldBe = true;
  //Validate
  CheckTreeSearch( p_expected, iNumTrees, p_oResults, p_oTreeSet[18] );

  //*******************************************
  //Set up search 11
  //*******************************************
  //Do the search
  query.str( "" );
  query << "distance=16.0 FROM x=2.3838,y=2.34985::height=9.0";
  p_oResults = p_oPop->Find( ( char * ) query.str().c_str() );
  //Set up the expected results
  for ( i = 0; i < iNumTrees; i++ )
    p_expected[i].bShouldBe = false;
  p_expected[36].bShouldBe = true; p_expected[37].bShouldBe = true;
  p_expected[48].bShouldBe = true; p_expected[49].bShouldBe = true;
  p_expected[50].bShouldBe = true; p_expected[51].bShouldBe = true;
  p_expected[78].bShouldBe = true;
  //Validate
  CheckTreeSearch( p_expected, iNumTrees, p_oResults, p_oTreeSet[37] );

  //*******************************************
  //Set up search 12
  //*******************************************
  //Do the search
  query.str( "" );
  query << "distance=11.314 FROM x=120.0,y=64.0::height=4.0";
  p_oResults = p_oPop->Find( ( char * ) query.str().c_str() );
  //Set up the expected results
  for ( i = 0; i < iNumTrees; i++ )
    p_expected[i].bShouldBe = false;
  p_expected[4].bShouldBe = true; p_expected[5].bShouldBe = true;
  p_expected[6].bShouldBe = true; p_expected[7].bShouldBe = true;
  p_expected[8].bShouldBe = true; p_expected[9].bShouldBe = true;
  p_expected[10].bShouldBe = true; p_expected[11].bShouldBe = true;
  p_expected[12].bShouldBe = true; p_expected[13].bShouldBe = true;
  p_expected[14].bShouldBe = true; p_expected[15].bShouldBe = true;
  p_expected[38].bShouldBe = true; p_expected[39].bShouldBe = true;
  p_expected[40].bShouldBe = true;
  //Validate
  CheckTreeSearch( p_expected, iNumTrees, p_oResults, p_oTreeSet[13] );

  //*******************************************
  //Set up search 13
  //*******************************************
  //Do the search
  query.str( "" );
  query << "distance=8.0 FROM x=56.0,y=32.0::height=9.0";
  p_oResults = p_oPop->Find( ( char * ) query.str().c_str() );
  //Set up the expected results
  for ( i = 0; i < iNumTrees; i++ )
    p_expected[i].bShouldBe = false;
  p_expected[17].bShouldBe = true; p_expected[18].bShouldBe = true;
  //Validate
  CheckTreeSearch( p_expected, iNumTrees, p_oResults, p_oTreeSet[18] );

  //*******************************************
  //Set up search 14
  //*******************************************
  //Do the search
  query.str( "" );
  query << "distance=16.0 FROM x=56.0,y=16.0::height=10.0";
  p_oResults = p_oPop->Find( ( char * ) query.str().c_str() );
  //Set up the expected results
  for ( i = 0; i < iNumTrees; i++ )
    p_expected[i].bShouldBe = false;
  p_expected[17].bShouldBe = true; p_expected[18].bShouldBe = true;
  //Validate
  CheckTreeSearch( p_expected, iNumTrees, p_oResults, p_oTreeSet[18] );

  //*******************************************
  //Set up search 15
  //*******************************************
  //Do the search
  query.str( "" );
  query << "distance=8.0 FROM x=120.0,y=64.0::height=3.0";
  p_oResults = p_oPop->Find( ( char * ) query.str().c_str() );
  //Set up the expected results
  for ( i = 0; i < iNumTrees; i++ )
    p_expected[i].bShouldBe = false;
  p_expected[5].bShouldBe = true; p_expected[8].bShouldBe = true;
  p_expected[9].bShouldBe = true; p_expected[10].bShouldBe = true;
  p_expected[11].bShouldBe = true; p_expected[12].bShouldBe = true;
  p_expected[13].bShouldBe = true; p_expected[14].bShouldBe = true;
  p_expected[16].bShouldBe = true; p_expected[39].bShouldBe = true;
  p_expected[40].bShouldBe = true;
  //Validate
  CheckTreeSearch( p_expected, iNumTrees, p_oResults, p_oTreeSet[13] );

  //*******************************************
  //Set up search 16
  //*******************************************
  //Do the search
  query.str( "" );
  query << "type=" << clTreePopulation::seed << "::species=0,1,2";
  p_oResults = p_oPop->Find( ( char * ) query.str().c_str() );
  //Check the minimum and maximum height divisions for searching
  CPPUNIT_ASSERT( 0 == p_oResults->m_iStartHeightDiv );
  CPPUNIT_ASSERT( 0 == p_oResults->m_iEndHeightDiv );
  //Set up the expected results
  for ( i = 0; i < iNumTrees; i++ )
    p_expected[i].bShouldBe = false;
  //Validate
  CheckTreeSearch( p_expected, iNumTrees, p_oResults, NULL );

  //*******************************************
  //Set up search 17
  //*******************************************
  //Do the search
  query.str( "" );
  query << "type=" << clTreePopulation::snag << "::species=0,1,2";
  p_oResults = p_oPop->Find( ( char * ) query.str().c_str() );
  //Check the minimum and maximum height divisions for searching
  CPPUNIT_ASSERT( 2 == p_oResults->m_iStartHeightDiv );
  CPPUNIT_ASSERT( 11 == p_oResults->m_iEndHeightDiv );
  //Set up the expected results
  for ( i = 0; i < iNumTrees; i++ )
    p_expected[i].bShouldBe = false;
  //Validate
  CheckTreeSearch( p_expected, iNumTrees, p_oResults, NULL );

  //*******************************************
  //Set up search 18
  //*******************************************
  //Do the search
  query.str( "" );
  query << "type=" << clTreePopulation::woody_debris << "::species=0,1,2";
  p_oResults = p_oPop->Find( ( char * ) query.str().c_str() );
  //Check the minimum and maximum height divisions for searching
  CPPUNIT_ASSERT( 2 == p_oResults->m_iStartHeightDiv );
  CPPUNIT_ASSERT( 11 == p_oResults->m_iEndHeightDiv );
  //Set up the expected results
  for ( i = 0; i < iNumTrees; i++ )
    p_expected[i].bShouldBe = false;
  //Validate
  CheckTreeSearch( p_expected, iNumTrees, p_oResults, NULL );

  //*******************************************
  //Set up search 19
  //*******************************************
  //Do the search
  query.str( "" );
  query << "type=" << clTreePopulation::seedling << "::species=0";
  p_oResults = p_oPop->Find( ( char * ) query.str().c_str() );
  //Check the minimum and maximum height divisions for searching
  CPPUNIT_ASSERT( 0 == p_oResults->m_iStartHeightDiv );
  CPPUNIT_ASSERT( 0 == p_oResults->m_iEndHeightDiv );
  //Set up the expected results
  for ( i = 0; i < iNumTrees; i++ )
    p_expected[i].bShouldBe = false;
  p_expected[1].bShouldBe = true; p_expected[20].bShouldBe = true;
  p_expected[41].bShouldBe = true;
  //Validate
  CheckTreeSearch( p_expected, iNumTrees, p_oResults, p_oTreeSet[41] );

  //*******************************************
  //Set up search 20
  //*******************************************
  //Do the search
  query.str( "" );
  query << "species=2,0,2::type=" << clTreePopulation::seedling << "," << clTreePopulation::sapling;
  p_oResults = p_oPop->Find( ( char * ) query.str().c_str() );
  //Check the minimum and maximum height divisions for searching
  CPPUNIT_ASSERT( 0 == p_oResults->m_iStartHeightDiv );
  CPPUNIT_ASSERT( 2 == p_oResults->m_iEndHeightDiv );
  //Set up the expected results
  for ( i = 0; i < iNumTrees; i++ )
    p_expected[i].bShouldBe = false;
  p_expected[1].bShouldBe = true; p_expected[3].bShouldBe = true;
  p_expected[13].bShouldBe = true; p_expected[16].bShouldBe = true;
  p_expected[19].bShouldBe = true; p_expected[20].bShouldBe = true;
  p_expected[21].bShouldBe = true; p_expected[41].bShouldBe = true;
  p_expected[43].bShouldBe = true; p_expected[44].bShouldBe = true;
  p_expected[46].bShouldBe = true; p_expected[47].bShouldBe = true;
  p_expected[78].bShouldBe = true;
  //Validate
  CheckTreeSearch( p_expected, iNumTrees, p_oResults, p_oTreeSet[41] );

  //*******************************************
  //Set up search 21
  //*******************************************
  //Do the search
  query.str( "" );
  query << "type=" << clTreePopulation::seedling << "," << clTreePopulation::sapling << ","
       << clTreePopulation::adult << "::species=0,1,2";
  p_oResults = p_oPop->Find( ( char * ) query.str().c_str() );
  //Set up the expected results
  for ( i = 0; i < iNumTrees; i++ )
    p_expected[i].bShouldBe = true;
  //Validate
  CheckTreeSearch( p_expected, iNumTrees, p_oResults, p_oTreeSet[36] );

  //*******************************************
  //Set up search 22
  //*******************************************
  //Do the search
  query.str( "" );
  query << "type=" << clTreePopulation::seedling << "," << clTreePopulation::adult << "::species=1";
  p_oResults = p_oPop->Find( ( char * ) query.str().c_str() );
  //Set up the expected results
  for ( i = 0; i < iNumTrees; i++ )
    p_expected[i].bShouldBe = false;
  p_expected[2].bShouldBe = true; p_expected[6].bShouldBe = true;
  p_expected[9].bShouldBe = true; p_expected[10].bShouldBe = true;
  p_expected[14].bShouldBe = true; p_expected[26].bShouldBe = true;
  p_expected[28].bShouldBe = true; p_expected[31].bShouldBe = true;
  p_expected[34].bShouldBe = true; p_expected[36].bShouldBe = true;
  p_expected[40].bShouldBe = true; p_expected[42].bShouldBe = true;
  p_expected[48].bShouldBe = true; p_expected[51].bShouldBe = true;
  p_expected[54].bShouldBe = true; p_expected[57].bShouldBe = true;
  p_expected[60].bShouldBe = true; p_expected[63].bShouldBe = true;
  p_expected[66].bShouldBe = true; p_expected[68].bShouldBe = true;
  p_expected[72].bShouldBe = true; p_expected[75].bShouldBe = true;
  //Validate
  CheckTreeSearch( p_expected, iNumTrees, p_oResults, p_oTreeSet[36] );

  //*******************************************
  //Set up search 23
  //*******************************************
  //Do the search
  query.str( "" );
  query << "type=" << clTreePopulation::adult << "," << clTreePopulation::sapling << "::species=2";
  p_oResults = p_oPop->Find( ( char * ) query.str().c_str() );
  //Check the minimum and maximum height divisions for searching
  CPPUNIT_ASSERT( 0 == p_oResults->m_iStartHeightDiv );
  CPPUNIT_ASSERT( 11 == p_oResults->m_iEndHeightDiv );
  //Set up the expected results
  for ( i = 0; i < iNumTrees; i++ )
    p_expected[i].bShouldBe = false;
  p_expected[0].bShouldBe = true; p_expected[5].bShouldBe = true;
  p_expected[7].bShouldBe = true; p_expected[11].bShouldBe = true;
  p_expected[12].bShouldBe = true; p_expected[16].bShouldBe = true;
  p_expected[17].bShouldBe = true; p_expected[19].bShouldBe = true;
  p_expected[21].bShouldBe = true; p_expected[24].bShouldBe = true;
  p_expected[27].bShouldBe = true; p_expected[30].bShouldBe = true;
  p_expected[33].bShouldBe = true; p_expected[38].bShouldBe = true;
  p_expected[46].bShouldBe = true; p_expected[49].bShouldBe = true;
  p_expected[52].bShouldBe = true; p_expected[55].bShouldBe = true;
  p_expected[58].bShouldBe = true; p_expected[61].bShouldBe = true;
  p_expected[64].bShouldBe = true; p_expected[67].bShouldBe = true;
  p_expected[70].bShouldBe = true; p_expected[73].bShouldBe = true;
  p_expected[76].bShouldBe = true; p_expected[77].bShouldBe = true;
  //Validate
  CheckTreeSearch( p_expected, iNumTrees, p_oResults, p_oTreeSet[46] );

  //*******************************************
  //Set up search 24
  //*******************************************
  //Do the search
  query.str( "" );
  query << "type=" << clTreePopulation::sapling << "::species=0";
  p_oResults = p_oPop->Find( ( char * ) query.str().c_str() );
  //Set up the expected results
  for ( i = 0; i < iNumTrees; i++ )
    p_expected[i].bShouldBe = false;
  p_expected[13].bShouldBe = true; p_expected[44].bShouldBe = true;
  p_expected[47].bShouldBe = true; p_expected[78].bShouldBe = true;
  //Validate
  CheckTreeSearch( p_expected, iNumTrees, p_oResults, p_oTreeSet[44] );

  //*******************************************
  //Set up search 25
  //*******************************************
  //Do the search
  query.str( "" );
  query << "type=" << clTreePopulation::adult << "::species=1";
  p_oResults = p_oPop->Find( ( char * ) query.str().c_str() );
  //Check the minimum and maximum height divisions for searching
  CPPUNIT_ASSERT( 2 == p_oResults->m_iStartHeightDiv );
  CPPUNIT_ASSERT( 11 == p_oResults->m_iEndHeightDiv );
  //Set up the expected results
  for ( i = 0; i < iNumTrees; i++ )
    p_expected[i].bShouldBe = false;
  p_expected[6].bShouldBe = true; p_expected[9].bShouldBe = true;
  p_expected[10].bShouldBe = true; p_expected[14].bShouldBe = true;
  p_expected[26].bShouldBe = true; p_expected[28].bShouldBe = true;
  p_expected[31].bShouldBe = true; p_expected[34].bShouldBe = true;
  p_expected[36].bShouldBe = true; p_expected[40].bShouldBe = true;
  p_expected[48].bShouldBe = true; p_expected[51].bShouldBe = true;
  p_expected[54].bShouldBe = true; p_expected[57].bShouldBe = true;
  p_expected[60].bShouldBe = true; p_expected[63].bShouldBe = true;
  p_expected[66].bShouldBe = true; p_expected[68].bShouldBe = true;
  p_expected[72].bShouldBe = true; p_expected[75].bShouldBe = true;
  //Validate
  CheckTreeSearch( p_expected, iNumTrees, p_oResults, p_oTreeSet[36] );

  //*******************************************
  //Set up search 26
  //*******************************************
  //Do the search
  query.str( "" );
  query << "type=" << clTreePopulation::seed;
  p_oResults = p_oPop->Find( ( char * ) query.str().c_str() );
  //Set up the expected results
  for ( i = 0; i < iNumTrees; i++ )
    p_expected[i].bShouldBe = false;
  //Validate
  CheckTreeSearch( p_expected, iNumTrees, p_oResults, NULL );

  //*******************************************
  //Set up search 27
  //*******************************************
  //Do the search
  query.str( "" );
  query << "type=" << clTreePopulation::snag;
  p_oResults = p_oPop->Find( ( char * ) query.str().c_str() );
  //Set up the expected results
  for ( i = 0; i < iNumTrees; i++ )
    p_expected[i].bShouldBe = false;
  //Validate
  CheckTreeSearch( p_expected, iNumTrees, p_oResults, NULL );

  //*******************************************
  //Set up search 28
  //*******************************************
  //Do the search
  query.str( "" );
  query << "type=" << clTreePopulation::woody_debris;
  p_oResults = p_oPop->Find( ( char * ) query.str().c_str() );
  //Set up the expected results
  for ( i = 0; i < iNumTrees; i++ )
    p_expected[i].bShouldBe = false;
  //Validate
  CheckTreeSearch( p_expected, iNumTrees, p_oResults, NULL );

  //*******************************************
  //Set up search 29
  //*******************************************
  //Do the search
  query.str( "" );
  query << "type=" << clTreePopulation::seedling << "::type=" << clTreePopulation::seedling;
  p_oResults = p_oPop->Find( ( char * ) query.str().c_str() );
  //Set up the expected results
  for ( i = 0; i < iNumTrees; i++ )
    p_expected[i].bShouldBe = false;
  p_expected[1].bShouldBe = true; p_expected[2].bShouldBe = true;
  p_expected[3].bShouldBe = true; p_expected[20].bShouldBe = true;
  p_expected[41].bShouldBe = true; p_expected[42].bShouldBe = true;
  p_expected[43].bShouldBe = true;
  //Validate
  CheckTreeSearch( p_expected, iNumTrees, p_oResults, p_oTreeSet[41] );

  //*******************************************
  //Set up search 30
  //*******************************************
  //Do the search
  query.str( "" );
  query << "type=" << clTreePopulation::seedling << "," << clTreePopulation::sapling;
  p_oResults = p_oPop->Find( ( char * ) query.str().c_str() );
  //Set up the expected results
  for ( i = 0; i < iNumTrees; i++ )
    p_expected[i].bShouldBe = false;
  p_expected[1].bShouldBe = true; p_expected[2].bShouldBe = true;
  p_expected[3].bShouldBe = true; p_expected[13].bShouldBe = true;
  p_expected[15].bShouldBe = true; p_expected[16].bShouldBe = true;
  p_expected[19].bShouldBe = true; p_expected[20].bShouldBe = true;
  p_expected[21].bShouldBe = true; p_expected[22].bShouldBe = true;
  p_expected[41].bShouldBe = true; p_expected[42].bShouldBe = true;
  p_expected[43].bShouldBe = true; p_expected[44].bShouldBe = true;
  p_expected[45].bShouldBe = true; p_expected[46].bShouldBe = true;
  p_expected[47].bShouldBe = true; p_expected[78].bShouldBe = true;
  //Validate
  CheckTreeSearch( p_expected, iNumTrees, p_oResults, p_oTreeSet[41] );

  //*******************************************
  //Set up search 31
  //*******************************************
  //Do the search
  query.str( "" );
  query << "type=" << clTreePopulation::seedling << "," << clTreePopulation::sapling << "," << clTreePopulation::adult << ","
       << clTreePopulation::sapling;
  p_oResults = p_oPop->Find( ( char * ) query.str().c_str() );
  //Set up the expected results
  for ( i = 0; i < iNumTrees; i++ )
    p_expected[i].bShouldBe = true;
  //Validate
  CheckTreeSearch( p_expected, iNumTrees, p_oResults, p_oTreeSet[36] );

  //*******************************************
  //Set up search 32
  //*******************************************
  //Do the search
  query.str( "" );
  query << "type=" << clTreePopulation::seedling << "," << clTreePopulation::adult;
  p_oResults = p_oPop->Find( ( char * ) query.str().c_str() );
  //Set up the expected results
  for ( i = 0; i < iNumTrees; i++ )
    p_expected[i].bShouldBe = true;
  //This time - set the trees we won't find
  p_expected[13].bShouldBe = false; p_expected[15].bShouldBe = false;
  p_expected[16].bShouldBe = false; p_expected[19].bShouldBe = false;
  p_expected[21].bShouldBe = false; p_expected[22].bShouldBe = false;
  p_expected[44].bShouldBe = false; p_expected[45].bShouldBe = false;
  p_expected[46].bShouldBe = false; p_expected[47].bShouldBe = false;
  p_expected[78].bShouldBe = false;
  //Validate
  CheckTreeSearch( p_expected, iNumTrees, p_oResults, p_oTreeSet[36] );

  //*******************************************
  //Set up search 33
  //*******************************************
  //Do the search
  query.str( "" );
  query << "type=" << clTreePopulation::sapling << "," << clTreePopulation::adult;
  p_oResults = p_oPop->Find( ( char * ) query.str().c_str() );
  //Set up the expected results
  for ( i = 0; i < iNumTrees; i++ )
    p_expected[i].bShouldBe = true;
  //This time - set the trees we won't find
  p_expected[1].bShouldBe = false; p_expected[2].bShouldBe = false;
  p_expected[3].bShouldBe = false; p_expected[20].bShouldBe = false;
  p_expected[41].bShouldBe = false; p_expected[42].bShouldBe = false;
  p_expected[43].bShouldBe = false;
  //Validate
  CheckTreeSearch( p_expected, iNumTrees, p_oResults, p_oTreeSet[36] );

  //*******************************************
  //Set up search 34
  //*******************************************
  //Do the search
  query.str( "" );
  query << "type=" << clTreePopulation::adult;
  p_oResults = p_oPop->Find( ( char * ) query.str().c_str() );
  //Set up the expected results
  for ( i = 0; i < iNumTrees; i++ )
    p_expected[i].bShouldBe = true;
  //This time - set the trees we won't find
  p_expected[1].bShouldBe = false; p_expected[2].bShouldBe = false;
  p_expected[3].bShouldBe = false; p_expected[20].bShouldBe = false;
  p_expected[41].bShouldBe = false; p_expected[42].bShouldBe = false;
  p_expected[43].bShouldBe = false; p_expected[13].bShouldBe = false;
  p_expected[15].bShouldBe = false; p_expected[16].bShouldBe = false;
  p_expected[19].bShouldBe = false; p_expected[21].bShouldBe = false;
  p_expected[22].bShouldBe = false; p_expected[44].bShouldBe = false;
  p_expected[45].bShouldBe = false; p_expected[46].bShouldBe = false;
  p_expected[47].bShouldBe = false; p_expected[78].bShouldBe = false;
  //Validate
  CheckTreeSearch( p_expected, iNumTrees, p_oResults, p_oTreeSet[36] );

  //delete the expected results array
  delete[] p_expected;
}

//----------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////
//     CheckTreeSearch()
/////////////////////////////////////////////////////////////////////////////
void clTestTreePopulation::CheckTreeSearch( struct treeResults * p_expected, short int iNumResults,
     clTreeSearch * p_oActual, clTree * p_oFirstTree )
     {
       clTree * p_oReturnedTree; //found tree
       short int i; //loop counter
       bool bFound; //whether or not you found a target tree

       //If the tree search pointer was NULL, exit gracefully
       CPPUNIT_ASSERT( p_oActual );

       //Reset the expected list found flag
       for ( i = 0; i < iNumResults; i++ )
         p_expected[i].iFoundFlag = -1;

       //Check the first tree returned
       p_oReturnedTree = p_oActual->NextTree();
       if (p_oFirstTree != p_oReturnedTree) {
         p_oFirstTree = NULL;
       }
       CPPUNIT_ASSERT( p_oFirstTree == p_oReturnedTree );

       //If the tree is already NULL, make sure it should be
       if ( NULL == p_oReturnedTree )
       {
         for ( i = 0; i < iNumResults; i++ )
         {
           CPPUNIT_ASSERT( !p_expected[i].bShouldBe );
         }
       }

       //Go through the trees until they're NULL
       while ( p_oReturnedTree )
       {
         bFound = false;
         //Find this tree in the list
         for ( i = 0; i < iNumResults; i++ )
         {
           if ( p_oReturnedTree == p_expected[i].p_oTree )
           {
             p_expected[i].iFoundFlag++;
             bFound = true;
             break;
           }
         }
         //If we didn't find the tree - note
         CPPUNIT_ASSERT( bFound );
         p_oReturnedTree = p_oActual->NextTree();
       } //end of while (p_oTree)

       //Hit NextTree() one more time
       p_oReturnedTree = p_oActual->NextTree();
       CPPUNIT_ASSERT( NULL == p_oReturnedTree );

       //Now check the results
       for ( i = 0; i < iNumResults; i++ )
       {
        if ((p_expected[i].bShouldBe && -1 == p_expected[i].iFoundFlag ) ||
           (!p_expected[i].bShouldBe && -1 != p_expected[i].iFoundFlag))
           p_oReturnedTree = NULL;

         CPPUNIT_ASSERT(
           ( p_expected[i].bShouldBe && -1 != p_expected[i].iFoundFlag ) ||
           (!p_expected[i].bShouldBe && -1 == p_expected[i].iFoundFlag ) );
         CPPUNIT_ASSERT( p_expected[i].iFoundFlag <= 0 );
       }
}

//----------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////
//     DoSet2Searches()
//////////////////////////////////////////////////////////////////////////////
void clTestTreePopulation::DoSet2Searches( clTreePopulation * p_oPop, clTree * * p_oTreeSet )
{
  using namespace std;
  short int iNumTrees = 80, //number of trees in this plot
       i; //loop counter
  struct treeResults * p_expected; //expected results list for all trees
  clTreeSearch * p_oResults; //tree search object
  clTree * p_oTree; //pointer to tree object
  stringstream query; //query string for searches

  p_expected = new struct treeResults[iNumTrees];
  //Load the trees into the results
  for ( i = 0; i < iNumTrees - 1; i++ )
    p_expected[i].p_oTree = p_oTreeSet[i];
  p_expected[79].p_oTree = NULL; //tree 80 not created yet

  //*******************************************
  //Set up search 35
  //*******************************************
  //Do the search
  query.str( "" );
  query << "type=" << clTreePopulation::sapling;
  p_oResults = p_oPop->Find( ( char * ) query.str().c_str() );
  //Set up the expected results
  for ( i = 0; i < iNumTrees; i++ )
    p_expected[i].bShouldBe = false;
  p_expected[13].bShouldBe = true; p_expected[15].bShouldBe = true;
  p_expected[16].bShouldBe = true; p_expected[19].bShouldBe = true;
  p_expected[21].bShouldBe = true; p_expected[22].bShouldBe = true;
  p_expected[44].bShouldBe = true; p_expected[45].bShouldBe = true;
  p_expected[46].bShouldBe = true; p_expected[47].bShouldBe = true;
  p_expected[78].bShouldBe = true;
  //Validate
  CheckTreeSearch( p_expected, iNumTrees, p_oResults, p_oTreeSet[44] );

  //*******************************************
  //Delete results of search 35
  //*******************************************
  p_oResults->StartOver();
  p_oTree = p_oResults->NextTree();
  while ( p_oTree )
  {
    p_oPop->KillTree( p_oTree, natural );
    p_oTree = p_oResults->NextTree();
  }

  //Null out those tree pointers
  p_expected[13].p_oTree = NULL; p_expected[15].p_oTree = NULL;
  p_expected[16].p_oTree = NULL; p_expected[19].p_oTree = NULL;
  p_expected[21].p_oTree = NULL; p_expected[22].p_oTree = NULL;
  p_expected[44].p_oTree = NULL; p_expected[45].p_oTree = NULL;
  p_expected[46].p_oTree = NULL; p_expected[47].p_oTree = NULL;
  p_expected[78].p_oTree = NULL;

  //*******************************************
  //Set up search 36 and delete those trees returned
  //*******************************************
  //Do the search
  query.str( "" );
  query << "distance=25.3 FROM x=0,y=0::height=0.0";
  p_oResults = p_oPop->Find( ( char * ) query.str().c_str() );
  //Cycle through the trees once so we can test StartOver()
  p_oTree = p_oResults->NextTree();
  while ( p_oTree )
  {
    p_oTree = p_oResults->NextTree();
  }
  p_oResults->StartOver();
  p_oTree = p_oResults->NextTree();
  while ( p_oTree )
  {
    p_oPop->KillTree( p_oTree, natural );
    p_oTree = p_oResults->NextTree();
  }

  //*******************************************
  //Set up search 37
  //*******************************************
  //Do the search
  query.str( "" );
  query << "type=" << clTreePopulation::sapling;
  p_oResults = p_oPop->Find( ( char * ) query.str().c_str() );
  //Set up the expected results
  for ( i = 0; i < iNumTrees; i++ )
    p_expected[i].bShouldBe = false;
  //Validate
  CheckTreeSearch( p_expected, iNumTrees, p_oResults, NULL );

  //*******************************************
  //Set up search 38
  //*******************************************
  //Do the search
  query.str( "" );
  query << "type=" << clTreePopulation::sapling << "::species=0";
  p_oResults = p_oPop->Find( ( char * ) query.str().c_str() );
  //Set up the expected results
  for ( i = 0; i < iNumTrees; i++ )
    p_expected[i].bShouldBe = false;
  //Validate
  CheckTreeSearch( p_expected, iNumTrees, p_oResults, NULL );

  //*******************************************
  //Set up search 39
  //*******************************************
  //Do the search
  query.str( "" );
  query << "type=" << clTreePopulation::adult;
  p_oResults = p_oPop->Find( ( char * ) query.str().c_str() );
  //Set up the expected results
  for ( i = 0; i < iNumTrees; i++ )
    p_expected[i].bShouldBe = false;
  p_expected[0].bShouldBe = true; p_expected[4].bShouldBe = true;
  p_expected[5].bShouldBe = true; p_expected[6].bShouldBe = true;
  p_expected[7].bShouldBe = true; p_expected[8].bShouldBe = true;
  p_expected[9].bShouldBe = true; p_expected[10].bShouldBe = true;
  p_expected[11].bShouldBe = true; p_expected[12].bShouldBe = true;
  p_expected[14].bShouldBe = true; p_expected[17].bShouldBe = true;
  p_expected[18].bShouldBe = true; p_expected[23].bShouldBe = true;
  p_expected[24].bShouldBe = true; p_expected[25].bShouldBe = true;
  p_expected[26].bShouldBe = true; p_expected[27].bShouldBe = true;
  p_expected[28].bShouldBe = true; p_expected[29].bShouldBe = true;
  p_expected[30].bShouldBe = true; p_expected[31].bShouldBe = true;
  p_expected[32].bShouldBe = true; p_expected[33].bShouldBe = true;
  p_expected[34].bShouldBe = true; p_expected[35].bShouldBe = true;
  p_expected[38].bShouldBe = true; p_expected[39].bShouldBe = true;
  p_expected[40].bShouldBe = true; p_expected[77].bShouldBe = true;
  //Validate
  CheckTreeSearch( p_expected, iNumTrees, p_oResults, p_oTreeSet[0] );

  //*******************************************
  //Set up search 40
  //*******************************************
  //Do the search
  query.str( "" );
  query << "type=" << clTreePopulation::adult << "::species=2";
  p_oResults = p_oPop->Find( ( char * ) query.str().c_str() );
  //Set up the expected results
  for ( i = 0; i < iNumTrees; i++ )
    p_expected[i].bShouldBe = false;
  p_expected[0].bShouldBe = true; p_expected[5].bShouldBe = true;
  p_expected[7].bShouldBe = true; p_expected[11].bShouldBe = true;
  p_expected[12].bShouldBe = true; p_expected[17].bShouldBe = true;
  p_expected[24].bShouldBe = true; p_expected[27].bShouldBe = true;
  p_expected[30].bShouldBe = true; p_expected[33].bShouldBe = true;
  p_expected[38].bShouldBe = true; p_expected[77].bShouldBe = true;
  //Validate
  CheckTreeSearch( p_expected, iNumTrees, p_oResults, p_oTreeSet[0] );

  //*******************************************
  //Set up search 41
  //*******************************************
  //Do the search
  query.str( "" );
  query << "type=" << clTreePopulation::seedling << "::species=2";
  p_oResults = p_oPop->Find( ( char * ) query.str().c_str() );
  //Set up the expected results
  for ( i = 0; i < iNumTrees; i++ )
    p_expected[i].bShouldBe = false;
  p_expected[3].bShouldBe = true;
  //Validate
  CheckTreeSearch( p_expected, iNumTrees, p_oResults, p_oTreeSet[3] );

  //*******************************************
  //Set up search 42
  //*******************************************
  //Do the search
  query.str( "" );
  query << "all";
  p_oResults = p_oPop->Find( ( char * ) query.str().c_str() );
  //Set up the expected results
  for ( i = 0; i < iNumTrees; i++ )
    p_expected[i].bShouldBe = false;
  p_expected[0].bShouldBe = true; p_expected[1].bShouldBe = true;
  p_expected[2].bShouldBe = true; p_expected[3].bShouldBe = true;
  p_expected[4].bShouldBe = true; p_expected[5].bShouldBe = true;
  p_expected[6].bShouldBe = true; p_expected[7].bShouldBe = true;
  p_expected[8].bShouldBe = true; p_expected[9].bShouldBe = true;
  p_expected[10].bShouldBe = true; p_expected[11].bShouldBe = true;
  p_expected[12].bShouldBe = true; p_expected[14].bShouldBe = true;
  p_expected[17].bShouldBe = true; p_expected[18].bShouldBe = true;
  p_expected[20].bShouldBe = true; p_expected[23].bShouldBe = true;
  p_expected[24].bShouldBe = true; p_expected[25].bShouldBe = true;
  p_expected[26].bShouldBe = true; p_expected[27].bShouldBe = true;
  p_expected[28].bShouldBe = true; p_expected[29].bShouldBe = true;
  p_expected[30].bShouldBe = true; p_expected[31].bShouldBe = true;
  p_expected[32].bShouldBe = true; p_expected[33].bShouldBe = true;
  p_expected[34].bShouldBe = true; p_expected[35].bShouldBe = true;
  p_expected[38].bShouldBe = true; p_expected[39].bShouldBe = true;
  p_expected[40].bShouldBe = true; p_expected[77].bShouldBe = true;
  //Validate twice
  CheckTreeSearch( p_expected, iNumTrees, p_oResults, p_oTreeSet[0] );
  p_oResults->StartOver();
  CheckTreeSearch( p_expected, iNumTrees, p_oResults, p_oTreeSet[0] );

  //*******************************************
  //Set up search 43
  //*******************************************
  //Do the search
  query.str( "" );
  query << "type=" << clTreePopulation::seedling;
  p_oResults = p_oPop->Find( ( char * ) query.str().c_str() );
  //Set up the expected results
  for ( i = 0; i < iNumTrees; i++ )
    p_expected[i].bShouldBe = false;
  p_expected[1].bShouldBe = true; p_expected[2].bShouldBe = true;
  p_expected[3].bShouldBe = true; p_expected[20].bShouldBe = true;
  //Validate
  CheckTreeSearch( p_expected, iNumTrees, p_oResults, p_oTreeSet[20] );

  //*******************************************
  //Delete results of search 43
  //*******************************************
  p_oResults->StartOver();
  p_oTree = p_oResults->NextTree();
  while ( p_oTree )
  {
    p_oPop->KillTree( p_oTree, natural );
    p_oTree = p_oResults->NextTree();
  }
  //NULL out those pointers
  p_expected[1].p_oTree = NULL; p_expected[2].p_oTree = NULL;
  p_expected[3].p_oTree = NULL; p_expected[20].p_oTree = NULL;

  //*******************************************
  //Add tree 80
  //*******************************************
  p_expected[79].p_oTree = p_oPop->CreateTree( 1.0, 3.0, 2, clTreePopulation::seedling, 0 );
  p_oTreeSet[79] = p_expected[79].p_oTree;
  //Make sure that the diameter isn't 0
  CPPUNIT_ASSERT( p_expected[79].p_oTree->GetType() == clTreePopulation::seedling );
  float fTemp;
  //Get the diameter - make sure it's greater than 0
  p_expected[79].p_oTree->GetValue( p_oPop->GetDiam10Code( p_expected[79].p_oTree->GetSpecies(), p_expected[79].p_oTree->GetType() ), & fTemp );
  CPPUNIT_ASSERT( fTemp > 0 );
  //Get the height - make sure it's > 0 & < 1.35
  p_expected[79].p_oTree->GetValue( p_oPop->GetHeightCode( p_expected[79].p_oTree->GetSpecies(), p_expected[79].p_oTree->GetType() ), & fTemp );
  CPPUNIT_ASSERT( fTemp > 0 || fTemp < 1.35 );

  //*******************************************
  //Set up search 44
  //*******************************************
  //Do the search
  query.str( "" );
  query << "all";
  p_oResults = p_oPop->Find( ( char * ) query.str().c_str() );
  //Set up the expected results
  for ( i = 0; i < iNumTrees; i++ )
    p_expected[i].bShouldBe = false;
  p_expected[0].bShouldBe = true; p_expected[4].bShouldBe = true;
  p_expected[5].bShouldBe = true; p_expected[6].bShouldBe = true;
  p_expected[7].bShouldBe = true; p_expected[8].bShouldBe = true;
  p_expected[9].bShouldBe = true; p_expected[10].bShouldBe = true;
  p_expected[11].bShouldBe = true; p_expected[12].bShouldBe = true;
  p_expected[14].bShouldBe = true; p_expected[17].bShouldBe = true;
  p_expected[18].bShouldBe = true; p_expected[23].bShouldBe = true;
  p_expected[24].bShouldBe = true; p_expected[25].bShouldBe = true;
  p_expected[26].bShouldBe = true; p_expected[27].bShouldBe = true;
  p_expected[28].bShouldBe = true; p_expected[29].bShouldBe = true;
  p_expected[30].bShouldBe = true; p_expected[31].bShouldBe = true;
  p_expected[32].bShouldBe = true; p_expected[33].bShouldBe = true;
  p_expected[34].bShouldBe = true; p_expected[35].bShouldBe = true;
  p_expected[38].bShouldBe = true; p_expected[39].bShouldBe = true;
  p_expected[40].bShouldBe = true; p_expected[77].bShouldBe = true;
  p_expected[79].bShouldBe = true;

  //Validate
  CheckTreeSearch( p_expected, iNumTrees, p_oResults, p_oTreeSet[79] );

  //*******************************************
  //Set up search 45 and delete those trees returned
  //*******************************************
  //Do the search
  query.str( "" );
  query << "type=" << clTreePopulation::seedling << "," << clTreePopulation::sapling << ","
       << clTreePopulation::adult << "::species=0";
  p_oResults = p_oPop->Find( ( char * ) query.str().c_str() );
  p_oTree = p_oResults->NextTree();
  while ( p_oTree )
  {
    p_oPop->KillTree( p_oTree, natural );
    p_oTree = p_oResults->NextTree();
  }

  //*******************************************
  //Set up search 46
  //*******************************************
  //Do the search
  query.str( "" );
  query << "species=0::type=" << clTreePopulation::seedling;
  p_oResults = p_oPop->Find( ( char * ) query.str().c_str() );
  //Set up the expected results
  for ( i = 0; i < iNumTrees; i++ )
    p_expected[i].bShouldBe = false;
  //Validate
  CheckTreeSearch( p_expected, iNumTrees, p_oResults, NULL );

  //delete the expected results array
  delete[] p_expected;
}

//----------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////
//     DoSet3Searches()
////////////////////////////////////////////////////////////////////////////
void clTestTreePopulation::DoSet3Searches( clTreePopulation * p_oPop )
{
  using namespace std;
  clTreeSearch * p_oResults; //tree search object
  clTree * p_oTree; //pointer to tree object
  stringstream query; //query string for searches

  //Delete all trees
  p_oPop->EmptyHashTable();

  //Perform search 1
  query << "all";
  p_oResults = p_oPop->Find( ( char * ) query.str().c_str() );
  p_oTree = p_oResults->NextTree();
  CPPUNIT_ASSERT( p_oTree == NULL );

}

//----------------------------------------------------------------------------

//////////////////////////////////////////////////////////////////////////////
//     EmptyFakeHashTable()
/////////////////////////////////////////////////////////////////////////////
void clTestTreePopulation::EmptyFakeHashTable( clTree * * * * p_oShortestHD, clTree * * * * p_oTallestHD,
     clFakeLinkedList * * * p_oShort, clFakeLinkedList * * * p_oTall, int iNumXCells, int iNumYCells )
     {
       clFakeLinkedList * p_oRec, * p_oNextRec;
       short int i, j, k;
       for ( i = 0; i < iNumXCells; i++ )
         for ( j = 0; j < iNumYCells; j++ )
         {
           p_oRec = p_oShort[i] [j];
           while ( p_oRec )
           {
             p_oNextRec = p_oRec->nextLink;
             delete p_oRec;
             p_oRec = p_oNextRec;
           }
           p_oShort[i] [j] = NULL;
           p_oTall[i] [j] = NULL;
           for ( k = 0; k < 11; k++ )
           {
             p_oShortestHD[i] [j] [k] = NULL;
             p_oTallestHD[i] [j] [k] = NULL;
           }
         }
}

//---------------------------------------------------------------------------

//////////////////////////////////////////////////////////////////////////////
//     CheckHashTable()
/////////////////////////////////////////////////////////////////////////////
void clTestTreePopulation::CheckHashTable( clTreePopulation * p_oPop, clTree * * * * p_oShortestHD,
     clTree * * * * p_oTallestHD, clFakeLinkedList * * * p_oShort, clFakeLinkedList * * * p_oTall,
     int iNumXCells, int iNumYCells )
     {

       clTree * p_oPopTree; //for checking tree links - tree population tree
       clFakeLinkedList * p_oTestTree; //for checking links - expected results
       short int i, j, k; //loop counters

       //Check the shortest height division links
       for ( i = 0; i < iNumXCells; i++ )
         for ( j = 0; j < iNumYCells; j++ )
           for ( k = 0; k < 11; k++ )
             CPPUNIT_ASSERT( p_oShortestHD[i] [j] [k] == p_oPop->mp_oTreeShortest[i] [j] [k] );

       //Check the tallest height division links
       for ( i = 0; i < iNumXCells; i++ )
         for ( j = 0; j < iNumYCells; j++ )
           for ( k = 0; k < 11; k++ )
             CPPUNIT_ASSERT( p_oTallestHD[i] [j] [k] == p_oPop->mp_oTreeTallest[i] [j] [k] );

       //Check the tree links from shortest to tallest
       for ( i = 0; i < iNumXCells; i++ )
         for ( j = 0; j < iNumYCells; j++ )
         {
           //Get the shortest tree of the real hash table for this grid cell
           for ( k = 0; k < 11; k++ )
           {
             p_oPopTree = p_oPop->mp_oTreeShortest[i] [j] [k];
             if ( p_oPopTree ) break;
           }
           //Get the shortest expected results tree
           p_oTestTree = p_oShort[i] [j];
           //Check the linked lists
           while ( p_oTestTree || p_oPopTree )
           {
             CPPUNIT_ASSERT( p_oTestTree->thisTree == p_oPopTree );
             p_oTestTree = p_oTestTree->nextLink;
             p_oPopTree = p_oPopTree->GetTaller();
           }
         }

       //Check the tree links from tallest to shortest
       for ( i = 0; i < iNumXCells; i++ )
         for ( j = 0; j < iNumYCells; j++ )
         {
           //Get the tallest tree of the real hash table for this grid cell
           for ( k = 10; k >= 0; k-- )
           {
             p_oPopTree = p_oPop->mp_oTreeTallest[i] [j] [k];
             if ( p_oPopTree ) break;
           }
           //Get the tallest expected results tree
           p_oTestTree = p_oTall[i] [j];
           //Check the linked lists
           while ( p_oTestTree || p_oPopTree )
           {
             CPPUNIT_ASSERT( p_oTestTree->prev == p_oPopTree->GetShorter() );
             p_oTestTree = p_oTestTree->prevLink;
             p_oPopTree = p_oPopTree->GetShorter();
           }
         }
}


//////////////////////////////////////////////////////////////////////////////
//     LoadTrees1()
/////////////////////////////////////////////////////////////////////////////
void clTestTreePopulation::LoadTrees1( clTreePopulation * p_oPop, clTree * * * * p_oShortestHD, clTree * * * * p_oTallestHD,
     clFakeLinkedList * * * p_oShort, clFakeLinkedList * * * p_oTall, clTree * * p_oTreeSet, int iNumXCells, int iNumYCells,
     bool bFullCheck, bool bUpdateHashTable )
     {
       clFakeLinkedList * p_oRec = NULL, * p_oNextRec = NULL; //for creating links
       float fX, fY, fDiam; //for creating trees
       short int iSp, iTp, //for creating trees
            iTreeNum = 0; //helps with tree indexes - reduces typing errors
       //***********************************************************
       //Create the trees
       //***********************************************************
       //--------->Create tree 1
       fX = 30.0; fY = 42.0; iSp = 2; iTp = clTreePopulation::adult; fDiam = 12.0;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       //Put the tree in the hash table - leave previous and next links as NULL
       if ( bUpdateHashTable )
       {
         p_oShort[3] [5] = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oTall[3] [5] = p_oShort[3] [5];
         p_oShortestHD[3] [5] [3] = p_oTreeSet[iTreeNum];
         p_oTallestHD[3] [5] [3] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 2
       fX = 115.0; fY = 56.0; iSp = 0; iTp = clTreePopulation::seedling; fDiam = 1.0;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table - leave previous and next links as NULL
         p_oShort[14] [7] = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oTall[14] [7] = p_oShort[14] [7];
         p_oShortestHD[14] [7] [0] = p_oTreeSet[iTreeNum];
         p_oTallestHD[14] [7] [0] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 3
       fX = 116.0; fY = 57.0; iSp = 1; iTp = clTreePopulation::seedling; fDiam = 0.9;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         p_oRec = p_oShort[14] [7];
         p_oShort[14] [7] = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oShort[14] [7]->nextLink = p_oRec; p_oShort[14] [7]->next = p_oRec->thisTree;
         p_oRec->prevLink = p_oShort[14] [7]; p_oRec->prev = p_oShort[14] [7]->thisTree;
         p_oShortestHD[14] [7] [0] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 4
       fX = 117.0; fY = 58.0; iSp = 2; iTp = clTreePopulation::seedling; fDiam = 1.3;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         p_oRec = p_oTall[14] [7];
         p_oTall[14] [7] = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oTall[14] [7]->prevLink = p_oRec; p_oTall[14] [7]->prev = p_oRec->thisTree;
         p_oRec->nextLink = p_oTall[14] [7]; p_oRec->next = p_oTall[14] [7]->thisTree;
         p_oTallestHD[14] [7] [0] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 5
       fX = 112.6; fY = 57.1; iSp = 0; iTp = clTreePopulation::sapling; fDiam = 35.0;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         p_oRec = p_oTall[14] [7];
         p_oTall[14] [7] = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oTall[14] [7]->prevLink = p_oRec; p_oTall[14] [7]->prev = p_oRec->thisTree;
         p_oRec->nextLink = p_oTall[14] [7]; p_oRec->next = p_oTall[14] [7]->thisTree;
         p_oTallestHD[14] [7] [6] = p_oTreeSet[iTreeNum];
         p_oShortestHD[14] [7] [6] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 6
       fX = 117.2; fY = 60.2; iSp = 2; iTp = clTreePopulation::adult; fDiam = 20.0;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         p_oRec = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oTall[14] [7]->prevLink->nextLink = p_oRec; p_oTall[14] [7]->prevLink->next = p_oRec->thisTree;
         p_oRec->prevLink = p_oTall[14] [7]->prevLink; p_oRec->prev = p_oTall[14] [7]->prev;
         p_oRec->nextLink = p_oTall[14] [7]; p_oRec->next = p_oTall[14] [7]->thisTree;
         p_oTall[14] [7]->prevLink = p_oRec; p_oTall[14] [7]->prev = p_oRec->thisTree;
         p_oTallestHD[14] [7] [4] = p_oTreeSet[iTreeNum];
         p_oShortestHD[14] [7] [4] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 7
       fX = 113.0; fY = 60.0; iSp = 1; iTp = clTreePopulation::adult; fDiam = 33.0;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         p_oRec = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oTall[14] [7]->prevLink->nextLink = p_oRec; p_oTall[14] [7]->prevLink->next = p_oRec->thisTree;
         p_oRec->prevLink = p_oTall[14] [7]->prevLink; p_oRec->prev = p_oTall[14] [7]->prev;
         p_oRec->nextLink = p_oTall[14] [7]; p_oRec->next = p_oTall[14] [7]->thisTree;
         p_oTall[14] [7]->prevLink = p_oRec; p_oTall[14] [7]->prev = p_oRec->thisTree;
         p_oTallestHD[14] [7] [5] = p_oTreeSet[iTreeNum];
         p_oShortestHD[14] [7] [5] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 8
       fX = 112.0; fY = 60.0; iSp = 2; iTp = clTreePopulation::adult; fDiam = 25.0;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         p_oNextRec = p_oRec; //p_oRec still has the record for tree 7 in it - insert new one after
         p_oRec = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oRec->prevLink = p_oNextRec; p_oRec->prev = p_oNextRec->thisTree;
         p_oRec->nextLink = p_oNextRec->nextLink; p_oRec->next = p_oNextRec->next;
         p_oNextRec->nextLink->prevLink = p_oRec; p_oNextRec->nextLink->prev = p_oRec->thisTree;
         p_oNextRec->nextLink = p_oRec; p_oNextRec->next = p_oRec->thisTree;
         p_oTallestHD[14] [7] [5] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 9
       fX = 116.3; fY = 60.1; iSp = 0; iTp = clTreePopulation::adult; fDiam = 25.0;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         //p_oNextRec still has the record for tree 7 in it - insert new one before
         p_oRec = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oRec->nextLink = p_oNextRec; p_oRec->next = p_oNextRec->thisTree;
         p_oRec->prevLink = p_oNextRec->prevLink; p_oRec->prev = p_oNextRec->prev;
         p_oNextRec->prevLink->nextLink = p_oRec; p_oNextRec->prevLink->next = p_oRec->thisTree;
         p_oNextRec->prevLink = p_oRec; p_oNextRec->prev = p_oRec->thisTree;
         p_oShortestHD[14] [7] [5] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 10
       fX = 116.8; fY = 58.1; iSp = 1; iTp = clTreePopulation::adult; fDiam = 35.0;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         //Get the tallest in height div 5 - this will be inserted after
         p_oNextRec = p_oTall[14] [7];
         while ( p_oNextRec )
         {
           if ( p_oNextRec->thisTree == p_oTallestHD[14] [7] [5] ) break;
           else
             p_oNextRec = p_oNextRec->prevLink;
         }
         p_oRec = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oRec->prevLink = p_oNextRec; p_oRec->prev = p_oNextRec->thisTree;
         p_oRec->nextLink = p_oNextRec->nextLink; p_oRec->next = p_oNextRec->next;
         p_oNextRec->nextLink->prevLink = p_oRec; p_oNextRec->nextLink->prev = p_oRec->thisTree;
         p_oNextRec->nextLink = p_oRec; p_oNextRec->next = p_oRec->thisTree;
         p_oTallestHD[14] [7] [5] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 11
       fX = 114.0; fY = 61.0; iSp = 1; iTp = clTreePopulation::adult; fDiam = 32.0;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         //Get tree 9 - this will be inserted after
         p_oNextRec = p_oTall[14] [7];
         while ( p_oNextRec )
         {
           if ( p_oNextRec->thisTree == p_oTreeSet[8] ) break;
           else
             p_oNextRec = p_oNextRec->prevLink;
         }
         p_oRec = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oRec->prevLink = p_oNextRec; p_oRec->prev = p_oNextRec->thisTree;
         p_oRec->nextLink = p_oNextRec->nextLink; p_oRec->next = p_oNextRec->next;
         p_oNextRec->nextLink->prevLink = p_oRec; p_oNextRec->nextLink->prev = p_oRec->thisTree;
         p_oNextRec->nextLink = p_oRec; p_oNextRec->next = p_oRec->thisTree;
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 12
       fX = 113.5; fY = 62.0; iSp = 2; iTp = clTreePopulation::adult; fDiam = 100.0;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         p_oRec = p_oTall[14] [7];
         p_oTall[14] [7] = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oTall[14] [7]->prevLink = p_oRec; p_oTall[14] [7]->prev = p_oRec->thisTree;
         p_oRec->nextLink = p_oTall[14] [7]; p_oRec->next = p_oTall[14] [7]->thisTree;
         p_oTallestHD[14] [7] [10] = p_oTreeSet[iTreeNum];
         p_oShortestHD[14] [7] [10] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 13
       fX = 118.0; fY = 63.0; iSp = 2; iTp = clTreePopulation::adult; fDiam = 102.0;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         p_oRec = p_oTall[14] [7];
         p_oTall[14] [7] = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oTall[14] [7]->prevLink = p_oRec; p_oTall[14] [7]->prev = p_oRec->thisTree;
         p_oRec->nextLink = p_oTall[14] [7]; p_oRec->next = p_oTall[14] [7]->thisTree;
         p_oTallestHD[14] [7] [10] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 14
       fX = 115.0; fY = 58.0; iSp = 0; iTp = clTreePopulation::sapling; fDiam = 8.0;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         //Get tree 4 - this will be inserted after
         p_oNextRec = p_oShort[14] [7];
         while ( p_oNextRec )
         {
           if ( p_oNextRec->thisTree == p_oTreeSet[3] ) break;
           else
             p_oNextRec = p_oNextRec->nextLink;
         }
         p_oRec = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oRec->prevLink = p_oNextRec; p_oRec->prev = p_oNextRec->thisTree;
         p_oRec->nextLink = p_oNextRec->nextLink; p_oRec->next = p_oNextRec->next;
         p_oNextRec->nextLink->prevLink = p_oRec; p_oNextRec->nextLink->prev = p_oRec->thisTree;
         p_oNextRec->nextLink = p_oRec; p_oNextRec->next = p_oRec->thisTree;
         p_oShortestHD[14] [7] [2] = p_oTreeSet[iTreeNum];
         p_oTallestHD[14] [7] [2] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 15
       fX = 112.5; fY = 62.9; iSp = 1; iTp = clTreePopulation::adult; fDiam = 15.0;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         p_oNextRec = p_oRec; //p_oRec still has the record for tree 14 in it - insert new one after
         p_oRec = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oRec->prevLink = p_oNextRec; p_oRec->prev = p_oNextRec->thisTree;
         p_oRec->nextLink = p_oNextRec->nextLink; p_oRec->next = p_oNextRec->next;
         p_oNextRec->nextLink->prevLink = p_oRec; p_oNextRec->nextLink->prev = p_oRec->thisTree;
         p_oNextRec->nextLink = p_oRec; p_oNextRec->next = p_oRec->thisTree;
         p_oTallestHD[14] [7] [3] = p_oTreeSet[iTreeNum];
         p_oShortestHD[14] [7] [3] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 16
       fX = 126.0; fY = 70.0; iSp = 1; iTp = clTreePopulation::seedling; fDiam = 6.7525;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table - leave previous and next links as NULL
         p_oShort[15] [8] = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oTall[15] [8] = p_oShort[15] [8];
         p_oShortestHD[15] [8] [1] = p_oTreeSet[iTreeNum];
         p_oTallestHD[15] [8] [1] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 17
       fX = 125.0; fY = 70.0; iSp = 2; iTp = clTreePopulation::sapling; fDiam = 1.5;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         p_oRec = p_oShort[15] [8];
         p_oShort[15] [8] = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oShort[15] [8]->nextLink = p_oRec; p_oShort[15] [8]->next = p_oRec->thisTree;
         p_oRec->prevLink = p_oShort[15] [8]; p_oRec->prev = p_oShort[15] [8]->thisTree;
         p_oShortestHD[15] [8] [0] = p_oTreeSet[iTreeNum];
         p_oTallestHD[15] [8] [0] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 18
       fX = 53.0; fY = 25.0; iSp = 2; iTp = clTreePopulation::adult; fDiam = 80.0;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         p_oShort[6] [3] = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oTall[6] [3] = p_oShort[6] [3];
         p_oShortestHD[6] [3] [9] = p_oTreeSet[iTreeNum];
         p_oTallestHD[6] [3] [9] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 19
       fX = 55.0; fY = 27.0; iSp = 0; iTp = clTreePopulation::adult; fDiam = 90.0;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         p_oRec = p_oShort[6] [3];
         p_oShort[6] [3] = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oShort[6] [3]->nextLink = p_oRec; p_oShort[6] [3]->next = p_oRec->thisTree;
         p_oRec->prevLink = p_oShort[6] [3]; p_oRec->prev = p_oShort[6] [3]->thisTree;
         p_oShortestHD[6] [3] [9] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 20
       fX = 52.0; fY = 24.0; iSp = 2; iTp = clTreePopulation::sapling; fDiam = 8.0;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         p_oRec = p_oShort[6] [3];
         p_oShort[6] [3] = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oShort[6] [3]->nextLink = p_oRec; p_oShort[6] [3]->next = p_oRec->thisTree;
         p_oRec->prevLink = p_oShort[6] [3]; p_oRec->prev = p_oShort[6] [3]->thisTree;
         p_oShortestHD[6] [3] [2] = p_oTreeSet[iTreeNum];
         p_oTallestHD[6] [3] [2] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 21
       fX = 54.0; fY = 26.0; iSp = 0; iTp = clTreePopulation::seedling; fDiam = 1.2;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         p_oRec = p_oShort[6] [3];
         p_oShort[6] [3] = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oShort[6] [3]->nextLink = p_oRec; p_oShort[6] [3]->next = p_oRec->thisTree;
         p_oRec->prevLink = p_oShort[6] [3]; p_oRec->prev = p_oShort[6] [3]->thisTree;
         p_oShortestHD[6] [3] [0] = p_oTreeSet[iTreeNum];
         p_oTallestHD[6] [3] [0] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 22
       fX = 100.0; fY = 24.0; iSp = 2; iTp = clTreePopulation::sapling; fDiam = 8.0;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         p_oShort[12] [3] = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oTall[12] [3] = p_oShort[12] [3];
         p_oShortestHD[12] [3] [2] = p_oTreeSet[iTreeNum];
         p_oTallestHD[12] [3] [2] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 23
       fX = 103.0; fY = 25.0; iSp = 1; iTp = clTreePopulation::sapling; fDiam = 8.0;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         p_oRec = p_oShort[12] [3];
         p_oShort[12] [3] = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oShort[12] [3]->nextLink = p_oRec; p_oShort[12] [3]->next = p_oRec->thisTree;
         p_oRec->prevLink = p_oShort[12] [3]; p_oRec->prev = p_oShort[12] [3]->thisTree;
         p_oShortestHD[12] [3] [2] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 24
       fX = 102.0; fY = 26.0; iSp = 0; iTp = clTreePopulation::adult; fDiam = 12.0;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         p_oRec = p_oTall[12] [3];
         p_oTall[12] [3] = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oTall[12] [3]->prevLink = p_oRec; p_oTall[12] [3]->prev = p_oRec->thisTree;
         p_oRec->nextLink = p_oTall[12] [3]; p_oRec->next = p_oTall[12] [3]->thisTree;
         p_oShortestHD[12] [3] [3] = p_oTreeSet[iTreeNum];
         p_oTallestHD[12] [3] [3] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 25
       fX = 98.0; fY = 27.0; iSp = 2; iTp = clTreePopulation::adult; fDiam = 45.0;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         p_oRec = p_oTall[12] [3];
         p_oTall[12] [3] = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oTall[12] [3]->prevLink = p_oRec; p_oTall[12] [3]->prev = p_oRec->thisTree;
         p_oRec->nextLink = p_oTall[12] [3]; p_oRec->next = p_oTall[12] [3]->thisTree;
         p_oShortestHD[12] [3] [7] = p_oTreeSet[iTreeNum];
         p_oTallestHD[12] [3] [7] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 26
       fX = 99.0; fY = 26.5; iSp = 0; iTp = clTreePopulation::adult; fDiam = 30.0;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         p_oRec = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oTall[12] [3]->prevLink->nextLink = p_oRec; p_oTall[12] [3]->prevLink->next = p_oRec->thisTree;
         p_oRec->prevLink = p_oTall[12] [3]->prevLink; p_oRec->prev = p_oTall[12] [3]->prev;
         p_oRec->nextLink = p_oTall[12] [3]; p_oRec->next = p_oTall[12] [3]->thisTree;
         p_oTall[12] [3]->prevLink = p_oRec; p_oTall[12] [3]->prev = p_oRec->thisTree;
         p_oTallestHD[12] [3] [5] = p_oTreeSet[iTreeNum];
         p_oShortestHD[12] [3] [5] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 27
       fX = 97.0; fY = 24.2; iSp = 1; iTp = clTreePopulation::adult; fDiam = 50.0;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         p_oRec = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oTall[12] [3]->prevLink->nextLink = p_oRec; p_oTall[12] [3]->prevLink->next = p_oRec->thisTree;
         p_oRec->prevLink = p_oTall[12] [3]->prevLink; p_oRec->prev = p_oTall[12] [3]->prev;
         p_oRec->nextLink = p_oTall[12] [3]; p_oRec->next = p_oTall[12] [3]->thisTree;
         p_oTall[12] [3]->prevLink = p_oRec; p_oTall[12] [3]->prev = p_oRec->thisTree;
         p_oShortestHD[12] [3] [7] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 28
       fX = 42.0; fY = 160.0; iSp = 2; iTp = clTreePopulation::adult; fDiam = 35.0;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table - leave previous and next links as NULL
         p_oShort[5] [20] = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oTall[5] [20] = p_oShort[5] [20];
         p_oShortestHD[5] [20] [6] = p_oTreeSet[iTreeNum];
         p_oTallestHD[5] [20] [6] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 29
       fX = 44.0; fY = 165.0; iSp = 1; iTp = clTreePopulation::adult; fDiam = 35.0;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         p_oRec = p_oShort[5] [20];
         p_oShort[5] [20] = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oShort[5] [20]->nextLink = p_oRec; p_oShort[5] [20]->next = p_oRec->thisTree;
         p_oRec->prevLink = p_oShort[5] [20]; p_oRec->prev = p_oShort[5] [20]->thisTree;
         p_oShortestHD[5] [20] [5] = p_oTreeSet[iTreeNum];
         p_oTallestHD[5] [20] [5] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 30
       fX = 45.0; fY = 167.0; iSp = 0; iTp = clTreePopulation::adult; fDiam = 15.0;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         p_oRec = p_oShort[5] [20];
         p_oShort[5] [20] = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oShort[5] [20]->nextLink = p_oRec; p_oShort[5] [20]->next = p_oRec->thisTree;
         p_oRec->prevLink = p_oShort[5] [20]; p_oRec->prev = p_oShort[5] [20]->thisTree;
         p_oShortestHD[5] [20] [3] = p_oTreeSet[iTreeNum];
         p_oTallestHD[5] [20] [3] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 31
       fX = 47.0; fY = 164.0; iSp = 2; iTp = clTreePopulation::adult; fDiam = 50.0;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         p_oRec = p_oTall[5] [20];
         p_oTall[5] [20] = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oTall[5] [20]->prevLink = p_oRec; p_oTall[5] [20]->prev = p_oRec->thisTree;
         p_oRec->nextLink = p_oTall[5] [20]; p_oRec->next = p_oTall[5] [20]->thisTree;
         p_oTallestHD[5] [20] [8] = p_oTreeSet[iTreeNum];
         p_oShortestHD[5] [20] [8] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 32
       fX = 43.0; fY = 161.0; iSp = 1; iTp = clTreePopulation::adult; fDiam = 95.0;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         p_oRec = p_oTall[5] [20];
         p_oTall[5] [20] = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oTall[5] [20]->prevLink = p_oRec; p_oTall[5] [20]->prev = p_oRec->thisTree;
         p_oRec->nextLink = p_oTall[5] [20]; p_oRec->next = p_oTall[5] [20]->thisTree;
         p_oTallestHD[5] [20] [8] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 33
       fX = 41.0; fY = 162.0; iSp = 0; iTp = clTreePopulation::adult; fDiam = 100.0;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         p_oRec = p_oTall[5] [20];
         p_oTall[5] [20] = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oTall[5] [20]->prevLink = p_oRec; p_oTall[5] [20]->prev = p_oRec->thisTree;
         p_oRec->nextLink = p_oTall[5] [20]; p_oRec->next = p_oTall[5] [20]->thisTree;
         p_oTallestHD[5] [20] [9] = p_oTreeSet[iTreeNum];
         p_oShortestHD[5] [20] [9] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 34
       fX = 43.5; fY = 165.6; iSp = 2; iTp = clTreePopulation::adult; fDiam = 33.0;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         //Get the tallest in height div 5 - this will be inserted after
         p_oNextRec = p_oTall[5] [20];
         while ( p_oNextRec )
         {
           if ( p_oNextRec->thisTree == p_oTallestHD[5] [20] [5] ) break;
           else
             p_oNextRec = p_oNextRec->prevLink;
         }
         p_oRec = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oRec->prevLink = p_oNextRec; p_oRec->prev = p_oNextRec->thisTree;
         p_oRec->nextLink = p_oNextRec->nextLink; p_oRec->next = p_oNextRec->next;
         p_oNextRec->nextLink->prevLink = p_oRec; p_oNextRec->nextLink->prev = p_oRec->thisTree;
         p_oNextRec->nextLink = p_oRec; p_oNextRec->next = p_oRec->thisTree;
         p_oShortestHD[5] [20] [6] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 35
       fX = 41.8; fY = 165.3; iSp = 1; iTp = clTreePopulation::adult; fDiam = 37.0;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         p_oNextRec = p_oRec; //p_oRec still has the record for tree 34 in it - insert new one before
         p_oRec = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oRec->nextLink = p_oNextRec; p_oRec->next = p_oNextRec->thisTree;
         p_oRec->prevLink = p_oNextRec->prevLink; p_oRec->prev = p_oNextRec->prev;
         p_oNextRec->prevLink->nextLink = p_oRec; p_oNextRec->prevLink->next = p_oRec->thisTree;
         p_oNextRec->prevLink = p_oRec; p_oNextRec->prev = p_oRec->thisTree;
         p_oTallestHD[5] [20] [5] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 36
       fX = 44.5; fY = 167.3; iSp = 0; iTp = clTreePopulation::adult; fDiam = 16.0;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         //Get the tallest tree in height div 3 - this will be inserted after
         p_oNextRec = p_oTall[5] [20];
         while ( p_oNextRec )
         {
           if ( p_oNextRec->thisTree == p_oTallestHD[5] [20] [3] ) break;
           else
             p_oNextRec = p_oNextRec->prevLink;
         }
         p_oRec = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oRec->prevLink = p_oNextRec; p_oRec->prev = p_oNextRec->thisTree;
         p_oRec->nextLink = p_oNextRec->nextLink; p_oRec->next = p_oNextRec->next;
         p_oNextRec->nextLink->prevLink = p_oRec; p_oNextRec->nextLink->prev = p_oRec->thisTree;
         p_oNextRec->nextLink = p_oRec; p_oNextRec->next = p_oRec->thisTree;
         p_oTallestHD[5] [20] [3] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 37
       fX = 2.0; fY = 4.0; iSp = 1; iTp = clTreePopulation::adult; fDiam = 10.0;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table - leave previous and next links as NULL
         p_oShort[0] [0] = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oTall[0] [0] = p_oShort[0] [0];
         p_oShortestHD[0] [0] [2] = p_oTreeSet[iTreeNum];
         p_oTallestHD[0] [0] [2] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 38
       fX = 157.0; fY = 198.0; iSp = 0; iTp = clTreePopulation::adult; fDiam = 9.8;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table - leave previous and next links as NULL
         p_oShort[19] [24] = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oTall[19] [24] = p_oShort[0] [0];
         p_oShortestHD[19] [24] [2] = p_oTreeSet[iTreeNum];
         p_oTallestHD[19] [24] [2] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 39
       fX = 112.2; fY = 60.0; iSp = 2; iTp = clTreePopulation::adult; fDiam = 25.0;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         //Get tree 8 - this will be inserted after
         p_oNextRec = p_oTall[14] [7];
         while ( p_oNextRec )
         {
           if ( p_oNextRec->thisTree == p_oTreeSet[7] ) break;
           else
             p_oNextRec = p_oNextRec->prevLink;
         }
         p_oRec = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oRec->prevLink = p_oNextRec; p_oRec->prev = p_oNextRec->thisTree;
         p_oRec->nextLink = p_oNextRec->nextLink; p_oRec->next = p_oNextRec->next;
         p_oNextRec->nextLink->prevLink = p_oRec; p_oNextRec->nextLink->prev = p_oRec->thisTree;
         p_oNextRec->nextLink = p_oRec; p_oNextRec->next = p_oRec->thisTree;
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 40
       fX = 113.5; fY = 60.5; iSp = 0; iTp = clTreePopulation::adult; fDiam = 25.0;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         //Get tree 9 - this will be inserted after
         p_oNextRec = p_oTall[14] [7];
         while ( p_oNextRec )
         {
           if ( p_oNextRec->thisTree == p_oTreeSet[8] ) break;
           else
             p_oNextRec = p_oNextRec->prevLink;
         }
         p_oRec = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oRec->prevLink = p_oNextRec; p_oRec->prev = p_oNextRec->thisTree;
         p_oRec->nextLink = p_oNextRec->nextLink; p_oRec->next = p_oNextRec->next;
         p_oNextRec->nextLink->prevLink = p_oRec; p_oNextRec->nextLink->prev = p_oRec->thisTree;
         p_oNextRec->nextLink = p_oRec; p_oNextRec->next = p_oRec->thisTree;
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 41
       fX = 113.7; fY = 60.7; iSp = 1; iTp = clTreePopulation::adult; fDiam = 35.0;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         //Get tree 10 - this will be inserted after
         p_oNextRec = p_oTall[14] [7];
         while ( p_oNextRec )
         {
           if ( p_oNextRec->thisTree == p_oTreeSet[9] ) break;
           else
             p_oNextRec = p_oNextRec->prevLink;
         }
         p_oRec = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oRec->prevLink = p_oNextRec; p_oRec->prev = p_oNextRec->thisTree;
         p_oRec->nextLink = p_oNextRec->nextLink; p_oRec->next = p_oNextRec->next;
         p_oNextRec->nextLink->prevLink = p_oRec; p_oNextRec->nextLink->prev = p_oRec->thisTree;
         p_oNextRec->nextLink = p_oRec; p_oNextRec->next = p_oRec->thisTree;
         p_oTallestHD[14] [7] [5] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 42
       fX = 20.58472; fY = 0.567627; iSp = 0; iTp = clTreePopulation::seedling; fDiam = 0.1;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table - leave previous and next links as NULL
         p_oShort[2] [0] = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oTall[2] [0] = p_oShort[2] [0];
         p_oShortestHD[2] [0] [0] = p_oTreeSet[iTreeNum];
         p_oTallestHD[2] [0] [0] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 43
       fX = 23.01001; fY = 0.823975; iSp = 1; iTp = clTreePopulation::seedling; fDiam = 0.5;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         p_oRec = p_oTall[2] [0];
         p_oTall[2] [0] = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oTall[2] [0]->prevLink = p_oRec; p_oTall[2] [0]->prev = p_oRec->thisTree;
         p_oRec->nextLink = p_oTall[2] [0]; p_oRec->next = p_oTall[2] [0]->thisTree;
         p_oTallestHD[2] [0] [0] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 44
       fX = 16.1987; fY = 0.964355; iSp = 2; iTp = clTreePopulation::seedling; fDiam = 0.7;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         p_oRec = p_oTall[2] [0];
         p_oTall[2] [0] = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oTall[2] [0]->prevLink = p_oRec; p_oTall[2] [0]->prev = p_oRec->thisTree;
         p_oRec->nextLink = p_oTall[2] [0]; p_oRec->next = p_oTall[2] [0]->thisTree;
         p_oTallestHD[2] [0] [0] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 45
       fX = 16.5283; fY = 1.01929; iSp = 0; iTp = clTreePopulation::sapling; fDiam = 1.79;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         p_oRec = p_oTall[2] [0];
         p_oTall[2] [0] = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oTall[2] [0]->prevLink = p_oRec; p_oTall[2] [0]->prev = p_oRec->thisTree;
         p_oRec->nextLink = p_oTall[2] [0]; p_oRec->next = p_oTall[2] [0]->thisTree;
         p_oTallestHD[2] [0] [0] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 46
       fX = 16.9312; fY = 1.14746; iSp = 1; iTp = clTreePopulation::sapling; fDiam = 4.3457;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         p_oRec = p_oTall[2] [0];
         p_oTall[2] [0] = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oTall[2] [0]->prevLink = p_oRec; p_oTall[2] [0]->prev = p_oRec->thisTree;
         p_oRec->nextLink = p_oTall[2] [0]; p_oRec->next = p_oTall[2] [0]->thisTree;
         p_oTallestHD[2] [0] [1] = p_oTreeSet[iTreeNum];
         p_oShortestHD[2] [0] [1] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 47
       fX = 17.0471; fY = 1.49536; iSp = 2; iTp = clTreePopulation::sapling; fDiam = 3.00903;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         p_oRec = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oTall[2] [0]->prevLink->nextLink = p_oRec; p_oTall[2] [0]->prevLink->next = p_oRec->thisTree;
         p_oRec->prevLink = p_oTall[2] [0]->prevLink; p_oRec->prev = p_oTall[2] [0]->prev;
         p_oRec->nextLink = p_oTall[2] [0]; p_oRec->next = p_oTall[2] [0]->thisTree;
         p_oTall[2] [0]->prevLink = p_oRec; p_oTall[2] [0]->prev = p_oRec->thisTree;
         p_oShortestHD[2] [0] [1] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 48
       fX = 17.2241; fY = 1.65405; iSp = 0; iTp = clTreePopulation::sapling; fDiam = 6.01807;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         p_oRec = p_oTall[2] [0];
         p_oTall[2] [0] = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oTall[2] [0]->prevLink = p_oRec; p_oTall[2] [0]->prev = p_oRec->thisTree;
         p_oRec->nextLink = p_oTall[2] [0]; p_oRec->next = p_oTall[2] [0]->thisTree;
         p_oTallestHD[2] [0] [1] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 49
       fX = 17.8162; fY = 1.75781; iSp = 1; iTp = clTreePopulation::adult; fDiam = 10.0;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         p_oRec = p_oTall[2] [0];
         p_oTall[2] [0] = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oTall[2] [0]->prevLink = p_oRec; p_oTall[2] [0]->prev = p_oRec->thisTree;
         p_oRec->nextLink = p_oTall[2] [0]; p_oRec->next = p_oTall[2] [0]->thisTree;
         p_oTallestHD[2] [0] [2] = p_oTreeSet[iTreeNum];
         p_oShortestHD[2] [0] [2] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 50
       fX = 18.0664; fY = 1.89819; iSp = 2; iTp = clTreePopulation::adult; fDiam = 10.1;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         p_oRec = p_oTall[2] [0];
         p_oTall[2] [0] = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oTall[2] [0]->prevLink = p_oRec; p_oTall[2] [0]->prev = p_oRec->thisTree;
         p_oRec->nextLink = p_oTall[2] [0]; p_oRec->next = p_oTall[2] [0]->thisTree;
         p_oTallestHD[2] [0] [2] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 51
       fX = 18.3167; fY = 2.23389; iSp = 0; iTp = clTreePopulation::sapling; fDiam = 9.87;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         p_oRec = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oTall[2] [0]->prevLink->nextLink = p_oRec; p_oTall[2] [0]->prevLink->next = p_oRec->thisTree;
         p_oRec->prevLink = p_oTall[2] [0]->prevLink; p_oRec->prev = p_oTall[2] [0]->prev;
         p_oRec->nextLink = p_oTall[2] [0]; p_oRec->next = p_oTall[2] [0]->thisTree;
         p_oTall[2] [0]->prevLink = p_oRec; p_oTall[2] [0]->prev = p_oRec->thisTree;
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 52
       fX = 18.3838; fY = 2.34985; iSp = 1; iTp = clTreePopulation::adult; fDiam = 12.5847;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         p_oRec = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oTall[2] [0]->prevLink->nextLink = p_oRec; p_oTall[2] [0]->prevLink->next = p_oRec->thisTree;
         p_oRec->prevLink = p_oTall[2] [0]->prevLink; p_oRec->prev = p_oTall[2] [0]->prev;
         p_oRec->nextLink = p_oTall[2] [0]; p_oRec->next = p_oTall[2] [0]->thisTree;
         p_oTall[2] [0]->prevLink = p_oRec; p_oTall[2] [0]->prev = p_oRec->thisTree;
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 53
       fX = 18.6523; fY = 2.70996; iSp = 2; iTp = clTreePopulation::adult; fDiam = 14.1987;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         p_oRec = p_oTall[2] [0];
         p_oTall[2] [0] = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oTall[2] [0]->prevLink = p_oRec; p_oTall[2] [0]->prev = p_oRec->thisTree;
         p_oRec->nextLink = p_oTall[2] [0]; p_oRec->next = p_oTall[2] [0]->thisTree;
         p_oTallestHD[2] [0] [3] = p_oTreeSet[iTreeNum];
         p_oShortestHD[2] [0] [3] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 54
       fX = 18.7866; fY = 2.72217; iSp = 0; iTp = clTreePopulation::adult; fDiam = 15.5283;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         p_oRec = p_oTall[2] [0];
         p_oTall[2] [0] = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oTall[2] [0]->prevLink = p_oRec; p_oTall[2] [0]->prev = p_oRec->thisTree;
         p_oRec->nextLink = p_oTall[2] [0]; p_oRec->next = p_oTall[2] [0]->thisTree;
         p_oTallestHD[2] [0] [3] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 55
       fX = 18.9331; fY = 2.87476; iSp = 1; iTp = clTreePopulation::adult; fDiam = 16.9312;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         //Get the tallest in height div 2 - this will be inserted after
         p_oNextRec = p_oTall[2] [0];
         while ( p_oNextRec )
         {
           if ( p_oNextRec->thisTree == p_oTallestHD[2] [0] [2] ) break;
           else
             p_oNextRec = p_oNextRec->prevLink;
         }
         p_oRec = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oRec->prevLink = p_oNextRec; p_oRec->prev = p_oNextRec->thisTree;
         p_oRec->nextLink = p_oNextRec->nextLink; p_oRec->next = p_oNextRec->next;
         p_oNextRec->nextLink->prevLink = p_oRec; p_oNextRec->nextLink->prev = p_oRec->thisTree;
         p_oNextRec->nextLink = p_oRec; p_oNextRec->next = p_oRec->thisTree;
         p_oShortestHD[2] [0] [3] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 56
       fX = 19.1833; fY = 2.88086; iSp = 2; iTp = clTreePopulation::adult; fDiam = 17.0471;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         p_oRec = p_oTall[2] [0];
         p_oTall[2] [0] = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oTall[2] [0]->prevLink = p_oRec; p_oTall[2] [0]->prev = p_oRec->thisTree;
         p_oRec->nextLink = p_oTall[2] [0]; p_oRec->next = p_oTall[2] [0]->thisTree;
         p_oTallestHD[2] [0] [4] = p_oTreeSet[iTreeNum];
         p_oShortestHD[2] [0] [4] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 57
       fX = 19.6533; fY = 3.00903; iSp = 0; iTp = clTreePopulation::adult; fDiam = 18.0664;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         p_oRec = p_oTall[2] [0];
         p_oTall[2] [0] = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oTall[2] [0]->prevLink = p_oRec; p_oTall[2] [0]->prev = p_oRec->thisTree;
         p_oRec->nextLink = p_oTall[2] [0]; p_oRec->next = p_oTall[2] [0]->thisTree;
         p_oTallestHD[2] [0] [4] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 58
       fX = 20.0317; fY = 3.23486; iSp = 1; iTp = clTreePopulation::adult; fDiam = 23.4741;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         p_oRec = p_oTall[2] [0];
         p_oTall[2] [0] = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oTall[2] [0]->prevLink = p_oRec; p_oTall[2] [0]->prev = p_oRec->thisTree;
         p_oRec->nextLink = p_oTall[2] [0]; p_oRec->next = p_oTall[2] [0]->thisTree;
         p_oTallestHD[2] [0] [4] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 59
       fX = 20.0989; fY = 3.92456; iSp = 2; iTp = clTreePopulation::adult; fDiam = 17.2241;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         //Get tree 56 - this will be inserted after
         p_oNextRec = p_oTall[2] [0];
         while ( p_oNextRec )
         {
           if ( p_oNextRec->thisTree == p_oTreeSet[55] ) break;
           else
             p_oNextRec = p_oNextRec->prevLink;
         }
         p_oRec = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oRec->prevLink = p_oNextRec; p_oRec->prev = p_oNextRec->thisTree;
         p_oRec->nextLink = p_oNextRec->nextLink; p_oRec->next = p_oNextRec->next;
         p_oNextRec->nextLink->prevLink = p_oRec; p_oNextRec->nextLink->prev = p_oRec->thisTree;
         p_oNextRec->nextLink = p_oRec; p_oNextRec->next = p_oRec->thisTree;
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 60
       fX = 20.2637; fY = 4.01001; iSp = 0; iTp = clTreePopulation::adult; fDiam = 23.4741;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         p_oRec = p_oTall[2] [0];
         p_oTall[2] [0] = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oTall[2] [0]->prevLink = p_oRec; p_oTall[2] [0]->prev = p_oRec->thisTree;
         p_oRec->nextLink = p_oTall[2] [0]; p_oRec->next = p_oTall[2] [0]->thisTree;
         p_oTallestHD[2] [0] [5] = p_oTreeSet[iTreeNum];
         p_oShortestHD[2] [0] [5] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 61
       fX = 20.6055; fY = 4.32129; iSp = 1; iTp = clTreePopulation::adult; fDiam = 35.3882;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         p_oRec = p_oTall[2] [0];
         p_oTall[2] [0] = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oTall[2] [0]->prevLink = p_oRec; p_oTall[2] [0]->prev = p_oRec->thisTree;
         p_oRec->nextLink = p_oTall[2] [0]; p_oRec->next = p_oTall[2] [0]->thisTree;
         p_oTallestHD[2] [0] [5] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 62
       fX = 20.8618; fY = 4.3457; iSp = 2; iTp = clTreePopulation::adult; fDiam = 26.886;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         p_oRec = p_oTall[2] [0];
         p_oTall[2] [0] = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oTall[2] [0]->prevLink = p_oRec; p_oTall[2] [0]->prev = p_oRec->thisTree;
         p_oRec->nextLink = p_oTall[2] [0]; p_oRec->next = p_oTall[2] [0]->thisTree;
         p_oTallestHD[2] [0] [5] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 63
       fX = 21.0754; fY = 4.93164; iSp = 0; iTp = clTreePopulation::adult; fDiam = 39.5691;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         p_oRec = p_oTall[2] [0];
         p_oTall[2] [0] = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oTall[2] [0]->prevLink = p_oRec; p_oTall[2] [0]->prev = p_oRec->thisTree;
         p_oRec->nextLink = p_oTall[2] [0]; p_oRec->next = p_oTall[2] [0]->thisTree;
         p_oTallestHD[2] [0] [6] = p_oTreeSet[iTreeNum];
         p_oShortestHD[2] [0] [6] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 64
       fX = 21.1365; fY = 5.04761; iSp = 1; iTp = clTreePopulation::adult; fDiam = 44.9097;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         p_oRec = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oTall[2] [0]->prevLink->nextLink = p_oRec; p_oTall[2] [0]->prevLink->next = p_oRec->thisTree;
         p_oRec->prevLink = p_oTall[2] [0]->prevLink; p_oRec->prev = p_oTall[2] [0]->prev;
         p_oRec->nextLink = p_oTall[2] [0]; p_oRec->next = p_oTall[2] [0]->thisTree;
         p_oTall[2] [0]->prevLink = p_oRec; p_oTall[2] [0]->prev = p_oRec->thisTree;
         p_oShortestHD[2] [0] [6] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 65
       fX = 21.3013; fY = 5.16968; iSp = 2; iTp = clTreePopulation::adult; fDiam = 33.728;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         p_oRec = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oTall[2] [0]->prevLink->nextLink = p_oRec; p_oTall[2] [0]->prevLink->next = p_oRec->thisTree;
         p_oRec->prevLink = p_oTall[2] [0]->prevLink; p_oRec->prev = p_oTall[2] [0]->prev;
         p_oRec->nextLink = p_oTall[2] [0]; p_oRec->next = p_oTall[2] [0]->thisTree;
         p_oTall[2] [0]->prevLink = p_oRec; p_oTall[2] [0]->prev = p_oRec->thisTree;
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 66
       fX = 21.521; fY = 5.58472; iSp = 0; iTp = clTreePopulation::adult; fDiam = 54.2786;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         p_oRec = p_oTall[2] [0];
         p_oTall[2] [0] = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oTall[2] [0]->prevLink = p_oRec; p_oTall[2] [0]->prev = p_oRec->thisTree;
         p_oRec->nextLink = p_oTall[2] [0]; p_oRec->next = p_oTall[2] [0]->thisTree;
         p_oTallestHD[2] [0] [7] = p_oTreeSet[iTreeNum];
         p_oShortestHD[2] [0] [7] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 67
       fX = 21.6125; fY = 6.01807; iSp = 1; iTp = clTreePopulation::adult; fDiam = 56.7627;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         p_oRec = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oTall[2] [0]->prevLink->nextLink = p_oRec; p_oTall[2] [0]->prevLink->next = p_oRec->thisTree;
         p_oRec->prevLink = p_oTall[2] [0]->prevLink; p_oRec->prev = p_oTall[2] [0]->prev;
         p_oRec->nextLink = p_oTall[2] [0]; p_oRec->next = p_oTall[2] [0]->thisTree;
         p_oTall[2] [0]->prevLink = p_oRec; p_oTall[2] [0]->prev = p_oRec->thisTree;
         p_oShortestHD[2] [0] [7] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 68
       fX = 21.9727; fY = 6.43311; iSp = 2; iTp = clTreePopulation::adult; fDiam = 43.3838;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         p_oRec = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oTall[2] [0]->prevLink->nextLink = p_oRec; p_oTall[2] [0]->prevLink->next = p_oRec->thisTree;
         p_oRec->prevLink = p_oTall[2] [0]->prevLink; p_oRec->prev = p_oTall[2] [0]->prev;
         p_oRec->nextLink = p_oTall[2] [0]; p_oRec->next = p_oTall[2] [0]->thisTree;
         p_oTall[2] [0]->prevLink = p_oRec; p_oTall[2] [0]->prev = p_oRec->thisTree;
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 69
       fX = 22.1191; fY = 6.73218; iSp = 1; iTp = clTreePopulation::adult; fDiam = 56.7566;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         //Get tallest in height div 6 - this will be inserted after
         p_oNextRec = p_oTall[2] [0];
         while ( p_oNextRec )
         {
           if ( p_oNextRec->thisTree == p_oTallestHD[2] [0] [6] ) break;
           else
             p_oNextRec = p_oNextRec->prevLink;
         }
         p_oRec = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oRec->prevLink = p_oNextRec; p_oRec->prev = p_oNextRec->thisTree;
         p_oRec->nextLink = p_oNextRec->nextLink; p_oRec->next = p_oNextRec->next;
         p_oNextRec->nextLink->prevLink = p_oRec; p_oNextRec->nextLink->prev = p_oRec->thisTree;
         p_oNextRec->nextLink = p_oRec; p_oNextRec->next = p_oRec->thisTree;
         p_oShortestHD[2] [0] [7] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 70
       fX = 22.2412; fY = 7.10449; iSp = 0; iTp = clTreePopulation::adult; fDiam = 58.1299;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         p_oRec = p_oTall[2] [0];
         p_oTall[2] [0] = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oTall[2] [0]->prevLink = p_oRec; p_oTall[2] [0]->prev = p_oRec->thisTree;
         p_oRec->nextLink = p_oTall[2] [0]; p_oRec->next = p_oTall[2] [0]->thisTree;
         p_oTallestHD[2] [0] [8] = p_oTreeSet[iTreeNum];
         p_oShortestHD[2] [0] [8] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 71
       fX = 22.2717; fY = 7.15332; iSp = 2; iTp = clTreePopulation::adult; fDiam = 50.2742;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         p_oRec = p_oTall[2] [0];
         p_oTall[2] [0] = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oTall[2] [0]->prevLink = p_oRec; p_oTall[2] [0]->prev = p_oRec->thisTree;
         p_oRec->nextLink = p_oTall[2] [0]; p_oRec->next = p_oTall[2] [0]->thisTree;
         p_oTallestHD[2] [0] [8] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 72
       fX = 22.29; fY = 7.47681; iSp = 0; iTp = clTreePopulation::adult; fDiam = 63.2141;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         p_oRec = p_oTall[2] [0];
         p_oTall[2] [0] = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oTall[2] [0]->prevLink = p_oRec; p_oTall[2] [0]->prev = p_oRec->thisTree;
         p_oRec->nextLink = p_oTall[2] [0]; p_oRec->next = p_oTall[2] [0]->thisTree;
         p_oTallestHD[2] [0] [8] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 73
       fX = 22.3267; fY = 7.8064; iSp = 1; iTp = clTreePopulation::adult; fDiam = 70.9778;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         //Get the tallest in height div 7 - this will be inserted after
         p_oNextRec = p_oTall[2] [0];
         while ( p_oNextRec )
         {
           if ( p_oNextRec->thisTree == p_oTallestHD[2] [0] [7] ) break;
           else
             p_oNextRec = p_oNextRec->prevLink;
         }
         p_oRec = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oRec->prevLink = p_oNextRec; p_oRec->prev = p_oNextRec->thisTree;
         p_oRec->nextLink = p_oNextRec->nextLink; p_oRec->next = p_oNextRec->next;
         p_oNextRec->nextLink->prevLink = p_oRec; p_oNextRec->nextLink->prev = p_oRec->thisTree;
         p_oNextRec->nextLink = p_oRec; p_oNextRec->next = p_oRec->thisTree;
         p_oShortestHD[2] [0] [8] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 74
       fX = 22.522; fY = 7.8186; iSp = 2; iTp = clTreePopulation::adult; fDiam = 77.9663;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         p_oRec = p_oTall[2] [0];
         p_oTall[2] [0] = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oTall[2] [0]->prevLink = p_oRec; p_oTall[2] [0]->prev = p_oRec->thisTree;
         p_oRec->nextLink = p_oTall[2] [0]; p_oRec->next = p_oTall[2] [0]->thisTree;
         p_oShortestHD[2] [0] [9] = p_oTreeSet[iTreeNum];
         p_oTallestHD[2] [0] [9] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 75
       fX = 22.6135; fY = 7.91626; iSp = 0; iTp = clTreePopulation::adult; fDiam = 101.978;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         p_oRec = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oTall[2] [0]->prevLink->nextLink = p_oRec; p_oTall[2] [0]->prevLink->next = p_oRec->thisTree;
         p_oRec->prevLink = p_oTall[2] [0]->prevLink; p_oRec->prev = p_oTall[2] [0]->prev;
         p_oRec->nextLink = p_oTall[2] [0]; p_oRec->next = p_oTall[2] [0]->thisTree;
         p_oTall[2] [0]->prevLink = p_oRec; p_oTall[2] [0]->prev = p_oRec->thisTree;
         p_oShortestHD[2] [0] [9] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 76
       fX = 22.644; fY = 7.97119; iSp = 1; iTp = clTreePopulation::adult; fDiam = 116.852;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         p_oNextRec = p_oRec;
         p_oRec = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oNextRec->prevLink->nextLink = p_oRec; p_oNextRec->prevLink->next = p_oRec->thisTree;
         p_oRec->prevLink = p_oNextRec->prevLink; p_oRec->prev = p_oNextRec->prev;
         p_oRec->nextLink = p_oNextRec; p_oRec->next = p_oNextRec->thisTree;
         p_oNextRec->prevLink = p_oRec; p_oNextRec->prev = p_oRec->thisTree;
         p_oShortestHD[2] [0] [9] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
       iTreeNum++;

       //--------->Create tree 77
       fX = 22.876; fY = 7.9; iSp = 2; iTp = clTreePopulation::adult; fDiam = 88.5498;
       p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
       if ( bUpdateHashTable )
       {
         //Put the tree in the hash table
         p_oRec = p_oTall[2] [0];
         p_oTall[2] [0] = new clFakeLinkedList( p_oTreeSet[iTreeNum] );
         p_oTall[2] [0]->prevLink = p_oRec; p_oTall[2] [0]->prev = p_oRec->thisTree;
         p_oRec->nextLink = p_oTall[2] [0]; p_oRec->next = p_oTall[2] [0]->thisTree;
         p_oTallestHD[2] [0] [10] = p_oTreeSet[iTreeNum];
         p_oShortestHD[2] [0] [10] = p_oTreeSet[iTreeNum];
       }
       if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
}

//---------------------------------------------------------------------------

//////////////////////////////////////////////////////////////////////////////
//     LoadNormal2Trees()
//////////////////////////////////////////////////////////////////////////////
void clTestTreePopulation::LoadTrees2( clTreePopulation * p_oPop, clTree * * p_oTreeSet, bool bFullCheck )
{

  float fX, fY, fDiam; //for creating trees
  short int iSp, iTp, //for creating trees
       iTreeNum = 77; //helps with tree indexes - reduces typing errors

  //***********************************************************
  //Create the trees
  //***********************************************************
  //--------->Create tree 78
  fX = 161.0; fY = 135.0; iSp = 2; iTp = clTreePopulation::adult; fDiam = 45.0;
  p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
  //Check to make sure this tree was put in the correct grid cell
  if ( bFullCheck )
  {
    CPPUNIT_ASSERT( p_oPop->mp_oTreeShortest[20] [16] [7] == p_oTreeSet[iTreeNum] );
  }
  iTreeNum++;

  //--------->Create tree 79
  fX = 159.0; fY = 201.0; iSp = 0; iTp = clTreePopulation::sapling; fDiam = 9.79;
  p_oTreeSet[iTreeNum] = p_oPop->CreateTree( fX, fY, iSp, iTp, fDiam );
  //Check to make sure this tree was put in the correct grid cell
  if ( bFullCheck )
  {
    CPPUNIT_ASSERT( p_oPop->mp_oTreeShortest[19] [25] [2] == p_oTreeSet[iTreeNum] );
  }
}

//---------------------------------------------------------------------------

//////////////////////////////////////////////////////////////////////////////
//     UpdateHashTableTrees()
/////////////////////////////////////////////////////////////////////////////
void clTestTreePopulation::UpdateHashTableTrees( clTreePopulation * p_oPop, clTree * * * * p_oShortestHD,
clTree * * * * p_oTallestHD, clFakeLinkedList * * * p_oShort, clFakeLinkedList * * * p_oTall, clTree * * p_oTreeSet,
int iNumXCells, int iNumYCells, bool bFullCheck, bool bUpdateNow, bool bUpdateAllometry )
{
  clFakeLinkedList * p_oRec, * p_oNextRec, * p_oPrevRec, * p_oHolderRec;
  float fDiam, fHeight; //for updating trees
  short int iSp, iType;

  //****************************************
  //Update tree 76
  //****************************************
  fHeight = 38.0; iSp = p_oTreeSet[75]->GetSpecies(); iType = p_oTreeSet[75]->GetType();
  p_oTreeSet[75]->SetValue( p_oPop->GetHeightCode( iSp, iType ), fHeight, bUpdateNow, bUpdateAllometry );
  //Get the rec for this tree
  p_oRec = p_oTall[2] [0];
  while ( p_oRec )
  {
    if ( p_oRec->thisTree == p_oTreeSet[75] ) break;
    else
      p_oRec = p_oRec->prevLink;
  }
  p_oShortestHD[2] [0] [9] = p_oTreeSet[74];
  //Swap with next
  p_oNextRec = p_oRec->nextLink;
  p_oPrevRec = p_oRec->prevLink;
  p_oNextRec->nextLink->prevLink = p_oRec; p_oNextRec->nextLink->prev = p_oRec->thisTree;
  p_oRec->nextLink = p_oNextRec->nextLink; p_oRec->next = p_oNextRec->next;
  p_oRec->prevLink = p_oNextRec; p_oRec->prev = p_oNextRec->thisTree;
  p_oNextRec->nextLink = p_oRec; p_oNextRec->next = p_oRec->thisTree;
  p_oNextRec->prevLink = p_oPrevRec; p_oNextRec->prev = p_oPrevRec->thisTree;
  p_oPrevRec->nextLink = p_oNextRec; p_oPrevRec->next = p_oNextRec->thisTree;
  if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );


  //****************************************
  //Update tree 49
  //****************************************
  if (bUpdateAllometry) {
    fDiam = 12.671; iSp = p_oTreeSet[48]->GetSpecies(); iType = p_oTreeSet[48]->GetType();
    p_oTreeSet[48]->SetValue( p_oPop->GetDbhCode( iSp, iType ), fDiam, bUpdateNow, bUpdateAllometry );
  } else {
    //Update the height directly
    fHeight = 11.4; iSp = p_oTreeSet[48]->GetSpecies(); iType = p_oTreeSet[48]->GetType();
    p_oTreeSet[48]->SetValue( p_oPop->GetHeightCode( iSp, iType ), fHeight, bUpdateNow, bUpdateAllometry );
  }
  //Get the rec for this tree
  p_oRec = p_oShort[2] [0];
  while ( p_oRec )
  {
    if ( p_oRec->thisTree == p_oTreeSet[48] ) break;
    else
      p_oRec = p_oRec->nextLink;
  }
  p_oShortestHD[2] [0] [2] = p_oTreeSet[50];
  p_oNextRec = p_oRec->nextLink; //Close the gap left
  p_oRec->prevLink->nextLink = p_oNextRec; p_oRec->prevLink->next = p_oNextRec->thisTree;
  p_oNextRec->prevLink = p_oRec->prevLink; p_oNextRec->prev = p_oRec->prev;
  //Get the rec for tree 52 - new previous
  p_oPrevRec = p_oTall[2] [0];
  while ( p_oPrevRec )
  {
    if ( p_oPrevRec->thisTree == p_oTreeSet[51] ) break;
    else
      p_oPrevRec = p_oPrevRec->prevLink;
  }
  p_oNextRec = p_oPrevRec->nextLink;
  p_oRec->nextLink = p_oNextRec; p_oRec->next = p_oNextRec->thisTree;
  p_oRec->prevLink = p_oPrevRec; p_oRec->prev = p_oPrevRec->thisTree;
  p_oPrevRec->nextLink = p_oRec; p_oPrevRec->next = p_oRec->thisTree;
  p_oNextRec->prevLink = p_oRec; p_oNextRec->prev = p_oRec->thisTree;
  if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  //****************************************
  //Update tree 42
  //****************************************
  fHeight = 1.0; iSp = p_oTreeSet[41]->GetSpecies(); iType = p_oTreeSet[41]->GetType();
  p_oTreeSet[41]->SetValue( p_oPop->GetHeightCode( iSp, iType ), fHeight, bUpdateNow, bUpdateAllometry );
  //Get rec for tree 43 - new shortest
  p_oHolderRec = p_oShort[2] [0];
  while ( p_oHolderRec )
  {
    if ( p_oHolderRec->thisTree == p_oTreeSet[42] ) break;
    else
      p_oHolderRec = p_oHolderRec->nextLink;
  }
  //Get the rec for this tree
  p_oRec = p_oShort[2] [0];
  p_oNextRec = p_oRec->nextLink; //Close the gap left
  p_oNextRec->prevLink = NULL; p_oNextRec->prev = NULL;
  //Get the rec for tree 44 - new previous
  p_oPrevRec = p_oShort[2] [0];
  while ( p_oPrevRec )
  {
    if ( p_oPrevRec->thisTree == p_oTreeSet[43] ) break;
    else
      p_oPrevRec = p_oPrevRec->nextLink;
  }
  p_oNextRec = p_oPrevRec->nextLink;
  p_oRec->nextLink = p_oNextRec; p_oRec->next = p_oNextRec->thisTree;
  p_oRec->prevLink = p_oPrevRec; p_oRec->prev = p_oPrevRec->thisTree;
  p_oPrevRec->nextLink = p_oRec; p_oPrevRec->next = p_oRec->thisTree;
  p_oNextRec->prevLink = p_oRec; p_oNextRec->prev = p_oRec->thisTree;
  p_oShortestHD[2] [0] [0] = p_oTreeSet[42];
  p_oShort[2] [0] = p_oHolderRec;
  if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  //****************************************
  //Update tree 75
  //****************************************
  fHeight = 35.0; iSp = p_oTreeSet[74]->GetSpecies(); iType = p_oTreeSet[74]->GetType();
  p_oTreeSet[74]->SetValue( p_oPop->GetHeightCode( iSp, iType ), fHeight, bUpdateNow, bUpdateAllometry );
  p_oShortestHD[2] [0] [9] = p_oTreeSet[75];
  p_oTallestHD[2] [0] [8] = p_oTreeSet[74];
  if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  //****************************************
  //Update tree 56
  //****************************************
  fHeight = 15.7; iSp = p_oTreeSet[55]->GetSpecies(); iType = p_oTreeSet[55]->GetType();
  p_oTreeSet[55]->SetValue( p_oPop->GetHeightCode( iSp, iType ), fHeight, bUpdateNow, bUpdateAllometry );
  p_oShortestHD[2] [0] [4] = p_oTreeSet[58];
  p_oTallestHD[2] [0] [3] = p_oTreeSet[55];
  if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  //****************************************
  //Update tree 69
  //****************************************
  fHeight = 27.0; iSp = p_oTreeSet[68]->GetSpecies(); iType = p_oTreeSet[68]->GetType();
  p_oTreeSet[68]->SetValue( p_oPop->GetHeightCode( iSp, iType ), fHeight, bUpdateNow, bUpdateAllometry );
  p_oShortestHD[2] [0] [7] = p_oTreeSet[66];
  //Get the rec for this tree
  p_oRec = p_oTall[2] [0];
  while ( p_oRec )
  {
    if ( p_oRec->thisTree == p_oTreeSet[68] ) break;
    else
      p_oRec = p_oRec->prevLink;
  }
  p_oNextRec = p_oRec->nextLink; //Close the gap left
  p_oRec->prevLink->nextLink = p_oNextRec; p_oRec->prevLink->next = p_oNextRec->thisTree;
  p_oNextRec->prevLink = p_oRec->prevLink; p_oNextRec->prev = p_oRec->prev;
  //Get the rec for tree 64 - new previous
  p_oPrevRec = p_oTall[2] [0];
  while ( p_oPrevRec )
  {
    if ( p_oPrevRec->thisTree == p_oTreeSet[63] ) break;
    else
      p_oPrevRec = p_oPrevRec->prevLink;
  }
  p_oNextRec = p_oPrevRec->nextLink;
  p_oRec->nextLink = p_oNextRec; p_oRec->next = p_oNextRec->thisTree;
  p_oRec->prevLink = p_oPrevRec; p_oRec->prev = p_oPrevRec->thisTree;
  p_oPrevRec->nextLink = p_oRec; p_oPrevRec->next = p_oRec->thisTree;
  p_oNextRec->prevLink = p_oRec; p_oNextRec->prev = p_oRec->thisTree;
  if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  //****************************************
  //Update tree 77
  //****************************************
  fHeight = 39.0; iSp = p_oTreeSet[76]->GetSpecies(); iType = p_oTreeSet[76]->GetType();
  p_oTreeSet[76]->SetValue( p_oPop->GetHeightCode( iSp, iType ), fHeight, bUpdateNow, bUpdateAllometry );
  p_oTallestHD[2] [0] [9] = p_oTreeSet[73];
  p_oTallestHD[2][0][10]=NULL;
  p_oShortestHD[2][0][10]=NULL;
  //Get rec for tree 74 - new shortest
  p_oHolderRec = p_oTall[2] [0];
  while ( p_oHolderRec )
  {
    if ( p_oHolderRec->thisTree == p_oTreeSet[73] ) break;
    else
      p_oHolderRec = p_oHolderRec->prevLink;
  }
  //Get the rec for this tree
  p_oRec = p_oTall[2] [0];
  //Swap with previous
  p_oPrevRec = p_oRec->prevLink;
  p_oPrevRec->prevLink->nextLink = p_oRec; p_oPrevRec->prevLink->next = p_oRec->thisTree;
  p_oRec->nextLink = p_oPrevRec; p_oRec->next = p_oPrevRec->thisTree;
  p_oRec->prevLink = p_oPrevRec->prevLink; p_oRec->prev = p_oPrevRec->prev;
  p_oPrevRec->nextLink = NULL; p_oPrevRec->next = NULL;
  p_oPrevRec->prevLink = p_oRec; p_oPrevRec->prev = p_oRec->thisTree;
  p_oTall[2] [0] = p_oHolderRec;
  if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  //****************************************
  //Update tree 58
  //****************************************
  fHeight = 17.251; iSp = p_oTreeSet[57]->GetSpecies(); iType = p_oTreeSet[57]->GetType();
  p_oTreeSet[57]->SetValue( p_oPop->GetHeightCode( iSp, iType ), fHeight, bUpdateNow, bUpdateAllometry );
  //Get the rec for this tree
  p_oRec = p_oTall[2] [0];
  while ( p_oRec )
  {
    if ( p_oRec->thisTree == p_oTreeSet[57] ) break;
    else
      p_oRec = p_oRec->prevLink;
  }
  p_oTallestHD[2] [0] [4] = p_oTreeSet[56];
  //Swap with previous
  p_oPrevRec = p_oRec->prevLink;
  p_oNextRec = p_oRec->nextLink;
  p_oPrevRec->prevLink->nextLink = p_oRec; p_oPrevRec->prevLink->next = p_oRec->thisTree;
  p_oRec->nextLink = p_oPrevRec; p_oRec->next = p_oPrevRec->thisTree;
  p_oRec->prevLink = p_oPrevRec->prevLink; p_oRec->prev = p_oPrevRec->prev;
  p_oPrevRec->nextLink = p_oNextRec; p_oPrevRec->next = p_oNextRec->thisTree;
  p_oPrevRec->prevLink = p_oRec; p_oPrevRec->prev = p_oRec->thisTree;
  p_oNextRec->prevLink = p_oPrevRec; p_oNextRec->prev = p_oPrevRec->thisTree;
  if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  //****************************************
  //Update tree 45
  //****************************************
  fHeight = 0.9; iSp = p_oTreeSet[44]->GetSpecies(); iType = p_oTreeSet[44]->GetType();
  p_oTreeSet[44]->SetValue( p_oPop->GetHeightCode( iSp, iType ), fHeight, bUpdateNow, bUpdateAllometry );
  //Get the rec for this tree
  p_oRec = p_oShort[2] [0];
  while ( p_oRec )
  {
    if ( p_oRec->thisTree == p_oTreeSet[44] ) break;
    else
      p_oRec = p_oRec->nextLink;
  }
  p_oTallestHD[2] [0] [0] = p_oTreeSet[41];
  //Swap with previous
  p_oPrevRec = p_oRec->prevLink;
  p_oNextRec = p_oRec->nextLink;
  p_oPrevRec->prevLink->nextLink = p_oRec; p_oPrevRec->prevLink->next = p_oRec->thisTree;
  p_oRec->nextLink = p_oPrevRec; p_oRec->next = p_oPrevRec->thisTree;
  p_oRec->prevLink = p_oPrevRec->prevLink; p_oRec->prev = p_oPrevRec->prev;
  p_oPrevRec->nextLink = p_oNextRec; p_oPrevRec->next = p_oNextRec->thisTree;
  p_oPrevRec->prevLink = p_oRec; p_oPrevRec->prev = p_oRec->thisTree;
  p_oNextRec->prevLink = p_oPrevRec; p_oNextRec->prev = p_oPrevRec->thisTree;
  if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  //****************************************
  //Update tree 42
  //****************************************
  fHeight = 4.5; iSp = p_oTreeSet[41]->GetSpecies(); iType = p_oTreeSet[41]->GetType();
  p_oTreeSet[41]->SetValue( p_oPop->GetHeightCode( iSp, iType ), fHeight, bUpdateNow, bUpdateAllometry );
  p_oShortestHD[2] [0] [1] = p_oTreeSet[41];
  p_oTallestHD[2] [0] [0] = p_oTreeSet[44];
  if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  //****************************************
  //Update tree 63
  //****************************************
  fHeight = 29.0; iSp = p_oTreeSet[62]->GetSpecies(); iType = p_oTreeSet[62]->GetType();
  p_oTreeSet[62]->SetValue( p_oPop->GetHeightCode( iSp, iType ), fHeight, bUpdateNow, bUpdateAllometry );
  p_oShortestHD[2] [0] [7] = p_oTreeSet[62];
  p_oTallestHD[2] [0] [6] = p_oTreeSet[64];
  if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  //****************************************
  //Update tree 50
  //****************************************
  fHeight = 14.5; iSp = p_oTreeSet[49]->GetSpecies(); iType = p_oTreeSet[49]->GetType();
  p_oTreeSet[49]->SetValue( p_oPop->GetHeightCode( iSp, iType ), fHeight, bUpdateNow, bUpdateAllometry );
  //Get the rec for this tree
  p_oRec = p_oShort[2] [0];
  while ( p_oRec )
  {
    if ( p_oRec->thisTree == p_oTreeSet[49] ) break;
    else
      p_oRec = p_oRec->nextLink;
  }
  p_oTallestHD[2] [0] [2] = p_oTreeSet[48];
  //Swap with next
  p_oNextRec = p_oRec->nextLink;
  p_oPrevRec = p_oRec->prevLink;
  p_oNextRec->nextLink->prevLink = p_oRec; p_oNextRec->nextLink->prev = p_oRec->thisTree;
  p_oRec->nextLink = p_oNextRec->nextLink; p_oRec->next = p_oNextRec->next;
  p_oRec->prevLink = p_oNextRec; p_oRec->prev = p_oNextRec->thisTree;
  p_oNextRec->nextLink = p_oRec; p_oNextRec->next = p_oRec->thisTree;
  p_oNextRec->prevLink = p_oPrevRec; p_oNextRec->prev = p_oPrevRec->thisTree;
  p_oPrevRec->nextLink = p_oNextRec; p_oPrevRec->next = p_oNextRec->thisTree;
  if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  //****************************************
  //Update tree 1
  //****************************************
  fHeight = 14.0; iSp = p_oTreeSet[0]->GetSpecies(); iType = p_oTreeSet[0]->GetType();
  p_oTreeSet[0]->SetValue( p_oPop->GetHeightCode( iSp, iType ), fHeight, bUpdateNow, bUpdateAllometry );
  if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  //****************************************
  //Update tree 37
  //****************************************
  fHeight = 37.0; iSp = p_oTreeSet[36]->GetSpecies(); iType = p_oTreeSet[36]->GetType();
  p_oTreeSet[36]->SetValue( p_oPop->GetHeightCode( iSp, iType ), fHeight, bUpdateNow, bUpdateAllometry );
  p_oShortestHD[0] [0] [9] = p_oTreeSet[36];
  p_oTallestHD[0] [0] [9] = p_oTreeSet[36];
  p_oShortestHD[0] [0] [2] = NULL;
  p_oTallestHD[0] [0] [2] = NULL;
  if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  //****************************************
  //Update tree 38
  //****************************************
  fHeight = 3.0; iSp = p_oTreeSet[37]->GetSpecies(); iType = p_oTreeSet[37]->GetType();
  p_oTreeSet[37]->SetValue( p_oPop->GetHeightCode( iSp, iType ), fHeight, bUpdateNow, bUpdateAllometry );
  p_oShortestHD[19] [24] [0] = p_oTreeSet[37];
  p_oTallestHD[19] [24] [0] = p_oTreeSet[37];
  p_oShortestHD[19] [24] [2] = NULL;
  p_oTallestHD[19] [24] [2] = NULL;
  if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  //****************************************
  //Update tree 11
  //****************************************
  fHeight = 22.0; iSp = p_oTreeSet[10]->GetSpecies(); iType = p_oTreeSet[10]->GetType();
  p_oTreeSet[10]->SetValue( p_oPop->GetHeightCode( iSp, iType ), fHeight, bUpdateNow, bUpdateAllometry );
  if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  //****************************************
  //Update tree 40
  //****************************************
  fHeight = 23.0; iSp = p_oTreeSet[39]->GetSpecies(); iType = p_oTreeSet[39]->GetType();
  p_oTreeSet[39]->SetValue( p_oPop->GetHeightCode( iSp, iType ), fHeight, bUpdateNow, bUpdateAllometry );
  //Get the rec for this tree
  p_oRec = p_oTall[14] [7];
  while ( p_oRec )
  {
    if ( p_oRec->thisTree == p_oTreeSet[39] ) break;
    else
      p_oRec = p_oRec->prevLink;
  }
  p_oNextRec = p_oRec->nextLink; //Close the gap left
  p_oRec->prevLink->nextLink = p_oNextRec; p_oRec->prevLink->next = p_oNextRec->thisTree;
  p_oNextRec->prevLink = p_oRec->prevLink; p_oNextRec->prev = p_oRec->prev;
  //Get the rec for tree 39 - new previous
  p_oPrevRec = p_oTall[14] [7];
  while ( p_oPrevRec )
  {
    if ( p_oPrevRec->thisTree == p_oTreeSet[38] ) break;
    else
      p_oPrevRec = p_oPrevRec->prevLink;
  }
  p_oNextRec = p_oPrevRec->nextLink;
  p_oRec->nextLink = p_oNextRec; p_oRec->next = p_oNextRec->thisTree;
  p_oRec->prevLink = p_oPrevRec; p_oRec->prev = p_oPrevRec->thisTree;
  p_oPrevRec->nextLink = p_oRec; p_oPrevRec->next = p_oRec->thisTree;
  p_oNextRec->prevLink = p_oRec; p_oNextRec->prev = p_oRec->thisTree;
  if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  //****************************************
  //Update tree 39
  //****************************************
  fHeight = 21.9; iSp = p_oTreeSet[38]->GetSpecies(); iType = p_oTreeSet[38]->GetType();
  p_oTreeSet[38]->SetValue( p_oPop->GetHeightCode( iSp, iType ), fHeight, bUpdateNow, bUpdateAllometry );
  //Get the rec for this tree
  p_oRec = p_oTall[14] [7];
  while ( p_oRec )
  {
    if ( p_oRec->thisTree == p_oTreeSet[38] ) break;
    else
      p_oRec = p_oRec->prevLink;
  }
  p_oNextRec = p_oRec->nextLink; //Close the gap left
  p_oRec->prevLink->nextLink = p_oNextRec; p_oRec->prevLink->next = p_oNextRec->thisTree;
  p_oNextRec->prevLink = p_oRec->prevLink; p_oNextRec->prev = p_oRec->prev;
  //Get the rec for tree 9 - new previous
  p_oPrevRec = p_oShort[14] [7];
  while ( p_oPrevRec )
  {
    if ( p_oPrevRec->thisTree == p_oTreeSet[8] ) break;
    else
      p_oPrevRec = p_oPrevRec->nextLink;
  }
  p_oNextRec = p_oPrevRec->nextLink;
  p_oRec->nextLink = p_oNextRec; p_oRec->next = p_oNextRec->thisTree;
  p_oRec->prevLink = p_oPrevRec; p_oRec->prev = p_oPrevRec->thisTree;
  p_oPrevRec->nextLink = p_oRec; p_oPrevRec->next = p_oRec->thisTree;
  p_oNextRec->prevLink = p_oRec; p_oNextRec->prev = p_oRec->thisTree;
  if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  //****************************************
  //Update tree 13
  //****************************************
  fHeight = 43.0; iSp = p_oTreeSet[12]->GetSpecies(); iType = p_oTreeSet[12]->GetType();
  p_oTreeSet[12]->SetValue( p_oPop->GetHeightCode( iSp, iType ), fHeight, bUpdateNow, bUpdateAllometry );
  if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  //****************************************
  //Update tree 48
  //****************************************
  fDiam = 5.8826; iSp = p_oTreeSet[47]->GetSpecies(); iType = p_oTreeSet[47]->GetType();
  if (bUpdateAllometry) {
    p_oTreeSet[47]->SetValue( p_oPop->GetDbhCode( iSp, iType ), fDiam, bUpdateNow, bUpdateAllometry );
  } else {
    //Update height directly
    fHeight = 7.5;
    p_oTreeSet[47]->SetValue( p_oPop->GetHeightCode( iSp, iType ), fHeight, bUpdateNow, bUpdateAllometry );
  }
  if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  //****************************************
  //Update tree 4
  //****************************************
  fHeight = 2.0; iSp = p_oTreeSet[3]->GetSpecies(); iType = p_oTreeSet[3]->GetType();
  p_oTreeSet[3]->SetValue( p_oPop->GetHeightCode( iSp, iType ), fHeight, bUpdateNow, bUpdateAllometry );
  if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  //****************************************
  //Update tree 12
  //****************************************
  fHeight = 42.0; iSp = p_oTreeSet[11]->GetSpecies(); iType = p_oTreeSet[11]->GetType();
  p_oTreeSet[11]->SetValue( p_oPop->GetHeightCode( iSp, iType ), fHeight, bUpdateNow, bUpdateAllometry );
  if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  //****************************************
  //Update tree 9
  //****************************************
  fHeight = 20.5; iSp = p_oTreeSet[8]->GetSpecies(); iType = p_oTreeSet[8]->GetType();
  p_oTreeSet[8]->SetValue( p_oPop->GetHeightCode( iSp, iType ), fHeight, bUpdateNow, bUpdateAllometry );
  if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  //****************************************
  //Update tree 3
  //****************************************
  fHeight = 0.9; iSp = p_oTreeSet[2]->GetSpecies(); iType = p_oTreeSet[2]->GetType();
  p_oTreeSet[2]->SetValue( p_oPop->GetHeightCode( iSp, iType ), fHeight, bUpdateNow, bUpdateAllometry );
  if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  //****************************************
  //Update tree 15
  //****************************************
  fHeight = 13.3; iSp = p_oTreeSet[14]->GetSpecies(); iType = p_oTreeSet[14]->GetType();
  p_oTreeSet[14]->SetValue( p_oPop->GetHeightCode( iSp, iType ), fHeight, bUpdateNow, bUpdateAllometry );
  if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  //****************************************
  //Update tree 6
  //****************************************
  fHeight = 22.5; iSp = p_oTreeSet[5]->GetSpecies(); iType = p_oTreeSet[5]->GetType();
  p_oTreeSet[5]->SetValue( p_oPop->GetHeightCode( iSp, iType ), fHeight, bUpdateNow, bUpdateAllometry );
  //Get the rec for this tree
  p_oRec = p_oShort[14] [7];
  while ( p_oRec )
  {
    if ( p_oRec->thisTree == p_oTreeSet[5] ) break;
    else
      p_oRec = p_oRec->nextLink;
  }
  p_oShortestHD[14] [7] [4] = NULL;
  p_oTallestHD[14] [7] [4] = NULL;
  p_oNextRec = p_oRec->nextLink; //Close the gap left
  p_oRec->prevLink->nextLink = p_oNextRec; p_oRec->prevLink->next = p_oNextRec->thisTree;
  p_oNextRec->prevLink = p_oRec->prevLink; p_oNextRec->prev = p_oRec->prev;
  //Get the rec for tree 8 - new previous
  p_oPrevRec = p_oShort[14] [7];
  while ( p_oPrevRec )
  {
    if ( p_oPrevRec->thisTree == p_oTreeSet[7] ) break;
    else
      p_oPrevRec = p_oPrevRec->nextLink;
  }
  p_oNextRec = p_oPrevRec->nextLink;
  p_oRec->nextLink = p_oNextRec; p_oRec->next = p_oNextRec->thisTree;
  p_oRec->prevLink = p_oPrevRec; p_oRec->prev = p_oPrevRec->thisTree;
  p_oPrevRec->nextLink = p_oRec; p_oPrevRec->next = p_oRec->thisTree;
  p_oNextRec->prevLink = p_oRec; p_oNextRec->prev = p_oRec->thisTree;
  if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  //****************************************
  //Update tree 15
  //****************************************
  fHeight = 10.0; iSp = p_oTreeSet[14]->GetSpecies(); iType = p_oTreeSet[14]->GetType();
  p_oTreeSet[14]->SetValue( p_oPop->GetHeightCode( iSp, iType ), fHeight, bUpdateNow, bUpdateAllometry );
  p_oShortestHD[14] [7] [3] = NULL;
  p_oTallestHD[14] [7] [3] = NULL;
  p_oTallestHD[14] [7] [2] = p_oTreeSet[14];
  if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  //****************************************
  //Update tree 14
  //****************************************
  fHeight = 12.7; iSp = p_oTreeSet[13]->GetSpecies(); iType = p_oTreeSet[13]->GetType();
  p_oTreeSet[13]->SetValue( p_oPop->GetHeightCode( iSp, iType ), fHeight, bUpdateNow, bUpdateAllometry );
  //Get the rec for this tree
  p_oRec = p_oShort[14] [7];
  while ( p_oRec )
  {
    if ( p_oRec->thisTree == p_oTreeSet[13] ) break;
    else
      p_oRec = p_oRec->nextLink;
  }
  p_oShortestHD[14] [7] [2] = p_oTreeSet[14];
  p_oShortestHD[14] [7] [3] = p_oTreeSet[13];
  p_oTallestHD[14] [7] [3] = p_oTreeSet[13];
  //Swap with next
  p_oNextRec = p_oRec->nextLink;
  p_oPrevRec = p_oRec->prevLink;
  p_oNextRec->nextLink->prevLink = p_oRec; p_oNextRec->nextLink->prev = p_oRec->thisTree;
  p_oRec->nextLink = p_oNextRec->nextLink; p_oRec->next = p_oNextRec->next;
  p_oRec->prevLink = p_oNextRec; p_oRec->prev = p_oNextRec->thisTree;
  p_oNextRec->nextLink = p_oRec; p_oNextRec->next = p_oRec->thisTree;
  p_oNextRec->prevLink = p_oPrevRec; p_oNextRec->prev = p_oPrevRec->thisTree;
  p_oPrevRec->nextLink = p_oNextRec; p_oPrevRec->next = p_oNextRec->thisTree;
  if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  //****************************************
  //Update tree 12
  //****************************************
  fHeight = 35.0; iSp = p_oTreeSet[11]->GetSpecies(); iType = p_oTreeSet[11]->GetType();
  p_oTreeSet[11]->SetValue( p_oPop->GetHeightCode( iSp, iType ), fHeight, bUpdateNow, bUpdateAllometry );
  p_oShortestHD[14] [7] [8] = p_oTreeSet[11];
  p_oTallestHD[14] [7] [8] = p_oTreeSet[11];
  p_oShortestHD[14] [7] [9] = p_oTallestHD[14] [7] [9] = NULL;
  p_oShortestHD[14] [7] [10] = p_oTallestHD[14] [7] [10];
  if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  //****************************************
  //Update tree 15
  //****************************************
  fHeight = 7.0; iSp = p_oTreeSet[14]->GetSpecies(); iType = p_oTreeSet[14]->GetType();
  p_oTreeSet[14]->SetValue( p_oPop->GetHeightCode( iSp, iType ), fHeight, bUpdateNow, bUpdateAllometry );
  p_oShortestHD[14] [7] [2] = NULL;
  p_oTallestHD[14] [7] [2] = NULL;
  p_oShortestHD[14] [7] [1] = p_oTreeSet[14];
  p_oTallestHD[14] [7] [1] = p_oTreeSet[14];
  if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  //****************************************
  //Update tree 41
  //****************************************
  fHeight = 25.0; iSp = p_oTreeSet[40]->GetSpecies(); iType = p_oTreeSet[40]->GetType();
  p_oTreeSet[40]->SetValue( p_oPop->GetHeightCode( iSp, iType ), fHeight, bUpdateNow, bUpdateAllometry );
  p_oTallestHD[14] [7] [5] = p_oTreeSet[9];
  p_oShortestHD[14] [7] [6] = p_oTreeSet[40];
  if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  //****************************************
  //Update tree 44
  //****************************************
  if (bUpdateAllometry) {
    fDiam = 0.35; iSp = p_oTreeSet[43]->GetSpecies(); iType = p_oTreeSet[43]->GetType();
    p_oTreeSet[43]->SetValue( p_oPop->GetDiam10Code( iSp, iType ), fDiam, bUpdateNow, bUpdateAllometry );
  } else {
    //Update the height directly
    fHeight = 0.4; iSp = p_oTreeSet[43]->GetSpecies(); iType = p_oTreeSet[43]->GetType();
    p_oTreeSet[43]->SetValue( p_oPop->GetHeightCode( iSp, iType ), fHeight, bUpdateNow, bUpdateAllometry );
  }
  //Get the rec for this tree
  p_oRec = p_oShort[2] [0];
  p_oRec = p_oRec->nextLink;
  p_oShortestHD[2] [0] [0] = p_oTreeSet[43];
  p_oShort[2] [0] = p_oRec;
  //Swap with previous
  p_oPrevRec = p_oRec->prevLink;
  p_oNextRec = p_oRec->nextLink;
  p_oRec->nextLink = p_oPrevRec; p_oRec->next = p_oPrevRec->thisTree;
  p_oRec->prevLink = p_oPrevRec->prevLink; p_oRec->prev = p_oPrevRec->prev;
  p_oPrevRec->nextLink = p_oNextRec; p_oPrevRec->next = p_oNextRec->thisTree;
  p_oPrevRec->prevLink = p_oRec; p_oPrevRec->prev = p_oRec->thisTree;
  p_oNextRec->prevLink = p_oPrevRec; p_oNextRec->prev = p_oPrevRec->thisTree;
  if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  //****************************************
  //Update tree 21
  //****************************************
  fHeight = 4.5; iSp = p_oTreeSet[20]->GetSpecies(); iType = p_oTreeSet[20]->GetType();
  p_oTreeSet[20]->SetValue( p_oPop->GetHeightCode( iSp, iType ), fHeight, bUpdateNow, bUpdateAllometry );
  p_oTallestHD[6] [3] [1] = p_oTreeSet[20];
  p_oShortestHD[6] [3] [1] = p_oTreeSet[20];
  p_oTallestHD[6] [3] [0] = NULL;
  p_oShortestHD[6] [3] [0] = NULL;
  if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  //****************************************
  //Update tree 20
  //****************************************
  fHeight = 39.8; iSp = p_oTreeSet[19]->GetSpecies(); iType = p_oTreeSet[19]->GetType();
  p_oTreeSet[19]->SetValue( p_oPop->GetHeightCode( iSp, iType ), fHeight, bUpdateNow, bUpdateAllometry );
  //Get the rec for this tree
  p_oRec = p_oTall[6] [3];
  while ( p_oRec )
  {
    if ( p_oRec->thisTree == p_oTreeSet[19] ) break;
    else
      p_oRec = p_oRec->prevLink;
  }
  p_oTallestHD[6] [3] [2] = NULL;
  p_oShortestHD[6] [3] [2] = NULL;
  p_oTallestHD[6] [3] [9] = p_oTreeSet[19];
  p_oNextRec = p_oRec->nextLink; //Close the gap left
  p_oRec->prevLink->nextLink = p_oNextRec; p_oRec->prevLink->next = p_oNextRec->thisTree;
  p_oNextRec->prevLink = p_oRec->prevLink; p_oNextRec->prev = p_oRec->prev;
  //Get the rec for tree 18 - new previous
  p_oPrevRec = p_oTall[6] [3];
  p_oRec->nextLink = NULL; p_oRec->next = NULL;
  p_oRec->prevLink = p_oPrevRec; p_oRec->prev = p_oPrevRec->thisTree;
  p_oPrevRec->nextLink = p_oRec; p_oPrevRec->next = p_oRec->thisTree;
  p_oTall[6] [3] = p_oRec;
  if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  //****************************************
  //Update tree 16
  //****************************************
  if (bUpdateAllometry) {
    fDiam = 15.1489; iSp = p_oTreeSet[15]->GetSpecies(); iType = p_oTreeSet[15]->GetType();
    p_oTreeSet[15]->SetValue( p_oPop->GetDiam10Code( iSp, iType ), fDiam, bUpdateNow, bUpdateAllometry );
  } else {
    //Update the height directly
    fHeight = 8.8; iSp = p_oTreeSet[15]->GetSpecies(); iType = p_oTreeSet[15]->GetType();
    p_oTreeSet[15]->SetValue( p_oPop->GetHeightCode( iSp, iType ), fHeight, bUpdateNow, bUpdateAllometry );
  }
  p_oTallestHD[15] [8] [2] = p_oTreeSet[15];
  p_oShortestHD[15] [8] [2] = p_oTreeSet[15];
  p_oTallestHD[15] [8] [1] = NULL;
  p_oShortestHD[15] [8] [1] = NULL;
  if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  //****************************************
  //Update tree 54
  //****************************************
  fHeight = 21.0; iSp = p_oTreeSet[53]->GetSpecies(); iType = p_oTreeSet[53]->GetType();
  p_oTreeSet[53]->SetValue( p_oPop->GetHeightCode( iSp, iType ), fHeight, bUpdateNow, bUpdateAllometry );
  //Get the rec for this tree
  p_oRec = p_oShort[2] [0];
  while ( p_oRec )
  {
    if ( p_oRec->thisTree == p_oTreeSet[53] ) break;
    else
      p_oRec = p_oRec->nextLink;
  }
  p_oNextRec = p_oRec->nextLink; //Close the gap left
  p_oRec->prevLink->nextLink = p_oNextRec; p_oRec->prevLink->next = p_oNextRec->thisTree;
  p_oNextRec->prevLink = p_oRec->prevLink; p_oNextRec->prev = p_oRec->prev;
  //Get the rec for tree 60 - new previous
  p_oPrevRec = p_oShort[2] [0];
  while ( p_oPrevRec )
  {
    if ( p_oPrevRec->thisTree == p_oTreeSet[59] ) break;
    else
      p_oPrevRec = p_oPrevRec->nextLink;
  }
  p_oNextRec = p_oPrevRec->nextLink;
  p_oRec->nextLink = p_oNextRec; p_oRec->next = p_oNextRec->thisTree;
  p_oRec->prevLink = p_oPrevRec; p_oRec->prev = p_oPrevRec->thisTree;
  p_oPrevRec->nextLink = p_oRec; p_oPrevRec->next = p_oRec->thisTree;
  p_oNextRec->prevLink = p_oRec; p_oNextRec->prev = p_oRec->thisTree;
  if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  //****************************************
  //Update tree 67
  //****************************************
  fHeight = 21.3; iSp = p_oTreeSet[66]->GetSpecies(); iType = p_oTreeSet[66]->GetType();
  p_oTreeSet[66]->SetValue( p_oPop->GetHeightCode( iSp, iType ), fHeight, bUpdateNow, bUpdateAllometry );
  //Get the rec for this tree
  p_oRec = p_oShort[2] [0];
  while ( p_oRec )
  {
    if ( p_oRec->thisTree == p_oTreeSet[66] ) break;
    else
      p_oRec = p_oRec->nextLink;
  }
  p_oNextRec = p_oRec->nextLink; //Close the gap left
  p_oRec->prevLink->nextLink = p_oNextRec; p_oRec->prevLink->next = p_oNextRec->thisTree;
  p_oNextRec->prevLink = p_oRec->prevLink; p_oNextRec->prev = p_oRec->prev;
  //Get the rec for tree 54 - new previous
  p_oPrevRec = p_oShort[2] [0];
  while ( p_oPrevRec )
  {
    if ( p_oPrevRec->thisTree == p_oTreeSet[53] ) break;
    else
      p_oPrevRec = p_oPrevRec->nextLink;
  }
  p_oNextRec = p_oPrevRec->nextLink;
  p_oRec->nextLink = p_oNextRec; p_oRec->next = p_oNextRec->thisTree;
  p_oRec->prevLink = p_oPrevRec; p_oRec->prev = p_oPrevRec->thisTree;
  p_oPrevRec->nextLink = p_oRec; p_oPrevRec->next = p_oRec->thisTree;
  p_oNextRec->prevLink = p_oRec; p_oNextRec->prev = p_oRec->thisTree;
  if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  //****************************************
  //Update tree 7
  //****************************************
  fHeight = 13.0; iSp = p_oTreeSet[6]->GetSpecies(); iType = p_oTreeSet[6]->GetType();
  p_oTreeSet[6]->SetValue( p_oPop->GetHeightCode( iSp, iType ), fHeight, bUpdateNow, bUpdateAllometry );
  //Get the rec for this tree
  p_oRec = p_oShort[14] [7];
  while ( p_oRec )
  {
    if ( p_oRec->thisTree == p_oTreeSet[6] ) break;
    else
      p_oRec = p_oRec->nextLink;
  }
  p_oNextRec = p_oRec->nextLink; //Close the gap left
  p_oRec->prevLink->nextLink = p_oNextRec; p_oRec->prevLink->next = p_oNextRec->thisTree;
  p_oNextRec->prevLink = p_oRec->prevLink; p_oNextRec->prev = p_oRec->prev;
  //Get the rec for tree 14 - new previous
  p_oPrevRec = p_oShort[14] [7];
  while ( p_oPrevRec )
  {
    if ( p_oPrevRec->thisTree == p_oTreeSet[13] ) break;
    else
      p_oPrevRec = p_oPrevRec->nextLink;
  }
  p_oNextRec = p_oPrevRec->nextLink;
  p_oRec->nextLink = p_oNextRec; p_oRec->next = p_oNextRec->thisTree;
  p_oRec->prevLink = p_oPrevRec; p_oRec->prev = p_oPrevRec->thisTree;
  p_oPrevRec->nextLink = p_oRec; p_oPrevRec->next = p_oRec->thisTree;
  p_oNextRec->prevLink = p_oRec; p_oNextRec->prev = p_oRec->thisTree;
  p_oTallestHD[14] [7] [3] = p_oTreeSet[6];
  if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  //****************************************
  //Update tree 12
  //****************************************
  fHeight = 24.5; iSp = p_oTreeSet[11]->GetSpecies(); iType = p_oTreeSet[11]->GetType();
  p_oTreeSet[11]->SetValue( p_oPop->GetHeightCode( iSp, iType ), fHeight, bUpdateNow, bUpdateAllometry );
  //Get the rec for this tree
  p_oRec = p_oTall[14] [7];
  p_oRec = p_oRec->prevLink;
  p_oNextRec = p_oRec->nextLink; //Close the gap left
  p_oRec->prevLink->nextLink = p_oNextRec; p_oRec->prevLink->next = p_oNextRec->thisTree;
  p_oNextRec->prevLink = p_oRec->prevLink; p_oNextRec->prev = p_oRec->prev;
  //Get the rec for tree 10 - new previous
  p_oPrevRec = p_oShort[14] [7];
  while ( p_oPrevRec )
  {
    if ( p_oPrevRec->thisTree == p_oTreeSet[9] ) break;
    else
      p_oPrevRec = p_oPrevRec->nextLink;
  }
  p_oNextRec = p_oPrevRec->nextLink;
  p_oRec->nextLink = p_oNextRec; p_oRec->next = p_oNextRec->thisTree;
  p_oRec->prevLink = p_oPrevRec; p_oRec->prev = p_oPrevRec->thisTree;
  p_oPrevRec->nextLink = p_oRec; p_oPrevRec->next = p_oRec->thisTree;
  p_oNextRec->prevLink = p_oRec; p_oNextRec->prev = p_oRec->thisTree;
  p_oShortestHD[14] [7] [6] = p_oTreeSet[11];
  p_oShortestHD[14] [7] [8] = NULL;
  p_oTallestHD[14] [7] [8] = NULL;
  if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  //****************************************
  //Update tree 7
  //****************************************
  fHeight = 23.5; iSp = p_oTreeSet[6]->GetSpecies(); iType = p_oTreeSet[6]->GetType();
  p_oTreeSet[6]->SetValue( p_oPop->GetHeightCode( iSp, iType ), fHeight, bUpdateNow, bUpdateAllometry );
  //Get the rec for this tree
  p_oRec = p_oTall[14] [7];
  while ( p_oRec )
  {
    if ( p_oRec->thisTree == p_oTreeSet[6] ) break;
    else
      p_oRec = p_oRec->prevLink;
  }
  p_oNextRec = p_oRec->nextLink; //Close the gap left
  p_oRec->prevLink->nextLink = p_oNextRec; p_oRec->prevLink->next = p_oNextRec->thisTree;
  p_oNextRec->prevLink = p_oRec->prevLink; p_oNextRec->prev = p_oRec->prev;
  //Get the rec for tree 10 - new previous
  p_oPrevRec = p_oShort[14] [7];
  while ( p_oPrevRec )
  {
    if ( p_oPrevRec->thisTree == p_oTreeSet[9] ) break;
    else
      p_oPrevRec = p_oPrevRec->nextLink;
  }
  p_oNextRec = p_oPrevRec->nextLink;
  p_oRec->nextLink = p_oNextRec; p_oRec->next = p_oNextRec->thisTree;
  p_oRec->prevLink = p_oPrevRec; p_oRec->prev = p_oPrevRec->thisTree;
  p_oPrevRec->nextLink = p_oRec; p_oPrevRec->next = p_oRec->thisTree;
  p_oNextRec->prevLink = p_oRec; p_oNextRec->prev = p_oRec->thisTree;
  p_oTallestHD[14] [7] [3] = p_oTreeSet[13];
  p_oTallestHD[14] [7] [5] = p_oTreeSet[6];
  if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  //****************************************
  //Update tree 2
  //****************************************
  fHeight = 20.4; iSp = p_oTreeSet[1]->GetSpecies(); iType = p_oTreeSet[1]->GetType();
  p_oTreeSet[1]->SetValue( p_oPop->GetHeightCode( iSp, iType ), fHeight, bUpdateNow, bUpdateAllometry );
  //Get the rec for this tree
  p_oRec = p_oShort[14] [7];
  while ( p_oRec )
  {
    if ( p_oRec->thisTree == p_oTreeSet[1] ) break;
    else
      p_oRec = p_oRec->nextLink;
  }
  p_oNextRec = p_oRec->nextLink; //Close the gap left
  p_oRec->prevLink->nextLink = p_oNextRec; p_oRec->prevLink->next = p_oNextRec->thisTree;
  p_oNextRec->prevLink = p_oRec->prevLink; p_oNextRec->prev = p_oRec->prev;
  //Get the rec for tree 14 - new previous
  p_oPrevRec = p_oShort[14] [7];
  while ( p_oPrevRec )
  {
    if ( p_oPrevRec->thisTree == p_oTreeSet[13] ) break;
    else
      p_oPrevRec = p_oPrevRec->nextLink;
  }
  p_oNextRec = p_oPrevRec->nextLink;
  p_oRec->nextLink = p_oNextRec; p_oRec->next = p_oNextRec->thisTree;
  p_oRec->prevLink = p_oPrevRec; p_oRec->prev = p_oPrevRec->thisTree;
  p_oPrevRec->nextLink = p_oRec; p_oPrevRec->next = p_oRec->thisTree;
  p_oNextRec->prevLink = p_oRec; p_oNextRec->prev = p_oRec->thisTree;
  p_oShortestHD[14] [7] [5] = p_oTreeSet[1];
  if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  //****************************************
  //Update tree 39
  //****************************************
  fHeight = 23.0; iSp = p_oTreeSet[38]->GetSpecies(); iType = p_oTreeSet[38]->GetType();
  p_oTreeSet[38]->SetValue( p_oPop->GetHeightCode( iSp, iType ), fHeight, bUpdateNow, bUpdateAllometry );
  //Get the rec for this tree
  p_oRec = p_oShort[14] [7];
  while ( p_oRec )
  {
    if ( p_oRec->thisTree == p_oTreeSet[38] ) break;
    else
      p_oRec = p_oRec->nextLink;
  }
  p_oNextRec = p_oRec->nextLink; //Close the gap left
  p_oRec->prevLink->nextLink = p_oNextRec; p_oRec->prevLink->next = p_oNextRec->thisTree;
  p_oNextRec->prevLink = p_oRec->prevLink; p_oNextRec->prev = p_oRec->prev;
  //Get the rec for tree 40 - new previous
  p_oPrevRec = p_oShort[14] [7];
  while ( p_oPrevRec )
  {
    if ( p_oPrevRec->thisTree == p_oTreeSet[39] ) break;
    else
      p_oPrevRec = p_oPrevRec->nextLink;
  }
  p_oNextRec = p_oPrevRec->nextLink;
  p_oRec->nextLink = p_oNextRec; p_oRec->next = p_oNextRec->thisTree;
  p_oRec->prevLink = p_oPrevRec; p_oRec->prev = p_oPrevRec->thisTree;
  p_oPrevRec->nextLink = p_oRec; p_oPrevRec->next = p_oRec->thisTree;
  p_oNextRec->prevLink = p_oRec; p_oNextRec->prev = p_oRec->thisTree;
  if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  //****************************************
  //Update tree 8
  //****************************************
  fHeight = 20.5; iSp = p_oTreeSet[7]->GetSpecies(); iType = p_oTreeSet[7]->GetType();
  p_oTreeSet[7]->SetValue( p_oPop->GetHeightCode( iSp, iType ), fHeight, bUpdateNow, bUpdateAllometry );
  //Get the rec for this tree
  p_oRec = p_oShort[14] [7];
  while ( p_oRec )
  {
    if ( p_oRec->thisTree == p_oTreeSet[7] ) break;
    else
      p_oRec = p_oRec->nextLink;
  }
  p_oNextRec = p_oRec->nextLink; //Close the gap left
  p_oRec->prevLink->nextLink = p_oNextRec; p_oRec->prevLink->next = p_oNextRec->thisTree;
  p_oNextRec->prevLink = p_oRec->prevLink; p_oNextRec->prev = p_oRec->prev;
  //Get the rec for tree 2 - new previous
  p_oPrevRec = p_oShort[14] [7];
  while ( p_oPrevRec )
  {
    if ( p_oPrevRec->thisTree == p_oTreeSet[1] ) break;
    else
      p_oPrevRec = p_oPrevRec->nextLink;
  }
  p_oNextRec = p_oPrevRec->nextLink;
  p_oRec->nextLink = p_oNextRec; p_oRec->next = p_oNextRec->thisTree;
  p_oRec->prevLink = p_oPrevRec; p_oRec->prev = p_oPrevRec->thisTree;
  p_oPrevRec->nextLink = p_oRec; p_oPrevRec->next = p_oRec->thisTree;
  p_oNextRec->prevLink = p_oRec; p_oNextRec->prev = p_oRec->thisTree;
  if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  //****************************************
  //Update tree 8
  //****************************************
  fHeight = 23.5; iSp = p_oTreeSet[7]->GetSpecies(); iType = p_oTreeSet[7]->GetType();
  p_oTreeSet[7]->SetValue( p_oPop->GetHeightCode( iSp, iType ), fHeight, bUpdateNow, bUpdateAllometry );
  //Get the rec for this tree
  p_oRec = p_oShort[14] [7];
  while ( p_oRec )
  {
    if ( p_oRec->thisTree == p_oTreeSet[7] ) break;
    else
      p_oRec = p_oRec->nextLink;
  }
  p_oNextRec = p_oRec->nextLink; //Close the gap left
  p_oRec->prevLink->nextLink = p_oNextRec; p_oRec->prevLink->next = p_oNextRec->thisTree;
  p_oNextRec->prevLink = p_oRec->prevLink; p_oNextRec->prev = p_oRec->prev;
  //Get the rec for tree 7 - new previous
  p_oPrevRec = p_oShort[14] [7];
  while ( p_oPrevRec )
  {
    if ( p_oPrevRec->thisTree == p_oTreeSet[6] ) break;
    else
      p_oPrevRec = p_oPrevRec->nextLink;
  }
  p_oNextRec = p_oPrevRec->nextLink;
  p_oRec->nextLink = p_oNextRec; p_oRec->next = p_oNextRec->thisTree;
  p_oRec->prevLink = p_oPrevRec; p_oRec->prev = p_oPrevRec->thisTree;
  p_oPrevRec->nextLink = p_oRec; p_oPrevRec->next = p_oRec->thisTree;
  p_oNextRec->prevLink = p_oRec; p_oNextRec->prev = p_oRec->thisTree;
  p_oTallestHD[14] [7] [5] = p_oTreeSet[7];
  if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );

  //****************************************
  //Update tree 6
  //****************************************
  fHeight = 20.4; iSp = p_oTreeSet[5]->GetSpecies(); iType = p_oTreeSet[5]->GetType();
  p_oTreeSet[5]->SetValue( p_oPop->GetHeightCode( iSp, iType ), fHeight, bUpdateNow, bUpdateAllometry );
  //Get the rec for this tree
  p_oRec = p_oShort[14] [7];
  while ( p_oRec )
  {
    if ( p_oRec->thisTree == p_oTreeSet[5] ) break;
    else
      p_oRec = p_oRec->nextLink;
  }
  p_oNextRec = p_oRec->nextLink; //Close the gap left
  p_oRec->prevLink->nextLink = p_oNextRec; p_oRec->prevLink->next = p_oNextRec->thisTree;
  p_oNextRec->prevLink = p_oRec->prevLink; p_oNextRec->prev = p_oRec->prev;
  //Get the rec for tree 14 - new previous
  p_oPrevRec = p_oShort[14] [7];
  while ( p_oPrevRec )
  {
    if ( p_oPrevRec->thisTree == p_oTreeSet[13] ) break;
    else
      p_oPrevRec = p_oPrevRec->nextLink;
  }
  p_oNextRec = p_oPrevRec->nextLink;
  p_oRec->nextLink = p_oNextRec; p_oRec->next = p_oNextRec->thisTree;
  p_oRec->prevLink = p_oPrevRec; p_oRec->prev = p_oPrevRec->thisTree;
  p_oPrevRec->nextLink = p_oRec; p_oPrevRec->next = p_oRec->thisTree;
  p_oNextRec->prevLink = p_oRec; p_oNextRec->prev = p_oRec->thisTree;
  p_oShortestHD[14] [7] [5] = p_oTreeSet[5];
  if ( bFullCheck ) CheckHashTable( p_oPop, p_oShortestHD, p_oTallestHD, p_oShort, p_oTall, iNumXCells, iNumYCells );
}
//---------------------------------------------------------------------------


/////////////////////////////////////////////////////////////////////////////
//  WriteXMLFile1()
/////////////////////////////////////////////////////////////////////////////
const char* clTestTreePopulation::WriteXMLFile1()
{
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
       << "<plot_lenX>160.0</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\"/>"
       << "<tr_species speciesName=\"Species_2\"/>"
       << "<tr_species speciesName=\"Species_3\"/>"
       << "</tr_speciesList>"
       << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"Species_1\">9.8</tr_madVal>"
       << "<tr_madVal species=\"Species_2\">10</tr_madVal>"
       << "<tr_madVal species=\"Species_3\">10.1</tr_madVal>"
       << "</tr_minAdultDBH>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_3\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>"
       << "</trees>"
       << "<allometry>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_2\">39.54</tr_chVal>"
       << "<tr_chVal species=\"Species_3\">45</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_2\">0.0614</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_3\">0.02418</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"Species_1\">0.9</tr_screVal>"
       << "<tr_screVal species=\"Species_2\">1</tr_screVal>"
       << "<tr_screVal species=\"Species_3\">1.1</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">0.5944</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_3\">0.7059</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_3\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.368</tr_sachVal>"
       << "<tr_sachVal species=\"Species_3\">0.340</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">0.5</tr_scheVal>"
       << "<tr_scheVal species=\"Species_3\">0.9</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_2\">0.0269</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_3\">0.02871</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_2\">0.0241</tr_soahVal>"
       << "<tr_soahVal species=\"Species_3\">0.0263</tr_soahVal>"
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
       << "</allometry>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>ConstantGLI</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
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
//  WriteXMLFile2()
/////////////////////////////////////////////////////////////////////////////
const char* clTestTreePopulation::WriteXMLFile2()
{
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
       << "<plot_lenX>162.0</plot_lenX>"
       << "<plot_lenY>203.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\"/>"
       << "<tr_species speciesName=\"Species_2\"/>"
       << "<tr_species speciesName=\"Species_3\"/>"
       << "</tr_speciesList>"
       << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"Species_1\">9.8</tr_madVal>"
       << "<tr_madVal species=\"Species_2\">10</tr_madVal>"
       << "<tr_madVal species=\"Species_3\">10.1</tr_madVal>"
       << "</tr_minAdultDBH>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_3\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>"
       << "</trees>"
       << "<allometry>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_2\">39.54</tr_chVal>"
       << "<tr_chVal species=\"Species_3\">45</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_2\">0.0614</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_3\">0.02418</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"Species_1\">0.9</tr_screVal>"
       << "<tr_screVal species=\"Species_2\">1</tr_screVal>"
       << "<tr_screVal species=\"Species_3\">1.1</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">0.5944</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_3\">0.7059</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_3\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.368</tr_sachVal>"
       << "<tr_sachVal species=\"Species_3\">0.340</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">0.5</tr_scheVal>"
       << "<tr_scheVal species=\"Species_3\">0.9</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_2\">0.0269</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_3\">0.02871</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_2\">0.0241</tr_soahVal>"
       << "<tr_soahVal species=\"Species_3\">0.0263</tr_soahVal>"
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
       << "</allometry>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>ConstantGLI</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
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
//  WriteXMLFile3()
/////////////////////////////////////////////////////////////////////////////
const char* clTestTreePopulation::WriteXMLFile3()
{
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
       << "<tr_madVal species=\"Species_1\">9.8</tr_madVal>"
       << "<tr_madVal species=\"Species_2\">10</tr_madVal>"
       << "</tr_minAdultDBH>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>"
       << "<tr_treemap>"
       << "<tm_treeSettings sp=\"Species_1\" tp=\"1\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"Diam10\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_2\" tp=\"1\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"Diam10\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_1\" tp=\"2\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_2\" tp=\"2\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_1\" tp=\"3\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_2\" tp=\"3\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_1\" tp=\"5\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_2\" tp=\"5\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tree sp=\"0\" tp=\"1\">"
       << "<fl c=\"0\">1</fl>"
       << "<fl c=\"1\">1</fl>"
       << "<fl c=\"2\">0.3</fl>"
       << "</tree>"
       << "<tree sp=\"1\" tp=\"1\">"
       << "<fl c=\"0\">2</fl>"
       << "<fl c=\"1\">2</fl>"
       << "<fl c=\"2\">0.3</fl>"
       << "</tree>"
       << "<tree sp=\"0\" tp=\"2\">"
       << "<fl c=\"0\">3</fl>"
       << "<fl c=\"1\">3</fl>"
       << "<fl c=\"2\">3</fl>"
       << "</tree>"
       << "<tree sp=\"1\" tp=\"2\">"
       << "<fl c=\"0\">4</fl>"
       << "<fl c=\"1\">4</fl>"
       << "<fl c=\"2\">3</fl>"
       << "</tree>"
       << "<tree sp=\"0\" tp=\"3\">"
       << "<fl c=\"0\">5</fl>"
       << "<fl c=\"1\">5</fl>"
       << "<fl c=\"2\">33</fl>"
       << "</tree>"
       << "<tree sp=\"1\" tp=\"3\">"
       << "<fl c=\"0\">6</fl>"
       << "<fl c=\"1\">6</fl>"
       << "<fl c=\"2\">33</fl>"
       << "</tree>"
       << "<tree sp=\"0\" tp=\"5\">"
       << "<fl c=\"0\">7</fl>"
       << "<fl c=\"1\">7</fl>"
       << "<fl c=\"2\">13</fl>"
       << "</tree>"
       << "<tree sp=\"1\" tp=\"5\">"
       << "<fl c=\"0\">8</fl>"
       << "<fl c=\"1\">8</fl>"
       << "<fl c=\"2\">13</fl>"
       << "</tree>"
       << "</tr_treemap>"
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
       << "<tr_screVal species=\"Species_1\">0.9</tr_screVal>"
       << "<tr_screVal species=\"Species_2\">1</tr_screVal>"
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
       << "<tr_scheVal species=\"Species_1\">1</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">0.5</tr_scheVal>"
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
       << "<behaviorName>ConstantGLI</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>GapDisperse</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Stump\" />"
       << "<applyTo species=\"Species_2\" type=\"Adult\" />"
       << "</behavior>"
       << "</behaviorList>"
       << "<ConstantGLI1>"
       << "<li_constGLI>100</li_constGLI>"
       << "</ConstantGLI1>"
       << "<GapDisperse2>"
       << "<di_weibullCanopySTR>"
       << "<di_wcsVal species=\"Species_1\">0.0</di_wcsVal>"
       << "<di_wcsVal species=\"Species_2\">0.0</di_wcsVal>"
       << "</di_weibullCanopySTR>"
       << "<di_weibullCanopyBeta>"
       << "<di_wcbVal species=\"Species_1\">0.0</di_wcbVal>"
       << "<di_wcbVal species=\"Species_2\">0.0</di_wcbVal>"
       << "</di_weibullCanopyBeta>"
       << "<di_weibullCanopyDispersal>"
       << "<di_wcdVal species=\"Species_1\">0.0</di_wcdVal>"
       << "<di_wcdVal species=\"Species_2\">0.0</di_wcdVal>"
       << "</di_weibullCanopyDispersal>"
       << "<di_weibullCanopyTheta>"
       << "<di_wctVal species=\"Species_1\">0.0</di_wctVal>"
       << "<di_wctVal species=\"Species_2\">0.0</di_wctVal>"
       << "</di_weibullCanopyTheta>"
       << "<di_weibullGapSTR>"
       << "<di_wgsVal species=\"Species_1\">0.0</di_wgsVal>"
       << "<di_wgsVal species=\"Species_2\">0.0</di_wgsVal>"
       << "</di_weibullGapSTR>"
       << "<di_weibullGapBeta>"
       << "<di_wgbVal species=\"Species_1\">0.0</di_wgbVal>"
       << "<di_wgbVal species=\"Species_2\">0.0</di_wgbVal>"
       << "</di_weibullGapBeta>"
       << "<di_weibullGapDispersal>"
       << "<di_wgdVal species=\"Species_1\">0.0</di_wgdVal>"
       << "<di_wgdVal species=\"Species_2\">0.0</di_wgdVal>"
       << "</di_weibullGapDispersal>"
       << "<di_weibullGapTheta>"
       << "<di_wgtVal species=\"Species_1\">0.0</di_wgtVal>"
       << "<di_wgtVal species=\"Species_2\">0.0</di_wgtVal>"
       << "</di_weibullGapTheta>"
       << "<di_lognormalCanopySTR>"
       << "<di_lcsVal species=\"Species_1\">0.0</di_lcsVal>"
       << "<di_lcsVal species=\"Species_2\">0.0</di_lcsVal>"
       << "</di_lognormalCanopySTR>"
       << "<di_lognormalCanopyBeta>"
       << "<di_lcbVal species=\"Species_1\">0.0</di_lcbVal>"
       << "<di_lcbVal species=\"Species_2\">0.0</di_lcbVal>"
       << "</di_lognormalCanopyBeta>"
       << "<di_lognormalCanopyX0>"
       << "<di_lcx0Val species=\"Species_1\">0.0</di_lcx0Val>"
       << "<di_lcx0Val species=\"Species_2\">0.0</di_lcx0Val>"
       << "</di_lognormalCanopyX0>"
       << "<di_lognormalCanopyXb>"
       << "<di_lcxbVal species=\"Species_1\">0.0</di_lcxbVal>"
       << "<di_lcxbVal species=\"Species_2\">0.0</di_lcxbVal>"
       << "</di_lognormalCanopyXb>"
       << "<di_lognormalGapSTR>"
       << "<di_lgsVal species=\"Species_1\">0.0</di_lgsVal>"
       << "<di_lgsVal species=\"Species_2\">0.0</di_lgsVal>"
       << "</di_lognormalGapSTR>"
       << "<di_lognormalGapBeta>"
       << "<di_lgbVal species=\"Species_1\">0.0</di_lgbVal>"
       << "<di_lgbVal species=\"Species_2\">0.0</di_lgbVal>"
       << "</di_lognormalGapBeta>"
       << "<di_lognormalGapX0>"
       << "<di_lgx0Val species=\"Species_1\">0.0</di_lgx0Val>"
       << "<di_lgx0Val species=\"Species_2\">0.0</di_lgx0Val>"
       << "</di_lognormalGapX0>"
       << "<di_lognormalGapXb>"
       << "<di_lgxbVal species=\"Species_1\">0.0</di_lgxbVal>"
       << "<di_lgxbVal species=\"Species_2\">0.0</di_lgxbVal>"
       << "</di_lognormalGapXb>"
       << "<di_suckerSTR>"
       << "<di_ssVal species=\"Species_1\">0.0</di_ssVal>"
       << "<di_ssVal species=\"Species_2\">0.0</di_ssVal>"
       << "</di_suckerSTR>"
       << "<di_suckerBeta>"
       << "<di_sbVal species=\"Species_1\">0.0</di_sbVal>"
       << "<di_sbVal species=\"Species_2\">0.0</di_sbVal>"
       << "</di_suckerBeta>"
       << "<di_maxGapDensity>0</di_maxGapDensity>"
       << "<di_gapFunction>"
       << "<di_gfVal species=\"Species_1\">0</di_gfVal>"
       << "<di_gfVal species=\"Species_2\">0</di_gfVal>"
       << "</di_gapFunction>"
       << "<di_canopyFunction>"
       << "<di_cfVal species=\"Species_1\">0</di_cfVal>"
       << "<di_cfVal species=\"Species_2\">0</di_cfVal>"
       << "</di_canopyFunction>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_1\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_2\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "</GapDisperse2>"
       << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
//  WriteXMLFile4()
/////////////////////////////////////////////////////////////////////////////
const char* clTestTreePopulation::WriteXMLFile4()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>6</timesteps>"
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
       << "<tr_madVal species=\"Species_1\">9.8</tr_madVal>"
       << "<tr_madVal species=\"Species_2\">10</tr_madVal>"
       << "</tr_minAdultDBH>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>"
       << "<tr_treemap>"
       << "<tm_treeSettings sp=\"Species_1\" tp=\"1\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"Diam10\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_2\" tp=\"1\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"Diam10\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_1\" tp=\"2\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_2\" tp=\"2\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_1\" tp=\"3\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_2\" tp=\"3\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_1\" tp=\"5\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_2\" tp=\"5\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tree sp=\"0\" tp=\"1\">"
       << "<fl c=\"0\">1</fl>"
       << "<fl c=\"1\">1</fl>"
       << "<fl c=\"2\">0.3</fl>"
       << "</tree>"
       << "<tree sp=\"1\" tp=\"1\">"
       << "<fl c=\"0\">2</fl>"
       << "<fl c=\"1\">2</fl>"
       << "<fl c=\"2\">0.3</fl>"
       << "</tree>"
       << "<tree sp=\"0\" tp=\"2\">"
       << "<fl c=\"0\">3</fl>"
       << "<fl c=\"1\">3</fl>"
       << "<fl c=\"2\">3</fl>"
       << "</tree>"
       << "<tree sp=\"1\" tp=\"2\">"
       << "<fl c=\"0\">4</fl>"
       << "<fl c=\"1\">4</fl>"
       << "<fl c=\"2\">3</fl>"
       << "</tree>"
       << "<tree sp=\"0\" tp=\"3\">"
       << "<fl c=\"0\">5</fl>"
       << "<fl c=\"1\">5</fl>"
       << "<fl c=\"2\">33</fl>"
       << "</tree>"
       << "<tree sp=\"1\" tp=\"3\">"
       << "<fl c=\"0\">6</fl>"
       << "<fl c=\"1\">6</fl>"
       << "<fl c=\"2\">33</fl>"
       << "</tree>"
       << "<tree sp=\"0\" tp=\"5\">"
       << "<fl c=\"0\">7</fl>"
       << "<fl c=\"1\">7</fl>"
       << "<fl c=\"2\">13</fl>"
       << "</tree>"
       << "<tree sp=\"1\" tp=\"5\">"
       << "<fl c=\"0\">8</fl>"
       << "<fl c=\"1\">8</fl>"
       << "<fl c=\"2\">13</fl>"
       << "</tree>"
       << "</tr_treemap>"
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
       << "<tr_screVal species=\"Species_1\">0.9</tr_screVal>"
       << "<tr_screVal species=\"Species_2\">1</tr_screVal>"
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
       << "<tr_scheVal species=\"Species_1\">1</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">0.5</tr_scheVal>"
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
       << "<behaviorName>ConstantGLI</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Snag\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>GapDisperse</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Stump\" />"
       << "<applyTo species=\"Species_2\" type=\"Adult\" />"
       << "</behavior>"
       << "</behaviorList>"
       << "<ConstantGLI1>"
       << "<li_constGLI>100</li_constGLI>"
       << "</ConstantGLI1>"
       << "<GapDisperse2>"
       << "<di_weibullCanopySTR>"
       << "<di_wcsVal species=\"Species_1\">0.0</di_wcsVal>"
       << "<di_wcsVal species=\"Species_2\">0.0</di_wcsVal>"
       << "</di_weibullCanopySTR>"
       << "<di_weibullCanopyBeta>"
       << "<di_wcbVal species=\"Species_1\">0.0</di_wcbVal>"
       << "<di_wcbVal species=\"Species_2\">0.0</di_wcbVal>"
       << "</di_weibullCanopyBeta>"
       << "<di_weibullCanopyDispersal>"
       << "<di_wcdVal species=\"Species_1\">0.0</di_wcdVal>"
       << "<di_wcdVal species=\"Species_2\">0.0</di_wcdVal>"
       << "</di_weibullCanopyDispersal>"
       << "<di_weibullCanopyTheta>"
       << "<di_wctVal species=\"Species_1\">0.0</di_wctVal>"
       << "<di_wctVal species=\"Species_2\">0.0</di_wctVal>"
       << "</di_weibullCanopyTheta>"
       << "<di_weibullGapSTR>"
       << "<di_wgsVal species=\"Species_1\">0.0</di_wgsVal>"
       << "<di_wgsVal species=\"Species_2\">0.0</di_wgsVal>"
       << "</di_weibullGapSTR>"
       << "<di_weibullGapBeta>"
       << "<di_wgbVal species=\"Species_1\">0.0</di_wgbVal>"
       << "<di_wgbVal species=\"Species_2\">0.0</di_wgbVal>"
       << "</di_weibullGapBeta>"
       << "<di_weibullGapDispersal>"
       << "<di_wgdVal species=\"Species_1\">0.0</di_wgdVal>"
       << "<di_wgdVal species=\"Species_2\">0.0</di_wgdVal>"
       << "</di_weibullGapDispersal>"
       << "<di_weibullGapTheta>"
       << "<di_wgtVal species=\"Species_1\">0.0</di_wgtVal>"
       << "<di_wgtVal species=\"Species_2\">0.0</di_wgtVal>"
       << "</di_weibullGapTheta>"
       << "<di_lognormalCanopySTR>"
       << "<di_lcsVal species=\"Species_1\">0.0</di_lcsVal>"
       << "<di_lcsVal species=\"Species_2\">0.0</di_lcsVal>"
       << "</di_lognormalCanopySTR>"
       << "<di_lognormalCanopyBeta>"
       << "<di_lcbVal species=\"Species_1\">0.0</di_lcbVal>"
       << "<di_lcbVal species=\"Species_2\">0.0</di_lcbVal>"
       << "</di_lognormalCanopyBeta>"
       << "<di_lognormalCanopyX0>"
       << "<di_lcx0Val species=\"Species_1\">0.0</di_lcx0Val>"
       << "<di_lcx0Val species=\"Species_2\">0.0</di_lcx0Val>"
       << "</di_lognormalCanopyX0>"
       << "<di_lognormalCanopyXb>"
       << "<di_lcxbVal species=\"Species_1\">0.0</di_lcxbVal>"
       << "<di_lcxbVal species=\"Species_2\">0.0</di_lcxbVal>"
       << "</di_lognormalCanopyXb>"
       << "<di_lognormalGapSTR>"
       << "<di_lgsVal species=\"Species_1\">0.0</di_lgsVal>"
       << "<di_lgsVal species=\"Species_2\">0.0</di_lgsVal>"
       << "</di_lognormalGapSTR>"
       << "<di_lognormalGapBeta>"
       << "<di_lgbVal species=\"Species_1\">0.0</di_lgbVal>"
       << "<di_lgbVal species=\"Species_2\">0.0</di_lgbVal>"
       << "</di_lognormalGapBeta>"
       << "<di_lognormalGapX0>"
       << "<di_lgx0Val species=\"Species_1\">0.0</di_lgx0Val>"
       << "<di_lgx0Val species=\"Species_2\">0.0</di_lgx0Val>"
       << "</di_lognormalGapX0>"
       << "<di_lognormalGapXb>"
       << "<di_lgxbVal species=\"Species_1\">0.0</di_lgxbVal>"
       << "<di_lgxbVal species=\"Species_2\">0.0</di_lgxbVal>"
       << "</di_lognormalGapXb>"
       << "<di_suckerSTR>"
       << "<di_ssVal species=\"Species_1\">0.0</di_ssVal>"
       << "<di_ssVal species=\"Species_2\">0.0</di_ssVal>"
       << "</di_suckerSTR>"
       << "<di_suckerBeta>"
       << "<di_sbVal species=\"Species_1\">0.0</di_sbVal>"
       << "<di_sbVal species=\"Species_2\">0.0</di_sbVal>"
       << "</di_suckerBeta>"
       << "<di_maxGapDensity>0</di_maxGapDensity>"
       << "<di_gapFunction>"
       << "<di_gfVal species=\"Species_1\">0</di_gfVal>"
       << "<di_gfVal species=\"Species_2\">0</di_gfVal>"
       << "</di_gapFunction>"
       << "<di_canopyFunction>"
       << "<di_cfVal species=\"Species_1\">0</di_cfVal>"
       << "<di_cfVal species=\"Species_2\">0</di_cfVal>"
       << "</di_canopyFunction>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_1\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_2\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "</GapDisperse2>"
       << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
//  WriteXMLFile5()
/////////////////////////////////////////////////////////////////////////////
const char* clTestTreePopulation::WriteXMLFile5()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>2</timesteps>"
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
       << "<tr_species speciesName=\"Species_1\"/>"
       << "<tr_species speciesName=\"Species_2\"/>"
       << "</tr_speciesList>"
       << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"Species_1\">9.8</tr_madVal>"
       << "<tr_madVal species=\"Species_2\">10</tr_madVal>"
       << "</tr_minAdultDBH>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>"
       << "<tr_treemap>"
       << "<tm_treeSettings sp=\"Species_1\" tp=\"1\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"Diam10\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_2\" tp=\"1\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"Diam10\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_1\" tp=\"2\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_2\" tp=\"2\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_1\" tp=\"3\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_2\" tp=\"3\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_1\" tp=\"5\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_2\" tp=\"5\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tree sp=\"0\" tp=\"1\">"
       << "<fl c=\"0\">1</fl>"
       << "<fl c=\"1\">1</fl>"
       << "<fl c=\"2\">0.3</fl>"
       << "</tree>"
       << "<tree sp=\"1\" tp=\"1\">"
       << "<fl c=\"0\">2</fl>"
       << "<fl c=\"1\">2</fl>"
       << "<fl c=\"2\">0.3</fl>"
       << "</tree>"
       << "<tree sp=\"0\" tp=\"2\">"
       << "<fl c=\"0\">3</fl>"
       << "<fl c=\"1\">3</fl>"
       << "<fl c=\"2\">3</fl>"
       << "</tree>"
       << "<tree sp=\"1\" tp=\"2\">"
       << "<fl c=\"0\">4</fl>"
       << "<fl c=\"1\">4</fl>"
       << "<fl c=\"2\">3</fl>"
       << "</tree>"
       << "<tree sp=\"0\" tp=\"3\">"
       << "<fl c=\"0\">5</fl>"
       << "<fl c=\"1\">5</fl>"
       << "<fl c=\"2\">33</fl>"
       << "</tree>"
       << "<tree sp=\"1\" tp=\"3\">"
       << "<fl c=\"0\">6</fl>"
       << "<fl c=\"1\">6</fl>"
       << "<fl c=\"2\">33</fl>"
       << "</tree>"
       << "<tree sp=\"0\" tp=\"5\">"
       << "<fl c=\"0\">7</fl>"
       << "<fl c=\"1\">7</fl>"
       << "<fl c=\"2\">13</fl>"
       << "</tree>"
       << "<tree sp=\"1\" tp=\"5\">"
       << "<fl c=\"0\">8</fl>"
       << "<fl c=\"1\">8</fl>"
       << "<fl c=\"2\">13</fl>"
       << "</tree>"
       << "</tr_treemap>"
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
       << "<tr_screVal species=\"Species_1\">0.9</tr_screVal>"
       << "<tr_screVal species=\"Species_2\">1</tr_screVal>"
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
       << "<tr_scheVal species=\"Species_1\">1</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">0.5</tr_scheVal>"
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
       << "<behaviorName>ConstantGLI</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Snag\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>GapDisperse</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Stump\" />"
       << "<applyTo species=\"Species_2\" type=\"Adult\" />"
       << "</behavior>"
       << "</behaviorList>"
       << "<ConstantGLI1>"
       << "<li_constGLI>100</li_constGLI>"
       << "</ConstantGLI1>"
       << "<GapDisperse2>"
       << "<di_weibullCanopySTR>"
       << "<di_wcsVal species=\"Species_1\">0.0</di_wcsVal>"
       << "<di_wcsVal species=\"Species_2\">0.0</di_wcsVal>"
       << "</di_weibullCanopySTR>"
       << "<di_weibullCanopyBeta>"
       << "<di_wcbVal species=\"Species_1\">0.0</di_wcbVal>"
       << "<di_wcbVal species=\"Species_2\">0.0</di_wcbVal>"
       << "</di_weibullCanopyBeta>"
       << "<di_weibullCanopyDispersal>"
       << "<di_wcdVal species=\"Species_1\">0.0</di_wcdVal>"
       << "<di_wcdVal species=\"Species_2\">0.0</di_wcdVal>"
       << "</di_weibullCanopyDispersal>"
       << "<di_weibullCanopyTheta>"
       << "<di_wctVal species=\"Species_1\">0.0</di_wctVal>"
       << "<di_wctVal species=\"Species_2\">0.0</di_wctVal>"
       << "</di_weibullCanopyTheta>"
       << "<di_weibullGapSTR>"
       << "<di_wgsVal species=\"Species_1\">0.0</di_wgsVal>"
       << "<di_wgsVal species=\"Species_2\">0.0</di_wgsVal>"
       << "</di_weibullGapSTR>"
       << "<di_weibullGapBeta>"
       << "<di_wgbVal species=\"Species_1\">0.0</di_wgbVal>"
       << "<di_wgbVal species=\"Species_2\">0.0</di_wgbVal>"
       << "</di_weibullGapBeta>"
       << "<di_weibullGapDispersal>"
       << "<di_wgdVal species=\"Species_1\">0.0</di_wgdVal>"
       << "<di_wgdVal species=\"Species_2\">0.0</di_wgdVal>"
       << "</di_weibullGapDispersal>"
       << "<di_weibullGapTheta>"
       << "<di_wgtVal species=\"Species_1\">0.0</di_wgtVal>"
       << "<di_wgtVal species=\"Species_2\">0.0</di_wgtVal>"
       << "</di_weibullGapTheta>"
       << "<di_lognormalCanopySTR>"
       << "<di_lcsVal species=\"Species_1\">0.0</di_lcsVal>"
       << "<di_lcsVal species=\"Species_2\">0.0</di_lcsVal>"
       << "</di_lognormalCanopySTR>"
       << "<di_lognormalCanopyBeta>"
       << "<di_lcbVal species=\"Species_1\">0.0</di_lcbVal>"
       << "<di_lcbVal species=\"Species_2\">0.0</di_lcbVal>"
       << "</di_lognormalCanopyBeta>"
       << "<di_lognormalCanopyX0>"
       << "<di_lcx0Val species=\"Species_1\">0.0</di_lcx0Val>"
       << "<di_lcx0Val species=\"Species_2\">0.0</di_lcx0Val>"
       << "</di_lognormalCanopyX0>"
       << "<di_lognormalCanopyXb>"
       << "<di_lcxbVal species=\"Species_1\">0.0</di_lcxbVal>"
       << "<di_lcxbVal species=\"Species_2\">0.0</di_lcxbVal>"
       << "</di_lognormalCanopyXb>"
       << "<di_lognormalGapSTR>"
       << "<di_lgsVal species=\"Species_1\">0.0</di_lgsVal>"
       << "<di_lgsVal species=\"Species_2\">0.0</di_lgsVal>"
       << "</di_lognormalGapSTR>"
       << "<di_lognormalGapBeta>"
       << "<di_lgbVal species=\"Species_1\">0.0</di_lgbVal>"
       << "<di_lgbVal species=\"Species_2\">0.0</di_lgbVal>"
       << "</di_lognormalGapBeta>"
       << "<di_lognormalGapX0>"
       << "<di_lgx0Val species=\"Species_1\">0.0</di_lgx0Val>"
       << "<di_lgx0Val species=\"Species_2\">0.0</di_lgx0Val>"
       << "</di_lognormalGapX0>"
       << "<di_lognormalGapXb>"
       << "<di_lgxbVal species=\"Species_1\">0.0</di_lgxbVal>"
       << "<di_lgxbVal species=\"Species_2\">0.0</di_lgxbVal>"
       << "</di_lognormalGapXb>"
       << "<di_suckerSTR>"
       << "<di_ssVal species=\"Species_1\">0.0</di_ssVal>"
       << "<di_ssVal species=\"Species_2\">0.0</di_ssVal>"
       << "</di_suckerSTR>"
       << "<di_suckerBeta>"
       << "<di_sbVal species=\"Species_1\">0.0</di_sbVal>"
       << "<di_sbVal species=\"Species_2\">0.0</di_sbVal>"
       << "</di_suckerBeta>"
       << "<di_maxGapDensity>0</di_maxGapDensity>"
       << "<di_gapFunction>"
       << "<di_gfVal species=\"Species_1\">0</di_gfVal>"
       << "<di_gfVal species=\"Species_2\">0</di_gfVal>"
       << "</di_gapFunction>"
       << "<di_canopyFunction>"
       << "<di_cfVal species=\"Species_1\">0</di_cfVal>"
       << "<di_cfVal species=\"Species_2\">0</di_cfVal>"
       << "</di_canopyFunction>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_1\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_2\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "</GapDisperse2>"
       << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
//  WriteXMLFile6()
/////////////////////////////////////////////////////////////////////////////
const char* clTestTreePopulation::WriteXMLFile6()
{
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
       << "<tr_madVal species=\"Species_1\">9.8</tr_madVal>"
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
       << "<tr_screVal species=\"Species_1\">0.9</tr_screVal>"
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
       << "<tr_scheVal species=\"Species_1\">1</tr_scheVal>"
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
       << "<behaviorName>ConstantGLI</behaviorName>"
       << "<listPosition>1</listPosition>"
       << "<version>1</version>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<ConstantGLI1>"
       << "<li_constGLI>100</li_constGLI>"
       << "</ConstantGLI1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}
