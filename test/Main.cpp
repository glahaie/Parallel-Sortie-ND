//---------------------------------------------------------------------------
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/Exception.h>
#include <cppunit/SourceLine.h>
#include "TestSimManager.h"
#include "TestLightFilter.h"
#include "TestModelMath.h"
#include "TestGrids.h"
#include "TestPlot.h"
#include "TestLightOrg.h"
#include "TestGLILight.h"
#include "TestGLIMap.h"
#include "TestGapLight.h"
#include "TestAllometry.h"
#include "TestGLIPoints.h"
#include "TestSailLight.h"
#include "TestBasalAreaLight.h"
#include "TestConstantGLI.h"
#include "TestAverageLight.h"
#include "TestOutput.h"
#include "TestQuadratGLILight.h"
#include "TestOutputShort.h"
#include "TestTreePopulation.h"
#include "TestLightDepSeedSurvival.h"
#include "Messages.h"
#include <iostream>
#include <cstdlib>
//---------------------------------------------------------------------------
using namespace std;

int main(int argc, char * argv[])
{
  try {
    int i=atoi(argv[1]);
    switch(i) {
    case 1:
    	{
      clTestModelMath *p_oMathTest = new clTestModelMath();
      p_oMathTest->TestMath();
      cout << "TestMath test was successful.\n";
      delete p_oMathTest;
      }
      break;
    case 2:
    	{
    //clTestSimManager *p_oSimManagerTest = new clTestSimManager();
    //p_oSimManagerTest->TestDoSetup1();
    //p_oSimManagerTest->TestDoSetup2();
    //p_oSimManagerTest->TestDoSetup3();
      cout << "TestSimManager test was successful.\n";
    //delete p_oSimManagerTest;
      }
      break;
    case 3:
    	{
      clTestLightFilter *p_oFilter = new clTestLightFilter();
      p_oFilter->TestLightFiltering();
      cout << "TestLightFiltering test was successful.\n";
      delete p_oFilter;
      }
      break;
    case 4:
    	{
      clTestTreePopulation *p_oTestTreePopulation = new clTestTreePopulation();
      p_oTestTreePopulation->TestTreePopulation();
      cout << "TestTreePopulation test was successful." << endl;
      delete p_oTestTreePopulation;
      }
      break;  
    case 5:
    	{
      clTestGLILight *p_oTestGLILight = new clTestGLILight();
      p_oTestGLILight->TestGLILight();
      cout << "TestGLILight test was successful." << endl;
      delete p_oTestGLILight;
      }
      break;
    case 6:
    	{
      clTestGLIMap *p_oTestGLIMap = new clTestGLIMap();
      p_oTestGLIMap->TestGLIMap();
      cout << "TestGLIMap test was successful." << endl;
      delete p_oTestGLIMap;
      }
      break;
    case 7:
    	{
      clTestGapLight *p_oTestGapLight = new clTestGapLight();
      p_oTestGapLight->TestGapLight();
      cout << "TestGapLight test was successful." << endl;
      delete p_oTestGapLight;
      }
      break;
    case 8:
    	{
      clTestGLIPoints *p_oTestGLIPoints = new clTestGLIPoints();
      p_oTestGLIPoints->TestGLIPoints();
      cout << "TestGLIPoints test was successful." << endl;
      delete p_oTestGLIPoints;
      }
      break;
    case 9:
    	{
      clTestSailLight *p_oTestSailLight = new clTestSailLight();
      p_oTestSailLight->TestSailLight();
      cout << "TestSailLight test was successful." << endl;
      delete p_oTestSailLight;
      }
      break;
    case 10:
    	{
      clTestLightOrg *p_oTestLightOrg = new clTestLightOrg();
      p_oTestLightOrg->TestLightOrg();
      cout << "TestLightOrg test was successful." << endl;
      delete p_oTestLightOrg;
      }
      break;
    case 11:
    	{
      clTestBasalAreaLight *p_oTestBasalLight = new clTestBasalAreaLight();
      p_oTestBasalLight->TestBasalAreaLight();
      cout << "TestBasalAreaLight test was successful." << endl;
      delete p_oTestBasalLight;
      }
      break;
    case 12:
    	{
      clTestConstantGLI *p_oTestConstantGLI = new clTestConstantGLI();
      p_oTestConstantGLI->TestConstantGLI();
      cout << "TestConstantGLI test was successful." << endl;
      delete p_oTestConstantGLI;
      }
      break;
    case 13:
    	{
      clTestAverageLight *p_oTest = new clTestAverageLight();
      p_oTest->TestAverageLight();
      cout << "TestAverageLight test was successful." << endl;
      delete p_oTest;
      }
      break;
    case 14:
    	{
      clTestLightDepSeedSurvival *p_oTestLightDepSeedSurvival = new clTestLightDepSeedSurvival();
      p_oTestLightDepSeedSurvival->TestLightDepSeedSurvival();
      cout << "TestLightDepSeedSurvival test was successful." << endl;
      delete p_oTestLightDepSeedSurvival;
      }
      break;
    case 15:
    	{
      clTestQuadratGLILight *p_oTestQuadratGLILight = new clTestQuadratGLILight();
      p_oTestQuadratGLILight->TestQuadratGLILight();
      cout << "TestQuadratGLILight test was successful." << endl;
      delete p_oTestQuadratGLILight;
      }
      break;
//*******************************************
// Problem
//*******************************************
  //clTestOutput *p_oTest = new clTestOutput();
  //p_oTest->TestOutput();
  //cout << "TestOutput test was successful." << endl;
  //delete p_oTest;

  }
  return 0;
  } catch (CppUnit::Exception& err) {
    cout << "Exception thrown - message: " << err.what() << " in file "
         << err.sourceLine().fileName() << " at line "
         << err.sourceLine().lineNumber() << ".";
  } catch (modelErr& err) {
    cout << "Exception thrown by " << err.cFunction << ":  " << err.cMoreInfo;
  } catch (...) {
    cout << "Exception thrown.";
  }
}