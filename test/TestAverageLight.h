//---------------------------------------------------------------------------
// TestAverageLight
//---------------------------------------------------------------------------
#if !defined(TestAverageLight_H)
#define TestAverageLight_H

#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>

class clSimManager;

/**
* Tests the clAverageLight class.
*/
class clTestAverageLight : public CppUnit::TestFixture
{

  public:

  /**
  * Rolls together all the tests into one function.
  */
  void TestAverageLight();

  private:

  /**
  * Tests normal processing - run 1.  This checks the calculation of mean GLI
  * and verifies that new light level calculations are triggered correctly.
  * WriteXMLFile1() does setup.
  * @param p_oSimManager Sim Manager to do runs.
  */
  void NormalProcessingRun1(clSimManager *p_oSimManager);

  /**
  * Tests normal processing - run 2.  This ensures that the calculation of mean
  * GLI happens when there are no trees affecting GLI.  WriteXMLFile2() does 
  * setup.
  * @param p_oSimManager Sim Manager to do runs.
  */
  void NormalProcessingRun2(clSimManager *p_oSimManager);
  
  /**
  * Tests normal processing - run 3.  This checks the calculation of mean GLI
  * when the grid cells are even multiples of the GLI map.
  * WriteXMLFile3() does setup.
  * @param p_oSimManager Sim Manager to do runs.
  */
  void NormalProcessingRun3(clSimManager *p_oSimManager);
  
  /**
  * Tests normal processing - run 4.  This checks the calculation of mean GLI
  * when the grid cells are not even multiples of the GLI map.
  * WriteXMLFile4() does setup.
  * @param p_oSimManager Sim Manager to do runs.
  */
  void NormalProcessingRun4(clSimManager *p_oSimManager);
  
  /**
  * Tests normal processing - run 5.  This checks the calculation of mean GLI
  * when the grid cell sizes are not specified.
  * WriteXMLFile5() does setup.
  * @param p_oSimManager Sim Manager to do runs.
  */
  void NormalProcessingRun5(clSimManager *p_oSimManager);

  /**
  * Tests error processing.
  * @param p_oSimManager Sim Manager to do runs.
  */
  void TestErrorProcessing(clSimManager *p_oSimManager);


  /**
  * Writes a parameter file for normal proceessing run 1.
  * @return Filename written.
  */
  const char* WriteXMLFile1();

  /**
  * Writes a parameter file for normal proceessing run 2.
  * @return Filename written.
  */
  const char* WriteXMLFile2();
  
  /**
  * Writes a parameter file for normal proceessing run 3.
  * @return Filename written.
  */
  const char* WriteXMLFile3();
  
  /**
  * Writes a parameter file for normal proceessing run 4.
  * @return Filename written.
  */
  const char* WriteXMLFile4();
  
  /**
  * Writes a parameter file for normal proceessing run 5.
  * @return Filename written.
  */
  const char* WriteXMLFile5();

  /**
  * Writes an error file where the GLI Map behavior is not enabled.
  * @return File name of the freshly written parameter file.
  */
  const char* WriteXMLErrorFile1();
  
  /**
  * Writes tree file.
  * @param oOut File stream to write to.
  */
  void WriteTreeFile(std::fstream &oOut); 
};
//---------------------------------------------------------------------------
#endif // TestAverageLight_H
