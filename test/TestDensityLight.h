//---------------------------------------------------------------------------
// TestDensityLight
//---------------------------------------------------------------------------
#if !defined(TestDensityLight_H)
#define TestDensityLight_H

#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>

class clSimManager;

/**
* Tests the clDensityLight class.
*/
class clTestDensityLight : public CppUnit::TestFixture
{

  public:

  /**
  * Rolls together all the tests into one function.
  */
  void TestDensityLight();

  private:

  /**
  * Tests normal processing - run 1.  This checks the calculation of mean GLI
  * and verifies that new light level calculations are triggered correctly.
  * WriteXMLFile1() does setup.
  * @param p_oSimManager Sim Manager to do runs.
  */
  void NormalProcessingRun1(clSimManager *p_oSimManager);

  /**
  * Tests normal processing - run 2.  This ensures that the calculation of mean
  * GLI is bounded between 0 and 100.  WriteXMLFile2() does setup.
  * @param p_oSimManager Sim Manager to do runs.
  */
  void NormalProcessingRun2(clSimManager *p_oSimManager);

  /**
  * Tests normal processing - run 3.  This checks to make sure grid cell sizes
  * are honored and allows checking of the light level distribution.
  * WriteXMLFile3() does setup.  This produces an output file called "Density
  * Light Distribution.txt".
  * @param p_oSimManager Sim Manager to do runs.
  */
  void NormalProcessingRun3(clSimManager *p_oSimManager);

  /**
  * Tests normal processing - run 4.  This double-checks grid map reading.
  * WriteXMLFile4() does setup.
  * @param p_oSimManager Sim Manager to do runs.
  */
  void NormalProcessingRun4(clSimManager *p_oSimManager);

  /**
  * Tests error processing.
  * @param p_oSimManager Sim Manager to do runs.
  */
  void TestErrorProcessing(clSimManager *p_oSimManager);


  /**
  * Writes a parameter file for normal proceessing run 1.
  * @return Filename written.
  */
  const char* WriteXMLFile1();

  /**
  * Writes a parameter file for normal proceessing run 2.
  * @return Filename written.
  */
  const char* WriteXMLFile2();

  /**
  * Writes a parameter file for normal proceessing run 3.
  * @return Filename written.
  */
  const char* WriteXMLFile3();

  /**
  * Writes a parameter file for normal proceessing run 4.
  * @return Filename written.
  */
  const char* WriteXMLFile4();

  /**
  * Writes an error file where the "c" parameter = 0.
  * @return File name of the freshly written parameter file.
  */
  const char* WriteXMLErrorFile1();

  /**
  * Writes an error file where the change threshold < 0.
  * @return File name of the freshly written parameter file.
  */
  const char* WriteXMLErrorFile2();

  /**
  * Writes an error file where the minimum DBH < 0.
  * @return File name of the freshly written parameter file.
  */
  const char* WriteXMLErrorFile3();

  /**
  * Writes an error file where the "Density Light" grid cell lengths don't
  * divide evenly into the plot lengths.
  * @return File name of the freshly written parameter file.
  */
  const char* WriteXMLErrorFile4();

  /**
  * Writes common portions of the test parameter files (allometry and tree
  * pop).
  * @param oOut File stream to write to.
  */
  void WriteCommonStuff(std::fstream &oOut);

};
//---------------------------------------------------------------------------
#endif // TestDensityLight_H
