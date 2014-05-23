//---------------------------------------------------------------------------
// CarbonValueCalculator.cpp
//---------------------------------------------------------------------------
#include "CarbonValueCalculator.h"
#include "TreePopulation.h"
#include "SimManager.h"
#include "ParsingFunctions.h"
#include "Grid.h"
#include "Plot.h"
#include "Constants.h"
#include <math.h>

////////////////////////////////////////////////////////////////////////////
// Constructor()
////////////////////////////////////////////////////////////////////////////
clCarbonValueCalculator::clCarbonValueCalculator( clSimManager * p_oSimManager ) : clWorkerBase( p_oSimManager ), clBehaviorBase( p_oSimManager )
{
	try
	{
		//Set the namestring
		strcpy( m_cNameString, "CarbonValueCalculator" );
		m_sXMLRoot = "CarbonValueCalculator";

		//Allowed file types
		m_iNumAllowedTypes = 2;
		mp_iAllowedFileTypes = new int[m_iNumAllowedTypes];
		mp_iAllowedFileTypes[0] = parfile;
		mp_iAllowedFileTypes[1] = detailed_output;

		//Versions
		m_fVersionNumber = 1;
		m_fMinimumVersionNumber = 1;

    //Indicate that this behavior intends to add one tree float data
    //member
    m_iNewTreeFloats = 1;

    mp_fCPercentBiomass = NULL;
    mp_iBiomassCodes = NULL;
    mp_iValueCodes = NULL;
    mp_iCarbonCodes = NULL;
    m_cQuery = NULL;
    mp_iTreeCarbonCodes = NULL;
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
    strcpy( stcErr.cFunction, "clCarbonValueCalculator::clCarbonValueCalculator" );
    throw( stcErr );
  }
}

////////////////////////////////////////////////////////////////////////////
// Destructor()
////////////////////////////////////////////////////////////////////////////
clCarbonValueCalculator::~clCarbonValueCalculator()
{
  int i;

	delete[] mp_fCPercentBiomass;
  delete[] mp_iValueCodes;
  delete[] m_cQuery;
  delete[] mp_iCarbonCodes;

  if ( mp_iBiomassCodes )
    for ( i = 0; i < m_iNumTotalSpecies; i++ )
      delete[] mp_iBiomassCodes[i];
  delete[] mp_iBiomassCodes;

  if ( mp_iTreeCarbonCodes )
    for ( i = 0; i < m_iNumTotalSpecies; i++ )
      delete[] mp_iTreeCarbonCodes[i];
  delete[] mp_iTreeCarbonCodes;
}

/////////////////////////////////////////////////////////////////////////////
// GetParameterFileData()
/////////////////////////////////////////////////////////////////////////////
void clCarbonValueCalculator::GetParameterFileData( xercesc::DOMDocument * p_oDoc, clTreePopulation *p_oPop )
{
  floatVal * p_fTempValues = NULL; //for getting species-specific values
  try {
    DOMElement * p_oElement = GetParentParametersElement(p_oDoc);
    int i;

    //Set up our floatVal array that will extract values only for the species
    //assigned to this behavior
    p_fTempValues = new floatVal[m_iNumBehaviorSpecies];
    for ( i = 0; i < m_iNumBehaviorSpecies; i++ )
      p_fTempValues[i].code = mp_iWhatSpecies[i];

    //Declare our array
    mp_fCPercentBiomass = new float[m_iNumTotalSpecies];

    //Get the parameter file values

    //Percent of biomass that is carbon
    FillSpeciesSpecificValue( p_oElement, "an_carbonPercentBiomassCarbon", "an_cpbcVal", p_fTempValues, m_iNumBehaviorSpecies, p_oPop, true );
    //Transfer to the appropriate array buckets, and
    //convert to proportion; check to make sure it's between 0 and 1
    for ( i = 0; i < m_iNumBehaviorSpecies; i++ ) {
      mp_fCPercentBiomass[p_fTempValues[i].code] = p_fTempValues[i].val / 100.0;
      if (mp_fCPercentBiomass[p_fTempValues[i].code] > 1 ||
          mp_fCPercentBiomass[p_fTempValues[i].code] < 0) {
        modelErr stcErr;
        strcpy( stcErr.cFunction, "clCarbonValueCalculator::GetParameterFileData" );
        strcpy( stcErr.cMoreInfo, "Percent of biomass that is carbon must be between 0 and 100.");
        stcErr.iErrorCode = BAD_DATA;
        throw( stcErr );
      }
    }

    FillSingleValue( p_oElement, "an_carbonPricePerMetricTonCarbon", & m_fPricePerTonCarbon, true );

    delete[] p_fTempValues;
  }
  catch ( modelErr & err )
  {
    delete[] p_fTempValues;
    throw( err );
  }
  catch ( modelMsg & msg )
  {
    delete[] p_fTempValues;
    throw( msg );
  } //non-fatal error
  catch ( ... )
  {
    delete[] p_fTempValues;
    modelErr stcErr;
    stcErr.iErrorCode = UNKNOWN;
    strcpy( stcErr.cFunction, "clCarbonValueCalculator::GetParameterFileData" );
    throw( stcErr );
  }
}

/////////////////////////////////////////////////////////////////////////////
// GetData()
/////////////////////////////////////////////////////////////////////////////
void clCarbonValueCalculator::GetData( xercesc::DOMDocument * p_oDoc )
{
  try
  {
    clTreePopulation * p_oPop = ( clTreePopulation * ) mp_oSimManager->GetPopulationObject( "treepopulation" );

    GetParameterFileData(p_oDoc, p_oPop);
    FormatQueryString(p_oPop);
    SetupGrid();
    GetBiomassCodes(p_oPop);
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
    strcpy( stcErr.cFunction, "clCarbonValueCalculator::GetData" );
    throw( stcErr );
  }
}

/////////////////////////////////////////////////////////////////////////////
// SetupGrid()()
/////////////////////////////////////////////////////////////////////////////
void clCarbonValueCalculator::SetupGrid()
{
  clPlot *p_oPlot = mp_oSimManager->GetPlotObject();
  char cLabel[MAX_GRID_LABEL_SIZE];
  short int i; //loop counter

  //Create the grid with one float data member for each species
  mp_oValueGrid = mp_oSimManager->CreateGrid( "Carbon Value",
                        0,                  //number of ints
                        2 * m_iNumTotalSpecies, //number of floats
                        0,                  //number of chars
                        0,                  //number of bools
                        p_oPlot->GetXPlotLength(), //1 cell for the plot
                        p_oPlot->GetYPlotLength() );

  mp_iValueCodes = new short int[m_iNumTotalSpecies];
  mp_iCarbonCodes = new short int[m_iNumTotalSpecies];
  //Register the data member called "value_x"
  for (i = 0; i < m_iNumTotalSpecies; i++) {
    sprintf(cLabel, "%s%d", "value_", i);
    mp_iValueCodes[i] = mp_oValueGrid->RegisterFloat( cLabel );
  }
  //Register the data member called "carbon_x"
  for (i = 0; i < m_iNumTotalSpecies; i++) {
    sprintf(cLabel, "%s%d", "carbon_", i);
    mp_iCarbonCodes[i] = mp_oValueGrid->RegisterFloat( cLabel );
  }
}

////////////////////////////////////////////////////////////////////////////
// Action()
////////////////////////////////////////////////////////////////////////////
void clCarbonValueCalculator::Action()
{
  try
  {
    clTreePopulation * p_oPop = ( clTreePopulation * ) mp_oSimManager->GetPopulationObject( "treepopulation" );
    clTreeSearch * p_oBehaviorTrees;
    clTree * p_oTree;
    float *p_fSpeciesTotals = new float[m_iNumTotalSpecies];
    float fValue; //tree's value
    int iSp, iTp;

    //Initialize our species totals arrays
    for (iSp = 0; iSp < m_iNumTotalSpecies; iSp++) {
      p_fSpeciesTotals[iSp] = 0;
    }

    //Reset the values in the species total grid to 0
    fValue = 0;
    for (iSp = 0; iSp < m_iNumTotalSpecies; iSp++) {
      mp_oValueGrid->SetValueOfCell(0, 0, mp_iValueCodes[iSp], fValue);
      mp_oValueGrid->SetValueOfCell(0, 0, mp_iCarbonCodes[iSp], fValue);
    }

    //Get the trees that apply to this behavior
    p_oBehaviorTrees = p_oPop->Find( m_cQuery );

    p_oTree = p_oBehaviorTrees->NextTree();
    while ( p_oTree )
    {

      iSp = p_oTree->GetSpecies();
      iTp = p_oTree->GetType() - clTreePopulation::sapling;

      //Double-check this tree's appropriateness by making sure we have a
      //non -1 return code for the carbon data member
      if ( -1 != mp_iTreeCarbonCodes[iSp] [iTp] )
      {

        //Get this tree's biomass
        p_oTree->GetValue( mp_iBiomassCodes[iSp] [iTp], & fValue );

        //Calculate this tree's carbon
        fValue *= mp_fCPercentBiomass[iSp];

        //Set its value
        p_oTree->SetValue( mp_iTreeCarbonCodes[iSp] [iTp], fValue );

        //Add the amount of carbon to the species total
        p_fSpeciesTotals[iSp] += fValue;
      }

      p_oTree = p_oBehaviorTrees->NextTree();
    }

    //Set the species totals for carbon amount into our grid; for each
    //species, calculate the value of the carbon also and set it into the
    //grid
    for (iSp = 0; iSp < m_iNumTotalSpecies; iSp++) {
      mp_oValueGrid->SetValueOfCell(0, 0, mp_iCarbonCodes[iSp], p_fSpeciesTotals[iSp]);
      p_fSpeciesTotals[iSp] *= m_fPricePerTonCarbon;
      mp_oValueGrid->SetValueOfCell(0, 0, mp_iValueCodes[iSp], p_fSpeciesTotals[iSp]);
    }

    delete[] p_fSpeciesTotals;
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
    strcpy( stcErr.cFunction, "clCarbonValueCalculator::Action" );
    throw( stcErr );
  }
}

////////////////////////////////////////////////////////////////////////////
// FormatQueryString()
////////////////////////////////////////////////////////////////////////////
void clCarbonValueCalculator::FormatQueryString(clTreePopulation *p_oPop)
{
  char * cQueryTemp = new char[(p_oPop->GetNumberOfSpecies() * 4) + 50];
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
}

////////////////////////////////////////////////////////////////////////////
// GetBiomassCodes()
////////////////////////////////////////////////////////////////////////////
void clCarbonValueCalculator::GetBiomassCodes(clTreePopulation *p_oPop)
{

  short int i, j;

  //Declare the array and get the return codes for our data members
  mp_iBiomassCodes = new short int * [m_iNumTotalSpecies];
  for ( i = 0; i < m_iNumTotalSpecies; i++ )
  {
    mp_iBiomassCodes[i] = new short int[3];
    for (j = 0; j < 3; j++) {
      mp_iBiomassCodes[i][j] = -1;
    }
  }

  for ( i = 0; i < m_iNumSpeciesTypeCombos; i++ )
  {
    mp_iBiomassCodes[mp_whatSpeciesTypeCombos[i].iSpecies]
                    [mp_whatSpeciesTypeCombos[i].iType - clTreePopulation::sapling] =
         p_oPop->GetFloatDataCode( "Biomass", mp_whatSpeciesTypeCombos[i].iSpecies, mp_whatSpeciesTypeCombos[i].iType );

    //Make sure that we got a code
    if ( -1 == mp_iBiomassCodes[mp_whatSpeciesTypeCombos[i].iSpecies]
                               [mp_whatSpeciesTypeCombos[i].iType - clTreePopulation::sapling])
    {
      modelErr stcErr;
      strcpy( stcErr.cFunction, "clCarbonValueCalculator::GetBiomassCodes" );
      strcpy( stcErr.cMoreInfo, "The carbon value behavior must be used with the dimension analysis behavior for all species." );
      stcErr.iErrorCode = BAD_DATA;
      throw( stcErr );
    }
  }
}

////////////////////////////////////////////////////////////////////////////
// RegisterTreeDataMembers()
////////////////////////////////////////////////////////////////////////////
void clCarbonValueCalculator::RegisterTreeDataMembers()
{

  clTreePopulation * p_oPop = ( clTreePopulation * ) mp_oSimManager->GetPopulationObject( "treepopulation" );
  short int i, j;

  m_iNumTotalSpecies = p_oPop->GetNumberOfSpecies();

  //Declare the array and register our new data member
  mp_iTreeCarbonCodes = new short int * [m_iNumTotalSpecies];
  for ( i = 0; i < m_iNumTotalSpecies; i++ )
  {
    mp_iTreeCarbonCodes[i] = new short int[3];
    for (j = 0; j < 3; j++) {
      mp_iTreeCarbonCodes[i][j] = -1;
    }
  }

  for ( i = 0; i < m_iNumSpeciesTypeCombos; i++ )
  {
    //Make sure that only allowed types have been applied
    if ( clTreePopulation::adult != mp_whatSpeciesTypeCombos[i].iType
         && clTreePopulation::sapling != mp_whatSpeciesTypeCombos[i].iType
         && clTreePopulation::snag != mp_whatSpeciesTypeCombos[i].iType )
         {

           modelErr stcErr;
           strcpy( stcErr.cFunction, "clCarbonValueCalculator::RegisterTreeDataMembers" );
           strcpy( stcErr.cMoreInfo, "This behavior can only be applied to saplings, adults, and snags." );
           stcErr.iErrorCode = BAD_DATA;
           throw( stcErr );
    }

    //Register the code and capture it
    mp_iTreeCarbonCodes[mp_whatSpeciesTypeCombos[i].iSpecies]
                     [mp_whatSpeciesTypeCombos[i].iType - clTreePopulation::sapling] =
         p_oPop->RegisterFloat( "Carbon", mp_whatSpeciesTypeCombos[i].iSpecies, mp_whatSpeciesTypeCombos[i].iType );
  }
}
