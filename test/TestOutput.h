//---------------------------------------------------------------------------
// TestOutput
//---------------------------------------------------------------------------
#if !defined(TestOutput_H)
  #define TestOutput_H

#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>

class clSimManager;

/**
 * This class tests the output behavior (clOutput).
*/
class clTestOutput : public CppUnit::TestFixture {

public:

  /**
  * Groups all tests into one.
  */
  void TestOutput();

private:

  /**
   * Tests file creation and saving. WriteXMLFile1() does setup. The filename
   * already has the extension on it.
   * @param p_oSimManager Sim manager object.
   */
  void TestFilePresence(clSimManager *p_oSimManager);


  void NormalProcessingRun1(clSimManager *p_oSimManager);
  void NormalProcessingRun3(clSimManager *p_oSimManager);
  void NormalProcessingRun4(clSimManager *p_oSimManager);
  void NormalProcessingRun5(clSimManager *p_oSimManager);
  void NormalProcessingRun6(clSimManager *p_oSimManager);
  void NormalProcessingRun7(clSimManager *p_oSimManager);

  /**
   * Writes a parameter file for normal processing run 1.
   * @return Filename written.
   */
  const char* WriteXMLFile1();

  /**
   * Writes a parameter file for normal processing run 1.
   * @return Filename written.
   */
  const char* WriteXMLFile2();

};
//---------------------------------------------------------------------------

#endif // TestMastingSpatialDisperse_H
