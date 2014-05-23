//---------------------------------------------------------------------------

#ifndef NCIGrowthH
#define NCIGrowthH
//---------------------------------------------------------------------------
#include "GrowthBase.h"
#include "NCIBase.h"

class clSimManager;
class clTree;
class clTreePopulation;

/**
* NCI growth - Version 2.1
*
* This is a growth shell object which applies the NCI (neighborhood competition
* index) function as it is defined in clNCIBase.
*
* The amount of growth is in cm/year. For multi-year timesteps, the behavior
* will calculate total growth with a loop. Each loop iteration will increment
* DBH for one year. For each year, the Size Effect (SE) value and the
* @htmlonly DBH<sup>&gamma;</sup> @endhtmlonly portion of the Crowding Effect
* is recalculated with the previous year's new DBH value. All values for each
* year of growth are summed to get the growth for the timestep.
*
* This is a generic behavior. It is expected that not all terms in the growth
* equation will be used. A user can turn off some of the terms by setting key
* parameters to 0 or 1. To be efficient, this behavior looks for this and
* has several alternate function forms to avoid extra math. It calls the
* correct function form through function pointers, which it sets during setup.
*
* If any damage effect parameters are used, this behavior must be combined with
* the storm damage behaviors. If the shading effect is used, some light
* behavior must be used (and it really should be clSailLight, but this isn't
* enforced).
*
* This cannot be applied to seedlings.  An error will be thrown if seedlings
* are passed.
*
* The parameter file call string for this to be diameter-incrementing with
* auto-height updating is "NCIGrowth"; for diameter-only incrementing, use
* "NCIGrowth diam only".  The namestring for this behavior is "ncigrowthshell".
* The XML string is "NCIGrowth".
*
* Copyright 2011 Charles D. Canham.
* @author Lora E. Murphy
*
* <br>Edit history:
* <br>-----------------
* <br>October 20, 2011 - Wiped the slate clean for SORTIE 7.0 (LEM)
*/
class clNCIGrowth : virtual public clGrowthBase, clNCIBase {
//note: need the virtual keyword to avoid base class ambiguity.

  public:

  /**
  * Constructor.
  * @param p_oSimManager Sim Manager object.
  */
   clNCIGrowth(clSimManager *p_oSimManager);

  /**
  * Destructor.
  */
  ~clNCIGrowth();

  /**
  * Returns the value in the tree's float data member that holds the value
  * that was calculated by PreGrowthCalcs().
  *
  * @param p_oTree Tree to which to apply growth.
  * @param p_oPop Tree population object.
  * @param fHeightGrowth Amount of height growth, in m (ignored).
  * @return Amount of diameter growth, in cm.
  */
  float CalcDiameterGrowthValue(clTree *p_oTree, clTreePopulation *p_oPop, float fHeightGrowth);

  /**
  * Calculates growth for all NCI trees.  The values are stashed in the
  * "Growth" tree float data member for later application.
  *
  * Steps:
  * <ol>
  * <li>Get all trees for this behavior.</li>
  * <li>For each tree, calculate NCI<sub>i</sub> by calling the function in the
  * function pointer NCI.  Stash the value in "Growth" for each tree.
  * On the way, pick up the max NCI<sub>i</sub> value for each species
  * (NCI<sub>max</sub>) if it is being used (if m_bUseNciMax = true).</li>
  * <li>Go through all the NCI trees again.  Calculate the amount of growth for
  * each using the equations above.  Use the function pointers to make sure
  * that the proper function forms are used.  Stash the end result in
  * "Growth".</li>
  * </ol>
  * This must be called first of any growth stuff, since it uses other trees'
  * DBHs to calculate NCI, and these must be before growth has been applied.
  *
  * Growth per timestep is calculated by looping over the number of years
  * per timestep and incrementing the DBH.
  *
  * @param p_oPop Tree population object.
  */
  void PreGrowthCalcs( clTreePopulation *p_oPop );

  /**
  * Does setup.
  * <ol>
  * <li>AssembleUniqueTypes() is called to create a list of unique behavior
  * types.</li>
  * <li>ReadParameterFile() is called to read the parameter file's data.</li>
  * <li>ValidateData() is called to validate the data.</li>
  * <li>GetTreeMemberCodes() is called to get tree data return codes.</li>
  * <li>SetFunctionPointers() is called to set up our function pointers.</li>
  * </ol>
  *
  * @param p_oDoc DOM tree of parsed input tree.
  */
  void DoShellSetup(xercesc::DOMDocument *p_oDoc);

  /**
  * Captures the namestring passed to this behavior.  This is overridden from
  * clBehaviorBase so we can capture the namestring passed.  Since this class
  * can create multiple kinds of behaviors that function differently, this will
  * capture what kind of behavior this is supposed to be.
  *
  * @param cNameString Behavior's namestring.
  */
  void SetNameData(char *cNameString);

  protected:

  short int **mp_iGrowthCodes; /**<Holds return data codes for the "Growth"
  tree data member.  Array size is number of species to which this behavior
  applies by 2 (saplings and adults).*/
  short int *mp_iWhatBehaviorTypes; /**<List of types managed by this behavior.*/
  short int m_iNumBehaviorTypes; /**<Number of types managed by this behavior.*/

  /**
  * Makes sure all input data is valid.  The following must all be true:
  * <ul>
  * <li>Max radius of neighbor effects must be >= 0</li>
  * <li>Max growth for each species must be > 0</li>
  * <li>X0 (size effect mode) for each species must be > 0</li>
  * <li>Xb (size effect variance) for each species must not = 0</li>
  * <li>Eta for each species for each damage category beyond undamaged must be
  * between 0 and 1, if used</li>
  * <li>Storm Effect parameters for each species for each damage category beyond
  * undamaged must be between 0 and 1, if used</li>
  * <li>DBH divisor must be > 0</li>
  * <li>Any species using Shading (mp_fShadingCoefficient != 0) must have
  * a light behavior assigned (has data member "Light" registered)</li>
  * </ul>
  * @throws modelErr if any of the above conditions are not met.
  */
  void ValidateData();

  /**
  * Gets the return codes for needed tree data members.  If storm damage is
  * used (any of the storm damage parameters are != 1), this declares and
  * populates the mp_iDamageCodes array with the return codes for the
  * "stm_dmg" tree int data member.
  * @throws modelErr if a code comes back -1 for any species/type combo to
  * which this behavior is applied.
  */
  void GetTreeMemberCodes();

  /**
  * Reads data from the parameter file.
  * @param p_oDoc DOM tree of parsed input tree.
  * @throws modelErr if this behavior has been applied to any types except
  * sapling and adult.
  */
  void ReadParameterFile( xercesc::DOMDocument *p_oDoc );

  /**
  * Assembles a unique list of types applied to this behavior and places it in
  * mp_iWhatBehaviorTypes.
  */
  void AssembleUniqueTypes();
};
//---------------------------------------------------------------------------
#endif
