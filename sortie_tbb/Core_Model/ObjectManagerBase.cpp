//---------------------------------------------------------------------------
#include "ObjectManagerBase.h"
#include "SimManager.h"
#include "WorkerBase.h"
//---------------------------------------------------------------------------
#include <iostream>


clSimManager *clObjectManagerBase::mp_oSimManager = NULL;

////////////////////////////////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////////////////////////////////
clObjectManagerBase::clObjectManagerBase(clSimManager *p_oSimManager) {
  try {
    //mp_oSimManager is static - it may already be initialized
    if (NULL == mp_oSimManager) mp_oSimManager = p_oSimManager;
    mp_oObjectArray = NULL;
    m_iNumObjects = 0;
  }
  catch(modelErr &err) {throw(err);}
  catch (modelMsg &msg) {throw(msg);} //non-fatal error
  catch(...) {
    modelErr stcErr;
    stcErr.iErrorCode = UNKNOWN;
    strcpy(stcErr.cFunction, "clObjectManagerBase::clObjectManagerBase");
    throw(stcErr);
  }
}


////////////////////////////////////////////////////////////////////////////
// Destructor
////////////////////////////////////////////////////////////////////////////
clObjectManagerBase::~clObjectManagerBase() {
  FreeMemory();
}

////////////////////////////////////////////////////////////////////////////
// PassObjectPointer()
///////////////////////////////////////////////////////////////////////////*/
clWorkerBase* clObjectManagerBase::PassObjectPointer(int iObjectNumber) {
  try {
    clWorkerBase *p_oObject = NULL;
    if (iObjectNumber >= 0 && iObjectNumber < m_iNumObjects)
      p_oObject = mp_oObjectArray[iObjectNumber];

    return p_oObject;
  }
  catch(modelErr &err) {throw(err);}
  catch (modelMsg &msg) {throw(msg);} //non-fatal error
  catch(...) {
    modelErr stcErr;
    stcErr.iErrorCode = UNKNOWN;
    strcpy(stcErr.cFunction, "clObjectManagerBase::PassObjectPointer(int)");
    throw(stcErr);
  }
  std::cout << "We return NULL" << std::endl;
  return NULL;
}


////////////////////////////////////////////////////////////////////////////
// PassObjectPointer()
////////////////////////////////////////////////////////////////////////////
clWorkerBase* clObjectManagerBase::PassObjectPointer(const char *cName) {
  try {
    clWorkerBase *p_oObject = NULL;
    for (int i = 0; i < m_iNumObjects; i++)
      if (mp_oObjectArray[i] && strcmp(mp_oObjectArray[i]->GetName(), cName) == 0)
        p_oObject = mp_oObjectArray[i];

    return p_oObject;
  }
  catch(modelErr &err) {throw(err);}
  catch (modelMsg &msg) {throw(msg);} //non-fatal error
  catch(...) {
    modelErr stcErr;
    stcErr.iErrorCode = UNKNOWN;
    strcpy(stcErr.cFunction, "clObjectManagerBase::PassObjectPointer(string)");
    throw(stcErr);
  }
  return NULL;
}


////////////////////////////////////////////////////////////////////////////
// TimestepCleanup()
////////////////////////////////////////////////////////////////////////////
void clObjectManagerBase::TimestepCleanup() {
  try {
    clWorkerBase *p_oObject = NULL;

    //for each member object, trigger their timestep cleanup function
    for (int i = 0; i < m_iNumObjects; i++) {
      p_oObject = mp_oObjectArray[i];
      p_oObject->TimestepCleanup();
    }
  }
  catch(modelErr &err) {throw(err);}
  catch (modelMsg &msg) {throw(msg);} //non-fatal error
  catch(...) {
    modelErr stcErr;
    stcErr.iErrorCode = UNKNOWN;
    strcpy(stcErr.cFunction, "clObjectManagerBase::TimestepCleanup");
    throw(stcErr);
  }
}


////////////////////////////////////////////////////////////////////////////
// EndOfRunCleanup()
////////////////////////////////////////////////////////////////////////////
void clObjectManagerBase::EndOfRunCleanup() {
  try {
    clWorkerBase *p_oObject = NULL;

    //for each member object, trigger their timestep cleanup function
    for (int i = 0; i < m_iNumObjects; i++) {
      p_oObject = mp_oObjectArray[i];
      p_oObject->EndOfRunCleanup();
    }
  }
  catch(modelErr &err) {throw(err);}
  catch (modelMsg &msg) {throw(msg);} //non-fatal error
  catch(...) {
    modelErr stcErr;
    stcErr.iErrorCode = UNKNOWN;
    strcpy(stcErr.cFunction, "clObjectManagerBase::EndOfRunCleanup");
    throw(stcErr);
  }
}


////////////////////////////////////////////////////////////////////////////
// FreeMemory()
////////////////////////////////////////////////////////////////////////////
void clObjectManagerBase::FreeMemory() {
  try {
    for (int i = 0; i < m_iNumObjects; i++) {
          delete mp_oObjectArray[i];
    } //end of for (int i = 0; i < m_iNumObjects; i++)

    delete[] mp_oObjectArray; mp_oObjectArray = NULL;
    m_iNumObjects = 0;
  }
  catch(modelErr &err) {throw(err);}
  catch (modelMsg &msg) {throw(msg);} //non-fatal error
  catch(...) {
    modelErr stcErr;
    stcErr.iErrorCode = UNKNOWN;
    strcpy(stcErr.cFunction, "clObjectManagerBase::FreeMemory");
    throw(stcErr);
  }
}


////////////////////////////////////////////////////////////////////////////
// DoObjectSetup()
////////////////////////////////////////////////////////////////////////////
void clObjectManagerBase::DoObjectSetup(DOMDocument *p_oDoc,fileType iFileType){
  try {
    std::string strFileCode; //for getting the file code

    //Make sure that the DOM_Document pointer is not NULL
    if (NULL == p_oDoc) {
      modelErr stcErr;
      strcpy(stcErr.cFunction, "clObjectManagerBase::DoObjectSetup");
      stcErr.iErrorCode = CANT_FIND_OBJECT;
      strcpy(stcErr.cMoreInfo, "Document pointer passed is NULL.");
      throw(stcErr);
    }

    for (int i = 0; i < m_iNumObjects; i++)
     mp_oObjectArray[i]->DoObjectSetup(p_oDoc, iFileType);
  }
  catch(modelErr &err) {throw(err);}
  catch (modelMsg &msg) {throw(msg);} //non-fatal error
  catch(...) {
    modelErr stcErr;
    stcErr.iErrorCode = UNKNOWN;
    strcpy(stcErr.cFunction, "clObjectManagerBase::DoObjectSetup");
    throw(stcErr);
  }
}
