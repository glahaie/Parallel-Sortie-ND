//---------------------------------------------------------------------------
// TestGrids
//---------------------------------------------------------------------------
#if !defined(TestGrids_H)
  #define TestGrids_H

#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>

class clGrid;
class clSimManager;

/**
* Tests grids.
*/
class clTestGrids : public CppUnit::TestFixture {

  public:

  /**
  * Comprehensive tester.
  */
  void TestGrids();

  protected:

  /**
  * Tests the GetAverage methods.
  * @param p_oGrid Grid to test.
  */
  void TestGetAverage(clGrid *p_oGrid);

  /**
  * Tests to make sure that the grid cell coordinate calculation methods work.
  * This feeds in one number, 13, to both start and end for X and Y.
  */
  void TestGetCoordinates(clGrid *p_oGrid);

  /**
   Creates a grid and initializes it with values.  The two data members are
   called "int" and "float".  The grid cell size is 4X6.
   @param p_oSimManager Sim manager.
   @return Created, initialized grid.
  */
  clGrid* CreateGrid(clSimManager *p_oSimManager);

  /**
  * Writes an XML file that will create the sim manager so we can create a
  * grid through the proper channels.  The plot size is 200X200 m.
  * @return Filename just written.
  */
  const char* WriteXMLFile1();

};
//---------------------------------------------------------------------------
#endif // TestGrids_H
