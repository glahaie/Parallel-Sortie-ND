//---------------------------------------------------------------------------
#include "ConstantRadialGrowth.h"
#include "Tree.h"
#include "GrowthOrg.h"
#include "ParsingFunctions.h"
#include "SimManager.h"
#include "TreePopulation.h"

//////////////////////////////////////////////////////////////////////////////
// clConstantRadialGrowth()
//////////////////////////////////////////////////////////////////////////////
clConstantRadialGrowth::clConstantRadialGrowth(clSimManager *p_oSimManager) :
    clWorkerBase( p_oSimManager ), clBehaviorBase( p_oSimManager ),
    clGrowthBase( p_oSimManager), clMichMenBase(p_oSimManager)
{
	strcpy(m_cNameString, "constradgrowthshell");
	m_sXMLRoot = "ConstRadialGrowth";
}

//////////////////////////////////////////////////////////////////////////////
// CalcDiameterGrowthValue()
//////////////////////////////////////////////////////////////////////////////
float clConstantRadialGrowth::CalcDiameterGrowthValue(clTree *p_oTree,
                    clTreePopulation *p_oPop, float fHeightGrowth) {
 try {
   float fDiam;                   //tree's diameter value

   //Get the appropriate diameter for this tree
   p_oTree->GetValue(mp_oGrowthOrg->GetDiamCode(p_oTree->GetSpecies(),
                                                p_oTree->GetType()),
                     &fDiam);

   return mp_fAdultConstRadInc[p_oTree->GetSpecies()];
 }
 catch (modelErr&err) {throw(err);}
 catch (modelMsg &msg) {throw(msg);} //non-fatal error
 catch (...) {
   modelErr stcErr;
   stcErr.iErrorCode = UNKNOWN;
   strcpy(stcErr.cFunction, "clConstantRadialGrowth::CalcDiameterGrowthValue");
   throw(stcErr);
 }
}


//////////////////////////////////////////////////////////////////////////////
// SetNameData()
/////////////////////////////////////////////////////////////////////////////*/
void clConstantRadialGrowth::SetNameData(char *cNameString) {
 try {

   //Check the string passed and set the flags accordingly
   if (strcmp("ConstRadialGrowth", cNameString) == 0) {
     m_iGrowthMethod = diameter_auto;
   } else if (strcmp("ConstRadialGrowth diam only", cNameString) == 0){
     m_iGrowthMethod = diameter_only;
   } else {
     modelErr stcErr;
     stcErr.iErrorCode = BAD_DATA;
     sprintf(stcErr.cMoreInfo, "%s%s%s", "Unrecognized behavior name \"",
        cNameString, "\".");
     strcpy(stcErr.cFunction, "clConstantRadialGrowth::SetNameData");
     throw(stcErr);
   }
 }
 catch (modelErr&err) {throw(err);}
 catch (modelMsg &msg) {throw(msg);} //non-fatal error
 catch (...) {
   modelErr stcErr;
   stcErr.iErrorCode = UNKNOWN;
   strcpy(stcErr.cFunction, "clConstantRadialGrowth::SetNameData");
   throw(stcErr);
 }
}


//////////////////////////////////////////////////////////////////////////////
// DoShellSetup()
//////////////////////////////////////////////////////////////////////////////
void clConstantRadialGrowth::DoShellSetup(xercesc::DOMDocument *p_oDoc) {
 try {
   short int iNumSpecies = mp_oGrowthOrg->GetNumberOfSpecies();

   mp_fAdultConstRadInc = new float[iNumSpecies];

   //Read the base variables
   GetParameterFileData(p_oDoc);

 }
 catch (modelErr&err) {throw(err);}
 catch (modelMsg &msg) {throw(msg);} //non-fatal error
 catch (...) {
   modelErr stcErr;
   stcErr.iErrorCode = UNKNOWN;
   strcpy(stcErr.cFunction, "clRelativeGrowth::GetNameData");
   throw(stcErr);
 }
}
