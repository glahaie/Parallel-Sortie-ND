//---------------------------------------------------------------------------
// TestGapLight
//---------------------------------------------------------------------------
#if !defined(TestGapLight_H)
  #define TestGapLight_H

#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>

class clGrid;
class clSimManager;

/**
* Tests the GapLight class.
*/
class clTestGapLight {

  public:

  /**
  * Performs testing.  Two runs are performed, identical but for the dimensions
  * of the grid cells.  For each, it starts with a known list of seedlings and
  * saplings for which light is to be tested.
  *
  * In each run, in the first timestep, there are no adult trees.  In the
  * timestep, there is a small list of adult trees.  In the last timestep,
  * there are adults in every cell.
  */
  void TestGapLight();

  protected:

  /**
  * Writes a parameter file.  This contains no grid information so that the
  * grid will default to 8 X 8 cells.
  *
  * @return Filename written.
  */
  const char* WriteXMLFile1();

  /**
  * Writes a parameter file.  This contains grid information so that the
  * grid will have 2 X 4 cells.
  *
  * @return Filename written.
  */
  const char* WriteXMLFile2();

};
//---------------------------------------------------------------------------
#endif // TestGapLight_H
