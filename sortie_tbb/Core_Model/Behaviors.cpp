//---------------------------------------------------------------------------
#include <iostream>
#include "Behaviors.h"
#include "BehaviorBase.h"
#include "SimManager.h"
#include "TreePopulation.h"
//HEADER FILES FOR REGISTERED BEHAVIOR OBJECTS
#include "Output.h"
#include "SailLight.h"
#include "GLILight.h"
#include "QuadratGLILight.h"
#include "LightFilter.h"
#include "AbsoluteGrowth.h"
#include "RelativeGrowth.h"
#include "ConstantRadialGrowth.h"
#include "ConstantBAGrowth.h"
#include "NCIGrowth.h"
#include "LogisticGrowth.h"
#include "BCMort.h"
#include "GMFMort.h"
#include "StochasticMort.h"
#include "SenescenceMort.h"
#include "SelfThinMort.h"
#include "TreeRemover.h"
#include "Substrate.h"
#include "SpatialDisperse.h"
#include "NonSpatialDisperse.h"
#include "Disturbance.h"
#include "Planting.h"
#include "Establishment.h"
#include "Germination.h"
#include "OutputShort.h"
#include "FuncResponseSeedPredation.h"
#include "MicroEstablishment.h"
#include "AllometricGrowthIncrementer.h"
#include "SimpleLinearGrowth.h"
#include "ShadedLinearGrowth.h"
#include "SizeDepLogisticGrowth.h"
#include "LognormalGrowth.h"
#include "WeibullSnagMort.h"
#include "SelectionHarvest.h" //(JM)
#include "NCIMort.h"
#include "StormDamageApplier.h"
#include "Storm.h"
#include "VolumeCalculator.h"
#include "GLIMap.h"
#include "DimensionAnalysis.h"
#include "GapLight.h"
#include "DoubleMMRelGrowth.h"
#include "ResourceMortality.h"
#include "StochasticGapGrowth.h"
#include "CompetitionMort.h"
#include "DensitySelfThinning.h"
#include "BoleVolumeCalculator.h"
#include "DensitySeedSurvival.h"
#include "LightDepSeedSurvival.h"
#include "SubstrateDepSeedSurvival.h"
#include "StormLight.h"
#include "LinearBiLevelGrowth.h"
#include "LogisticBiLevelMortality.h"
#include "LogBiLevelGrowth.h"
#include "PRSemiStochGrowth.h"
#include "StochasticBiLevelMortality.h"
#include "GLIPoints.h"
#include "TreeAgeCalculator.h"
#include "NCIBAGrowth.h"
#include "BasalAreaLight.h"
#include "StormKiller.h"
#include "HeightGLIWeibullMortality.h"
#include "PRStormBiLevelGrowth.h"
#include "MerchValueCalculator.h"
#include "CarbonValueCalculator.h"
#include "Windstorm.h"
#include "ExpResourceMortality.h"
#include "AggregatedMortality.h"
#include "ConstantGLI.h"
#include "AverageLight.h"
#include "HarvestInterface.h"
#include "PartitionedBiomass.h"
#include "SnagDecomp.h"
#include "RandomBrowse.h"
#include "BrowsedRelativeGrowth.h"
#include "BrowsedStochasticMortality.h"
#include "MastingSpatialDisperse.h"
#include "StormKilledPartitionedBiomass.h"
#include "NeighborhoodSeedPredation.h"
#include "CompetitionHarvest.h"
#include "RipleysKCalculator.h"
#include "ConditOmegaCalculator.h"
#include "DetailedSubstrate.h"
#include "StormDirectKiller.h"
#include "MastingNonSpatialDisperse.h"
#include "MichMenNegGrowth.h"
#include "MichMenPhotoinhibition.h"
#include "FoliarChemistry.h"
#include "PowerHeightGrowth.h"
#include "PostHarvestSkiddingMort.h"
#include "LaggedPostHarvestGrowth.h"
#include "EpiphyticEstablishment.h"
#include "DensitySelfThinningGompertz.h"
#include "NCIJuvenileGrowth.h"
#include "WeibullClimateGrowth.h"
#include "WeibullClimateSurvival.h"
#include "WeibullClimateQuadratGrowth.h"
#include "TempDependentNeighborhoodDisperse.h"
#include "TempDependentNeighborhoodSurvival.h"
#include "ClimateChange.h"
#include "InsectInfestation.h"
#include "InsectInfestationMortality.h"
#include "StateReporter.h"
#include "GeneralizedHarvestRegime.h"
#include "SuppressionDurationMort.h"
#include "QualityVigorClassifier.h"
//Test objects
#include "RandomSeedLogger.h"

using namespace xercesc;

///////////////////////////////////////////////////////////////////////////
// CreateObjects()
///////////////////////////////////////////////////////////////////////////
void clBehaviorManager::CreateObjects( xercesc::DOMDocument * p_oDoc )
{
  try
  {
    clPopulationBase * p_oTempObject = NULL;
    clTreePopulation * p_oTreePop = NULL; //for querying species
    struct behaviorData data; //data structure to pass to the
    //behavior manager to create the behavior objects
    DOMElement * p_oElement, //Element-type nodes in the document tree
         * p_oNameElement;
    DOMNode * p_oBehavior, * p_oBehaviorName, * p_oDocNode;
    DOMNodeList * p_oNodeList, //Node lists - used to grab all children of a node
         * p_oNodeList2, * p_oBehaviorChildren;
    XMLCh *sVal;
    char * cData; //for getting text data
    int iNumNodes, //used to count nodes
         iNumCombos, //used to loop through the species list
         i, j, k; //loop counters
    short int iSpeciesCode, //returned species code
         iType; //type code translated from text
    bool bDuplicate = false; //used for sniffing out duplicate species

    //Initialize the data structure
    data.iNumCombos = 0;
    data.p_whatCombos = NULL;

    //Have we already been set up?  If so, clear memory
    if ( m_iNumObjects > 0 ) FreeMemory();

    // Get the list of behaviors so we can process them one at a time
    sVal = XMLString::transcode( "behaviorList" );
    p_oNodeList = p_oDoc->getElementsByTagName( sVal );
    XMLString::release(&sVal);
    if ( 0 == p_oNodeList->getLength() )
    {
      modelErr stcErr;
      stcErr.iErrorCode = DATA_MISSING;
      strcpy( stcErr.cFunction, "clBehaviorManager::CreateObjects" );
      strcpy( stcErr.cMoreInfo, "behaviorList" );
      throw( stcErr );
    }
    p_oDocNode = p_oNodeList->item( 0 ); //now we have the behavior list element
    p_oElement = ( DOMElement * ) p_oDocNode; //cast to DOM_Element object
    sVal = XMLString::transcode( "behavior" );
    //p_oNodeList now has the list of "behavior" elements
    p_oNodeList = p_oElement->getElementsByTagName( sVal );
    XMLString::release(&sVal);
    iNumNodes = p_oNodeList->getLength();

    if ( 0 == iNumNodes )
    { //no behaviors were found
      modelErr stcErr;
      stcErr.iErrorCode = DATA_MISSING;
      strcpy( stcErr.cFunction, "clBehaviorManager::CreateObjects" );
      strcpy( stcErr.cMoreInfo, "behavior" );
      throw( stcErr );
    }

    //Get the tree population object
    p_oTempObject = mp_oSimManager->GetPopulationObject( "treepopulation" );
    if ( NULL == p_oTempObject )
    {
      modelErr stcErr;
      strcpy( stcErr.cFunction, "clBehaviorManager::CreateObjects" );
      stcErr.iErrorCode = CANT_FIND_OBJECT;
      strcpy( stcErr.cMoreInfo, "clTreePopulation" );
      throw( stcErr );
    } //error condition
    p_oTreePop = ( clTreePopulation * ) p_oTempObject;

    // For each behavior, create it
    for ( i = 0; i < iNumNodes; i++ )
    {

      //Get the behavior name string
      p_oBehavior = p_oNodeList->item( i ); //has ith "behavior" element
      p_oElement = ( DOMElement * ) p_oBehavior; //cast to DOM_Element object
      sVal = XMLString::transcode( "behaviorName" );
      p_oNodeList2 = p_oElement->getElementsByTagName( sVal );
      XMLString::release(&sVal);
      if ( 0 == p_oNodeList2->getLength() )
      {
        modelErr stcErr;
        stcErr.iErrorCode = DATA_MISSING;
        strcpy( stcErr.cFunction, "clBehaviorManager::CreateObjects" );
        sprintf( stcErr.cMoreInfo, "%s%d", "behaviorName - behavior #", i );
        throw( stcErr );
      }
      p_oBehaviorName = p_oNodeList2->item( 0 ); //oBehaviorName holds the
      //"behaviorName" child of the ith "behavior" element
      //The name string is in the first child of the "behaviorName" node
      cData = XMLString::transcode( p_oBehaviorName->getChildNodes()->item( 0 )->getNodeValue() );
      strncpy( data.cNameString, cData, MAX_NAMESTRING_SIZE - 1 );
      delete[] cData; cData = NULL;
      //This doesn't always happen with strncpy - make it explicit
      data.cNameString[MAX_NAMESTRING_SIZE - 1] = '\0';

      //Get the version number
      sVal = XMLString::transcode( "version" );
      p_oNodeList2 = p_oElement->getElementsByTagName( sVal );
      XMLString::release(&sVal);
      if ( 0 == p_oNodeList2->getLength() )
      {
        modelErr stcErr;
        stcErr.iErrorCode = DATA_MISSING;
        strcpy( stcErr.cFunction, "clBehaviorManager::CreateObjects" );
        sprintf( stcErr.cMoreInfo, "%s%d", "version - behavior #", i );
        throw( stcErr );
      }
      p_oBehaviorName = p_oNodeList2->item( 0 ); //reusing this variable
      cData = XMLString::transcode( p_oBehaviorName->getChildNodes()->item( 0 )->getNodeValue() );
      data.fVersion = atof( cData );
      if ( 0 == data.fVersion && strcmp( cData, "0" ) != 0 )
      {
        //the version wasn't a number - throw an error
        delete[] cData;
        modelErr stcErr;
        stcErr.iErrorCode = BAD_DATA;
        strcpy( stcErr.cFunction, "clBehaviorManager::CreateObjects" );
        strcpy( stcErr.cMoreInfo, "Version is not a number." );
        throw( stcErr );
      }
      delete[] cData; cData = NULL;

      //Get the behavior list number
      sVal = XMLString::transcode( "listPosition" );
      p_oNodeList2 = p_oElement->getElementsByTagName( sVal );
      XMLString::release(&sVal);
      if ( 0 == p_oNodeList2->getLength() ) {
        modelErr stcErr;
        stcErr.iErrorCode = DATA_MISSING;
        strcpy( stcErr.cFunction, "clBehaviorManager::CreateObjects");
        sprintf(stcErr.cMoreInfo, "%s%d", "list position - behavior #", i);
        throw( stcErr );
      }
      p_oBehaviorName = p_oNodeList2->item( 0 ); //reusing this variable
      cData = XMLString::transcode( p_oBehaviorName->getChildNodes()->item( 0 )->getNodeValue() );
      data.iBehaviorListNumber = atoi( cData );
      if ( 0 == data.iBehaviorListNumber && strcmp( cData, "0" ) != 0 ) {
        //the version wasn't a number - throw an error
        delete[] cData;
        modelErr stcErr;
        stcErr.iErrorCode = BAD_DATA;
        strcpy( stcErr.cFunction, "clBehaviorManager::CreateObjects");
        strcpy(stcErr.cMoreInfo, "Behavior list is not a number.");
        throw( stcErr );
      }
      delete[] cData; cData = NULL;

      //Count the number of species/type combos - there may be none
      sVal = XMLString::transcode( "applyTo" );
      p_oBehaviorChildren = p_oElement->getElementsByTagName( sVal );
      XMLString::release(&sVal);
      iNumCombos = p_oBehaviorChildren->getLength();
      data.iNumCombos = iNumCombos;

      //Get the list of species/type combos if there are any
      //Allocate the array of species/type codes and pre-set the values to -1 -
      //that way if there are bad values or duplicates we will know at the end
      if ( 0 != iNumCombos )
      {
        data.p_whatCombos = new struct stcSpeciesTypeCombo[iNumCombos];
        for ( j = 0; j < iNumCombos; j++ )
        {
          data.p_whatCombos[j].iSpecies = -1;
          data.p_whatCombos[j].iType = -1;
        }
        for ( j = 0; j < iNumCombos; j++ )
        {
          p_oBehaviorName = p_oBehaviorChildren->item( j );
          p_oNameElement = ( DOMElement * ) p_oBehaviorName;

          //Get the species code from the attribute "species"
          sVal = XMLString::transcode( "species" );
          cData = XMLString::transcode( p_oNameElement->getAttributeNode( sVal )->getValue() );
          XMLString::release(&sVal);
          iSpeciesCode = p_oTreePop->TranslateSpeciesNameToCode( cData );
          delete[] cData; cData = NULL;

          if ( -1 == iSpeciesCode )
          { //bad species - throw error
            modelErr stcErr;
            strcpy( stcErr.cFunction, "clBehaviorManager::CreateObjects" );
            stcErr.iErrorCode = BAD_DATA;
            sprintf( stcErr.cMoreInfo, "%s%d", "Invalid species code for behavior # ", i );
            throw( stcErr );
          }

          //Get the type code from the attribute "type"
          sVal = XMLString::transcode( "type" );
          cData = XMLString::transcode( p_oNameElement->getAttributeNode( sVal )->getValue() );
          XMLString::release(&sVal);

          //translate the type to a number
          if ( strcmp( cData, "Seed" ) == 0 )
            iType = clTreePopulation::seed;
          else if ( strcmp( cData, "Seedling" ) == 0 )
            iType = clTreePopulation::seedling;
          else if ( strcmp( cData, "Sapling" ) == 0 )
            iType = clTreePopulation::sapling;
          else if ( strcmp( cData, "Adult" ) == 0 )
            iType = clTreePopulation::adult;
          else if ( strcmp( cData, "Stump" ) == 0 )
            iType = clTreePopulation::stump;
          else if ( strcmp( cData, "Snag" ) == 0 )
            iType = clTreePopulation::snag;
          else if ( strcmp( cData, "Woody_debris" ) == 0 )
            iType = clTreePopulation::woody_debris;
          else
          { //unrecognized type - throw error
            modelErr stcErr;
            strcpy( stcErr.cFunction, "clBehaviorManager::CreateObjects" );
            stcErr.iErrorCode = BAD_DATA;
            sprintf( stcErr.cMoreInfo, "%s%s", "Unrecognized type:  ", cData );
            delete[] cData;
            throw( stcErr );
          }
          delete[] cData; cData = NULL;

          //We have valid species and type codes - check for a duplicate combo
          bDuplicate = false;
          for ( k = 0; k < j; k++ )
            if ( iSpeciesCode == data.p_whatCombos[k].iSpecies && iType == data.p_whatCombos[k].iType )
              bDuplicate = true;
          if ( !bDuplicate )
          { //our value is valid and not a duplicate
            data.p_whatCombos[j].iSpecies = iSpeciesCode;
            data.p_whatCombos[j].iType = iType;
          }
          else
            data.iNumCombos--; //duplicate - decrease the count by one

        } //end of for (j = 0; j < iNumCombos; j++)
      } //end of if (0 != iNumCombos)


      //Create behavior and pass type/species data
      CreateBehavior( & data );

      //Re-initialize the data structure
      data.iNumCombos = 0;
      if ( data.p_whatCombos )
      {
        delete[] data.p_whatCombos; data.p_whatCombos = NULL;
      }
      strcpy( data.cNameString, "" );

    } //end of for (i = 0; i < iNumNodes; i++)

    delete[] cData;
  } //end of try block
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
    strcpy( stcErr.cFunction, "clBehaviorManager::CreateObjects" );
    throw( stcErr );
  }
}

////////////////////////////////////////////////////////////////////////////
// CreateBehavior()
/////////////////////////////////////////////////////////////////////////////
void clBehaviorManager::CreateBehavior( behaviorData * p_data )
{
  try
  {
    clWorkerBase * * p_oTempObjectArray = NULL; //in case we need to increase the
    //size of the array
    clBehaviorBase * p_oBehavior; //for casting our object to clBehaviorBase
    short int iIndex = -1, //place in the array to create the new behavior
         iReturnCode, //for testing the version number
         i; //loop counter

    //Check to make sure we have a name - if not throw an error
    if ( strlen( p_data->cNameString ) == 0 )
    {
      modelErr stcErr;
      strcpy( stcErr.cFunction, "clBehaviorManager::CreateBehavior" );
      stcErr.iErrorCode = DATA_MISSING;
      strcpy( stcErr.cMoreInfo, "namestring" );
      throw( stcErr );
    }

    //************
    // This next section was originally a good idea; but I forgot about it and
    //went on to divorce the object namestring from the parameter file call
    //string. Which was stupid. Which caused a bug that caused me to need
    //to comment this out.
    //************

    //Determine the next open pointer in the behavior array - if this is a
    //new definition for an existing object then delete the old object - the
    //index will be set to the "hole" created
/*    for ( i = 0; i < m_iNumObjects; i++ )
      if ( strcmp( p_data->cNameString, mp_oObjectArray[i]->GetName() ) == 0 )
      {
        delete mp_oObjectArray[i];
      }
    for ( i = 0; i < m_iNumObjects; i++ )
      if ( !mp_oObjectArray[i] )
      {
        iIndex = i;
        break;
      }*/

    //Check to see if we found an open spot in the array - if we didn't increase
    //the size of the array by one
    if ( -1 == iIndex )
    {
      //make a copy of the array
      p_oTempObjectArray = new clWorkerBase * [m_iNumObjects];
      for ( i = 0; i < m_iNumObjects; i++ )
        p_oTempObjectArray[i] = mp_oObjectArray[i];
      //resize the object array
      delete[] mp_oObjectArray;
      m_iNumObjects++;
      mp_oObjectArray = new clWorkerBase * [m_iNumObjects];
      //copy the old array back in
      for ( i = 0; i < m_iNumObjects - 1; i++ )
        mp_oObjectArray[i] = p_oTempObjectArray[i];
      delete[] p_oTempObjectArray;
      iIndex = m_iNumObjects - 1;
      mp_oObjectArray[iIndex] = NULL;
    } //end of if (-1 == iIndex)

    //Figure out what type of object we are supposed to create, and create the
    //appropriate one

    //*************************************************
    // State Change Behaviors
    //*************************************************
    if ( strcmp( "TemperatureClimateChange", p_data->cNameString ) == 0 ||
         strcmp( "PrecipitationClimateChange", p_data->cNameString ) == 0 )
    {
      clClimateChange * p_oObj = new clClimateChange( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oObj;

    }

    //*************************************************
    // Light Behaviors
    //*************************************************
    else if ( strcmp( "SailLight", p_data->cNameString ) == 0 )
    {
      clSailLight * p_oLight = new clSailLight( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oLight;

    }
    else if ( strcmp( "GLILight", p_data->cNameString ) == 0 )
    {
      clGliLight * p_oLight = new clGliLight( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oLight;

    }
    else if ( strcmp( "QuadratLight", p_data->cNameString ) == 0 )
    {
      clQuadratGLILight * p_oLight = new clQuadratGLILight( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oLight;

    }
     else if ( strcmp( "LightFilter", p_data->cNameString ) == 0 )
    {
      clLightFilter * p_oLight = new clLightFilter( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oLight;
    }
    else if ( strcmp( "GLIMapCreator", p_data->cNameString ) == 0 )
    {
      clGLIMap * p_oLight = new clGLIMap( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oLight;
    }
    else if ( strcmp( "GLIPointCreator", p_data->cNameString ) == 0 )
    {
      clGLIPoints * p_oLight = new clGLIPoints( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oLight;
    }
    else if ( strcmp( "GapLight", p_data->cNameString ) == 0 )
    {
      clGapLight * p_oLight = new clGapLight( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oLight;
    }
    else if ( strcmp( "StormLight", p_data->cNameString ) == 0 )
    {
      clStormLight * p_oLight = new clStormLight( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oLight;
    }
    else if ( strcmp( "BasalAreaLight", p_data->cNameString ) == 0 )
    {
      clBasalAreaLight * p_oLight = new clBasalAreaLight( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oLight;
    }
    else if ( strcmp( "ConstantGLI", p_data->cNameString ) == 0 )
    {
      clConstantGLI * p_oLight = new clConstantGLI( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oLight;
    }
    else if ( strcmp( "AverageLight", p_data->cNameString ) == 0 )
    {
      clAverageLight * p_oLight = new clAverageLight( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oLight;
    }

    //*************************************************
    // Growth Behaviors
    //*************************************************

    else if ( strcmp( "AbsRadialGrowth", p_data->cNameString ) == 0 ||
              strcmp( "AbsBAGrowth", p_data->cNameString ) == 0 ||
              strcmp( "AbsUnlimGrowth", p_data->cNameString ) == 0 ||
              strcmp( "AbsRadialGrowth diam only", p_data->cNameString ) == 0 ||
              strcmp( "AbsBAGrowth diam only", p_data->cNameString ) == 0 ||
              strcmp( "AbsUnlimGrowth diam only", p_data->cNameString ) == 0 )
    {
      clAbsoluteGrowth * p_oGrowth = new clAbsoluteGrowth( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oGrowth;
    }
    else if ( strcmp( "RelRadialGrowth", p_data->cNameString ) == 0 ||
              strcmp( "RelBAGrowth", p_data->cNameString ) == 0 ||
              strcmp( "RelUnlimGrowth", p_data->cNameString ) == 0 ||
              strcmp( "RelRadialGrowth diam only", p_data->cNameString ) == 0 ||
              strcmp( "RelBAGrowth diam only", p_data->cNameString ) == 0 ||
              strcmp( "RelUnlimGrowth diam only", p_data->cNameString ) == 0 ||
              strcmp( "RelativeHeight", p_data->cNameString ) == 0)
    {
      clRelativeGrowth * p_oGrowth = new clRelativeGrowth( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oGrowth;
    }
    else if (strcmp( "LogisticGrowth diam only", p_data->cNameString ) == 0 ||
             strcmp( "LogisticGrowth", p_data->cNameString ) == 0 ||
             strcmp( "LogisticGrowth height only", p_data->cNameString ) == 0 )
    {
      clLogisticGrowth * p_oGrowth = new clLogisticGrowth( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oGrowth;
    }
    else if (strcmp( "LognormalGrowth diam only", p_data->cNameString ) == 0 ||
             strcmp( "LognormalGrowth", p_data->cNameString ) == 0 ||
             strcmp( "LognormalGrowth height only", p_data->cNameString ) == 0 )
    {
      clLognormalGrowth * p_oGrowth = new clLognormalGrowth( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oGrowth;
    }
    else if ( strcmp( "SizeDependentLogisticGrowth diam only", p_data->cNameString ) == 0
         || strcmp( "SizeDependentLogisticGrowth", p_data->cNameString ) == 0
         || strcmp( "SizeDependentLogisticGrowth height only", p_data->cNameString ) == 0 )
    {
      clSizeDepLogisticGrowth * p_oGrowth = new clSizeDepLogisticGrowth( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oGrowth;
    }
    else if ( strcmp( "SimpleLinearGrowth diam only", p_data->cNameString ) == 0
         || strcmp( "SimpleLinearGrowth", p_data->cNameString ) == 0
         || strcmp( "SimpleLinearGrowth height only", p_data->cNameString ) == 0 )
    {
      clSimpleLinearGrowth * p_oGrowth = new clSimpleLinearGrowth( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oGrowth;
    }
    else if ( strcmp( "ShadedLinearGrowth diam only", p_data->cNameString ) == 0
         || strcmp( "ShadedLinearGrowth", p_data->cNameString ) == 0
         || strcmp( "ShadedLinearGrowth height only", p_data->cNameString ) == 0 )
    {
      clShadedLinearGrowth * p_oGrowth = new clShadedLinearGrowth( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oGrowth;
    }
    else if ( strcmp( "LinearBilevelGrowth diam only", p_data->cNameString ) == 0
         || strcmp( "LinearBilevelGrowth", p_data->cNameString ) == 0 )
    {
      clLinearBiLevelGrowth * p_oGrowth = new clLinearBiLevelGrowth( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oGrowth;
    }
    else if ( strcmp( "NCIGrowth", p_data->cNameString ) == 0 ||
              strcmp( "NCIGrowth diam only", p_data->cNameString ) == 0 )
    {
      clNCIGrowth * p_oGrowth = new clNCIGrowth( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oGrowth;

    }
    else if ( strcmp( "ConstRadialGrowth", p_data->cNameString ) == 0 ||
              strcmp( "ConstRadialGrowth diam only", p_data->cNameString ) == 0)
    {
      clConstantRadialGrowth * p_oGrowth = new clConstantRadialGrowth( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oGrowth;
    }
    else if ( strcmp( "ConstBAGrowth", p_data->cNameString ) == 0 ||
              strcmp( "ConstBAGrowth diam only", p_data->cNameString ) == 0 )
    {
      clConstantBAGrowth * p_oGrowth = new clConstantBAGrowth( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oGrowth;
    }
    else if ( strcmp( "HeightIncrementer", p_data->cNameString ) == 0 ||
              strcmp( "DiameterIncrementer", p_data->cNameString ) == 0)
    {
      clAllometricGrowthIncrementer * p_oGrowth = new clAllometricGrowthIncrementer( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oGrowth;
    }
    else if ( strcmp( "DoubleResourceRelative", p_data->cNameString ) == 0
         || strcmp( "DoubleResourceRelative diam only", p_data->cNameString ) == 0 )
    {
      clDoubleMMRelGrowth * p_oGrowth = new clDoubleMMRelGrowth( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oGrowth;
    }
    else if ( strcmp( "StochasticGapGrowth", p_data->cNameString ) == 0 )
    {
      clStochasticGapGrowth * p_oGrowth = new clStochasticGapGrowth( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oGrowth;
    }
    else if ( strcmp( "LogBilevelGrowth height only", p_data->cNameString ) == 0 )
    {
      clLogBiLevelGrowth * p_oGrowth = new clLogBiLevelGrowth( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oGrowth;
    }
    else if ( strcmp( "PRSemiStochastic diam only", p_data->cNameString ) == 0 )
    {
      clPRSemiStochGrowth * p_oGrowth = new clPRSemiStochGrowth( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oGrowth;
    }
    else if ( strcmp( "NCIBAGrowth", p_data->cNameString ) == 0 ||
              strcmp( "NCIBAGrowth diam only", p_data->cNameString ) == 0 )
    {
      clNCIBAGrowth * p_oGrowth = new clNCIBAGrowth( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oGrowth;
    }
    else if ( strcmp( "PRStormBilevelGrowth", p_data->cNameString ) == 0 )
    {
      clPRStormBiLevelGrowth * p_oGrowth = new clPRStormBiLevelGrowth( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oGrowth;
    }
    else if ( strcmp( "BrowsedRelativeGrowth", p_data->cNameString ) == 0 ||
              strcmp( "BrowsedRelativeGrowth diam only", p_data->cNameString ) == 0 )
    {
      clBrowsedRelativeGrowth * p_oGrowth = new clBrowsedRelativeGrowth( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oGrowth;
    }
    else if ( strcmp( "MichaelisMentenNegativeGrowth height only", p_data->cNameString ) == 0 )
    {
      clMichMenNegGrowth * p_oGrowth = new clMichMenNegGrowth( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oGrowth;
    }
    else if ( strcmp( "MichaelisMentenPhotoinhibitionGrowth height only", p_data->cNameString ) == 0 )
    {
      clMichMenPhotoinhibition * p_oGrowth = new clMichMenPhotoinhibition( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oGrowth;
    }
    else if ( strcmp( "PowerGrowth height only", p_data->cNameString ) == 0 )
    {
      clPowerHeightGrowth * p_oGrowth = new clPowerHeightGrowth( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oGrowth;
    }
    else if ( strcmp( "LaggedPostHarvestGrowth", p_data->cNameString ) == 0 ||
        strcmp( "LaggedPostHarvestGrowth diam only", p_data->cNameString ) == 0)
    {
      clLaggedPostHarvestGrowth * p_oGrowth = new clLaggedPostHarvestGrowth( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oGrowth;
    }
    else if ( strcmp( "NCIJuvenileGrowth", p_data->cNameString ) == 0 ||
        strcmp( "NCIJuvenileGrowth diam only", p_data->cNameString ) == 0)
    {
      clNCIJuvenileGrowth * p_oGrowth = new clNCIJuvenileGrowth( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oGrowth;
    }
    else if ( strcmp( "WeibullClimateGrowth", p_data->cNameString ) == 0 ||
        strcmp( "WeibullClimateGrowth diam only", p_data->cNameString ) == 0)
    {
      clWeibullClimateGrowth * p_oGrowth = new clWeibullClimateGrowth( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oGrowth;
    }
    else if ( strcmp( "WeibullClimateQuadratGrowth", p_data->cNameString ) == 0 ||
        strcmp( "WeibullClimateQuadratGrowth diam only", p_data->cNameString ) == 0)
    {
      clWeibullClimateQuadratGrowth * p_oGrowth = new clWeibullClimateQuadratGrowth( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oGrowth;
    }

    //*************************************************
    // Mortality Behaviors
    //*************************************************

    else if ( strcmp( "BCMortality", p_data->cNameString ) == 0 )
    {
      clBCMort * p_oMort = new clBCMort( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oMort;

    }
    else if ( strcmp( "GMFMortality", p_data->cNameString ) == 0 )
    {
      clGMFMort * p_oMort = new clGMFMort( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oMort;

    }
    else if ( strcmp( "SelfThinning", p_data->cNameString ) == 0 )
    {
      clSelfThinMort * p_oMort = new clSelfThinMort( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oMort;

    }
    else if ( strcmp( "Senescence", p_data->cNameString ) == 0 )
    {
      clSenescenceMort * p_oMort = new clSenescenceMort( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oMort;

    }
    else if ( strcmp( "StochasticMortality", p_data->cNameString ) == 0)
    {
      clStochasticMort * p_oMort = new clStochasticMort( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oMort;

    }
    else if ( strcmp( "WeibullSnagMortality", p_data->cNameString ) == 0 )
    {
      clWeibullSnagMort * p_oMort = new clWeibullSnagMort( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oMort;

    }
    else if ( strcmp( "NCIMortality", p_data->cNameString ) == 0 )
    {
      clNCIMort * p_oMort = new clNCIMort( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oMort;

    }
    else if ( strcmp( "GrowthResourceMortality", p_data->cNameString ) == 0 )
    {
      clResourceMortality * p_oMort = new clResourceMortality( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oMort;

    }
    else if ( strcmp( "CompetitionMortality", p_data->cNameString ) == 0 )
    {
      clCompetitionMort * p_oMort = new clCompetitionMort( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oMort;

    }
    else if ( strcmp( "DensitySelfThinning", p_data->cNameString ) == 0 )
    {
      clDensitySelfThinning * p_oMort = new clDensitySelfThinning( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oMort;

    }
    else if ( strcmp( "LogisticBiLevelMortality", p_data->cNameString ) == 0 )
    {
      clLogisticBiLevelMortality * p_oMort = new clLogisticBiLevelMortality( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oMort;

    }
    else if ( strcmp( "StochasticBiLevelMortality", p_data->cNameString ) == 0 ||
            strcmp( "StochasticBiLevelMortality - GLI", p_data->cNameString ) == 0)
    {
      clStochasticBiLevelMortality * p_oMort = new clStochasticBiLevelMortality( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oMort;

    }
    else if ( strcmp( "HeightGLIWeibullMortality", p_data->cNameString ) == 0 )
    {
      clHeightGLIWeibullMortality * p_oMort = new clHeightGLIWeibullMortality( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oMort;

    }
    else if ( strcmp( "ExponentialGrowthResourceMortality", p_data->cNameString ) == 0 )
    {
      clExpResourceMortality * p_oMort = new clExpResourceMortality( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oMort;

    }
    else if ( strcmp( "AggregatedMortality", p_data->cNameString ) == 0 )
    {
      clAggregatedMortality * p_oMort = new clAggregatedMortality( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oMort;

    }
    else if ( strcmp( "SnagDecayClassDynamics", p_data->cNameString ) == 0 )
    {
      clSnagDecomp * p_oMort = new clSnagDecomp( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oMort;

    }
    else if ( strcmp( "BrowsedStochasticMortality", p_data->cNameString ) == 0 )
    {
      clBrowsedStochasticMortality * p_oMort = new clBrowsedStochasticMortality( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oMort;

    }
    else if ( strcmp( "PostHarvestSkiddingMortality", p_data->cNameString ) == 0 )
    {
      clPostHarvestSkiddingMort * p_oMort = new clPostHarvestSkiddingMort( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oMort;

    }
    else if ( strcmp( "GompertzDensitySelfThinning", p_data->cNameString ) == 0 )
    {
      clDensitySelfThinningGompertz * p_oMort = new clDensitySelfThinningGompertz( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oMort;

    }
    else if ( strcmp( "WeibullClimateSurvival", p_data->cNameString ) == 0 )
    {
      clWeibullClimateSurvival * p_oMort = new clWeibullClimateSurvival( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oMort;

    }
    else if ( strcmp( "TempDependentNeighborhoodSurvival", p_data->cNameString ) == 0 )
    {
      clTempDependentNeighborhoodSurvival * p_oMort = new clTempDependentNeighborhoodSurvival( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oMort;

    }
    else if ( strcmp( "InsectInfestationMortality", p_data->cNameString ) == 0 )
    {
      clInsectInfestationMortality * p_oMort = new clInsectInfestationMortality( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oMort;

    }
    else if ( strcmp( "SuppressionDurationMortality", p_data->cNameString ) == 0 )
    {
      clSuppressionDurationMort * p_oMort = new clSuppressionDurationMort( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oMort;

    }
    else if ( strcmp( "RemoveDead", p_data->cNameString ) == 0 )
    {
      clTreeRemover * p_oMort = new clTreeRemover( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oMort;
    }

    //*************************************************
    // Substrate Behavior
    //*************************************************
    else if ( strcmp( "Substrate", p_data->cNameString ) == 0 )
    {
      clSubstrate * p_oSubstrate = new clSubstrate( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oSubstrate;

    }
    else if ( strcmp( "DetailedSubstrate", p_data->cNameString ) == 0 )
    {
      clDetailedSubstrate * p_oSubstrate = new clDetailedSubstrate( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oSubstrate;

    }


    else if ( strcmp( "EpiphyticEstablishment", p_data->cNameString ) == 0 )
    {
      clEpiphyticEstablishment * p_oEstablish = new clEpiphyticEstablishment( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oEstablish;

    }

    //*************************************************
    // Disperse Behaviors
    //*************************************************
    else if ( ( strcmp( "GapDisperse", p_data->cNameString ) == 0 )
         || ( strcmp( "NonGapDisperse", p_data->cNameString ) == 0 ) )
         {
           clSpatialDispersal * p_oDisperse = new clSpatialDispersal( mp_oSimManager );
           mp_oObjectArray[iIndex] = p_oDisperse;
    }
    else if ( strcmp( "NonSpatialDisperse", p_data->cNameString ) == 0 )
    {
      clNonSpatialDispersal * p_oDisperse = new clNonSpatialDispersal( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oDisperse;

    }
    else if ( strcmp( "MastingSpatialDisperse", p_data->cNameString ) == 0 )
    {
      clMastingSpatialDisperse * p_oDisperse = new clMastingSpatialDisperse( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oDisperse;
    }
    else if ( strcmp( "MastingNonSpatialDisperse", p_data->cNameString ) == 0 )
    {
      clMastingNonSpatialDisperse * p_oDisperse = new clMastingNonSpatialDisperse( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oDisperse;
    }
    else if ( strcmp( "TemperatureDependentNeighborhoodDisperse", p_data->cNameString ) == 0 )
    {
      clTempDependentNeighborhoodDisperse * p_oDisperse = new clTempDependentNeighborhoodDisperse( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oDisperse;
    }

    //*************************************************
    // Seed Survival Behaviors
    //*************************************************
    else if ( strcmp( "FunctionalResponseSeedPredation", p_data->cNameString ) == 0 ||
        strcmp( "LinkedFunctionalResponseSeedPredation", p_data->cNameString ) == 0)
    {
      clFuncResponseSeedPredation * p_oPredation = new clFuncResponseSeedPredation( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oPredation;
    }
    else if ( strcmp( "NeighborhoodSeedPredation", p_data->cNameString ) == 0 ||
        strcmp( "LinkedNeighborhoodSeedPredation", p_data->cNameString ) == 0)
    {
      clNeighborhoodSeedPredation * p_oPredation = new clNeighborhoodSeedPredation( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oPredation;
    }
    else if ( strcmp( "Germination", p_data->cNameString ) == 0 )
    {
      clGermination * p_oGermination = new clGermination( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oGermination;
    }
    else if ( strcmp( "DensityDependentSeedSurvival", p_data->cNameString ) == 0  ||
        strcmp( "ConspecificTreeDensityDependentSeedSurvival", p_data->cNameString ) == 0)
    {
      clDensitySeedSurvival * p_oSeedSurvival = new clDensitySeedSurvival( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oSeedSurvival;
    }
    else if ( strcmp( "LightDependentSeedSurvival", p_data->cNameString ) == 0 ||
              strcmp( "StormLightDependentSeedSurvival", p_data->cNameString ) == 0)
    {
      clLightDepSeedSurvival * p_oSeedSurvival = new clLightDepSeedSurvival( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oSeedSurvival;
    }
    else if ( strcmp( "NoGapSubstrateSeedSurvival", p_data->cNameString ) == 0 ||
              strcmp( "MicrotopographicSubstrateSeedSurvival", p_data->cNameString ) == 0 ||
              strcmp( "GapSubstrateSeedSurvival", p_data->cNameString ) == 0)
    {
      clSubstrateDepSeedSurvival * p_oSeedSurvival = new clSubstrateDepSeedSurvival( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oSeedSurvival;
    }

    //*************************************************
    // Establishment Behaviors
    //*************************************************

    else if (  strcmp( "Establishment", p_data->cNameString ) == 0 )
    {
      clEstablishment * p_oDisperse = new clEstablishment( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oDisperse;
    }
    else if ( strcmp( "MicroEstablishment", p_data->cNameString ) == 0 )
    {
      clMicroEstablishment * p_oDisperse = new clMicroEstablishment( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oDisperse;
    }
    //*************************************************
    // Disturbance Behaviors
    //*************************************************
    else if ( strcmp( "SelectionHarvest", p_data->cNameString ) == 0 )
    {
      clSelectionHarvest * p_oSelectionHarvest;
      p_oSelectionHarvest = new clSelectionHarvest( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oSelectionHarvest;
    }
    else if ( strcmp( "Harvest", p_data->cNameString ) == 0 || strcmp( "EpisodicMortality", p_data->cNameString ) == 0 )
    {
      clDisturbance * p_oDisturbance = new clDisturbance( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oDisturbance;

    }
    else if ( strcmp( "Plant", p_data->cNameString ) == 0 )
    {
      clPlant * p_oPlant = new clPlant( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oPlant;
    }

    else if ( strcmp( "StormDamageApplier", p_data->cNameString ) == 0 )
    {
      clStormDamageApplier * p_oObj = new clStormDamageApplier( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oObj;
    }
    else if ( strcmp( "StormKiller", p_data->cNameString ) == 0 )
    {
      clStormKiller * p_oObj = new clStormKiller( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oObj;
    }
    else if ( strcmp( "StormDirectKiller", p_data->cNameString ) == 0 )
    {
      clStormDirectKiller * p_oObj = new clStormDirectKiller( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oObj;
    }
    else if ( strcmp( "Storm", p_data->cNameString ) == 0 )
    {
      clStorm * p_oObj = new clStorm( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oObj;
    }
    else if ( strcmp( "Windstorm", p_data->cNameString ) == 0 )
    {
      clWindstorm * p_oObj = new clWindstorm( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oObj;
    }
    //Note the name comparison isn't the same for this one
    else if ( strstr( p_data->cNameString, "HarvestInterface" ) != NULL )
    {
      clHarvestInterface * p_oObj = new clHarvestInterface( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oObj;
    }
    else if ( strcmp( "RandomBrowse", p_data->cNameString ) == 0 )
    {
      clRandomBrowse * p_oObj = new clRandomBrowse( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oObj;
    }
    else if ( strcmp( "CompetitionHarvest", p_data->cNameString ) == 0 )
    {
      clCompetitionHarvest * p_oObj = new clCompetitionHarvest( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oObj;
    }
    else if ( strcmp( "InsectInfestation", p_data->cNameString ) == 0 )
    {
      clInsectInfestation * p_oObj = new clInsectInfestation( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oObj;
    }
    else if ( strcmp( "GeneralizedHarvestRegime", p_data->cNameString ) == 0 )
    {
      clGeneralizedHarvestRegime * p_oObj = new clGeneralizedHarvestRegime( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oObj;
    }
    else if ( strcmp( "QualityVigorClassifier", p_data->cNameString ) == 0 )
    {
      clQualityVigorClassifier * p_oObj = new clQualityVigorClassifier( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oObj;
    }

    //*************************************************
    // Output Behaviors
    //*************************************************

    else if ( strcmp( "Output", p_data->cNameString ) == 0 )
    {
      clOutput * p_oOutput = new clOutput( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oOutput;

    }
    else if ( strcmp( "ShortOutput", p_data->cNameString ) == 0 )
    {
      clShortOutput * p_oOutput = new clShortOutput( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oOutput;
    }

    //*************************************************
    // Analysis Behaviors
    //*************************************************
    else if ( strcmp( "TreeVolumeCalculator", p_data->cNameString ) == 0 )
    {
      clVolumeCalculator * p_oOutput = new clVolumeCalculator( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oOutput;
    }
    else if ( strcmp( "TreeBoleVolumeCalculator", p_data->cNameString ) == 0 )
    {
      clBoleVolumeCalculator * p_oOutput = new clBoleVolumeCalculator( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oOutput;
    }
    else if ( strcmp( "DimensionAnalysis", p_data->cNameString ) == 0 )
    {
      clDimensionAnalysis * p_oOutput = new clDimensionAnalysis( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oOutput;
    }
    else if ( strcmp( "TreeAgeCalculator", p_data->cNameString ) == 0 )
    {
      clTreeAgeCalculator * p_oOutput = new clTreeAgeCalculator( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oOutput;
    }
    else if ( strcmp( "MerchValueCalculator", p_data->cNameString ) == 0 )
    {
      clMerchValueCalculator * p_oOutput = new clMerchValueCalculator( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oOutput;
    }
    else if ( strcmp( "CarbonValueCalculator", p_data->cNameString ) == 0 )
    {
      clCarbonValueCalculator * p_oOutput = new clCarbonValueCalculator( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oOutput;
    }
    else if ( ( strcmp( "PartitionedDBHBiomass", p_data->cNameString ) == 0 )
         || ( strcmp( "PartitionedHeightBiomass", p_data->cNameString ) == 0 ) )
    {
      clPartitionedBiomass * p_oOutput = new clPartitionedBiomass( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oOutput;
    }
    else if ( ( strcmp( "StormKilledPartitionedDBHBiomass", p_data->cNameString ) == 0 )
         || ( strcmp( "StormKilledPartitionedHeightBiomass", p_data->cNameString ) == 0 ) )
    {
      clStormKilledPartitionedBiomass * p_oOutput = new clStormKilledPartitionedBiomass( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oOutput;
    }
    else if ( strcmp( "RipleysK", p_data->cNameString ) == 0 )
    {
      clRipleysKCalculator * p_oOutput = new clRipleysKCalculator( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oOutput;
    }
    else if ( strcmp( "ConditsOmega", p_data->cNameString ) == 0 )
    {
      clConditOmegaCalculator * p_oOutput = new clConditOmegaCalculator( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oOutput;
    }
    else if ( strcmp( "Crown Radius Reporter", p_data->cNameString ) == 0 )
    {
     // clCrownRadiusReporter * p_oOutput = new clCrownRadiusReporter( mp_oSimManager );
     // mp_oObjectArray[iIndex] = p_oOutput;
    }
    else if ( strcmp( "FoliarChemistry", p_data->cNameString ) == 0 )
    {
      clFoliarChemistry * p_oOutput = new clFoliarChemistry( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oOutput;
    }
    else if ( strcmp( "StateReporter", p_data->cNameString ) == 0 )
    {
      clStateReporter * p_oOutput = new clStateReporter( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oOutput;
    }
    //*************************************************
    // Test objects
    //*************************************************

    else if ( strcmp( "random seed logger", p_data->cNameString ) == 0 )
    {
      clRandomSeedLogger * p_oTest = new clRandomSeedLogger( mp_oSimManager );
      mp_oObjectArray[iIndex] = p_oTest;
    }
    else
    { //we do not have a recognized type
      modelErr stcErr;
      strcpy( stcErr.cFunction, "clBehaviorManager::CreateBehavior" );
      stcErr.iErrorCode = BAD_DATA;
      sprintf( stcErr.cMoreInfo, "%s%s", "Unrecognized behavior ", p_data->cNameString );
      throw( stcErr );
    }

    //Pass the species, type, and name data to the behavior
    p_oBehavior = dynamic_cast < clBehaviorBase * > ( mp_oObjectArray[iIndex] );
    p_oBehavior->SetSpeciesTypeCombos( p_data->iNumCombos, p_data->p_whatCombos );
    p_oBehavior->SetNameData( p_data->cNameString );
    p_oBehavior->SetBehaviorListNumber( p_data->iBehaviorListNumber );
    iReturnCode = p_oBehavior->ValidateVersionNumber( p_data->fVersion );

    //If the return code was error, throw error
    if ( -1 == iReturnCode )
    {
      modelErr stcErr;
      strcpy( stcErr.cFunction, "clBehaviorManager::CreateBehavior" );
      stcErr.iErrorCode = BAD_DATA;
      strcpy( stcErr.cMoreInfo, "Behavior version number wrong for " );
      strcat( stcErr.cMoreInfo, p_data->cNameString );
      throw( stcErr );
    }
  } //end of try block
  catch ( modelErr & err ) { throw( err ); }
  catch ( modelMsg & msg ) { throw( msg ); } //non-fatal error
  catch ( ... ) {
    modelErr stcErr;
    stcErr.iErrorCode = UNKNOWN;
    strcpy( stcErr.cFunction, "clBehaviorManager::CreateBehavior" );
    throw( stcErr );
  }
}
//---------------------------------------------------------------------------
