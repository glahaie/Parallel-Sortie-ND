//---------------------------------------------------------------------------
// TestBasalAreaLight
//---------------------------------------------------------------------------
#if !defined(TestBasalAreaLight_H)
#define TestBasalAreaLight_H

#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>

class clSimManager;

/**
* Tests the clBasalAreaLight class.
*/
class clTestBasalAreaLight : public CppUnit::TestFixture
{

  public:

  /**
  * Rolls together all the tests into one function.
  */
  void TestBasalAreaLight();

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
  * Tests normal processing - run 5.  This double-checks radius.
  * WriteXMLFile5() does setup.
  * @param p_oSimManager Sim Manager to do runs.
  */
  void NormalProcessingRun5(clSimManager *p_oSimManager);

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
  * Writes a parameter file for normal proceessing run 5.
  * @return Filename written.
  */
  const char* WriteXMLFile5();

  /**
  * Writes an error file where the conifer "c" parameter = 0.
  * @return File name of the freshly written parameter file.
  */
  const char* WriteXMLErrorFile1();
  
  /**
  * Writes an error file where the angiosperm "c" parameter = 0.
  * @return File name of the freshly written parameter file.
  */
  const char* WriteXMLErrorFile2();

  /**
  * Writes an error file where the change threshold < 0.
  * @return File name of the freshly written parameter file.
  */
  const char* WriteXMLErrorFile3();

  /**
  * Writes an error file where the minimum DBH < 0.
  * @return File name of the freshly written parameter file.
  */
  const char* WriteXMLErrorFile4();
  
  /**
  * Writes an error file where the radius is negative.
  * @return File name of the freshly written parameter file.
  */
  const char* WriteXMLErrorFile5();

  /**
  * Writes common portions of the test parameter files (allometry and tree
  * pop).
  * @param oOut File stream to write to.
  */
  void WriteCommonStuff(std::fstream &oOut);

};
//---------------------------------------------------------------------------
#endif // TestBasalAreaLight_H
