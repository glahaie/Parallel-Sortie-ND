//---------------------------------------------------------------------------
// TestOutputShort
//---------------------------------------------------------------------------
#if !defined(TestOutputShort_H)
  #define TestOutputShort_H

#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>

class clSimManager;

/**
 * This class tests the short output behavior (clOutputShort).
*/
class clTestOutputShort : public CppUnit::TestFixture {

public:

  /**
  * Groups all tests into one.
  */
  void TestOutputShort();

private:

  /**
   * Tests file creation and saving. WriteXMLFile1() does setup. The filename
   * already has the extension on it.
   * @param p_oSimManager Sim manager object.
   */
  void NormalProcessingRun1(clSimManager *p_oSimManager);

  /**
   * Tests file creation and saving. WriteXMLFile2() does setup. The filename
   * already has the extension on it.
   * @param p_oSimManager Sim manager object.
   */
  void NormalProcessingRun2(clSimManager *p_oSimManager);

  /**
   * Tests file creation and saving. WriteXMLFile3() does setup. The filename
   * already has the extension on it.
   * @param p_oSimManager Sim manager object.
   */
  void NormalProcessingRun3(clSimManager *p_oSimManager);

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

  /**
   * Writes a parameter file for normal processing run 3.
   * @return Filename written.
   */
  const char* WriteXMLFile3();

  /**
  * Writes the tree map.
  * @param oOut File stream to write to.
  */
  void WriteTreeMap(std::fstream &oOut);

};
//---------------------------------------------------------------------------

#endif // TestOutputShort_H
