//---------------------------------------------------------------------------
// TestQuadratGLILight
//---------------------------------------------------------------------------
#if !defined(TestQuadratGLILight_H)
#define TestQuadratGLILight_H

#include <cppunit/TestFixture.h>
#include <fstream>

class clSimManager;

/**
 * Tests the class clQuadratGLILight.
 */
class clTestQuadratGLILight : public CppUnit::TestFixture {

public:

  /**
   * Rolls all other tests into a single function to call.
   */
  void TestQuadratGLILight();

protected:

  /**
   * Tests the setup for the "Quadrat GLI" grid.  Tests the following conditions:
   * <ol>
   * <li>The "Quadrat GLI" grid is correctly set up when there is no grid setup
   * information in the parameter file.  WriteXMLFile1() is used to create the
   * parameter file in question. "Quadrat GLI" should have an 8m X 8m
   * resolution.</li>
   * <li>The "Quadrat GLI" grid is correctly set up when there is grid setup
   * information in the parameter file.  WriteXMLFile2() is used to create the
   * parameter file in question. "Quadrat GLI" should have a 10m X 10m
   * resolution with no map values.
   * </li>
   * </ol>
   * @param p_oSimManager Sim manager for running tests.
   */
  void TestGridSetup(clSimManager *p_oSimManager);

  /**
   * Tests the setup for the parameters.  Tests the following conditions:
   * <ol>
   * <li>The Quadrat GLI behavior is the only light behavior in the list.
   * WriteXMLFile1() creates the parameter file.  The brightness array is
   * checked to make sure it has non-zero values.</li>
   * <li>The Quadrat GLI behavior and the GLI Light behavior are both in the
   * list, and the GLI Light behavior comes first (meaning the Quadrat GLI
   * behavior can borrow brightness array information from it).  WriteXMLFile2()
   * creates the parameter file.  The brightness array has non-zero values.
   * The Quadrat GLI has its correct settings for sky grids.</li>
   * <li>The GLI light behavior and the Quadrat GLI Light behavior are both in
   * the list, and the GLI Light behavior comes second (meaning the Quadrat GLI
   * behavior cannot borrow brightness array information from it).
   * WriteXMLFile3() creates the parameter file.  The brightness array has non-
   * zero values. The Quadrat GLI has its correct settings for sky grids.</li>
   * <li>The Quadrat GLI behavior and the GLI light behavior are both in the
   * list, the Quadrat GLI behavior comes second, and the light settings are
   * different. WriteXMLFile6() creates the parameter file.  The Quadrat GLI
   * grid is of the right size for its sky grids and contains non-zero
   * values.</li>
   * </ol>
   * @param p_oSimManager Sim manager for running tests.
   */
  void TestParameterSetup(clSimManager *p_oSimManager);

  /**
   * Makes sure Quadrat GLI processing is performed correctly. WriteXMLFile2()
   * does setup. Two "Quadrat GLI" grid cells, (0, 0) and (5, 5), have their
   * GLIs tested according to expected values from a spreadsheet. This verifies
   * that GLI is being correctly calculated. All other cell values should be -1.
   * @param p_oSimManager Sim manager for running tests.
   */
  void TestNormalProcessingRun1(clSimManager *p_oSimManager);

  /**
   * Makes sure Quadrat GLI processing is performed correctly. WriteXMLFile5()
   * does setup. This makes sure that every cell gets a GLI value when that
   * flag is set.
   * @param p_oSimManager Sim manager for running tests.
   */
  void TestNormalProcessingRun2(clSimManager *p_oSimManager);

  /**
   * Tests error processing.  Each of the error files is fed in to make sure
   * that clQuadratGLILight correctly throws an error.
   */
  void TestErrorProcessing(clSimManager *p_oSimManager);

  /**
   * Writes a parameter file to direct testing.
   * <ul>
   * <li>Two tree species</li>
   * <li>One behavior - Quadrat GLI</li>
   * </ul>
   * @return Filename written.
   */
  const char* WriteXMLFile1();

  /**
   * Writes a parameter file to direct testing.
   * <ul>
   * <li>Two tree species</li>
   * <li>Grid information for "Quadrat GLI" setting it to 10m by 10m with full
   * map information</li>
   * <li>First behavior - GLI Light</li>
   * <li>Second behavior - Quadrat GLI</li>
   * <li>Same sky grid information for Quadrat GLI Light and GLI Light - 12 alt
   * and 18 azi grids</li>
   * </ul>
   * @return Filename written.
   */
  const char* WriteXMLFile2();

  /**
   * Writes a parameter file to direct testing.
   * <ul>
   * <li>Two tree species</li>
   * <li>Tree densities - to provide canopy cover to calculate GLI against</li>
   * <li>First behavior - Quadrat GLI</li>
   * <li>Second behavior - Quadrat GLI Light</li>
   * <li>Same sky grid information for Quadrat GLI Light and GLI Map - 12 alt
   * and 18 azi grids</li>
   * <li>Both behaviors have their light heights set to 0 m</li>
   * <li>Quadrat GLI grid set to 8 X 8 cells so it will match GLI Map</li>
   * </ul>
   * @return Filename written.
   */
  const char* WriteXMLFile3();

  /**
   * Writes a parameter file to direct testing.
   * <ul>
   * <li>Two tree species</li>
   * <li>First behavior - GLI Light</li>
   * <li>Second behavior - GLI Map</li>
   * <li>Different sky grid information for GLI Light and GLI Map</li>
   * </ul>
   * @return Filename written.
   */
  const char* WriteXMLFile4();

  /**
   * Writes a parameter file to direct testing.
   * <ul>
   * <li>Two tree species</li>
   * <li>Tree densities - to provide canopy cover to calculate GLI against</li>
   * <li>Only behavior - Quadrat GLI</li>
   * <li>Quadrat GLI forced to calculate every cell</li>
   * </ul>
   * @return Filename written.
   */
  const char* WriteXMLFile5();

  /**
   * Writes a parameter file to direct error testing.  The number of azimuth
   * grids for Quadrat GLI is less than or equal to 0.
   * @return Filename written.
   */
  const char* WriteXMLErrorFile1();

  /**
   * Writes a parameter file to direct error testing.  The number of altitude
   * grids for Quadrat GLI is less than or equal to 0.
   * @return Filename written.
   */
  const char* WriteXMLErrorFile2();

  /**
   * Writes a parameter file to direct error testing.  The height of the GLI
   * photo is less than 0.
   * @return Filename written.
   */
  const char* WriteXMLErrorFile3();

  /**
   * Writes common portions of the test parameter files (tree pop, plot, etc).
   * @param oOut File stream to write to.
   */
  void WriteCommonStuff(std::fstream &oOut);

};
//---------------------------------------------------------------------------
#endif // TestGLIMap_H
