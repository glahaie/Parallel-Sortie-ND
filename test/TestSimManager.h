//---------------------------------------------------------------------------

#ifndef TestSimManagerH
#define TestSimManagerH

#include "SimManager.h"

#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>

/**
  Tests the class clSimManager.
*/
class clTestSimManager : public CppUnit::TestFixture {

  public:


  /**
    Tests DoSetup().  Creates and parses an XML file, then feeds it to
    mp_oSimManager().  This parses the file from WriteXMLFile1().
  */
  void TestDoSetup1();

  /**
    Tests DoSetup().  Creates and parses an XML file, then feeds it to
    mp_oSimManager().  This parses the file from WriteXMLFile2().
  */
  void TestDoSetup2();


/**
    Tests DoSetup().  Creates and parses an XML file, then feeds it to
    mp_oSimManager().  This parses the file from WriteXMLFile3().
  */
  void TestDoSetup3();


  /**
    Creates a test suite of all the test cases in this object.  I'm putting
    it here so it will be easier to see and add new cases to.

    @return The test suite.
  */
  static CppUnit::Test *suite () {
   CppUnit::TestSuite *suite = new CppUnit::TestSuite ("TestSimManager");

    suite->addTest (new CppUnit::TestCaller <clTestSimManager> ("TestDoSetup1",
          &clTestSimManager::TestDoSetup1));
    suite->addTest (new CppUnit::TestCaller <clTestSimManager> ("TestDoSetup2",
          &clTestSimManager::TestDoSetup2));
    suite->addTest (new CppUnit::TestCaller <clTestSimManager> ("TestDoSetup3",
          &clTestSimManager::TestDoSetup3));

    return suite;
  };

  private:
  /**
    Writes the text of an XML file.  This file is abbreviated, and will be
    parsed within the test code itself rather than being passed to the
    test object for parsing.
    <p>
    This contains a positive random seed, which should become negative.

    @return The filename of the XML file to parse.
  */
  const char* WriteXMLFile1();

  /**
    Writes the text of an XML file.  This file is abbreviated, and will be
    parsed within the test code itself rather than being passed to the
    test object for parsing.
    <p>
    This contains a random seed of 0, which should become negative.

    @return The filename of the XML file to parse.
  */
  const char* WriteXMLFile2();

  /**
    Writes the text of an XML file.  This file is abbreviated, and will be
    parsed within the test code itself rather than being passed to the
    test object for parsing.
    <p>
    This contains a negative random seed, which should be left alone.

    @return The filename of the XML file to parse.
  */
  const char* WriteXMLFile3();


  /**
    Writes an XML file which contains a data error, to test if the test
    object will throw an exception.  Number of timesteps is negative.

    @return The filename of the XML file to parse.
  */
  const char* WriteXMLErrorFile1();

  /**
    Writes an XML file which contains a data error, to test if the test
    object will throw an exception.  Current timestep is too big.

    @return The filename of the XML file to parse.
  */
  const char* WriteXMLErrorFile2();

  /**
    Writes an XML file which contains a data error, to test if the test
    object will throw an exception.  Years per timestep is 0.

    @return The filename of the XML file to parse.
  */
  const char* WriteXMLErrorFile3();
};
//---------------------------------------------------------------------------
#endif
