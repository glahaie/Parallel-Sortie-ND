//---------------------------------------------------------------------------
#include <stdio.h>
#include "LightOrg.h"
#include "SimManager.h"
#include "TreePopulation.h"
#include "ParsingFunctions.h"
#include "Allometry.h"
#include <iostream>
//#include <cstdlib> // getenv & atoi
#include <vector> // parallel_for
//#include <string> //treatment of getenv

//Intel Threading Building Block
//#include "tbb/parallel_invoke.h"
#include "tbb/parallel_for.h"
#include "tbb/task_group.h"
#include "tbb/tick_count.h"
//#include "tbb/task_scheduler_init.h"
#include "tbb/partitioner.h"
#include "tbb/blocked_range.h"
#include "tbb/pipeline.h"

using namespace tbb;

//////////////////////////////////////////////////////////////////////////////
// Constructor
//////////////////////////////////////////////////////////////////////////////
clLightOrg::clLightOrg( clLightBase * p_oHookedShell )
{
  try
  {
    //Initialize variables to 0, NULL, etc.
    mp_oLightFunctionTable = NULL;
    mp_iLightCodes = NULL;
    m_iTotalSpecies = 0;
    m_iTotalTypes = 0;
    mp_fLightExtCoef = NULL;
    mp_fSnagLightExtCoef = NULL;
    mp_iSnagAgeClasses = NULL;
    m_fBeamFracGlobRad = 0;
    m_fClearSkyTransCoeff = 0;
    m_iFirstJulDay = 0;
    m_iLastJulDay = 0;
    m_fMaxTreeHeight = 0;

    m_iNumSnagAgeClasses = 3;

    //Make sure the hooked shell object pointer isn't NULL - if it is throw
    //error
    if ( NULL == p_oHookedShell )
    {
      modelErr stcErr;
      strcpy( stcErr.cFunction, "clLightOrg::clLightOrg" );
      strcpy( stcErr.cMoreInfo, "Null pointer was passed to the function." );
      stcErr.iErrorCode = CANT_FIND_OBJECT;
      throw( stcErr );
    }

    //Otherwise - set the flag on the shell object that it's hooked
    p_oHookedShell->m_bHooked = true;
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
    strcpy( stcErr.cFunction, "clLightOrg::clLightOrg" );
    throw( stcErr );
  }
}


//////////////////////////////////////////////////////////////////////////////
// Destructor
//////////////////////////////////////////////////////////////////////////////
clLightOrg::~clLightOrg()
{
  int i; //loop counter
  //Delete all arrays
  delete[] mp_fLightExtCoef;

  if ( mp_oLightFunctionTable )
    for ( i = 0; i < m_iTotalSpecies; i++ )
      delete[] mp_oLightFunctionTable[i];

  if ( mp_iLightCodes )
    for ( i = 0; i < m_iTotalSpecies; i++ )
      delete[] mp_iLightCodes[i];

  if ( mp_fSnagLightExtCoef )
    for ( i = 0; i < m_iNumSnagAgeClasses; i++ )
      delete[] mp_fSnagLightExtCoef[i];

  delete[] mp_oLightFunctionTable;
  delete[] mp_iLightCodes;
  delete[] mp_fSnagLightExtCoef;
  delete[] mp_iSnagAgeClasses;
}


//////////////////////////////////////////////////////////////////////////////
// DoSetup
//////////////////////////////////////////////////////////////////////////////
void clLightOrg::DoSetup( clSimManager * p_oSimManager, xercesc::DOMDocument * p_oDoc )
{
  try
  {
    short int i; //loop counter

    //Double-check - if either pointer passed is NULL, throw an error
    if ( NULL == p_oSimManager || NULL == p_oDoc )
    {
      modelErr stcErr;
      strcpy( stcErr.cFunction, "clLightOrg::DoSetup" );
      strcpy( stcErr.cMoreInfo, "Null pointer was passed to the function." );
      stcErr.iErrorCode = CANT_FIND_OBJECT;
      throw( stcErr );
    }

    //If the number of years per timestep is not an integer, throw an error
    float fNumYearsPerTimestep = p_oSimManager->GetNumberOfYearsPerTimestep();
    if ( fabs( clModelMath::Round( fNumYearsPerTimestep, 0 ) - fNumYearsPerTimestep ) > 0 )
    {
      modelErr stcErr;
      strcpy( stcErr.cFunction, "clLightOrg::DoSetup" );
      strcpy( stcErr.cMoreInfo, "Light cannot be used if there is not an integer number of years per timestep." );
      stcErr.iErrorCode = BAD_DATA;
      throw( stcErr );
    }

    //Get the tree population object, and from it the numbers of species and types
    mp_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    m_iTotalSpecies = mp_oPop->GetNumberOfSpecies();
    m_iTotalTypes = mp_oPop->GetNumberOfTypes();

    //Declare the light variable arrays
    mp_fLightExtCoef = new float[m_iTotalSpecies];
    if ( mp_oPop->GetUsesSnags() )
    {
      mp_iSnagAgeClasses = new int[m_iNumSnagAgeClasses];
      mp_fSnagLightExtCoef = new float * [m_iNumSnagAgeClasses];
      for ( i = 0; i < m_iNumSnagAgeClasses; i++ )
        mp_fSnagLightExtCoef[i] = new float[m_iTotalSpecies];
    }

    //Get needed data from the parameter file
    GetParameterFileData( p_oSimManager, p_oDoc );

    //Calculate maximum tree height
    clAllometry *p_oAllom = mp_oPop->GetAllometryObject();
    for ( i = 0; i < m_iTotalSpecies; i++ )
      if ( p_oAllom->GetMaxTreeHeight( i ) > m_fMaxTreeHeight )
        m_fMaxTreeHeight = p_oAllom->GetMaxTreeHeight( i );

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
    strcpy( stcErr.cFunction, "clLightOrg::DoSetup" );
    throw( stcErr );
  }
}


//////////////////////////////////////////////////////////////////////////////
// PopulateLightFunctionsTable()
//////////////////////////////////////////////////////////////////////////////
void clLightOrg::PopulateLightFunctionsTable( clSimManager * p_oSimManager, clTreePopulation * p_oPop )
{
  try
  {
    clBehaviorBase * p_oTempBehavior; //for going through behaviors looking for
    //light shells
    clLightBase * p_oLightShell; //light shell object
    char cBehaviorName[MAX_NAMESTRING_SIZE], //behavior namestrings
         cShellMarker[] = "lightshell";
    stcSpeciesTypeCombo combo; //species/type combo from a behavior
    short int iNumBehaviors, //total number of behaviors
         iNumCombos, //number of species/type combos for a behavior
         i, j, //loop counters
         iTotalSpecies = p_oPop->GetNumberOfSpecies(), iTotalTypes = p_oPop->GetNumberOfTypes();

    //Declare the table - it's # species by # types
    mp_oLightFunctionTable = new clLightBase * * [iTotalSpecies];
    for ( i = 0; i < iTotalSpecies; i++ )
    {
      mp_oLightFunctionTable[i] = new clLightBase * [iTotalTypes];
      for ( j = 0; j < iTotalTypes; j++ )
        mp_oLightFunctionTable[i] [j] = NULL;
    }

    //Now go through all the behaviors to pick out the light shells - should have
    //the string "lightshell" in their namestrings
    //Get total number of behaviors
    iNumBehaviors = p_oSimManager->GetNumberOfBehaviors();
    for ( i = 0; i < iNumBehaviors; i++ )
    {
      p_oTempBehavior = p_oSimManager->GetBehaviorObject( i );
      strcpy( cBehaviorName, p_oTempBehavior->GetName() );
      if ( NULL != strstr( cBehaviorName, cShellMarker ) )
      {
        //This is a light shell object - cast its pointer as such
        p_oLightShell = dynamic_cast < clLightBase * > ( p_oTempBehavior );

        //Find out which species/type combos this shell wants to act on,
        //and set its pointer in that place in the table
        iNumCombos = p_oLightShell->GetNumSpeciesTypeCombos();
        for ( j = 0; j < iNumCombos; j++ )
        {
          combo = p_oLightShell->GetSpeciesTypeCombo( j );

          //Make sure another light shell hasn't already claimed this combo -
          //if it has, throw an error.  If not, assign this pointer
          if ( mp_oLightFunctionTable[combo.iSpecies] [combo.iType] != NULL )
          {
            modelErr stcErr;
            strcpy( stcErr.cFunction, "clLightOrg::DoSetup" );
            sprintf( stcErr.cMoreInfo, "%s%d%s%d%s", "Type/species combo species=", combo.iSpecies, " type=", combo.iType,
                 " has more than one light object assigned." );
            stcErr.iErrorCode = DATA_READ_ONLY;
            throw( stcErr );
          }
          else
            mp_oLightFunctionTable[combo.iSpecies] [combo.iType] = p_oLightShell;
        }
      } //end of if (NULL != strstr(cBehaviorName, cShellMarker))
    } //end of for (i = 0; i < iNumBehaviors; i++)
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
    strcpy( stcErr.cFunction, "clLightOrg::PopulateLightFunctionsTable" );
    throw( stcErr );
  }
}


//////////////////////////////////////////////////////////////////////////////
// GetParameterFileData()
//////////////////////////////////////////////////////////////////////////////
void clLightOrg::GetParameterFileData( clSimManager * p_oSimManager, xercesc::DOMDocument * p_oDoc )
{
  try
  {
    DOMElement * p_oElement; //for retrieving values from the parameter file
    clLightBase * p_oTemp; //for finding light objects
    int iVal;
    short int //iTotalTypes = mp_oPop->GetNumberOfTypes(),
         iNumBehaviors = p_oSimManager->GetNumberOfBehaviors(), i, j; //loop counters
    bool bNeedParameters = false;

    //See if anybody needs the common parameters.  Do this by checking the
    //whole behavior list.  This allows us to find all light-base-descended
    //behaviors, including those that don't belong in the light shell list
    for ( i = 0; i < iNumBehaviors; i++ )
    {
      //Can this behavior be casted to a light object?
      p_oTemp = dynamic_cast < clLightBase * > ( p_oSimManager->GetBehaviorObject( i ) );
      if ( p_oTemp != NULL && p_oTemp->m_bNeedsCommonParameters == true )
      {
        bNeedParameters = true;
        break;
      }
    }

    if ( !bNeedParameters ) return;

    //Get the root node of the parameter file
    p_oElement = p_oDoc->getDocumentElement();

    //Get each needed value - if these are missing they'll throw an error
    //Beam fraction global radiation
    FillSingleValue( p_oElement, "li_beamFractGlobalRad", & m_fBeamFracGlobRad, true );
    //Light extinction coefficient
    FillSpeciesSpecificValue( p_oElement, "li_lightExtinctionCoefficient", "li_lecVal", mp_fLightExtCoef, mp_oPop, true );
    //Clear sky transmission coefficient
    FillSingleValue( p_oElement, "li_clearSkyTransCoeff", & m_fClearSkyTransCoeff, true );
    //Make sure not zero
    if ( fabs( m_fClearSkyTransCoeff - 0 ) < 0.001 )
    {
      modelErr stcErr;
      stcErr.iErrorCode = BAD_DATA;
      strcpy( stcErr.cFunction, "clLightOrg::GetParameterFileData" );
      strcpy( stcErr.cMoreInfo, "The value for clear sky transmission coefficient cannot be 0." );
      throw( stcErr );
    }


    //Start of growing season
    FillSingleValue( p_oElement, "li_julianDayGrowthStarts", & m_iFirstJulDay, true );
    //End of growing season
    FillSingleValue( p_oElement, "li_julianDayGrowthEnds", & m_iLastJulDay, true );

    //Snag parameters, if appropriate
    if ( mp_fSnagLightExtCoef )
    {
      //Light extinction coefficient for snag age class 1
      FillSpeciesSpecificValue( p_oElement, "li_snag1LightExtinctionCoefficient", "li_s1lecVal",
           mp_fSnagLightExtCoef[0], mp_oPop, true );

      //Light extinction coefficient for snag age class 2
      FillSpeciesSpecificValue( p_oElement, "li_snag2LightExtinctionCoefficient", "li_s2lecVal",
           mp_fSnagLightExtCoef[1], mp_oPop, true );

      //Light extinction coefficient for snag age class 3
      FillSpeciesSpecificValue( p_oElement, "li_snag3LightExtinctionCoefficient", "li_s3lecVal",
           mp_fSnagLightExtCoef[2], mp_oPop, true );

      //Snag age class 1
      FillSingleValue( p_oElement, "li_snagAgeClass1", & iVal, true );
      mp_iSnagAgeClasses[0] = iVal;

      //Snag age class 2
      FillSingleValue( p_oElement, "li_snagAgeClass2", & iVal, true );
      mp_iSnagAgeClasses[1] = iVal;

      //Infinity-like value for age class 3
      mp_iSnagAgeClasses[2] = 10000;

      //Make sure the age classes are positive numbers that don't overlap
      if ( mp_iSnagAgeClasses[0] < 0 || mp_iSnagAgeClasses[1] < 0 || mp_iSnagAgeClasses[1] < mp_iSnagAgeClasses[0] )
      {
        modelErr stcErr;
        stcErr.iErrorCode = BAD_DATA;
        strcpy( stcErr.cFunction, "clLightOrg::GetParameterFileData" );
        strcpy( stcErr.cMoreInfo, "Snag age classes must be positive and cannot overlap." );
        throw( stcErr );
      }
    }

    //Make sure the light extinction coefficients are all between 0 and 1
    for ( i = 0; i < m_iTotalSpecies; i++ )
    {
      if ( mp_fLightExtCoef[i] < 0.0 || mp_fLightExtCoef[i] > 1.0 )
      {
        modelErr stcErr;
        stcErr.iErrorCode = BAD_DATA;
        strcpy( stcErr.cFunction, "clLightOrg::GetParameterFileData" );
        strcpy( stcErr.cMoreInfo, "All light extinction coefficient values must be between 0 and 1." );
        throw( stcErr );
      }
    }

    if ( mp_fSnagLightExtCoef )
    {
      for ( i = 0; i < m_iNumSnagAgeClasses; i++ )
      {
        for ( j = 0; j < m_iTotalSpecies; j++ )
        {
          if ( mp_fSnagLightExtCoef[i] [j] < 0.0 || mp_fSnagLightExtCoef[i] [j] > 1.0 )
          {
            modelErr stcErr;
            stcErr.iErrorCode = BAD_DATA;
            strcpy( stcErr.cFunction, "clLightOrg::GetParameterFileData" );
            strcpy( stcErr.cMoreInfo, "All light extinction coefficient values must be between 0 and 1." );
            throw( stcErr );
          }
        }
      }
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
    strcpy( stcErr.cFunction, "clLightOrg::GetParameterFileData" );
    throw( stcErr );
  }
}


//////////////////////////////////////////////////////////////////////////////
// DoTreeDataMemberRegistrations()
//////////////////////////////////////////////////////////////////////////////
void clLightOrg::DoTreeDataMemberRegistrations( clSimManager * p_oSimManager, clTreePopulation * p_oPop )
{
  try
  {
    char cLabel[] = "Light";
    short int i, j, //loop counters
              iTotalTypes = p_oPop->GetNumberOfTypes();

    m_iTotalSpecies = p_oPop->GetNumberOfSpecies();

    //Declare and initialize the return codes array
    mp_iLightCodes = new short int * [m_iTotalSpecies];
    for ( i = 0; i < m_iTotalSpecies; i++ )
    {
      mp_iLightCodes[i] = new short int[iTotalTypes];
      for ( j = 0; j < iTotalTypes; j++ )
        mp_iLightCodes[i] [j] = -1;
    }

    //Assemble the light functions table
    PopulateLightFunctionsTable( p_oSimManager, p_oPop );

    //Now go through the light functions table and register the variable for
    //each species/type combo with a valid pointer
    for ( i = 0; i < m_iTotalSpecies; i++ )
      for ( j = 0; j < iTotalTypes; j++ )
        if ( NULL != mp_oLightFunctionTable[i] [j] )
          mp_iLightCodes[i] [j] = p_oPop->RegisterFloat( cLabel, i, j );

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
    strcpy( stcErr.cFunction, "clLightOrg::DoTreeDataMemberRegistrations" );
    throw( stcErr );
  }
}

/******************************************************************************
 * Functions and enums used in parallel implementation
 *****************************************************************************/


//applyLight: checks if the tree is dead or not, if not, it calls the appropriate
//method. This is the code that was executed in the original while loop,as is.
void applyLight(clTree *p_oTree, clTreePopulation *mp_oPop,
        clLightBase *** mp_oLightFunctionTable, short int **mp_iLightCodes)
{
    //Get the tree's species and type
    short int iSp = p_oTree->GetSpecies();
    short int iType = p_oTree->GetType();
    if ( NULL != mp_oLightFunctionTable[iSp] [iType] )
    {
        //Make sure this tree is not dead from a previous disturbance
        short int iDeadCode = mp_oPop->GetIntDataCode( "dead", iSp, p_oTree->GetType() );
        int iIsDead;
        if ( -1 != iDeadCode )
        {
            p_oTree->GetValue( iDeadCode, & iIsDead );
        }
        else
         iIsDead = notdead;

        if ( notdead == iIsDead )
        {
            float fLightVal = mp_oLightFunctionTable[iSp] [iType]->CalcLightValue( p_oTree, mp_oPop );

            //Assign the value to the "Light" float data member of the tree
            p_oTree->SetValue( mp_iLightCodes[iSp] [iType], fLightVal, false );
        }
    }
}

//Choices for parallel algorithms in doLightAssignments()
enum ParallelOptions {SEQUENTIAL, PARALLEL_PIPELINE, PARALLEL_TASKS, PARALLEL_FOR};

//////////////////////////////////////////////////////////////////////////////
// DoLightAssignments()
//////////////////////////////////////////////////////////////////////////////
void clLightOrg::DoLightAssignments()
{
	//Functor for the task_group
	class Optimize {
	private:
	  clTree *p_oTree;
	  clTreePopulation *mp_oPop;
	  clLightBase ***mp_oLightFunctionTable;
	  short int **mp_iLightCodes;

	public:
		Optimize(clTree *p_oTree_ ,clTreePopulation *mp_oPop_, clLightBase *** mp_oLightFunctionTable_, short int **mp_iLightCodes_)
		  : p_oTree(p_oTree_), mp_oPop(mp_oPop_), mp_oLightFunctionTable(mp_oLightFunctionTable_), mp_iLightCodes(mp_iLightCodes_)
		{}

        void operator() () {
        applyLight(p_oTree, mp_oPop, mp_oLightFunctionTable, mp_iLightCodes);
    }

  };

  //Choosing the type of parallel approach we want
  char *parallel = getenv("PARALLEL");
  ParallelOptions option = SEQUENTIAL;
  if(parallel !=NULL) {
    if(strcmp(parallel, "PARALLEL_PIPELINE") == 0) {
        option = PARALLEL_PIPELINE;
    } else if(strcmp(parallel, "PARALLEL_TASKS") == 0) {
        option = PARALLEL_TASKS;
    } else if (strcmp(parallel, "PARALLEL_FOR") == 0) {
        option = PARALLEL_FOR;
    }
  }

  try
  {
    clTreeSearch * p_oAllTrees; //search object for getting all trees
    clTree * p_oTree; //for working with a single tree

    //Ask the tree population to find all trees
    p_oAllTrees = mp_oPop->Find( "all" );

    //Go through the trees one at a time
    if(option == PARALLEL_PIPELINE) {
        parallel_pipeline(10,
                make_filter<void, clTree *>(
                    filter::serial,
                    [&] (flow_control& fc)-> clTree* {
                        clTree * nextTree = p_oAllTrees->NextTree();
                        if (nextTree != NULL) {
                            return nextTree;
                        } else {
                            fc.stop();
                            return NULL;
                        }
                    }) &
                make_filter<clTree *,void>(
                    filter::parallel,
                    [&](clTree * nextTree) {
                        applyLight(nextTree, mp_oPop, mp_oLightFunctionTable, mp_iLightCodes);
                    })
                );
    } else if(option == PARALLEL_TASKS) {

        p_oTree = p_oAllTrees->NextTree();
        task_group g;
        while ( p_oTree )
        {
            Optimize A (p_oTree, mp_oPop, mp_oLightFunctionTable, mp_iLightCodes);
            g.run( A );
            p_oTree = p_oAllTrees->NextTree();
        } //end of while (p_oTree)
        g.wait();
	
    } else if (option == PARALLEL_FOR) {

      
        p_oTree = p_oAllTrees->NextTree();
        std::vector<clTree*> trees;

	//Create a vector containing all the trees
        while(p_oTree) {
            trees.push_back(p_oTree);
            p_oTree = p_oAllTrees->NextTree();
        }

        static affinity_partitioner ap;
        parallel_for(blocked_range<size_t>(0,trees.size()),
                [&] (blocked_range<size_t> r) {
                    for(size_t i = r.begin(); i != r.end(); ++i) {
                        applyLight(trees[i], mp_oPop, mp_oLightFunctionTable, mp_iLightCodes);
                    }
                },
                ap);

    } else {
        p_oTree = p_oAllTrees->NextTree();
        while(p_oTree) {
            applyLight(p_oTree, mp_oPop, mp_oLightFunctionTable, mp_iLightCodes);
            p_oTree = p_oAllTrees->NextTree();
        }
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
    strcpy( stcErr.cFunction, "clLightOrg::DoLightAssignments" );
    throw( stcErr );
  }
}


//////////////////////////////////////////////////////////////////////////////
// GetLightExtCoeff()
//////////////////////////////////////////////////////////////////////////////
float clLightOrg::GetLightExtCoeff( clTree * p_oTree )
{
  try
  {
    int iSpecies = p_oTree->GetSpecies();
    if ( clTreePopulation::snag == p_oTree->GetType() )
    {
      if (mp_fSnagLightExtCoef) {
        int iAge, i;
        //Get the snag's age
        p_oTree->GetValue( mp_oPop->GetAgeCode( iSpecies ), & iAge );
        for ( i = 0; i < m_iNumSnagAgeClasses; i++ )
        {
          if ( iAge <= mp_iSnagAgeClasses[i] )
          {
            return mp_fSnagLightExtCoef[i] [iSpecies];
          }
        }
      }
      else {
        //This is an unexpected snag and it shouldn't shade, so give back a
        //value of 1 (no light blocked)
        return 1.0;
      }
    }
    else
    {
      return mp_fLightExtCoef[iSpecies];
    }
    return 0;
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
    strcpy( stcErr.cFunction, "clLightOrg::GetLightExtinctionCoefficient" );
    throw( stcErr );
  }
}
