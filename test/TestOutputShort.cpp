//---------------------------------------------------------------------------
// TestOutput.cpp
//---------------------------------------------------------------------------
#include "TestOutputShort.h"
#include "SimManager.h"
#include "TreePopulation.h"
#include "PlatformFuncs.h"
#include "DataTypes.h"
#include <stdio.h>
#include <fstream>
#include <math.h>
#include <iostream>

/////////////////////////////////////////////////////////////////////////////
// TestOutput()
/////////////////////////////////////////////////////////////////////////////
void clTestOutputShort::TestOutputShort() {
  clSimManager *p_oSimManager = new clSimManager(3, 3, "");

  NormalProcessingRun1(p_oSimManager);
  NormalProcessingRun2(p_oSimManager);
  NormalProcessingRun3(p_oSimManager);

  delete p_oSimManager;
}

/////////////////////////////////////////////////////////////////////////////
// NormalProcessingRun1()
/////////////////////////////////////////////////////////////////////////////
void clTestOutputShort::NormalProcessingRun1(clSimManager *p_oSimManager) {

  //Feed our file to the sim manager
  p_oSimManager->ReadFile(WriteXMLFile1());
  //Run one timestep
  p_oSimManager->RunSim(1);

  //Verify that the output file has been created
  CPPUNIT_ASSERT(DoesFileExist("Short Run 1.out"));

  ifstream infile;
  char cNum[21], cTemp[5001] ;
  float fExp, fAct;
  infile.open ("Short Run 1.out", ifstream::in);

  if (infile.is_open()) {
    //while (infile.good()) {
    infile.getline(cTemp, 5000);
    infile.getline(cTemp, 5000);
    infile.getline(cTemp, 5000);
    infile.getline(cTemp, 5000);
    infile.getline(cTemp, 5000);
    infile.getline(cTemp, 5000);
    infile.getline(cTemp, 5000);
    infile.getline(cTemp, 5000); //Header

     //Initial conditions, whole plot
    infile.getline(cNum, 20, '\t');
    fExp = 0; //Step
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; //Subplot
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 1.333333333; //Sdl Abs Den Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.222222222; //Sdl Abs Den Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 3.555555556; //Sdl Den Total
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.006581459; //Sapl Abs BA Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.012186611; //Sapl Abs BA Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.018768069; //Sapl BA Total
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.350673186; //Sapl Rel BA Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.649326814; //Sapl Rel BA Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.222222222; //Sapl Abs Den Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 4.444444444; //Sapl Abs Den Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 6.666666667; //Sapl Den Total
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.333333333; //Sapl Rel Den Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.666666667; //Sapl Rel Den Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.210353602; //Adult Abs BA Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.510873154; //Adult Abs BA Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.721226756; //Adult BA Total
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.812263659; //Adult Rel BA Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.187736341; //Adult Rel BA Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.666666667; //Adult Abs Den Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.222222222; //Adult Abs Den Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 4.888888889; //Adult Den Total
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.545454545; //Adult Rel Den Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.454545455; //Adult Rel Den Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 3.671478286; //Snag Abs BA Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 1.079680022; //Snag Abs BA Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 4.751158309; //Snag BA Total
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.772754358; //Snag Rel BA Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.227245642; //Snag Rel BA Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.666666667; //Snag Abs Den Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.222222222; //Snag Abs Den Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 4.888888889; //Snag Den Total
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.545454545; //Snag Rel Den Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20);
    fExp = 0.454545455; //Snag Rel Den Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);


     //Initial conditions, subplot 1
    infile.getline(cNum, 20, '\t');
    fExp = 0; //Step
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 1; //Subplot
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.773668639; //Sdl Abs Den Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 4.622781065; //Sdl Abs Den Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 7.396449704; //Sdl Den Total
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.013691089; //Sapl Abs BA Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.002493047; //Sapl Abs BA Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.016184135; //Sapl BA Total
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.845957385; //Sapl Rel BA Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.154042615; //Sapl Rel BA Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 4.622781065; //Sapl Abs Den Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.773668639; //Sapl Abs Den Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 7.396449704; //Sapl Den Total
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.625; //Sapl Rel Den Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.375; //Sapl Rel Den Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; //Adult Abs BA Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 1.062744634; //Adult Abs BA Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 1.062744634; //Adult BA Total
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; //Adult Rel BA Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 1; //Adult Rel BA Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; //Adult Abs Den Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 4.622781065; //Adult Abs Den Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 4.622781065; //Adult Den Total
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; //Adult Rel Den Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 1; //Adult Rel Den Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 7.637598136; //Snag Abs BA Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.246005963; //Snag Abs BA Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 9.8836041; //Snag BA Total
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.772754358; //Snag Rel BA Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.227245642; //Snag Rel BA Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 5.547337278; //Snag Abs Den Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 4.622781065; //Snag Abs Den Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 10.17011834; //Snag Den Total
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.545454545; //Snag Rel Den Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20);
    fExp = 0.454545455; //Snag Rel Den Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);

    //Initial conditions, subplot 2
    infile.getline(cNum, 20, '\t');
    fExp = 0; //Step
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2; //Subplot
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; //Sdl Abs Den Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.325581395; //Sdl Abs Den Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.325581395; //Sdl Den Total
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.00528398; // Sapl Abs BA Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.020198383; //Sapl Abs BA Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.025482363; //Sapl BA Total
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.207358321; //Sapl Rel BA Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.792641679; //Sapl Rel BA Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.325581395; //Sapl Abs Den Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 6.201550388; //Sapl Abs Den Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 8.527131783; //Sapl Den Total
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.272727273; //Sapl Rel Den Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.727272727; //Sapl Rel Den Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 3.85526791; // Adult Abs BA Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.891057827; //Adult Abs BA Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 4.746325737; //Adult BA Total
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.812263659; //Adult Rel BA Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.187736341; //Adult Rel BA Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 4.651162791; //Adult Abs Den Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 3.875968992; //Adult Abs Den Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 8.527131783; //Adult Den Total
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.545454545; //Adult Rel Den Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.454545455; //Adult Rel Den Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.170564273; //Snag Abs BA Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; //Snag Abs BA Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.170564273; //Snag BA Total
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 1; //Snag Rel BA Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; //Snag Rel BA Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 1.550387597; //Snag Abs Den Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; //Snag Abs Den Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 1.550387597; //Snag Den Total
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 1; //Snag Rel Den Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20);
    fExp = 0; //Snag Rel Den Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);

    infile.close();
  } else {
    cout << "Error opening file";
  }

  DeleteThisFile("Short Run 1.out");
  CPPUNIT_ASSERT(!DoesFileExist("Short Run 1.out"));

}

/////////////////////////////////////////////////////////////////////////////
// NormalProcessingRun2()
/////////////////////////////////////////////////////////////////////////////
void clTestOutputShort::NormalProcessingRun2(clSimManager *p_oSimManager) {

  //Feed our file to the sim manager
  p_oSimManager->ReadFile(WriteXMLFile2());
  clTreePopulation *p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject("treepopulation");
  clTree *p_oTree;
  float fX, fY, fDiam;
  int iDead, iSp, iTp;

  //Create dead trees
  fX = 15.7288; fY = 36.0596;
  iTp = clTreePopulation::snag; iSp = 1; fDiam = 35.04523872; iDead = harvest;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::snag; iSp = 0; fDiam = 56.2373354; iDead = natural;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::snag; iSp = 1; fDiam = 53.80508187; iDead = natural;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::sapling; iSp = 0; fDiam = 5.339709196; iDead = disease;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::seedling; iSp = 1; fDiam = 0.1; iDead = disease;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::sapling; iSp = 1; fDiam = 8.158679444; iDead = disease;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::adult; iSp = 1; fDiam = 55.31119422; iDead = fire;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::seedling; iSp = 0; fDiam = 0.1; iDead = fire;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::sapling; iSp = 1; fDiam = 7.356514522; iDead = fire;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::seedling; iSp = 1; fDiam = 0.1; iDead = fire;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::seedling; iSp = 1; fDiam = 0.1; iDead = fire;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::seedling; iSp = 0; fDiam = 0.1; iDead = insects;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::snag; iSp = 1; fDiam = 48.09070743; iDead = insects;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::seedling; iSp = 1; fDiam = 0.1; iDead = insects;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::snag; iSp = 0; fDiam = 28.89395384; iDead = insects;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::adult; iSp = 0; fDiam = 10.37021475; iDead = insects;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::seedling; iSp = 1; fDiam = 0.1; iDead = storm;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::adult; iSp = 1; fDiam = 36.77501151; iDead = storm;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::seedling; iSp = 1; fDiam = 0.1; iDead = storm;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::sapling; iSp = 1; fDiam = 8.30976872; iDead = storm;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::seedling; iSp = 0; fDiam = 0.1; iDead = storm;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::snag; iSp = 1; fDiam = 48.45715508; iDead = storm;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::sapling; iSp = 1; fDiam = 5.779524893; iDead = storm;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::snag; iSp = 1; fDiam = 39.1111815; iDead = remove_tree;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::adult; iSp = 0; fDiam = 58.76941482; iDead = remove_tree;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::sapling; iSp = 0; fDiam = 0.186498229; iDead = remove_tree;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::sapling; iSp = 0; fDiam = 7.329027055; iDead = remove_tree;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::adult; iSp = 1; fDiam = 15.13257052; iDead = remove_tree;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::sapling; iSp = 0; fDiam = 8.754955642; iDead = remove_tree;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::seedling; iSp = 0; fDiam = 0.1; iDead = remove_tree;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::snag; iSp = 0; fDiam = 10.40033328; iDead = remove_tree;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::adult; iSp = 1; fDiam = 26.96989998; iDead = remove_tree;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::sapling; iSp = 0; fDiam = 1.319946108; iDead = remove_tree;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::snag; iSp = 0; fDiam = 54.25924969; iDead = remove_tree;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::adult; iSp = 1; fDiam = 31.59205228; iDead = remove_tree;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::adult; iSp = 1; fDiam = 35.01872194; iDead = remove_tree;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::sapling; iSp = 0; fDiam = 6.612757597; iDead = harvest;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::adult; iSp = 0; fDiam = 11.9346109; iDead = remove_tree;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::seedling; iSp = 0; fDiam = 0.1; iDead = fire;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::seedling; iSp = 1; fDiam = 0.1; iDead = storm;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::seedling; iSp = 0; fDiam = 0.1; iDead = natural;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::sapling; iSp = 1; fDiam = 8.586264061; iDead = disease;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::sapling; iSp = 1; fDiam = 8.833394024; iDead = storm;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::snag; iSp = 0; fDiam = 13.29596774; iDead = harvest;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::seedling; iSp = 0; fDiam = 0.1; iDead = disease;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::snag; iSp = 1; fDiam = 59.51475428; iDead = storm;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::seedling; iSp = 0; fDiam = 0.1; iDead = natural;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::adult; iSp = 0; fDiam = 45.18388484; iDead = disease;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::snag; iSp = 1; fDiam = 27.76072762; iDead = insects;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::sapling; iSp = 0; fDiam = 5.26697542; iDead = harvest;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::sapling; iSp = 0; fDiam = 9.640456798; iDead = natural;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::sapling; iSp = 1; fDiam = 6.305955991; iDead = natural;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::snag; iSp = 1; fDiam = 11.61954534; iDead = storm;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::sapling; iSp = 0; fDiam = 6.278535356; iDead = natural;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::snag; iSp = 0; fDiam = 55.5413574; iDead = natural;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::seedling; iSp = 0; fDiam = 0.1; iDead = storm;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::sapling; iSp = 0; fDiam = 7.248720633; iDead = disease;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::sapling; iSp = 1; fDiam = 7.676735429; iDead = storm;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::snag; iSp = 0; fDiam = 22.44437042; iDead = harvest;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::seedling; iSp = 0; fDiam = 0.1; iDead = harvest;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::sapling; iSp = 1; fDiam = 2.797971866; iDead = insects;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
 p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::adult; iSp = 1; fDiam = 10.38040263; iDead = remove_tree;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::snag; iSp = 0; fDiam = 31.68417906; iDead = fire;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::adult; iSp = 1; fDiam = 44.23276857; iDead = fire;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::sapling; iSp = 1; fDiam = 6.421950441; iDead = natural;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::seedling; iSp = 1; fDiam = 0.1; iDead = natural;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::sapling; iSp = 1; fDiam = 4.425348657; iDead = harvest;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::adult; iSp = 0; fDiam = 21.44889387; iDead = remove_tree;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::snag; iSp = 1; fDiam = 42.42071846; iDead = storm;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::adult; iSp = 0; fDiam = 14.35184038; iDead = disease;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::seedling; iSp = 0; fDiam = 0.1; iDead = insects;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::snag; iSp = 0; fDiam = 43.91851122; iDead = storm;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::snag; iSp = 1; fDiam = 33.43999281; iDead = disease;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::seedling; iSp = 1; fDiam = 0.1; iDead = natural;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::seedling; iSp = 1; fDiam = 0.1; iDead = insects;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::sapling; iSp = 1; fDiam = 0.559285995; iDead = fire;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::seedling; iSp = 0; fDiam = 0.1; iDead = storm;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::seedling; iSp = 1; fDiam = 0.1; iDead = fire;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::seedling; iSp = 0; fDiam = 0.1; iDead = natural;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::sapling; iSp = 1; fDiam = 5.384247855; iDead = storm;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::snag; iSp = 1; fDiam = 37.88555597; iDead = storm;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::sapling; iSp = 1; fDiam = 4.283149345; iDead = storm;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::sapling; iSp = 0; fDiam = 2.780768137; iDead = insects;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::sapling; iSp = 0; fDiam = 0.137235154; iDead = disease;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::sapling; iSp = 0; fDiam = 5.923894264; iDead = natural;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
 p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::seedling; iSp = 0; fDiam = 0.1; iDead = remove_tree;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::adult; iSp = 0; fDiam = 56.74632464; iDead = disease;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::adult; iSp = 0; fDiam = 46.98617101; iDead = disease;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::snag; iSp = 1; fDiam = 44.45224322; iDead = insects;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::snag; iSp = 0; fDiam = 23.60044213; iDead = remove_tree;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::adult; iSp = 1; fDiam = 39.40256465; iDead = storm;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::seedling; iSp = 1; fDiam = 0.1; iDead = remove_tree;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::seedling; iSp = 0; fDiam = 0.1; iDead = insects;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::sapling; iSp = 0; fDiam = 8.954006578; iDead = natural;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
 p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::snag; iSp = 1; fDiam = 43.27999221; iDead = storm;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::snag; iSp = 1; fDiam = 31.80702296; iDead = insects;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::snag; iSp = 0; fDiam = 48.51729803; iDead = storm;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::sapling; iSp = 0; fDiam = 3.153833785; iDead = storm;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::adult; iSp = 0; fDiam = 34.62380431; iDead = harvest;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::adult; iSp = 1; fDiam = 25.84225253; iDead = storm;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::adult; iSp = 0; fDiam = 11.49877166; iDead = insects;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::seedling; iSp = 1; fDiam = 0.1; iDead = insects;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::adult; iSp = 0; fDiam = 15.71488345; iDead = insects;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::adult; iSp = 0; fDiam = 48.49289149; iDead = natural;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::sapling; iSp = 0; fDiam = 1.861199754; iDead = natural;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::sapling; iSp = 1; fDiam = 0.402643648; iDead = fire;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::sapling; iSp = 0; fDiam = 4.272992666; iDead = natural;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::seedling; iSp = 0; fDiam = 0.1; iDead = insects;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::adult; iSp = 1; fDiam = 43.17878428; iDead = harvest;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::sapling; iSp = 1; fDiam = 3.530260052; iDead = fire;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::sapling; iSp = 1; fDiam = 8.867118981; iDead = natural;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::snag; iSp = 1; fDiam = 48.65051881; iDead = remove_tree;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::snag; iSp = 0; fDiam = 55.03461708; iDead = insects;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::snag; iSp = 1; fDiam = 29.16249551; iDead = insects;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::snag; iSp = 0; fDiam = 24.69165155; iDead = disease;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::snag; iSp = 1; fDiam = 30.05713377; iDead = fire;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::sapling; iSp = 0; fDiam = 3.636145943; iDead = harvest;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::adult; iSp = 0; fDiam = 44.80775341; iDead = natural;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::sapling; iSp = 1; fDiam = 3.883732777; iDead = insects;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::snag; iSp = 0; fDiam = 20.02281069; iDead = disease;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::adult; iSp = 0; fDiam = 42.39682134; iDead = insects;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::adult; iSp = 0; fDiam = 53.93957579; iDead = insects;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::sapling; iSp = 0; fDiam = 2.637483332; iDead = storm;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::seedling; iSp = 1; fDiam = 0.1; iDead = harvest;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::seedling; iSp = 0; fDiam = 0.1; iDead = remove_tree;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::adult; iSp = 1; fDiam = 35.78034328; iDead = insects;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::snag; iSp = 0; fDiam = 43.40956406; iDead = natural;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::seedling; iSp = 0; fDiam = 0.1; iDead = remove_tree;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::snag; iSp = 1; fDiam = 21.21350419; iDead = natural;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::sapling; iSp = 1; fDiam = 8.870560369; iDead = insects;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::adult; iSp = 1; fDiam = 37.71209406; iDead = disease;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::adult; iSp = 1; fDiam = 25.89938385; iDead = insects;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::sapling; iSp = 1; fDiam = 0.87689794; iDead = insects;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::sapling; iSp = 0; fDiam = 6.395076179; iDead = disease;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::snag; iSp = 0; fDiam = 18.0272108; iDead = insects;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::sapling; iSp = 0; fDiam = 9.17906555; iDead = remove_tree;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::sapling; iSp = 1; fDiam = 1.626184657; iDead = fire;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::seedling; iSp = 0; fDiam = 0.1; iDead = fire;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::snag; iSp = 1; fDiam = 31.6499312; iDead = storm;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::adult; iSp = 0; fDiam = 41.22942698; iDead = remove_tree;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::sapling; iSp = 0; fDiam = 2.293737071; iDead = remove_tree;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::adult; iSp = 1; fDiam = 44.91765093; iDead = natural;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::snag; iSp = 0; fDiam = 16.22505271; iDead = fire;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::seedling; iSp = 0; fDiam = 0.1; iDead = insects;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::seedling; iSp = 1; fDiam = 0.1; iDead = disease;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::snag; iSp = 1; fDiam = 27.86818493; iDead = remove_tree;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::sapling; iSp = 0; fDiam = 1.117957649; iDead = insects;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::adult; iSp = 0; fDiam = 37.92743569; iDead = fire;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
 p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::snag; iSp = 0; fDiam = 19.17749933; iDead = storm;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::sapling; iSp = 0; fDiam = 3.842197674; iDead = storm;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::seedling; iSp = 1; fDiam = 0.1; iDead = harvest;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::snag; iSp = 1; fDiam = 28.23254556; iDead = natural;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::sapling; iSp = 1; fDiam = 9.914087091; iDead = natural;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::snag; iSp = 0; fDiam = 11.48903653; iDead = harvest;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::seedling; iSp = 1; fDiam = 0.1; iDead = insects;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::adult; iSp = 0; fDiam = 31.91198791; iDead = harvest;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::snag; iSp = 1; fDiam = 26.47799095; iDead = storm;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::sapling; iSp = 1; fDiam = 5.858131847; iDead = natural;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::adult; iSp = 1; fDiam = 32.23335558; iDead = disease;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::snag; iSp = 1; fDiam = 32.84481276; iDead = storm;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::adult; iSp = 1; fDiam = 59.29438984; iDead = fire;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::adult; iSp = 0; fDiam = 13.36485472; iDead = harvest;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
 p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::snag; iSp = 0; fDiam = 48.82752482; iDead = harvest;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::sapling; iSp = 1; fDiam = 8.02871339; iDead = disease;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::adult; iSp = 0; fDiam = 59.6715678; iDead = fire;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
 p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::snag; iSp = 0; fDiam = 45.37626352; iDead = remove_tree;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::snag; iSp = 0; fDiam = 48.54779063; iDead = fire;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::seedling; iSp = 0; fDiam = 0.1; iDead = storm;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::sapling; iSp = 0; fDiam = 0.07600299; iDead = remove_tree;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::seedling; iSp = 1; fDiam = 0.1; iDead = remove_tree;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::snag; iSp = 0; fDiam = 39.8599689; iDead = remove_tree;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::seedling; iSp = 0; fDiam = 0.1; iDead = insects;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::adult; iSp = 1; fDiam = 37.43326311; iDead = natural;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::sapling; iSp = 1; fDiam = 7.296477739; iDead = disease;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::sapling; iSp = 0; fDiam = 1.37552502; iDead = remove_tree;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::adult; iSp = 0; fDiam = 28.26995004; iDead = insects;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::snag; iSp = 0; fDiam = 20.58622838; iDead = harvest;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::sapling; iSp = 1; fDiam = 3.488299383; iDead = remove_tree;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::seedling; iSp = 0; fDiam = 0.1; iDead = storm;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::sapling; iSp = 1; fDiam = 7.553636002; iDead = insects;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::adult; iSp = 0; fDiam = 42.1458391; iDead = harvest;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::adult; iSp = 1; fDiam = 36.24524668; iDead = natural;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::adult; iSp = 0; fDiam = 50.20408284; iDead = natural;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::snag; iSp = 0; fDiam = 29.1425219; iDead = storm;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::snag; iSp = 1; fDiam = 45.54564415; iDead = remove_tree;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::snag; iSp = 1; fDiam = 11.29381113; iDead = natural;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::seedling; iSp = 1; fDiam = 0.1; iDead = insects;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::sapling; iSp = 1; fDiam = 9.711965996; iDead = harvest;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::seedling; iSp = 1; fDiam = 0.1; iDead = insects;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::sapling; iSp = 1; fDiam = 1.322135257; iDead = disease;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::adult; iSp = 1; fDiam = 29.65233105; iDead = natural;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::adult; iSp = 1; fDiam = 25.82806743; iDead = fire;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::adult; iSp = 0; fDiam = 39.05222002; iDead = insects;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::snag; iSp = 0; fDiam = 12.64117172; iDead = remove_tree;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::sapling; iSp = 0; fDiam = 7.918954095; iDead = disease;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::sapling; iSp = 1; fDiam = 1.08147679; iDead = fire;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::adult; iSp = 1; fDiam = 41.68449668; iDead = harvest;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::sapling; iSp = 1; fDiam = 2.884233891; iDead = remove_tree;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);
  iTp = clTreePopulation::snag; iSp = 0; fDiam = 54.04385315; iDead = harvest;
  p_oTree = p_oPop->CreateTree(fX, fY, iSp, iTp, fDiam);
  p_oTree->SetValue(p_oPop->GetIntDataCode("dead", iSp, iTp), iDead);


  //Run one timestep
  p_oSimManager->RunSim(1);

  //Verify that the output file has been created
  CPPUNIT_ASSERT(DoesFileExist("Short Run 2.out"));

  ifstream infile;
  char cNum[21], cTemp[10000] ;
  float fExp, fAct;
  infile.open ("Short Run 2.out", ifstream::in);

  if (infile.is_open()) {
    //while (infile.good()) {
    infile.getline(cTemp, 9999);
    infile.getline(cTemp, 9999);
    infile.getline(cTemp, 9999);
    infile.getline(cTemp, 9999);
    infile.getline(cTemp, 9999);
    infile.getline(cTemp, 9999); //Header

    //Initial conditions
    infile.getline(cNum, 20, '\t');
    fExp = 0; //Step
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; //Subplot
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 1.333333333; //Sdl Abs Den Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.222222222; //Sdl Abs Den Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 3.555555556; //Sdl Den Total
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.006581459; //Sapl Abs BA Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.012186611; //Sapl Abs BA Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.018768069; //Sapl BA Total
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.350673186; //Sapl Rel BA Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.649326814; //Sapl Rel BA Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.222222222; //Sapl Abs Den Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 4.444444444; //Sapl Abs Den Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 6.666666667; //Sapl Den Total
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.333333333; //Sapl Rel Den Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.666666667; //Sapl Rel Den Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.210353602; //Adult Abs BA Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.510873154; //Adult Abs BA Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.721226756; //Adult BA Total
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.812263659; //Adult Rel BA Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.187736341; //Adult Rel BA Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.666666667; //Adult Abs Den Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.222222222; //Adult Abs Den Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 4.888888889; //Adult Den Total
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.545454545; //Adult Rel Den Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.454545455; //Adult Rel Den Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 3.671478286; //Snag Abs BA Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 1.079680022; //Snag Abs BA Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 4.751158309; //Snag BA Total
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.772754358; //Snag Rel BA Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.227245642; //Snag Rel BA Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.666666667; //Snag Abs Den Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.222222222; //Snag Abs Den Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 4.888888889; //Snag Den Total
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.545454545; //Snag Rel Den Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.454545455; //Snag Rel Den Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sdl Dead harvest Species 1 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sdl Dead harvest Species 2 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sdl Dead harvest Total  Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sdl Dead natural Species 1 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sdl Dead natural Species 2 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sdl Dead natural Total  Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sdl Dead disease Species 1 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sdl Dead disease Species 2 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sdl Dead disease Total  Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sdl Dead fire Species 1 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sdl Dead fire Species 2 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sdl Dead fire Total  Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sdl Dead insects Species 1 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sdl Dead insects Species 2 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sdl Dead insects Total  Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sdl Dead storm Species 1 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sdl Dead storm Species 2 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sdl Dead storm Total  Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sdl Dead remove_tree Species 1 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sdl Dead remove_tree Species 2 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sdl Dead remove_tree Total  Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sapl Dead harvest Species 1 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sapl Dead harvest Species 2 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sapl Dead harvest Total  Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sapl Dead harvest Species 1 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sapl Dead harvest Species 2 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sapl Dead harvest Total  Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sapl Dead natural Species 1 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sapl Dead natural Species 2 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sapl Dead natural Total  Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sapl Dead natural Species 1 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sapl Dead natural Species 2 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sapl Dead natural Total  Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sapl Dead disease Species 1 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sapl Dead disease Species 2 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sapl Dead disease Total  Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sapl Dead disease Species 1 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sapl Dead disease Species 2 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sapl Dead disease Total  Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sapl Dead fire Species 1 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sapl Dead fire Species 2 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sapl Dead fire Total  Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sapl Dead fire Species 1 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sapl Dead fire Species 2 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sapl Dead fire Total  Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sapl Dead insects Species 1 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sapl Dead insects Species 2 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sapl Dead insects Total  Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sapl Dead insects Species 1 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sapl Dead insects Species 2 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sapl Dead insects Total  Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sapl Dead storm Species 1 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sapl Dead storm Species 2 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sapl Dead storm Total  Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sapl Dead storm Species 1 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sapl Dead storm Species 2 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sapl Dead storm Total  Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sapl Dead remove_tree Species 1 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sapl Dead remove_tree Species 2 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sapl Dead remove_tree Total  Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sapl Dead remove_tree Species 1 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sapl Dead remove_tree Species 2 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sapl Dead remove_tree Total  Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Adult Dead harvest Species 1 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Adult Dead harvest Species 2 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Adult Dead harvest Total  Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Adult Dead harvest Species 1 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Adult Dead harvest Species 2 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Adult Dead harvest Total  Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Adult Dead natural Species 1 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Adult Dead natural Species 2 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Adult Dead natural Total  Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Adult Dead natural Species 1 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Adult Dead natural Species 2 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Adult Dead natural Total  Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Adult Dead disease Species 1 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Adult Dead disease Species 2 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Adult Dead disease Total  Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Adult Dead disease Species 1 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Adult Dead disease Species 2 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Adult Dead disease Total  Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Adult Dead fire Species 1 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Adult Dead fire Species 2 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Adult Dead fire Total  Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Adult Dead fire Species 1 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Adult Dead fire Species 2 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Adult Dead fire Total  Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Adult Dead insects Species 1 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Adult Dead insects Species 2 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Adult Dead insects Total  Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Adult Dead insects Species 1 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Adult Dead insects Species 2 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Adult Dead insects Total  Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Adult Dead storm Species 1 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Adult Dead storm Species 2 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Adult Dead storm Total  Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Adult Dead storm Species 1 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Adult Dead storm Species 2 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Adult Dead storm Total  Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Adult Dead remove_tree Species 1 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Adult Dead remove_tree Species 2 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Adult Dead remove_tree Total  Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Adult Dead remove_tree Species 1 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Adult Dead remove_tree Species 2 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Adult Dead remove_tree Total  Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Snag Dead harvest Species 1 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Snag Dead harvest Species 2 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Snag Dead harvest Total  Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Snag Dead harvest Species 1 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Snag Dead harvest Species 2 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Snag Dead harvest Total  Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Snag Dead natural Species 1 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Snag Dead natural Species 2 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Snag Dead natural Total  Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Snag Dead natural Species 1 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Snag Dead natural Species 2 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Snag Dead natural Total  Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Snag Dead disease Species 1 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Snag Dead disease Species 2 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Snag Dead disease Total  Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Snag Dead disease Species 1 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Snag Dead disease Species 2 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Snag Dead disease Total  Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Snag Dead fire Species 1 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Snag Dead fire Species 2 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Snag Dead fire Total  Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Snag Dead fire Species 1 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Snag Dead fire Species 2 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Snag Dead fire Total  Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Snag Dead insects Species 1 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Snag Dead insects Species 2 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Snag Dead insects Total  Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Snag Dead insects Species 1 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Snag Dead insects Species 2 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Snag Dead insects Total  Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Snag Dead storm Species 1 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Snag Dead storm Species 2 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Snag Dead storm Total  Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Snag Dead storm Species 1 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Snag Dead storm Species 2 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Snag Dead storm Total  Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Snag Dead remove_tree Species 1 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Snag Dead remove_tree Species 2 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Snag Dead remove_tree Total  Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Snag Dead remove_tree Species 1 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Snag Dead remove_tree Species 2 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20);
    fExp = 0; // Snag Dead remove_tree Total  Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);





    //Timestep 1
    infile.getline(cNum, 20, '\t');
    fExp = 1; //Step
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; //Subplot
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 10001.3; //Sdl Abs Den Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 20002.2; //Sdl Abs Den Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 30003.6; //Sdl Den Total
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.006581459; //Sapl Abs BA Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.012186611; //Sapl Abs BA Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.018768069; //Sapl BA Total
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.350673186; //Sapl Rel BA Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.649326814; //Sapl Rel BA Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.222222222; //Sapl Abs Den Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 4.444444444; //Sapl Abs Den Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 6.666666667; //Sapl Den Total
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.333333333; //Sapl Rel Den Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.666666667; //Sapl Rel Den Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.210353602; //Adult Abs BA Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.510873154; //Adult Abs BA Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.721226756; //Adult BA Total
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.812263659; //Adult Rel BA Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.187736341; //Adult Rel BA Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.666666667; //Adult Abs Den Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.222222222; //Adult Abs Den Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 4.888888889; //Adult Den Total
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.545454545; //Adult Rel Den Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.454545455; //Adult Rel Den Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 4.616479512; //Snag Abs BA Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 1.875396252; //Snag Abs BA Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 6.491875764; //Snag BA Total
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.711116429; //Snag Rel BA Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.288883571; //Snag Rel BA Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 9.777777778; //Snag Abs Den Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 8.888888889; //Snag Abs Den Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 18.66666667; //Snag Den Total
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.523809524; //Snag Rel Den Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.476190476; //Snag Rel Den Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.444444444; // Sdl Dead harvest Species 1 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.888888889; // Sdl Dead harvest Species 2 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 1.333333333; // Sdl Dead harvest Total  Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 1.333333333; // Sdl Dead natural Species 1 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.888888889; // Sdl Dead natural Species 2 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.222222222; // Sdl Dead natural Total  Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.444444444; // Sdl Dead disease Species 1 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.888888889; // Sdl Dead disease Species 2 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 1.333333333; // Sdl Dead disease Total  Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 1.333333333; // Sdl Dead fire Species 1 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 1.333333333; // Sdl Dead fire Species 2 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.666666667; // Sdl Dead fire Total  Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.666666667; // Sdl Dead insects Species 1 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.666666667; // Sdl Dead insects Species 2 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 5.333333333; // Sdl Dead insects Total  Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.222222222; // Sdl Dead storm Species 1 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 1.333333333; // Sdl Dead storm Species 2 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 3.555555556; // Sdl Dead storm Total  Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 1.777777778; // Sdl Dead remove_tree Species 1 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.888888889; // Sdl Dead remove_tree Species 2 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.666666667; // Sdl Dead remove_tree Total  Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.002956279; // Sapl Dead harvest Species 1 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.003976069; // Sapl Dead harvest Species 2 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.006932348; // Sapl Dead harvest Total  Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 1.333333333; // Sapl Dead harvest Species 1 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.888888889; // Sapl Dead harvest Species 2 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.222222222; // Sapl Dead harvest Total  Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.009402008; // Sapl Dead natural Species 1 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.010201071; // Sapl Dead natural Species 2 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.01960308; //  Sapl Dead natural Total  Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.666666667; // Sapl Dead natural Species 1 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.222222222; // Sapl Dead natural Species 2 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 4.888888889; // Sapl Dead natural Total  Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.006446622; // Sapl Dead disease Species 1 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.009066457; // Sapl Dead disease Species 2 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.015513078; // Sapl Dead disease Total  Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.222222222; // Sapl Dead disease Species 1 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.222222222; // Sapl Dead disease Species 2 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 4.444444444; // Sapl Dead disease Total  Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sapl Dead fire Species 1 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.002473831; // Sapl Dead fire Species 2 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.002473831; // Sapl Dead fire Total  Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Sapl Dead fire Species 1 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.666666667; // Sapl Dead fire Species 2 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.666666667; // Sapl Dead fire Total  Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.000313548; // Sapl Dead insects Species 1 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.005564991; // Sapl Dead insects Species 2 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.005878539; // Sapl Dead insects Total  Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.888888889; // Sapl Dead insects Species 1 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.222222222; // Sapl Dead insects Species 2 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 3.111111111; // Sapl Dead insects Total  Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.001105333; // Sapl Dead storm Species 1 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.010009525; // Sapl Dead storm Species 2 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.011114859; // Sapl Dead storm Total  Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 1.333333333; // Sapl Dead storm Species 1 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.666666667; // Sapl Dead storm Species 2 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 4; // Sapl Dead storm Total  Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.00780355; //  Sapl Dead remove_tree Species 1 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.000715133; // Sapl Dead remove_tree Species 2 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.008518683; // Sapl Dead remove_tree Total  Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 3.555555556; // Sapl Dead remove_tree Species 1 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.888888889; // Sapl Dead remove_tree Species 2 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 4.444444444; // Sapl Dead remove_tree Total  Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.145632852; // Adult Dead harvest Species 1 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.125733682; // Adult Dead harvest Species 2 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.271366535; // Adult Dead harvest Total  Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 1.777777778; // Adult Dead harvest Species 1 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.888888889; // Adult Dead harvest Species 2 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.666666667; // Adult Dead harvest Total  Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.240148412; // Adult Dead natural Species 1 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.195889584; // Adult Dead natural Species 2 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.436037995; // Adult Dead natural Total  Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 1.333333333; // Adult Dead natural Species 1 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 1.777777778; // Adult Dead natural Species 2 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 3.111111111; // Adult Dead natural Total  Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.267922156; // Adult Dead disease Species 1 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.085911782; // Adult Dead disease Species 2 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.353833938; // Adult Dead disease Total  Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 1.777777778; // Adult Dead disease Species 1 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.888888889; // Adult Dead disease Species 2 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.666666667; // Adult Dead disease Total  Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.174504525; // Adult Dead fire Species 1 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.321097988; // Adult Dead fire Species 2 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.495602512; // Adult Dead fire Total  Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.888888889; // Adult Dead fire Species 1 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 1.777777778; // Adult Dead fire Species 2 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.666666667; // Adult Dead fire Total  Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.262426133; // Adult Dead insects Species 1 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.068103133; // Adult Dead insects Species 2 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.330529266; // Adult Dead insects Total  Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 3.111111111; // Adult Dead insects Species 1 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.888888889; // Adult Dead insects Species 2 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 4; // Adult Dead insects Total  Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Adult Dead storm Species 1 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.124713744; // Adult Dead storm Species 2 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.124713744; // Adult Dead storm Total  Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Adult Dead storm Species 1 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 1.333333333; // Adult Dead storm Species 2 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 1.333333333; // Adult Dead storm Total  Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.200929276; // Adult Dead remove_tree Species 1 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.114790012; // Adult Dead remove_tree Species 2 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.315719288; // Adult Dead remove_tree Total  Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 1.777777778; // Adult Dead remove_tree Species 1 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.222222222; // Adult Dead remove_tree Species 2 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 4; // Adult Dead remove_tree Total  Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.228330553; // Snag Dead harvest Species 1 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.042871177; // Snag Dead harvest Species 2 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.271201731; // Snag Dead harvest Total  Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.666666667; // Snag Dead harvest Species 1 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.444444444; // Snag Dead harvest Species 2 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 3.111111111; // Snag Dead harvest Total  Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.28385583; //  Snag Dead natural Species 1 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.149038077; // Snag Dead natural Species 2 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.432893907; // Snag Dead natural Total  Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 1.333333333; // Snag Dead natural Species 1 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 1.777777778; // Snag Dead natural Species 2 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 3.111111111; // Snag Dead natural Total  Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.035276267; // Snag Dead disease Species 1 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.039033699; // Snag Dead disease Species 2 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.074309966; // Snag Dead disease Total  Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.888888889; // Snag Dead disease Species 1 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.444444444; // Snag Dead disease Species 2 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 1.333333333; // Snag Dead disease Total  Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.126502425; // Snag Dead fire Species 1 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.031535701; // Snag Dead fire Species 2 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.158038126; // Snag Dead fire Total  Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 1.333333333; // Snag Dead fire Species 1 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.444444444; // Snag Dead fire Species 2 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 1.777777778; // Snag Dead fire Total  Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.146211467; // Snag Dead insects Species 1 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.241606414; // Snag Dead insects Species 2 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.387817881; // Snag Dead insects Total  Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 1.333333333; // Snag Dead insects Species 1 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.222222222; // Snag Dead insects Species 2 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 3.555555556; // Snag Dead insects Total  Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.191980175; // Snag Dead storm Species 1 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.48571431; //  Snag Dead storm Species 2 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.677694485; // Snag Dead storm Total  Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 1.777777778; // Snag Dead storm Species 1 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 4; // Snag Dead storm Species 2 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 5.777777778; // Snag Dead storm Total  Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.258896403; // Snag Dead remove_tree Species 1 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.235535636; // Snag Dead remove_tree Species 2 Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.494432039; // Snag Dead remove_tree Total  Abs BA
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.666666667; // Snag Dead remove_tree Species 1 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 1.777777778; // Snag Dead remove_tree Species 2 Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 4.444444444; // Snag Dead remove_tree Total  Abs Den
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);


    infile.close();
  } else {
    cout << "Error opening file";
  }

  DeleteThisFile("Short Run 2.out");
  CPPUNIT_ASSERT(!DoesFileExist("Short Run 2.out"));
}

/////////////////////////////////////////////////////////////////////////////
// NormalProcessingRun3()
/////////////////////////////////////////////////////////////////////////////
void clTestOutputShort::NormalProcessingRun3(clSimManager *p_oSimManager) {

  //Feed our file to the sim manager
  p_oSimManager->ReadFile(WriteXMLFile3());
  //Run one timestep
  p_oSimManager->RunSim(1);

  //Verify that the output file has been created
  CPPUNIT_ASSERT(DoesFileExist("Short Run 3.out"));

  ifstream infile;
  char cNum[21], cTemp[5001] ;
  float fExp, fAct;
  infile.open ("Short Run 3.out", ifstream::in);

  if (infile.is_open()) {
    //while (infile.good()) {
    infile.getline(cTemp, 5000);
    infile.getline(cTemp, 5000);
    infile.getline(cTemp, 5000);
    infile.getline(cTemp, 5000);
    infile.getline(cTemp, 5000);
    infile.getline(cTemp, 5000);
    infile.getline(cTemp, 5000);
    infile.getline(cTemp, 5000); //Header

     //Initial conditions, whole plot
    infile.getline(cNum, 20, '\t');
    fExp = 0; //Step
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; //Subplot
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 1.333333333; //Sdl Abs Den Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.222222222; //Sdl Abs Den Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 3.555555556; //Sdl Den Total
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.006581459; //Sapl Abs BA Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.012186611; //Sapl Abs BA Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.018768069; //Sapl BA Total
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.350673186; //Sapl Rel BA Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.649326814; //Sapl Rel BA Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.222222222; //Sapl Abs Den Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 4.444444444; //Sapl Abs Den Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 6.666666667; //Sapl Den Total
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.333333333; //Sapl Rel Den Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.666666667; //Sapl Rel Den Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.210353602; //Adult Abs BA Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.510873154; //Adult Abs BA Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.721226756; //Adult BA Total
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.812263659; //Adult Rel BA Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.187736341; //Adult Rel BA Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.666666667; //Adult Abs Den Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.222222222; //Adult Abs Den Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 4.888888889; //Adult Den Total
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.545454545; //Adult Rel Den Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.454545455; //Adult Rel Den Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 3.671478286; //Snag Abs BA Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 1.079680022; //Snag Abs BA Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 4.751158309; //Snag BA Total
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.772754358; //Snag Rel BA Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.227245642; //Snag Rel BA Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.666666667; //Snag Abs Den Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.222222222; //Snag Abs Den Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 4.888888889; //Snag Den Total
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.545454545; //Snag Rel Den Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20);
    fExp = 0.454545455; //Snag Rel Den Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);


     //Initial conditions, subplot 1
    infile.getline(cNum, 20, '\t');
    fExp = 0; //Step
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 1; //Subplot
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 3.462603878; //Sdl Abs Den Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 5.771006464; //Sdl Abs Den Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 9.233610342; //Sdl Den Total
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.002844989; //Sapl Abs BA Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; //Sapl Abs BA Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.002844989; //Sapl BA Total
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 1; //Sapl Rel BA Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; //Sapl Rel BA Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.308402585; //Sapl Abs Den Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; //Sapl Abs Den Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.308402585; //Sapl Den Total
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 1; //Sapl Rel Den Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; //Sapl Rel Den Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; //Adult Abs BA Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.960613452; //Adult Abs BA Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.960613452; //Adult BA Total
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; //Adult Rel BA Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 1; //Adult Rel BA Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; //Adult Abs Den Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 4.616805171; //Adult Abs Den Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 4.616805171; //Adult Den Total
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; //Adult Rel Den Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 1; //Adult Rel Den Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; //Snag Abs BA Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.803878174; //Snag Abs BA Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.803878174; //Snag BA Total
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; //Snag Rel BA Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 1; //Snag Rel BA Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; //Snag Abs Den Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 5.771006464; //Snag Abs Den Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 5.771006464; //Snag Den Total
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; //Snag Rel Den Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20);
    fExp = 1; //Snag Rel Den Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);

    //Initial conditions, subplot 2
    infile.getline(cNum, 20, '\t');
    fExp = 0; //Step
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2; //Subplot
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 1.993620415; //Sdl Abs Den Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 5.980861244; //Sdl Abs Den Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 7.974481659; //Sdl Den Total
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.004914071; // Sapl Abs BA Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; //Sapl Abs BA Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0.004914071; //Sapl BA Total
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 1; //Sapl Rel BA Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; //Sapl Rel BA Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 3.987240829; //Sapl Abs Den Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; //Sapl Abs Den Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 3.987240829; //Sapl Den Total
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 1; //Sapl Rel Den Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; //Sapl Rel Den Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; // Adult Abs BA Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 1.659241416; //Adult Abs BA Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 1.659241416; //Adult BA Total
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; //Adult Rel BA Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 1; //Adult Rel BA Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; //Adult Abs Den Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 7.974481659; //Adult Abs Den Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 7.974481659; //Adult Den Total
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; //Adult Rel Den Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 1; //Adult Rel Den Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; //Snag Abs BA Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.031846772; //Snag Abs BA Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 2.031846772; //Snag BA Total
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; //Snag Rel BA Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 1; //Snag Rel BA Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; //Snag Abs Den Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 3.987240829; //Snag Abs Den Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 3.987240829; //Snag Den Total
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20, '\t');
    fExp = 0; //Snag Rel Den Species 1
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);
    infile.getline(cNum, 20);
    fExp = 1; //Snag Rel Den Species 2
    fAct = atof(cNum);
    CPPUNIT_ASSERT(fabs(fAct-fExp)<0.0001);

    infile.close();
  } else {
    cout << "Error opening file";
  }

  DeleteThisFile("Short Run 3.out");
  CPPUNIT_ASSERT(!DoesFileExist("Short Run 3.out"));

}

/////////////////////////////////////////////////////////////////////////////
// WriteXMLFile1()
/////////////////////////////////////////////////////////////////////////////
const char* clTestOutputShort::WriteXMLFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06080101\">"
       << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<rt_timestep>0</rt_timestep>"
       << "<randomSeed>0</randomSeed>"
       << "<yearsPerTimestep>1.0</yearsPerTimestep>"
       << "<plot_lenX>150.0</plot_lenX>"
       << "<plot_lenY>150.0</plot_lenY>"
       << "<plot_latitude>0.0</plot_latitude>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
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
       << "</tr_maxSeedlingHeight>";

  WriteTreeMap(oOut);

  oOut << "</trees>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>ShortOutput</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "</behaviorList>"
       << "<allometry>"
       << "<tr_whatAdultHeightDiam>"
       << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_2\">0</tr_wahdVal>"
       << "</tr_whatAdultHeightDiam>"
       << "<tr_whatSaplingHeightDiam>"
       << "<tr_wsahdVal species=\"Species_1\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_2\">0</tr_wsahdVal>"
       << "</tr_whatSaplingHeightDiam>"
       << "<tr_whatSeedlingHeightDiam>"
       << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_2\">0</tr_wsehdVal>"
       << "</tr_whatSeedlingHeightDiam>"
       << "<tr_whatAdultCrownRadDiam>"
       << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_2\">0</tr_wacrdVal>"
       << "</tr_whatAdultCrownRadDiam>"
       << "<tr_whatSaplingCrownRadDiam>"
       << "<tr_wscrdVal species=\"Species_1\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_2\">0</tr_wscrdVal>"
       << "</tr_whatSaplingCrownRadDiam>"
       << "<tr_whatAdultCrownHeightHeight>"
       << "<tr_wachhVal species=\"Species_1\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_2\">0</tr_wachhVal>"
       << "</tr_whatAdultCrownHeightHeight>"
       << "<tr_whatSaplingCrownHeightHeight>"
       << "<tr_wschhVal species=\"Species_1\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_2\">0</tr_wschhVal>"
       << "</tr_whatSaplingCrownHeightHeight>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_2\">39.54</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_2\">0.0614</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.368</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">0.5944</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0.0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0.0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_2\">0.0241</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_2\">0.0269</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "</allometry>"
       << "<ShortOutput>"
       << "<so_filename>Short Run 1.out</so_filename>"
       << "<so_treeTypeInfo type=\"Seedling\">"
       << "<so_saveRDN save=\"false\"/>"
       << "<so_saveADN save=\"true\"/>"
       << "</so_treeTypeInfo>"
       << "<so_treeTypeInfo type=\"Sapling\">"
       << "<so_saveRBA save=\"true\"/>"
       << "<so_saveABA save=\"true\"/>"
       << "<so_saveRDN save=\"true\"/>"
       << "<so_saveADN save=\"true\"/>"
       << "</so_treeTypeInfo>"
       << "<so_treeTypeInfo type=\"Adult\">"
       << "<so_saveRBA save=\"true\"/>"
       << "<so_saveABA save=\"true\"/>"
       << "<so_saveRDN save=\"true\"/>"
       << "<so_saveADN save=\"true\"/>"
       << "</so_treeTypeInfo>"
       << "<so_treeTypeInfo type=\"Snag\">"
       << "<so_saveRBA save=\"true\"/>"
       << "<so_saveABA save=\"true\"/>"
       << "<so_saveRDN save=\"true\"/>"
       << "<so_saveADN save=\"true\"/>"
       << "</so_treeTypeInfo>"
       << "<so_subplot>"
       << "<so_subplotName>Subplot 1</so_subplotName>"
       << "<pointSet>"
       << "<po_point x=\"0\" y=\"0\"/>"
       << "<po_point x=\"0\" y=\"1\"/>"
       << "<po_point x=\"0\" y=\"2\"/>"
       << "<po_point x=\"0\" y=\"3\"/>"
       << "<po_point x=\"0\" y=\"4\"/>"
       << "<po_point x=\"0\" y=\"5\"/>"
       << "<po_point x=\"0\" y=\"6\"/>"
       << "<po_point x=\"0\" y=\"7\"/>"
       << "<po_point x=\"0\" y=\"8\"/>"
       << "<po_point x=\"0\" y=\"9\"/>"
       << "<po_point x=\"0\" y=\"10\"/>"
       << "<po_point x=\"0\" y=\"11\"/>"
       << "<po_point x=\"0\" y=\"12\"/>"
       << "<po_point x=\"1\" y=\"0\"/>"
       << "<po_point x=\"1\" y=\"1\"/>"
       << "<po_point x=\"1\" y=\"2\"/>"
       << "<po_point x=\"1\" y=\"3\"/>"
       << "<po_point x=\"1\" y=\"4\"/>"
       << "<po_point x=\"1\" y=\"5\"/>"
       << "<po_point x=\"1\" y=\"6\"/>"
       << "<po_point x=\"1\" y=\"7\"/>"
       << "<po_point x=\"1\" y=\"8\"/>"
       << "<po_point x=\"1\" y=\"9\"/>"
       << "<po_point x=\"1\" y=\"10\"/>"
       << "<po_point x=\"1\" y=\"11\"/>"
       << "<po_point x=\"1\" y=\"12\"/>"
       << "<po_point x=\"2\" y=\"0\"/>"
       << "<po_point x=\"2\" y=\"1\"/>"
       << "<po_point x=\"2\" y=\"2\"/>"
       << "<po_point x=\"2\" y=\"3\"/>"
       << "<po_point x=\"2\" y=\"4\"/>"
       << "<po_point x=\"2\" y=\"5\"/>"
       << "<po_point x=\"2\" y=\"6\"/>"
       << "<po_point x=\"2\" y=\"7\"/>"
       << "<po_point x=\"2\" y=\"8\"/>"
       << "<po_point x=\"2\" y=\"9\"/>"
       << "<po_point x=\"2\" y=\"10\"/>"
       << "<po_point x=\"2\" y=\"11\"/>"
       << "<po_point x=\"2\" y=\"12\"/>"
       << "<po_point x=\"3\" y=\"0\"/>"
       << "<po_point x=\"3\" y=\"1\"/>"
       << "<po_point x=\"3\" y=\"2\"/>"
       << "<po_point x=\"3\" y=\"3\"/>"
       << "<po_point x=\"3\" y=\"4\"/>"
       << "<po_point x=\"3\" y=\"5\"/>"
       << "<po_point x=\"3\" y=\"6\"/>"
       << "<po_point x=\"3\" y=\"7\"/>"
       << "<po_point x=\"3\" y=\"8\"/>"
       << "<po_point x=\"3\" y=\"9\"/>"
       << "<po_point x=\"3\" y=\"10\"/>"
       << "<po_point x=\"3\" y=\"11\"/>"
       << "<po_point x=\"3\" y=\"12\"/>"
       << "<po_point x=\"4\" y=\"0\"/>"
       << "<po_point x=\"4\" y=\"1\"/>"
       << "<po_point x=\"4\" y=\"2\"/>"
       << "<po_point x=\"4\" y=\"3\"/>"
       << "<po_point x=\"4\" y=\"4\"/>"
       << "<po_point x=\"4\" y=\"5\"/>"
       << "<po_point x=\"4\" y=\"6\"/>"
       << "<po_point x=\"4\" y=\"7\"/>"
       << "<po_point x=\"4\" y=\"8\"/>"
       << "<po_point x=\"4\" y=\"9\"/>"
       << "<po_point x=\"4\" y=\"10\"/>"
       << "<po_point x=\"4\" y=\"11\"/>"
       << "<po_point x=\"4\" y=\"12\"/>"
       << "<po_point x=\"5\" y=\"0\"/>"
       << "<po_point x=\"5\" y=\"1\"/>"
       << "<po_point x=\"5\" y=\"2\"/>"
       << "<po_point x=\"5\" y=\"3\"/>"
       << "<po_point x=\"5\" y=\"4\"/>"
       << "<po_point x=\"5\" y=\"5\"/>"
       << "<po_point x=\"5\" y=\"6\"/>"
       << "<po_point x=\"5\" y=\"7\"/>"
       << "<po_point x=\"5\" y=\"8\"/>"
       << "<po_point x=\"5\" y=\"9\"/>"
       << "<po_point x=\"5\" y=\"10\"/>"
       << "<po_point x=\"5\" y=\"11\"/>"
       << "<po_point x=\"5\" y=\"12\"/>"
       << "<po_point x=\"6\" y=\"0\"/>"
       << "<po_point x=\"6\" y=\"1\"/>"
       << "<po_point x=\"6\" y=\"2\"/>"
       << "<po_point x=\"6\" y=\"3\"/>"
       << "<po_point x=\"6\" y=\"4\"/>"
       << "<po_point x=\"6\" y=\"5\"/>"
       << "<po_point x=\"6\" y=\"6\"/>"
       << "<po_point x=\"6\" y=\"7\"/>"
       << "<po_point x=\"6\" y=\"8\"/>"
       << "<po_point x=\"6\" y=\"9\"/>"
       << "<po_point x=\"6\" y=\"10\"/>"
       << "<po_point x=\"6\" y=\"11\"/>"
       << "<po_point x=\"6\" y=\"12\"/>"
       << "<po_point x=\"7\" y=\"0\"/>"
       << "<po_point x=\"7\" y=\"1\"/>"
       << "<po_point x=\"7\" y=\"2\"/>"
       << "<po_point x=\"7\" y=\"3\"/>"
       << "<po_point x=\"7\" y=\"4\"/>"
       << "<po_point x=\"7\" y=\"5\"/>"
       << "<po_point x=\"7\" y=\"6\"/>"
       << "<po_point x=\"7\" y=\"7\"/>"
       << "<po_point x=\"7\" y=\"8\"/>"
       << "<po_point x=\"7\" y=\"9\"/>"
       << "<po_point x=\"7\" y=\"10\"/>"
       << "<po_point x=\"7\" y=\"11\"/>"
       << "<po_point x=\"7\" y=\"12\"/>"
       << "<po_point x=\"8\" y=\"0\"/>"
       << "<po_point x=\"8\" y=\"1\"/>"
       << "<po_point x=\"8\" y=\"2\"/>"
       << "<po_point x=\"8\" y=\"3\"/>"
       << "<po_point x=\"8\" y=\"4\"/>"
       << "<po_point x=\"8\" y=\"5\"/>"
       << "<po_point x=\"8\" y=\"6\"/>"
       << "<po_point x=\"8\" y=\"7\"/>"
       << "<po_point x=\"8\" y=\"8\"/>"
       << "<po_point x=\"8\" y=\"9\"/>"
       << "<po_point x=\"8\" y=\"10\"/>"
       << "<po_point x=\"8\" y=\"11\"/>"
       << "<po_point x=\"8\" y=\"12\"/>"
       << "<po_point x=\"9\" y=\"0\"/>"
       << "<po_point x=\"9\" y=\"1\"/>"
       << "<po_point x=\"9\" y=\"2\"/>"
       << "<po_point x=\"9\" y=\"3\"/>"
       << "<po_point x=\"9\" y=\"4\"/>"
       << "<po_point x=\"9\" y=\"5\"/>"
       << "<po_point x=\"9\" y=\"6\"/>"
       << "<po_point x=\"9\" y=\"7\"/>"
       << "<po_point x=\"9\" y=\"8\"/>"
       << "<po_point x=\"9\" y=\"9\"/>"
       << "<po_point x=\"9\" y=\"10\"/>"
       << "<po_point x=\"9\" y=\"11\"/>"
       << "<po_point x=\"9\" y=\"12\"/>"
       << "<po_point x=\"10\" y=\"0\"/>"
       << "<po_point x=\"10\" y=\"1\"/>"
       << "<po_point x=\"10\" y=\"2\"/>"
       << "<po_point x=\"10\" y=\"3\"/>"
       << "<po_point x=\"10\" y=\"4\"/>"
       << "<po_point x=\"10\" y=\"5\"/>"
       << "<po_point x=\"10\" y=\"6\"/>"
       << "<po_point x=\"10\" y=\"7\"/>"
       << "<po_point x=\"10\" y=\"8\"/>"
       << "<po_point x=\"10\" y=\"9\"/>"
       << "<po_point x=\"10\" y=\"10\"/>"
       << "<po_point x=\"10\" y=\"11\"/>"
       << "<po_point x=\"10\" y=\"12\"/>"
       << "<po_point x=\"11\" y=\"0\"/>"
       << "<po_point x=\"11\" y=\"1\"/>"
       << "<po_point x=\"11\" y=\"2\"/>"
       << "<po_point x=\"11\" y=\"3\"/>"
       << "<po_point x=\"11\" y=\"4\"/>"
       << "<po_point x=\"11\" y=\"5\"/>"
       << "<po_point x=\"11\" y=\"6\"/>"
       << "<po_point x=\"11\" y=\"7\"/>"
       << "<po_point x=\"11\" y=\"8\"/>"
       << "<po_point x=\"11\" y=\"9\"/>"
       << "<po_point x=\"11\" y=\"10\"/>"
       << "<po_point x=\"11\" y=\"11\"/>"
       << "<po_point x=\"11\" y=\"12\"/>"
       << "<po_point x=\"12\" y=\"0\"/>"
       << "<po_point x=\"12\" y=\"1\"/>"
       << "<po_point x=\"12\" y=\"2\"/>"
       << "<po_point x=\"12\" y=\"3\"/>"
       << "<po_point x=\"12\" y=\"4\"/>"
       << "<po_point x=\"12\" y=\"5\"/>"
       << "<po_point x=\"12\" y=\"6\"/>"
       << "<po_point x=\"12\" y=\"7\"/>"
       << "<po_point x=\"12\" y=\"8\"/>"
       << "<po_point x=\"12\" y=\"9\"/>"
       << "<po_point x=\"12\" y=\"10\"/>"
       << "<po_point x=\"12\" y=\"11\"/>"
       << "<po_point x=\"12\" y=\"12\"/>"
       << "</pointSet>"
       << "</so_subplot>"
       << "<so_subplot>"
       << "<so_subplotName>Subplot 2</so_subplotName>"
       << "<pointSet>"
       << "<po_point x=\"0\" y=\"6\"/>"
       << "<po_point x=\"0\" y=\"7\"/>"
       << "<po_point x=\"0\" y=\"8\"/>"
       << "<po_point x=\"0\" y=\"9\"/>"
       << "<po_point x=\"0\" y=\"12\"/>"
       << "<po_point x=\"0\" y=\"13\"/>"
       << "<po_point x=\"0\" y=\"14\"/>"
       << "<po_point x=\"0\" y=\"15\"/>"
       << "<po_point x=\"0\" y=\"16\"/>"
       << "<po_point x=\"0\" y=\"17\"/>"
       << "<po_point x=\"0\" y=\"18\"/>"
       << "<po_point x=\"1\" y=\"6\"/>"
       << "<po_point x=\"1\" y=\"7\"/>"
       << "<po_point x=\"1\" y=\"8\"/>"
       << "<po_point x=\"1\" y=\"9\"/>"
       << "<po_point x=\"1\" y=\"12\"/>"
       << "<po_point x=\"1\" y=\"13\"/>"
       << "<po_point x=\"1\" y=\"14\"/>"
       << "<po_point x=\"1\" y=\"15\"/>"
       << "<po_point x=\"1\" y=\"16\"/>"
       << "<po_point x=\"1\" y=\"17\"/>"
       << "<po_point x=\"1\" y=\"18\"/>"
       << "<po_point x=\"2\" y=\"6\"/>"
       << "<po_point x=\"2\" y=\"7\"/>"
       << "<po_point x=\"2\" y=\"8\"/>"
       << "<po_point x=\"2\" y=\"9\"/>"
       << "<po_point x=\"2\" y=\"12\"/>"
       << "<po_point x=\"2\" y=\"13\"/>"
       << "<po_point x=\"2\" y=\"14\"/>"
       << "<po_point x=\"2\" y=\"15\"/>"
       << "<po_point x=\"2\" y=\"16\"/>"
       << "<po_point x=\"2\" y=\"17\"/>"
       << "<po_point x=\"2\" y=\"18\"/>"
       << "<po_point x=\"3\" y=\"6\"/>"
       << "<po_point x=\"3\" y=\"7\"/>"
       << "<po_point x=\"3\" y=\"8\"/>"
       << "<po_point x=\"3\" y=\"9\"/>"
       << "<po_point x=\"3\" y=\"12\"/>"
       << "<po_point x=\"3\" y=\"13\"/>"
       << "<po_point x=\"3\" y=\"14\"/>"
       << "<po_point x=\"3\" y=\"15\"/>"
       << "<po_point x=\"3\" y=\"16\"/>"
       << "<po_point x=\"3\" y=\"17\"/>"
       << "<po_point x=\"3\" y=\"18\"/>"
       << "<po_point x=\"4\" y=\"6\"/>"
       << "<po_point x=\"4\" y=\"7\"/>"
       << "<po_point x=\"4\" y=\"8\"/>"
       << "<po_point x=\"4\" y=\"9\"/>"
       << "<po_point x=\"4\" y=\"12\"/>"
       << "<po_point x=\"4\" y=\"13\"/>"
       << "<po_point x=\"4\" y=\"14\"/>"
       << "<po_point x=\"4\" y=\"15\"/>"
       << "<po_point x=\"4\" y=\"16\"/>"
       << "<po_point x=\"4\" y=\"17\"/>"
       << "<po_point x=\"4\" y=\"18\"/>"
       << "<po_point x=\"5\" y=\"6\"/>"
       << "<po_point x=\"5\" y=\"7\"/>"
       << "<po_point x=\"5\" y=\"8\"/>"
       << "<po_point x=\"5\" y=\"9\"/>"
       << "<po_point x=\"5\" y=\"12\"/>"
       << "<po_point x=\"5\" y=\"13\"/>"
       << "<po_point x=\"5\" y=\"14\"/>"
       << "<po_point x=\"5\" y=\"15\"/>"
       << "<po_point x=\"5\" y=\"16\"/>"
       << "<po_point x=\"5\" y=\"17\"/>"
       << "<po_point x=\"5\" y=\"18\"/>"
       << "<po_point x=\"6\" y=\"6\"/>"
       << "<po_point x=\"6\" y=\"7\"/>"
       << "<po_point x=\"6\" y=\"8\"/>"
       << "<po_point x=\"6\" y=\"9\"/>"
       << "<po_point x=\"6\" y=\"12\"/>"
       << "<po_point x=\"6\" y=\"13\"/>"
       << "<po_point x=\"6\" y=\"14\"/>"
       << "<po_point x=\"6\" y=\"15\"/>"
       << "<po_point x=\"6\" y=\"16\"/>"
       << "<po_point x=\"6\" y=\"17\"/>"
       << "<po_point x=\"6\" y=\"18\"/>"
       << "<po_point x=\"7\" y=\"6\"/>"
       << "<po_point x=\"7\" y=\"7\"/>"
       << "<po_point x=\"7\" y=\"8\"/>"
       << "<po_point x=\"7\" y=\"9\"/>"
       << "<po_point x=\"7\" y=\"12\"/>"
       << "<po_point x=\"7\" y=\"13\"/>"
       << "<po_point x=\"7\" y=\"14\"/>"
       << "<po_point x=\"7\" y=\"15\"/>"
       << "<po_point x=\"7\" y=\"16\"/>"
       << "<po_point x=\"7\" y=\"17\"/>"
       << "<po_point x=\"7\" y=\"18\"/>"
       << "<po_point x=\"8\" y=\"6\"/>"
       << "<po_point x=\"8\" y=\"7\"/>"
       << "<po_point x=\"8\" y=\"8\"/>"
       << "<po_point x=\"8\" y=\"9\"/>"
       << "<po_point x=\"8\" y=\"12\"/>"
       << "<po_point x=\"8\" y=\"13\"/>"
       << "<po_point x=\"8\" y=\"14\"/>"
       << "<po_point x=\"8\" y=\"15\"/>"
       << "<po_point x=\"8\" y=\"16\"/>"
       << "<po_point x=\"8\" y=\"17\"/>"
       << "<po_point x=\"8\" y=\"18\"/>"
       << "<po_point x=\"9\" y=\"6\"/>"
       << "<po_point x=\"9\" y=\"7\"/>"
       << "<po_point x=\"9\" y=\"8\"/>"
       << "<po_point x=\"9\" y=\"9\"/>"
       << "<po_point x=\"9\" y=\"12\"/>"
       << "<po_point x=\"9\" y=\"13\"/>"
       << "<po_point x=\"9\" y=\"14\"/>"
       << "<po_point x=\"9\" y=\"15\"/>"
       << "<po_point x=\"9\" y=\"16\"/>"
       << "<po_point x=\"9\" y=\"17\"/>"
       << "<po_point x=\"9\" y=\"18\"/>"
       << "<po_point x=\"10\" y=\"6\"/>"
       << "<po_point x=\"10\" y=\"7\"/>"
       << "<po_point x=\"10\" y=\"8\"/>"
       << "<po_point x=\"10\" y=\"9\"/>"
       << "<po_point x=\"10\" y=\"12\"/>"
       << "<po_point x=\"10\" y=\"13\"/>"
       << "<po_point x=\"10\" y=\"14\"/>"
       << "<po_point x=\"10\" y=\"15\"/>"
       << "<po_point x=\"10\" y=\"16\"/>"
       << "<po_point x=\"10\" y=\"17\"/>"
       << "<po_point x=\"10\" y=\"18\"/>"
       << "<po_point x=\"11\" y=\"6\"/>"
       << "<po_point x=\"11\" y=\"7\"/>"
       << "<po_point x=\"11\" y=\"8\"/>"
       << "<po_point x=\"11\" y=\"9\"/>"
       << "<po_point x=\"11\" y=\"12\"/>"
       << "<po_point x=\"11\" y=\"13\"/>"
       << "<po_point x=\"11\" y=\"14\"/>"
       << "<po_point x=\"11\" y=\"15\"/>"
       << "<po_point x=\"11\" y=\"16\"/>"
       << "<po_point x=\"11\" y=\"17\"/>"
       << "<po_point x=\"11\" y=\"18\"/>"
       << "<po_point x=\"12\" y=\"6\"/>"
       << "<po_point x=\"12\" y=\"7\"/>"
       << "<po_point x=\"12\" y=\"8\"/>"
       << "<po_point x=\"12\" y=\"9\"/>"
       << "<po_point x=\"12\" y=\"12\"/>"
       << "<po_point x=\"12\" y=\"13\"/>"
       << "<po_point x=\"12\" y=\"14\"/>"
       << "<po_point x=\"12\" y=\"15\"/>"
       << "<po_point x=\"12\" y=\"16\"/>"
       << "<po_point x=\"12\" y=\"17\"/>"
       << "<po_point x=\"12\" y=\"18\"/>"
       << "<po_point x=\"13\" y=\"6\"/>"
       << "<po_point x=\"13\" y=\"7\"/>"
       << "<po_point x=\"13\" y=\"8\"/>"
       << "<po_point x=\"13\" y=\"9\"/>"
       << "<po_point x=\"13\" y=\"12\"/>"
       << "<po_point x=\"13\" y=\"13\"/>"
       << "<po_point x=\"13\" y=\"14\"/>"
       << "<po_point x=\"13\" y=\"15\"/>"
       << "<po_point x=\"13\" y=\"16\"/>"
       << "<po_point x=\"13\" y=\"17\"/>"
       << "<po_point x=\"13\" y=\"18\"/>"
       << "<po_point x=\"14\" y=\"6\"/>"
       << "<po_point x=\"14\" y=\"7\"/>"
       << "<po_point x=\"14\" y=\"8\"/>"
       << "<po_point x=\"14\" y=\"9\"/>"
       << "<po_point x=\"14\" y=\"12\"/>"
       << "<po_point x=\"14\" y=\"13\"/>"
       << "<po_point x=\"14\" y=\"14\"/>"
       << "<po_point x=\"14\" y=\"15\"/>"
       << "<po_point x=\"14\" y=\"16\"/>"
       << "<po_point x=\"14\" y=\"17\"/>"
       << "<po_point x=\"14\" y=\"18\"/>"
       << "<po_point x=\"15\" y=\"6\"/>"
       << "<po_point x=\"15\" y=\"7\"/>"
       << "<po_point x=\"15\" y=\"8\"/>"
       << "<po_point x=\"15\" y=\"9\"/>"
       << "<po_point x=\"15\" y=\"12\"/>"
       << "<po_point x=\"15\" y=\"13\"/>"
       << "<po_point x=\"15\" y=\"14\"/>"
       << "<po_point x=\"15\" y=\"15\"/>"
       << "<po_point x=\"15\" y=\"16\"/>"
       << "<po_point x=\"15\" y=\"17\"/>"
       << "<po_point x=\"15\" y=\"18\"/>"
       << "<po_point x=\"16\" y=\"6\"/>"
       << "<po_point x=\"16\" y=\"7\"/>"
       << "<po_point x=\"16\" y=\"8\"/>"
       << "<po_point x=\"16\" y=\"9\"/>"
       << "<po_point x=\"16\" y=\"12\"/>"
       << "<po_point x=\"16\" y=\"13\"/>"
       << "<po_point x=\"16\" y=\"14\"/>"
       << "<po_point x=\"16\" y=\"15\"/>"
       << "<po_point x=\"16\" y=\"16\"/>"
       << "<po_point x=\"16\" y=\"17\"/>"
       << "<po_point x=\"16\" y=\"18\"/>"
       << "<po_point x=\"17\" y=\"6\"/>"
       << "<po_point x=\"17\" y=\"7\"/>"
       << "<po_point x=\"17\" y=\"8\"/>"
       << "<po_point x=\"17\" y=\"9\"/>"
       << "<po_point x=\"17\" y=\"12\"/>"
       << "<po_point x=\"17\" y=\"13\"/>"
       << "<po_point x=\"17\" y=\"14\"/>"
       << "<po_point x=\"17\" y=\"15\"/>"
       << "<po_point x=\"17\" y=\"16\"/>"
       << "<po_point x=\"17\" y=\"17\"/>"
       << "<po_point x=\"17\" y=\"18\"/>"
       << "<po_point x=\"18\" y=\"6\"/>"
       << "<po_point x=\"18\" y=\"7\"/>"
       << "<po_point x=\"18\" y=\"8\"/>"
       << "<po_point x=\"18\" y=\"9\"/>"
       << "<po_point x=\"18\" y=\"12\"/>"
       << "<po_point x=\"18\" y=\"13\"/>"
       << "<po_point x=\"18\" y=\"14\"/>"
       << "<po_point x=\"18\" y=\"15\"/>"
       << "<po_point x=\"18\" y=\"16\"/>"
       << "<po_point x=\"18\" y=\"17\"/>"
       << "<po_point x=\"18\" y=\"18\"/>"
       << "</pointSet>"
       << "</so_subplot>"
       << "</ShortOutput>"
       << "</paramFile>";
  oOut.close();

  return cFileString;
}


/////////////////////////////////////////////////////////////////////////////
// WriteXMLFile2()
/////////////////////////////////////////////////////////////////////////////
const char* clTestOutputShort::WriteXMLFile2()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06080101\">"
       << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<rt_timestep>0</rt_timestep>"
       << "<randomSeed>0</randomSeed>"
       << "<yearsPerTimestep>1.0</yearsPerTimestep>"
       << "<plot_lenX>150.0</plot_lenX>"
       << "<plot_lenY>150.0</plot_lenY>"
       << "<plot_latitude>0.0</plot_latitude>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
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
       << "</tr_maxSeedlingHeight>";

  WriteTreeMap(oOut);

  oOut << "</trees>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Snag\"/>"
       << "<applyTo species=\"Species_2\" type=\"Snag\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RemoveDead</behaviorName>"
       << "<version>3</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Snag\"/>"
       << "<applyTo species=\"Species_2\" type=\"Snag\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>NonSpatialDisperse</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>4</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Establishment</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>5</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>ShortOutput</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>6</listPosition>"
       << "</behavior>"
       << "</behaviorList>"
       << "<allometry>"
       << "<tr_whatAdultHeightDiam>"
       << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_2\">0</tr_wahdVal>"
       << "</tr_whatAdultHeightDiam>"
       << "<tr_whatSaplingHeightDiam>"
       << "<tr_wsahdVal species=\"Species_1\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_2\">0</tr_wsahdVal>"
       << "</tr_whatSaplingHeightDiam>"
       << "<tr_whatSeedlingHeightDiam>"
       << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_2\">0</tr_wsehdVal>"
       << "</tr_whatSeedlingHeightDiam>"
       << "<tr_whatAdultCrownRadDiam>"
       << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_2\">0</tr_wacrdVal>"
       << "</tr_whatAdultCrownRadDiam>"
       << "<tr_whatSaplingCrownRadDiam>"
       << "<tr_wscrdVal species=\"Species_1\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_2\">0</tr_wscrdVal>"
       << "</tr_whatSaplingCrownRadDiam>"
       << "<tr_whatAdultCrownHeightHeight>"
       << "<tr_wachhVal species=\"Species_1\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_2\">0</tr_wachhVal>"
       << "</tr_whatAdultCrownHeightHeight>"
       << "<tr_whatSaplingCrownHeightHeight>"
       << "<tr_wschhVal species=\"Species_1\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_2\">0</tr_wschhVal>"
       << "</tr_whatSaplingCrownHeightHeight>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_2\">39.54</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_2\">0.0614</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.368</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">0.5944</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0.0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0.0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_2\">0.0241</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_2\">0.0269</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "</allometry>"
       << "<StochasticMortality1>"
       << "<mo_stochasticMortRate>"
       << "<mo_smrVal species=\"Species_1\">0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_2\">0</mo_smrVal>"
       << "</mo_stochasticMortRate>"
       << "</StochasticMortality1>"
       << "<StochasticMortality2>"
       << "<mo_stochasticMortRate>"
       << "<mo_smrVal species=\"Species_1\">0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_2\">0</mo_smrVal>"
       << "</mo_stochasticMortRate>"
       << "</StochasticMortality2>"
       << "<NonSpatialDisperse4>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_1\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_2\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_nonSpatialSlopeOfLambda>"
       << "<di_nssolVal species=\"Species_1\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_2\">0</di_nssolVal>"
       << "</di_nonSpatialSlopeOfLambda>"
       << "<di_nonSpatialInterceptOfLambda>"
       << "<di_nsiolVal species=\"Species_1\">1</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_2\">2</di_nsiolVal>"
       << "</di_nonSpatialInterceptOfLambda>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</NonSpatialDisperse4>"
       << "<ShortOutput>"
       << "<so_filename>Short Run 2.out</so_filename>"
       << "<so_treeTypeInfo type=\"Seedling\">"
       << "<so_saveRDN save=\"false\"/>"
       << "<so_saveADN save=\"true\"/>"
       << "</so_treeTypeInfo>"
       << "<so_treeTypeInfo type=\"Sapling\">"
       << "<so_saveRBA save=\"true\"/>"
       << "<so_saveABA save=\"true\"/>"
       << "<so_saveRDN save=\"true\"/>"
       << "<so_saveADN save=\"true\"/>"
       << "</so_treeTypeInfo>"
       << "<so_treeTypeInfo type=\"Adult\">"
       << "<so_saveRBA save=\"true\"/>"
       << "<so_saveABA save=\"true\"/>"
       << "<so_saveRDN save=\"true\"/>"
       << "<so_saveADN save=\"true\"/>"
       << "</so_treeTypeInfo>"
       << "<so_treeTypeInfo type=\"Snag\">"
       << "<so_saveRBA save=\"true\"/>"
       << "<so_saveABA save=\"true\"/>"
       << "<so_saveRDN save=\"true\"/>"
       << "<so_saveADN save=\"true\"/>"
       << "</so_treeTypeInfo>"
       << "<so_deadTreeTypeInfo type=\"Seedling\" reason=\"harvest\">"
       << "<so_saveADN save=\"true\"/>"
       << "</so_deadTreeTypeInfo>"
       << "<so_deadTreeTypeInfo type=\"Seedling\" reason=\"natural\">"
       << "<so_saveADN save=\"true\"/>"
       << "</so_deadTreeTypeInfo>"
       << "<so_deadTreeTypeInfo type=\"Seedling\" reason=\"disease\">"
       << "<so_saveADN save=\"true\"/>"
       << "</so_deadTreeTypeInfo>"
       << "<so_deadTreeTypeInfo type=\"Seedling\" reason=\"fire\">"
       << "<so_saveADN save=\"true\"/>"
       << "</so_deadTreeTypeInfo>"
       << "<so_deadTreeTypeInfo type=\"Seedling\" reason=\"insects\">"
       << "<so_saveADN save=\"true\"/>"
       << "</so_deadTreeTypeInfo>"
       << "<so_deadTreeTypeInfo type=\"Seedling\" reason=\"storm\">"
       << "<so_saveADN save=\"true\"/>"
       << "</so_deadTreeTypeInfo>"
       << "<so_deadTreeTypeInfo type=\"Seedling\" reason=\"remove_tree\">"
       << "<so_saveADN save=\"true\"/>"
       << "</so_deadTreeTypeInfo>"
       << "<so_deadTreeTypeInfo type=\"Sapling\" reason=\"harvest\">"
       << "<so_saveADN save=\"true\"/>"
       << "<so_saveABA save=\"true\"/>"
       << "</so_deadTreeTypeInfo>"
       << "<so_deadTreeTypeInfo type=\"Sapling\" reason=\"natural\">"
       << "<so_saveADN save=\"true\"/>"
       << "<so_saveABA save=\"true\"/>"
       << "</so_deadTreeTypeInfo>"
       << "<so_deadTreeTypeInfo type=\"Sapling\" reason=\"disease\">"
       << "<so_saveADN save=\"true\"/>"
       << "<so_saveABA save=\"true\"/>"
       << "</so_deadTreeTypeInfo>"
       << "<so_deadTreeTypeInfo type=\"Sapling\" reason=\"fire\">"
       << "<so_saveADN save=\"true\"/>"
       << "<so_saveABA save=\"true\"/>"
       << "</so_deadTreeTypeInfo>"
       << "<so_deadTreeTypeInfo type=\"Sapling\" reason=\"insects\">"
       << "<so_saveADN save=\"true\"/>"
       << "<so_saveABA save=\"true\"/>"
       << "</so_deadTreeTypeInfo>"
       << "<so_deadTreeTypeInfo type=\"Sapling\" reason=\"storm\">"
       << "<so_saveADN save=\"true\"/>"
       << "<so_saveABA save=\"true\"/>"
       << "</so_deadTreeTypeInfo>"
       << "<so_deadTreeTypeInfo type=\"Sapling\" reason=\"remove_tree\">"
       << "<so_saveADN save=\"true\"/>"
       << "<so_saveABA save=\"true\"/>"
       << "</so_deadTreeTypeInfo>"
       << "<so_deadTreeTypeInfo type=\"Adult\" reason=\"harvest\">"
       << "<so_saveADN save=\"true\"/>"
       << "<so_saveABA save=\"true\"/>"
       << "</so_deadTreeTypeInfo>"
       << "<so_deadTreeTypeInfo type=\"Adult\" reason=\"natural\">"
       << "<so_saveADN save=\"true\"/>"
       << "<so_saveABA save=\"true\"/>"
       << "</so_deadTreeTypeInfo>"
       << "<so_deadTreeTypeInfo type=\"Adult\" reason=\"disease\">"
       << "<so_saveADN save=\"true\"/>"
       << "<so_saveABA save=\"true\"/>"
       << "</so_deadTreeTypeInfo>"
       << "<so_deadTreeTypeInfo type=\"Adult\" reason=\"fire\">"
       << "<so_saveADN save=\"true\"/>"
       << "<so_saveABA save=\"true\"/>"
       << "</so_deadTreeTypeInfo>"
       << "<so_deadTreeTypeInfo type=\"Adult\" reason=\"insects\">"
       << "<so_saveADN save=\"true\"/>"
       << "<so_saveABA save=\"true\"/>"
       << "</so_deadTreeTypeInfo>"
       << "<so_deadTreeTypeInfo type=\"Adult\" reason=\"storm\">"
       << "<so_saveADN save=\"true\"/>"
       << "<so_saveABA save=\"true\"/>"
       << "</so_deadTreeTypeInfo>"
       << "<so_deadTreeTypeInfo type=\"Adult\" reason=\"remove_tree\">"
       << "<so_saveADN save=\"true\"/>"
       << "<so_saveABA save=\"true\"/>"
       << "</so_deadTreeTypeInfo>"
       << "<so_deadTreeTypeInfo type=\"Snag\" reason=\"harvest\">"
       << "<so_saveADN save=\"true\"/>"
       << "<so_saveABA save=\"true\"/>"
       << "</so_deadTreeTypeInfo>"
       << "<so_deadTreeTypeInfo type=\"Snag\" reason=\"natural\">"
       << "<so_saveADN save=\"true\"/>"
       << "<so_saveABA save=\"true\"/>"
       << "</so_deadTreeTypeInfo>"
       << "<so_deadTreeTypeInfo type=\"Snag\" reason=\"disease\">"
       << "<so_saveADN save=\"true\"/>"
       << "<so_saveABA save=\"true\"/>"
       << "</so_deadTreeTypeInfo>"
       << "<so_deadTreeTypeInfo type=\"Snag\" reason=\"fire\">"
       << "<so_saveADN save=\"true\"/>"
       << "<so_saveABA save=\"true\"/>"
       << "</so_deadTreeTypeInfo>"
       << "<so_deadTreeTypeInfo type=\"Snag\" reason=\"insects\">"
       << "<so_saveADN save=\"true\"/>"
       << "<so_saveABA save=\"true\"/>"
       << "</so_deadTreeTypeInfo>"
       << "<so_deadTreeTypeInfo type=\"Snag\" reason=\"storm\">"
       << "<so_saveADN save=\"true\"/>"
       << "<so_saveABA save=\"true\"/>"
       << "</so_deadTreeTypeInfo>"
       << "<so_deadTreeTypeInfo type=\"Snag\" reason=\"remove_tree\">"
       << "<so_saveADN save=\"true\"/>"
       << "<so_saveABA save=\"true\"/>"
       << "</so_deadTreeTypeInfo>"
       << "</ShortOutput>"
       << "</paramFile>";
  oOut.close();

  return cFileString;
}


/////////////////////////////////////////////////////////////////////////////
// WriteXMLFile3()
/////////////////////////////////////////////////////////////////////////////
const char* clTestOutputShort::WriteXMLFile3() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06080101\">"
       << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<rt_timestep>0</rt_timestep>"
       << "<randomSeed>0</randomSeed>"
       << "<yearsPerTimestep>1.0</yearsPerTimestep>"
       << "<plot_lenX>150.0</plot_lenX>"
       << "<plot_lenY>150.0</plot_lenY>"
       << "<plot_latitude>0.0</plot_latitude>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
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
       << "</tr_maxSeedlingHeight>";

  WriteTreeMap(oOut);

  oOut << "</trees>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>ShortOutput</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "</behaviorList>"
       << "<allometry>"
       << "<tr_whatAdultHeightDiam>"
       << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_2\">0</tr_wahdVal>"
       << "</tr_whatAdultHeightDiam>"
       << "<tr_whatSaplingHeightDiam>"
       << "<tr_wsahdVal species=\"Species_1\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_2\">0</tr_wsahdVal>"
       << "</tr_whatSaplingHeightDiam>"
       << "<tr_whatSeedlingHeightDiam>"
       << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_2\">0</tr_wsehdVal>"
       << "</tr_whatSeedlingHeightDiam>"
       << "<tr_whatAdultCrownRadDiam>"
       << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_2\">0</tr_wacrdVal>"
       << "</tr_whatAdultCrownRadDiam>"
       << "<tr_whatSaplingCrownRadDiam>"
       << "<tr_wscrdVal species=\"Species_1\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_2\">0</tr_wscrdVal>"
       << "</tr_whatSaplingCrownRadDiam>"
       << "<tr_whatAdultCrownHeightHeight>"
       << "<tr_wachhVal species=\"Species_1\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_2\">0</tr_wachhVal>"
       << "</tr_whatAdultCrownHeightHeight>"
       << "<tr_whatSaplingCrownHeightHeight>"
       << "<tr_wschhVal species=\"Species_1\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_2\">0</tr_wschhVal>"
       << "</tr_whatSaplingCrownHeightHeight>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_2\">39.54</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_2\">0.0614</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.368</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">0.5944</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0.0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0.0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_2\">0.0241</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_2\">0.0269</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "</allometry>"
       << "<ShortOutput>"
       << "<so_filename>Short Run 3.out</so_filename>"
       << "<so_subplotXLength>6</so_subplotXLength>"
       << "<so_subplotYLength>4</so_subplotYLength>"
       << "<so_treeTypeInfo type=\"Seedling\">"
       << "<so_saveRDN save=\"false\"/>"
       << "<so_saveADN save=\"true\"/>"
       << "</so_treeTypeInfo>"
       << "<so_treeTypeInfo type=\"Sapling\">"
       << "<so_saveRBA save=\"true\"/>"
       << "<so_saveABA save=\"true\"/>"
       << "<so_saveRDN save=\"true\"/>"
       << "<so_saveADN save=\"true\"/>"
       << "</so_treeTypeInfo>"
       << "<so_treeTypeInfo type=\"Adult\">"
       << "<so_saveRBA save=\"true\"/>"
       << "<so_saveABA save=\"true\"/>"
       << "<so_saveRDN save=\"true\"/>"
       << "<so_saveADN save=\"true\"/>"
       << "</so_treeTypeInfo>"
       << "<so_treeTypeInfo type=\"Snag\">"
       << "<so_saveRBA save=\"true\"/>"
       << "<so_saveABA save=\"true\"/>"
       << "<so_saveRDN save=\"true\"/>"
       << "<so_saveADN save=\"true\"/>"
       << "</so_treeTypeInfo>"
       << "<so_subplot>"
       << "<so_subplotName>Subplot 1</so_subplotName>"
       << "<pointSet>";
  for (int i = 0; i < 19; i++) {
    for (int j = 0; j < 19; j++) {
      oOut << "<po_point x=\"" << i << "\" y=\"" << j << "\"/>";
    }
  }
  oOut << "</pointSet>"
       << "</so_subplot>"
       << "<so_subplot>"
       << "<so_subplotName>Subplot 2</so_subplotName>"
       << "<pointSet>"
       << "<po_point x=\"0\" y=\"6\"/>"
       << "<po_point x=\"0\" y=\"7\"/>"
       << "<po_point x=\"0\" y=\"8\"/>"
       << "<po_point x=\"0\" y=\"9\"/>"
       << "<po_point x=\"0\" y=\"12\"/>"
       << "<po_point x=\"0\" y=\"13\"/>"
       << "<po_point x=\"0\" y=\"14\"/>"
       << "<po_point x=\"0\" y=\"15\"/>"
       << "<po_point x=\"0\" y=\"16\"/>"
       << "<po_point x=\"0\" y=\"17\"/>"
       << "<po_point x=\"0\" y=\"18\"/>"
       << "<po_point x=\"1\" y=\"6\"/>"
       << "<po_point x=\"1\" y=\"7\"/>"
       << "<po_point x=\"1\" y=\"8\"/>"
       << "<po_point x=\"1\" y=\"9\"/>"
       << "<po_point x=\"1\" y=\"12\"/>"
       << "<po_point x=\"1\" y=\"13\"/>"
       << "<po_point x=\"1\" y=\"14\"/>"
       << "<po_point x=\"1\" y=\"15\"/>"
       << "<po_point x=\"1\" y=\"16\"/>"
       << "<po_point x=\"1\" y=\"17\"/>"
       << "<po_point x=\"1\" y=\"18\"/>"
       << "<po_point x=\"2\" y=\"6\"/>"
       << "<po_point x=\"2\" y=\"7\"/>"
       << "<po_point x=\"2\" y=\"8\"/>"
       << "<po_point x=\"2\" y=\"9\"/>"
       << "<po_point x=\"2\" y=\"12\"/>"
       << "<po_point x=\"2\" y=\"13\"/>"
       << "<po_point x=\"2\" y=\"14\"/>"
       << "<po_point x=\"2\" y=\"15\"/>"
       << "<po_point x=\"2\" y=\"16\"/>"
       << "<po_point x=\"2\" y=\"17\"/>"
       << "<po_point x=\"2\" y=\"18\"/>"
       << "<po_point x=\"3\" y=\"6\"/>"
       << "<po_point x=\"3\" y=\"7\"/>"
       << "<po_point x=\"3\" y=\"8\"/>"
       << "<po_point x=\"3\" y=\"9\"/>"
       << "<po_point x=\"3\" y=\"12\"/>"
       << "<po_point x=\"3\" y=\"13\"/>"
       << "<po_point x=\"3\" y=\"14\"/>"
       << "<po_point x=\"3\" y=\"15\"/>"
       << "<po_point x=\"3\" y=\"16\"/>"
       << "<po_point x=\"3\" y=\"17\"/>"
       << "<po_point x=\"3\" y=\"18\"/>"
       << "<po_point x=\"4\" y=\"6\"/>"
       << "<po_point x=\"4\" y=\"7\"/>"
       << "<po_point x=\"4\" y=\"8\"/>"
       << "<po_point x=\"4\" y=\"9\"/>"
       << "<po_point x=\"4\" y=\"12\"/>"
       << "<po_point x=\"4\" y=\"13\"/>"
       << "<po_point x=\"4\" y=\"14\"/>"
       << "<po_point x=\"4\" y=\"15\"/>"
       << "<po_point x=\"4\" y=\"16\"/>"
       << "<po_point x=\"4\" y=\"17\"/>"
       << "<po_point x=\"4\" y=\"18\"/>"
       << "<po_point x=\"5\" y=\"6\"/>"
       << "<po_point x=\"5\" y=\"7\"/>"
       << "<po_point x=\"5\" y=\"8\"/>"
       << "<po_point x=\"5\" y=\"9\"/>"
       << "<po_point x=\"5\" y=\"12\"/>"
       << "<po_point x=\"5\" y=\"13\"/>"
       << "<po_point x=\"5\" y=\"14\"/>"
       << "<po_point x=\"5\" y=\"15\"/>"
       << "<po_point x=\"5\" y=\"16\"/>"
       << "<po_point x=\"5\" y=\"17\"/>"
       << "<po_point x=\"5\" y=\"18\"/>"
       << "<po_point x=\"6\" y=\"6\"/>"
       << "<po_point x=\"6\" y=\"7\"/>"
       << "<po_point x=\"6\" y=\"8\"/>"
       << "<po_point x=\"6\" y=\"9\"/>"
       << "<po_point x=\"6\" y=\"12\"/>"
       << "<po_point x=\"6\" y=\"13\"/>"
       << "<po_point x=\"6\" y=\"14\"/>"
       << "<po_point x=\"6\" y=\"15\"/>"
       << "<po_point x=\"6\" y=\"16\"/>"
       << "<po_point x=\"6\" y=\"17\"/>"
       << "<po_point x=\"6\" y=\"18\"/>"
       << "<po_point x=\"7\" y=\"6\"/>"
       << "<po_point x=\"7\" y=\"7\"/>"
       << "<po_point x=\"7\" y=\"8\"/>"
       << "<po_point x=\"7\" y=\"9\"/>"
       << "<po_point x=\"7\" y=\"12\"/>"
       << "<po_point x=\"7\" y=\"13\"/>"
       << "<po_point x=\"7\" y=\"14\"/>"
       << "<po_point x=\"7\" y=\"15\"/>"
       << "<po_point x=\"7\" y=\"16\"/>"
       << "<po_point x=\"7\" y=\"17\"/>"
       << "<po_point x=\"7\" y=\"18\"/>"
       << "<po_point x=\"8\" y=\"6\"/>"
       << "<po_point x=\"8\" y=\"7\"/>"
       << "<po_point x=\"8\" y=\"8\"/>"
       << "<po_point x=\"8\" y=\"9\"/>"
       << "<po_point x=\"8\" y=\"12\"/>"
       << "<po_point x=\"8\" y=\"13\"/>"
       << "<po_point x=\"8\" y=\"14\"/>"
       << "<po_point x=\"8\" y=\"15\"/>"
       << "<po_point x=\"8\" y=\"16\"/>"
       << "<po_point x=\"8\" y=\"17\"/>"
       << "<po_point x=\"8\" y=\"18\"/>"
       << "<po_point x=\"9\" y=\"6\"/>"
       << "<po_point x=\"9\" y=\"7\"/>"
       << "<po_point x=\"9\" y=\"8\"/>"
       << "<po_point x=\"9\" y=\"9\"/>"
       << "<po_point x=\"9\" y=\"12\"/>"
       << "<po_point x=\"9\" y=\"13\"/>"
       << "<po_point x=\"9\" y=\"14\"/>"
       << "<po_point x=\"9\" y=\"15\"/>"
       << "<po_point x=\"9\" y=\"16\"/>"
       << "<po_point x=\"9\" y=\"17\"/>"
       << "<po_point x=\"9\" y=\"18\"/>"
       << "<po_point x=\"10\" y=\"6\"/>"
       << "<po_point x=\"10\" y=\"7\"/>"
       << "<po_point x=\"10\" y=\"8\"/>"
       << "<po_point x=\"10\" y=\"9\"/>"
       << "<po_point x=\"10\" y=\"12\"/>"
       << "<po_point x=\"10\" y=\"13\"/>"
       << "<po_point x=\"10\" y=\"14\"/>"
       << "<po_point x=\"10\" y=\"15\"/>"
       << "<po_point x=\"10\" y=\"16\"/>"
       << "<po_point x=\"10\" y=\"17\"/>"
       << "<po_point x=\"10\" y=\"18\"/>"
       << "<po_point x=\"11\" y=\"6\"/>"
       << "<po_point x=\"11\" y=\"7\"/>"
       << "<po_point x=\"11\" y=\"8\"/>"
       << "<po_point x=\"11\" y=\"9\"/>"
       << "<po_point x=\"11\" y=\"12\"/>"
       << "<po_point x=\"11\" y=\"13\"/>"
       << "<po_point x=\"11\" y=\"14\"/>"
       << "<po_point x=\"11\" y=\"15\"/>"
       << "<po_point x=\"11\" y=\"16\"/>"
       << "<po_point x=\"11\" y=\"17\"/>"
       << "<po_point x=\"11\" y=\"18\"/>"
       << "<po_point x=\"12\" y=\"6\"/>"
       << "<po_point x=\"12\" y=\"7\"/>"
       << "<po_point x=\"12\" y=\"8\"/>"
       << "<po_point x=\"12\" y=\"9\"/>"
       << "<po_point x=\"12\" y=\"12\"/>"
       << "<po_point x=\"12\" y=\"13\"/>"
       << "<po_point x=\"12\" y=\"14\"/>"
       << "<po_point x=\"12\" y=\"15\"/>"
       << "<po_point x=\"12\" y=\"16\"/>"
       << "<po_point x=\"12\" y=\"17\"/>"
       << "<po_point x=\"12\" y=\"18\"/>"
       << "<po_point x=\"13\" y=\"6\"/>"
       << "<po_point x=\"13\" y=\"7\"/>"
       << "<po_point x=\"13\" y=\"8\"/>"
       << "<po_point x=\"13\" y=\"9\"/>"
       << "<po_point x=\"13\" y=\"12\"/>"
       << "<po_point x=\"13\" y=\"13\"/>"
       << "<po_point x=\"13\" y=\"14\"/>"
       << "<po_point x=\"13\" y=\"15\"/>"
       << "<po_point x=\"13\" y=\"16\"/>"
       << "<po_point x=\"13\" y=\"17\"/>"
       << "<po_point x=\"13\" y=\"18\"/>"
       << "<po_point x=\"14\" y=\"6\"/>"
       << "<po_point x=\"14\" y=\"7\"/>"
       << "<po_point x=\"14\" y=\"8\"/>"
       << "<po_point x=\"14\" y=\"9\"/>"
       << "<po_point x=\"14\" y=\"12\"/>"
       << "<po_point x=\"14\" y=\"13\"/>"
       << "<po_point x=\"14\" y=\"14\"/>"
       << "<po_point x=\"14\" y=\"15\"/>"
       << "<po_point x=\"14\" y=\"16\"/>"
       << "<po_point x=\"14\" y=\"17\"/>"
       << "<po_point x=\"14\" y=\"18\"/>"
       << "<po_point x=\"15\" y=\"6\"/>"
       << "<po_point x=\"15\" y=\"7\"/>"
       << "<po_point x=\"15\" y=\"8\"/>"
       << "<po_point x=\"15\" y=\"9\"/>"
       << "<po_point x=\"15\" y=\"12\"/>"
       << "<po_point x=\"15\" y=\"13\"/>"
       << "<po_point x=\"15\" y=\"14\"/>"
       << "<po_point x=\"15\" y=\"15\"/>"
       << "<po_point x=\"15\" y=\"16\"/>"
       << "<po_point x=\"15\" y=\"17\"/>"
       << "<po_point x=\"15\" y=\"18\"/>"
       << "<po_point x=\"16\" y=\"6\"/>"
       << "<po_point x=\"16\" y=\"7\"/>"
       << "<po_point x=\"16\" y=\"8\"/>"
       << "<po_point x=\"16\" y=\"9\"/>"
       << "<po_point x=\"16\" y=\"12\"/>"
       << "<po_point x=\"16\" y=\"13\"/>"
       << "<po_point x=\"16\" y=\"14\"/>"
       << "<po_point x=\"16\" y=\"15\"/>"
       << "<po_point x=\"16\" y=\"16\"/>"
       << "<po_point x=\"16\" y=\"17\"/>"
       << "<po_point x=\"16\" y=\"18\"/>"
       << "<po_point x=\"17\" y=\"6\"/>"
       << "<po_point x=\"17\" y=\"7\"/>"
       << "<po_point x=\"17\" y=\"8\"/>"
       << "<po_point x=\"17\" y=\"9\"/>"
       << "<po_point x=\"17\" y=\"12\"/>"
       << "<po_point x=\"17\" y=\"13\"/>"
       << "<po_point x=\"17\" y=\"14\"/>"
       << "<po_point x=\"17\" y=\"15\"/>"
       << "<po_point x=\"17\" y=\"16\"/>"
       << "<po_point x=\"17\" y=\"17\"/>"
       << "<po_point x=\"17\" y=\"18\"/>"
       << "<po_point x=\"18\" y=\"6\"/>"
       << "<po_point x=\"18\" y=\"7\"/>"
       << "<po_point x=\"18\" y=\"8\"/>"
       << "<po_point x=\"18\" y=\"9\"/>"
       << "<po_point x=\"18\" y=\"12\"/>"
       << "<po_point x=\"18\" y=\"13\"/>"
       << "<po_point x=\"18\" y=\"14\"/>"
       << "<po_point x=\"18\" y=\"15\"/>"
       << "<po_point x=\"18\" y=\"16\"/>"
       << "<po_point x=\"18\" y=\"17\"/>"
       << "<po_point x=\"18\" y=\"18\"/>"
       << "</pointSet>"
       << "</so_subplot>"
       << "</ShortOutput>"
       << "</paramFile>";
  oOut.close();

  return cFileString;
}


/////////////////////////////////////////////////////////////////////////////
// WriteTreeMap()
/////////////////////////////////////////////////////////////////////////////
void clTestOutputShort::WriteTreeMap(std::fstream &oOut) {

  oOut << "<tr_treemap>"
       << "<tm_treeSettings sp=\"Species_1\" tp=\"1\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"Height\">2</tm_floatCode>"
       << "<tm_floatCode label=\"Diam10\">3</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_1\" tp=\"2\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"Height\">2</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">3</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_1\" tp=\"3\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"Height\">2</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">3</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_1\" tp=\"5\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"Height\">2</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">3</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_2\" tp=\"1\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"Height\">2</tm_floatCode>"
       << "<tm_floatCode label=\"Diam10\">3</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_2\" tp=\"2\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"Height\">2</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">3</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_2\" tp=\"3\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"Height\">2</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">3</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_2\" tp=\"5\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"Height\">2</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">3</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tree sp=\"0\" tp=\"1\">"
       << "<fl c=\"0\">4.93164</fl>"
       << "<fl c=\"1\">20.4529</fl>"
       << "<fl c=\"3\">0.1</fl>"
       << "</tree>"
       << "<tree sp=\"0\" tp=\"1\">"
       << "<fl c=\"0\">9.11865</fl>"
       << "<fl c=\"1\">33.8013</fl>"
       << "<fl c=\"3\">0.1</fl>"
       << "</tree>"
       << "<tree sp=\"0\" tp=\"1\">"
       << "<fl c=\"0\">9.31396</fl>"
       << "<fl c=\"1\">41.3818</fl>"
       << "<fl c=\"3\">0.1</fl>"
       << "</tree>"
       << "<tree sp=\"1\" tp=\"1\">"
       << "<fl c=\"0\">3.92456</fl>"
       << "<fl c=\"1\">45.7397</fl>"
       << "<fl c=\"3\">0.1</fl>"
       << "</tree>"
       << "<tree sp=\"1\" tp=\"1\">"
       << "<fl c=\"0\">3.23486</fl>"
       << "<fl c=\"1\">42.8955</fl>"
       << "<fl c=\"3\">0.1</fl>"
       << "</tree>"
       << "<tree sp=\"1\" tp=\"1\">"
       << "<fl c=\"0\">9.17969</fl>"
       << "<fl c=\"1\">52.9602</fl>"
       << "<fl c=\"3\">0.1</fl>"
       << "</tree>"
       << "<tree sp=\"1\" tp=\"1\">"
       << "<fl c=\"0\">9.729</fl>"
       << "<fl c=\"1\">50.0366</fl>"
       << "<fl c=\"3\">0.1</fl>"
       << "</tree>"
       << "<tree sp=\"1\" tp=\"1\">"
       << "<fl c=\"0\">2.70996</fl>"
       << "<fl c=\"1\">63.5498</fl>"
       << "<fl c=\"3\">0.1</fl>"
       << "</tree>"
       << "<tree sp=\"0\" tp=\"2\">"
       << "<fl c=\"0\">0.567627</fl>"
       << "<fl c=\"1\">67.4805</fl>"
       << "<fl c=\"3\">2.4529</fl>"
       << "</tree>"
       << "<tree sp=\"0\" tp=\"2\">"
       << "<fl c=\"0\">3.00903</fl>"
       << "<fl c=\"1\">72.6868</fl>"
       << "<fl c=\"3\">5.0366</fl>"
       << "</tree>"
       << "<tree sp=\"0\" tp=\"2\">"
       << "<fl c=\"0\">7.91626</fl>"
       << "<fl c=\"1\">79.4434</fl>"
       << "<fl c=\"3\">7.4434</fl>"
       << "</tree>"
       << "<tree sp=\"0\" tp=\"2\">"
       << "<fl c=\"0\">0.823975</fl>"
       << "<fl c=\"1\">88.9771</fl>"
       << "<fl c=\"3\">9.9768</fl>"
       << "</tree>"
       << "<tree sp=\"0\" tp=\"2\">"
       << "<fl c=\"0\">1.65405</fl>"
       << "<fl c=\"1\">92.7002</fl>"
       << "<fl c=\"3\">1.49</fl>"
       << "</tree>"
       << "<tree sp=\"1\" tp=\"2\">"
       << "<fl c=\"0\">5.04761</fl>"
       << "<fl c=\"1\">91.1194</fl>"
       << "<fl c=\"3\">1.197</fl>"
       << "</tree>"
       << "<tree sp=\"1\" tp=\"2\">"
       << "<fl c=\"0\">9.33838</fl>"
       << "<fl c=\"1\">99.5117</fl>"
       << "<fl c=\"3\">4.119</fl>"
       << "</tree>"
       << "<tree sp=\"1\" tp=\"2\">"
       << "<fl c=\"0\">8.80127</fl>"
       << "<fl c=\"1\">94.9768</fl>"
       << "<fl c=\"3\">3.9917</fl>"
       << "</tree>"
       << "<tree sp=\"1\" tp=\"2\">"
       << "<fl c=\"0\">5.16968</fl>"
       << "<fl c=\"1\">104.865</fl>"
       << "<fl c=\"3\">3.3799</fl>"
       << "</tree>"
       << "<tree sp=\"1\" tp=\"2\">"
       << "<fl c=\"0\">4.32129</fl>"
       << "<fl c=\"1\">119.867</fl>"
       << "<fl c=\"3\">1.744</fl>"
       << "</tree>"
       << "<tree sp=\"1\" tp=\"2\">"
       << "<fl c=\"0\">2.34985</fl>"
       << "<fl c=\"1\">127.039</fl>"
       << "<fl c=\"3\">6.884</fl>"
       << "</tree>"
       << "<tree sp=\"1\" tp=\"2\">"
       << "<fl c=\"0\">1.14746</fl>"
       << "<fl c=\"1\">122.955</fl>"
       << "<fl c=\"3\">6.437</fl>"
       << "</tree>"
       << "<tree sp=\"1\" tp=\"2\">"
       << "<fl c=\"0\">0.964355</fl>"
       << "<fl c=\"1\">122.571</fl>"
       << "<fl c=\"3\">9.5117</fl>"
       << "</tree>"
       << "<tree sp=\"1\" tp=\"2\">"
       << "<fl c=\"0\">2.88086</fl>"
       << "<fl c=\"1\">120.776</fl>"
       << "<fl c=\"3\">4.865</fl>"
       << "</tree>"
       << "<tree sp=\"1\" tp=\"2\">"
       << "<fl c=\"0\">8.58765</fl>"
       << "<fl c=\"1\">120.49</fl>"
       << "<fl c=\"3\">9.867</fl>"
       << "</tree>"
       << "<tree sp=\"0\" tp=\"3\">"
       << "<fl c=\"0\">4.3457</fl>"
       << "<fl c=\"1\">120.197</fl>"
       << "<fl c=\"3\">146.606</fl>"
       << "</tree>"
       << "<tree sp=\"0\" tp=\"3\">"
       << "<fl c=\"0\">9.83887</fl>"
       << "<fl c=\"1\">131.873</fl>"
       << "<fl c=\"3\">150.793</fl>"
       << "</tree>"
       << "<tree sp=\"0\" tp=\"3\">"
       << "<fl c=\"0\">7.8064</fl>"
       << "<fl c=\"1\">134.985</fl>"
       << "<fl c=\"3\">37.4146</fl>"
       << "</tree>"
       << "<tree sp=\"0\" tp=\"3\">"
       << "<fl c=\"0\">1.89819</fl>"
       << "<fl c=\"1\">142.023</fl>"
       << "<fl c=\"3\">32.0618</fl>"
       << "</tree>"
       << "<tree sp=\"0\" tp=\"3\">"
       << "<fl c=\"0\">7.10449</fl>"
       << "<fl c=\"1\">146.606</fl>"
       << "<fl c=\"3\">125.012</fl>"
       << "</tree>"
       << "<tree sp=\"0\" tp=\"3\">"
       << "<fl c=\"0\">2.72217</fl>"
       << "<fl c=\"1\">141.119</fl>"
       << "<fl c=\"3\">32.16064</fl>"
       << "</tree>"
       << "<tree sp=\"1\" tp=\"3\">"
       << "<fl c=\"0\">7.97119</fl>"
       << "<fl c=\"1\">57.44</fl>"
       << "<fl c=\"3\">14.0259</fl>"
       << "</tree>"
       << "<tree sp=\"1\" tp=\"3\">"
       << "<fl c=\"0\">6.43311</fl>"
       << "<fl c=\"1\">51.666</fl>"
       << "<fl c=\"3\">19.22</fl>"
       << "</tree>"
       << "<tree sp=\"1\" tp=\"3\">"
       << "<fl c=\"0\">1.75781</fl>"
       << "<fl c=\"1\">50.793</fl>"
       << "<fl c=\"3\">54.7058</fl>"
       << "</tree>"
       << "<tree sp=\"1\" tp=\"3\">"
       << "<fl c=\"0\">2.87476</fl>"
       << "<fl c=\"1\">71.79</fl>"
       << "<fl c=\"3\">83.8928</fl>"
       << "</tree>"
       << "<tree sp=\"1\" tp=\"3\">"
       << "<fl c=\"0\">1.49536</fl>"
       << "<fl c=\"1\">78.241</fl>"
       << "<fl c=\"3\">63.5498</fl>"
       << "</tree>"
       << "<tree sp=\"0\" tp=\"5\">"
       << "<fl c=\"0\">1.01929</fl>"
       << "<fl c=\"1\">88.135</fl>"
       << "<fl c=\"3\">134.985</fl>"
       << "</tree>"
       << "<tree sp=\"0\" tp=\"5\">"
       << "<fl c=\"0\">7.15332</fl>"
       << "<fl c=\"1\">81.989</fl>"
       << "<fl c=\"3\">178.241</fl>"
       << "</tree>"
       << "<tree sp=\"0\" tp=\"5\">"
       << "<fl c=\"0\">7.8186</fl>"
       << "<fl c=\"1\">81.183</fl>"
       << "<fl c=\"3\">132.306</fl>"
       << "</tree>"
       << "<tree sp=\"0\" tp=\"5\">"
       << "<fl c=\"0\">2.23389</fl>"
       << "<fl c=\"1\">97.278</fl>"
       << "<fl c=\"3\">183.191</fl>"
       << "</tree>"
       << "<tree sp=\"0\" tp=\"5\">"
       << "<fl c=\"0\">6.73218</fl>"
       << "<fl c=\"1\">91.058</fl>"
       << "<fl c=\"3\">45.0928</fl>"
       << "</tree>"
       << "<tree sp=\"0\" tp=\"5\">"
       << "<fl c=\"0\">6.01807</fl>"
       << "<fl c=\"1\">98.108</fl>"
       << "<fl c=\"3\">45.7397</fl>"
       << "</tree>"
       << "<tree sp=\"1\" tp=\"5\">"
       << "<fl c=\"0\">11.1389</fl>"
       << "<fl c=\"1\">3.9917</fl>"
       << "<fl c=\"3\">120.776</fl>"
       << "</tree>"
       << "<tree sp=\"1\" tp=\"5\">"
       << "<fl c=\"0\">18.7866</fl>"
       << "<fl c=\"1\">20.7581</fl>"
       << "<fl c=\"3\">33.6365</fl>"
       << "</tree>"
       << "<tree sp=\"1\" tp=\"5\">"
       << "<fl c=\"0\">10.8032</fl>"
       << "<fl c=\"1\">21.7468</fl>"
       << "<fl c=\"3\">47.2839</fl>"
       << "</tree>"
       << "<tree sp=\"1\" tp=\"5\">"
       << "<fl c=\"0\">16.9312</fl>"
       << "<fl c=\"1\">39.3799</fl>"
       << "<fl c=\"3\">56.897</fl>"
       << "</tree>"
       << "<tree sp=\"1\" tp=\"5\">"
       << "<fl c=\"0\">15.7288</fl>"
       << "<fl c=\"1\">36.0596</fl>"
       << "<fl c=\"3\">98.6877</fl>"
       << "</tree>"
       << "</tr_treemap>";
}

