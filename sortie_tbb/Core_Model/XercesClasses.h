//---------------------------------------------------------------------------

#ifndef XercesClassesH
#define XercesClassesH
//---------------------------------------------------------------------------
#include <xercesc/dom/DOMErrorHandler.hpp>
#include <xercesc/dom/DOMEntityResolver.hpp>
#include <xercesc/sax/InputSource.hpp>

class DOMError;

//
// Xerces classes
// These are extensions needed to fully implement the Xerces XML parser into the
// model.

// Copyright 2003 Charles D. Canham.


/**
 * clXercesErrorHandler
 * This class is a Xerces-compatible error handler that will accept errors
 * from the parser and translate them to the model's error-trapping system.
 * @author Lora E. Murphy
 *
 *<br>Edit history:
 *<br>Edit <br>-----------------
 *<br>Edit <br>April 28, 2004 - Submitted as beta (LEM)
 */
class clXercesErrorHandler : public xercesc::DOMErrorHandler {

  /**
   * Implementation of the error handler interface.
   * @param oDomError Error
   */
  bool handleError(const xercesc::DOMError &oDomError);

};
//---------------------------------------------------------------------------
#endif
