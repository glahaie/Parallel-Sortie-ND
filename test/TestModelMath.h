//---------------------------------------------------------------------------
// TestModelMath
//---------------------------------------------------------------------------
#if !defined(TestModelMath_H)
  #define TestModelMath_H

#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>

class clModelMath;

/**
* Tests the clModelMath class.
*/
class clTestModelMath : public CppUnit::TestFixture {
  public:

  /**
  * Tests the various math functions.
  */
  void TestMath();

  protected:

  /**
  * Tests the functions.  This is all rolled together because I copied over
  * legacy testing code.  As I add new functions I will not include them here.
  */
  void TestFunctions();

  /**
  * Tests the random number generator.
  */
  void TestRandom();

  /**
  * Tests the function AddBarkToDBH().  Test conditions:
  * <ul>
  * <li>DIB is less than 0.<li>
  * <li>DIB equals 0.<li>
  * <li>DIB is a very small value.<li>
  * <li>DIB is a normal value (between 0 and 100).<li>
  * <li>DIB is a very large value.<li>
  * <li>DIB is a value large enough to cause float overflow
  * (threshold 1E18).<li>
  * </ul>
  */
  void TestAddBarkToDBH();

};
//---------------------------------------------------------------------------
#endif // TestMathLib_H
