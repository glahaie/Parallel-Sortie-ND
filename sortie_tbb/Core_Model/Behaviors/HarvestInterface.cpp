//---------------------------------------------------------------------------
#include "HarvestInterface.h"
#include "SimManager.h"
#include "Grid.h"
#include "ParsingFunctions.h"
#include "TreePopulation.h"
#include "Disturbance.h"
#include "PlatformFuncs.h"
#include <stdio.h>
//#include <io.h>
#include <fstream>
#include <math.h>

#define PARAM_FILE_LINE_LENGTH 1000
//---------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////
// Constructor
/////////////////////////////////////////////////////////////////////////////
clHarvestInterface::clHarvestInterface( clSimManager * p_oSimManager ) : clWorkerBase( p_oSimManager ), clBehaviorBase( p_oSimManager )
{
  try
  {
    strcpy( m_cNameString, "HarvestInterface" );
    m_sXMLRoot = "HarvestInterface";

    //Versions
    m_fVersionNumber = 1.1;
    m_fMinimumVersionNumber = 1;

    //Allowed file types
    m_iNumAllowedTypes = 2;
    mp_iAllowedFileTypes = new int[m_iNumAllowedTypes];
    mp_iAllowedFileTypes[0] = parfile;
    mp_iAllowedFileTypes[1] = detailed_output;

    m_iReasonCode = harvest;

    mp_cNewTreeDataMembers = NULL;
    mp_cFileColumns = NULL;
    mp_bAppliesToTrees = NULL;
    //mp_fInitialValues = NULL;
    mp_iMemberType = NULL;
    mp_bUserDefinedColumn = NULL;
    mp_iColumnTranslation = NULL;

    mp_oResultsGrid = NULL;
    mp_iDenCutCodes = NULL;
    mp_iBaCutCodes = NULL;

    strcpy(m_cExecutable, "");
    strcpy(m_cInputFile, "");
    strcpy(m_cTreesToCutFile, "");
    strcpy(m_cTreesToUpdateFile, "");
    strcpy(m_cBatchFileIn, "");
    strcpy(m_cBatchParamsOut, "");
    strcpy(m_cArguments, "");

    m_iNewTreeFloats = 0;
    m_iNumFileColumns = 0;
  }
  catch ( modelErr & err )
  {
    throw( err );
  } //non-fatal error
  catch ( ... )
  {
    modelErr stcErr;
    stcErr.iErrorCode = UNKNOWN;
    strcpy( stcErr.cFunction, "clHarvestInterface::clHarvestInterface" );
    throw( stcErr );
  }
}

/////////////////////////////////////////////////////////////////////////////
// Destructor
/////////////////////////////////////////////////////////////////////////////
clHarvestInterface::~clHarvestInterface()
{
  int i;

  if (mp_cNewTreeDataMembers) {
    for (i = 0; i < m_iNewTreeFloats; i++)
      delete[] mp_cNewTreeDataMembers[i];
  }
  delete[] mp_cNewTreeDataMembers;

  if (mp_cFileColumns) {
    for (i = 0; i < m_iNumFileColumns; i++)
      delete[] mp_cFileColumns[i];
  }
  delete[] mp_cFileColumns;

  if (mp_bAppliesToTrees) {
    for (i = 0; i < m_iNumSpecies; i++)
      delete[] mp_bAppliesToTrees[i];
  }
  delete[] mp_bAppliesToTrees;
  delete[] mp_iMemberType;
  //delete[] mp_fInitialValues;
  delete[] mp_bUserDefinedColumn;
  delete[] mp_iColumnTranslation;;

  if ( mp_iDenCutCodes )
    for ( i = 0; i < m_iNumAllowedCutRanges; i++ )
    {
      delete[] mp_iDenCutCodes[i];
      delete[] mp_iBaCutCodes[i];
    }
}

/////////////////////////////////////////////////////////////////////////////
// SetNameData
/////////////////////////////////////////////////////////////////////////////
void clHarvestInterface::SetNameData(char *cNameString)
{
  //See if any data members have been passed in on the namestring
  char *p_cStart = NULL, *p_cEnd = NULL, *p_cLoop = NULL;
  int i, iValNum, iCharCount;

  p_cStart = strchr(cNameString, '(');
  if (NULL == p_cStart) {
    //No data members passed
    m_iNewTreeFloats = 0;
    return;
  }

  //How many new data members are there?
  while (NULL != p_cStart) {
    m_iNewTreeFloats++;
    p_cStart++;
    p_cStart = strchr(p_cStart, '(');
  }

  //Declare a place for these new labels
  mp_cNewTreeDataMembers = new char*[m_iNewTreeFloats];
  for (i = 0; i < m_iNewTreeFloats; i++) {
    mp_cNewTreeDataMembers[i] = new char[MAX_TREE_LABEL_SIZE];
    strcpy(mp_cNewTreeDataMembers[i], "");
  }
  //mp_fInitialValues = new float[m_iNewTreeFloats];

  //Parse out the data members
  iValNum = 0;
  p_cStart = strchr(cNameString, '(');
  while (NULL != p_cStart) {

    //Get the name
    p_cEnd = strchr(p_cStart, ')');
    if (NULL == p_cEnd) {
      modelErr stcErr;
      stcErr.iErrorCode = DATA_MISSING;
      strcpy( stcErr.cMoreInfo, "Couldn't parse out the new data members." );
      strcpy( stcErr.cFunction, "clHarvestInterface::SetNameData" );
      throw( stcErr );
    }

    p_cStart++;
    iCharCount = 0;
    for (p_cLoop = p_cStart; p_cLoop != p_cEnd &&
                               iCharCount < MAX_TREE_LABEL_SIZE-1; p_cLoop++) {
      mp_cNewTreeDataMembers[iValNum][iCharCount] = *p_cLoop;
      iCharCount++;
    }
    mp_cNewTreeDataMembers[iValNum][iCharCount] = '\0';

    //Was the name too long?
    if ((iCharCount = MAX_TREE_LABEL_SIZE - 1) && (p_cLoop != p_cEnd)) {
      modelErr stcErr;
      stcErr.iErrorCode = DATA_MISSING;
      sprintf( stcErr.cMoreInfo, "%s%s%s", "New data member name too long: \"",
                 mp_cNewTreeDataMembers[iValNum], "\"." );
      strcpy( stcErr.cFunction, "clHarvestInterface::SetNameData" );
      throw( stcErr );
    }

    //Get the initial value
    /*p_cStart = strchr(p_cStart, '@');
    p_cEnd = strchr(p_cStart, ')');
    if (NULL == p_cEnd) {
      modelErr stcErr;
      stcErr.iErrorCode = DATA_MISSING;
      strcpy( stcErr.cMoreInfo, "Couldn't parse out the new data members." );
      strcpy( stcErr.cFunction, "clHarvestInterface::SetNameData" );
      throw( stcErr );
    }
    strcpy(p_cTemp, "");
    p_cStart++;
    p_cEnd--;
    iCharCount = 0;
    for (p_cLoop = p_cStart; p_cLoop != p_cEnd; p_cLoop++) {
      p_cTemp[iCharCount] = *p_cLoop;
      iCharCount++;
    }
    p_cTemp[iCharCount] = '\0';

    //Transform to a float
    mp_fInitialValues[iValNum] = atof(p_cTemp);
    if (0 == mp_fInitialValues[iValNum] &&
        '0' != p_cTemp[0]) {
      modelErr stcErr;
      stcErr.iErrorCode = DATA_MISSING;
      sprintf( stcErr.cMoreInfo, "%s%s%s%s%s",
           "Initial value for new tree data member \"",
           mp_cNewTreeDataMembers[iValNum], "\" is not a number: \"",
           p_cTemp, "\"." );
      strcpy( stcErr.cFunction, "clHarvestInterface::SetNameData" );
      throw( stcErr );
    } */

    iValNum++;
    p_cStart = strchr(p_cStart, '(');
  }
}

/////////////////////////////////////////////////////////////////////////////
// RegisterTreeDataMembers
/////////////////////////////////////////////////////////////////////////////
void clHarvestInterface::RegisterTreeDataMembers()
{
  clTreePopulation *p_oPop = (clTreePopulation*) mp_oSimManager->GetPopulationObject("treepopulation");
  int iNumTypes, iSp, iTp, i;

  //Set up the species/type applies-to array
  m_iNumSpecies = p_oPop->GetNumberOfSpecies();
  iNumTypes = p_oPop->GetNumberOfTypes();

  mp_bAppliesToTrees = new bool*[m_iNumSpecies];
  for (iSp = 0; iSp < m_iNumSpecies; iSp++) {
    mp_bAppliesToTrees[iSp] = new bool[iNumTypes];
    for (iTp = 0; iTp < iNumTypes; iTp++) {
      mp_bAppliesToTrees[iSp][iTp] = false;
    }
  }

  for (i = 0; i < m_iNumSpeciesTypeCombos; i++) {
    mp_bAppliesToTrees[mp_whatSpeciesTypeCombos[i].iSpecies]
                      [mp_whatSpeciesTypeCombos[i].iType] = true;
  }

  if (0 == m_iNewTreeFloats) return;

  for (iSp = 0; iSp < m_iNumSpecies; iSp++) {
    for (iTp = 0; iTp < iNumTypes; iTp++) {
      if (mp_bAppliesToTrees[iSp][iTp]) {
        for (i = 0; i < m_iNewTreeFloats; i++) {
          p_oPop->RegisterFloat(mp_cNewTreeDataMembers[i], iSp, iTp);
        }
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////
// GetData()
//////////////////////////////////////////////////////////////////////////////
void clHarvestInterface::GetData( xercesc::DOMDocument * p_oDoc )
{
  try
  {
    using namespace std;
    DOMNodeList *p_oColumns,
                *p_oAllColumns;
    DOMElement * p_oElement = GetParentParametersElement(p_oDoc);
    clTreePopulation * p_oPop = ( clTreePopulation * ) mp_oSimManager->GetPopulationObject( "treepopulation" );
    ofstream parametersOut;
    ifstream parametersIn;
    char *cData, cTemp[PARAM_FILE_LINE_LENGTH];
    float fNumYearsPerTS = mp_oSimManager->GetNumberOfYearsPerTimestep();
    int iNumColumns, //number of extra columns added by user to input file
        iNumBaseColumns = 6, //number of default required columns
        iSp, iTp, i, j, //loop counters
        iNumLines, //line counter
        iCode,
        iParamLine, //line on the batch parameters file, if applicable
        iNumTypes = p_oPop->GetNumberOfTypes();

    //***********************************
    //Setup the "Harvest Results" grid
    //***********************************

    SetupResultsGrid();


    //***********************************
    //Read parameters
    //***********************************

    //Executable
    FillSingleValue( p_oElement, "hi_executable", m_cExecutable, MAX_FILENAME_SIZE, true );

    //Make sure that the harvest executable exists
    if (!DoesFileExist(m_cExecutable)) {
      modelErr stcErr;
      stcErr.iErrorCode = CANT_FIND_OBJECT;
      sprintf( stcErr.cMoreInfo, "%s%s", "Missing file: ", m_cExecutable );
      strcpy( stcErr.cFunction, "clHarvestInterface::GetData" );
      throw( stcErr );
    }

    // Path and filename of the input file to the harvest executable
    FillSingleValue( p_oElement, "hi_harvestableTreesFile", m_cInputFile, MAX_FILENAME_SIZE, true );

    // Path and filename of the file of the trees to cut that is created by the
    // harvest executable
    FillSingleValue( p_oElement, "hi_treesToHarvestFile", m_cTreesToCutFile, MAX_FILENAME_SIZE, true );

    // Harvest period
    FillSingleValue( p_oElement, "hi_harvestPeriod", &m_iPeriod, true );
    if (0 > m_iPeriod) {
      modelErr stcErr;
      stcErr.iErrorCode = BAD_DATA;
      sprintf( stcErr.cMoreInfo, "%s%d%s",
         "Harvest period must be a non-negative number. Value: \"",
         m_iPeriod, "\"." );
      strcpy( stcErr.cFunction, "clHarvestInterface::GetData" );
      throw( stcErr );
    }
    if (m_iPeriod > 0) {
      m_iPeriod /= (int)fNumYearsPerTS;
      if (m_iPeriod < 1)
        m_iPeriod = 1;
    }
    m_iNextTimestepToHarvest = m_iPeriod;

    // Path and filename of the file of the trees to update that is created by
    // the harvest executable - optional
    if (m_iNewTreeFloats > 0) {
      FillSingleValue( p_oElement, "hi_treesToUpdateFile", m_cTreesToUpdateFile, MAX_FILENAME_SIZE, false );
    }

    // Argument string to pass to the user executable - optional
    FillSingleValue( p_oElement, "hi_executableArguments", m_cArguments, MAX_ARGUMENT_LENGTH, false );

    //***********************************
    //Read parameters for and set up the file columns
    //***********************************
    // List of columns beyond the defaults - optional
    m_iNumFileColumns = iNumBaseColumns;
    p_oAllColumns = p_oElement->getElementsByTagName( XMLString::transcode( "hi_dataMembers" ) );
    if (0 < p_oAllColumns->getLength()) {
      p_oElement = ( DOMElement * ) p_oAllColumns->item( 0 );

      p_oColumns = p_oElement->getElementsByTagName( XMLString::transcode( "hi_dataMember" ) );
      iNumColumns = p_oColumns->getLength();

      if (iNumColumns > 0) {
        m_iNumFileColumns += iNumColumns;

        //Declare the columns array so we can put the data there
        mp_cFileColumns = new char*[m_iNumFileColumns];
        for (i = 0; i < m_iNumFileColumns; i++) {
          mp_cFileColumns[i] = new char[MAX_TREE_LABEL_SIZE];
          strcpy(mp_cFileColumns[i], "");
        }

        for ( i = 0; i < iNumColumns; i++ )
        {
          cData = xercesc::XMLString::transcode(p_oColumns->item(i)->getChildNodes()->item(0)->getNodeValue());
          strcpy(mp_cFileColumns[iNumBaseColumns + i], cData);
        }
      }
    }
    //Set up the default columns
    if (NULL == mp_cFileColumns) {
      mp_cFileColumns = new char*[m_iNumFileColumns];
      for (i = 0; i < m_iNumFileColumns; i++) {
        mp_cFileColumns[i] = new char[MAX_TREE_LABEL_SIZE];
        strcpy(mp_cFileColumns[i], "");
      }
    }

    mp_iMemberType = new member_type[m_iNumFileColumns];
    for (i = 0; i < m_iNumFileColumns; i++)
      mp_iMemberType[i] = notassigned;

    strcpy(mp_cFileColumns[0], "X");
    mp_iMemberType[0] = isfloat;
    strcpy(mp_cFileColumns[1], "Y");
    mp_iMemberType[1] = isfloat;
    strcpy(mp_cFileColumns[2], "Species");
    mp_iMemberType[2] = isint;
    strcpy(mp_cFileColumns[3], "Type");
    mp_iMemberType[3] = isint;
    strcpy(mp_cFileColumns[4], "Diam");
    mp_iMemberType[4] = isfloat;
    strcpy(mp_cFileColumns[5], "Height");
    mp_iMemberType[5] = isfloat;

    //Verify that any additional columns exist, and what kind they are, and
    //that the kinds agree for all tree types and species
    if (m_iNumFileColumns > iNumBaseColumns) {
      for (i = iNumBaseColumns; i < m_iNumFileColumns; i++) {
        for (iSp = 0; iSp < m_iNumSpecies; iSp++) {
          for (iTp = 0; iTp < iNumTypes; iTp++) {
            if (mp_bAppliesToTrees[iSp][iTp]) {
              iCode = -1;

              //Is it a float?
              if (p_oPop->GetFloatDataCode(mp_cFileColumns[i],iSp, iTp) > -1) {
                iCode = 0;
                if (notassigned == mp_iMemberType[i]) {
                  mp_iMemberType[i] = isfloat;
                } else if (isfloat != mp_iMemberType[i]) {
                  modelErr stcErr;
                  stcErr.iErrorCode = BAD_DATA;
                  sprintf( stcErr.cMoreInfo, "%s%s%s", "Tree data member \"",
                        mp_cFileColumns[i], "\" of ambiguous type." );
                  strcpy( stcErr.cFunction, "clHarvestInterface::GetData" );
                  throw( stcErr );
                }
              }

              //Is it an int?
              if (p_oPop->GetIntDataCode(mp_cFileColumns[i],iSp, iTp) > -1) {
                iCode = 0;
                if (notassigned == mp_iMemberType[i]) {
                  mp_iMemberType[i] = isint;
                } else if (isint != mp_iMemberType[i]) {
                  modelErr stcErr;
                  stcErr.iErrorCode = BAD_DATA;
                  sprintf( stcErr.cMoreInfo, "%s%s%s", "Tree data member \"",
                        mp_cFileColumns[i], "\" of ambiguous type." );
                  strcpy( stcErr.cFunction, "clHarvestInterface::GetData" );
                  throw( stcErr );
                }
              }

              //Is it a bool?
              if (p_oPop->GetBoolDataCode(mp_cFileColumns[i],iSp, iTp) > -1) {
                iCode = 0;
                if (notassigned == mp_iMemberType[i]) {
                  mp_iMemberType[i] = isbool;
                } else if (isbool != mp_iMemberType[i]) {
                  modelErr stcErr;
                  stcErr.iErrorCode = BAD_DATA;
                  sprintf( stcErr.cMoreInfo, "%s%s%s", "Tree data member \"",
                        mp_cFileColumns[i], "\" of ambiguous type." );
                  strcpy( stcErr.cFunction, "clHarvestInterface::GetData" );
                  throw( stcErr );
                }
              }

              //Is it a char?
              if (p_oPop->GetCharDataCode(mp_cFileColumns[i],iSp, iTp) > -1) {
                iCode = 0;
                if (notassigned == mp_iMemberType[i]) {
                  mp_iMemberType[i] = ischar;
                } else if (ischar != mp_iMemberType[i]) {
                  modelErr stcErr;
                  stcErr.iErrorCode = BAD_DATA;
                  sprintf( stcErr.cMoreInfo, "%s%s%s", "Tree data member \"",
                        mp_cFileColumns[i], "\" of ambiguous type." );
                  strcpy( stcErr.cFunction, "clHarvestInterface::GetData" );
                  throw( stcErr );
                }
              }

              //Make sure we found this data member for this tree type and
              //species
              if (-1 == iCode) {
                modelErr stcErr;
                stcErr.iErrorCode = BAD_DATA;
                sprintf( stcErr.cMoreInfo, "%s%s%s%d%s%d%s",
                      "Tree data member \"",
                      mp_cFileColumns[i],
                      "\" missing for trees of species ",
                      iSp, " and type ", iTp, "." );
                strcpy( stcErr.cFunction, "clHarvestInterface::GetData" );
                throw( stcErr );
              }
            }
          }
        }
      }
    }

    mp_bUserDefinedColumn = new bool[m_iNumFileColumns];
    mp_iColumnTranslation = new int[m_iNumFileColumns];
    for (i = 0; i < m_iNumFileColumns; i++) {
      mp_bUserDefinedColumn[i] = false;
      mp_iColumnTranslation[i] = -1;
      for (j = 0; j < m_iNewTreeFloats; j++) {
        if (0 == strcmp(mp_cFileColumns[i], mp_cNewTreeDataMembers[j])) {
          mp_bUserDefinedColumn[i] = true;
          mp_iColumnTranslation[i] = j;
          break;
        }
      }
    }

    //***********************************
    //Process batch parameters, if warranted
    //***********************************
    if (0 < mp_oSimManager->GetBatchNumber()) {

      // Path and filename of the batch parameters input file
      FillSingleValue( p_oElement, "hi_batchParamsFile", m_cBatchFileIn, MAX_FILENAME_SIZE, false );

      //Only continue if we've got a file
      if (0 < strlen(m_cBatchFileIn)) {

        //Make sure that the file exists
        if (!DoesFileExist(m_cBatchFileIn)) {
          modelErr stcErr;
          stcErr.iErrorCode = CANT_FIND_OBJECT;
          sprintf( stcErr.cMoreInfo, "%s%s", "Missing file: ", m_cBatchFileIn );
          strcpy( stcErr.cFunction, "clHarvestInterface::GetData" );
          throw( stcErr );
        }

        // Path and filename of the parameters output file that this will write
        FillSingleValue( p_oElement, "hi_batchSingleRunParamsFile", m_cBatchParamsOut, MAX_FILENAME_SIZE, true );

        //What line are we on in the parameter file?
        iParamLine = mp_oSimManager->GetBatchNumber();

        //Read that line of the parameters
        parametersIn.open( m_cBatchFileIn );
        iNumLines = 1;
        while (!parametersIn.eof() && iNumLines < iParamLine) {
          parametersIn.getline(cTemp, PARAM_FILE_LINE_LENGTH);
          if (strlen(cTemp) > 1)
            iNumLines++;
        }
        if (iNumLines != iParamLine) {
          modelErr stcErr;
          strcpy(stcErr.cFunction, "clHarvestInterface::GetData");
          sprintf(stcErr.cMoreInfo, "%s%d", "Couldn't find parameters for batch run #", iParamLine);
          stcErr.iErrorCode = BAD_FILE;
          throw(stcErr);
        }

        parametersIn.getline(cTemp, PARAM_FILE_LINE_LENGTH);
        if (strlen(cTemp) < 2) {
          modelErr stcErr;
          strcpy(stcErr.cFunction, "clHarvestInterface::GetData");
          sprintf(stcErr.cMoreInfo, "%s%d", "Couldn't find parameters for batch run #", iParamLine);
          stcErr.iErrorCode = BAD_FILE;
          throw(stcErr);
        }
        parametersIn.close();

        //Write parameter file for the executable
        parametersOut.open( m_cBatchParamsOut, ios::trunc | ios::out);

        parametersOut << cTemp;
        parametersOut << endl;
        parametersOut.close();
      }
    }
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
    strcpy( stcErr.cFunction, "clHarvestInterface::GetData" );
    throw( stcErr );
  }
}


//////////////////////////////////////////////////////////////////////////////
// Action()
//////////////////////////////////////////////////////////////////////////////
void clHarvestInterface::Action()
{
  try
  {
    using namespace std;

    ResetResultsGrid();

    if (mp_oSimManager->GetCurrentTimestep() != m_iNextTimestepToHarvest) {
      return;
    } else {
      m_iNextTimestepToHarvest += m_iPeriod;
    }

    fstream harvest, update, harvest2, update2; //harvested tree file
    char cTemp[PARAM_FILE_LINE_LENGTH];
    clTreePopulation * p_oPop = ( clTreePopulation * ) mp_oSimManager->GetPopulationObject( "treepopulation" );
    clTreeSearch *p_oHarvestTrees = p_oPop->Find("all");
    clTree *p_oTree = p_oHarvestTrees->NextTree();
    string sSpecies, sType, sTemp;
    float fVal, fTemp, *p_fX = NULL, *p_fY = NULL, *p_fDiam = NULL, fDiam, fX, fY, fThisBA;
    long int i, j;
    int iSp, iTp, iTemp, iCount, *p_iSp = NULL, *p_iTp = NULL,
        iVal, iNumLines,
        iNumBaseColumns = 6;
    bool bVal, *p_bFound = NULL;

    //Write all applicable trees out to file
    harvest.open( m_cInputFile, ios::out | ios::trunc );

    //Write the first line - current timestep and number of timesteps
    harvest << mp_oSimManager->GetCurrentTimestep()
            << "\t"
            << mp_oSimManager->GetNumberOfTimesteps()
            << "\n";

    //Write the second line - the column names
    harvest << mp_cFileColumns[0];
    for (i = 1; i < m_iNumFileColumns; i++) {
      harvest << "\t" << mp_cFileColumns[i];
    }
    harvest << "\n";

    //Write the trees
    while (p_oTree) {
      iSp = p_oTree->GetSpecies();
      iTp = p_oTree->GetType();

      if (mp_bAppliesToTrees[iSp][iTp]) {

        //Write out the required columns
        //X
        p_oTree->GetValue(p_oPop->GetXCode(iSp, iTp), &fVal);
        harvest << fVal << "\t";

        //Y
        p_oTree->GetValue(p_oPop->GetYCode(iSp, iTp), &fVal);
        harvest << fVal << "\t";

        //Species and type
        harvest << iSp << "\t" << iTp << "\t";

        //Diameter
        if (clTreePopulation::seedling == iTp) {
          p_oTree->GetValue(p_oPop->GetDiam10Code(iSp, iTp), &fVal);
        } else {
          p_oTree->GetValue(p_oPop->GetDbhCode(iSp, iTp), &fVal);
        }
        harvest << fVal << "\t";

        //Height
        p_oTree->GetValue(p_oPop->GetHeightCode(iSp, iTp), &fVal);
        harvest << fVal;

        for (i = iNumBaseColumns; i < m_iNumFileColumns; i++) {
          harvest << "\t";
          if (isfloat == mp_iMemberType[i]) {
            p_oTree->GetValue(p_oPop->GetFloatDataCode(mp_cFileColumns[i], iSp, iTp), &fVal);
            harvest << fVal;
          }
          else if (isint == mp_iMemberType[i]) {
            p_oTree->GetValue(p_oPop->GetIntDataCode(mp_cFileColumns[i], iSp, iTp), &iVal);
            harvest << iVal;
          }
          else if (isbool == mp_iMemberType[i]) {
            p_oTree->GetValue(p_oPop->GetBoolDataCode(mp_cFileColumns[i], iSp, iTp), &bVal);
            harvest << bVal;
          }
          else {
            p_oTree->GetValue(p_oPop->GetFloatDataCode(mp_cFileColumns[i], iSp, iTp), cTemp);
            harvest << cTemp;
          }
        }
        harvest << "\n";
      }
      p_oTree = p_oHarvestTrees->NextTree();
    }
    harvest.close();

    //Call the harvest executable
    LaunchProcess(m_cExecutable, m_cArguments, "");

    //**********************************
    //Harvest trees
    //**********************************
    //Find the output file of harvested trees
    if (!DoesFileExist(m_cTreesToCutFile)) {
      modelErr stcErr;
      stcErr.iErrorCode = BAD_FILE;
      strcpy( stcErr.cMoreInfo, "I can't find the harvested trees file." );
      strcpy( stcErr.cFunction, "clHarvestInterface::Action" );
      throw( stcErr );
    }

    //Count the number of lines
    harvest.open(m_cTreesToCutFile, ios::in );
    iNumLines = -2; //skip the first two lines
    while (!harvest.eof()) {
       harvest.getline(cTemp,100);
       if (strlen(cTemp) > 1)
         iNumLines++;
    }

    if (0 < iNumLines) {
      //Declare arrays to hold all the data
      p_fDiam = new float[iNumLines];
      p_fX = new float[iNumLines];
      p_fY = new float[iNumLines];
      p_iSp = new int[iNumLines];
      p_iTp = new int[iNumLines];
      p_bFound = new bool[iNumLines];

      //Go back to the beginning of the file and read it into the arrays
      iCount = 0;
      harvest.close();
      //I tried to seek the file back to the beginning but couldn't get it to
      //go - so I just started over with a new filestream
      harvest2.open(m_cTreesToCutFile, ios::in );
      //Throw out the first two lines
      harvest2.getline(cTemp, PARAM_FILE_LINE_LENGTH);
      harvest2.getline(cTemp, PARAM_FILE_LINE_LENGTH);

      while (!harvest2.eof() && iCount < iNumLines) {
        //Throw away all columns except the first five (X, Y, type, species,
        //diameter)
        harvest2 >> p_fX[iCount] >> p_fY[iCount] >> p_iSp[iCount]
                 >> p_iTp[iCount] >> p_fDiam[iCount];
        harvest2.getline(cTemp, PARAM_FILE_LINE_LENGTH);

        p_bFound[iCount] = false;
        iCount++;
      }
      harvest2.close();

      //Find each tree in the list and kill it
      p_oHarvestTrees->StartOver();
      p_oTree = p_oHarvestTrees->NextTree();
      while (p_oTree) {
        iSp = p_oTree->GetSpecies();
        iTp = p_oTree->GetType();
        if (clTreePopulation::seedling == iTp) {
          p_oTree->GetValue(p_oPop->GetDiam10Code(iSp, iTp), &fDiam);
        } else {
          p_oTree->GetValue(p_oPop->GetDbhCode(iSp, iTp), & fDiam);
        }
        p_oTree->GetValue(p_oPop->GetXCode(iSp, iTp), & fX);
        p_oTree->GetValue(p_oPop->GetYCode(iSp, iTp), & fY);

        //Try to find it in the list
        for (i = 0; i < iNumLines; i++) {
          if (iSp == p_iSp[i] &&
              iTp == p_iTp[i] &&
              fabs(fDiam - p_fDiam[i]) < 0.001 &&
              fabs(fX - p_fX[i]) < 0.001 &&
              fabs(fY - p_fY[i]) < 0.001 &&
              p_bFound[i] == false) {

            //Kill the tree
            p_oPop->KillTree( p_oTree, m_iReasonCode );

            //Add to harvest results grid
            mp_oResultsGrid->SetValueAtPoint( fX, fY, m_iHarvestTypeCode, clDisturbance::partial );
            mp_oResultsGrid->GetValueAtPoint( fX, fY, mp_iDenCutCodes[0][iSp], & iTemp );
            iTemp += 1;
            mp_oResultsGrid->SetValueAtPoint( fX, fY, mp_iDenCutCodes[0][iSp], iTemp );

			      if (iTp != clTreePopulation::seedling)
            	fThisBA = clModelMath::CalculateBasalArea( fDiam );
            else //tree is a seedling and has no BA
            	fThisBA = 0.0;

            mp_oResultsGrid->GetValueAtPoint( fX, fY, mp_iBaCutCodes[0][iSp], & fTemp );
            fTemp += fThisBA;
            mp_oResultsGrid->SetValueAtPoint( fX, fY, mp_iBaCutCodes[0][iSp], fTemp );

            //Mark it as found
            p_bFound[i] = true;
            break;
          }
        }

        p_oTree = p_oHarvestTrees->NextTree();
      }

      //Make sure all the trees in the list got found
      for (i = 0; i < iNumLines; i++) {
        if (false == p_bFound[i]) {
          modelErr stcErr;
          stcErr.iErrorCode = BAD_DATA;
          sprintf( stcErr.cMoreInfo, "%s%g%s%g%s%d%s%d%s%g%s",
              "Unrecognized tree in harvest file. X = ",
              p_fX[i], ", Y = ", p_fY[i], ", species = ", p_iSp[i],
              ", type = ", p_iTp[i], ", diam = ", p_fDiam[i], ".");
          strcpy( stcErr.cFunction, "clHarvestInterface::Action" );
          throw( stcErr );
        }
      }
    } //end of if (0 < iNumLines) - harvest file reading

    delete[] p_fDiam; p_fDiam = NULL;
    delete[] p_fX; p_fX = NULL;
    delete[] p_fY; p_fY = NULL;
    delete[] p_iSp; p_iSp = NULL;
    delete[] p_iTp; p_iTp = NULL;
    delete[] p_bFound; p_bFound = NULL;

    //**********************************
    //Update trees
    //**********************************
    if ('\0' == m_cTreesToUpdateFile[0]) return;

    //Array to hold values of user variables
    float **p_fNewVals = new float*[m_iNewTreeFloats];
    for (i = 0; i < m_iNewTreeFloats; i++)
      p_fNewVals[i] = NULL;

    //Test to make sure the update file exists
    if (!DoesFileExist(m_cTreesToUpdateFile)) {
      modelErr stcErr;
      stcErr.iErrorCode = BAD_FILE;
      strcpy( stcErr.cMoreInfo, "I can't find the updated trees file." );
      strcpy( stcErr.cFunction, "clHarvestInterface::Action" );
      throw( stcErr );
    }

    //Count the number of lines
    update.open(m_cTreesToUpdateFile, ios::in );
    iNumLines = -2; //skip the first two lines
    while (!update.eof()) {
       update.getline(cTemp,100);
       if (strlen(cTemp) > 1)
         iNumLines++;
    }

    if (0 < iNumLines) {
      //Declare arrays to hold all the data
      p_fDiam = new float[iNumLines];
      p_fX = new float[iNumLines];
      p_fY = new float[iNumLines];
      p_iSp = new int[iNumLines];
      p_iTp = new int[iNumLines];
      p_bFound = new bool[iNumLines];
      for (i = 0; i < m_iNewTreeFloats; i++)
        p_fNewVals[i] = new float[iNumLines];

      //Go back to the beginning of the file and read it into the arrays
      iCount = 0;
      update.close();
      //I tried to seek the file back to the beginning but couldn't get it to
      //go - so I just started over with a new filestream
      update2.open(m_cTreesToUpdateFile, ios::in );
      //Throw out the first two lines
      update2.getline(cTemp, PARAM_FILE_LINE_LENGTH);
      update2.getline(cTemp, PARAM_FILE_LINE_LENGTH);
      while (!update2.eof() && iCount < iNumLines) {
        //Read in the first five columns (X, Y, type, species, diameter)
        update2 >> p_fX[iCount] >> p_fY[iCount] >> p_iSp[iCount]
                >> p_iTp[iCount] >> p_fDiam[iCount];

        //Throw away height
        update2 >> cTemp;

        //Now read in any columns for new user variables
        for (i = iNumBaseColumns; i < m_iNumFileColumns; i++) {
          if (mp_bUserDefinedColumn[i]) {
            update2 >> p_fNewVals[mp_iColumnTranslation[i]][iCount];
          }
          else {
            //Throw away the value
            update2 >> cTemp;
          }
        }

        p_bFound[iCount] = false;
        iCount++;
      }
      update2.close();

      //Find each tree in the list and update it
      p_oHarvestTrees->StartOver();
      p_oTree = p_oHarvestTrees->NextTree();
      while (p_oTree) {
        iSp = p_oTree->GetSpecies();
        iTp = p_oTree->GetType();
        if (clTreePopulation::seedling == iTp) {
          p_oTree->GetValue(p_oPop->GetDiam10Code(iSp, iTp), &fDiam);
        } else {
          p_oTree->GetValue(p_oPop->GetDbhCode(iSp, iTp), & fDiam);
        }
        p_oTree->GetValue(p_oPop->GetXCode(iSp, iTp), & fX);
        p_oTree->GetValue(p_oPop->GetYCode(iSp, iTp), & fY);

        //Try to find it in the list
        for (i = 0; i < iNumLines; i++) {
          if (iSp == p_iSp[i] &&
              iTp == p_iTp[i] &&
              fabs(fDiam - p_fDiam[i]) < 0.001 &&
              fabs(fX - p_fX[i]) < 0.001 &&
              fabs(fY - p_fY[i]) < 0.001 &&
              p_bFound[i] == false) {

            //Update the tree
            for (j = 0; j < m_iNewTreeFloats; j++) {
              p_oTree->SetValue(p_oPop->GetFloatDataCode(mp_cNewTreeDataMembers[j], iSp, iTp), p_fNewVals[j][i]);
            }

            //Mark it as found
            p_bFound[i] = true;
            break;
          }
        }

        p_oTree = p_oHarvestTrees->NextTree();
      }

      //Make sure all the trees in the list got found
      for (i = 0; i < iNumLines; i++) {
        if (false == p_bFound[i]) {
          modelErr stcErr;
          stcErr.iErrorCode = BAD_DATA;
          sprintf( stcErr.cMoreInfo, "%s%g%s%g%s%d%s%d%s%g%s",
              "Unrecognized tree in update file. X = ",
              p_fX[i], ", Y = ", p_fY[i], ", species = ", p_iSp[i],
              ", type = ", p_iTp[i], ", diam = ", p_fDiam[i], ".");
          strcpy( stcErr.cFunction, "clHarvestInterface::Action" );
          throw( stcErr );
        }
      }
    } //end of if (0 < iNumLines) - harvest file reading

    delete[] p_fDiam;
    delete[] p_fX;
    delete[] p_fY;
    delete[] p_iSp;
    delete[] p_iTp;
    delete[] p_bFound;
    for (i = 0; i < m_iNewTreeFloats; i++) {
      delete[] p_fNewVals[i];
    }
    delete[] p_fNewVals;


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
    strcpy( stcErr.cFunction, "clHarvestInterface::Action" );
    throw( stcErr );
  }
}


//////////////////////////////////////////////////////////////////////////////
// SetupResultsGrid()
//////////////////////////////////////////////////////////////////////////////
void clHarvestInterface::SetupResultsGrid()
{
  try
  {
  	clTreePopulation *p_oPop = (clTreePopulation*) mp_oSimManager->GetPopulationObject("treepopulation");
    clBehaviorBase *p_oTemp = mp_oSimManager->GetBehaviorObject("Harvest");
    clDisturbance *p_oHarvest = dynamic_cast<clDisturbance*>(p_oTemp);
    char cFloatLabel[MAX_GRID_LABEL_SIZE];
    float fCellLength = p_oPop->GetGridCellSize();
    short int iNumSpecies = p_oPop->GetNumberOfSpecies(), i, j;

    m_iNumAllowedCutRanges = p_oHarvest->GetNumberOfCutRanges();


    //*************************************
    //Harvest results grid
    //*************************************

    //Declare the arrays for density and ba codes
    mp_iDenCutCodes = new short int * [m_iNumAllowedCutRanges];
    mp_iBaCutCodes = new short int * [m_iNumAllowedCutRanges];
    for ( i = 0; i < m_iNumAllowedCutRanges; i++ )
    {
      mp_iDenCutCodes[i] = new short int[iNumSpecies];
      mp_iBaCutCodes[i] = new short int[iNumSpecies];
    }

    mp_oResultsGrid = mp_oSimManager->CreateGrid( "Harvest Results", //grid name
         1 + ( m_iNumAllowedCutRanges * iNumSpecies ), //number of int data members
         ( m_iNumAllowedCutRanges * iNumSpecies ), //num float data members
         0, //number of char data members
         0, //number of bool data members
         fCellLength, //X cell length
         fCellLength ); //Y cell length

    //Register the data members
    m_iHarvestTypeCode = mp_oResultsGrid->RegisterInt( "Harvest Type" );

    for ( i = 0; i < m_iNumAllowedCutRanges; i++ )
      for ( j = 0; j < iNumSpecies; j++ )
      {
        sprintf( cFloatLabel, "%s%d%s%d", "Cut Density_", i, "_", j );
        mp_iDenCutCodes[i] [j] = mp_oResultsGrid->RegisterInt( cFloatLabel );
        sprintf( cFloatLabel, "%s%d%s%d", "Cut Basal Area_", i, "_", j );
        mp_iBaCutCodes[i] [j] = mp_oResultsGrid->RegisterFloat( cFloatLabel );
      }

    //Use the ResetResultsGrid function to initialize the values
    ResetResultsGrid();

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
    strcpy( stcErr.cFunction, "clHarvestInterface::SetupResultsGrid" );
    throw( stcErr );
  }
}



//----------------------------------------------------------------------------

//////////////////////////////////////////////////////////////////////////////
// ResetResultsGrid()
//////////////////////////////////////////////////////////////////////////////
void clHarvestInterface::ResetResultsGrid()
{
  try
  {
  	clTreePopulation *p_oPop = (clTreePopulation*) mp_oSimManager->GetPopulationObject("treepopulation");
    float fValue = 0;
    int iValue;
    short int iNumXCells = mp_oResultsGrid->GetNumberXCells(),
              iNumYCells = mp_oResultsGrid->GetNumberYCells(),
              iNumSpecies = p_oPop->GetNumberOfSpecies(),
              i, j, iSp, iRange; //loop counters

    //For the harvest results grid - reset all values
    for ( i = 0; i < iNumXCells; i++ )
      for ( j = 0; j < iNumYCells; j++ )
      {

        iValue = -1;
        mp_oResultsGrid->SetValueOfCell( i, j, m_iHarvestTypeCode, iValue );

        iValue = 0;
        //Cut Density and Cut Basal Area - set values to 0
        for ( iSp = 0; iSp < iNumSpecies; iSp++ )
          for ( iRange = 0; iRange < m_iNumAllowedCutRanges; iRange++ )
          {
            mp_oResultsGrid->SetValueOfCell( i, j, mp_iDenCutCodes[iRange] [iSp], iValue );
            mp_oResultsGrid->SetValueOfCell( i, j, mp_iBaCutCodes[iRange] [iSp], fValue );
          }
      }

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
    strcpy( stcErr.cFunction, "clHarvestInterface::ResetResultsGrid" );
    throw( stcErr );
  }
}

