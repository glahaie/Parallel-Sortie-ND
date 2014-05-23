//---------------------------------------------------------------------------
// TestConstantGLI
//---------------------------------------------------------------------------
#if !defined(TestConstantGLI_H)
#define TestConstantGLI_H

#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>

class clSimManager;

/**
* Tests the clConstantGLI class.
*/
class clTestConstantGLI : public CppUnit::TestFixture
{

  public:

  /**
  * Rolls together all the tests into one function.
  */
  void TestConstantGLI();

  private:

  /**
  * Tests normal processing.  This checks that GLI is correctly assigned to the
  * trees to which the behavior applies.
  * WriteXMLFile1() does setup.
  * @param p_oSimManager Sim Manager to do runs.
  */
  void TestNormalProcessing(clSimManager *p_oSimManager);

  /**
  * Tests error processing.
  * @param p_oSimManager Sim Manager to do runs.
  */
  void TestErrorProcessing(clSimManager *p_oSimManager);

  /**
  * Writes a parameter file for normal proceessing.  There are three species,
  * and the constant GLI behavior is applied to species 2 and 3.
  * @return Filename written.
  */
  const char* WriteXMLFile1();

  /**
  * Writes an error file where the constant GLI is less than 0.
  * @return File name of the freshly written parameter file.
  */
  const char* WriteXMLErrorFile1();

  /**
  * Writes an error file where the constant GLI is greater than 100.
  * @return File name of the freshly written parameter file.
  */
  const char* WriteXMLErrorFile2();

  /**
  * Writes common portions of the test parameter files (allometry and tree
  * pop).
  * @param oOut File stream to write to.
  */
  void WriteCommonStuff(std::fstream &oOut);

};
//---------------------------------------------------------------------------
#endif // TestDensityLight_H
