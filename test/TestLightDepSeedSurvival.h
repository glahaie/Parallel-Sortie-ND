//---------------------------------------------------------------------------
// TestLightDepSeedSurvival
//---------------------------------------------------------------------------
#if !defined(TestLightDepSeedSurvival_H)
  #define TestLightDepSeedSurvival_H

#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>

class clSimManager;

/**
* Tests the clLightDepSeedSurvival class.
*/
class clTestLightDepSeedSurvival : public CppUnit::TestFixture {

  public:

  /**
  * Tests the clLightDepSeedSurvival class.
  */
  void TestLightDepSeedSurvival();

  protected:

  /**
  * This tests normal processing when the clLightDepSeedSurvival class
  * calculates GLI.  This performs DoNormalGLIRun1() and
  * DoNormalGLIRun2().
  * @param p_oSimManager Sim Manager object.
  */
  void TestNormalGLIProcessing(clSimManager *p_oSimManager);

  /**
  * This tests normal processing when the clLightDepSeedSurvival class
  * gets GLI from Storm Light.
  * @param p_oSimManager Sim Manager object.
  */
  void TestNormalStormLightProcessing(clSimManager *p_oSimManager);

  /**
  * Tests error processing.  It checks for the following errors:
  * <ul>
  * <li>Any of the light extinction coefficient values are not between 0 and 1.</li>
  * <li>The value for m_fLightHeight is not zero or greater</li>
  * <li>The value for mp_fOptimumGLI is not between 0 and 100.</li>
  * <li>There is no disperse behavior enabled.</li>
  * <li>The behavior is supposed to get GLI from Storm Light but Storm Light
  * isn't present.</li>
  * </ul>
  */
  void TestErrorProcessing(clSimManager *p_oSimManager);

  /**
  * This tests normal processing when the clLightDepSeedSurvival class
  * calculates GLI.  This run has storm damage and no snags.
  *
  * A plot is set up and a set of trees added
  * designed to give target GLI values to certain "Dispersed Seed" grid cells.
  * Mostly there is only one neighbor, and the trees are placed such that the
  * GLI point is completely within their canopies, to make test calculations
  * easy.  (GLI calculations themselves don't need testing here.)  A given
  * number of seeds of species 2, 3, and 4 is added to each of 9 grid cells.
  * The run goes, and then we check that the appropriate number of seedlings
  * of each species in each cell exists.  WriteXMLFile1() writes the parameter
  * file.
  * @param p_oSimManager Sim Manager object.
  */
  void DoNormalGLIRun1(clSimManager *p_oSimManager);

  /**
  * This tests normal processing when the clLightDepSeedSurvival class
  * calculates GLI.  This run has no storm damage but has snags.
  *
  * A plot is set up and a set of trees added
  * designed to give target GLI values to certain "Dispersed Seed" grid cells.
  * Mostly there is only one neighbor, and the trees are placed such that the
  * GLI point is completely within their canopies, to make test calculations
  * easy.  (GLI calculations themselves don't need testing here.)  A given
  * number of seeds of species 2, 3, and 4 is added to each of 9 grid cells.
  * The run goes, and then we check that the appropriate number of seedlings
  * of each species in each cell exists.  WriteXMLFile2() writes the parameter
  * file.
  * @param p_oSimManager Sim Manager object.
  */
  void DoNormalGLIRun2(clSimManager *p_oSimManager);

  /**
  * Writes the setup file for DoNormalGLIRun1().  This contains 5 species, one
  * unused (species 1; this helps catch array-index problems).  Non-spatial
  * disperse is applied to adults of all species, with values such that no
  * seeds will be dispersed from any trees.  Species 2-4 get light-dependent
  * seed survival. Species 2-4 get storm damage.
  *
  * @return Filename written.
  */
  const char* WriteXMLFile1();

  /**
  * Writes the setup file for DoNormalGLIRun2().  This contains 5 species, one
  * unused (species 1; this helps catch array-index problems).  Non-spatial
  * disperse is applied to adults of all species, with values such that no
  * seeds will be dispersed from any trees.  Species 2-4 get light-dependent
  * seed survival. Species 2-4 get Weibull snag mortality.
  *
  * @return Filename written.
  */
  const char* WriteXMLFile2();

  /**
  * Writes the setup file for DoNormalStormLightProcessing().  This contains 5
  * species, one unused (species 1; this helps catch array-index problems).
  * Non-spatial disperse is applied to adults of all species, with values such
  * that no seeds will be dispersed from any trees.  Species 2-4 get
  * storm-light-dependent seed survival.
  *
  * @return Filename written.
  */
  const char* WriteXMLFile3();

  /**
  * Writes a file where a light extinction coefficient is not between 0 and 1.
  * @return Filename written.
  */
  const char* WriteXMLErrorFile1();

  /**
  * Writes a file where the value for m_fLightHeight is not zero or greater.
  * @return Filename written.
  */
  const char* WriteXMLErrorFile2();

  /**
  * Writes a file where the value for mp_fOptimumGLI is not between 0 and 100.
  * @return Filename written.
  */
  const char* WriteXMLErrorFile3();

  /**
  * Writes a file where there is no disperse behavior.
  * @return Filename written.
  */
  const char* WriteXMLErrorFile4();

 /**
  * Writes a file where the number of altitude angles is less than 1.
  * @return Filename written.
  */
  const char* WriteXMLErrorFile5();

  /**
  * Writes a file where the number of azimuth angles is less than 1.
  * @return Filename written.
  */
  const char* WriteXMLErrorFile6();

  /**
  * Writes a file that has Storm Light Dependent Seed Survival but does not
  * have storm light.
  * @return Filename written.
  */
  const char* WriteXMLErrorFile7();


  /**
  * Writes common portions of the test parameter files (tree pop, plot, etc).
  * Ends with &lt;/trees&gt.
  * @param oOut File stream to write to.
  */
  void WriteCommonStuff(std::fstream &oOut);


};
//---------------------------------------------------------------------------
#endif // TestPuertoRicoEstablishment_H
