
// TestOutput.cpp
//---------------------------------------------------------------------------
#include "TestOutput.h"
#include "SimManager.h"
#include "Output.h"
#include "PlatformFuncs.h"
#include "XercesClasses.h"
//#include "Windows.h"
#include "DataTypes.h"
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <math.h>
#include <iostream>
#include <xercesc/dom/DOMBuilder.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/dom/DOM.hpp>

/////////////////////////////////////////////////////////////////////////////
// TestOutput()
/////////////////////////////////////////////////////////////////////////////
void clTestOutput::TestOutput() {
  clSimManager *p_oSimManager = new clSimManager(3, 3, "");

  NormalProcessingRun1(p_oSimManager);
  NormalProcessingRun3(p_oSimManager);
  NormalProcessingRun4(p_oSimManager);
  NormalProcessingRun5(p_oSimManager);
  NormalProcessingRun6(p_oSimManager);
  NormalProcessingRun7(p_oSimManager);
  TestFilePresence(p_oSimManager);


  delete p_oSimManager;
}

/////////////////////////////////////////////////////////////////////////////
// NormalProcessingRun1()
/////////////////////////////////////////////////////////////////////////////
void clTestOutput::NormalProcessingRun1(clSimManager *p_oSimManager) {

/*  p_oSimManager->ReadFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Detailed Output Run 1.xml");
  p_oSimManager->RunSim();

  string sArgs = " -xf \"C:/Code/Core_Model_Tester/Output_Test_Materials/SORTIE 1.gz.tar\" -C \"Output_Test_Materials\"";
  LaunchProcess("c:/code/core_model_tester/tar.exe", sArgs, "c:/code/core_model_tester");
  sArgs = " -dqf \"C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/SORTIE 1_0.xml.gz\"";
  LaunchProcess("c:/code/core_model_tester/gzip.exe", sArgs, "c:/code/core_model_tester");
  sArgs = " -dqf \"C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/SORTIE 1_1.xml.gz\"";
  LaunchProcess("c:/code/core_model_tester/gzip.exe", sArgs, "c:/code/core_model_tester");
  sArgs = " -dqf \"C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/SORTIE 1_2.xml.gz\"";
  LaunchProcess("c:/code/core_model_tester/gzip.exe", sArgs, "c:/code/core_model_tester");
  sArgs = " -dqf \"C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/SORTIE 1_3.xml.gz\"";
  LaunchProcess("c:/code/core_model_tester/gzip.exe", sArgs, "c:/code/core_model_tester");
  sArgs = " -dqf \"C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/SORTIE 1_4.xml.gz\"";
  LaunchProcess("c:/code/core_model_tester/gzip.exe", sArgs, "c:/code/core_model_tester");

  //Prepare XML parsing tools
  XMLPlatformUtils::Initialize();
  XMLCh *sVal = XMLString::transcode( "LS" );
  DOMImplementation * p_oImpl = DOMImplementationRegistry::getDOMImplementation( sVal );
  xercesc::DOMBuilder *p_oXMLParser = ( ( DOMImplementationLS * ) p_oImpl )->createDOMBuilder( DOMImplementationLS::MODE_SYNCHRONOUS, 0 );
  clXercesErrorHandler *p_oXMLErrorHandler = new clXercesErrorHandler;
  p_oXMLParser->setErrorHandler( p_oXMLErrorHandler );
  XMLString::release(&sVal);

  //Initial conditions
  DOMDocument *p_oDoc = p_oXMLParser->parseURI("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/SORTIE 1_0.xml" );
  sVal = XMLString::transcode( "tree" );
  DOMNodeList * p_oTrees = p_oDoc->getElementsByTagName( sVal );
  int iNumSettings = p_oTrees->getLength();
  CPPUNIT_ASSERT(iNumSettings == 175);

  //TS 1
  p_oDoc = p_oXMLParser->parseURI("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/SORTIE 1_1.xml" );
  p_oTrees = p_oDoc->getElementsByTagName( sVal );
  iNumSettings = p_oTrees->getLength();
  CPPUNIT_ASSERT(iNumSettings == 2);

  //TS 2
  p_oDoc = p_oXMLParser->parseURI("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/SORTIE 1_2.xml" );
  p_oTrees = p_oDoc->getElementsByTagName( sVal );
  iNumSettings = p_oTrees->getLength();
  CPPUNIT_ASSERT(iNumSettings == 127);

  //TS 3
  p_oDoc = p_oXMLParser->parseURI("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/SORTIE 1_3.xml" );
  p_oTrees = p_oDoc->getElementsByTagName( sVal );
  iNumSettings = p_oTrees->getLength();
  CPPUNIT_ASSERT(iNumSettings == 2);

  //TS 4
  p_oDoc = p_oXMLParser->parseURI("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/SORTIE 1_4.xml" );
  p_oTrees = p_oDoc->getElementsByTagName( sVal );
  iNumSettings = p_oTrees->getLength();
  CPPUNIT_ASSERT(iNumSettings == 175);

  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/SORTIE 1_0.xml");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/SORTIE 1_1.xml");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/SORTIE 1_2.xml");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/SORTIE 1_3.xml");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/SORTIE 1_4.xml");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/SORTIE 1.xml.gz");
  RemoveDirectory("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/");
  RemoveDirectory("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/");
  RemoveDirectory("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/SORTIE 1.gz.tar");

  XMLString::release(&sVal);
  p_oXMLParser->release();
  delete p_oXMLErrorHandler; p_oXMLErrorHandler = NULL;
  XMLPlatformUtils::Terminate();
*/
}

/////////////////////////////////////////////////////////////////////////////
// NormalProcessingRun3()
/////////////////////////////////////////////////////////////////////////////
void clTestOutput::NormalProcessingRun3(clSimManager *p_oSimManager) {

  /*p_oSimManager->ReadFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Detailed Output Run 3.xml");
  p_oSimManager->RunSim();

  string sArgs = " -xf \"C:/Code/Core_Model_Tester/Output_Test_Materials/Run 3.gz.tar\" -C \"Output_Test_Materials\"";
  LaunchProcess("c:/code/core_model_tester/tar.exe", sArgs, "c:/code/core_model_tester");
  sArgs = " -xf \"C:/Code/Core_Model_Tester/Output_Test_Materials/Run 3_run 3 subplot 1.gz.tar\" -C \"Output_Test_Materials\"";
  LaunchProcess("c:/code/core_model_tester/tar.exe", sArgs, "c:/code/core_model_tester");

  sArgs = " -dqf \"C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/Run 3_0.xml.gz\"";
  LaunchProcess("c:/code/core_model_tester/gzip.exe", sArgs, "c:/code/core_model_tester");
  sArgs = " -dqf \"C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/Run 3_run 3 subplot 1_0.xml.gz\"";
  LaunchProcess("c:/code/core_model_tester/gzip.exe", sArgs, "c:/code/core_model_tester");


  //Prepare XML parsing tools
  XMLPlatformUtils::Initialize();
  XMLCh *sVal = XMLString::transcode( "LS" );
  DOMImplementation * p_oImpl = DOMImplementationRegistry::getDOMImplementation( sVal );
  xercesc::DOMBuilder *p_oXMLParser = ( ( DOMImplementationLS * ) p_oImpl )->createDOMBuilder( DOMImplementationLS::MODE_SYNCHRONOUS, 0 );
  clXercesErrorHandler *p_oXMLErrorHandler = new clXercesErrorHandler;
  p_oXMLParser->setErrorHandler( p_oXMLErrorHandler );
  XMLString::release(&sVal);

  //Initial conditions
  DOMDocument *p_oDoc = p_oXMLParser->parseURI("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/Run 3_0.xml" );
  sVal = XMLString::transcode( "tree" );
  DOMNodeList * p_oTrees = p_oDoc->getElementsByTagName( sVal );
  int iNumSettings = p_oTrees->getLength();
  CPPUNIT_ASSERT(iNumSettings == 893);

  //Initial conditions subplot 1
  p_oDoc = p_oXMLParser->parseURI("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/Run 3_run 3 subplot 1_0.xml" );
  p_oTrees = p_oDoc->getElementsByTagName( sVal );
  iNumSettings = p_oTrees->getLength();
  CPPUNIT_ASSERT(iNumSettings == 83);

  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/Run 3_0.xml");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/Run 3_1.xml.gz");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/Run 3_2.xml.gz");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/Run 3_3.xml.gz");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/Run 3_4.xml.gz");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/Run 3_run 3 subplot 1_0.xml");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/Run 3_run 3 subplot 1_1.xml.gz");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/Run 3_run 3 subplot 1_2.xml.gz");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/Run 3_run 3 subplot 1_3.xml.gz");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/Run 3_run 3 subplot 1_4.xml.gz");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/Run 3.xml.gz");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/Run 3_run 3 subplot 1.xml.gz");
  RemoveDirectory("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/");
  RemoveDirectory("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/");
  RemoveDirectory("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Run 3.gz.tar");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Run 3_run 3 subplot 1.gz.tar");

  XMLString::release(&sVal);
  p_oXMLParser->release();
  delete p_oXMLErrorHandler; p_oXMLErrorHandler = NULL;
  XMLPlatformUtils::Terminate();*/
}

/////////////////////////////////////////////////////////////////////////////
// NormalProcessingRun4()
/////////////////////////////////////////////////////////////////////////////
void clTestOutput::NormalProcessingRun4(clSimManager *p_oSimManager) {

 /* p_oSimManager->ReadFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Detailed Output Run 4.xml");
  p_oSimManager->RunSim();

  string sArgs = " -xf \"C:/Code/Core_Model_Tester/Output_Test_Materials/Run 4.gz.tar\" -C \"Output_Test_Materials\"";
  LaunchProcess("c:/code/core_model_tester/tar.exe", sArgs, "c:/code/core_model_tester");
  sArgs = " -xf \"C:/Code/Core_Model_Tester/Output_Test_Materials/Run 4_Run 4 subplot 1.gz.tar\" -C \"Output_Test_Materials\"";
  LaunchProcess("c:/code/core_model_tester/tar.exe", sArgs, "c:/code/core_model_tester");
  sArgs = " -xf \"C:/Code/Core_Model_Tester/Output_Test_Materials/Run 4_Run 4 subplot 2.gz.tar\" -C \"Output_Test_Materials\"";
  LaunchProcess("c:/code/core_model_tester/tar.exe", sArgs, "c:/code/core_model_tester");

  sArgs = " -dqf \"C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/Run 4_0.xml.gz\"";
  LaunchProcess("c:/code/core_model_tester/gzip.exe", sArgs, "c:/code/core_model_tester");
  sArgs = " -dqf \"C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/Run 4_Run 4 subplot 1_0.xml.gz\"";
  LaunchProcess("c:/code/core_model_tester/gzip.exe", sArgs, "c:/code/core_model_tester");
  sArgs = " -dqf \"C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/Run 4_Run 4 subplot 2_0.xml.gz\"";
  LaunchProcess("c:/code/core_model_tester/gzip.exe", sArgs, "c:/code/core_model_tester");

  //Prepare XML parsing tools
  XMLPlatformUtils::Initialize();
  XMLCh *sVal = XMLString::transcode( "LS" );
  DOMImplementation * p_oImpl = DOMImplementationRegistry::getDOMImplementation( sVal );
  xercesc::DOMBuilder *p_oXMLParser = ( ( DOMImplementationLS * ) p_oImpl )->createDOMBuilder( DOMImplementationLS::MODE_SYNCHRONOUS, 0 );
  clXercesErrorHandler *p_oXMLErrorHandler = new clXercesErrorHandler;
  p_oXMLParser->setErrorHandler( p_oXMLErrorHandler );
  XMLString::release(&sVal);

  //Initial conditions
  DOMDocument *p_oDoc = p_oXMLParser->parseURI("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/Run 4_0.xml" );
  sVal = XMLString::transcode( "tree" );
  DOMNodeList * p_oTrees = p_oDoc->getElementsByTagName( sVal );
  int iNumSettings = p_oTrees->getLength();
  CPPUNIT_ASSERT(iNumSettings == 893);

  //Initial conditions subplot 1
  p_oDoc = p_oXMLParser->parseURI("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/Run 4_Run 4 subplot 1_0.xml" );
  p_oTrees = p_oDoc->getElementsByTagName( sVal );
  iNumSettings = p_oTrees->getLength();
  CPPUNIT_ASSERT(iNumSettings == 1);

  //Initial conditions subplot 2
  p_oDoc = p_oXMLParser->parseURI("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/Run 4_Run 4 subplot 2_0.xml" );
  p_oTrees = p_oDoc->getElementsByTagName( sVal );
  iNumSettings = p_oTrees->getLength();
  CPPUNIT_ASSERT(iNumSettings == 89);

  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Run 4.out");

  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/Run 4_0.xml");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/Run 4_1.xml.gz");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/Run 4_2.xml.gz");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/Run 4_3.xml.gz");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/Run 4_4.xml.gz");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/Run 4_Run 4 subplot 1_0.xml");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/Run 4_Run 4 subplot 1_1.xml.gz");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/Run 4_Run 4 subplot 1_2.xml.gz");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/Run 4_Run 4 subplot 1_3.xml.gz");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/Run 4_Run 4 subplot 1_4.xml.gz");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/Run 4_Run 4 subplot 2.xml.gz");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/Run 4_Run 4 subplot 2_0.xml");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/Run 4_Run 4 subplot 2_1.xml.gz");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/Run 4_Run 4 subplot 2_2.xml.gz");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/Run 4_Run 4 subplot 2_3.xml.gz");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/Run 4_Run 4 subplot 2_4.xml.gz");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/Run 4.xml.gz");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/Run 4_Run 4 subplot 1.xml.gz");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/Run 4_Run 4 subplot 2.xml.gz");
  RemoveDirectory("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/");
  RemoveDirectory("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/");
  RemoveDirectory("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Run 4.gz.tar");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Run 4_Run 4 subplot 1.gz.tar");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Run 4_Run 4 subplot 2.gz.tar");

  XMLString::release(&sVal);
  p_oXMLParser->release();
  delete p_oXMLErrorHandler; p_oXMLErrorHandler = NULL;
  XMLPlatformUtils::Terminate();*/
}

/////////////////////////////////////////////////////////////////////////////
// NormalProcessingRun5()
/////////////////////////////////////////////////////////////////////////////
void clTestOutput::NormalProcessingRun5(clSimManager *p_oSimManager) {

 /* int i, j;

  string sOutputPath = "C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/";

  p_oSimManager->ReadFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Detailed Output run 5.xml");
  p_oSimManager->RunSim();

  stringstream sArgs;
  sArgs << " -xf \"C:/Code/Core_Model_Tester/Output_Test_Materials/run 5.gz.tar\" -C \"Output_Test_Materials\"";
  LaunchProcess("c:/code/core_model_tester/tar.exe", sArgs.str(), "c:/code/core_model_tester");
  sArgs.str("");
  sArgs << " -dqf \"C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/run 5_0.xml.gz\"";
  LaunchProcess("c:/code/core_model_tester/gzip.exe", sArgs.str(), "c:/code/core_model_tester");
  sArgs.str("");
  sArgs << " -dqf \"C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/run 5_1.xml.gz\"";
  LaunchProcess("c:/code/core_model_tester/gzip.exe", sArgs.str(), "c:/code/core_model_tester");
  sArgs.str("");
  sArgs << " -dqf \"C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/run 5_2.xml.gz\"";
  LaunchProcess("c:/code/core_model_tester/gzip.exe", sArgs.str(), "c:/code/core_model_tester");
  sArgs.str("");
  sArgs << " -dqf \"C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/run 5_3.xml.gz\"";
  LaunchProcess("c:/code/core_model_tester/gzip.exe", sArgs.str(), "c:/code/core_model_tester");
  sArgs.str("");
  sArgs << " -dqf \"C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/run 5_4.xml.gz\"";
  LaunchProcess("c:/code/core_model_tester/gzip.exe", sArgs.str(), "c:/code/core_model_tester");

  for (i = 1; i < 6; i++) {
    sArgs.str("");
    sArgs << " -xf \"C:/Code/Core_Model_Tester/Output_Test_Materials/run 5_run 5 subplot " << i << ".gz.tar\" -C \"Output_Test_Materials\"";
    LaunchProcess("c:/code/core_model_tester/tar.exe", sArgs.str(), "c:/code/core_model_tester");
    for (j = 0; j < 5; j++) {
      sArgs.str("");
      sArgs << " -dqf \"" << sOutputPath << "run 5_run 5 subplot " << i << "_" << j << ".xml.gz\"";
      LaunchProcess("c:/code/core_model_tester/gzip.exe", sArgs.str(), "c:/code/core_model_tester");
    }
  }

  //Prepare XML parsing tools
  XMLPlatformUtils::Initialize();
  XMLCh *sVal = XMLString::transcode( "LS" );
  DOMImplementation * p_oImpl = DOMImplementationRegistry::getDOMImplementation( sVal );
  xercesc::DOMBuilder *p_oXMLParser = ( ( DOMImplementationLS * ) p_oImpl )->createDOMBuilder( DOMImplementationLS::MODE_SYNCHRONOUS, 0 );
  clXercesErrorHandler *p_oXMLErrorHandler = new clXercesErrorHandler;
  p_oXMLParser->setErrorHandler( p_oXMLErrorHandler );
  XMLString::release(&sVal);

  //
  //Initial conditions

  //Whole plot
  sArgs.str(""); sArgs << sOutputPath << "run 5_0.xml";
  DOMDocument *p_oDoc = p_oXMLParser->parseURI(sArgs.str().c_str());
  sVal = XMLString::transcode( "tree" );
  DOMNodeList * p_oTrees = p_oDoc->getElementsByTagName( sVal );
  int iNumSettings = p_oTrees->getLength();
  CPPUNIT_ASSERT(iNumSettings == 175);

  //Subplot 1
  sArgs.str(""); sArgs << sOutputPath << "run 5_run 5 subplot 1_0.xml";
  p_oDoc = p_oXMLParser->parseURI(sArgs.str().c_str() );
  p_oTrees = p_oDoc->getElementsByTagName( sVal );
  iNumSettings = p_oTrees->getLength();
  CPPUNIT_ASSERT(iNumSettings == 20);

  //Subplot 2
  sArgs.str(""); sArgs << sOutputPath << "run 5_run 5 subplot 2_0.xml";
  p_oDoc = p_oXMLParser->parseURI(sArgs.str().c_str() );
  p_oTrees = p_oDoc->getElementsByTagName( sVal );
  iNumSettings = p_oTrees->getLength();
  CPPUNIT_ASSERT(iNumSettings == 25);

  //Subplot 3
  sArgs.str(""); sArgs << sOutputPath << "run 5_run 5 subplot 3_0.xml";
  p_oDoc = p_oXMLParser->parseURI(sArgs.str().c_str() );
  p_oTrees = p_oDoc->getElementsByTagName( sVal );
  iNumSettings = p_oTrees->getLength();
  CPPUNIT_ASSERT(iNumSettings == 175);

  //Subplot 4
  sArgs.str(""); sArgs << sOutputPath << "run 5_run 5 subplot 4_0.xml";
  p_oDoc = p_oXMLParser->parseURI(sArgs.str().c_str() );
  p_oTrees = p_oDoc->getElementsByTagName( sVal );
  iNumSettings = p_oTrees->getLength();
  CPPUNIT_ASSERT(iNumSettings == 10);

  //Subplot 5
  sArgs.str(""); sArgs << sOutputPath << "run 5_run 5 subplot 5_0.xml";
  p_oDoc = p_oXMLParser->parseURI(sArgs.str().c_str() );
  p_oTrees = p_oDoc->getElementsByTagName( sVal );
  iNumSettings = p_oTrees->getLength();
  CPPUNIT_ASSERT(iNumSettings == 1);

  //
  //Timestep 1

  //Whole plot
  sArgs.str(""); sArgs << sOutputPath << "run 5_1.xml";
  p_oDoc = p_oXMLParser->parseURI(sArgs.str().c_str());
  sVal = XMLString::transcode( "tree" );
  p_oTrees = p_oDoc->getElementsByTagName( sVal );
  iNumSettings = p_oTrees->getLength();
  CPPUNIT_ASSERT(iNumSettings == 2);

  //Subplot 1
  sArgs.str(""); sArgs << sOutputPath << "run 5_run 5 subplot 1_1.xml";
  p_oDoc = p_oXMLParser->parseURI(sArgs.str().c_str() );
  p_oTrees = p_oDoc->getElementsByTagName( sVal );
  iNumSettings = p_oTrees->getLength();
  CPPUNIT_ASSERT(iNumSettings == 0);

  //Subplot 2
  sArgs.str(""); sArgs << sOutputPath << "run 5_run 5 subplot 2_1.xml";
  p_oDoc = p_oXMLParser->parseURI(sArgs.str().c_str() );
  p_oTrees = p_oDoc->getElementsByTagName( sVal );
  iNumSettings = p_oTrees->getLength();
  CPPUNIT_ASSERT(iNumSettings == 0);

  //Subplot 3
  sArgs.str(""); sArgs << sOutputPath << "run 5_run 5 subplot 3_1.xml";
  p_oDoc = p_oXMLParser->parseURI(sArgs.str().c_str() );
  p_oTrees = p_oDoc->getElementsByTagName( sVal );
  iNumSettings = p_oTrees->getLength();
  CPPUNIT_ASSERT(iNumSettings == 2);

  //Subplot 4
  sArgs.str(""); sArgs << sOutputPath << "run 5_run 5 subplot 4_1.xml";
  p_oDoc = p_oXMLParser->parseURI(sArgs.str().c_str() );
  p_oTrees = p_oDoc->getElementsByTagName( sVal );
  iNumSettings = p_oTrees->getLength();
  CPPUNIT_ASSERT(iNumSettings == 0);

  //Subplot 5
  sArgs.str(""); sArgs << sOutputPath << "run 5_run 5 subplot 5_1.xml";
  p_oDoc = p_oXMLParser->parseURI(sArgs.str().c_str() );
  p_oTrees = p_oDoc->getElementsByTagName( sVal );
  iNumSettings = p_oTrees->getLength();
  CPPUNIT_ASSERT(iNumSettings == 1);

  //
  //Timestep 2

  //Whole plot
  sArgs.str(""); sArgs << sOutputPath << "run 5_2.xml";
  p_oDoc = p_oXMLParser->parseURI(sArgs.str().c_str());
  sVal = XMLString::transcode( "tree" );
  p_oTrees = p_oDoc->getElementsByTagName( sVal );
  iNumSettings = p_oTrees->getLength();
  CPPUNIT_ASSERT(iNumSettings == 127);

  //Subplot 1
  sArgs.str(""); sArgs << sOutputPath << "run 5_run 5 subplot 1_2.xml";
  p_oDoc = p_oXMLParser->parseURI(sArgs.str().c_str() );
  p_oTrees = p_oDoc->getElementsByTagName( sVal );
  iNumSettings = p_oTrees->getLength();
  CPPUNIT_ASSERT(iNumSettings == 16);

  //Subplot 2
  sArgs.str(""); sArgs << sOutputPath << "run 5_run 5 subplot 2_2.xml";
  p_oDoc = p_oXMLParser->parseURI(sArgs.str().c_str() );
  p_oTrees = p_oDoc->getElementsByTagName( sVal );
  iNumSettings = p_oTrees->getLength();
  CPPUNIT_ASSERT(iNumSettings == 18);

  //Subplot 3
  sArgs.str(""); sArgs << sOutputPath << "run 5_run 5 subplot 3_2.xml";
  p_oDoc = p_oXMLParser->parseURI(sArgs.str().c_str() );
  p_oTrees = p_oDoc->getElementsByTagName( sVal );
  iNumSettings = p_oTrees->getLength();
  CPPUNIT_ASSERT(iNumSettings == 127);

  //Subplot 4
  sArgs.str(""); sArgs << sOutputPath << "run 5_run 5 subplot 4_2.xml";
  p_oDoc = p_oXMLParser->parseURI(sArgs.str().c_str() );
  p_oTrees = p_oDoc->getElementsByTagName( sVal );
  iNumSettings = p_oTrees->getLength();
  CPPUNIT_ASSERT(iNumSettings == 7);

  //Subplot 5
  sArgs.str(""); sArgs << sOutputPath << "run 5_run 5 subplot 5_2.xml";
  p_oDoc = p_oXMLParser->parseURI(sArgs.str().c_str() );
  p_oTrees = p_oDoc->getElementsByTagName( sVal );
  iNumSettings = p_oTrees->getLength();
  CPPUNIT_ASSERT(iNumSettings == 1);

  //
  //Timestep 3

  //Whole plot
  sArgs.str(""); sArgs << sOutputPath << "run 5_3.xml";
  p_oDoc = p_oXMLParser->parseURI(sArgs.str().c_str());
  sVal = XMLString::transcode( "tree" );
  p_oTrees = p_oDoc->getElementsByTagName( sVal );
  iNumSettings = p_oTrees->getLength();
  CPPUNIT_ASSERT(iNumSettings == 2);

  //Subplot 1
  sArgs.str(""); sArgs << sOutputPath << "run 5_run 5 subplot 1_3.xml";
  p_oDoc = p_oXMLParser->parseURI(sArgs.str().c_str() );
  p_oTrees = p_oDoc->getElementsByTagName( sVal );
  iNumSettings = p_oTrees->getLength();
  CPPUNIT_ASSERT(iNumSettings == 0);

  //Subplot 2
  sArgs.str(""); sArgs << sOutputPath << "run 5_run 5 subplot 2_3.xml";
  p_oDoc = p_oXMLParser->parseURI(sArgs.str().c_str() );
  p_oTrees = p_oDoc->getElementsByTagName( sVal );
  iNumSettings = p_oTrees->getLength();
  CPPUNIT_ASSERT(iNumSettings == 0);

  //Subplot 3
  sArgs.str(""); sArgs << sOutputPath << "run 5_run 5 subplot 3_3.xml";
  p_oDoc = p_oXMLParser->parseURI(sArgs.str().c_str() );
  p_oTrees = p_oDoc->getElementsByTagName( sVal );
  iNumSettings = p_oTrees->getLength();
  CPPUNIT_ASSERT(iNumSettings == 2);

  //Subplot 4
  sArgs.str(""); sArgs << sOutputPath << "run 5_run 5 subplot 4_3.xml";
  p_oDoc = p_oXMLParser->parseURI(sArgs.str().c_str() );
  p_oTrees = p_oDoc->getElementsByTagName( sVal );
  iNumSettings = p_oTrees->getLength();
  CPPUNIT_ASSERT(iNumSettings == 0);

  //Subplot 5
  sArgs.str(""); sArgs << sOutputPath << "run 5_run 5 subplot 5_3.xml";
  p_oDoc = p_oXMLParser->parseURI(sArgs.str().c_str() );
  p_oTrees = p_oDoc->getElementsByTagName( sVal );
  iNumSettings = p_oTrees->getLength();
  CPPUNIT_ASSERT(iNumSettings == 1);

  //
  //Timestep 4

  //Whole plot
  sArgs.str(""); sArgs << sOutputPath << "run 5_4.xml";
  p_oDoc = p_oXMLParser->parseURI(sArgs.str().c_str());
  sVal = XMLString::transcode( "tree" );
  p_oTrees = p_oDoc->getElementsByTagName( sVal );
  iNumSettings = p_oTrees->getLength();
  CPPUNIT_ASSERT(iNumSettings == 175);

  //Subplot 1
  sArgs.str(""); sArgs << sOutputPath << "run 5_run 5 subplot 1_4.xml";
  p_oDoc = p_oXMLParser->parseURI(sArgs.str().c_str() );
  p_oTrees = p_oDoc->getElementsByTagName( sVal );
  iNumSettings = p_oTrees->getLength();
  CPPUNIT_ASSERT(iNumSettings == 20);

  //Subplot 2
  sArgs.str(""); sArgs << sOutputPath << "run 5_run 5 subplot 2_4.xml";
  p_oDoc = p_oXMLParser->parseURI(sArgs.str().c_str() );
  p_oTrees = p_oDoc->getElementsByTagName( sVal );
  iNumSettings = p_oTrees->getLength();
  CPPUNIT_ASSERT(iNumSettings == 25);

  //Subplot 3
  sArgs.str(""); sArgs << sOutputPath << "run 5_run 5 subplot 3_4.xml";
  p_oDoc = p_oXMLParser->parseURI(sArgs.str().c_str() );
  p_oTrees = p_oDoc->getElementsByTagName( sVal );
  iNumSettings = p_oTrees->getLength();
  CPPUNIT_ASSERT(iNumSettings == 175);

  //Subplot 4
  sArgs.str(""); sArgs << sOutputPath << "run 5_run 5 subplot 4_4.xml";
  p_oDoc = p_oXMLParser->parseURI(sArgs.str().c_str() );
  p_oTrees = p_oDoc->getElementsByTagName( sVal );
  iNumSettings = p_oTrees->getLength();
  CPPUNIT_ASSERT(iNumSettings == 10);

  //Subplot 5
  sArgs.str(""); sArgs << sOutputPath << "run 5_run 5 subplot 5_4.xml";
  p_oDoc = p_oXMLParser->parseURI(sArgs.str().c_str() );
  p_oTrees = p_oDoc->getElementsByTagName( sVal );
  iNumSettings = p_oTrees->getLength();
  CPPUNIT_ASSERT(iNumSettings == 1);

  for (i = 0; i < 5; i++) {
    sArgs.str(""); sArgs << sOutputPath << "run 5_" << i << ".xml";
    DeleteThisFile(sArgs.str().c_str());
    for (j = 1; j < 6; j++) {
      sArgs.str(""); sArgs << sOutputPath << "run 5_run 5 subplot " << j << "_" << i << ".xml";
      DeleteThisFile(sArgs.str().c_str());
    }
  }
  sArgs.str(""); sArgs << sOutputPath << "run 5.xml.gz";
  DeleteThisFile(sArgs.str().c_str());
  for (j = 1; j < 6; j++) {
    sArgs.str(""); sArgs << sOutputPath << "run 5_run 5 subplot " << j << ".xml.gz";
    DeleteThisFile(sArgs.str().c_str());
  }
  RemoveDirectory("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/");
  RemoveDirectory("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/");
  RemoveDirectory("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/run 5.gz.tar");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/run 5_run 5 subplot 1.gz.tar");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/run 5_run 5 subplot 2.gz.tar");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/run 5_run 5 subplot 3.gz.tar");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/run 5_run 5 subplot 4.gz.tar");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/run 5_run 5 subplot 5.gz.tar");

  XMLString::release(&sVal);
  p_oXMLParser->release();
  delete p_oXMLErrorHandler; p_oXMLErrorHandler = NULL;
  XMLPlatformUtils::Terminate();*/
}


/////////////////////////////////////////////////////////////////////////////
// NormalProcessingRun6()
/////////////////////////////////////////////////////////////////////////////
void clTestOutput::NormalProcessingRun6(clSimManager *p_oSimManager) {

 /* p_oSimManager->ReadFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Detailed Output run 6.xml");
  p_oSimManager->RunSim();

  string sArgs = " -xf \"C:/Code/Core_Model_Tester/Output_Test_Materials/run 6.gz.tar\" -C \"Output_Test_Materials\"";
  LaunchProcess("c:/code/core_model_tester/tar.exe", sArgs, "c:/code/core_model_tester");
  sArgs = " -xf \"C:/Code/Core_Model_Tester/Output_Test_Materials/run 6_run 6 subplot 1.gz.tar\" -C \"Output_Test_Materials\"";
  LaunchProcess("c:/code/core_model_tester/tar.exe", sArgs, "c:/code/core_model_tester");

  sArgs = " -dqf \"C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/run 6_0.xml.gz\"";
  LaunchProcess("c:/code/core_model_tester/gzip.exe", sArgs, "c:/code/core_model_tester");
  sArgs = " -dqf \"C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/run 6_run 6 subplot 1_0.xml.gz\"";
  LaunchProcess("c:/code/core_model_tester/gzip.exe", sArgs, "c:/code/core_model_tester");

  //Prepare XML parsing tools
  XMLPlatformUtils::Initialize();
  XMLCh *sVal = XMLString::transcode( "LS" );
  DOMImplementation * p_oImpl = DOMImplementationRegistry::getDOMImplementation( sVal );
  xercesc::DOMBuilder *p_oXMLParser = ( ( DOMImplementationLS * ) p_oImpl )->createDOMBuilder( DOMImplementationLS::MODE_SYNCHRONOUS, 0 );
  clXercesErrorHandler *p_oXMLErrorHandler = new clXercesErrorHandler;
  p_oXMLParser->setErrorHandler( p_oXMLErrorHandler );
  XMLString::release(&sVal);

  //Initial conditions
  DOMDocument *p_oDoc = p_oXMLParser->parseURI("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/run 6_0.xml" );
  sVal = XMLString::transcode( "tree" );
  DOMNodeList * p_oTrees = p_oDoc->getElementsByTagName( sVal );
  int iNumSettings = p_oTrees->getLength();
  CPPUNIT_ASSERT(iNumSettings == 893);

  //Initial conditions subplot 1
  p_oDoc = p_oXMLParser->parseURI("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/run 6_run 6 subplot 1_0.xml" );
  p_oTrees = p_oDoc->getElementsByTagName( sVal );
  iNumSettings = p_oTrees->getLength();
  CPPUNIT_ASSERT(iNumSettings == 72);

  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/run 6_0.xml");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/run 6_1.xml.gz");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/run 6_2.xml.gz");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/run 6_3.xml.gz");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/run 6_4.xml.gz");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/run 6_run 6 subplot 1_0.xml");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/run 6_run 6 subplot 1_1.xml.gz");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/run 6_run 6 subplot 1_2.xml.gz");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/run 6_run 6 subplot 1_3.xml.gz");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/run 6_run 6 subplot 1_4.xml.gz");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/run 6.xml.gz");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/run 6_run 6 subplot 1.xml.gz");
  RemoveDirectory("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/");
  RemoveDirectory("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/");
  RemoveDirectory("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/run 6.gz.tar");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/run 6_run 6 subplot 1.gz.tar");

  XMLString::release(&sVal);
  p_oXMLParser->release();
  delete p_oXMLErrorHandler; p_oXMLErrorHandler = NULL;
  XMLPlatformUtils::Terminate();*/
}

/////////////////////////////////////////////////////////////////////////////
// NormalProcessingRun7()
/////////////////////////////////////////////////////////////////////////////
void clTestOutput::NormalProcessingRun7(clSimManager *p_oSimManager) {

/*  using namespace std;
  DOMNode * p_oNode;
  DOMElement * p_oElement;
  char * cData = NULL, *cSp = NULL, *cTp = NULL;
  XMLCh *sCode, *sSp, *sTp;
  int iNumHarvest = 0,
      iNumDisease = 0,
      iNumNatural = 0,
      iNumStorm = 0,
      iNumInsects = 0,
      iNumOther = 0, i;

  p_oSimManager->ReadFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Detailed Output run 7.xml");
  p_oSimManager->RunSim();

  string sArgs = " -xf \"C:/Code/Core_Model_Tester/Output_Test_Materials/run 7.gz.tar\" -C \"Output_Test_Materials\"";
  LaunchProcess("c:/code/core_model_tester/tar.exe", sArgs, "c:/code/core_model_tester");

  sArgs = " -dqf \"C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/run 7_0.xml.gz\"";
  LaunchProcess("c:/code/core_model_tester/gzip.exe", sArgs, "c:/code/core_model_tester");
  sArgs = " -dqf \"C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/run 7_1.xml.gz\"";
  LaunchProcess("c:/code/core_model_tester/gzip.exe", sArgs, "c:/code/core_model_tester");

  //Prepare XML parsing tools
  XMLPlatformUtils::Initialize();
  XMLCh *sVal = XMLString::transcode( "LS" );
  DOMImplementation * p_oImpl = DOMImplementationRegistry::getDOMImplementation( sVal );
  xercesc::DOMBuilder *p_oXMLParser = ( ( DOMImplementationLS * ) p_oImpl )->createDOMBuilder( DOMImplementationLS::MODE_SYNCHRONOUS, 0 );
  clXercesErrorHandler *p_oXMLErrorHandler = new clXercesErrorHandler;
  p_oXMLParser->setErrorHandler( p_oXMLErrorHandler );
  XMLString::release(&sVal);

  //Initial conditions live
  DOMDocument *p_oDoc = p_oXMLParser->parseURI("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/run 7_0.xml" );
  sVal = XMLString::transcode( "tree" );
  DOMNodeList * p_oTrees = p_oDoc->getElementsByTagName( sVal );
  int iNumSettings = p_oTrees->getLength();
  CPPUNIT_ASSERT(iNumSettings == 893);
  XMLString::release(&sVal);

  //Initial conditions dead
  sVal = XMLString::transcode( "ghost" );
  p_oTrees = p_oDoc->getElementsByTagName( sVal );
  iNumSettings = p_oTrees->getLength();
  CPPUNIT_ASSERT(iNumSettings == 0);
  XMLString::release(&sVal);

  //TS 1 Live
  p_oDoc = p_oXMLParser->parseURI("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/run 7_1.xml" );
  sVal = XMLString::transcode( "tree" );
  p_oTrees = p_oDoc->getElementsByTagName( sVal );
  iNumSettings = p_oTrees->getLength();
  CPPUNIT_ASSERT(iNumSettings == 527);
  XMLString::release(&sVal);

  //TS 1 dead
  sVal = XMLString::transcode( "ghost" );
  p_oTrees = p_oDoc->getElementsByTagName( sVal );
  iNumSettings = p_oTrees->getLength();
  CPPUNIT_ASSERT(iNumSettings == 366);

  sCode = XMLString::transcode( "rs" );
  sSp = XMLString::transcode( "sp" );
  sTp = XMLString::transcode( "tp" );
  for ( i = 0; i < iNumSettings; i++ ) {
    p_oNode = p_oTrees->item( i );
    p_oElement = ( DOMElement * ) p_oNode;
    cData = XMLString::transcode( p_oElement->getAttributeNode( sCode )->getNodeValue() );
    cSp = XMLString::transcode( p_oElement->getAttributeNode( sSp )->getNodeValue() );
    cTp = XMLString::transcode( p_oElement->getAttributeNode( sTp )->getNodeValue() );
    if ( strcmp( "1", cData ) == 0 ) {
      iNumHarvest++;
      CPPUNIT_ASSERT(strcmp( "0", cSp) == 0);
      CPPUNIT_ASSERT(strcmp( "3", cTp) == 0);
    } else if ( strcmp( "2", cData ) == 0 ) {
      iNumNatural++;
      CPPUNIT_ASSERT(strcmp( "0", cSp) == 0);
      CPPUNIT_ASSERT(strcmp( "2", cTp) == 0);
    } else if ( strcmp( "3", cData ) == 0 ) {
      iNumDisease++;
      CPPUNIT_ASSERT(strcmp( "2", cSp) == 0);
      CPPUNIT_ASSERT(strcmp( "3", cTp) == 0);
    } else if ( strcmp( "5", cData ) == 0 ) {
      iNumInsects++;
      CPPUNIT_ASSERT(strcmp( "1", cSp) == 0);
      CPPUNIT_ASSERT(strcmp( "3", cTp) == 0);
    } else if ( strcmp( "6", cData ) == 0 ) {
      iNumStorm++;
      CPPUNIT_ASSERT(strcmp( "3", cSp) == 0);
      CPPUNIT_ASSERT(strcmp( "2", cTp) == 0);
    } else {
      iNumOther++;
    }
    delete[] cData; cData = NULL;
    delete[] cSp; cSp = NULL;
    delete[] cTp; cTp = NULL;
  }
  XMLString::release(&sVal);
  XMLString::release(&sCode);
  XMLString::release(&sSp);
  XMLString::release(&sTp);

  CPPUNIT_ASSERT(iNumHarvest == 95);
  CPPUNIT_ASSERT(iNumDisease == 66);
  CPPUNIT_ASSERT(iNumNatural == 130);
  CPPUNIT_ASSERT(iNumStorm == 26);
  CPPUNIT_ASSERT(iNumInsects == 49);
  CPPUNIT_ASSERT(iNumOther == 0);

  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/run 7_0.xml");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/run 7_1.xml");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/run 7_2.xml.gz");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/run 7_3.xml.gz");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/run 7_4.xml.gz");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/run 7.xml.gz");
  RemoveDirectory("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/Output_Test_Materials/");
  RemoveDirectory("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/Core_Model_Tester/");
  RemoveDirectory("C:/Code/Core_Model_Tester/Output_Test_Materials/Code/");
  DeleteThisFile("C:/Code/Core_Model_Tester/Output_Test_Materials/run 7.gz.tar");

  XMLString::release(&sVal);
  p_oXMLParser->release();
  delete p_oXMLErrorHandler; p_oXMLErrorHandler = NULL;
  XMLPlatformUtils::Terminate();*/
}


/////////////////////////////////////////////////////////////////////////////
// TestFilePresence()
/////////////////////////////////////////////////////////////////////////////
void clTestOutput::TestFilePresence(clSimManager *p_oSimManager) {

  //Feed our file to the sim manager
  p_oSimManager->ReadFile(WriteXMLFile1());

  //Verify that the output file has been created
  CPPUNIT_ASSERT(DoesFileExist("testoutput.gz.tar"));

  //Run one timestep
  p_oSimManager->RunSim(1);

  //Verify that the output file has been created
  CPPUNIT_ASSERT(DoesFileExist("testoutput.gz.tar"));

  DeleteThisFile("testoutput.gz.tar");
  CPPUNIT_ASSERT(!DoesFileExist("testoutput.gz.tar"));

  p_oSimManager->ReadFile(WriteXMLFile2());

  //Verify that the output file has been created
  CPPUNIT_ASSERT(DoesFileExist("testoutput1.gz.tar"));

  //Run one timestep
  p_oSimManager->RunSim(1);

  //Verify that the output file has been created
  CPPUNIT_ASSERT(DoesFileExist("testoutput1.gz.tar"));

  DeleteThisFile("testoutput1.gz.tar");
  CPPUNIT_ASSERT(!DoesFileExist("testoutput1.gz.tar"));
}


/////////////////////////////////////////////////////////////////////////////
// WriteXMLFile1()
/////////////////////////////////////////////////////////////////////////////
const char* clTestOutput::WriteXMLFile1()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06080101\">"
       << "<plot>"
       << "<timesteps>400</timesteps>"
       << "<rt_timestep>0</rt_timestep>"
       << "<randomSeed>0</randomSeed>"
       << "<yearsPerTimestep>5.0</yearsPerTimestep>"
       << "<plot_lenX>500.0</plot_lenX>"
       << "<plot_lenY>500.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>41.92</plot_latitude>"
       << "<plot_title>Default parameter file-use for testing only</plot_title>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"ACRU\"/>"
       << "<tr_species speciesName=\"ACSA\"/>"
       << "<tr_species speciesName=\"BEAL\"/>"
       << "</tr_speciesList>"
       << "<tr_sizeClasses>"
       << "<tr_sizeClass sizeKey=\"s1.0\"/>"
       << "<tr_sizeClass sizeKey=\"s10.0\"/>"
       << "</tr_sizeClasses>"
       << "<tr_initialDensities>"
       << "<tr_idVals whatSpecies=\"ACRU\">"
       << "<tr_initialDensity sizeClass=\"s1.0\">25.0</tr_initialDensity>"
       << "</tr_idVals>"
       << "<tr_idVals whatSpecies=\"ACSA\">"
       << "<tr_initialDensity sizeClass=\"s1.0\">25.0</tr_initialDensity>"
       << "</tr_idVals>"
       << "<tr_idVals whatSpecies=\"BEAL\">"
       << "<tr_initialDensity sizeClass=\"s1.0\">25.0</tr_initialDensity>"
       << "</tr_idVals>"
       << "</tr_initialDensities>"
       << "<tr_seedDiam10Cm>0.2</tr_seedDiam10Cm>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"ACRU\">10.0</tr_madVal>"
       << "<tr_madVal species=\"ACSA\">10.0</tr_madVal>"
       << "<tr_madVal species=\"BEAL\">10.0</tr_madVal>"
       << "</tr_minAdultDBH>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"ACRU\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"ACSA\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"BEAL\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>"
       << "</trees>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>QuadratLight</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"ACRU\" type=\"Seedling\"/>"
       << "<applyTo species=\"ACSA\" type=\"Seedling\"/>"
       << "<applyTo species=\"BEAL\" type=\"Seedling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Output</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"ACRU\" type=\"Seedling\"/>"
       << "<applyTo species=\"ACRU\" type=\"Sapling\"/>"
       << "<applyTo species=\"ACRU\" type=\"Adult\"/>"
       << "<applyTo species=\"ACSA\" type=\"Seedling\"/>"
       << "<applyTo species=\"ACSA\" type=\"Sapling\"/>"
       << "<applyTo species=\"ACSA\" type=\"Adult\"/>"
       << "<applyTo species=\"BEAL\" type=\"Seedling\"/>"
       << "<applyTo species=\"BEAL\" type=\"Sapling\"/>"
       << "<applyTo species=\"BEAL\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<allometry>"
       << "<tr_whatAdultHeightDiam>"
       << "<tr_wahdVal species=\"ACRU\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"ACSA\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"BEAL\">0</tr_wahdVal>"
       << "</tr_whatAdultHeightDiam>"
       << "<tr_whatSaplingHeightDiam>"
       << "<tr_wsahdVal species=\"ACRU\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"ACSA\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"BEAL\">0</tr_wsahdVal>"
       << "</tr_whatSaplingHeightDiam>"
       << "<tr_whatSeedlingHeightDiam>"
       << "<tr_wsehdVal species=\"ACRU\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"ACSA\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"BEAL\">0</tr_wsehdVal>"
       << "</tr_whatSeedlingHeightDiam>"
       << "<tr_whatAdultCrownRadDiam>"
       << "<tr_wacrdVal species=\"ACRU\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"ACSA\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"BEAL\">0</tr_wacrdVal>"
       << "</tr_whatAdultCrownRadDiam>"
       << "<tr_whatSaplingCrownRadDiam>"
       << "<tr_wscrdVal species=\"ACRU\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"ACSA\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"BEAL\">0</tr_wscrdVal>"
       << "</tr_whatSaplingCrownRadDiam>"
       << "<tr_whatAdultCrownHeightHeight>"
       << "<tr_wachhVal species=\"ACRU\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"ACSA\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"BEAL\">0</tr_wachhVal>"
       << "</tr_whatAdultCrownHeightHeight>"
       << "<tr_whatSaplingCrownHeightHeight>"
       << "<tr_wschhVal species=\"ACRU\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"ACSA\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"BEAL\">0</tr_wschhVal>"
       << "</tr_whatSaplingCrownHeightHeight>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"ACRU\">30.0</tr_chVal>"
       << "<tr_chVal species=\"ACSA\">30.0</tr_chVal>"
       << "<tr_chVal species=\"BEAL\">30.0</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"ACRU\">0.108</tr_sacrVal>"
       << "<tr_sacrVal species=\"ACSA\">0.107</tr_sacrVal>"
       << "<tr_sacrVal species=\"BEAL\">0.109</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"ACRU\">1.0</tr_screVal>"
       << "<tr_screVal species=\"ACSA\">1.0</tr_screVal>"
       << "<tr_screVal species=\"BEAL\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"ACRU\">0.49</tr_sachVal>"
       << "<tr_sachVal species=\"ACSA\">0.58</tr_sachVal>"
       << "<tr_sachVal species=\"BEAL\">0.54</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"ACRU\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"ACSA\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"BEAL\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"ACRU\">0.75</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"ACSA\">0.75</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"BEAL\">0.75</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"ACRU\">0.0</tr_idtdVal>"
       << "<tr_idtdVal species=\"ACSA\">0.0</tr_idtdVal>"
       << "<tr_idtdVal species=\"BEAL\">0.0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"ACRU\">0.063</tr_soahVal>"
       << "<tr_soahVal species=\"ACSA\">0.062333334</tr_soahVal>"
       << "<tr_soahVal species=\"BEAL\">0.063</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"ACRU\">0.03</tr_sohdVal>"
       << "<tr_sohdVal species=\"ACSA\">0.03</tr_sohdVal>"
       << "<tr_sohdVal species=\"BEAL\">0.03</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "</allometry>"
       << "<GeneralLight>"
       << "<li_beamFractGlobalRad>0.5</li_beamFractGlobalRad>"
       << "<li_clearSkyTransCoeff>0.65</li_clearSkyTransCoeff>"
       << "<li_julianDayGrowthStarts>120</li_julianDayGrowthStarts>"
       << "<li_julianDayGrowthEnds>270</li_julianDayGrowthEnds>"
       << "<li_lightExtinctionCoefficient>"
       << "<li_lecVal species=\"ACRU\">0.399</li_lecVal>"
       << "<li_lecVal species=\"ACSA\">0.399</li_lecVal>"
       << "<li_lecVal species=\"BEAL\">0.399</li_lecVal>"
       << "</li_lightExtinctionCoefficient>"
       << "</GeneralLight>"
       << "<QuadratLight1>"
       << "<li_heightOfFishEyePhoto>0</li_heightOfFishEyePhoto>"
       << "<li_quadratAllGLIs>0</li_quadratAllGLIs>"
       << "<li_minSunAngle>0.779</li_minSunAngle>"
       << "<li_numAltGrids>12</li_numAltGrids>"
       << "<li_numAziGrids>18</li_numAziGrids>"
       << "<li_quadratLightHeight>0.675</li_quadratLightHeight>"
       << "</QuadratLight1>"
       << "<output>"
       << "<ou_filename>testoutput.gz.tar</ou_filename>"
       << "<ou_treeInfo species=\"ACRU\" type=\"Seedling\">"
       << "<ou_saveFreq>1</ou_saveFreq>"
       << "<ou_float>X</ou_float>"
       << "<ou_float>Y</ou_float>"
       << "<ou_float>Diam10</ou_float>"
       << "<ou_float>Height</ou_float>"
       << "</ou_treeInfo>"
       << "<ou_treeInfo species=\"ACRU\" type=\"Sapling\">"
       << "<ou_saveFreq>1</ou_saveFreq>"
       << "<ou_float>X</ou_float>"
       << "<ou_float>Y</ou_float>"
       << "<ou_float>Diam10</ou_float>"
       << "<ou_float>DBH</ou_float>"
       << "<ou_float>Height</ou_float>"
       << "</ou_treeInfo>"
       << "<ou_treeInfo species=\"ACRU\" type=\"Adult\">"
       << "<ou_saveFreq>1</ou_saveFreq>"
       << "<ou_float>X</ou_float>"
       << "<ou_float>Y</ou_float>"
       << "<ou_float>DBH</ou_float>"
       << "<ou_float>Height</ou_float>"
       << "</ou_treeInfo>"
       << "<ou_treeInfo species=\"ACSA\" type=\"Seedling\">"
       << "<ou_saveFreq>1</ou_saveFreq>"
       << "<ou_float>X</ou_float>"
       << "<ou_float>Y</ou_float>"
       << "<ou_float>Diam10</ou_float>"
       << "<ou_float>Height</ou_float>"
       << "</ou_treeInfo>"
       << "<ou_treeInfo species=\"ACSA\" type=\"Sapling\">"
       << "<ou_saveFreq>1</ou_saveFreq>"
       << "<ou_float>X</ou_float>"
       << "<ou_float>Y</ou_float>"
       << "<ou_float>Diam10</ou_float>"
       << "<ou_float>DBH</ou_float>"
       << "<ou_float>Height</ou_float>"
       << "</ou_treeInfo>"
       << "<ou_treeInfo species=\"ACSA\" type=\"Adult\">"
       << "<ou_saveFreq>1</ou_saveFreq>"
       << "<ou_float>X</ou_float>"
       << "<ou_float>Y</ou_float>"
       << "<ou_float>DBH</ou_float>"
       << "<ou_float>Height</ou_float>"
       << "</ou_treeInfo>"
       << "<ou_treeInfo species=\"BEAL\" type=\"Seedling\">"
       << "<ou_saveFreq>1</ou_saveFreq>"
       << "<ou_float>X</ou_float>"
       << "<ou_float>Y</ou_float>"
       << "<ou_float>Diam10</ou_float>"
       << "<ou_float>Height</ou_float>"
       << "</ou_treeInfo>"
       << "<ou_treeInfo species=\"BEAL\" type=\"Sapling\">"
       << "<ou_saveFreq>1</ou_saveFreq>"
       << "<ou_float>X</ou_float>"
       << "<ou_float>Y</ou_float>"
       << "<ou_float>Diam10</ou_float>"
       << "<ou_float>DBH</ou_float>"
       << "<ou_float>Height</ou_float>"
       << "</ou_treeInfo>"
       << "<ou_treeInfo species=\"BEAL\" type=\"Adult\">"
       << "<ou_saveFreq>1</ou_saveFreq>"
       << "<ou_float>X</ou_float>"
       << "<ou_float>Y</ou_float>"
       << "<ou_float>DBH</ou_float>"
       << "<ou_float>Height</ou_float>"
       << "</ou_treeInfo>"
       << "<ou_gridInfo gridName=\"Quadrat GLI\">"
       << "<ou_saveFreq>1</ou_saveFreq>"
       << "<ou_float>GLI</ou_float>"
       << "</ou_gridInfo>"
       << "</output>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteXMLFile2()
/////////////////////////////////////////////////////////////////////////////
const char* clTestOutput::WriteXMLFile2()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06080101\">"
       << "<plot>"
       << "<timesteps>400</timesteps>"
       << "<rt_timestep>0</rt_timestep>"
       << "<randomSeed>0</randomSeed>"
       << "<yearsPerTimestep>5.0</yearsPerTimestep>"
       << "<plot_lenX>500.0</plot_lenX>"
       << "<plot_lenY>500.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>41.92</plot_latitude>"
       << "<plot_title>Default parameter file-use for testing only</plot_title>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"ACRU\"/>"
       << "<tr_species speciesName=\"ACSA\"/>"
       << "<tr_species speciesName=\"BEAL\"/>"
       << "</tr_speciesList>"
       << "<tr_sizeClasses>"
       << "<tr_sizeClass sizeKey=\"s1.0\"/>"
       << "<tr_sizeClass sizeKey=\"s10.0\"/>"
       << "</tr_sizeClasses>"
       << "<tr_initialDensities>"
       << "<tr_idVals whatSpecies=\"ACRU\">"
       << "<tr_initialDensity sizeClass=\"s1.0\">25.0</tr_initialDensity>"
       << "</tr_idVals>"
       << "<tr_idVals whatSpecies=\"ACSA\">"
       << "<tr_initialDensity sizeClass=\"s1.0\">25.0</tr_initialDensity>"
       << "</tr_idVals>"
       << "<tr_idVals whatSpecies=\"BEAL\">"
       << "<tr_initialDensity sizeClass=\"s1.0\">25.0</tr_initialDensity>"
       << "</tr_idVals>"
       << "</tr_initialDensities>"
       << "<tr_seedDiam10Cm>0.2</tr_seedDiam10Cm>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"ACRU\">10.0</tr_madVal>"
       << "<tr_madVal species=\"ACSA\">10.0</tr_madVal>"
       << "<tr_madVal species=\"BEAL\">10.0</tr_madVal>"
       << "</tr_minAdultDBH>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"ACRU\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"ACSA\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"BEAL\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>"
       << "</trees>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>QuadratLight</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"ACRU\" type=\"Seedling\"/>"
       << "<applyTo species=\"ACSA\" type=\"Seedling\"/>"
       << "<applyTo species=\"BEAL\" type=\"Seedling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Output</behaviorName>"
       << "<version>1.0</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"ACRU\" type=\"Seedling\"/>"
       << "<applyTo species=\"ACRU\" type=\"Sapling\"/>"
       << "<applyTo species=\"ACRU\" type=\"Adult\"/>"
       << "<applyTo species=\"ACSA\" type=\"Seedling\"/>"
       << "<applyTo species=\"ACSA\" type=\"Sapling\"/>"
       << "<applyTo species=\"ACSA\" type=\"Adult\"/>"
       << "<applyTo species=\"BEAL\" type=\"Seedling\"/>"
       << "<applyTo species=\"BEAL\" type=\"Sapling\"/>"
       << "<applyTo species=\"BEAL\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<allometry>"
       << "<tr_whatAdultHeightDiam>"
       << "<tr_wahdVal species=\"ACRU\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"ACSA\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"BEAL\">0</tr_wahdVal>"
       << "</tr_whatAdultHeightDiam>"
       << "<tr_whatSaplingHeightDiam>"
       << "<tr_wsahdVal species=\"ACRU\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"ACSA\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"BEAL\">0</tr_wsahdVal>"
       << "</tr_whatSaplingHeightDiam>"
       << "<tr_whatSeedlingHeightDiam>"
       << "<tr_wsehdVal species=\"ACRU\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"ACSA\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"BEAL\">0</tr_wsehdVal>"
       << "</tr_whatSeedlingHeightDiam>"
       << "<tr_whatAdultCrownRadDiam>"
       << "<tr_wacrdVal species=\"ACRU\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"ACSA\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"BEAL\">0</tr_wacrdVal>"
       << "</tr_whatAdultCrownRadDiam>"
       << "<tr_whatSaplingCrownRadDiam>"
       << "<tr_wscrdVal species=\"ACRU\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"ACSA\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"BEAL\">0</tr_wscrdVal>"
       << "</tr_whatSaplingCrownRadDiam>"
       << "<tr_whatAdultCrownHeightHeight>"
       << "<tr_wachhVal species=\"ACRU\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"ACSA\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"BEAL\">0</tr_wachhVal>"
       << "</tr_whatAdultCrownHeightHeight>"
       << "<tr_whatSaplingCrownHeightHeight>"
       << "<tr_wschhVal species=\"ACRU\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"ACSA\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"BEAL\">0</tr_wschhVal>"
       << "</tr_whatSaplingCrownHeightHeight>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"ACRU\">30.0</tr_chVal>"
       << "<tr_chVal species=\"ACSA\">30.0</tr_chVal>"
       << "<tr_chVal species=\"BEAL\">30.0</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"ACRU\">0.108</tr_sacrVal>"
       << "<tr_sacrVal species=\"ACSA\">0.107</tr_sacrVal>"
       << "<tr_sacrVal species=\"BEAL\">0.109</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"ACRU\">1.0</tr_screVal>"
       << "<tr_screVal species=\"ACSA\">1.0</tr_screVal>"
       << "<tr_screVal species=\"BEAL\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"ACRU\">0.49</tr_sachVal>"
       << "<tr_sachVal species=\"ACSA\">0.58</tr_sachVal>"
       << "<tr_sachVal species=\"BEAL\">0.54</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"ACRU\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"ACSA\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"BEAL\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"ACRU\">0.75</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"ACSA\">0.75</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"BEAL\">0.75</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"ACRU\">0.0</tr_idtdVal>"
       << "<tr_idtdVal species=\"ACSA\">0.0</tr_idtdVal>"
       << "<tr_idtdVal species=\"BEAL\">0.0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"ACRU\">0.063</tr_soahVal>"
       << "<tr_soahVal species=\"ACSA\">0.062333334</tr_soahVal>"
       << "<tr_soahVal species=\"BEAL\">0.063</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"ACRU\">0.03</tr_sohdVal>"
       << "<tr_sohdVal species=\"ACSA\">0.03</tr_sohdVal>"
       << "<tr_sohdVal species=\"BEAL\">0.03</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "</allometry>"
       << "<GeneralLight>"
       << "<li_beamFractGlobalRad>0.5</li_beamFractGlobalRad>"
       << "<li_clearSkyTransCoeff>0.65</li_clearSkyTransCoeff>"
       << "<li_julianDayGrowthStarts>120</li_julianDayGrowthStarts>"
       << "<li_julianDayGrowthEnds>270</li_julianDayGrowthEnds>"
       << "<li_lightExtinctionCoefficient>"
       << "<li_lecVal species=\"ACRU\">0.399</li_lecVal>"
       << "<li_lecVal species=\"ACSA\">0.399</li_lecVal>"
       << "<li_lecVal species=\"BEAL\">0.399</li_lecVal>"
       << "</li_lightExtinctionCoefficient>"
       << "</GeneralLight>"
       << "<QuadratLight1>"
       << "<li_heightOfFishEyePhoto>0</li_heightOfFishEyePhoto>"
       << "<li_quadratAllGLIs>0</li_quadratAllGLIs>"
       << "<li_minSunAngle>0.779</li_minSunAngle>"
       << "<li_numAltGrids>12</li_numAltGrids>"
       << "<li_numAziGrids>18</li_numAziGrids>"
       << "<li_quadratLightHeight>0.675</li_quadratLightHeight>"
       << "</QuadratLight1>"
       << "<output>"
       << "<ou_filename>testoutput1</ou_filename>"
       << "<ou_treeInfo species=\"ACRU\" type=\"Seedling\">"
       << "<ou_saveFreq>1</ou_saveFreq>"
       << "<ou_float>X</ou_float>"
       << "<ou_float>Y</ou_float>"
       << "<ou_float>Diam10</ou_float>"
       << "<ou_float>Height</ou_float>"
       << "</ou_treeInfo>"
       << "<ou_treeInfo species=\"ACRU\" type=\"Sapling\">"
       << "<ou_saveFreq>1</ou_saveFreq>"
       << "<ou_float>X</ou_float>"
       << "<ou_float>Y</ou_float>"
       << "<ou_float>Diam10</ou_float>"
       << "<ou_float>DBH</ou_float>"
       << "<ou_float>Height</ou_float>"
       << "</ou_treeInfo>"
       << "<ou_treeInfo species=\"ACRU\" type=\"Adult\">"
       << "<ou_saveFreq>1</ou_saveFreq>"
       << "<ou_float>X</ou_float>"
       << "<ou_float>Y</ou_float>"
       << "<ou_float>DBH</ou_float>"
       << "<ou_float>Height</ou_float>"
       << "</ou_treeInfo>"
       << "<ou_treeInfo species=\"ACSA\" type=\"Seedling\">"
       << "<ou_saveFreq>1</ou_saveFreq>"
       << "<ou_float>X</ou_float>"
       << "<ou_float>Y</ou_float>"
       << "<ou_float>Diam10</ou_float>"
       << "<ou_float>Height</ou_float>"
       << "</ou_treeInfo>"
       << "<ou_treeInfo species=\"ACSA\" type=\"Sapling\">"
       << "<ou_saveFreq>1</ou_saveFreq>"
       << "<ou_float>X</ou_float>"
       << "<ou_float>Y</ou_float>"
       << "<ou_float>Diam10</ou_float>"
       << "<ou_float>DBH</ou_float>"
       << "<ou_float>Height</ou_float>"
       << "</ou_treeInfo>"
       << "<ou_treeInfo species=\"ACSA\" type=\"Adult\">"
       << "<ou_saveFreq>1</ou_saveFreq>"
       << "<ou_float>X</ou_float>"
       << "<ou_float>Y</ou_float>"
       << "<ou_float>DBH</ou_float>"
       << "<ou_float>Height</ou_float>"
       << "</ou_treeInfo>"
       << "<ou_treeInfo species=\"BEAL\" type=\"Seedling\">"
       << "<ou_saveFreq>1</ou_saveFreq>"
       << "<ou_float>X</ou_float>"
       << "<ou_float>Y</ou_float>"
       << "<ou_float>Diam10</ou_float>"
       << "<ou_float>Height</ou_float>"
       << "</ou_treeInfo>"
       << "<ou_treeInfo species=\"BEAL\" type=\"Sapling\">"
       << "<ou_saveFreq>1</ou_saveFreq>"
       << "<ou_float>X</ou_float>"
       << "<ou_float>Y</ou_float>"
       << "<ou_float>Diam10</ou_float>"
       << "<ou_float>DBH</ou_float>"
       << "<ou_float>Height</ou_float>"
       << "</ou_treeInfo>"
       << "<ou_treeInfo species=\"BEAL\" type=\"Adult\">"
       << "<ou_saveFreq>1</ou_saveFreq>"
       << "<ou_float>X</ou_float>"
       << "<ou_float>Y</ou_float>"
       << "<ou_float>DBH</ou_float>"
       << "<ou_float>Height</ou_float>"
       << "</ou_treeInfo>"
       << "<ou_gridInfo gridName=\"Quadrat GLI\">"
       << "<ou_saveFreq>1</ou_saveFreq>"
       << "<ou_float>GLI</ou_float>"
       << "</ou_gridInfo>"
       << "</output>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}
