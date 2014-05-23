//---------------------------------------------------------------------------
// TestModelMath.cpp
//---------------------------------------------------------------------------
#include "TestModelMath.h"
#include "ModelMath.h"
#include "Messages.h"
#include <math.h>
#include <gsl/gsl_randist.h>

///////////////////////////////////////////////////////////////////////////
//  TestMath()
///////////////////////////////////////////////////////////////////////////
void clTestModelMath::TestMath() {

  TestRandom();
  TestFunctions();
  TestAddBarkToDBH();
}

///////////////////////////////////////////////////////////////////////////
// TestAddBarkToDBH()
///////////////////////////////////////////////////////////////////////////
void clTestModelMath::TestAddBarkToDBH() {

  float fDIB, fA, fB, fC, fExpectedDBH, fActualDBH;

  //Normal processing
  fDIB = 8;
  fA = 0.01;
  fB = 0.5;
  fC = 0.1;
  fExpectedDBH = 10.41;
  fActualDBH = clModelMath::AddBarkToDBH(fDIB, fA, fB, fC);
  CPPUNIT_ASSERT(fabs(fExpectedDBH - fActualDBH) < 0.001);

  fDIB = 45.3;
  fA = 0.2;
  fB = 0.8;
  fC = 0.01;
  fExpectedDBH = 56.9609;
  fActualDBH = clModelMath::AddBarkToDBH(fDIB, fA, fB, fC);
  CPPUNIT_ASSERT(fabs(fExpectedDBH - fActualDBH) < 0.001);

  fDIB = 2.30E-23;
  fA = 0.2;
  fB = 0.8;
  fC = 0.01;
  fExpectedDBH = 0.2;
  fActualDBH = clModelMath::AddBarkToDBH(fDIB, fA, fB, fC);
  CPPUNIT_ASSERT(fabs(fExpectedDBH - fActualDBH) < 0.001);

  fDIB = 4.50E+10;
  fA = 0.01;
  fB = 0.5;
  fC = 0.1;
  fExpectedDBH = 2.025E+20;
  fActualDBH = clModelMath::AddBarkToDBH(fDIB, fA, fB, fC);
  CPPUNIT_ASSERT(fabs(fExpectedDBH - fActualDBH) < 1E15);

  //Error processing
  try
  {
    fDIB = -25.2;
    fA = 0.01;
    fB = 0.5;
    fC = 0.1;
    clModelMath::AddBarkToDBH(fDIB, fA, fB, fC);
    CppUnit::Asserter::fail("TestAddBarkToDBH error processing didn't catch error for DIB < 0.");
  }
  catch (modelErr& err)
  {
    ;
  }

  try
  {
    fDIB = 0;
    fA = 0.01;
    fB = 0.5;
    fC = 0.1;
    clModelMath::AddBarkToDBH(fDIB, fA, fB, fC);
    CppUnit::Asserter::fail("TestAddBarkToDBH error processing didn't catch error for DIB = 0.");
  }
  catch (modelErr& err)
  {
    ;
  }

  try
  {
    fDIB = 8.30E+20;
    fA = 0.01;
    fB = 0.5;
    fC = 0.1;
    clModelMath::AddBarkToDBH(fDIB, fA, fB, fC);
    CppUnit::Asserter::fail("TestAddBarkToDBH error processing didn't catch error for large values of DIB.");
  }
  catch (modelErr& err)
  {
    ;
  }

}

///////////////////////////////////////////////////////////////////////////
//  TestRandom()
///////////////////////////////////////////////////////////////////////////
void clTestModelMath::TestRandom() {

  long iSeed;
  float fNumTimes = 100000000, fRandom,
    fRandom2,
    fLowE4 = 1E-04,
    fLowE3 = 1E-03,
    fLowE5 = 1e-05,
    fHiE4 = 1-1E-04,
    fHiE3 = 1-1E-03,
    fHiE5 = 1-1E-05,
    fExpected;
  int i,
  iLessThanE4 = 0,
  iLessThanE5 = 0,
  iLessThanE3 = 0,
  iMoreThanE3 = 0,
  iMoreThanE4 = 0,
  iMoreThanE5 = 0;

  //Make sure two different seeds don't give the same sequence
  iSeed = -1154552;
  clModelMath::SetRandomSeed(iSeed);
  fRandom = clModelMath::GetRand();
  iSeed = -25;
  clModelMath::SetRandomSeed(iSeed);
  fRandom2 = clModelMath::GetRand();
  CPPUNIT_ASSERT(fabs(fRandom - fRandom2) > 0.01);

  //Run the random numbers and make sure that we're getting the appropriate
  //number of low and high values
  iSeed = -5;
  clModelMath::SetRandomSeed(iSeed);
  for (i = 0; i < fNumTimes; i++) {
    fRandom = clModelMath::GetRand();

    if (fRandom < fLowE3) iLessThanE3++;
    if (fRandom < fLowE4) iLessThanE4++;
    if (fRandom < fLowE5) iLessThanE5++;

    if (fRandom > fHiE3) iMoreThanE3++;
    if (fRandom > fHiE4) iMoreThanE4++;
    if (fRandom > fHiE5) iMoreThanE5++;
  }

  //Make sure we're getting within 10% of what we want
  fExpected = fNumTimes * fLowE3;
  CPPUNIT_ASSERT(fabs(fExpected - iLessThanE3)/fExpected < 0.1);
  CPPUNIT_ASSERT(fabs(fExpected - iMoreThanE3)/fExpected < 0.1);

  fExpected = fNumTimes * fLowE4;
  CPPUNIT_ASSERT(fabs(fExpected - iLessThanE4)/fExpected < 0.1);
  CPPUNIT_ASSERT(fabs(fExpected - iMoreThanE4)/fExpected < 0.1);

  fExpected = fNumTimes * fLowE5;
  CPPUNIT_ASSERT(fabs(fExpected - iLessThanE5)/fExpected < 0.1);
  CPPUNIT_ASSERT(fabs(fExpected - iMoreThanE5)/fExpected < 0.1);

  //Test GetRand - test 100 random numbers
  for (i = 0; i < 100; i++) {
    fRandom = clModelMath::GetRand();
    CPPUNIT_ASSERT(fRandom > 0.0 && fRandom < 1.0);
  }

  //Test normal distribution - 1000 random numbers, and check the mean and
  //standard deviation. This is less about a fear that the distribution is
  //calculated incorrectly (I'm sure it's not, having faith in the GSL) and
  //more about making sure we have correctly implemented it.
  float *p_fRans = new float[1000];
  float fStdDev = 5, fMean = 0, fActualStdDev = 0;
  for (i = 0; i < 1000; i++) {
    p_fRans[i] = clModelMath::NormalRandomDraw(fStdDev);
    fMean += p_fRans[i];
  }
  //Finish calculating the mean and check - should be about zero
  fMean /= 1000.0;
  CPPUNIT_ASSERT(fabs(fMean) < 0.2);

  //Calculate standard deviation
  for (i = 0; i < 1000; i++) {
    fActualStdDev += pow(p_fRans[i] - fMean, 2);
  }
  fActualStdDev /= 1000.0;
  fActualStdDev = sqrt(fActualStdDev);
  CPPUNIT_ASSERT(fabs(fStdDev - fActualStdDev) < 0.2);

  //Again, this is just a test to make sure I'm correctly using the GSL
  float p = 0.55;
  fMean = 0;
  for (i = 0; i < 1000; i++) {
    p_fRans[i] = gsl_ran_binomial(clModelMath::randgen, p, 1);
    CPPUNIT_ASSERT(p_fRans[i] == 0 || p_fRans[i] == 1);
    fMean += p_fRans[i];
  }
  fMean /= 1000.0;
  CPPUNIT_ASSERT(fabs(fMean - p) < 0.05);
  delete[] p_fRans;

  //Test of the Gamma implementation
  float fScale = 0.00000001, fMeanPar = 25, fMax, fMin, fVal;
  fMean = 0; fMin = 10000; fMax = 0;
  for (i = 0; i < 1000; i++) {
    fVal = clModelMath::GammaRandomDraw(fMeanPar, fScale);
    fMean += fVal;
    fMin = fMin > fVal ? fVal : fMin;
    fMax = fMax < fVal ? fVal : fMax;
  }
  fMean /= 1000.0;
  CPPUNIT_ASSERT(fabs(fMean - fMeanPar) < 0.05);
  CPPUNIT_ASSERT(fMax < 25.5);
  CPPUNIT_ASSERT(fMin > 24.5);
}

///////////////////////////////////////////////////////////////////////////
//  TestFunctions()
///////////////////////////////////////////////////////////////////////////

void clTestModelMath::TestFunctions() {
  float fExpectedResult, fActualResult, //for comparing results
        fSlope, fIntercept, fX,         //for testing CalcPointValue
        fDbh;                           //for testing CalculateBasalArea

  //*******************************************
  //Test CalcPointValue
  //*******************************************
  fSlope = 0.0; fIntercept = 0.0; fX = 0.0; fExpectedResult = 0.0;
  fActualResult = clModelMath::CalcPointValue(fX, fSlope, fIntercept);
  CPPUNIT_ASSERT(fabs(fActualResult - fExpectedResult) < 0.0001);

  fSlope = 3.5; fIntercept = 14.664; fX = 92.34; fExpectedResult = 337.854;
  fActualResult = clModelMath::CalcPointValue(fX, fSlope, fIntercept);
  CPPUNIT_ASSERT(fabs(fActualResult - fExpectedResult) < 0.0001);

  fSlope = -46.2334; fIntercept = -8.498; fX = -0.9982; fExpectedResult = 37.65217988;
  fActualResult = clModelMath::CalcPointValue(fX, fSlope, fIntercept);
  CPPUNIT_ASSERT(fabs(fActualResult - fExpectedResult) < 0.0001);

  fSlope = 24.46; fX = -238; fExpectedResult = -5821.48;
  fActualResult = clModelMath::CalcPointValue(fX, fSlope);
  CPPUNIT_ASSERT(fabs(fActualResult - fExpectedResult) < 0.0001);

  fSlope = -0.897; fIntercept = 2.4; fX = 8.90E-23; fExpectedResult = 2.4;
  fActualResult = clModelMath::CalcPointValue(fX, fSlope, fIntercept);
  CPPUNIT_ASSERT(fabs(fActualResult - fExpectedResult) < 0.0001);

  fSlope = 4.773; fIntercept = 2.498; fX = 6.20E+19; fExpectedResult = 2.95926E+20;
  fActualResult = clModelMath::CalcPointValue(fX, fSlope, fIntercept);
  CPPUNIT_ASSERT(fabs(fActualResult - fExpectedResult) < 1.0E+15);

  fSlope = 8.90E-23; fIntercept = 98.2984; fX = -3.985; fExpectedResult = 98.2984;
  fActualResult = clModelMath::CalcPointValue(fX, fSlope, fIntercept);
  CPPUNIT_ASSERT(fabs(fActualResult - fExpectedResult) < 0.0001);

  fSlope = 6.20E+19; fIntercept = 0.009; fX = 9.573; fExpectedResult = 5.93526E+20;
  fActualResult = clModelMath::CalcPointValue(fX, fSlope, fIntercept);
  CPPUNIT_ASSERT(fabs(fActualResult - fExpectedResult) < 1.0E+15);

  fSlope = 78; fIntercept = 8.90E-23; fX = 8.225; fExpectedResult = 641.55;
  fActualResult = clModelMath::CalcPointValue(fX, fSlope, fIntercept);
  CPPUNIT_ASSERT(fabs(fActualResult - fExpectedResult) < 0.0001);

  fSlope = 25; fIntercept = 6.20E+19; fX = 0.1258; fExpectedResult = 6.20E+19;
  fActualResult = clModelMath::CalcPointValue(fX, fSlope, fIntercept);
  CPPUNIT_ASSERT(fabs(fActualResult - fExpectedResult) < 1.0E+14);

  //*******************************************
  //Test CalculateBasalArea
  //*******************************************
  fDbh = 36.35; fExpectedResult = 0.103776426;
  fActualResult = clModelMath::CalculateBasalArea(fDbh);
  CPPUNIT_ASSERT(fabs(fActualResult - fExpectedResult) < 0.0001);

  fDbh = 8.90E-10; fExpectedResult = 6.22113885E-23;
  fActualResult = clModelMath::CalculateBasalArea(fDbh);
  CPPUNIT_ASSERT(fabs(fActualResult - fExpectedResult) < 1.0E-28);

  fDbh = 6.20E+19; fExpectedResult = 3.01907E+35;
  fActualResult = clModelMath::CalculateBasalArea(fDbh);
  CPPUNIT_ASSERT(fabs(fActualResult - fExpectedResult) < 1.0E30);

  //Test RandomRound
  fExpectedResult = 30;
  fActualResult = clModelMath::RandomRound(29.999);
  CPPUNIT_ASSERT(fabs(fActualResult - fExpectedResult) < 0.000001);

  fExpectedResult = 15;
  fActualResult = clModelMath::RandomRound(15.001);
  CPPUNIT_ASSERT(fabs(fActualResult - fExpectedResult) < 0.0000001);
}
//---------------------------------------------------------------------------
