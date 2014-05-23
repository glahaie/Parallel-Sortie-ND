//---------------------------------------------------------------------------
// TestStormLight
//---------------------------------------------------------------------------
#if !defined(TestStormLight_H)
#define TestStormLight_H

#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>

class clSimManager;

/**
* Tests the clStormLight class.
*/
class clTestStormLight : public CppUnit::TestFixture
{

  public:

  /**
  * Rolls together all the tests into one function.
  */
  void TestStormLight();

  private:

  /**
  * Tests normal processing - run 1.  This run uses a deterministic light level
  * and puts in a given set of trees, both with and without storm damage.
  * This then checks the light values in select cells to make sure that the
  * proper values are set.  WriteXMLFile1() does setup.
  * @param p_oSimManager Sim Manager to do runs.
  */
  void NormalProcessingRun1(clSimManager *p_oSimManager);

  /**
  * Tests normal processing - run 2.  This run uses a deterministic light level
  * but no snags in the run.  This puts in a given set of trees, both with and
  * without storm damage. This then checks the light values in select cells to
  * make sure that the proper values are set.  WriteXMLFile2() does setup.
  * @param p_oSimManager Sim Manager to do runs.
  */
  void NormalProcessingRun2(clSimManager *p_oSimManager);

  /**
  * Tests error processing.
  * @param p_oSimManager Sim Manager to do runs.
  */
  void TestErrorProcessing(clSimManager *p_oSimManager);


  /**
  * Writes a parameter file for normal proceessing run 1.  This has the storm
  * and storm damage appliers, a mortality behavior to satisfy storm
  * requirements, and the storm light behavior. The timestep length is 1 year.
  * @return Filename written.
  */
  const char* WriteXMLFile1();

  /**
  * Writes a parameter file for normal proceessing run 1.  This has the storm
  * and storm damage appliers, a mortality behavior to satisfy storm
  * requirements, and the storm light behavior. The timestep length is 1 year.
  * @return Filename written.
  */
  const char* WriteXMLFile2();

  /**
  * Writes an error file where the minimum number of trees for a full canopy
  * is less than 0.
  * @return File name of the freshly written parameter file.
  */
  const char* WriteXMLErrorFile1();


};
//---------------------------------------------------------------------------
#endif // TestStormLights_H
