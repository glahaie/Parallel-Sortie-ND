//---------------------------------------------------------------------------
#include "XercesClasses.h"
#include "Messages.h"
#include <xercesc/util/XMLString.hpp>
#include <xercesc/dom/DOMError.hpp>
#include <xercesc/framework/LocalFileInputSource.hpp>
#include <xercesc/framework/Wrapper4InputSource.hpp>
#include <xercesc/util/XMLUniDefs.hpp>

//---------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////
// handleError()
/////////////////////////////////////////////////////////////////////////////
bool clXercesErrorHandler::handleError(const xercesc::DOMError &oDomError) {
  //if it's just a warning - ignore
  if (xercesc::DOMError::DOM_SEVERITY_WARNING == oDomError.getSeverity())
    return true;

  modelErr stcErr;
  stcErr.iErrorCode = BAD_XML_FILE;
  strcpy(stcErr.cFunction, "Xerces parser");
  strcpy(stcErr.cMoreInfo, xercesc::XMLString::transcode(oDomError.getMessage()));
  throw(stcErr);
}
