//---------------------------------------------------------------------------
// TestAllometry
//---------------------------------------------------------------------------
#if !defined(TestAllometry_H)
  #define TestAllometry_H

#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>

class clSimManager;


/**
* Tests the clAllometry class.
*/
class clTestAllometry : public CppUnit::TestFixture
{
  public:

  /**
  * Groups together all the testing functions.
  */
  void TestAllometry();

  protected:

  /**
  * Verifies that allometry functions calculate correctly.  This run uses
  * WriteXMLFile1 for setup.  This file contains 6 species, with a mix of
  * allometric functions throughout the life history stages.  This tests each
  * allometric function for each life history stage for each species.  (No
  * actual trees are used; we just call the functions directly.)
  * @param p_oSimManager Sim manager for performing runs.
  */
  void TestNormalProcessingRun1(clSimManager *p_oSimManager);

  /**
  * Verifies that non-spatial density dependent crown allometry functions
  * calculate correctly.  This run uses WriteXMLFile7 for setup. This file
  * contains 4 species, three of which use those functions.
  * @param p_oSimManager Sim manager for performing runs.
  */
  void TestNormalProcessingRun2(clSimManager *p_oSimManager);

  /**
  * Verifies that NCI crown allometry functions calculate correctly. This run
  * uses WriteXMLFile8 for setup. This file contains 4 species, three of which
  * use those functions.
  * @param p_oSimManager Sim manager for performing runs.
  */
  void TestNormalProcessingRun3(clSimManager *p_oSimManager);

  /**
  * Tests error processing.  In the first part, invalid requests are made of
  * the clAllometry functions.  In the second part, parameter files with bad
  * data are read in.
  */
  void TestErrorProcessing(clSimManager *p_oSimManager);

  /**
  * Writes a parameter file to test allometry.  This contains six species, with
  * functions mixed up between them.
  * @return Filename written.
  */
  const char* WriteXMLFile1();

  /**
  * This writes a file with only standard functions and parameters, to make
  * sure that the others aren't required if not needed.
  * @return Filename written.
  */
  const char* WriteXMLFile2();

  /**
  * This writes a file with only linear functions and parameters, to make
  * sure that the others aren't required if not needed.
  * @return Filename written.
  */
  const char* WriteXMLFile3();

  /**
  * This writes a file with only reverse linear functions and parameters, to
  * make sure that the others aren't required if not needed.
  * @return Filename written.
  */
  const char* WriteXMLFile4();

  /**
  * This writes a file with linear height-DBH and standard crown adult
  * parameters, and standard height-DBH and Chapman-Richards sapling
  * parameters, to make sure arrays are declared correctly.
  * @return Filename written.
  */
  const char* WriteXMLFile5();

  /**
  * This writes a file with linear height-DBH and Chapman-Richards crown adult
  * parameters, and standard sapling parameters, to make sure arrays are
  * declared correctly.
  * @return Filename written.
  */
  const char* WriteXMLFile6();

  /**
  * This writes a file with non-spatial density dependent crown allometry
  * parameters.
  * @return Filename written.
  */
  const char* WriteXMLFile7();

  /**
  * This writes a file with NCI crown allometry parameters.
  * @return Filename written.
  */
  const char* WriteXMLFile8();

  /**
  * This writes a file with an unrecognized function for adult allometry.
  * @return Filename written.
  */
  const char* WriteXMLErrorFile1();

  /**
  * This writes a file with an unrecognized function for sapling allometry.
  * @return Filename written.
  */
  const char* WriteXMLErrorFile2();

  /**
  * This writes a file with an unrecognized function for seedling allometry.
  * @return Filename written.
  */
  const char* WriteXMLErrorFile3();

  /**
  * This writes a file with a 0 value for adult linear slope.
  * @return Filename written.
  */
  const char* WriteXMLErrorFile4();

  /**
  * This writes a file with a 0 value for adult reverse linear slope.
  * @return Filename written.
  */
  const char* WriteXMLErrorFile5();

  /**
  * This writes a file with a 0 value for sapling linear slope.
  * @return Filename written.
  */
  const char* WriteXMLErrorFile6();

  /**
  * This writes a file with a 0 value for sapling reverse linear slope.
  * @return Filename written.
  */
  const char* WriteXMLErrorFile7();

  /**
  * This writes a file with a 0 value for seedling linear slope.
  * @return Filename written.
  */
  const char* WriteXMLErrorFile8();

  /**
  * This writes a file with a 0 value for seedling reverse linear slope.
  * @return Filename written.
  */
  const char* WriteXMLErrorFile9();

  /**
  * This writes a file with a 0 value for diam10 to dbh ratio.
  * @return Filename written.
  */
  const char* WriteXMLErrorFile10();

  /**
  * This writes a file with an unrecognized function for adult crown radius.
  * @return Filename written.
  */
  const char* WriteXMLErrorFile11();

  /**
  * This writes a file with an unrecognized function for adult crown height.
  * @return Filename written.
  */
  const char* WriteXMLErrorFile12();

  /**
  * This writes a file with an unrecognized function for sapling crown radius.
  * @return Filename written.
  */
  const char* WriteXMLErrorFile13();

  /**
  * This writes a file with an unrecognized function for sapling crown height.
  * @return Filename written.
  */
  const char* WriteXMLErrorFile14();
};
//---------------------------------------------------------------------------
#endif // TestTree_H
