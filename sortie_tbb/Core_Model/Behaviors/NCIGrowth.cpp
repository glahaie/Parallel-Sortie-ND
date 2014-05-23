//---------------------------------------------------------------------------
#include "NCIGrowth.h"
#include "TreePopulation.h"
#include "SimManager.h"
#include "ParsingFunctions.h"
#include "Plot.h"
#include "GrowthOrg.h"
#include "Allometry.h"
#include <stdio.h>

//////////////////////////////////////////////////////////////////////////////
// Constructor
//////////////////////////////////////////////////////////////////////////////
clNCIGrowth::clNCIGrowth(clSimManager * p_oSimManager) :
  clWorkerBase(p_oSimManager), clBehaviorBase(p_oSimManager),
      clGrowthBase(p_oSimManager) {
  try
  {
    //Set namestring
    strcpy( m_cNameString, "ncigrowthshell" );
    m_sXMLRoot = "NCIGrowth";

    //Null out our pointers
    mp_iGrowthCodes = NULL;

    //Version 2
    m_fVersionNumber = 2.1;
    m_fMinimumVersionNumber = 2.0;
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
    strcpy( stcErr.cFunction, "clNciGrowth::clNciGrowth" );
    throw( stcErr );
  }
}

////////////////////////////////////////////////////////////////////////////
// Destructor
////////////////////////////////////////////////////////////////////////////
clNCIGrowth::~clNCIGrowth() {
  if (mp_iGrowthCodes) {
    for (int i = 0; i < m_iNumBehaviorSpecies; i++) {
      delete[] mp_iGrowthCodes[i];
    }
    delete[] mp_iGrowthCodes;
  }
  delete[] mp_iWhatBehaviorTypes;
}

////////////////////////////////////////////////////////////////////////////
// ReadParameterFile()
////////////////////////////////////////////////////////////////////////////
void clNCIGrowth::ReadParameterFile(xercesc::DOMDocument * p_oDoc) {
  try
  {
    clTreePopulation * p_oPop = ( clTreePopulation * ) mp_oSimManager->GetPopulationObject( "treepopulation" );
    DOMElement * p_oElement = GetParentParametersElement(p_oDoc);
    floatVal * p_fTempValues; //for getting species-specific values
    char cName[100];
    short int i, j; //loop counters

    //If any of the types is seedling, error out
    for ( i = 0; i < m_iNumSpeciesTypeCombos; i++ )
    if ( clTreePopulation::sapling != mp_whatSpeciesTypeCombos[i].iType
        && clTreePopulation::adult != mp_whatSpeciesTypeCombos[i].iType )
    {
      modelErr stcErr;
      stcErr.iErrorCode = BAD_DATA;
      strcpy( stcErr.cFunction, "clNciGrowth::ReadParameterFile" );
      strcpy( stcErr.cMoreInfo, "This behavior can only be applied to saplings and adults." );
      throw( stcErr );
    }

    //Make the list of indexes
    for ( i = 0; i < m_iNumBehaviorSpecies; i++ )
    mp_iIndexes[mp_iWhatSpecies[i]] = i;

    //Set up our floatVal array that will extract values only for the species
    //assigned to this behavior
    p_fTempValues = new floatVal[m_iNumBehaviorSpecies];
    for ( i = 0; i < m_iNumBehaviorSpecies; i++ )
    p_fTempValues[i].code = mp_iWhatSpecies[i];

    //Fill the variables

    //*************************************
    // General parameters
    //*************************************
    //Maximum potential growth
    FillSpeciesSpecificValue( p_oElement, "gr_nciMaxPotentialGrowth", "gr_nmpgVal", p_fTempValues,
        m_iNumBehaviorSpecies, p_oPop, true );
    //Transfer to the appropriate array buckets
    for ( i = 0; i < m_iNumBehaviorSpecies; i++ )
    mp_fMaxPotentialValue[mp_iIndexes[p_fTempValues[i].code]] = p_fTempValues[i].val;

    //*************************************
    // Crowding effect parameters
    //*************************************
    //Max crowding radius
    FillSpeciesSpecificValue( p_oElement, "gr_nciMaxCrowdingRadius", "gr_nmcrVal", p_fTempValues,
        m_iNumBehaviorSpecies, p_oPop, true );
    //Transfer to the appropriate array buckets
    for ( i = 0; i < m_iNumBehaviorSpecies; i++ )
    mp_fMaxCrowdingRadius[mp_iIndexes[p_fTempValues[i].code]] = p_fTempValues[i].val;

    //Neighbor DBH effect (alpha)
    FillSpeciesSpecificValue( p_oElement, "gr_nciAlpha", "gr_naVal", p_fTempValues, m_iNumBehaviorSpecies, p_oPop, true );
    //Transfer to the appropriate array buckets
    for ( i = 0; i < m_iNumBehaviorSpecies; i++ )
    mp_fAlpha[mp_iIndexes[p_fTempValues[i].code]] = p_fTempValues[i].val;

    //Neighbor distance effect (beta)
    FillSpeciesSpecificValue( p_oElement, "gr_nciBeta", "gr_nbVal", p_fTempValues, m_iNumBehaviorSpecies, p_oPop, true );
    //Transfer to the appropriate array buckets
    for ( i = 0; i < m_iNumBehaviorSpecies; i++ )
    mp_fBeta[mp_iIndexes[p_fTempValues[i].code]] = p_fTempValues[i].val;

    //Size sensitivity to NCI parameter (gamma)
    FillSpeciesSpecificValue( p_oElement, "gr_nciSizeSensNCI", "gr_nssnVal", p_fTempValues,
        m_iNumBehaviorSpecies, p_oPop, true );
    //Transfer to the appropriate array buckets
    for ( i = 0; i < m_iNumBehaviorSpecies; i++ )
    mp_fGamma[mp_iIndexes[p_fTempValues[i].code]] = p_fTempValues[i].val;

    //Lambda
    for ( i = 0; i < m_iNumTotalSpecies; i++ )
    {
      sprintf( cName, "%s%s%s", "gr_nci", p_oPop->TranslateSpeciesCodeToName( i ), "NeighborLambda" );
      FillSpeciesSpecificValue( p_oElement, cName, "gr_nlVal", p_fTempValues, m_iNumBehaviorSpecies, p_oPop, true );
      for ( j = 0; j < m_iNumBehaviorSpecies; j++ )
      {
        mp_fLambda[mp_iIndexes[p_fTempValues[j].code]] [i] = p_fTempValues[j].val;
      }
    }

    //Minimum neighbor DBH
    FillSpeciesSpecificValue( p_oElement, "gr_nciMinNeighborDBH", "gr_nmndVal", mp_fMinimumNeighborDBH, p_oPop, true );

    //Crowding Slope (C)
    FillSpeciesSpecificValue( p_oElement, "gr_nciCrowdingSlope", "gr_ncslVal", p_fTempValues,
        m_iNumBehaviorSpecies, p_oPop, true );
    //Transfer to the appropriate array buckets
    for ( i = 0; i < m_iNumBehaviorSpecies; i++ )
    mp_fCrowdingSlope[mp_iIndexes[p_fTempValues[i].code]] = p_fTempValues[i].val;

    //Crowding Steepness (D)
    FillSpeciesSpecificValue( p_oElement, "gr_nciCrowdingSteepness", "gr_ncstVal", p_fTempValues,
        m_iNumBehaviorSpecies, p_oPop, true );
    //Transfer to the appropriate array buckets
    for ( i = 0; i < m_iNumBehaviorSpecies; i++ )
    mp_fCrowdingSteepness[mp_iIndexes[p_fTempValues[i].code]] = p_fTempValues[i].val;

    //Neighbor storm effect - medium damage - not required if not using
    //storms; pre-fill with 1 (no damage) in case it's not in the parameter file
    for ( i = 0; i < m_iNumBehaviorSpecies; i++ )
    {
      mp_fMedDamageEta[i] = 1.0;
    }
    FillSpeciesSpecificValue( p_oElement, "gr_nciNeighStormEffMedDmg", "gr_nnsemdVal", p_fTempValues,
        m_iNumBehaviorSpecies, p_oPop, false );
    //Transfer to the appropriate array buckets
    for ( i = 0; i < m_iNumBehaviorSpecies; i++ )
    mp_fMedDamageEta[mp_iIndexes[p_fTempValues[i].code]] = p_fTempValues[i].val;

    //Neighbor storm effect - full damage - not required if not using
    //storms; pre-fill with 1 (no damage) in case it's not in the parameter file
    for ( i = 0; i < m_iNumBehaviorSpecies; i++ )
    {
      mp_fFullDamageEta[i] = 1.0;
    }
    FillSpeciesSpecificValue( p_oElement, "gr_nciNeighStormEffFullDmg", "gr_nnsefdVal", p_fTempValues,
        m_iNumBehaviorSpecies, p_oPop, false );
    //Transfer to the appropriate array buckets
    for ( i = 0; i < m_iNumBehaviorSpecies; i++ )
    mp_fFullDamageEta[mp_iIndexes[p_fTempValues[i].code]] = p_fTempValues[i].val;

    //NCI DBH divisor
    FillSingleValue( p_oElement, "gr_nciDbhDivisor", & m_fDbhDivisor, true );

    //Whether to include snags
    FillSingleValue( p_oElement, "gr_nciIncludeSnagsInNCI", & m_bIncludeSnags, true );

    //*************************************
    // Size effect parameters
    //*************************************
    //Size effect mode (X0)
    FillSpeciesSpecificValue( p_oElement, "gr_nciSizeEffectMode", "gr_nsemVal", p_fTempValues,
        m_iNumBehaviorSpecies, p_oPop, true );
    //Transfer to the appropriate array buckets
    for ( i = 0; i < m_iNumBehaviorSpecies; i++ )
    mp_fX0[mp_iIndexes[p_fTempValues[i].code]] = p_fTempValues[i].val;

    //Size effect variance (Xb)
    FillSpeciesSpecificValue( p_oElement, "gr_nciSizeEffectVariance", "gr_nsevVal", p_fTempValues,
        m_iNumBehaviorSpecies, p_oPop, true );
    //Transfer to the appropriate array buckets
    for ( i = 0; i < m_iNumBehaviorSpecies; i++ )
    mp_fXb[mp_iIndexes[p_fTempValues[i].code]] = p_fTempValues[i].val;

    //*************************************
    // Shading effect parameters - not required
    //*************************************
    //Shading coefficient (m) - initialize all values to 0 in case they are
    //not in the parameter file - this turns off shading
    for ( i = 0; i < m_iNumBehaviorSpecies; i++ )
    {
      mp_fShadingCoefficient[i] = 0.0;
      p_fTempValues[i].val = 0.0;
    }
    FillSpeciesSpecificValue( p_oElement, "gr_nciShadingCoefficient", "gr_nscVal", p_fTempValues,
        m_iNumBehaviorSpecies, p_oPop, false );
    //Transfer to the appropriate array buckets
    for ( i = 0; i < m_iNumBehaviorSpecies; i++ )
    mp_fShadingCoefficient[mp_iIndexes[p_fTempValues[i].code]] = p_fTempValues[i].val;

    //Shading exponent (n)
    FillSpeciesSpecificValue( p_oElement, "gr_nciShadingExponent", "gr_nseVal", p_fTempValues,
        m_iNumBehaviorSpecies, p_oPop, false );
    //Transfer to the appropriate array buckets
    for ( i = 0; i < m_iNumBehaviorSpecies; i++ )
    mp_fShadingExponent[mp_iIndexes[p_fTempValues[i].code]] = p_fTempValues[i].val;

    //*************************************
    // Damage effect parameters - not required
    //*************************************
    //Initialize all values to 1 (no damage) in case they aren't in the
    //parameter file
    for ( i = 0; i < m_iNumBehaviorSpecies; i++ )
    {
      mp_fMedDamageStormEff[i] = 1.0;
      mp_fFullDamageStormEff[i] = 1.0;
      p_fTempValues[i].val = 1.0;
    }

    //Storm effect - medium damage
    FillSpeciesSpecificValue( p_oElement, "gr_nciStormEffMedDmg", "gr_nsemdVal", p_fTempValues,
        m_iNumBehaviorSpecies, p_oPop, false );
    //Transfer to the appropriate array buckets
    for ( i = 0; i < m_iNumBehaviorSpecies; i++ )
    mp_fMedDamageStormEff[mp_iIndexes[p_fTempValues[i].code]] = p_fTempValues[i].val;

    //Storm effect - full damage
    FillSpeciesSpecificValue( p_oElement, "gr_nciStormEffFullDmg", "gr_nsefdVal", p_fTempValues,
        m_iNumBehaviorSpecies, p_oPop, false );
    //Transfer to the appropriate array buckets
    for ( i = 0; i < m_iNumBehaviorSpecies; i++ )
    mp_fFullDamageStormEff[mp_iIndexes[p_fTempValues[i].code]] = p_fTempValues[i].val;

    delete[] p_fTempValues;
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
    strcpy( stcErr.cFunction, "clNciGrowth::ReadParameterFile" );
    throw( stcErr );
  }
}

////////////////////////////////////////////////////////////////////////////
// ValidateData
////////////////////////////////////////////////////////////////////////////
void clNCIGrowth::ValidateData() {
  try
  {

    int i;
    for ( i = 0; i < m_iNumBehaviorSpecies; i++ )
    {

      //Make sure that the max radius of neighbor effects is > 0
      if ( mp_fMaxCrowdingRadius[i] < 0 )
      {
        modelErr stcErr;
        strcpy( stcErr.cMoreInfo, "All values for max crowding radius must be greater than 0." );
        throw( stcErr );
      }

      //Make sure that the maximum growth for each species is > 0
      if ( mp_fMaxPotentialValue[i] <= 0 )
      {
        modelErr stcErr;
        strcpy( stcErr.cMoreInfo, "All values for max potential growth must be greater than 0." );
        throw( stcErr );
      }

      //Make sure that the size effect mode is not 0
      if ( 0 >= mp_fX0[i] )
      {
        modelErr stcErr;
        strcpy( stcErr.cMoreInfo, "Size effect mode values must be greater than 0." );
        throw( stcErr );
      }

      //Make sure that the size effect variance is not 0
      if ( 0 == mp_fXb[i] )
      {
        modelErr stcErr;
        strcpy( stcErr.cMoreInfo, "Size effect variance values cannot be 0." );
        throw( stcErr );
      }

      //Make sure that the storm effect values are between 0 and 1
      if ( 0 > mp_fMedDamageStormEff[i] || mp_fMedDamageStormEff[i] > 1 )
      {
        modelErr stcErr;
        strcpy( stcErr.cMoreInfo, "Storm effect values must be between 0 and 1." );
        throw( stcErr );
      }

      if ( 0 > mp_fFullDamageStormEff[i] || mp_fFullDamageStormEff[i] > 1 )
      {
        modelErr stcErr;
        strcpy( stcErr.cMoreInfo, "Storm effect values must be between 0 and 1." );
        throw( stcErr );
      }

      //Make sure that the neighbor storm effect values are between 0 and 1
      if ( 0 > mp_fMedDamageEta[i] || mp_fMedDamageEta[i] > 1 )
      {
        modelErr stcErr;
        strcpy( stcErr.cMoreInfo, "Neighbor storm effect values must be between 0 and 1." );
        throw( stcErr );
      }

      if ( 0 > mp_fFullDamageEta[i] || mp_fFullDamageEta[i] > 1 )
      {
        modelErr stcErr;
        strcpy( stcErr.cMoreInfo, "Neighbor storm effect values must be between 0 and 1." );
        throw( stcErr );
      }
    }

    for ( i = 0; i < m_iNumTotalSpecies; i++ )
    {
      //Make sure that the minimum neighbor DBH is not negative
      if ( 0 > mp_fMinimumNeighborDBH[i] )
      {
        modelErr stcErr;
        strcpy( stcErr.cMoreInfo, "Minimum neighbor DBH for NCI cannot be less than 0." );
        throw( stcErr );
      }
    }

    //Make sure the DBH divisor is greater than 0
    if ( m_fDbhDivisor <= 0 )
    {
      modelErr stcErr;
      strcpy( stcErr.cMoreInfo, "The NCI DBH divisor must be greater than 0." );
      throw( stcErr );
    }

    //Make sure all species/type combos that use shading have "Light" registered
    for ( i = 0; i < m_iNumSpeciesTypeCombos; i++ )
    {
      if ( 0 != mp_fShadingCoefficient[mp_iIndexes[mp_whatSpeciesTypeCombos[i].iSpecies]] )
      {
        if ( -1 == mp_oGrowthOrg->GetLightCode( mp_whatSpeciesTypeCombos[i].iSpecies, mp_whatSpeciesTypeCombos[i].iType ) )
        {
          modelErr stcErr;
          strcpy( stcErr.cFunction, "clNciGrowth::DoShellSetup" );
          sprintf( stcErr.cMoreInfo, "%s%d%s%d%s", "Type/species combo species=", mp_whatSpeciesTypeCombos[i].iSpecies,
              " type=", mp_whatSpeciesTypeCombos[i].iType, " does not have a required light behavior." );
          stcErr.iErrorCode = BAD_DATA;
          throw( stcErr );
        }
      }
    }
  }
  catch ( modelErr & err )
  {
    strcpy( err.cFunction, "clNciGrowth::ValidateData" );
    err.iErrorCode = BAD_DATA;
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
    strcpy( stcErr.cFunction, "clNciGrowth::ValidateData" );
    throw( stcErr );
  }
}

////////////////////////////////////////////////////////////////////////////
// GetTreeMemberCodes()
////////////////////////////////////////////////////////////////////////////
void clNCIGrowth::GetTreeMemberCodes() {
  clTreePopulation
      * p_oPop =
          ( clTreePopulation * ) mp_oSimManager->GetPopulationObject("treepopulation");
  int i, j, iNumTypes = p_oPop->GetNumberOfTypes();
  bool bUsed = false;

  //See if damage is used at all
  for (i = 0; i < m_iNumBehaviorSpecies; i++) {
    if (mp_fMedDamageStormEff[i] < 1 || mp_fFullDamageStormEff[i] < 1
        || mp_fMedDamageEta[i] < 1 || mp_fFullDamageEta[i] < 1) {
      bUsed = true;
      break;
    }
  }

  if ( true == bUsed) {
    mp_iDamageCodes = new short int * [m_iNumTotalSpecies];
    for (i = 0; i < m_iNumTotalSpecies; i++) {
      mp_iDamageCodes[i] = new short int[iNumTypes];
      for (j = 0; j < iNumTypes; j++)
        mp_iDamageCodes[i][j] = -1;

      mp_iDamageCodes[i] [clTreePopulation::sapling] = p_oPop->GetIntDataCode(
          "stm_dmg", i, clTreePopulation::sapling);
      mp_iDamageCodes[i] [clTreePopulation::adult] = p_oPop->GetIntDataCode(
          "stm_dmg", i, clTreePopulation::adult);
      mp_iDamageCodes[i] [clTreePopulation::snag] = p_oPop->GetIntDataCode(
          "stm_dmg", i, clTreePopulation::snag);
    }
  }

  //Get codes for growth
  mp_iGrowthCodes = new short int * [m_iNumBehaviorSpecies];
  for (i = 0; i < m_iNumBehaviorSpecies; i++) {
    mp_iGrowthCodes[i] = new short int[2];
    for (j = 0; j < 2; j++) {
      mp_iGrowthCodes[i][j] = -1;
    }
  }

  for (i = 0; i < m_iNumSpeciesTypeCombos; i++) {

    //Get the code from growth org
    mp_iGrowthCodes[mp_iIndexes[mp_whatSpeciesTypeCombos[i].iSpecies]]
    [mp_whatSpeciesTypeCombos[i].iType - clTreePopulation::sapling]
        = mp_oGrowthOrg->GetGrowthCode(mp_whatSpeciesTypeCombos[i].iSpecies,
            mp_whatSpeciesTypeCombos[i].iType);
  }

  //Is light used at all?
  for (i = 0; i < m_iNumBehaviorSpecies; i++) {
    if (fabs(mp_fShadingCoefficient[i]) >= 0.001) {
      bUsed = true;
      break;
    }
  }

  if (bUsed) {

    //Declare the light codes array
    mp_iLightCodes = new short int * [m_iNumBehaviorSpecies];
    for (i = 0; i < m_iNumBehaviorSpecies; i++) {
      mp_iLightCodes[i] = new short int[2];
    }

    for (i = 0; i < m_iNumSpeciesTypeCombos; i++) {

      //Get the code if this species uses light
      if (fabs(mp_fShadingCoefficient[mp_iIndexes[mp_whatSpeciesTypeCombos[i].iSpecies]])
          >= 0.001) {
        mp_iLightCodes[mp_iIndexes[mp_whatSpeciesTypeCombos[i].iSpecies]] [mp_whatSpeciesTypeCombos[i].iType - clTreePopulation::sapling]
            = p_oPop->GetFloatDataCode("Light",
                mp_whatSpeciesTypeCombos[i].iSpecies,
                mp_whatSpeciesTypeCombos[i].iType);

        if ( -1
            == mp_iLightCodes[mp_iIndexes[mp_whatSpeciesTypeCombos[i].iSpecies]]
            [mp_whatSpeciesTypeCombos[i].iType - clTreePopulation::sapling]) {
          modelErr stcErr;
          strcpy(stcErr.cFunction, "clNCIMort::GetTreeMemberCodes");
          strcpy(
              stcErr.cMoreInfo,
              "All trees to which the shading effect of NCI mortality is used must have a light behavior applied.");
          stcErr.iErrorCode = BAD_DATA;
          throw( stcErr );
        }
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////
// DoShellSetup()
////////////////////////////////////////////////////////////////////////////
void clNCIGrowth::DoShellSetup(xercesc::DOMDocument * p_oDoc) {
  try
  {
    clTreePopulation * p_oPop = ( clTreePopulation * ) mp_oSimManager->GetPopulationObject( "treepopulation" );
    DoNCISetup( p_oPop, m_iNumBehaviorSpecies);
    AssembleUniqueTypes();
    ReadParameterFile( p_oDoc );
    ValidateData();
    GetTreeMemberCodes();
    SetFunctionPointers();

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
    strcpy( stcErr.cFunction, "clNciGrowth::DoShellSetup" );
    throw( stcErr );
  }
}

////////////////////////////////////////////////////////////////////////////
// AssembleUniqueTypes
////////////////////////////////////////////////////////////////////////////
void clNCIGrowth::AssembleUniqueTypes() {
  short int * p_iTypesList, //for assembling the list of unique types
      i, j; //loop counters
  bool bFound; //flag used in assembling list of unique types

  //Declare the temp. types array to be as big as the combo list to make
  //sure we have space for everything, and initialize values to -1
  p_iTypesList = new short int[m_iNumSpeciesTypeCombos];
  for (i = 0; i < m_iNumSpeciesTypeCombos; i++)
    p_iTypesList[i] = -1;

  m_iNumBehaviorTypes = 0;
  //Go through each combo, and for the type for that combo, if it's not
  //already on the temp list, add it
  m_iNumBehaviorTypes = 0;
  for (i = 0; i < m_iNumSpeciesTypeCombos; i++) {
    bFound = false;
    //Test to see if this type is already on the list
    for (j = 0; j < m_iNumBehaviorTypes; j++) {
      if (mp_whatSpeciesTypeCombos[i].iType == p_iTypesList[j]) {
        bFound = true;
        break;
      }
    }
    if ( !bFound) {
      //Add the type to the list and increment the number of found species
      //by one
      p_iTypesList[m_iNumBehaviorTypes] = mp_whatSpeciesTypeCombos[i].iType;
      m_iNumBehaviorTypes++;
    }
  } //end of for (i = 0; i < m_iNumSpeciesTypeCombos; i++)

  mp_iWhatBehaviorTypes = new short int[m_iNumBehaviorTypes];
  for (i = 0; i < m_iNumBehaviorTypes; i++)
    mp_iWhatBehaviorTypes[i] = p_iTypesList[i];

  delete[] p_iTypesList;
}

//////////////////////////////////////////////////////////////////////////////
// SetNameData()
//////////////////////////////////////////////////////////////////////////////
void clNCIGrowth::SetNameData(char * cNameString) {
  try
  {

    //Check the string passed and set the flags accordingly
    if ( strcmp( "NCIGrowth", cNameString ) == 0 )
    {
      m_iGrowthMethod = diameter_auto;
    }
    else if ( strcmp( "NCIGrowth diam only", cNameString ) == 0 )
    {
      m_iGrowthMethod = diameter_only;
    }
    else
    {
      modelErr stcErr;
      stcErr.iErrorCode = BAD_DATA;
      sprintf( stcErr.cMoreInfo, "%s%s%s", "Unrecognized behavior name \"", cNameString, "\"." );
      strcpy( stcErr.cFunction, "clNciGrowth::SetNameData" );
      throw( stcErr );
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
    strcpy( stcErr.cFunction, "clNciGrowth::SetNameData" );
    throw( stcErr );
  }
}


////////////////////////////////////////////////////////////////////////////
// CalcGrowthValue
////////////////////////////////////////////////////////////////////////////
float clNCIGrowth::CalcDiameterGrowthValue(clTree * p_oTree,
    clTreePopulation * p_oPop, float fHeightGrowth) {
  try
  {
    float fAmountDiamIncrease; //amount diameter increase

    //Get the tree's growth - it's already calculated
    p_oTree->GetValue( mp_iGrowthCodes[mp_iIndexes[p_oTree->GetSpecies()]] [p_oTree->GetType() - clTreePopulation::sapling],
        & fAmountDiamIncrease );

    return fAmountDiamIncrease;
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
    strcpy( stcErr.cFunction, "clNciGrowth::CalcDiameterGrowthValue" );
    throw( stcErr );
  }
}

////////////////////////////////////////////////////////////////////////////
// PreGrowthCalcs
////////////////////////////////////////////////////////////////////////////
void clNCIGrowth::PreGrowthCalcs(clTreePopulation * p_oPop) {
  try
  {
#ifdef NCI_WRITER
    using namespace std;
    int iTS = mp_oSimManager->GetCurrentTimestep();
    char cFilename[100];
    sprintf(cFilename, "%s%d%s", "GrowthNCI", iTS, ".txt");
    fstream out( cFilename, ios::trunc | ios::out );
    out << "Timestep\tSpecies\tDBH\tNCI\tSize Effect\tCrowding Effect\tDamage Effect\tGrowth\n";
#endif

    clTreeSearch * p_oNCITrees; //trees that this growth behavior applies to
    clAllometry * p_oAllom = p_oPop->GetAllometryObject();
    clPlot * p_oPlot = mp_oSimManager->GetPlotObject();
    clTree * p_oTree; //a single tree we're working with
    bool * p_bUseGamma = new bool[m_iNumBehaviorSpecies]; //whether or not a
    //species has the DBH^gamma term in its crowding effect
    char cQuery[75], //for searching for trees
    cQueryPiece[5]; //for assembling the search query
    float fDamageEffect, //this tree's damage effect
    fCrowdingEffect, //tree's crowding effect
    fNCI, //the NCI
    fSizeEffect, //tree's size effect
    fShadingEffect, //tree's shading effect
    fDbh, //tree's dbh
    fNumberYearsPerTimestep = mp_oSimManager->GetNumberOfYearsPerTimestep(), fAmountDiamIncrease, //amount diameter increase
    fTempDiamIncrease; //amount diameter increase - intermediate
    int iIsDead;
    short int iSpecies, iType, //type and species of a tree
    i, //loop counter
    iDeadCode; //tree's dead code

    //Populate the use gamma flag array
    for ( i = 0; i < m_iNumBehaviorSpecies; i++ )
    {
      p_bUseGamma[i] = ( fabs( mp_fGamma[i] ) > 0.001 );
    }

    //Do a type/species search on all the types and species
    strcpy( cQuery, "species=" );
    for ( i = 0; i < m_iNumBehaviorSpecies - 1; i++ )
    {
      sprintf( cQueryPiece, "%d%s", mp_iWhatSpecies[i], "," );
      strcat( cQuery, cQueryPiece );
    }
    sprintf( cQueryPiece, "%d", mp_iWhatSpecies[m_iNumBehaviorSpecies - 1] );
    strcat( cQuery, cQueryPiece );

    strcat( cQuery, "::type=" );
    for ( i = 0; i < m_iNumBehaviorTypes - 1; i++ )
    {
      sprintf( cQueryPiece, "%d%s", mp_iWhatBehaviorTypes[i], "," );
      strcat( cQuery, cQueryPiece );
    }
    sprintf( cQueryPiece, "%d", mp_iWhatBehaviorTypes[m_iNumBehaviorTypes - 1] );
    strcat( cQuery, cQueryPiece );

    p_oNCITrees = p_oPop->Find( cQuery );

    //************************************
    // Loop through and to calculate growth for each tree
    //************************************
    p_oTree = p_oNCITrees->NextTree();
    while ( p_oTree )
    {
      iSpecies = p_oTree->GetSpecies();
      iType = p_oTree->GetType();

      if ( -1 != mp_iGrowthCodes[mp_iIndexes[iSpecies]] [iType - clTreePopulation::sapling] )
      {

        //Make sure tree's not dead
        iDeadCode = p_oPop->GetIntDataCode( "dead", p_oTree->GetSpecies(), p_oTree->GetType() );
        if ( -1 != iDeadCode )
        {
          p_oTree->GetValue( iDeadCode, & iIsDead );
        }
        else
        iIsDead = notdead;

        if ( notdead == iIsDead )
        {

          p_oTree->GetValue( p_oPop->GetDbhCode( iSpecies, iType ), & fDbh );

          //First calculate the pieces that have no DBH component and thus will
          //not change in our loop

          //Get NCI
          fNCI = ( * this.*mp_NCI[mp_iIndexes[iSpecies]] ) ( p_oTree, p_oPop, p_oPlot );

          //Get the tree's damage effect
          fDamageEffect = ( * this.*DamageEffect ) ( p_oTree );

          //Get the tree's shading effect
          fShadingEffect = ( * this.*mp_ShadingEffect[mp_iIndexes[iSpecies]] ) ( p_oTree );
          //Make sure it's between 0 and 1
          if ( fShadingEffect < 0 ) fShadingEffect = 0;
          if ( fShadingEffect > 1 ) fShadingEffect = 1;

          //If the tree's species doesn't have the DBH^gamma term in its
          //crowding effect, then we can calculate that now too
          if ( !p_bUseGamma[mp_iIndexes[iSpecies]] )
          {
            fCrowdingEffect = ( * this.*mp_CrowdingEffect[mp_iIndexes[iSpecies]] ) ( fDbh, fNCI, iSpecies );
            //Make sure it's between 0 and 1
            if ( fCrowdingEffect < 0 ) fCrowdingEffect = 0;
            if ( fCrowdingEffect > 1 ) fCrowdingEffect = 1;
          }

          //To correctly compound growth over the number of years per timestep,
          //we have to loop over the number of years, re-calculating the parts
          //with DBH and incrementing the DBH each time
          fAmountDiamIncrease = 0;
          for ( i = 0; i < fNumberYearsPerTimestep; i++ )
          {

            //If the crowding effect term has DBH^gamma, we need to recalculate
            //it with every loop pass, so do that
            if ( p_bUseGamma[mp_iIndexes[iSpecies]] )
            {
              fCrowdingEffect = ( * this.*mp_CrowdingEffect[mp_iIndexes[iSpecies]] ) ( fDbh, fNCI, iSpecies );
              //Make sure it's between 0 and 1
              if ( fCrowdingEffect < 0 ) fCrowdingEffect = 0;
              if ( fCrowdingEffect > 1 ) fCrowdingEffect = 1;
            }

            //Get the tree's size effect
            fSizeEffect = exp( -0.5 * pow( log( fDbh / mp_fX0[mp_iIndexes[iSpecies]] ) / mp_fXb[mp_iIndexes[iSpecies]], 2 ) );

            //Make sure it's bounded between 0 and 1
            if ( fSizeEffect < 0 ) fSizeEffect = 0;
            if ( fSizeEffect > 1 ) fSizeEffect = 1;

            //Calculate actual growth in cm/yr
            fTempDiamIncrease = mp_fMaxPotentialValue[mp_iIndexes[iSpecies]] * fSizeEffect * fCrowdingEffect
            * fShadingEffect * fDamageEffect;

            //Add it to the running total of diameter increase
            fAmountDiamIncrease += fTempDiamIncrease;

            //Increase the DBH for the next loop.  If this is a sapling,
            //convert to a dbh value from what would be a diam10 increase
            if ( clTreePopulation::sapling == iType )
            {
              fDbh += p_oAllom->ConvertDiam10ToDbh( fTempDiamIncrease, iSpecies );
            }
            else
            {
              fDbh += fTempDiamIncrease;
            }
          }

          //Assign the growth back to "Growth" and hold it
          p_oTree->SetValue( mp_iGrowthCodes[mp_iIndexes[iSpecies]] [iType - clTreePopulation::sapling], fAmountDiamIncrease );

#ifdef NCI_WRITER
          //if (p_oTree->GetSpecies() == 8) {
            p_oTree->GetValue( p_oPop->GetDbhCode( iSpecies, iType ), & fDbh );
            out << iTS << "\t" << p_oTree->GetSpecies() << "\t" << fDbh
                << "\t" << fNCI << "\t" << fSizeEffect << "\t" << fCrowdingEffect
                << "\t" << fDamageEffect << "\t" << fAmountDiamIncrease << "\n";
          //}
#endif

        } //end of if (bIsNCITree)
      }

      p_oTree = p_oNCITrees->NextTree();
    }

#ifdef NCI_WRITER
    out.close();
#endif

    delete[] p_bUseGamma;
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
    strcpy( stcErr.cFunction, "clNciGrowth::PreCalcGrowth" );
    throw( stcErr );
  }
}
