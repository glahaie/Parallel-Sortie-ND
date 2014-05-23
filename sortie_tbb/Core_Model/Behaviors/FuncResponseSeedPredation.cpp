//---------------------------------------------------------------------------
// FuncResponseSeedPredation.cpp
//---------------------------------------------------------------------------
#include "FuncResponseSeedPredation.h"
#include "Grid.h"
#include "ModelMath.h"
#include "ParsingFunctions.h"
#include "SimManager.h"
#include "TreePopulation.h"
#include "Constants.h"
#include "Plot.h"
#include <math.h>
#include <fstream>

/////////////////////////////////////////////////////////////////////////////
// Constructor
/////////////////////////////////////////////////////////////////////////////
clFuncResponseSeedPredation::clFuncResponseSeedPredation(
    clSimManager * p_oSimManager) :
  clWorkerBase(p_oSimManager), clBehaviorBase(p_oSimManager) {
  try
  {
    strcpy(m_cNameString, "FunctionalResponseSeedPredation");
    m_sXMLRoot = "FunctionalResponseSeedPredation";

    //Versions
    m_fVersionNumber = 1;
    m_fMinimumVersionNumber = 1;

    //Allowed file types
    m_iNumAllowedTypes = 2;
    mp_iAllowedFileTypes = new int[m_iNumAllowedTypes];
    mp_iAllowedFileTypes[0] = parfile;
    mp_iAllowedFileTypes[1] = detailed_output;

    mp_iSeedGridCode = NULL;
    mp_fMaxInstantaneousDeclineRate = NULL;
    mp_fDemographicEfficiency = NULL;
    mp_fDensityDependentCoefficient = NULL;
    mp_fForagingEfficiency = NULL;
    mp_fMaxIntakeRate = NULL;

    mp_fTempSeeds = NULL;

  }
  catch (modelErr& err)
  {
    throw(err);
  }
  catch (modelMsg & msg)
  {
    throw(msg);
  } //non-fatal error
  catch (...)
  {
    modelErr stcErr;
    stcErr.iErrorCode = UNKNOWN;
    strcpy(stcErr.cFunction, "clFuncResponseSeedPredation::clFuncResponseSeedPredation");
    throw(stcErr);
  }
}

/////////////////////////////////////////////////////////////////////////////
// Destructor
/////////////////////////////////////////////////////////////////////////////
clFuncResponseSeedPredation::~clFuncResponseSeedPredation() {
  delete[] mp_iSeedGridCode;
  delete[] mp_fMaxInstantaneousDeclineRate;
  delete[] mp_fDemographicEfficiency;
  delete[] mp_fDensityDependentCoefficient;
  delete[] mp_fForagingEfficiency;
  delete[] mp_fMaxIntakeRate;
  delete[] mp_fTempSeeds;
}

/////////////////////////////////////////////////////////////////////////////
// Action
/////////////////////////////////////////////////////////////////////////////
void clFuncResponseSeedPredation::Action() {
  try
  {
    using namespace std;
    fstream oOut;
    float fTemp, fNumTotalSeeds, fNumPredators;
    int iNumXCells = mp_oSeedGrid->GetNumberXCells(), //number X seed grid cells
        iNumYCells = mp_oSeedGrid->GetNumberYCells(), //number Y seed grid cells
        iX, iY, //grid loop counters
        i;

    if (!m_bPreservePredatorDensities)
    {
      SetPredatorInitialDensity();
    }

    // If there is output to do, add up the starting seeds of each species and
    // write it out
    if (strlen(m_cOutput) > 0) {
      float *p_fSeedsToWrite = new float[m_iNumBehaviorSpecies];
      for (i = 0; i < m_iNumBehaviorSpecies; i++)
        p_fSeedsToWrite[i] = 0;

      for (iX = 0; iX < iNumXCells; iX++) {
        for (iY = 0; iY < iNumYCells; iY++) {
          for (i = 0; i < m_iNumBehaviorSpecies; i++) {
            mp_oSeedGrid->GetValueOfCell(iX, iY, mp_iSeedGridCode[i], &fTemp);
            p_fSeedsToWrite[i] += fTemp;
          }
        }
      }

      oOut.open(m_cOutput, ios::out | ios::app);
      oOut << "\n\nSeed predation, timestep "
           << mp_oSimManager->GetCurrentTimestep()
           << ", Starting seed numbers:\nSpecies";
      for (i = 0; i < m_iNumBehaviorSpecies; i++)
        oOut << "\t" << mp_iWhatSpecies[i];
      oOut << "\nNumber";
      for (i = 0; i < m_iNumBehaviorSpecies; i++)
        oOut << "\t" << p_fSeedsToWrite[i];

      oOut.close();
      delete[] p_fSeedsToWrite;
    }

    if (m_bIsLinked) {

      //Get all the seeds and all the predators
      for (i = 0; i < m_iNumBehaviorSpecies; i++)
        mp_fTempSeeds[i] = 0;

      m_fTempPredators = 0;
      for (iX = 0; iX < iNumXCells; iX++)
      {
        for (iY = 0; iY < iNumYCells; iY++)
        {
          mp_oPredatorGrid->GetValueOfCell(iX, iY, m_iNumPredsCode, &fNumPredators);
          m_fTempPredators += fNumPredators;
          for (i = 0; i < m_iNumBehaviorSpecies; i++)
          {
            mp_oSeedGrid->GetValueOfCell(iX, iY, mp_iSeedGridCode[i], &fTemp);
            mp_fTempSeeds[i] += fTemp;
          }
        }
      }

      //Get the starting number of total seeds for calculating offtake
      fNumTotalSeeds = 0;
      for (i = 0; i < m_iNumBehaviorSpecies; i++) {
        fNumTotalSeeds += mp_fTempSeeds[i];
      }

      if (fNumTotalSeeds == 0) m_fOfftake = 0;
      else {
        DoModel();
        fTemp = 0;
        for (i = 0; i < m_iNumBehaviorSpecies; i++) {
          fTemp += mp_fTempSeeds[i];
        }
        m_fOfftake = (fNumTotalSeeds - fTemp)/fNumTotalSeeds;
      }
      //Update predator grid - spread them out evenly
      fNumPredators = m_fTempPredators / (iNumXCells * iNumYCells);
      for (iX = 0; iX < iNumXCells; iX++) {
        for (iY = 0; iY < iNumYCells; iY++) {
           mp_oPredatorGrid->SetValueOfCell(iX, iY, m_iNumPredsCode, fNumPredators);
        }
      }

    } else {

      //Go through each grid cell
      for (iX = 0; iX < iNumXCells; iX++)
      {
        for (iY = 0; iY < iNumYCells; iY++)
        {

          //Get the number of seeds for each species
          for (i = 0; i < m_iNumBehaviorSpecies; i++)
          {
            mp_oSeedGrid->GetValueOfCell(iX, iY, mp_iSeedGridCode[i], &fTemp);
            mp_fTempSeeds[i] = fTemp;
          }

          //Get initial number of predators
          mp_oPredatorGrid->GetValueOfCell(iX, iY, m_iNumPredsCode, & m_fTempPredators);

          DoModel();

          //Update the amount of seeds and predators in the grids
          for (i = 0; i < m_iNumBehaviorSpecies; i++)
          {
            mp_oSeedGrid->SetValueOfCell(iX, iY, mp_iSeedGridCode[i], mp_fTempSeeds[i]);
          }
          mp_oPredatorGrid->SetValueOfCell(iX, iY, m_iNumPredsCode, m_fTempPredators);
        }
      }
    }

    // If there is output to do, add up the final seeds of each species and
    // write it out
    if (strlen(m_cOutput) > 0) {
      float *p_fSeedsToWrite = new float[m_iNumBehaviorSpecies];
      for (i = 0; i < m_iNumBehaviorSpecies; i++)
        p_fSeedsToWrite[i] = 0;

      for (iX = 0; iX < iNumXCells; iX++) {
        for (iY = 0; iY < iNumYCells; iY++) {
          for (i = 0; i < m_iNumBehaviorSpecies; i++) {
            mp_oSeedGrid->GetValueOfCell(iX, iY, mp_iSeedGridCode[i], &fTemp);
            p_fSeedsToWrite[i] += fTemp;
          }
        }
      }

      oOut.open(m_cOutput, ios::out | ios::app);
      oOut << "\n\nSeed predation, timestep "
           << mp_oSimManager->GetCurrentTimestep()
           << ", Final seed numbers after predator consumption:\nSpecies";
      for (i = 0; i < m_iNumBehaviorSpecies; i++)
        oOut << "\t" << mp_iWhatSpecies[i];
      oOut << "\nNumber";
      for (i = 0; i < m_iNumBehaviorSpecies; i++)
        oOut << "\t" << p_fSeedsToWrite[i];

      oOut.close();
      delete[] p_fSeedsToWrite;
    }
  }
  catch (modelErr& err)
  {
    throw(err);
  }
  catch (modelMsg & msg)
  {
    throw(msg);
  } //non-fatal error
  catch (...)
  {
    modelErr stcErr;
    stcErr.iErrorCode = UNKNOWN;
    strcpy(stcErr.cFunction, "clFuncResponseSeedPredation::Action");
    throw(stcErr);
  }
}

/////////////////////////////////////////////////////////////////////////////
// DoModel
/////////////////////////////////////////////////////////////////////////////
void clFuncResponseSeedPredation::DoModel() {
        //if outputting - number of overall seeds for each timestep
  float **p_fOverallSeeds = NULL,
        //if outputting - number of overall predators for each timestep
        *p_fOverallPredators = NULL,
        //number new seeds added each week during seed fall
        *p_fSeedFallAmount = NULL,
        //number of seeds consumed by predators
        *p_fNumSeedsConsumed = NULL,
        //per capita seed offtake for each timestep
        *p_fPerCapitaOfftake = NULL,
        *p_fNumSeeds = NULL;
  try
  {
    using namespace std;
    fstream oOut;
    float fPerCapitaSeedAvail, //number seeds per capita available for the week
          fInstantaneousRateOfChange, //rate of change of predator population
          fOfftake, //amount of total offtake in one week
          fAllOfftake,
          fTotalSeeds,
          fModelAreaInHa,
          fProportionNotGerminating = 1 - m_fProportionGerminating,
          fWeekToDay = 1.0 / 7.0;
    int iWeek, i, iSeason;
    bool bOutput = false;

    if (m_bIsLinked) {
      clPlot *p_oPlot = mp_oSimManager->GetPlotObject();
      fModelAreaInHa = p_oPlot->GetPlotArea();
    }
    else fModelAreaInHa = m_fCellArea / M_SQ_PER_HA;

    //If there's a filename, open it and set the output flag to true
    if (strlen(m_cOutput) > 0)
    {
      bOutput = true;
      oOut.open(m_cOutput, ios::out | ios::app);
      oOut << "\n\nSeed predation, timestep "
           << mp_oSimManager->GetCurrentTimestep()
           << "\nWeek";

      for (i = 0; i < m_iNumBehaviorSpecies; i++)
        oOut << "\t Sp " << mp_iWhatSpecies[i] << " Seeds";

      oOut << "\tPredators";

      p_fOverallSeeds = new float*[m_iNumBehaviorSpecies];
      for (i = 0; i < m_iNumBehaviorSpecies; i++)
        p_fOverallSeeds[i] = new float[m_iNumWeeksToModel + 1];

      p_fOverallPredators = new float[m_iNumWeeksToModel + 1];

      for (iWeek = 0; iWeek <= m_iNumWeeksToModel; iWeek++)
      {
        for (i = 0; i < m_iNumBehaviorSpecies; i++)
          p_fOverallSeeds[i][iWeek] = 0;
        p_fOverallPredators[iWeek] = 0;
      }
    }

    //mp_fTempSeeds contains the starting number of seeds; p_fNumSeeds will
    //count down the number remaining; fNumSeedsConsumed has the number
    //eaten by predators (which is NOT just the previous total minus the
    //current count - some seeds safely "escape" by germinating)

    p_fSeedFallAmount = new float[m_iNumBehaviorSpecies];
    p_fNumSeeds = new float[m_iNumBehaviorSpecies];
    p_fPerCapitaOfftake = new float[m_iNumBehaviorSpecies];
    p_fNumSeedsConsumed = new float[m_iNumBehaviorSpecies];

    for (i = 0; i < m_iNumBehaviorSpecies; i++) {
      p_fNumSeeds[i] = 0;
      p_fNumSeedsConsumed[i] = 0;

      //Get the seed fall amount for each species
      p_fSeedFallAmount[i] = mp_fTempSeeds[i] / m_iNumWeeksSeedFall;
    }

    if (bOutput)
    {
      for (i = 0; i < m_iNumBehaviorSpecies; i++)
        p_fOverallSeeds[i][0] += p_fSeedFallAmount[i];
      p_fOverallPredators[0] += m_fTempPredators;
    }

    //Go through the number of timesteps for this cell
    for (iWeek = 0; iWeek < m_iNumWeeksToModel; iWeek++)
    {

      ////////////////////////////////////////////////////
      // Update the number of seeds
      ////////////////////////////////////////////////////

      //If this is a seed fall week, add the seed fall amount to the
      //number of seeds for each species
      if (iWeek < m_iNumWeeksSeedFall)
      {
        for (i = 0; i < m_iNumBehaviorSpecies; i++) {
          p_fNumSeeds[i] += p_fSeedFallAmount[i];
        }
      }

      //If this is a germination week, subtract out the number of
      //germinating seeds
      if (iWeek >= (m_iWeekGerminationStarts-1))
      {
        for (i = 0; i < m_iNumBehaviorSpecies; i++) {
          p_fNumSeeds[i] *= fProportionNotGerminating;
        }
      }

      //Get the total number of seeds so we can calculate proportion of seeds
      fTotalSeeds = 0;
      for (i = 0; i < m_iNumBehaviorSpecies; i++) {
        fTotalSeeds += p_fNumSeeds[i];
      }
      if (fTotalSeeds == 0) break;

      for (i = 0; i < m_iNumBehaviorSpecies; i++) {

        //Get the per capita seed availability per day
        fPerCapitaSeedAvail = (p_fNumSeeds[i] / m_fTempPredators) * fWeekToDay;

        //Get per capita seed offtake per day, multiplied by the proportion'
        //of this species
        p_fPerCapitaOfftake[i] = mp_fMaxIntakeRate[i] *
                                (p_fNumSeeds[i] / fTotalSeeds) *
               (1 - exp(-(fPerCapitaSeedAvail * mp_fForagingEfficiency[i])));

        //Subtract how much seed was eaten from the total seed pool - scale
        //back up to per week
        fOfftake = p_fPerCapitaOfftake[i] * m_fTempPredators * 7;
        if(fOfftake > p_fNumSeeds[i]) fOfftake = p_fNumSeeds[i];
        p_fNumSeeds[i] -= fOfftake;
        p_fNumSeedsConsumed[i] += fOfftake;
        if (p_fNumSeeds[i] < 0) p_fNumSeeds[i] = 0;

      }

      ////////////////////////////////////////////////////
      // Update the number of predators
      ////////////////////////////////////////////////////

      //Figure out the season
      if (iWeek < (m_iWeekSeason2Starts-1))
        iSeason = 0;
      else iSeason = 1;

      //Get the summed offtake weighted by each species' proportions
      fAllOfftake = 0;
      for (i = 0; i < m_iNumBehaviorSpecies; i++) {
        fAllOfftake += p_fPerCapitaOfftake[i];
      }

      //Calculate the instantaneous rate of change
      fInstantaneousRateOfChange =  mp_fMaxInstantaneousDeclineRate[iSeason] +
               (mp_fDemographicEfficiency[iSeason] * fAllOfftake) +
               (mp_fDensityDependentCoefficient[iSeason] *
               (m_fTempPredators/fModelAreaInHa));
      fInstantaneousRateOfChange /= 12;

      //Now calculate the number of predators
      m_fTempPredators = m_fTempPredators * exp(fInstantaneousRateOfChange);

      //If number of predators is zero, stop the loop
      if (0 == m_fTempPredators)
      {
        break;
      }

      if (bOutput)
      {
        for (i = 0; i < m_iNumBehaviorSpecies; i++)
          p_fOverallSeeds[i][iWeek + 1] += p_fNumSeeds[i];
        p_fOverallPredators[iWeek + 1] += m_fTempPredators;
      }
    }

    //The number left is the original amount minus the number consumed -
    //update mp_fTempSeeds
    for (i = 0; i < m_iNumBehaviorSpecies; i++) {
       mp_fTempSeeds[i] -= p_fNumSeedsConsumed[i];
    }

    if (bOutput)
    {
      //Write out all output
      for (iWeek = 0; iWeek < m_iNumWeeksToModel + 1; iWeek++)
      {
        oOut << "\n" << iWeek;
        for (i = 0; i < m_iNumBehaviorSpecies; i++)
          oOut << "\t" << p_fOverallSeeds[i][iWeek];
        oOut << "\t" << p_fOverallPredators[iWeek];
      }
      oOut.close();

      for (i = 0; i < m_iNumBehaviorSpecies; i++)
        delete[] p_fOverallSeeds[i];
    }
    delete[] p_fOverallSeeds;
    delete[] p_fOverallPredators;
    delete[] p_fSeedFallAmount;
    delete[] p_fNumSeeds;
    delete[] p_fPerCapitaOfftake;
    delete[] p_fNumSeedsConsumed;

  }
  catch (modelErr& err)
  {
    delete[] p_fOverallSeeds;
    delete[] p_fOverallPredators;
    delete[] p_fSeedFallAmount;
    delete[] p_fNumSeeds;
    delete[] p_fPerCapitaOfftake;
    delete[] p_fNumSeedsConsumed;
    throw(err);
  }
  catch (modelMsg & msg)
  {
    delete[] p_fOverallSeeds;
    delete[] p_fOverallPredators;
    delete[] p_fSeedFallAmount;
    delete[] p_fNumSeeds;
    delete[] p_fPerCapitaOfftake;
    delete[] p_fNumSeedsConsumed;
    throw(msg);
  } //non-fatal error
  catch (...)
  {
    delete[] p_fOverallSeeds;
    delete[] p_fOverallPredators;
    delete[] p_fSeedFallAmount;
    delete[] p_fNumSeeds;
    delete[] p_fPerCapitaOfftake;
    delete[] p_fNumSeedsConsumed;
    modelErr stcErr;
    stcErr.iErrorCode = UNKNOWN;
    strcpy(stcErr.cFunction, "clFuncResponseSeedPredation::Action");
    throw(stcErr);
  }
}

/////////////////////////////////////////////////////////////////////////////
// GetParameterFileData
/////////////////////////////////////////////////////////////////////////////
void clFuncResponseSeedPredation::GetParameterFileData(DOMDocument * p_oDoc) {
  floatVal *p_fTempValues = NULL;  //for getting species-specific values
  try
  {
    clTreePopulation * p_oPop = ( clTreePopulation * ) mp_oSimManager->GetPopulationObject( "treepopulation" );
    DOMElement * p_oElement = GetParentParametersElement(p_oDoc);
    int i;

    mp_fMaxInstantaneousDeclineRate = new float[2];
    mp_fDemographicEfficiency = new float[2];
    mp_fDensityDependentCoefficient = new float[2];

    mp_fForagingEfficiency = new float[m_iNumBehaviorSpecies];
    mp_fMaxIntakeRate = new float[m_iNumBehaviorSpecies];

    //Declare the temp array and populate it with the species to which this
    //behavior applies
    p_fTempValues = new floatVal[m_iNumBehaviorSpecies];
    for (i = 0; i < m_iNumBehaviorSpecies; i++)
      p_fTempValues[i].code = mp_iWhatSpecies[i];

    //Max instantaneous rate at which predator abundance declines in the
    //absense of food
    FillSingleValue(p_oElement, "pr_funcRespMaxInstDeclineRate1", & mp_fMaxInstantaneousDeclineRate[0], true);
    FillSingleValue(p_oElement, "pr_funcRespMaxInstDeclineRate2", & mp_fMaxInstantaneousDeclineRate[1], true);

    //Population's demographic efficiency
    FillSingleValue(p_oElement, "pr_funcRespDemographicEfficiency1", & mp_fDemographicEfficiency[0], true);
    FillSingleValue(p_oElement, "pr_funcRespDemographicEfficiency2", & mp_fDemographicEfficiency[1], true);

    //Density-dependent coefficient
    FillSingleValue(p_oElement, "pr_funcRespDensityDependentCoefficient1", & mp_fDensityDependentCoefficient[0], true);
    FillSingleValue(p_oElement, "pr_funcRespDensityDependentCoefficient2", & mp_fDensityDependentCoefficient[1], true);


    //Maximum intake rate - number of seeds per predator per week
    FillSpeciesSpecificValue(p_oElement, "pr_funcRespMaxIntakeRate",
        "pr_frmirVal", p_fTempValues, m_iNumBehaviorSpecies, p_oPop, true);
    for (i = 0; i < m_iNumBehaviorSpecies; i++)
      mp_fMaxIntakeRate[i] = p_fTempValues[i].val;

    //Foraging efficiency
    FillSpeciesSpecificValue(p_oElement, "pr_funcRespForagingEfficiency",
        "pr_frfeVal", p_fTempValues, m_iNumBehaviorSpecies, p_oPop, true);
    for (i = 0; i < m_iNumBehaviorSpecies; i++)
      mp_fForagingEfficiency[i] = p_fTempValues[i].val;

    //Number of weeks for which seedfall occurs
    FillSingleValue(p_oElement, "pr_funcRespNumWeeksSeedFall", & m_iNumWeeksSeedFall, true);
    //Throw an error if not positive
    if (m_iNumWeeksSeedFall <= 0)
    {
      delete[] p_fTempValues;
      modelErr stcErr;
      stcErr.iErrorCode = BAD_DATA;
      strcpy(stcErr.cFunction, "clFuncResponseSeedPredation::GetData");
      strcpy(stcErr.cMoreInfo, "Number of weeks of seedfall must be greater than zero.");
      throw(stcErr);
    }

    //Number of weeks to model
    FillSingleValue(p_oElement, "pr_funcRespNumWeeksToModel", & m_iNumWeeksToModel, true);
    //Throw an error if not between 0 and 53 (non-inclusive)
    if (m_iNumWeeksToModel <= 0 || m_iNumWeeksToModel > 52)
    {
      delete[] p_fTempValues;
      modelErr stcErr;
      stcErr.iErrorCode = BAD_DATA;
      strcpy(stcErr.cFunction, "clFuncResponseSeedPredation::GetData");
      strcpy(stcErr.cMoreInfo, "Number of weeks to model must be between 1 and 52 inclusive.");
      throw(stcErr);
    }

    //Week in which germination starts
    FillSingleValue(p_oElement, "pr_funcRespWeekGerminationStarts", & m_iWeekGerminationStarts, true);
    //Throw an error if not between 0 and 52 (inclusive)
    if (m_iWeekGerminationStarts < 0 || m_iWeekGerminationStarts > 52)
    {
      delete[] p_fTempValues;
      modelErr stcErr;
      stcErr.iErrorCode = BAD_DATA;
      strcpy(stcErr.cFunction, "clFuncResponseSeedPredation::GetData");
      strcpy(stcErr.cMoreInfo, "Week germination starts must be between 0 and 52 inclusive.");
      throw(stcErr);
    }

    //Week in which season 2 starts
    FillSingleValue(p_oElement, "pr_funcRespWeekSeason2Starts", & m_iWeekSeason2Starts, true);
    //Throw an error if not between 0 and 52 (inclusive)
    if (m_iWeekSeason2Starts < 0 || m_iWeekSeason2Starts > 52)
    {
      delete[] p_fTempValues;
      modelErr stcErr;
      stcErr.iErrorCode = BAD_DATA;
      strcpy(stcErr.cFunction, "clFuncResponseSeedPredation::GetData");
      strcpy(stcErr.cMoreInfo, "Week season 2 must be between 0 and 52 inclusive.");
      throw(stcErr);
    }

    //Proportion germinating
    FillSingleValue(p_oElement, "pr_funcRespProportionGerminating", & m_fProportionGerminating, true);
    //Throw an error if not between 0 and 1 (inclusive)
    if (m_fProportionGerminating < 0 || m_fProportionGerminating > 1)
    {
      delete[] p_fTempValues;
      modelErr stcErr;
      stcErr.iErrorCode = BAD_DATA;
      strcpy(stcErr.cFunction, "clFuncResponseSeedPredation::GetData");
      strcpy(stcErr.cMoreInfo, "Proportion germinating must be between 0 and 1 inclusive.");
      throw(stcErr);
    }

    //Output filename, if desired
    m_cOutput[0] = '\0';
    FillSingleValue(p_oElement, "pr_funcRespOutputFilename", m_cOutput, MAX_FILENAME_SIZE, false);

    //Whether or not to preserve predator densities
    FillSingleValue(p_oElement, "pr_funcRespPreservePredatorDensities", & m_bPreservePredatorDensities, true);

    //Predator initial density in number per square meter
    FillSingleValue(p_oElement, "pr_funcRespPredatorInitialDensity", & m_fPredatorInitialDensity, true);
    //Throw an error if not positive
    if (m_fPredatorInitialDensity <= 0)
    {
      delete[] p_fTempValues;
      modelErr stcErr;
      stcErr.iErrorCode = BAD_DATA;
      strcpy(stcErr.cFunction, "clFuncResponseSeedPredation::GetData");
      strcpy(stcErr.cMoreInfo, "Predator initial density must be greater than zero.");
      throw(stcErr);
    }
    delete[] p_fTempValues;

  }
  catch (modelErr& err)
  {
  	delete[] p_fTempValues;
    throw(err);
  }
  catch (modelMsg & msg)
  {
    throw(msg);
  } //non-fatal error
  catch (...)
  {
    modelErr stcErr;
    stcErr.iErrorCode = UNKNOWN;
    strcpy(stcErr.cFunction, "clFuncResponseSeedPredation::GetParameterFileData");
    throw(stcErr);
  }
}

/////////////////////////////////////////////////////////////////////////////
// GetData
/////////////////////////////////////////////////////////////////////////////
void clFuncResponseSeedPredation::GetData(DOMDocument * p_oDoc) {
try
  {
    char cLabel[MAX_GRID_LABEL_SIZE];
    int i;

    GetParameterFileData(p_oDoc);

    //Declare our seed grid and temp seeds arrays
    mp_fTempSeeds = new float[m_iNumBehaviorSpecies];
    mp_iSeedGridCode = new short int[m_iNumBehaviorSpecies];

    //Fetch the seed grid
    mp_oSeedGrid = mp_oSimManager->GetGridObject("Dispersed Seeds");
    if (mp_oSeedGrid == NULL)
    {
      modelErr stcErr;
      strcpy(stcErr.cFunction, "clFuncResponseSeedPredation::GetData");
      strcpy(stcErr.cMoreInfo, "Disperse behaviors must be used with functional response seed predation.");
      stcErr.iErrorCode = CANT_FIND_OBJECT;
      throw(stcErr);
    }

    //Now get the data codes
    for (i = 0; i < m_iNumBehaviorSpecies; i++)
    {
      sprintf(cLabel, "%s%d", "seeds_", mp_iWhatSpecies[i]);
      mp_iSeedGridCode[i] = mp_oSeedGrid->GetFloatDataCode(cLabel);
      if (-1 == mp_iSeedGridCode[i])
      {
        modelErr stcErr;
        stcErr.iErrorCode = BAD_DATA;
        strcpy(stcErr.cFunction, "clFuncResponseSeedPredation::GetData");
        strcpy(stcErr.cMoreInfo, "Unexpected grid data return code.");
        throw(stcErr);
      }
    }

    m_fCellArea = mp_oSeedGrid->GetLengthXCells() * mp_oSeedGrid->GetLengthYCells();

    //Set up the predator grid
    //Check to see if there was a map file
    mp_oPredatorGrid = mp_oSimManager->GetGridObject("Seed Predators");
    if (mp_oPredatorGrid == NULL)
    {

      //Create the grid and initialize it
      mp_oPredatorGrid = mp_oSimManager->CreateGrid("Seed Predators", //grid name
          0, //number of int data members
          1, //number of float data members
          0, //number of char data members
          0, //number of bool data members
          mp_oSeedGrid->GetLengthXCells(), //length of X cells
          mp_oSeedGrid->GetLengthYCells()); //length of Y cells

      m_iNumPredsCode = mp_oPredatorGrid->RegisterFloat("num preds");

      if (m_bPreservePredatorDensities)
      {
        SetPredatorInitialDensity();
      }
    }
    else
    {
      //Get the code - throw error if not present
      m_iNumPredsCode = mp_oPredatorGrid->GetFloatDataCode("num preds");
      if (-1 == m_iNumPredsCode)
      {
        modelErr stcErr;
        stcErr.iErrorCode = BAD_DATA;
        strcpy(stcErr.cFunction, "clFuncResponseSeedPredation::GetData");
        strcpy(stcErr.cMoreInfo, "Unexpected grid data return code.");
        throw(stcErr);
      }

      if (mp_oSeedGrid->GetNumberXCells() != mp_oPredatorGrid->GetNumberXCells()
          || mp_oSeedGrid->GetNumberYCells() != mp_oPredatorGrid->GetNumberYCells())
      {
        modelErr stcErr;
        stcErr.iErrorCode = BAD_DATA;
        strcpy(stcErr.cFunction, "clFuncResponseSeedPredation::GetData");
        strcpy(stcErr.cMoreInfo, "Predator grid cell resolution doesn't match seed grid cell resolution.");
        throw(stcErr);
      }
    }

  }
  catch (modelErr& err)
  {
    throw(err);
  }
  catch (modelMsg & msg)
  {
    throw(msg);
  } //non-fatal error
  catch (...)
  {
    modelErr stcErr;
    stcErr.iErrorCode = UNKNOWN;
    strcpy(stcErr.cFunction, "clFuncResponseSeedPredation::GetData");
    throw(stcErr);
  }
}

/////////////////////////////////////////////////////////////////////////////
// SetPredatorInitialDensity
/////////////////////////////////////////////////////////////////////////////
void clFuncResponseSeedPredation::SetPredatorInitialDensity() {
  float fNumPredators = m_fPredatorInitialDensity * m_fCellArea;
  int iNumXCells = mp_oPredatorGrid->GetNumberXCells(), iNumYCells =
      mp_oPredatorGrid->GetNumberYCells(), iX, iY;

  for (iX = 0; iX < iNumXCells; iX++) {
    for (iY = 0; iY < iNumYCells; iY++) {
      mp_oPredatorGrid->SetValueOfCell(iX, iY, m_iNumPredsCode, fNumPredators);
    }
  }
}

//////////////////////////////////////////////////////////////////////////////
// SetNameData()
//////////////////////////////////////////////////////////////////////////////
void clFuncResponseSeedPredation::SetNameData(char * cNameString) {

  //Check the string passed and set the flags accordingly
  if (strcmp("FunctionalResponseSeedPredation", cNameString) == 0) {
    strcpy(m_cNameString, "FunctionalResponseSeedPredation");
    m_bIsLinked = false;
  } else if (strcmp("LinkedFunctionalResponseSeedPredation", cNameString) == 0) {
    strcpy(m_cNameString, "LinkedFunctionalResponseSeedPredation");
    m_bIsLinked = true;
  }
}

/////////////////////////////////////////////////////////////////////////////
// Action
/////////////////////////////////////////////////////////////////////////////
/*void clFuncResponseSeedPredation::Action() {
  try
  {
    using namespace std;
    fstream oOut;
    float * p_fOverallSeeds = NULL, //if outputting - number of overall seeds
    //for each timestep
    * p_fOverallPredators = NULL, //if outputting - number of overall
    //predators for each timestep
    * p_fSeedProportions = new float[m_iNumBehaviorSpecies], //proportion
    //of each species' seeds in the cell so we can preserve it
    fNumSeeds, //number of seeds in a cell
    fNumSeedsConsumed, //number of seeds consumed by predators
    fSeedFallAmount, //number new seeds added each week during seed fall
    fPerCapitaOfftake, //per capita seed offtake for each timestep
    fInstantaneousRateOfChange, //rate of change of predator population
    fPerCapitaSeedAvail, //number seeds per capita available for the week
    fOfftake, //amount of total offtake in one week
    fProportionNotGerminating = 1 - m_fProportionGerminating, fWeekToDay = 1.0 / 7.0, fNumPredators; //number of predators in a cell
    int iNumXCells = mp_oSeedGrid->GetNumberXCells(), //number X seed grid cells
    iNumYCells = mp_oSeedGrid->GetNumberYCells(), //number Y seed grid cells
    iSeedFallCounter, //counter which controls the time of seed rain
    iX, iY, //grid loop counters
    i;
    bool bOutput = false; //Whether or not to write timestep data

    if (!m_bPreservePredatorDensities)
    {
      SetPredatorInitialDensity();
    }

    //If there's a filename, open it and set the output flag to true
    if (strlen(m_cOutput) > 0)
    {
      bOutput = true;
      oOut.open(m_cOutput, ios::out | ios::app);
      oOut << "\n\nSeed predation, timestep " << mp_oSimManager->GetCurrentTimestep() << "\nWeek\tSeeds\tPredators";

      p_fOverallSeeds = new float[m_iNumWeeksToModel + 1];
      p_fOverallPredators = new float[m_iNumWeeksToModel + 1];

      for (i = 0; i <= m_iNumWeeksToModel; i++)
      {
        p_fOverallSeeds[i] = 0;
        p_fOverallPredators[i] = 0;
      }
    }

    //Go through each grid cell
    for (iX = 0; iX < iNumXCells; iX++)
    {
      for (iY = 0; iY < iNumYCells; iY++)
      {

        //Get the total number of seeds and their relative proportions
        fNumSeeds = 0;
        fNumSeedsConsumed = 0;
        for (i = 0; i < m_iNumBehaviorSpecies; i++)
        {
          mp_oSeedGrid->GetValueOfCell(iX, iY, mp_iSeedGridCode[i], p_fSeedProportions + i);
          fNumSeeds += p_fSeedProportions[i];
        }
        if (fNumSeeds > 0)
        {
          for (i = 0; i < m_iNumBehaviorSpecies; i++)
          {
            p_fSeedProportions[i] /= fNumSeeds;
          }
        }

        //Get initial number of predators
        mp_oPredatorGrid->GetValueOfCell(iX, iY, m_iNumPredsCode, & fNumPredators);

        //Get the seed fall amount
        fSeedFallAmount = fNumSeeds / m_iNumWeeksSeedFall;

        //Initialize the seed fall counter and the number of seeds
        iSeedFallCounter = 1;
        fNumSeeds = 0;

        if (bOutput)
        {
          p_fOverallSeeds[0] += fSeedFallAmount;
          p_fOverallPredators[0] += fNumPredators;
        }

        //Go through the number of timesteps for this cell
        for (i = 0; i < m_iNumWeeksToModel; i++)
        {

          ////////////////////////////////////////////////////
          // Update the number of seeds
          ////////////////////////////////////////////////////

          //If this is a seed fall week, add the seed fall amount to the
          //number of seeds
          if (iSeedFallCounter <= m_iNumWeeksSeedFall)
          {
            fNumSeeds += fSeedFallAmount;
            iSeedFallCounter++;
          }

          //If this is a germination week, subtract out the number of
          //germinating seeds
          if (i >= m_iWeekGerminationStarts)
          {
            fNumSeeds *= fProportionNotGerminating;
          }

          //Get the per capita seed availability per day
          fPerCapitaSeedAvail = (fNumSeeds / fNumPredators) * fWeekToDay;

          //Get per capita seed offtake per day
          fPerCapitaOfftake = m_fMaxIntakeRate * (1 - exp(-(fPerCapitaSeedAvail * m_fForagingEfficiency)));

          //Subtract how much seed was eaten from the total seed pool - scale
          //back up to per week
          fOfftake = fPerCapitaOfftake * fNumPredators * 7;
          fNumSeeds -= fOfftake;
          fNumSeedsConsumed += fOfftake;
          if (fNumSeeds < 0) fNumSeeds = 0;

          ////////////////////////////////////////////////////
          // Update the number of predators
          ////////////////////////////////////////////////////

          //Calculate the instantaneous rate of change
          //Yes, I know fPerCapitaOfftake is per day; it's supposed to be this
          //way but I don't know why
          fInstantaneousRateOfChange =
          m_fMaxInstantaneousDeclineRate + (m_fDemographicEfficiency * fPerCapitaOfftake)
          + (m_fDensityDependentCoefficient * fNumPredators);

          //Now calculate the number of predators
          fNumPredators = fNumPredators * exp(fInstantaneousRateOfChange);

          //If number of predators is zero, stop the loop
          if (0 == fNumPredators)
          {
            break;
          }

          if (bOutput)
          {
            p_fOverallSeeds[i + 1] += fNumSeeds;
            p_fOverallPredators[i + 1] += fNumPredators;
          }
        }

        //Update the amount of seeds and predators in the grids
        for (i = 0; i < m_iNumBehaviorSpecies; i++)
        {
          mp_oSeedGrid->GetValueOfCell(iX, iY, mp_iSeedGridCode[i], & fNumSeeds);
          //Subtract from the amount of seeds the species proportion of the
          //total number consumed
          fNumSeeds -= clModelMath::RandomRound(p_fSeedProportions[i] * fNumSeedsConsumed);
          if (fNumSeeds < 0) fNumSeeds = 0;
          mp_oSeedGrid->SetValueOfCell(iX, iY, mp_iSeedGridCode[i], fNumSeeds);
        }
        mp_oPredatorGrid->SetValueOfCell(iX, iY, m_iNumPredsCode, fNumPredators);
      }
    }

    if (bOutput)
    {
      //Write out all output
      for (i = 0; i < m_iNumWeeksToModel + 1; i++)
      {
        oOut << "\n" << i << "\t" << p_fOverallSeeds[i] << "\t" << p_fOverallPredators[i];
      }
      oOut.close();
    }
    delete[] p_fSeedProportions;
    delete[] p_fOverallSeeds;
    delete[] p_fOverallPredators;

  }
  catch (modelErr& err)
  {
    throw(err);
  }
  catch (modelMsg & msg)
  {
    throw(msg);
  } //non-fatal error
  catch (...)
  {
    modelErr stcErr;
    stcErr.iErrorCode = UNKNOWN;
    strcpy(stcErr.cFunction, "clFuncResponseSeedPredation::Action");
    throw(stcErr);
  }
} */
