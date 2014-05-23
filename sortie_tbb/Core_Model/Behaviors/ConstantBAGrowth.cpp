//---------------------------------------------------------------------------
#include "ConstantBAGrowth.h"
#include "Tree.h"
#include "GrowthOrg.h"
#include "ParsingFunctions.h"
#include "SimManager.h"
#include "TreePopulation.h"

//////////////////////////////////////////////////////////////////////////////
// clConstantBAGrowth()
//////////////////////////////////////////////////////////////////////////////
clConstantBAGrowth::clConstantBAGrowth(clSimManager *p_oSimManager) :
clWorkerBase(p_oSimManager), clBehaviorBase(p_oSimManager), clGrowthBase(p_oSimManager),
clMichMenBase(p_oSimManager) {
  strcpy(m_cNameString, "constbagrowthshell");
  m_sXMLRoot = "ConstBAGrowth";
}

//////////////////////////////////////////////////////////////////////////////
// CalcDiameterGrowthValue()
//////////////////////////////////////////////////////////////////////////////
float clConstantBAGrowth::CalcDiameterGrowthValue(clTree *p_oTree,
    clTreePopulation *p_oPop, float fHeightGrowth) {
  float fDiam;                   //tree's diameter value

  //Get the appropriate diameter for this tree
  p_oTree->GetValue(mp_oGrowthOrg->GetDiamCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDiam);

  return mp_fAdultConstBAInc[p_oTree->GetSpecies()] / fDiam;
}


//////////////////////////////////////////////////////////////////////////////
// SetNameData()
//////////////////////////////////////////////////////////////////////////////
void clConstantBAGrowth::SetNameData(char *cNameString) {

  //Check the string passed and set the flags accordingly
  if (strcmp("ConstBAGrowth", cNameString) == 0) {
    m_iGrowthMethod = diameter_auto;
  } else if (strcmp("ConstBAGrowth diam only", cNameString) == 0){
    m_iGrowthMethod = diameter_only;
  } else {
    modelErr stcErr;
    stcErr.iErrorCode = BAD_DATA;
    sprintf(stcErr.cMoreInfo, "%s%s%s", "Unrecognized behavior name \"",
        cNameString, "\".");
    strcpy(stcErr.cFunction, "clConstantBAGrowth::SetNameData");
    throw(stcErr);
  }
}


//////////////////////////////////////////////////////////////////////////////
// DoShellSetup()
//////////////////////////////////////////////////////////////////////////////
void clConstantBAGrowth::DoShellSetup(xercesc::DOMDocument *p_oDoc) {
  short int iNumSpecies = mp_oGrowthOrg->GetNumberOfSpecies();

  mp_fAdultConstBAInc = new float[iNumSpecies];

  //Read the base variables
  GetParameterFileData(p_oDoc);
}
