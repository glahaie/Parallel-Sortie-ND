//---------------------------------------------------------------------------
#include <iostream>
//#include <conio.h>
#include <math.h>
#include "Interface.h"
#include <cstdlib>
#include <cstring>
#include <cstdio>

//---------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////
// DoIntroduction()
/////////////////////////////////////////////////////////////////////////////
void DoIntroduction()
{
  WriteIntroductoryScreen();
  WritePrompt();
}

//----------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////
// ExternalErrorHandler()
/////////////////////////////////////////////////////////////////////////////
void ExternalErrorHandler( modelErr stcErr, int iModelState, bool batch )
{

  //Go through the error types we know of
  if ( NEED_FILE == stcErr.iErrorCode )
    WriteNeedFile();
  else if ( BAD_FILE == stcErr.iErrorCode )
    WriteBadFile( stcErr );
  else if ( MODEL_NOT_READY == stcErr.iErrorCode )
    WriteNotReadyToRun();
  else if ( BAD_FILE_TYPE == stcErr.iErrorCode )
    WriteBadFileType( stcErr );
  else if ( BAD_XML_FILE == stcErr.iErrorCode )
    WriteBadXMLFile( stcErr );
  else if ( DATA_MISSING == stcErr.iErrorCode )
    WriteDataMissingFromFile( stcErr );
  else if ( BAD_DATA == stcErr.iErrorCode )
    WriteBadData( stcErr );
  else if ( ILLEGAL_OP == stcErr.iErrorCode )
    WriteIllegalOp( stcErr );
  else if ( DATA_READ_ONLY == stcErr.iErrorCode )
    WriteDataReadOnly( stcErr );
  else if ( CANT_FIND_OBJECT == stcErr.iErrorCode )
    WriteCantFindObject( stcErr );
  else if ( TREE_WRONG_TYPE == stcErr.iErrorCode )
    WriteTreeWrongType( stcErr );
  else if ( ACCESS_VIOLATION == stcErr.iErrorCode )
    WriteAccessViolation( stcErr );
  else if ( UNKNOWN == stcErr.iErrorCode )
    WriteUnknownError( stcErr );
  else
    WriteUnknownError( stcErr );



  if ( !batch )
  {
    if ( No_Data == iModelState )
      WriteNotReadyToRun();
    else
      WriteModelReady();
    WritePrompt();
  }

}

//----------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////
// SendMessage()
/////////////////////////////////////////////////////////////////////////////
void SendMessage( modelMsg stcMsg, bool batch )
{
  using namespace std;
  modelErr stcErr; //we'll use this to translate the message structure to
  //an error structure to pass to writing functions

  //Go through the message types we know of
  if ( MODEL_READY == stcMsg.iMessageCode )
  {
    WriteModelReady();
    WritePrompt();
  }
  else if ( MODEL_NOT_READY == stcMsg.iMessageCode )
  {
    WriteModelNotReady();
    WritePrompt();
  }
  else if ( MODEL_PAUSED == stcMsg.iMessageCode )
  {
    WriteModelPaused();
    WritePrompt();
  }
  else if ( RUN_COMPLETE == stcMsg.iMessageCode )
  {
    int iFirst = 0, iSecond = 0; //the two timesteps we expect
    unsigned long iRunTime = 0;
    //parse out the timesteps
    string::size_type pos;
    std::string strData = stcMsg.cMoreInfo;
    if ( "" != strData )
    {
      pos = strData.find( "," );
      if ( string::npos != pos )
      {
        iFirst = atoi( strData.substr( 0, pos ).c_str() );
        strData = strData.substr( pos + 1 ); //trim off first arg
        pos = strData.find( "," );
        iSecond = atoi( strData.substr( 0, pos ).c_str() );
        iRunTime = atoi( strData.substr( pos + 1 ).c_str() );
      }
      else
        iFirst = atoi( strData.c_str() );
    }

    WriteRunComplete( iFirst, iSecond, iRunTime );
    WritePrompt();
  }
  else if ( BAD_ARGUMENT == stcMsg.iMessageCode )
  {
    WriteBadArgument( stcMsg );
    WritePrompt();
  }
  else if ( BAD_COMMAND == stcMsg.iMessageCode )
  {
    WriteBadCommand();
    WritePrompt();
  }
  else if ( COMMAND_DONE == stcMsg.iMessageCode )
  {
    WritePrompt();
  }
  else if ( INFO == stcMsg.iMessageCode )
  {
    cout << "\t" << stcMsg.cMoreInfo << "\n";
  }
  else if ( NEED_FILE == stcMsg.iMessageCode )
  {
    WriteNeedFile();
    if ( !batch ) WritePrompt();
  }
  else if ( BAD_FILE == stcMsg.iMessageCode )
  {
    stcErr.iErrorCode = stcMsg.iMessageCode;
    strcpy( stcErr.cFunction, stcMsg.cFunction );
    strcpy( stcErr.cMoreInfo, stcMsg.cMoreInfo );
    WriteBadFile( stcErr );
    if ( !batch ) WritePrompt();
  }
  else if ( BAD_FILE_TYPE == stcMsg.iMessageCode )
  {
    stcErr.iErrorCode = stcMsg.iMessageCode;
    strcpy( stcErr.cFunction, stcMsg.cFunction );
    strcpy( stcErr.cMoreInfo, stcMsg.cMoreInfo );
    WriteBadFileType( stcErr );
    if ( !batch ) WriteNotReadyToRun();
    if ( !batch ) WritePrompt();
  }
  else if ( BAD_XML_FILE == stcMsg.iMessageCode )
  {
    stcErr.iErrorCode = stcMsg.iMessageCode;
    strcpy( stcErr.cFunction, stcMsg.cFunction );
    strcpy( stcErr.cMoreInfo, stcMsg.cMoreInfo );
    WriteBadXMLFile( stcErr );
    if ( !batch ) WriteNotReadyToRun();
    if ( !batch ) WritePrompt();
  }
  else if ( DATA_MISSING == stcMsg.iMessageCode )
  {
    stcErr.iErrorCode = stcMsg.iMessageCode;
    strcpy( stcErr.cFunction, stcMsg.cFunction );
    strcpy( stcErr.cMoreInfo, stcMsg.cMoreInfo );
    WriteDataMissingFromFile( stcErr );
    if ( !batch ) WriteNotReadyToRun();
    if ( !batch ) WritePrompt();
  }
  else if ( BAD_DATA == stcMsg.iMessageCode )
  {
    stcErr.iErrorCode = stcMsg.iMessageCode;
    strcpy( stcErr.cFunction, stcMsg.cFunction );
    strcpy( stcErr.cMoreInfo, stcMsg.cMoreInfo );
    WriteBadData( stcErr );
    if ( !batch ) WriteNotReadyToRun();
    if ( !batch ) WritePrompt();
  }
  else if ( DATA_READ_ONLY == stcMsg.iMessageCode )
  {
    stcErr.iErrorCode = stcMsg.iMessageCode;
    strcpy( stcErr.cFunction, stcMsg.cFunction );
    strcpy( stcErr.cMoreInfo, stcMsg.cMoreInfo );
    WriteDataReadOnly( stcErr );
    if ( !batch ) WriteNotReadyToRun();
    if ( !batch ) WritePrompt();
  }
  else if ( CANT_FIND_OBJECT == stcMsg.iMessageCode )
  {
    stcErr.iErrorCode = stcMsg.iMessageCode;
    strcpy( stcErr.cFunction, stcMsg.cFunction );
    strcpy( stcErr.cMoreInfo, stcMsg.cMoreInfo );
    WriteCantFindObject( stcErr );
    if ( !batch ) WriteNotReadyToRun();
    if ( !batch ) WritePrompt();
  }
  else if ( TREE_WRONG_TYPE == stcMsg.iMessageCode )
  {
    stcErr.iErrorCode = stcMsg.iMessageCode;
    strcpy( stcErr.cFunction, stcMsg.cFunction );
    strcpy( stcErr.cMoreInfo, stcMsg.cMoreInfo );
    WriteTreeWrongType( stcErr );
    if ( !batch ) WriteNotReadyToRun();
    if ( !batch ) WritePrompt();
  }
  else if ( UNKNOWN == stcMsg.iMessageCode )
  {
    stcErr.iErrorCode = stcMsg.iMessageCode;
    strcpy( stcErr.cFunction, stcMsg.cFunction );
    strcpy( stcErr.cMoreInfo, stcMsg.cMoreInfo );
    WriteUnknownError( stcErr );
    if ( !batch ) WriteNotReadyToRun();
    if ( !batch ) WritePrompt();
  }
  else
  {
    stcErr.iErrorCode = stcMsg.iMessageCode;
    strcpy( stcErr.cFunction, stcMsg.cFunction );
    strcpy( stcErr.cMoreInfo, stcMsg.cMoreInfo );
    WriteUnknownError( stcErr );
    if ( !batch ) WriteNotReadyToRun();
    if ( !batch ) WritePrompt();
  }
}

//----------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////
// CheckForMessage()
/////////////////////////////////////////////////////////////////////////////
modelMsg CheckForMessage(char *cAppPath)
{
  using namespace std;	
  modelMsg stcMsg; //what this function will return

//This may not even be needed for Linux

  //Did the user hit any keys?  If so, send a message of "paused"
//  if ( 0 != kbhit() )
//    stcMsg.iMessageCode = MODEL_PAUSED;
//  else //no keys hit
    stcMsg.iMessageCode = NO_MESSAGE;

  return stcMsg;
}

//----------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////
// GetMessage()
/////////////////////////////////////////////////////////////////////////////
modelMsg GetMessage()
{
  using namespace std;
  const int iLineSize = 250; //max number of characters we expect to receive
  //from a command line argument
  modelMsg stcMsg; //the message structure we will return
  char cInBuf[iLineSize]; //in buffer
  string strCommandLine, //what the user types on the command line - for
       //parsing
       strCommand, //this captures the actual command parsed out of the
       //command line
       strArg; //this captures the additional arguments to the command
  //that will be passed in the message structure
  string::size_type pos; //for string parsing operations

  while ( 1 )
  {
    //Get what the user typed on the command line
    cin.getline( cInBuf, iLineSize );
    strCommandLine = cInBuf;

    //Parse out the command - if there's a space in what we captured, then the
    //first part is the command
    pos = strCommandLine.find_first_of( " " );
    if ( pos == string::npos )
    {
      strCommand = strCommandLine;
      strArg = "";
    }
    else
    {
      strCommand = strCommandLine.substr( 0, pos );
      strArg = strCommandLine.substr( pos + 1 );
    }

    //If this was a help request, handle it in this function rather than
    //passing it on
    if ( "help" == strCommand )
    {
      if ( "" == strArg )
      {
        WriteGeneralHelp();
        WritePrompt();
      }
      else if ( "input" == strArg )
      {
        WriteInputHelp();
        WritePrompt();
      }
      else if ( "run" == strArg )
      {
        WriteRunHelp();
        WritePrompt();
      }
      else if ( "quit" == strArg )
      {
        WriteQuitHelp();
        WritePrompt();
      }
      else
      {
        WriteBadCommand();
        WritePrompt();
      }
    } //end of if ("help" = strCommand)
    else
    { //not help
      //Put the arguments, if any, into the message structure
      strcpy( stcMsg.cMoreInfo, strArg.c_str() );

      //Figure out what the message is
      if ( "quit" == strCommand )
      {
        stcMsg.iMessageCode = QUIT;
        return stcMsg;
      }
      else if ( "run" == strCommand )
      {
        stcMsg.iMessageCode = RUN;
        return stcMsg;
      }
      else if ( "input" == strCommand )
      {
        stcMsg.iMessageCode = INPUT_FILE;
        return stcMsg;
      }
      else
      { //unrecognized message
        stcMsg.iMessageCode = UNKNOWN;
        //Put the message command back into the string
        strcpy( stcMsg.cMoreInfo, strCommandLine.c_str() );
        return stcMsg;
      }
    } //end of else
  } //end of while (1)

}

//----------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////
// WritePrompt()
/////////////////////////////////////////////////////////////////////////////
void WritePrompt()
{
  using namespace std;	
  cout << "SORTIE:>  ";
}

//----------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////
// WriteIntroductoryScreen()
/////////////////////////////////////////////////////////////////////////////
void WriteIntroductoryScreen()
{
  using namespace std;	
  cout << "*************************************\n";
  cout << "               SORTIE                \n";
  cout << "*************************************\n";
  cout << "Model Status: Not ready to run.\n\n";
  cout << "To enter a parameter file:  Type  \"input \" followed by the path ";
  cout << "and name of the parameter file.\n\n";
  cout << "For a list of all commands with examples, type \"help\".  To end, ";
  cout << "type \"quit\".\n";
}

//---------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////
// WriteBadCommand()
/////////////////////////////////////////////////////////////////////////////
void WriteBadCommand()
{
  using namespace std;	
  cout << "I do not understand that command.  Type \"help\" for a list" << " of commands.\n\n";
}

//---------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////
// WriteGeneralHelp()
/////////////////////////////////////////////////////////////////////////////
void WriteGeneralHelp()
{
  using namespace std;	
  cout << "\n\n*************************************\n";
  cout << "             SORTIE HELP             \n";
  cout << "*************************************\n\n";
  cout << "Note:  Case is important.  Type all commands in lowercase.\n";
  cout << "Type the desired command, then a space, then any required";
  cout << " arguments.\n\n";
  cout << "Command     Arguments             Purpose\n";
  cout << "------------------------------------------------\n";
  cout << " help       Optional -            Displays the help screen.\n";
  cout << "             command\n";
  cout << " quit       (None)                Exits SORTIE.\n\n";
  cout << " input      File path and whether Gives SORTIE a file to read.\n";
  cout << "            to keep current set-\n";
  cout << "            tings (true/false)\n\n";
  cout << " run        Optional - number of  Runs the model.\n";
  cout << "            timesteps to run\n\n";
  //  cout << " reset      (None)                Resets the current timestep\n";
  //  cout << "                                  to 1, leaving current trees.\n";
  //  cout << " pause      (None)                Pauses the run.\n\n";

  cout << "For more information on a given command, type \"help\" followed by";
  cout << " the name of the command - i.e. \"help input\".\n";
}

//----------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////
// WriteInputHelp()
/////////////////////////////////////////////////////////////////////////////
void WriteInputHelp()
{
  using namespace std;	
  cout << "\n\n****************************************\n";
  cout << "INPUT HELP\n\n";
  cout << "PURPOSE:  This feeds an input file to SORTIE.  This must be used at"
       << " the beginning of a run to input a parameter file.  This may be used"
       << " at anytime after, including during the run, for updating and chang" << "ing settings.\n\n";
  cout << "ARGUMENTS:  The first argument is the full path and filename of the"
       << " file to read.  The second argument, optional, is a true/false for"
       << " whether or not to keep current data.  For instance, if you are"
       << " entering a tree map file, this indicates whether or not to keep the"
       << " current trees.  This argument does not apply in all cases.\n\n";
  cout << "EXAMPLE:  input c:\\sortie\\parameterfile.xml false\n";
}

//----------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////
// WriteRunHelp()
/////////////////////////////////////////////////////////////////////////////
void WriteRunHelp()
{
  using namespace std;	
  cout << "\n\n****************************************\n";
  cout << "RUN HELP\n\n";
  cout << "PURPOSE:  This starts the SORTIE run.  You must have input a" << " parameter file for this to work.\n\n";
  cout << "ARGUMENTS:  There is an optional argument for a number of timesteps"
       << " to run.  For instance, typing \"run 5\" runs the model for the next"
       << " five timesteps, at which point the model pauses to await commands."
       << " Leaving off this argument causes the model to run to the end.\n";
}

//----------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////
// WritePauseHelp()
/////////////////////////////////////////////////////////////////////////////
void WritePauseHelp()
{
  ;
}

//----------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////
// WriteQuitHelp()
/////////////////////////////////////////////////////////////////////////////
void WriteQuitHelp()
{
  using namespace std;	
  cout << "QUIT HELP\n\n";
  cout << "PURPOSE:  This quits SORTIE.\n\n";
  cout << "ARGUMENTS:  None.\n";
}

//----------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////
// WriteResetHelp()
/////////////////////////////////////////////////////////////////////////////
void WriteResetHelp()
{
  using namespace std;	
  cout << "RESET HELP\n\n";
  cout << "PURPOSE:  This resets the current timestep back to one.  This does"
       << " not change the current tree set or reload the parameter file.  You"
       << " might use this to start a new run after one has just finished,"
       << " using the same settings on that set of trees.\n";
  cout << "ARGUMENTS:  None.\n";
}

//----------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////
// WriteNeedFile()
/////////////////////////////////////////////////////////////////////////////
void WriteNeedFile()
{
  using namespace std;	
  cerr << "I need a file path and name with the input command.  Please type"
       << " \"input\" again and follow it with a complete file path and" << " name.\n";
}

//----------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////
// WriteBadFile()
/////////////////////////////////////////////////////////////////////////////
void WriteBadFile( modelErr stcErr )
{
  using namespace std;	
  cerr << "SORTIE could not open or read this file.";
  if ( strcmp( "", stcErr.cMoreInfo ) != 0 )
    cerr << "  The file is:  " << stcErr.cMoreInfo;
  cerr << "  The function which passed this error is:  " << stcErr.cFunction << "\n\n";
}

//----------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////
// WriteModelReady()
/////////////////////////////////////////////////////////////////////////////
void WriteModelReady()
{
  using namespace std;	 
  cout << "Model status:  Ready to run.\n";
}

//----------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////
// WriteModelNotReady()
/////////////////////////////////////////////////////////////////////////////
void WriteModelNotReady()
{
  using namespace std;	
  cout << "Model status:  Not ready to run.\n";
}

//----------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////
// WriteBadArgument()
/////////////////////////////////////////////////////////////////////////////
void WriteBadArgument( modelMsg stcMsg )
{
  using namespace std;	 
  cerr << "I did not understand the argument(s) to the last command.";
  if ( strcmp( "", stcMsg.cMoreInfo ) != 0 )
    cerr << "  More information:  " << stcMsg.cMoreInfo;
  cerr << "  Please use the \"help\" command for more information.\n";
}

//----------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////
// WriteNotReadyToRun()
/////////////////////////////////////////////////////////////////////////////
void WriteNotReadyToRun()
{
  using namespace std;	
  cout << "The model is not ready to run.\n";
}

//----------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////
// WriteRunComplete()
/////////////////////////////////////////////////////////////////////////////
void WriteRunComplete( int iCurrentTimestep, int iNumTimesteps, unsigned long iRunTime )
{
  using namespace std;	 
  char cTime[20], cTime2[20];
  int iTemp;

  //Calc number of hours
  iTemp = (int)floor( (double)(iRunTime / 3600) );
  sprintf( cTime, "%d", iTemp );
  strcat( cTime, ":" );
  iRunTime -= ( iTemp * 3600 );

  //Calc number of minutes
  iTemp = (int)floor( (double)(iRunTime / 60) );
  sprintf( cTime2, "%s%d", cTime, iTemp );
  strcat( cTime2, ":" );
  iRunTime -= ( iTemp * 60 );

  //Add number of seconds
  sprintf( cTime, "%s%lu", cTime2, iRunTime );

  cout << "The requested run is complete.\n" << "Timesteps completed:  " << iCurrentTimestep << " out of " << iNumTimesteps
       << ".  Run time:  " << cTime << ".\n";
}

//----------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////
// WriteModelPaused()
/////////////////////////////////////////////////////////////////////////////
void WriteModelPaused()
{
  using namespace std;	 
  cout << "The run is paused.  To start the model where it left off, type"
       << " \"run\" (if you entered a number of timesteps to run earlier, it"
       << " will still run to that point).  Or, enter another command.\n";
}

//----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////
// WriteBadFileType()
////////////////////////////////////////////////////////////////////////////
void WriteBadFileType( modelErr stcErr )
{
  using namespace std;	
  cerr << "SORTIE cannot process this file type.";
  if ( strcmp( "", stcErr.cMoreInfo ) != 0 )
    cerr << "  The file is:  " << stcErr.cMoreInfo;
  cerr << "  The function which passed this error is:  " << stcErr.cFunction << "\n\n";
}

//---------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////
// WriteBadXMLFile()
////////////////////////////////////////////////////////////////////////////
void WriteBadXMLFile( modelErr stcErr )
{
  using namespace std;	
  cerr << "This XML file is not well-formed or is invalid. It cannot" << " be parsed.";
  if ( strcmp( "", stcErr.cMoreInfo ) != 0 )
    cerr << "  The file is:  " << stcErr.cMoreInfo;
  cerr << "  The function which passed this error is:  " << stcErr.cFunction << "\n\n";
}

//---------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////
// WriteDataMissingFromFile()
////////////////////////////////////////////////////////////////////////////
void WriteDataMissingFromFile( modelErr stcErr )
{
  using namespace std;	
  cerr << "This file is missing data.";
  if ( strcmp( "", stcErr.cMoreInfo ) != 0 )
    cerr << "  More information:  " << stcErr.cMoreInfo;
  cerr << "  The function which passed this error is:  " << stcErr.cFunction << "\n\n";
}

//---------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////
// WriteBadData()
////////////////////////////////////////////////////////////////////////////
void WriteBadData( modelErr stcErr )
{
  using namespace std;	
  cerr << "The model has attempted to use bad or invalid data.";
  if ( strcmp( "", stcErr.cMoreInfo ) != 0 )
    cerr << "  More information:  " << stcErr.cMoreInfo;
  cerr << "  The function which passed this error is:  " << stcErr.cFunction << "\n\n";
}

//---------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////
// WriteIllegalOp()
////////////////////////////////////////////////////////////////////////////
void WriteIllegalOp( modelErr stcErr )
{
  using namespace std;	
  cerr << "The model has attempted to perform an illegal operation.";
  if ( strcmp( "", stcErr.cMoreInfo ) != 0 )
    cerr << "  More information:  " << stcErr.cMoreInfo;
  cerr << "  The function which passed this error is:  " << stcErr.cFunction << "\n\n";
}

//---------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////
// WriteDataReadOnly()
////////////////////////////////////////////////////////////////////////////
void WriteDataReadOnly( modelErr stcErr )
{
  using namespace std;
  cerr << "The model has attempted to write to a read-only piece of data.";
  if ( strcmp( "", stcErr.cMoreInfo ) != 0 )
    cerr << "  More information:  " << stcErr.cMoreInfo;
  cerr << "  The function which passed this error is:  " << stcErr.cFunction << "\n\n";
}

//---------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////
// WriteCantFindObject()
////////////////////////////////////////////////////////////////////////////
void WriteCantFindObject( modelErr stcErr )
{
  using namespace std;
  cerr << "The model is unable to find a needed object.";
  if ( strcmp( "", stcErr.cMoreInfo ) != 0 )
    cerr << "  More information:  " << stcErr.cMoreInfo;
  cerr << "  The function which passed this error is:  " << stcErr.cFunction << "\n\n";
}

//---------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////
// WriteTreeWrongType()
////////////////////////////////////////////////////////////////////////////
void WriteTreeWrongType( modelErr stcErr )
{
  using namespace std;	
  cerr << "A tree is of the wrong type.";
  if ( strcmp( "", stcErr.cMoreInfo ) != 0 )
    cerr << "  More information:  " << stcErr.cMoreInfo;
  cerr << "  The function which passed this error is:  " << stcErr.cFunction << "\n\n";
}

//---------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////
// WriteAccessViolation()
////////////////////////////////////////////////////////////////////////////
void WriteAccessViolation( modelErr stcErr )
{
  using namespace std;	
  cerr << "There was an access violation.";
  if ( strcmp( "", stcErr.cMoreInfo ) != 0 )
    cerr << "  More information:  " << stcErr.cMoreInfo;
  cerr << "  The function which passed this error is:  " << stcErr.cFunction << "\n\n";
}

//---------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////
// WriteUnknownError()
////////////////////////////////////////////////////////////////////////////
void WriteUnknownError( modelErr stcErr )
{
  using namespace std;
  cerr << "An unknown error has occurred.";
  if ( strcmp( "", stcErr.cMoreInfo ) != 0 )
    cerr << "  More information:  " << stcErr.cMoreInfo;
  cerr << "  The function which passed this error is:  " << stcErr.cFunction << "\n\n";
}
//---------------------------------------------------------------------------



