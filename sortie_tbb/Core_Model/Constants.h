#ifndef ConstantsH
#define ConstantsH
//---------------------------------------------------------------------------
/**
* @file Constants.h
Constant declarations

Copyright 2003 Charles D. Canham.
@author Lora E. Murphy

<br>Edit history:
<br>-----------------
<br>April 28, 2004 - Submitted as beta (LEM)
<br>January 26, 2005 - Changed rundata file to detailed output file
*/

const int MAX_FILENAME_SIZE = 1000; /**<Max length of filename strings*/
const int MAX_COMMAND_LENGTH = 25; /**<Max length of behavior registered command
                                   strings*/
const int MAX_VERSION_SIZE = 4;  /**<Max length of version number string*/
const int MAX_GRID_LABEL_SIZE = 50;  /**<Max size of the grid value labels*/
const int MAX_GRID_CHAR_VALUE_SIZE = 25; /**<Max size of the grid char values*/
const char DETAILED_OUTPUT_FILE_EXT[] = ".xml"; /**<File extension for detailed output files*/
const char ZIPPED_FILE_EXT[] = ".xml.gz";/**<Zipped file extension*/
const char GZIP_EXT[] = ".gz"; /**<GZIP file extension*/
const char TARBALL_FILE_EXT[] = ".gz.tar"; /**<Zipped, tarred file extension -
                keep this lowercase always!*/
const char SHORT_OUTPUT_FILE_EXT[] = ".out";/**<File extension for short output files*/
const char TEXT_FILE_EXT[] = ".txt";/**<File extension for text files*/
const int DETAILED_OUTPUT_FILE_VERSION = 1; /**<File version for detailed output files*/
const int MAX_TREE_LABEL_SIZE = 50; /**<Max size of tree data member label strings*/
const int MAX_TREE_CHAR_VALUE_SIZE = 25; /**<Max size of tree char data member
                                         value strings*/
const int MAX_SPECIES_NAME_SIZE = 50; /**<Max size of tree species name strings*/
const int MAX_NAMESTRING_SIZE = 100; /**<Max length of object namestrings*/
const int MAX_PLOTTITLE_SIZE = 80; /**<Max length of plot title string*/
const float QUADRAT_CELL_SIZE = 2; /**<Grid cell resolution for quadrat light*/
const float CONVERT_TO_DEGREES = 57.29578; /**<Multiply radian values by this to get degrees*/
const float CONVERT_TO_RADIANS = 0.0174533;/**<Multiply degree values by this to get radians*/
const int M_SQ_PER_HA = 10000; /**<Number of square meters in a hectare*/
const float VERY_SMALL_VALUE = 1e-5; /**<Small value - arbitrarily chosen - this
                                     is the smallest value that I can get to
                                     always have an effect on float precision*/
const float CONVERT_IN_TO_CM = 2.54; /**<Multiply a value in inches by this to transform to cm*/
const float CONVERT_CM_TO_IN = 0.394; /**<Multiply a value in cm by this to transform to inches*/
const float CONVERT_LBS_TO_KG = 0.454; /**<Multiply a value in pounds by this to transform to kg*/
const float CONVERT_KG_TO_LB = 2.20462262; /**<Multiply a value in kg by this to transform to lb*/
const float CONVERT_KG_TO_MG = 0.001; /**<Multiply a value in kg by this to transform to metric tons (Mg)*/
const float CONVERT_G_TO_KG = 0.001; /**<Multiply a value in g by this to transform to kg*/
const float CONVERT_MM_TO_CM = 0.1; /**<Multiply a value in mm by this to transform to cm*/
const float CONVERT_CM_TO_MM = 10.0; /**<Multiply a value in cm by this to transform to mm*/
const float CONVERT_MG_TO_KG = 1000; /**<Multiply a value in Mg by this to transform to kg*/
const int MAX_SUBPLOT_NAME_SIZE = 100; /**<Size of subplot names*/

//---------------------------------------------------------------------------
#endif
