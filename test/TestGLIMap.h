//---------------------------------------------------------------------------
// TestGLIMap
//---------------------------------------------------------------------------
#if !defined(TestGLIMap_H)
  #define TestGLIMap_H

#include <cppunit/TestFixture.h>
#include <fstream>

class clSimManager;

/**
* Tests the class clGLIMap.
*
* <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
* TO DO:  Prepare a couple of GLI points for an 8 by 8 grid to test GLI when
* the GLI Map behavior is the only one in the run.  Then add them to
* TestNormalProcessing.
* <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
*/
class clTestGLIMap : public CppUnit::TestFixture {

  public:

  /**
  * Rolls all other tests into a single function to call.
  */
  void TestGLIMap();

  protected:

  /**
  * Tests the setup for the "GLI Map" grid.  Tests the following conditions:
  * <ol>
  * <li>The "GLI Map" grid is correctly set up when there is no grid setup
  * information in the parameter file.  WriteXMLFile1() is used to create the
  * parameter file in question.  "GLI Map" should have an 8m X 8m
  * resolution.</li>
  * <li>The "GLI Map" grid is correctly set up when there is grid setup
  * information in the parameter file.  WriteXMLFile2() is used to create the
  * parameter file in question.  "GLI Map" should have a 10m X 10m resolution
  * with no map values.
  * </li>
  * </ol>
  */
  void TestGridSetup(clSimManager *p_oSimManager);

  /**
  * Tests the setup for the parameters.  Tests the following conditions:
  * <ol>
  * <li>The GLI Map behavior is the only light behavior in the list.
  * WriteXMLFile1() creates the parameter file.  The brightness array is
  * checked to make sure it has non-zero values.</li>
  * <li>The GLI Map behavior and the Quadrat GLI Light behavior are both in the
  * list, and the Quadrat GLI Light behavior comes first (meaning the GLI Map
  * behavior can borrow brightness array information from it).  WriteXMLFile2()
  * creates the parameter file.  The brightness array has non-zero values.
  * The GLI Map has its correct settings for sky grids.</li>
  * <li>The GLI Map behavior and the Quadrat GLI Light behavior are both in the
  * list, and the Quadrat GLI Light behavior comes second (meaning the GLI Map
  * behavior cannot borrow brightness array information from it).
  * WriteXMLFile3() creates the parameter file.  The brightness array has non-
  * zero values. The GLI Map has its correct settings for sky grids.</li>
  * <li>The GLI Map behavior and the GLI Light behavior are both in the list,
  * and the GLI Light behavior comes first (meaning the GLI Map behavior can
  * borrow brightness array information from it).  WriteXMLFile4() creates the
  * parameter file.  The brightness array has non-zero values. The GLI Map has
  * its correct settings for sky grids.</li>
  * <li>The GLI Map behavior and the GLI Light behavior are both in the list,
  * and the GLI Light behavior comes second (meaning the GLI Map behavior
  * cannot borrow brightness array information from it).  WriteXMLFile5()
  * creates the parameter file.  The brightness array has non-zero values. The
  * GLI Map has its correct settings for sky grids.</li>
  * <li>The GLI Map behavior and the GLI light behavior are both in the list,
  * the GLI Map behavior comes second, and the light settings are different.
  * WriteXMLFile6() creates the parameter file.  The GLI Map behavior is of the
  * right size for its sky grids and contains non-zero values.
  * </ol>
  */
  void TestParameterSetup(clSimManager *p_oSimManager);

  /**
  * Makes sure the GLI map is created correctly.
  * <ul>
  * <li>Run 1: WriteXMLFile2() does setup.  A seedling is placed in every grid
  * cell (to force clQuadratGLILight to perform a GLI calculation for all grid
  * cells).  Two "GLI Map" grid cells, (0, 0) and (5, 5), have their GLIs
  * tested according to expected values from a spreadsheet. This verifies that
  * GLI is being calculated.  Then the "GLI Map" and Quadrat GLI grids are
  * compared cell by cell to make sure their values are the same.</li>
  * <li>Run 2: WriteXMLFile3() does setup.  A seedling is placed in every grid
  * cell (to force clQuadratGLILight to perform a GLI calculation for all grid
  * cells).  The "GLI Map" and Quadrat GLI grids are compared cell by cell to
  * make sure their values are the same.  This makes sure that processing takes
  * place correctly when GLI Map is the first light behavior.</li>
  * <li>Run 3:  WriteXMLFile1() does setup.  Two "GLI Map" grid cells
  * have their GLIs tested according to expected values from a spreadsheet.
  * This verifies that GLI is being calculated correctly when there are no
  * other light behaviors.
  * </ul>
  */
  void TestNormalProcessing(clSimManager *p_oSimManager);

  /**
  * Tests error processing.  Each of the error files is fed in to make sure
  * that clGLIMap correctly throws an error.
  */
  void TestErrorProcessing(clSimManager *p_oSimManager);

  /**
  * Writes a parameter file to direct testing.
  * <ul>
  * <li>One tree species</li>
  * <li>One behavior - GLI Map</li>
  * </ul>
  * @return Filename written.
  */
  const char* WriteXMLFile1();

  /**
  * Writes a parameter file to direct testing.
  * <ul>
  * <li>One tree species</li>
  * <li>Grid information for "GLI Map" setting it to 10m by 10m with full map
  * information</li>
  * <li>Quadrat GLI grid is also set to 10m by 10m<li>
  * <li>First behavior - Quadrat GLI Light</li>
  * <li>Second behavior - GLI Map</li>
  * <li>Same sky grid information for Quadrat GLI Light and GLI Map - 12 alt
  * and 18 azi grids</li>
  * <li>Both behaviors have their light heights set to 2 m</li>
  * </ul>
  * @return Filename written.
  */
  const char* WriteXMLFile2();

  /**
  * Writes a parameter file to direct testing.
  * <ul>
  * <li>One tree species</li>
  * <li>Tree densities - to provide canopy cover to calculate GLI against</li>
  * <li>First behavior - GLI Map</li>
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
  * <li>One tree species</li>
  * <li>First behavior - GLI Light</li>
  * <li>Second behavior - GLI Map</li>
  * <li>Same sky grid information for GLI Light and GLI Map</li>
  * </ul>
  * @return Filename written.
  */
  const char* WriteXMLFile4();

  /**
  * Writes a parameter file to direct testing.
  * <ul>
  * <li>One tree species</li>
  * <li>First behavior - GLI Map</li>
  * <li>Second behavior - GLI Light</li>
  * <li>Same sky grid information for GLI Light and GLI Map</li>
  * </ul>
  * @return Filename written.
  */
  const char* WriteXMLFile5();

  /**
  * Writes a parameter file to direct testing.
  * <ul>
  * <li>One tree species</li>
  * <li>First behavior - GLI Light</li>
  * <li>Second behavior - GLI Map</li>
  * <li>Different sky grid information for GLI Light and GLI Map</li>
  * </ul>
  * @return Filename written.
  */
  const char* WriteXMLFile6();

  /**
  * Writes a parameter file to direct error testing.  The number of azimuth
  * grids for GLI Map is less than or equal to 0.
  * @return Filename written.
  */
  const char* WriteXMLErrorFile1();

  /**
  * Writes a parameter file to direct error testing.  The number of altitude
  * grids for GLI Map is less than or equal to 0.
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
