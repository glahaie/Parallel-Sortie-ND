//---------------------------------------------------------------------------
// CrownRadiusReporter.cpp
//---------------------------------------------------------------------------
#include "CrownRadiusReporter.h"
#include "TreePopulation.h"
#include "Allometry.h"
#include "SimManager.h"
#include <math.h>

////////////////////////////////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////////////////////////////////
clCrownRadiusReporter::clCrownRadiusReporter(clSimManager * p_oSimManager) :
  clWorkerBase(p_oSimManager), clBehaviorBase(p_oSimManager) {
  try
  {

    strcpy( m_cNameString, "Crown Radius Reporter" );

    mp_iRadiusCodes = NULL;
    m_cQuery = NULL;

    //Versions
    m_fVersionNumber = 1;
    m_fMinimumVersionNumber = 1;

    //Allowed file types
    m_iNumAllowedTypes = 2;
    mp_iAllowedFileTypes = new int[m_iNumAllowedTypes];
    mp_iAllowedFileTypes[0] = parfile;
    mp_iAllowedFileTypes[1] = detailed_output;

    //Indicate that this behavior intends to add one tree float data
    //member
    m_iNewTreeFloats = 1;

  }
  catch ( modelErr & err )
  {
    throw( err );
  }
  catch ( modelMsg & msg )
  {
    throw( msg );
  } //non-fatal error
  catch ( ... )
  {
    modelErr stcErr;
    stcErr.iErrorCode = UNKNOWN;
    strcpy( stcErr.cFunction, "clCrownRadiusReporter::clCrownRadiusReporter" );
    throw( stcErr );
  }
}

////////////////////////////////////////////////////////////////////////////
// Destructor
////////////////////////////////////////////////////////////////////////////
clCrownRadiusReporter::~clCrownRadiusReporter() {
  if (mp_iRadiusCodes) {
    for (int i = 0; i < m_iNumSpecies; i++) {
      delete[] mp_iRadiusCodes[i];
    }
    delete[] mp_iRadiusCodes;
  }

  delete[] m_cQuery;
}

////////////////////////////////////////////////////////////////////////////
// GetData()
////////////////////////////////////////////////////////////////////////////
void clCrownRadiusReporter::GetData(xercesc::DOMDocument * p_oDoc) {
  try
  {
    clTreePopulation * p_oPop = ( clTreePopulation * ) mp_oSimManager->GetPopulationObject( "treepopulation" );
    char * cQueryTemp = new char[( p_oPop->GetNumberOfSpecies() * 4 ) + 50];
    char cQueryPiece[5]; //for assembling the search query
    int i;
    bool bSapling = false, bAdult = false, bSnag = false;

    //Do a type/species search on all the types and species
    strcpy( cQueryTemp, "species=" );
    for ( i = 0; i < m_iNumBehaviorSpecies - 1; i++ )
    {
      sprintf( cQueryPiece, "%d%s", mp_iWhatSpecies[i], "," );
      strcat( cQueryTemp, cQueryPiece );
    }
    sprintf( cQueryPiece, "%d", mp_iWhatSpecies[m_iNumBehaviorSpecies - 1] );
    strcat( cQueryTemp, cQueryPiece );

    //Find all the types
    for ( i = 0; i < m_iNumSpeciesTypeCombos; i++ )
    {
      if ( clTreePopulation::sapling == mp_whatSpeciesTypeCombos[i].iType )
      {
        bSapling = true;
      }
      else if ( clTreePopulation::adult == mp_whatSpeciesTypeCombos[i].iType )
      {
        bAdult = true;
      }
      else if ( clTreePopulation::snag == mp_whatSpeciesTypeCombos[i].iType )
      {
        bSnag = true;
      }
    }
    strcat( cQueryTemp, "::type=" );
    if ( bSapling )
    {
      sprintf( cQueryPiece, "%d%s", clTreePopulation::sapling, "," );
      strcat( cQueryTemp, cQueryPiece );
    }
    if ( bAdult )
    {
      sprintf( cQueryPiece, "%d%s", clTreePopulation::adult, "," );
      strcat( cQueryTemp, cQueryPiece );
    }
    if ( bSnag )
    {
      sprintf( cQueryPiece, "%d%s", clTreePopulation::snag, "," );
      strcat( cQueryTemp, cQueryPiece );
    }

    //Remove the last comma
    cQueryTemp[strlen( cQueryTemp ) - 1] = '\0';

    //Now put it in m_cQuery, sized correctly
    m_cQuery = new char[strlen( cQueryTemp ) + 1];
    strcpy( m_cQuery, cQueryTemp );
    delete[] cQueryTemp;

    Action();

  }
  catch ( modelErr & err )
  {
    throw( err );
  }
  catch ( modelMsg & msg )
  {
    throw( msg );
  } //non-fatal error
  catch ( ... )
  {
    modelErr stcErr;
    stcErr.iErrorCode = UNKNOWN;
    strcpy( stcErr.cFunction, "clCrownRadiusReporter::GetData" );
    throw( stcErr );
  }
}

////////////////////////////////////////////////////////////////////////////
// RegisterTreeDataMembers()
////////////////////////////////////////////////////////////////////////////
void clCrownRadiusReporter::RegisterTreeDataMembers() {

  clTreePopulation
      * p_oPop =
          ( clTreePopulation * ) mp_oSimManager->GetPopulationObject("treepopulation");
  short int i, j, iNumTypes = p_oPop->GetNumberOfTypes();

  m_iNumSpecies = p_oPop->GetNumberOfSpecies();

  //Declare the array and register our new data member
  mp_iRadiusCodes = new short int * [m_iNumSpecies];
  for (i = 0; i < m_iNumSpecies; i++) {
    mp_iRadiusCodes[i] = new short int[iNumTypes];
    for (j = 0; j < iNumTypes; j++) {
      mp_iRadiusCodes[i][j] = -1;
    }
  }

  for (i = 0; i < m_iNumSpeciesTypeCombos; i++) {
    //Make sure that only allowed types have been applied
    if (clTreePopulation::adult != mp_whatSpeciesTypeCombos[i].iType &&
        clTreePopulation::sapling != mp_whatSpeciesTypeCombos[i].iType &&
        clTreePopulation::snag != mp_whatSpeciesTypeCombos[i].iType) {

      modelErr stcErr;
      strcpy(stcErr.cFunction, "clCrownRadiusReporter::RegisterTreeDataMembers");
      strcpy(stcErr.cMoreInfo,
          "The crown radius reporter behavior can only be applied to saplings, adults, and snags.");
      stcErr.iErrorCode = BAD_DATA;
      throw( stcErr );
    }

    //Register the code and capture it
    mp_iRadiusCodes[mp_whatSpeciesTypeCombos[i].iSpecies] [mp_whatSpeciesTypeCombos[i].iType]
        = p_oPop->RegisterFloat("Crown_Radius", mp_whatSpeciesTypeCombos[i].iSpecies,
            mp_whatSpeciesTypeCombos[i].iType);
  }
}

////////////////////////////////////////////////////////////////////////////
// Action()
////////////////////////////////////////////////////////////////////////////
void clCrownRadiusReporter::Action() {
  clTreePopulation
      * p_oPop =
          ( clTreePopulation * ) mp_oSimManager->GetPopulationObject("treepopulation");
  clAllometry *p_oAllom = p_oPop->GetAllometryObject();
  clTreeSearch * p_oBehaviorTrees = p_oPop->Find(m_cQuery);
  clTree * p_oTree;
  float fRad;
  int iSp, iTp;

  try
  {

    p_oTree = p_oBehaviorTrees->NextTree();
    while ( p_oTree )
    {

      iSp = p_oTree->GetSpecies();
      iTp = p_oTree->GetType();

      //Double-check this tree's appropriateness by making sure we have a
      //non -1 return code for the crown radius data member
      if ( -1 != mp_iRadiusCodes[iSp][iTp] )
      {

        //Get the radius
        if (iTp == clTreePopulation::sapling)
          fRad = p_oAllom->CalcSaplingCrownRadius(p_oTree);
        else
          fRad = p_oAllom->CalcAdultCrownRadius(p_oTree);

        //Set the value
        p_oTree->SetValue( mp_iRadiusCodes[iSp][iTp], fRad );

      }

      p_oTree = p_oBehaviorTrees->NextTree();
    }
  }
  catch ( modelErr & err )
  {
    throw( err );
  }
  catch ( modelMsg & msg )
  {
    throw( msg );
  } //non-fatal error
  catch ( ... )
  {
    modelErr stcErr;
    stcErr.iErrorCode = UNKNOWN;
    strcpy( stcErr.cFunction, "clCrownRadiusReporter::Action" );
    throw( stcErr );
  }
}
