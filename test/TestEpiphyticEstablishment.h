//---------------------------------------------------------------------------
// TestEpiphyticEstablishment
//---------------------------------------------------------------------------
#if !defined(TestEpiphyticEstablishment_H)
  #define TestEpiphyticEstablishment_H

#include <cppunit/TestFixture.h>
#include <fstream>

class clSimManager;

/**
* Tests the class clEpiphyticEstablishment.
*/
class clTestEpiphyticEstablishment : public CppUnit::TestFixture {

  public:

  /**
  * Rolls all other tests into a single function to call.
  */
  void TestEpiphyticEstablishment();

  protected:


  /**
  * WriteXMLFile1() does setup. Four groups of substrate trees are distributed
  * around the plot, and the resulting seedlings are identified and counted.
  * This verifies that substrate trees are correctly identified, that seedling
  * probabilities are correctly calculated, and that seedling heights are
  * correctly determined.
  * @param p_oSimManager Sim manager
  */
  void TestNormalProcessingRun1(clSimManager *p_oSimManager);

  /**
   * Make sure GLI gets set up right.
   * @param p_oSimManager Sim manager
   */
  void TestNormalProcessingRun2(clSimManager *p_oSimManager);

  /**
  * Tests error processing.
  * @param p_oSimManager Sim manager
  */
  void TestErrorProcessing(clSimManager *p_oSimManager);

  /**
  * Writes a parameter file to direct testing for normal processing run one.
  * @return Filename written.
  */
  const char* WriteXMLFile1();

  /**
  * Writes a parameter file to direct testing for normal processing run two.
  * @return Filename written.
  */
  const char* WriteXMLFile2();

   /**
  * Writes a file where the number of altitude angles is less than 1.
  * @return Filename written.
  */
  const char* WriteXMLErrorFile1();

  /**
  * Writes a file where the number of azimuth angles is less than 1.
  * @return Filename written.
  */
  const char* WriteXMLErrorFile2();

  /**
  * Writes a file where the behavior is applied to seedlings.
  * @return Filename written.
  */
  const char* WriteXMLErrorFile3();

  /**
  * Writes a file where some of the trees don't have mortality applied.
  * @return Filename written.
  */
  const char* WriteXMLErrorFile4();

  /**
  * Writes common portions of the test parameter files.
  * @param oOut File stream to write to.
  */
  void WriteErrorCommonStuff(std::fstream &oOut);

};
//---------------------------------------------------------------------------
#endif // TestEpiphyticEstablishment_H
