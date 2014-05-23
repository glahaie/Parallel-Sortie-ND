//---------------------------------------------------------------------------

#ifndef InterfaceH
#define InterfaceH

#include "Messages.h"

/*//////////////////////////////////////////////////////////////////////////
 DoIntroduction()
 This will be called before anything else is done in a non-batch situation.
 It allows the interface to call any introductory screens, or ignore it if
 there's nothing to be done.
//////////////////////////////////////////////////////////////////////////*/
void DoIntroduction();

/*//////////////////////////////////////////////////////////////////////////
 GetMessage()
 This is used when the model is expecting a user message and cannot go on
 without one.  This function will continue to listen for input until some has
 been received.
//////////////////////////////////////////////////////////////////////////*/
modelMsg GetMessage();

/*//////////////////////////////////////////////////////////////////////////
 CheckForMessage()
 This is used when the model is checking for a message which may have come
 in during processing.  A return message of "no message" is acceptable if
 the user has not requested any actions.

 For now this assumes that any keys hit by the user mean "pause", but this
 idea should be expanded out if significant need for message-passing is
 discovered.
//////////////////////////////////////////////////////////////////////////*/
modelMsg CheckForMessage(char *cAppPath);

/*//////////////////////////////////////////////////////////////////////////
 SendMessage()
 This function accepts a message from the sim manager.
//////////////////////////////////////////////////////////////////////////*/
void SendMessage(modelMsg msg, bool batch = false);

/*//////////////////////////////////////////////////////////////////////////
 ExternalErrorHandler()
 This function accepts an error from the sim manager and processes it by
 displaying the appropriate error message.  If this is batch, different
 messages can be written.
//////////////////////////////////////////////////////////////////////////*/
void ExternalErrorHandler(modelErr stcError, int iModelState, bool batch);
//---------------------------------------------------------------------------
#endif


