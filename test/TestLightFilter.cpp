//---------------------------------------------------------------------------
// TestLightFilter.cpp
//---------------------------------------------------------------------------

#include <fstream>
#include <math.h>
#include "TestLightFilter.h"
#include "TreePopulation.h"
#include "TreeSearch.h"
#include "SimManager.h"
#include "BehaviorBase.h"
#include <cppunit/Asserter.h>

/////////////////////////////////////////////////////////////////////////////
// TestLightFiltering()
/////////////////////////////////////////////////////////////////////////////
void clTestLightFilter::TestLightFiltering()
{

  try
  {
    clSimManager * p_oSimManager = new clSimManager( 3, 3, "" );

    //Feed our file to the sim manager
    p_oSimManager->ReadFile( WriteXMLFile1() );

    clTreePopulation *p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject("treepopulation");

    //Fake the tree initial conditions
    SetTreeValues( p_oPop );

    //Now call light filtering - it's the second behavior
    p_oSimManager->GetBehaviorObject( 1 )->Action();

    //Verify file 1
    VerifyXMLFile1( p_oPop );

    //Now exception processing - write the error file and expect to catch an
    //error
    try
    {
      p_oSimManager->ReadFile( WriteXMLErrorFile1() );
      CppUnit::Asserter::fail( "TestLightFilter error processing didn't catch error for WriteXMLErrorFile1." );
    }
    catch ( modelErr& err )
    {
      if ( strstr( err.cFunction, "clLightFilter::GetData" ) == NULL )
      {
        CppUnit::Asserter::fail( "TestLightFilter error processing caught wrong error for WriteXMLErrorFile1." );
      }
      ;
    }

    //Clean up
    delete p_oSimManager;
  }
  catch ( modelErr & err )
  {
    std::string sMsg = "TestLightFiltering failed with message ";
    sMsg.append( err.cMoreInfo );
    CppUnit::Asserter::fail( sMsg );
  }
}


///////////////////////////////////////////////////////////////////////////
// VerifyValues()
////////////////////////////////////////////////////////////////////////////
void clTestLightFilter::VerifyXMLFile1( clTreePopulation * p_oPop )
{

  clTreeSearch * p_oAllTrees = p_oPop->Find( "all" );
  clTree * p_oTree = p_oAllTrees->NextTree();
  int iSp, iTp, iCounter;
  float fX, fLight;

  while ( p_oTree )
  {

    //Get the X and light values
    iSp = p_oTree->GetSpecies();
    iTp = p_oTree->GetType();

    p_oTree->GetValue( p_oPop->GetFloatDataCode( "Light", iSp, iTp ), & fLight );
    p_oTree->GetValue( p_oPop->GetXCode( iSp, iTp ), & fX );

    //Verify each tree - identified by its X coord
    if ( 1 == fX )
    {
      //Get the counter value
      p_oTree->GetValue( p_oPop->GetIntDataCode( "lf_count", iSp, iTp ), & iCounter );

      CPPUNIT_ASSERT( 1 == iCounter );
      CPPUNIT_ASSERT( 87 == fLight );
    }
    else if ( 2 == fX )
    {
      //Make sure there's no counter or Z
      CPPUNIT_ASSERT( -1 == p_oPop->GetIntDataCode( "z", iSp, iTp ) );
      CPPUNIT_ASSERT( -1 == p_oPop->GetIntDataCode( "lf_count", iSp, iTp ) );
      CPPUNIT_ASSERT( 67 == fLight );
    }
    else if ( 3 == fX )
    {
      //Get the counter value
      p_oTree->GetValue( p_oPop->GetIntDataCode( "lf_count", iSp, iTp ), & iCounter );

      CPPUNIT_ASSERT( 0 == iCounter );
      CPPUNIT_ASSERT( ( fabs( 13.16311656 - fLight ) / fLight ) < 0.01 );
    }
    else if ( 4 == fX )
    {
      //Get the counter value
      p_oTree->GetValue( p_oPop->GetIntDataCode( "lf_count", iSp, iTp ), & iCounter );

      CPPUNIT_ASSERT( 0 == iCounter );
      CPPUNIT_ASSERT( ( fabs( 67.60685892 - fLight ) / fLight ) < 0.01 );
    }
    else if ( 5 == fX )
    {
      //Get the counter value
      p_oTree->GetValue( p_oPop->GetIntDataCode( "lf_count", iSp, iTp ), & iCounter );

      CPPUNIT_ASSERT( 0 == iCounter );
      CPPUNIT_ASSERT( 34 == fLight );
    }
    else if ( 6 == fX )
    {
      //Get the counter value
      p_oTree->GetValue( p_oPop->GetIntDataCode( "lf_count", iSp, iTp ), & iCounter );

      CPPUNIT_ASSERT( 0 == iCounter );
      CPPUNIT_ASSERT( ( fabs( 26.85279333 - fLight ) / fLight ) < 0.01 );
    }
    else
    {
      //Make a false assertion to fail the test
      CPPUNIT_ASSERT( 0 == 1 );
    }

    p_oTree = p_oAllTrees->NextTree();
  }
}


///////////////////////////////////////////////////////////////////////////
// SetTreeValues()
////////////////////////////////////////////////////////////////////////////
void clTestLightFilter::SetTreeValues( clTreePopulation * p_oPop )
{
  clTreeSearch * p_oAllTrees = p_oPop->Find( "all" );
  clTree * p_oTree = p_oAllTrees->NextTree();
  int iSp, iTp;
  float fX, fLight;

  while ( p_oTree )
  {

    //Get the X value
    iSp = p_oTree->GetSpecies();
    iTp = p_oTree->GetType();

    p_oTree->GetValue( p_oPop->GetXCode( iSp, iTp ), & fX );

    //Find the tree by its X and Y coords
    if ( 1 == fX )
    {

      fLight = 87;
      p_oTree->SetValue( p_oPop->GetFloatDataCode( "Light", iSp, iTp ), fLight );
      p_oTree->SetValue( p_oPop->GetIntDataCode( "z", iSp, iTp ), 345 );
      p_oTree->SetValue( p_oPop->GetIntDataCode( "lf_count", iSp, iTp ), 3 );

    }
    else if ( 2 == fX )
    {

      fLight = 67;
      p_oTree->SetValue( p_oPop->GetFloatDataCode( "Light", iSp, iTp ), fLight );

    }
    else if ( 3 == fX )
    {

      fLight = 52;
      p_oTree->SetValue( p_oPop->GetFloatDataCode( "Light", iSp, iTp ), fLight );
      p_oTree->SetValue( p_oPop->GetIntDataCode( "z", iSp, iTp ), 5 );
      p_oTree->SetValue( p_oPop->GetIntDataCode( "lf_count", iSp, iTp ), 0 );

    }
    else if ( 4 == fX )
    {

      fLight = 73;
      p_oTree->SetValue( p_oPop->GetFloatDataCode( "Light", iSp, iTp ), fLight );
      p_oTree->SetValue( p_oPop->GetIntDataCode( "z", iSp, iTp ), 150 );
      p_oTree->SetValue( p_oPop->GetIntDataCode( "lf_count", iSp, iTp ), 0 );

    }
    else if ( 5 == fX )
    {

      fLight = 34;
      p_oTree->SetValue( p_oPop->GetFloatDataCode( "Light", iSp, iTp ), fLight );
      p_oTree->SetValue( p_oPop->GetIntDataCode( "z", iSp, iTp ), 4000 );
      p_oTree->SetValue( p_oPop->GetIntDataCode( "lf_count", iSp, iTp ), 0 );

    }
    else if ( 6 == fX )
    {

      fLight = 99;
      p_oTree->SetValue( p_oPop->GetFloatDataCode( "Light", iSp, iTp ), fLight );
      p_oTree->SetValue( p_oPop->GetIntDataCode( "z", iSp, iTp ), 0 );
      p_oTree->SetValue( p_oPop->GetIntDataCode( "lf_count", iSp, iTp ), 0 );

    }
    else
    {
      //Make a false assertion to fail the test
      CPPUNIT_ASSERT( 0 == 1 );
    }

    p_oTree = p_oAllTrees->NextTree();
  }
}


////////////////////////////////////////////////////////////////////////////
// WriteXMLFile1()
////////////////////////////////////////////////////////////////////////////
const char* clTestLightFilter::WriteXMLFile1()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<yearsPerTimestep>2</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>200.0</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\" />"
       << "<tr_species speciesName=\"Species_2\" />"
       << "<tr_species speciesName=\"Species_3\" />"
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
       << "<tr_treemap>"
       << "<tm_treeSettings sp=\"Species_1\" tp=\"1\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"Height\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_2\" tp=\"1\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"Height\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_3\" tp=\"1\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"Height\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tree sp=\"0\" tp=\"1\">"
       << "<fl c=\"0\">1</fl>"
       << "<fl c=\"1\">1</fl>"
       << "<fl c=\"2\">0.56</fl>"
       << "</tree>"
       << "<tree sp=\"1\" tp=\"1\">"
       << "<fl c=\"0\">2</fl>"
       << "<fl c=\"1\">2</fl>"
       << "<fl c=\"2\">1.0</fl>"
       << "</tree>"
       << "<tree sp=\"2\" tp=\"1\">"
       << "<fl c=\"0\">3</fl>"
       << "<fl c=\"1\">3</fl>"
       << "<fl c=\"2\">0.4</fl>"
       << "</tree>"
       << "<tree sp=\"0\" tp=\"1\">"
       << "<fl c=\"0\">4</fl>"
       << "<fl c=\"1\">4</fl>"
       << "<fl c=\"2\">1.1</fl>"
       << "</tree>"
       << "<tree sp=\"2\" tp=\"1\">"
       << "<fl c=\"0\">5</fl>"
       << "<fl c=\"1\">5</fl>"
       << "<fl c=\"2\">0.95</fl>"
       << "</tree>"
       << "<tree sp=\"2\" tp=\"1\">"
       << "<fl c=\"0\">6</fl>"
       << "<fl c=\"1\">6</fl>"
       << "<fl c=\"2\">0.45</fl>"
       << "</tree>"
       << "</tr_treemap>"
       << "</trees>"
       << "<allometry>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_2\">39.54</tr_chVal>"
       << "<tr_chVal species=\"Species_3\">40.0</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_2\">0.0614</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_3\">0.0242</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_3\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">0.5944</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_3\">0.7059</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_3\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.368</tr_sachVal>"
       << "<tr_sachVal species=\"Species_3\">0.464</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_3\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_2\">0.0269</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_3\">0.02871</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_2\">0.0241</tr_soahVal>"
       << "<tr_soahVal species=\"Species_3\">0.0263</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
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
       << "</allometry>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>QuadratLight</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>LightFilter</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<GeneralLight>"
       << "<li_beamFractGlobalRad>0.5</li_beamFractGlobalRad>"
       << "<li_clearSkyTransCoeff>0.65</li_clearSkyTransCoeff>"
       << "<li_julianDayGrowthStarts>105</li_julianDayGrowthStarts>"
       << "<li_julianDayGrowthEnds>258</li_julianDayGrowthEnds>"
       << "<li_lightExtinctionCoefficient>"
       << "<li_lecVal species=\"Species_1\">0.08</li_lecVal>"
       << "<li_lecVal species=\"Species_2\">0.091</li_lecVal>"
       << "<li_lecVal species=\"Species_3\">0.059</li_lecVal>"
       << "</li_lightExtinctionCoefficient>"
       << "</GeneralLight>"
       << "<QuadratLight1>"
       << "<li_heightOfFishEyePhoto>0</li_heightOfFishEyePhoto>"
       << "<li_minSunAngle>0.785</li_minSunAngle>"
       << "<li_numAltGrids>12</li_numAltGrids>"
       << "<li_numAziGrids>18</li_numAziGrids>"
       << "<li_quadratLightHeight>0.675</li_quadratLightHeight>"
       << "<li_quadratAllGLIs>0</li_quadratAllGLIs>"
       << "</QuadratLight1>"
       << "<LightFilter2>"
       << "<lf_lightExtinctionCoefficient>1.535</lf_lightExtinctionCoefficient>"
       << "<lf_heightOfFilter>1.3</lf_heightOfFilter>"
       << "</LightFilter2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteXMLErrorFile1()
////////////////////////////////////////////////////////////////////////////
const char* clTestLightFilter::WriteXMLErrorFile1()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<yearsPerTimestep>2</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>200.0</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\" />"
       << "<tr_species speciesName=\"Species_2\" />"
       << "<tr_species speciesName=\"Species_3\" />"
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
       << "<tr_treemap>"
       << "<tm_treeSettings sp=\"Species_1\" tp=\"1\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"Height\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_2\" tp=\"1\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"Height\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_3\" tp=\"1\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"Height\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tree sp=\"0\" tp=\"1\">"
       << "<fl c=\"0\">1</fl>"
       << "<fl c=\"1\">1</fl>"
       << "<fl c=\"2\">0.56</fl>"
       << "</tree>"
       << "<tree sp=\"1\" tp=\"1\">"
       << "<fl c=\"0\">2</fl>"
       << "<fl c=\"1\">2</fl>"
       << "<fl c=\"2\">1.0</fl>"
       << "</tree>"
       << "<tree sp=\"2\" tp=\"1\">"
       << "<fl c=\"0\">3</fl>"
       << "<fl c=\"1\">3</fl>"
       << "<fl c=\"2\">0.4</fl>"
       << "</tree>"
       << "<tree sp=\"0\" tp=\"1\">"
       << "<fl c=\"0\">4</fl>"
       << "<fl c=\"1\">4</fl>"
       << "<fl c=\"2\">1.1</fl>"
       << "</tree>"
       << "<tree sp=\"2\" tp=\"1\">"
       << "<fl c=\"0\">5</fl>"
       << "<fl c=\"1\">5</fl>"
       << "<fl c=\"2\">0.95</fl>"
       << "</tree>"
       << "<tree sp=\"2\" tp=\"1\">"
       << "<fl c=\"0\">6</fl>"
       << "<fl c=\"1\">6</fl>"
       << "<fl c=\"2\">0.45</fl>"
       << "</tree>"
       << "</tr_treemap>"
       << "</trees>"
       << "<allometry>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_2\">39.54</tr_chVal>"
       << "<tr_chVal species=\"Species_3\">40.0</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_2\">0.0614</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_3\">0.0242</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_3\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">0.5944</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_3\">0.7059</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_3\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.368</tr_sachVal>"
       << "<tr_sachVal species=\"Species_3\">0.464</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_3\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_2\">0.0269</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_3\">0.02871</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_2\">0.0241</tr_soahVal>"
       << "<tr_soahVal species=\"Species_3\">0.0263</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
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
       << "</allometry>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>QuadratLight</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>LightFilter</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<GeneralLight>"
       << "<li_beamFractGlobalRad>0.5</li_beamFractGlobalRad>"
       << "<li_clearSkyTransCoeff>0.65</li_clearSkyTransCoeff>"
       << "<li_julianDayGrowthStarts>105</li_julianDayGrowthStarts>"
       << "<li_julianDayGrowthEnds>258</li_julianDayGrowthEnds>"
       << "<li_lightExtinctionCoefficient>"
       << "<li_lecVal species=\"Species_1\">0.08</li_lecVal>"
       << "<li_lecVal species=\"Species_2\">0.091</li_lecVal>"
       << "<li_lecVal species=\"Species_3\">0.059</li_lecVal>"
       << "</li_lightExtinctionCoefficient>"
       << "</GeneralLight>"
       << "<QuadratLight1>"
       << "<li_heightOfFishEyePhoto>0</li_heightOfFishEyePhoto>"
       << "<li_minSunAngle>0.785</li_minSunAngle>"
       << "<li_numAltGrids>12</li_numAltGrids>"
       << "<li_numAziGrids>18</li_numAziGrids>"
       << "<li_quadratLightHeight>0.675</li_quadratLightHeight>"
       << "<li_quadratAllGLIs>0</li_quadratAllGLIs>"
       << "</QuadratLight1>"
       << "<LightFilter2>"
       << "<lf_lightExtinctionCoefficient>1.535</lf_lightExtinctionCoefficient>"
       << "<lf_heightOfFilter>1.3</lf_heightOfFilter>"
       << "</LightFilter2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}
//---------------------------------------------------------------------------

