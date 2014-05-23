//---------------------------------------------------------------------------
#include "TestSimManager.h"

#include <fstream>
#include <xercesc/dom/DOMBuilder.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationRegistry.hpp>

//---------------------------------------------------------------------------

using namespace xercesc;
////////////////////////////////////////////////////////////////////////////
// TestDoSetup()
////////////////////////////////////////////////////////////////////////////
void clTestSimManager::TestDoSetup1() {

   clSimManager *p_oSimManager = new clSimManager(5,3, "");

   //Test the constructor
   CPPUNIT_ASSERT(p_oSimManager->GetMajorVersion() == 5);
   CPPUNIT_ASSERT(p_oSimManager->GetMinorVersion() == 3);

   //Prepare XML parsing tools
   //I must confess I don't exactly know what's going on here - I'm following
   //the Xerces examples
   XMLCh *sVal = XMLString::transcode("LS");
   DOMImplementation *p_oImpl=DOMImplementationRegistry::getDOMImplementation(sVal);
   DOMBuilder *p_oXMLParser = ((DOMImplementationLS*)p_oImpl)
             ->createDOMBuilder(DOMImplementationLS::MODE_SYNCHRONOUS, 0);
   DOMDocument *p_oDoc = p_oXMLParser->parseURI(WriteXMLFile1());
   XMLString::release(&sVal);

   //Now feed it to p_oSimManager and see if the right stuff comes back out
   p_oSimManager->DoSetup(p_oDoc);

   CPPUNIT_ASSERT(10 == p_oSimManager->GetNumberOfTimesteps());
   CPPUNIT_ASSERT(1 == p_oSimManager->GetCurrentTimestep());
   CPPUNIT_ASSERT(3 == p_oSimManager->GetNumberOfYearsPerTimestep());
   //Random seed sign should have switched from positive to negative
   long *p_iSeed = p_oSimManager->GetRandomSeed();
   CPPUNIT_ASSERT(-2 == (int)*p_iSeed);

   //Exception processing
   p_oDoc = p_oXMLParser->parseURI(WriteXMLErrorFile1());
   try {
     p_oSimManager->DoSetup(p_oDoc);
     //I don't know how to fail a test - so I'll make a false assertion
     CPPUNIT_ASSERT(1 == 0);
   } catch (modelErr& err) {
     ;
   }

   p_oDoc = p_oXMLParser->parseURI(WriteXMLErrorFile2());
   try {
     p_oSimManager->DoSetup(p_oDoc);
     //I don't know how to fail a test - so I'll make a false assertion
     CPPUNIT_ASSERT(1 == 0);
   } catch (modelErr& err) {
    ;
   }

   p_oDoc = p_oXMLParser->parseURI(WriteXMLErrorFile3());
   try {
     p_oSimManager->DoSetup(p_oDoc);
     //I don't know how to fail a test - so I'll make a false assertion
     CPPUNIT_ASSERT(1 == 0);
   } catch (modelErr& err) {
    ;
   }
   
   p_oXMLParser->release();

   delete p_oSimManager;
}
//---------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////
// TestDoSetup2()
////////////////////////////////////////////////////////////////////////////
void clTestSimManager::TestDoSetup2() {

   clSimManager *p_oSimManager = new clSimManager(5,3, "");

   //Prepare XML parsing tools
   //I must confess I don't exactly know what's going on here - I'm following
   //the Xerces examples
   XMLCh *sVal = XMLString::transcode("LS");
   DOMImplementation *p_oImpl=DOMImplementationRegistry::getDOMImplementation(sVal);
   DOMBuilder *p_oXMLParser = ((DOMImplementationLS*)p_oImpl)
             ->createDOMBuilder(DOMImplementationLS::MODE_SYNCHRONOUS, 0);
   DOMDocument *p_oDoc = p_oXMLParser->parseURI(WriteXMLFile2());
   XMLString::release(&sVal);

   //Now feed it to p_oSimManager and see if the right stuff comes back out
   p_oSimManager->DoSetup(p_oDoc);

   CPPUNIT_ASSERT(10 == p_oSimManager->GetNumberOfTimesteps());
   CPPUNIT_ASSERT(1 == p_oSimManager->GetCurrentTimestep());
   CPPUNIT_ASSERT(3 == p_oSimManager->GetNumberOfYearsPerTimestep());
   //Random seed should have been chosen negative
   long *p_iSeed = p_oSimManager->GetRandomSeed();
   CPPUNIT_ASSERT(*p_iSeed < 0);
   
   p_oXMLParser->release();

   delete p_oSimManager;
}
//---------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////
// TestDoSetup3()
////////////////////////////////////////////////////////////////////////////
void clTestSimManager::TestDoSetup3() {

  clSimManager *p_oSimManager = new clSimManager(5,3, "");

   //Prepare XML parsing tools
   //I must confess I don't exactly know what's going on here - I'm following
   //the Xerces examples
   XMLCh *sVal = XMLString::transcode("LS");
   DOMImplementation *p_oImpl=DOMImplementationRegistry::getDOMImplementation(sVal);
   DOMBuilder *p_oXMLParser = ((DOMImplementationLS*)p_oImpl)
             ->createDOMBuilder(DOMImplementationLS::MODE_SYNCHRONOUS, 0);
   DOMDocument *p_oDoc = p_oXMLParser->parseURI(WriteXMLFile3());
   XMLString::release(&sVal);

   //Now feed it to p_oSimManager and see if the right stuff comes back out
   p_oSimManager->DoSetup(p_oDoc);

   CPPUNIT_ASSERT(10 == p_oSimManager->GetNumberOfTimesteps());
   CPPUNIT_ASSERT(1 == p_oSimManager->GetCurrentTimestep());
   CPPUNIT_ASSERT(3 == p_oSimManager->GetNumberOfYearsPerTimestep());
   //Random seed should be as it is in the file
   long *p_iSeed = p_oSimManager->GetRandomSeed();
   CPPUNIT_ASSERT((int)*p_iSeed == -24);

   p_oXMLParser->release();

   delete p_oSimManager;
}
//---------------------------------------------------------------------------


////////////////////////////////////////////////////////////////////////////
//  WriteXMLFile1()
////////////////////////////////////////////////////////////////////////////
const char* clTestSimManager::WriteXMLFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>";
  oOut << "<paramFile fileCode=\"06010101\">";
  oOut << "<plot>";
  oOut << "<timesteps>10</timesteps>";
  oOut << "<currentTimestep>1</currentTimestep>";
  oOut << "<yearsPerTimestep>3</yearsPerTimestep>";
  oOut << "<randomSeed>2</randomSeed>";
  oOut << "</plot>";
  oOut << "</paramFile>";

  oOut.close();

  return cFileString;
}
//---------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////
//  WriteXMLFile2()
////////////////////////////////////////////////////////////////////////////
const char* clTestSimManager::WriteXMLFile2() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>";
  oOut << "<paramFile fileCode=\"06010101\">";
  oOut << "<plot>";
  oOut << "<timesteps>10</timesteps>";
  oOut << "<currentTimestep>1</currentTimestep>";
  oOut << "<yearsPerTimestep>3</yearsPerTimestep>";
  oOut << "<randomSeed>0</randomSeed>";
  oOut << "</plot>";
  oOut << "</paramFile>";

  oOut.close();

  return cFileString;
}
//---------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////
//  WriteXMLFile3()
////////////////////////////////////////////////////////////////////////////
const char* clTestSimManager::WriteXMLFile3() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>";
  oOut << "<paramFile fileCode=\"06010101\">";
  oOut << "<plot>";
  oOut << "<timesteps>10</timesteps>";
  oOut << "<currentTimestep>1</currentTimestep>";
  oOut << "<yearsPerTimestep>3</yearsPerTimestep>";
  oOut << "<randomSeed>-24</randomSeed>";
  oOut << "</plot>";
  oOut << "</paramFile>";

  oOut.close();

  return cFileString;
}
//---------------------------------------------------------------------------

/*///////////////////////////////////////////////////////////////////////////
  WriteXMLErrorFile1()
///////////////////////////////////////////////////////////////////////////*/
const char* clTestSimManager::WriteXMLErrorFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut(cFileString, ios::out | ios::trunc);

  //Write file
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>";
  oOut << "<paramFile fileCode=\"06010101\">";
  oOut << "<plot>";
  oOut << "<timesteps>-10</timesteps>";
  oOut << "<currentTimestep>1</currentTimestep>"
       << "<yearsPerTimestep>3</yearsPerTimestep>"
       << "<randomSeed>2</randomSeed>"
       << "</plot>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}
//---------------------------------------------------------------------------

/*///////////////////////////////////////////////////////////////////////////
  WriteXMLErrorFile2()
///////////////////////////////////////////////////////////////////////////*/
const char* clTestSimManager::WriteXMLErrorFile2() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut(cFileString, ios::out | ios::trunc);

  //Write file
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>10</timesteps>"
       << "<currentTimestep>11</currentTimestep>"
       << "<yearsPerTimestep>3</yearsPerTimestep>"
       << "<randomSeed>2</randomSeed>"
       << "</plot>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}
//---------------------------------------------------------------------------

/*///////////////////////////////////////////////////////////////////////////
  WriteXMLErrorFile3()
///////////////////////////////////////////////////////////////////////////*/
const char* clTestSimManager::WriteXMLErrorFile3() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut(cFileString, ios::out | ios::trunc);

  //Write file
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>10</timesteps>"
       << "<currentTimestep>1</currentTimestep>"
       << "<yearsPerTimestep>0</yearsPerTimestep>"
       << "<randomSeed>2</randomSeed>"
       << "</plot>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}
//---------------------------------------------------------------------------

