//---------------------------------------------------------------------------
// TestTree
//---------------------------------------------------------------------------
#if !defined(TestTree_H)
  #define TestTree_H

#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>

class clSimManager;


/**
 * Tests the clTree class.
 */
class clTestTree : public CppUnit::TestFixture
{
  public:

  /**
  * Groups together all the tree testing functions into a comprehensive test.
  */
  void TestTree();

  protected:

  /**
  * Verifies that allometry is updated correctly.  (This is really more of
  * a test of a clTreePopulation function, but that test unit is getting
  * awfully crowded.)  WriteXMLFile1() is used to create a run.  A seedling,
  * a sapling, and an adult are created, and then height and diameter are
  * changed both with the allometry to be updated and without.  This also
  * tests transitions between the life history stages.
  */
  void TestAllometryUpdating(clSimManager *p_oSimManager);

  /**
   * Tests the cloning function.
   * @param p_oSimManager
   */
  void TestClone(clSimManager *p_oSimManager);

  /**
  * Writes a parameter file to test trees.  Two species are used; the only
  * difference between the two is the maximum seedling height.
  * @return Filename written.
  */
  const char* WriteXMLFile1();

  /**
  * Writes a parameter file to test trees. This provides lots of tree data
  * members.
  * @return Filename written.
  */
  const char* WriteXMLFile2();

};
//---------------------------------------------------------------------------
#endif // TestTree_H
