//---------------------------------------------------------------------------
// TestPlot
//---------------------------------------------------------------------------
#if !defined(TestPlot_H)
  #define TestPlot_H

#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>

class clPlot;

/**
* Tests the clPlot class.
*/
class clTestPlot : public CppUnit::TestFixture
{
  public:

  /**
  * Groups together all the other plot testing functions into a comprehensive
  * plot test.
  */
  void TestPlot();

  protected:

  /**
  * Tests clPlot's getter functions.
  */
  void TestPlotGetters(clPlot *p_oPlot);

  /**
  * Tests the GetDistance() function of clPlot.
  */
  void TestGetDistance(clPlot *p_oPlot);

  /**
  * Tests the GetAzimuth() function of clPlot.
  */
  void TestGetAzimuth(clPlot *p_oPlot);

  /**
  * Tests the GetFastAzimuthAngle() function of clPlot.  This is not yet a
  * thorough test - just one to help with bug fixes.
  */
  void TestGetFastAzimuthAngle(clPlot *p_oPlot);

  /**
  *
  * Tests the GetUncorrectedX and GetUncorrectedY functions of clPlot.
  */
  void TestGetUncorrectedXandY(clPlot *p_oPlot);

  /**
  * Writes a parameter file to test plot.
  * @return Filename written.
  */
  const char* WriteXMLFile1();

};
#endif // TestPlot_H
