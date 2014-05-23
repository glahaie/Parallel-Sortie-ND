//---------------------------------------------------------------------------
// TestSailLight
//---------------------------------------------------------------------------
#if !defined(TestSailLight_H)
  #define TestSailLight_H

#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>

class clSimManager;

/**
* Tests the clSailLight class (currently not completely).
*/
class clTestSailLight : public CppUnit::TestFixture {

  public:

  /**
  * Gathers all testing into one function.
  */
  void TestSailLight();

  protected:

  /**
  * Tests light extinction coefficient management by taking a target tree and
  * surrounding it with both live and snag neighbors to see if the amount of
  * shade calculated by sail light comes out right.  WriteXMLFile1() is used
  * to set up the run.  A single sapling of species 1 is created, along with
  * four neighbors.  Then sail light is run and the resulting shade is compared
  * to expected.
  *
  * This run uses top-of-crown fisheye.
  */
  void Run1(clSimManager *p_oSimManager);

  /**
  * Tests light extinction coefficient management by taking 2 target trees and
  * surrounding them with neighbors to see if the amount of shade calculated by
  * sail light comes out right.  WriteXMLFile2() is used to set up the run.
  *
  * This run uses mid-crown fisheye (with a seedling to make sure it still gets
  * top-of-crown), and differing crown radius equations for saplings and
  * adults.
  */
  void Run2(clSimManager *p_oSimManager);

  /**
  * Writes a parameter file to direct testing.  Timestep length is 1 year.
  * This contains one species.
  * Sail light is applied to Species 1 saplings.
  * @return Filename written.
  */
  const char* WriteXMLFile1();

  /**
  * Writes a parameter file to direct testing.  Timestep length is 1 year.
  * This contains one species.
  * Sail light is applied to Species 1 saplings and seedlings.
  * @return Filename written.
  */
  const char* WriteXMLFile2();
};
//---------------------------------------------------------------------------
#endif // TestSailLight_H
