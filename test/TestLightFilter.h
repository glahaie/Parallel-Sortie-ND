//---------------------------------------------------------------------------

#ifndef TestLightFilterH
#define TestLightFilterH

#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>

class clTreePopulation;
class clSimManager;

/**
  This class tests the light filter behavior.  It writes out parameter files
  and uses them as input to perform setup; it then sets up the desired initial
  conditions, causes the light filter behavior to run, then tests its output.
*/
class clTestLightFilter : public CppUnit::TestFixture {

public:

/**
  Tests light filtering.  It will cause a parameter file to be written,
  and then passed to a clSimManager object.  This object will read it.
  The trees will be retrieved and assigned GLIs, and then light filter is
  run and the data validated.
*/
void TestLightFiltering();

/**
  Creates a test suite of all the test cases in this object.  I'm putting
  it here so it will be easier to see and add new cases to.

  @return The test suite.
*/


private:

/**
* Verifies the values after WriteXMLFile1 has been executed.
*
* @param p_oPop Tree population.
*/
  void VerifyXMLFile1(clTreePopulation *p_oPop);

  /**
  * Sets the initial conditions for each tree prior to running the light filter
  * behavior.  This assumes the trees have already been created.  Each tree
  * will have its "Z" and "Light" value set according to the test script.
  *
  * @param p_oPop Tree population.
  */
  void SetTreeValues(clTreePopulation *p_oPop);

  /**
    Writes a parameter file to direct testing.  This contains all tree
    information and light filter information, and a behavior list that
    includes quadratlight (for correct registration of "lgm" tree data member)
    and the light filter behavior.  It also has a tree map so we'll be dealing
    with a known list of trees.

    @return Filename written.
  */
  const char* WriteXMLFile1();

  /**
  * Writes a file designed to produce an error in setup.  The error is that
  * there is not a light behavior assigned to all species/types that use
  * light filtering.
  */
  const char* WriteXMLErrorFile1();
};
//---------------------------------------------------------------------------
#endif
