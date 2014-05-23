//---------------------------------------------------------------------------

#ifndef TestGLIPointsH
#define TestGLIPointsH

#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>

class clSimManager;

/**
* This class tests the clGLIPoints class.
*/
class clTestGLIPoints : public CppUnit::TestFixture {

  public:

  /**
  * Puts the tests together into one.
  */
  void TestGLIPoints();

  private:

  /**
  * Tests normal processing calculations.  WriteXMLFile1() is used for setup.
  * This only has one behavior, GLI points.  It is run.  Then this will read
  * in the output file and test the values.
  * @param p_oSimManager Object to run a test with.
  */
  void TestNormalProcessing(clSimManager *p_oSimManager);

  /**
  * This tests error processing during setup.  This inputs bad files and makes
  * sure that errors result.
  * @param p_oSimManager Object to run a test with.
  */
  void TestErrorProcessing(clSimManager *p_oSimManager);

  /**
  * Writes a parameter file to direct testing.  There is one species and one
  * behavior:  GLI points.
  *
  * @return Filename written.
  */
  const char* WriteXMLFile1();

  /**
  * Writes a parameter file with no points in the points list.
  * @return Filename written.
  */
  const char* WriteXMLErrorFile1();

  /**
  * Writes a parameter file where the number of azimuth angles is less than 0.
  * @return Filename written.
  */
  const char* WriteXMLErrorFile2();

  /**
  * Writes a parameter file where the number of altitude angles is less than 0.
  * @return Filename written.
  */
  const char* WriteXMLErrorFile3();

  /**
  * Writes a parameter file where a point's X or Y coordinate is outside the
  * plot.
  * @return Filename written.
  */
  const char* WriteXMLErrorFile4();

  /**
  * Writes a parameter file where a point's height is negative.
  * @return Filename written.
  */
  const char* WriteXMLErrorFile5();

  /**The filename.*/
  char* m_sFileName;

};
//---------------------------------------------------------------------------
#endif
