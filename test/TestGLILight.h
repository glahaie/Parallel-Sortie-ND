//---------------------------------------------------------------------------

#ifndef TestGLILightH
#define TestGLILightH

#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>

class clTreePopulation;
class clSimManager;

/**
 * This class tests the GLILight class.
 */
class clTestGLILight : public CppUnit::TestFixture {

public:

  /**
  * Puts the tests together into one.
  */
  void TestGLILight();

  private:

  /**For testing the values in tree records*/
  struct fakeRecord {
    float fX, /**<X value*/
          fY, /**<Y value*/
          fLight; /**<Expected GLI*/
    bool bRead; /**<whether or not this has been read*/
    };

  /**
  * Tests GLI calculations.  WriteXMLFile1() is used for setup.  Seventeen
  * trees are created, and the GLI calculations of six of them are tested to
  * make sure they are right.  There is only one species, for simplicity.
  * @param p_oSimManager Object to run a test with.
  */
  void Run1(clSimManager *p_oSimManager);

  /**
  * Tests GLI calculations.  WriteXMLFile2() is used for setup.  Five
  * trees are created, and the GLI calculations of two of them are tested to
  * make sure they are right.  This tests mid-crown calculations.  There is
  * only one species, for simplicity.
  * @param p_oSimManager Object to run a test with.
  */
  void Run2(clSimManager *p_oSimManager);

  /**
  * Tests GLI calculations in the southern hemisphere. WriteXMLFile3() is used
  * for setup.  Seventeen trees are created, and the GLI calculations of six of
  * them are tested to make sure they are right.  There is only one species,
  * for simplicity.
  * @param p_oSimManager Object to run a test with.
  */
  void Run3(clSimManager *p_oSimManager);

  /**
  * This tests error processing during setup.  The only error currently trapped
  * for is that the number of years per timestep is less than 1.
  * @param p_oSimManager Object to run a test with.
  */
  void TestDoSetupErrorProcessing(clSimManager *p_oSimManager);

  /**
  * Writes a parameter file to direct testing for GLI light assignments.
  * @return Filename written.
  */
  const char* WriteXMLFile1();

  /**
  * Writes a parameter file to direct testing for GLI light assignments.
  * @return Filename written.
  */
  const char* WriteXMLFile2();

  /**
  * Writes a parameter file to direct testing for GLI light assignments.
  * @return Filename written.
  */
  const char* WriteXMLFile3();

  /**
  * Writes a parameter file with a deliberate error.  The number of years per
  * timestep is less than 1, which should cause light to throw an error.
  * @return Filename written.
  */
  const char* WriteXMLErrorFile1();
};
//---------------------------------------------------------------------------
#endif
