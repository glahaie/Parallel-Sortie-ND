//---------------------------------------------------------------------------
// TestConstantGLI.cpp
//---------------------------------------------------------------------------
#include "TestConstantGLI.h"
#include "SimManager.h"
#include "TreePopulation.h"
#include "Plot.h"
#include "ModelMath.h"
#include <math.h>
#include <fstream>

/////////////////////////////////////////////////////////////////////////////
// TestConstantGLI()
/////////////////////////////////////////////////////////////////////////////
void clTestConstantGLI::TestConstantGLI()
{

  clSimManager * p_oSimManager = new clSimManager(3, 3, "");

  TestNormalProcessing(p_oSimManager);
  TestErrorProcessing(p_oSimManager);

  //Clean up
  delete p_oSimManager;
}

////////////////////////////////////////////////////////////////////////////
//  TestErrorProcessing()
////////////////////////////////////////////////////////////////////////////
void clTestConstantGLI::TestErrorProcessing( clSimManager * p_oSimManager )
{
  try
  {
    p_oSimManager->ReadFile( WriteXMLErrorFile1() );
    CppUnit::Asserter::fail( "TestConstantGLI error processing didn't catch error for WriteXMLErrorFile1." );
  }
  catch ( modelErr& err )
  {
    if ( strstr( err.cFunction, "clConstantGLI::DoShellSetup" ) == NULL )
    {
      CppUnit::Asserter::fail( "TestConstantGLI error processing caught wrong error for WriteXMLErrorFile1." );
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile( WriteXMLErrorFile2() );
    CppUnit::Asserter::fail( "TestConstantGLI error processing didn't catch error for WriteXMLErrorFile2." );
  }
  catch ( modelErr& err )
  {
    if ( strstr( err.cFunction, "clConstantGLI::DoShellSetup" ) == NULL )
    {
      CppUnit::Asserter::fail( "TestConstantGLI error processing caught wrong error for WriteXMLErrorFile2." );
    }
    ;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestNormalProcessing()
/////////////////////////////////////////////////////////////////////////////
void clTestConstantGLI::TestNormalProcessing(clSimManager *p_oSimManager)
{
  clTreePopulation *p_oPop;
  clPlot *p_oPlot;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;
  float fActualLight, fExpectedLight, fX, fY, fPlotLengthX, fPlotLengthY,
        fDiam = 15;
  int iSp, iNum, iNumSpecies = 3, iCode;

  //Feed our file to the sim manager
  p_oSimManager->ReadFile(WriteXMLFile1());
  p_oPop = (clTreePopulation*) p_oSimManager->GetPopulationObject("treepopulation");
  p_oPlot = p_oSimManager->GetPlotObject();

  fPlotLengthX = p_oPlot->GetXPlotLength();
  fPlotLengthY = p_oPlot->GetYPlotLength();

  //Create 100 trees of each species scattered randomly around the plot
  for (iSp = 0; iSp < iNumSpecies; iSp++) {
    for (iNum = 0; iNum < 100; iNum++) {
      fX = clModelMath::GetRand() * fPlotLengthX;
      fY = clModelMath::GetRand() * fPlotLengthY;
      p_oPop->CreateTree( fX, fY, iSp, clTreePopulation::adult, fDiam );
    }
  }

  //Run one timestep
  p_oSimManager->RunSim(1);

  //Check that species 1 has a light level of 100, and species 2 and 3 have
  //12.5
  p_oAllTrees = p_oPop->Find("all");
  p_oTree = p_oAllTrees->NextTree();
  while (p_oTree) {
    iCode = p_oPop->GetFloatDataCode("Light", p_oTree->GetSpecies(), p_oTree->GetType());
    if (0 == p_oTree->GetSpecies()) {
      CPPUNIT_ASSERT(-1 == iCode);
    }
    else {
      p_oTree->GetValue(iCode, &fActualLight);
      fExpectedLight = 12.5;
      CPPUNIT_ASSERT(fabs(fActualLight - fExpectedLight) < 0.001);
    }
    p_oTree = p_oAllTrees->NextTree();
  }
}

/////////////////////////////////////////////////////////////////////////////
//  WriteXMLFile1()
/////////////////////////////////////////////////////////////////////////////
const char* clTestConstantGLI::WriteXMLFile1()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>3</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>0</randomSeed>"
       << "<plot_lenX>100</plot_lenX>"
       << "<plot_lenY>100</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>";

  WriteCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>ConstantGLI</behaviorName>"
       << "<applyTo species=\"Species_2\" type=\"Adult\" />"
       << "<applyTo species=\"Species_3\" type=\"Adult\" />"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "</behaviorList>"
       << "<ConstantGLI1>"
       << "<li_constGLI>12.5</li_constGLI>"
       << "</ConstantGLI1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
//  WriteXMLErrorFile1()
/////////////////////////////////////////////////////////////////////////////
const char* clTestConstantGLI::WriteXMLErrorFile1()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>3</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>0</randomSeed>"
       << "<plot_lenX>100</plot_lenX>"
       << "<plot_lenY>100</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>";

  WriteCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>ConstantGLI</behaviorName>"
       << "<applyTo species=\"Species_2\" type=\"Adult\" />"
       << "<applyTo species=\"Species_3\" type=\"Adult\" />"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "</behaviorList>"
       << "<ConstantGLI1>"
       << "<li_constGLI>-12.5</li_constGLI>"
       << "</ConstantGLI1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
//  WriteXMLErrorFile2()
/////////////////////////////////////////////////////////////////////////////
const char* clTestConstantGLI::WriteXMLErrorFile2()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>3</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>0</randomSeed>"
       << "<plot_lenX>100</plot_lenX>"
       << "<plot_lenY>100</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>";

  WriteCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>ConstantGLI</behaviorName>"
       << "<applyTo species=\"Species_2\" type=\"Adult\" />"
       << "<applyTo species=\"Species_3\" type=\"Adult\" />"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "</behaviorList>"
       << "<ConstantGLI1>"
       << "<li_constGLI>122.5</li_constGLI>"
       << "</ConstantGLI1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteCommonStuff()
/////////////////////////////////////////////////////////////////////////////
void clTestConstantGLI::WriteCommonStuff( std::fstream &oOut )
{
  using namespace std;
  oOut << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\"/>"
       << "<tr_species speciesName=\"Species_2\"/>"
       << "<tr_species speciesName=\"Species_3\"/>"
       << "</tr_speciesList>"
       << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_2\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_3\">10.0</tr_madVal>"
       << "</tr_minAdultDBH>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_3\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>"
       << "</trees>"
       << "<allometry>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_2\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_3\">0.0299</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_2\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_3\">39.48</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_2\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_3\">0.0549</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_3\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_3\">0.8008</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_3\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_3\">0.389</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_3\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_2\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_3\">0.03418</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "<tr_whatSeedlingHeightDiam>"
       << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_2\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_3\">0</tr_wsehdVal>"
       << "</tr_whatSeedlingHeightDiam>"
       << "<tr_whatSaplingHeightDiam>"
       << "<tr_wsahdVal species=\"Species_1\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_2\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_3\">0</tr_wsahdVal>"
       << "</tr_whatSaplingHeightDiam>"
       << "<tr_whatAdultHeightDiam>"
       << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_2\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_3\">0</tr_wahdVal>"
       << "</tr_whatAdultHeightDiam>"
       << "<tr_whatAdultCrownRadDiam>"
       << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_2\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_3\">0</tr_wacrdVal>"
       << "</tr_whatAdultCrownRadDiam>"
       << "<tr_whatAdultCrownHeightHeight>"
       << "<tr_wachhVal species=\"Species_1\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_2\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_3\">0</tr_wachhVal>"
       << "</tr_whatAdultCrownHeightHeight>"
       << "<tr_whatSaplingCrownRadDiam>"
       << "<tr_wscrdVal species=\"Species_1\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_2\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_3\">0</tr_wscrdVal>"
       << "</tr_whatSaplingCrownRadDiam>"
       << "<tr_whatSaplingCrownHeightHeight>"
       << "<tr_wschhVal species=\"Species_1\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_2\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_3\">0</tr_wschhVal>"
       << "</tr_whatSaplingCrownHeightHeight>"
       << "</allometry>";
}
