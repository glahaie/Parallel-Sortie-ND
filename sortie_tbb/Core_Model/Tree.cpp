//---------------------------------------------------------------------------
#include <stdio.h>
#include "Tree.h"
#include "TreePopulation.h"
#include "DeadTree.h"
//---------------------------------------------------------------------------

clTreePopulation *clTree::mp_oTreePop = NULL;

////////////////////////////////////////////////////////////////////////////
// Constructor
///////////////////////////////////////////////////////////////////////////*/
clTree::clTree(int iType, int iSpecies, int iNumFloats, int iNumInts,
   int iNumChars, int iNumBools, clTreePopulation *p_oTreePop) {
  try {
    int i;
    char cEmptyString[] = "\0";

    //mp_oTreePop is static - it may already be initialized
    if (NULL == mp_oTreePop) mp_oTreePop = p_oTreePop;

    //Verify that type and species is okay
    if (iType<clTreePopulation::seed || iType>clTreePopulation::woody_debris) {
      modelErr stcErr;
      stcErr.iErrorCode = BAD_DATA;
      strcpy(stcErr.cFunction, "clTree::clTree");
      sprintf(stcErr.cMoreInfo, "%s%d", "Unrecognized tree type:  ", iType);
      throw(stcErr);
    }
    if (iSpecies < 0 || iSpecies >= mp_oTreePop->m_iNumSpecies) {
      modelErr stcErr;
      stcErr.iErrorCode = BAD_DATA;
      strcpy(stcErr.cFunction, "clTree::clTree");
      sprintf(stcErr.cMoreInfo, "%s%d", "Unrecognized tree type:  ", iType);
      throw(stcErr);
    }
    if (iNumFloats < 0 || iNumInts < 0 || iNumChars < 0 || iNumBools < 0) {
      modelErr stcErr;
      stcErr.iErrorCode = BAD_DATA;
      strcpy(stcErr.cFunction, "clTree::clTree");
      strcpy(stcErr.cMoreInfo, "Data member numbers cannot be less than zero.");
      throw(stcErr);
    }

    m_iSpecies = iSpecies;
    m_iType = iType;

    //Null out the pointers
    mp_fFloatValues = NULL;
    mp_iIntValues = NULL;
    mp_cCharValues = NULL;
    mp_bBoolValues = NULL;

    if (iNumFloats > 0) {
      mp_fFloatValues = new float[iNumFloats];
      for (i = 0; i < iNumFloats; i++)
        mp_fFloatValues[i] = 0;
    }
    if (iNumInts > 0) {
      mp_iIntValues = new int[iNumInts];
      for (i = 0; i < iNumInts; i++)
        mp_iIntValues[i] = 0;
    }
    if (iNumChars > 0) {
      mp_cCharValues = new char*[iNumChars];
      for (i = 0; i < iNumChars; i++) {
        mp_cCharValues[i] = new char[MAX_TREE_CHAR_VALUE_SIZE];
        strcpy(mp_cCharValues[i], cEmptyString);
      }
    }
    if (iNumBools > 0) {
      mp_bBoolValues = new bool[iNumBools];
      for (i = 0; i < iNumBools; i++)
        mp_bBoolValues[i] = false;
    }
  }
  catch (modelErr&err) {throw(err);}
  catch (modelMsg &msg) {throw(msg);} //non-fatal error
  catch (...) {
    modelErr stcErr;    stcErr.iErrorCode = UNKNOWN;
    strcpy(stcErr.cFunction, "clTree::clTree");
    throw(stcErr);
  }
}

////////////////////////////////////////////////////////////////////////////
// Destructor
////////////////////////////////////////////////////////////////////////////
clTree::~clTree() {
  //Delete all arrays
  delete[] mp_fFloatValues;
  delete[] mp_iIntValues;
  for (int i = 0; i < mp_oTreePop->mp_iNumTreeCharVals[m_iSpecies][m_iType];i++)
      delete[] mp_cCharValues[i];
  delete[] mp_cCharValues;
  delete[] mp_bBoolValues;
}

////////////////////////////////////////////////////////////////////////////
// SetValue
///////////////////////////////////////////////////////////////////////////*/
void clTree::SetValue(short int iCode, int iValue) {
  mp_oTreePop->UpdateTree(this, iCode, iValue);
}

////////////////////////////////////////////////////////////////////////////
// SetValue
///////////////////////////////////////////////////////////////////////////*/
void clTree::SetValue(short int iCode, float fValue, bool bUpdateNow, bool bUpdateAllometry) {
  mp_oTreePop->UpdateTree(this, iCode, fValue, bUpdateNow, bUpdateAllometry);
}

////////////////////////////////////////////////////////////////////////////
// SetValue
///////////////////////////////////////////////////////////////////////////*/
void clTree::SetValue(short int iCode, bool bValue) {
  mp_oTreePop->UpdateTree(this, iCode, bValue);
}

////////////////////////////////////////////////////////////////////////////
// SetValue
///////////////////////////////////////////////////////////////////////////*/
void clTree::SetValue(short int iCode, char *cValue) {
  mp_oTreePop->UpdateTree(this, iCode, cValue);
}


////////////////////////////////////////////////////////////////////////////
// GetValue
///////////////////////////////////////////////////////////////////////////*/
void clTree::GetValue(short int iCode, int *p_iValHolder) {
  *p_iValHolder = mp_iIntValues[iCode];
}

////////////////////////////////////////////////////////////////////////////
// GetValue
///////////////////////////////////////////////////////////////////////////*/
void clTree::GetValue(short int iCode, float *p_fValHolder) {
  *p_fValHolder = mp_fFloatValues[iCode];
}

////////////////////////////////////////////////////////////////////////////
// GetValue
///////////////////////////////////////////////////////////////////////////*/
void clTree::GetValue(short int iCode, bool *p_bValHolder) {
  *p_bValHolder = mp_bBoolValues[iCode];
}

////////////////////////////////////////////////////////////////////////////
// GetValue
///////////////////////////////////////////////////////////////////////////*/
void clTree::GetValue(short int iCode, char *p_cValHolder) {
  strcpy(p_cValHolder, mp_cCharValues[iCode]);
}


////////////////////////////////////////////////////////////////////////////
// MakeDeadClone
////////////////////////////////////////////////////////////////////////////
clDeadTree* clTree::MakeDeadClone() {
  clDeadTree *p_oClone = new clDeadTree(m_iType, m_iSpecies,
      mp_oTreePop->mp_iNumTreeFloatVals[m_iSpecies] [m_iType],
      mp_oTreePop->mp_iNumTreeIntVals[m_iSpecies] [m_iType],
      mp_oTreePop->mp_iNumTreeCharVals[m_iSpecies] [m_iType],
      mp_oTreePop->mp_iNumTreeBoolVals[m_iSpecies] [m_iType]);

  int i;

  for (i = 0; i < mp_oTreePop->mp_iNumTreeFloatVals[m_iSpecies][m_iType]; i++) {
    p_oClone->mp_fFloatValues[i] = mp_fFloatValues[i];
  }

  for (i = 0; i < mp_oTreePop->mp_iNumTreeIntVals[m_iSpecies][m_iType]; i++) {
    p_oClone->mp_iIntValues[i] = mp_iIntValues[i];
  }

  for (i = 0; i < mp_oTreePop->mp_iNumTreeBoolVals[m_iSpecies][m_iType]; i++) {
    p_oClone->mp_bBoolValues[i] = mp_bBoolValues[i];
  }

  for (i = 0; i < mp_oTreePop->mp_iNumTreeCharVals[m_iSpecies][m_iType]; i++) {
    strcpy(p_oClone->mp_cCharValues[i], mp_cCharValues[i]);
  }

  return p_oClone;
}
