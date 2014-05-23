//---------------------------------------------------------------------------
// TestLightOrg
//---------------------------------------------------------------------------
#if !defined(TestLightOrg_H)
  #define TestLightOrg_H

#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>

class clSimManager;

/**
* Tests the clLightOrg class (currently not completely).
*/
class clTestLightOrg : public CppUnit::TestFixture {

  public:

  /**
  * Gathers all testing into one function.
  */
  void TestLightOrg();

  protected:

  /**
  * Tests light extinction coefficient management by taking a target tree and
  * surrounding it with both live and snag neighbors to see if the amount of
  * shade calculated by sail light comes out right.  WriteXMLFile1() is used
  * to set up the run.  A single sapling of species 1 is created, along with
  * four neighbors.  Then sail light is run and the resulting shade is compared
  * to expected.  Incidentally, this is a good test of sail light as well.
  */
  void TestGetLightExtinctionCoefficient(clSimManager *p_oSimManager);

  /**
  * Tests the DoSetup() function of clLightOrg.  Incompletely.  This just tests
  * to make sure that the snag data isn't required for a non-snag run,
  * that the error of size classes overlapping is caught correctly, and that
  * all light extinction coefficients are required to be between 0 and 1.
  */
  void TestDoSetup(clSimManager *p_oSimManager);

  /**
  * Writes a parameter file to direct testing.  Timestep length is 1 year.
  * This contains one species.
  * Sail light is applied to Species 1 saplings.
  * @return Filename written.
  */
  const char* WriteXMLFile1();

  /**
  * Writes a parameter file to direct testing.  Has no snags, nor any snag
  * light extinction coefficient parameters.
  * @return Filename written.
  */
  const char* WriteXMLFile2();

  /**
  * Writes a parameter file to direct error testing.  Snag age classes
  * overlap.
  * @return Filename written.
  */
  const char* WriteXMLErrorFile1();

  /**
  * Writes a parameter file to direct error testing.  One of the regular
  * light extinction coefficients is not between 0 and 1.
  * @return Filename written.
  */
  const char* WriteXMLErrorFile2();

  /**
  * Writes a parameter file to direct error testing.  One of the snag
  * light extinction coefficients is not between 0 and 1.
  * @return Filename written.
  */
  const char* WriteXMLErrorFile3();



};
//---------------------------------------------------------------------------
#endif // TestLightOrg_H
