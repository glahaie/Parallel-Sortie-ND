//---------------------------------------------------------------------------
// TestAllometricGrowthIncrementer
//---------------------------------------------------------------------------
#if !defined(TestAllometricGrowthIncrementer_H)
  #define TestAllometricGrowthIncrementer_H

#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>

class clSimManager;

/**
* Tests the clAllometricGrowthIncrementer class. I'm also allowing this to form
* part of the test of clConstBAGrowth and clConstantRadialGrowth.  Ironically,
* since I wrote this, this is also now partly a test of clGrowthOrg, and
* TestGrowthOrg is partly a test of clGrowthHeightIncrementer, because I
* switched some functionality between classes.  But I am much too lazy to
* switch the test code too.  After all, it's all there, right?
*/
class clTestAllometricGrowthIncrementer : public CppUnit::TestFixture {

  public:

  /**
  * Rolls the test up into one function.
  */
  void TestAllometricGrowthIncrementer();

  protected:
    
  /**
  * Tests the clGrowthHeightIncrementer class when doing height incrementing.
  * WriteXMLFile1() is used to do setup. This creates four trees; two of the 
  * trees should have heights incremented to below the maximum tree canopy 
  * height, and two must be limited to the maximum tree canopy height. A 
  * timestep is run and the DBH and height are checked.
  * @param p_oSimManager Sim manager object for doing the run.
  */
  void TestNormalProcessingRun1(clSimManager *p_oSimManager);
  
  /**
   * Tests the clGrowthHeightIncrementer class when doing diameter incrementing.
   * WriteXMLFile2() is used to do setup. Six trees are created representing all
   * live life history stages. A timestep is run and the DBHs and heights are 
   * checked.
   * @param p_oSimManager Sim manager object for doing the run.
   */
  void TestNormalProcessingRun2(clSimManager *p_oSimManager);

  /**
  * Writes a parameter file to direct testing.  This contains two species, with
  * either constant basal area or constant radial growth assigned.
  *
  * @return Filename written.
  */
  const char* WriteXMLFile1();
  
  /**
  * Writes a parameter file for normal processing run 2.
  *
  * @return Filename written.
  */
  const char* WriteXMLFile2();
};
//---------------------------------------------------------------------------
#endif // TestAllometricGrowthIncrementer_H
