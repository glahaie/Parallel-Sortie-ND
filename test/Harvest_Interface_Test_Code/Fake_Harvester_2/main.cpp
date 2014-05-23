#include <fstream>
#include <math.h>
#include <iostream>

#ifdef linux
#define TESTPATH "/home/lora/SORTIE/Core_Model_Tester/"
#else
#define TESTPATH "c:\\Code\\Core_Model_Tester\\"
#endif

//Fake tester for run 2 of the harvest interface test.
int main ( int argc, char * argv[] ) {
  using namespace std;

  char cPath[500];

  if (3 != argc) {
    //Divide by zero to throw an error
    int iTemp = (7 - 6) - 1;
    int iTemp2 = 2 / iTemp;
  }
  if (strcmp(argv[1], "Some") != 0) {
    //Divide by zero to throw an error
    int iTemp = (7 - 6) - 1;
    int iTemp2 = 2 / iTemp;
  }
  if (strcmp(argv[2], "arguments!") != 0) {
    //Divide by zero to throw an error
    int iTemp = (7 - 6) - 1;
    int iTemp2 = 2 / iTemp;
  }

  ifstream infile( "Test 2 Harvest.txt" );
  int iTs;

  //Which timestep are we on?
  infile >> iTs;

  if (1 == iTs) {

    //Check the header
    char cTemp[100], cTest;
    std::string sHeaderColumn;

    infile.getline(cTemp,100); //eliminate the rest of the first line
    infile >> sHeaderColumn;
    if (sHeaderColumn != "X") {
      //Divide by zero to throw an error
      int iTemp = (7 - 6) - 1;
      int iTemp2 = 2 / iTemp;
    }
    infile >> sHeaderColumn;
    if (sHeaderColumn != "Y") {
      //Divide by zero to throw an error
      int iTemp = (7 - 6) - 1;
      int iTemp2 = 2 / iTemp;
    }
    infile >> sHeaderColumn;
    if (sHeaderColumn != "Species") {
      //Divide by zero to throw an error
      int iTemp = (7 - 6) - 1;
      int iTemp2 = 2 / iTemp;
    }
    infile >> sHeaderColumn;
    if (sHeaderColumn != "Type") {
      //Divide by zero to throw an error
      int iTemp = (7 - 6) - 1;
      int iTemp2 = 2 / iTemp;
    }
    infile >> sHeaderColumn;
    if (sHeaderColumn != "Diam") {
      //Divide by zero to throw an error
      int iTemp = (7 - 6) - 1;
      int iTemp2 = 2 / iTemp;
    }
    infile >> sHeaderColumn;
    if (sHeaderColumn != "Height") {
      //Divide by zero to throw an error
      int iTemp = (7 - 6) - 1;
      int iTemp2 = 2 / iTemp;
    }
    infile >> sHeaderColumn;
    if (sHeaderColumn != "Growth") {
      //Divide by zero to throw an error
      int iTemp = (7 - 6) - 1;
      int iTemp2 = 2 / iTemp;
    }
    infile >> sHeaderColumn;
    if (sHeaderColumn != "Light") {
      //Divide by zero to throw an error
      int iTemp = (7 - 6) - 1;
      int iTemp2 = 2 / iTemp;
    }

    //Verify the first line (should be tree # 40)
    float fVal;
    int iVal;

    //X
    infile >> fVal;
    if (fabs(fVal - 6.33182) > 0.001) {
      //Divide by zero to throw an error
      int iTemp = (7 - 6) - 1;
      int iTemp2 = 2 / iTemp;
    }
    //Y
    infile >> fVal;
    if (fabs(fVal - 75.0587) > 0.001) {
      //Divide by zero to throw an error
      int iTemp = (7 - 6) - 1;
      int iTemp2 = 2 / iTemp;
    }
    //Species
    infile >> iVal;
    if (iVal != 2) {
      //Divide by zero to throw an error
      int iTemp = (7 - 6) - 1;
      int iTemp2 = 2 / iTemp;
    }
    //Type
    infile >> iVal;
    if (iVal != 2) {
      //Divide by zero to throw an error
      int iTemp = (7 - 6) - 1;
      int iTemp2 = 2 / iTemp;
    }
    //Diam
    infile >> fVal;
    if (fabs(fVal - 4.24863) > 0.001) {
      //Divide by zero to throw an error
      int iTemp = (7 - 6) - 1;
      int iTemp2 = 2 / iTemp;
    }
    //Height
    infile >> fVal;
    if (fabs(fVal - 8.07802073) > 0.001) {
      //Divide by zero to throw an error
      int iTemp = (7 - 6) - 1;
      int iTemp2 = 2 / iTemp;
    }
    //Growth - 0 in the first timestep
    infile >> fVal;
    if (fabs(fVal - 0) > 0.001) {
      //Divide by zero to throw an error
      int iTemp = (7 - 6) - 1;
      int iTemp2 = 2 / iTemp;
    }
    //Light - 0 in the first timestep
    infile >> fVal;
    if (fabs(fVal - 0) > 0.001) {
      //Divide by zero to throw an error
      int iTemp = (7 - 6) - 1;
      int iTemp2 = 2 / iTemp;
    }

    //Count the lines of the input file and make sure there are 54 more
    int iNumLines = 0;
    while (!infile.eof()) {
      infile.getline(cTemp,100);
      if (strlen(cTemp) > 1)
        iNumLines++;
    }

    if (54 != iNumLines) {
      //Divide by zero to throw an error
      int iTemp = (7 - 6) - 1;
      int iTemp2 = 2 / iTemp;
    }

    infile.close();

    //Write a fake list of harvested trees
    sprintf(cPath, "%s%s", TESTPATH, "Cut File 2.txt");
    ofstream outfile (cPath);

    //Fake header
    outfile << 1 << "\t" << 3 << "\n";
    outfile << "X\tY\tSpecies\tType\tDiam\tHeight\tGrowth\tLight\n";

    //Tree 2
    outfile << 74.4779 << "\t" << 2.86341 << "\t" << 1 << "\t" << 3 << "\t"
            << 26.2185 << "\t" << 10 << "\t" << 0 << "\t" << 0 << endl;

    //Tree 3
    outfile << 36.3822 << "\t" << 2.95831 << "\t" << 2 << "\t" << 3 << "\t"
            << 21.2419 << "\t" << 0 << "\t" << 0 << "\t" << 0 << endl;

    //Tree 9
    outfile << 72.0387 << "\t" << 13.9719 << "\t" << 1 << "\t" << 3 << "\t"
            << 12.3629 << "\t" << 0 << "\t" << 0 << "\t" << 0 << endl;

    //Tree 15
    outfile << 28.4697 << "\t" << 22.4661 << "\t" << 0 << "\t" << 1 << "\t"
            << 1.14 << "\t" << 0 << "\t" << 0 << "\t" << 0 << endl;

    //Tree 19
    outfile << 74.1404 << "\t" << 39.8158 << "\t" << 2 << "\t" << 3 << "\t"
            << 24.7286 << "\t" << 0 << "\t" << 0 << "\t" << 0 << endl;

    //Tree 20
    outfile << 90.0865 << "\t" << 40.4886 << "\t" << 1 << "\t" << 3 << "\t"
            << 28.1205 << "\t" << 0 << "\t" << 0 << "\t" << 0 << endl;

    //Tree 21
    outfile << 94.9792 << "\t" << 40.9522 << "\t" << 2 << "\t" << 3 << "\t"
            << 24.5678 << "\t" << 0 << "\t" << 0 << "\t" << 0 << endl;

    //Tree 22
    outfile << 36.0762 << "\t" << 42.6468 << "\t" << 2 << "\t" << 3 << "\t"
            << 20.4855 << "\t" << 0 << "\t" << 0 << "\t" << 0 << endl;

    //Tree 34
    outfile << 9.38922 << "\t" << 59.3884 << "\t" << 2 << "\t" << 3 << "\t"
            << 19.1746 << "\t" << 0 << "\t" << 0 << "\t" << 0 << endl;

    //Tree 48
    outfile << 91.4707 << "\t" << 86.3797 << "\t" << 2 << "\t" << 2 << "\t"
            << 8.31 << "\t" << 0 << "\t" << 0 << "\t" << 0 << endl;

    //Tree 50
    outfile << 36.6376 << "\t" << 87.5301 << "\t" << 2 << "\t" << 2 << "\t"
            << 6.8901 << "\t" << 0 << "\t" << 0 << "\t" << 0 << endl;

    outfile.close();

  } else if (2 == iTs) {

    //Check the header
    char cTemp[100], cTest;
    std::string sHeaderColumn;

    infile.getline(cTemp,100); //eliminate the rest of the first line
    infile >> sHeaderColumn;
    if (sHeaderColumn != "X") {
      //Divide by zero to throw an error
      int iTemp = (7 - 6) - 1;
      int iTemp2 = 2 / iTemp;
    }
    infile >> sHeaderColumn;
    if (sHeaderColumn != "Y") {
      //Divide by zero to throw an error
      int iTemp = (7 - 6) - 1;
      int iTemp2 = 2 / iTemp;
    }
    infile >> sHeaderColumn;
    if (sHeaderColumn != "Species") {
      //Divide by zero to throw an error
      int iTemp = (7 - 6) - 1;
      int iTemp2 = 2 / iTemp;
    }
    infile >> sHeaderColumn;
    if (sHeaderColumn != "Type") {
      //Divide by zero to throw an error
      int iTemp = (7 - 6) - 1;
      int iTemp2 = 2 / iTemp;
    }
    infile >> sHeaderColumn;
    if (sHeaderColumn != "Diam") {
      //Divide by zero to throw an error
      int iTemp = (7 - 6) - 1;
      int iTemp2 = 2 / iTemp;
    }
    infile >> sHeaderColumn;
    if (sHeaderColumn != "Height") {
      //Divide by zero to throw an error
      int iTemp = (7 - 6) - 1;
      int iTemp2 = 2 / iTemp;
    }
    infile >> sHeaderColumn;
    if (sHeaderColumn != "Growth") {
      //Divide by zero to throw an error
      int iTemp = (7 - 6) - 1;
      int iTemp2 = 2 / iTemp;
    }
    infile >> sHeaderColumn;
    if (sHeaderColumn != "Light") {
      //Divide by zero to throw an error
      int iTemp = (7 - 6) - 1;
      int iTemp2 = 2 / iTemp;
    }

    //Verify the first line (should be tree # 40)
    float fVal;
    int iVal;

    //X
    infile >> fVal;
    if (fabs(fVal - 6.33182) > 0.001) {
      //Divide by zero to throw an error
      int iTemp = (7 - 6) - 1;
      int iTemp2 = 2 / iTemp;
    }
    //Y
    infile >> fVal;
    if (fabs(fVal - 75.0587) > 0.001) {
      //Divide by zero to throw an error
      int iTemp = (7 - 6) - 1;
      int iTemp2 = 2 / iTemp;
    }
    //Species
    infile >> iVal;
    if (iVal != 2) {
      //Divide by zero to throw an error
      int iTemp = (7 - 6) - 1;
      int iTemp2 = 2 / iTemp;
    }
    //Type
    infile >> iVal;
    if (iVal != 2) {
      //Divide by zero to throw an error
      int iTemp = (7 - 6) - 1;
      int iTemp2 = 2 / iTemp;
    }
    //Diam
    infile >> fVal;
    if (fabs(fVal - 5.14863) > 0.001) {
      //Divide by zero to throw an error
      int iTemp = (7 - 6) - 1;
      int iTemp2 = 2 / iTemp;
    }
    //Height
    infile >> fVal;
    if (fabs(fVal - 9.28642) > 0.001) {
      //Divide by zero to throw an error
      int iTemp = (7 - 6) - 1;
      int iTemp2 = 2 / iTemp;
    }
    //Growth
    infile >> fVal;
    if (fabs(fVal - 6) > 0.001) {
      //Divide by zero to throw an error
      int iTemp = (7 - 6) - 1;
      int iTemp2 = 2 / iTemp;
    }
    //Light
    infile >> fVal;
    if (fabs(fVal - 100) > 0.001) {
      //Divide by zero to throw an error
      int iTemp = (7 - 6) - 1;
      int iTemp2 = 2 / iTemp;
    }

    //Count the lines of the input file and make sure there are 43 more
    int iNumLines = 0;
    while (!infile.eof()) {
      infile.getline(cTemp,100);
      if (strlen(cTemp) > 1)
        iNumLines++;
    }

    if (43 != iNumLines) {
      //Divide by zero to throw an error
      int iTemp = (7 - 6) - 1;
      int iTemp2 = 2 / iTemp;
    }

    infile.close();

    //Write a fake list of harvested trees - we're killing all the rest
    sprintf(cPath, "%s%s", TESTPATH, "Cut File 2.txt");
    ofstream outfile (cPath);

    //Fake header
    outfile << 2 << "\t" << 3 << "\n";
    outfile << "X\tY\tSpecies\tType\tDiam\tHeight\tGrowth\tLight\n";

    //Tree 1
    outfile << 42.0525 << "\t" << 2.21632 << "\t" << 1 << "\t" << 3 << "\t"
            << 20.5095 << "\t" << 10  << "\t"<< 0 << "\t" << 0 << "\t" << endl;

    //Tree 4
    outfile << 26.7469 << "\t" << 3.75704 << "\t" << 1 << "\t" << 3 << "\t"
            << 13.6089 << "\t" << 10 << "\t" << 0 << "\t" << 0 << "\t" << endl;

    //Tree 5
    outfile << 49.8263 << "\t" << 4.18441 << "\t" << 0 << "\t" << 2 << "\t"
            << 6.42101 << "\t" << 10 << "\t" << 0 << "\t" << 0 << "\t" << endl;

    //Tree 6
    outfile << 27.794 << "\t" << 8.64942 << "\t" << 1 << "\t" << 3 << "\t"
            << 28.5256 << "\t" << 10 << "\t" << 0 << "\t" << 0 << "\t" << endl;

    //Tree 7
    outfile << 78.0224 << "\t" << 12.6457 << "\t" << 1 << "\t" << 3 << "\t"
            << 26.3755 << "\t" << 10 << "\t" << 0 << "\t" << 0 << "\t" << endl;

    //Tree 8
    outfile << 88.2882 << "\t" << 13.1436 << "\t" << 0 << "\t" << 2 << "\t"
            << 3.8165 << "\t" << 10 << "\t" << 0 << "\t" << 0 << "\t" << endl;

    //Tree 10
    outfile << 18.4304 << "\t" << 15.3092 << "\t" << 0 << "\t" << 3 << "\t"
            << 13.8248 << "\t" << 10 << "\t" << 0 << "\t" << 0 << "\t" << endl;

    //Tree 11
    outfile << 39.366  << "\t" <<  19.9556 << "\t" <<  0 << "\t" <<  1 << "\t"
            <<  1.12  << "\t" <<  10  << "\t" <<  0 << "\t" <<  0 << endl;

    //Tree 12
    outfile << 86.5371 << "\t" <<  20.0087 << "\t" <<  1 << "\t" <<  1 << "\t"
            <<  1.14  << "\t" <<  10  << "\t" <<  0 << "\t" <<  0 << endl;

    //Tree 13
    outfile << 93.3186 << "\t" <<  20.998  << "\t" <<  2 << "\t" <<  1 << "\t"
            <<  1.2 << "\t" <<  10  << "\t" <<  0 << "\t" <<  0 << endl;

    //Tree 14
    outfile << 30.1811 << "\t" <<  21.9206 << "\t" <<  2 << "\t" <<  1 << "\t"
            <<  1.12  << "\t" <<  10  << "\t" <<  0 << "\t" <<  0 << endl;

    //Tree 16
    outfile << 55.9178 << "\t" <<  25.7332 << "\t" <<  1 << "\t" <<  3 << "\t"
            <<  17.3983 << "\t" <<  10  << "\t" <<  0 << "\t" <<  0 << endl;

    //Tree 17
    outfile << 20.4647 << "\t" <<  27.7396 << "\t" <<  2 << "\t" <<  3 << "\t"
            <<  24.272  << "\t" <<  10  << "\t" <<  0 << "\t" <<  0 << endl;

    //Tree 18
    outfile << 98.1614 << "\t" <<  29.6613 << "\t" <<  0 << "\t" <<  2 << "\t"
            <<  8.42262 << "\t" <<  10  << "\t" <<  0 << "\t" <<  0 << endl;

    //Tree 23
    outfile << 70.1652 << "\t" <<  43.3971 << "\t" <<  0 << "\t" <<  3 << "\t"
            <<  15.1196 << "\t" <<  10  << "\t" <<  0 << "\t" <<  0 << endl;

    //Tree 24
    outfile << 67.6349 << "\t" <<  47.9413 << "\t" <<  1 << "\t" <<  3 << "\t"
            <<  26.2077 << "\t" <<  10  << "\t" <<  0 << "\t" <<  0 << endl;

    //Tree 25
    outfile << 69.7277 << "\t" <<  48.6251 << "\t" <<  0 << "\t" <<  2 << "\t"
            <<  7.98507 << "\t" <<  10  << "\t" <<  0 << "\t" <<  0 << endl;

    //Tree 26
    outfile << 86.0179 << "\t" <<  49.4856 << "\t" <<  2 << "\t" <<  3 << "\t"
            <<  17.5575 << "\t" <<  10  << "\t" <<  0 << "\t" <<  0 << endl;

    //Tree 27
    outfile << 68.888  << "\t" <<  50.1366 << "\t" <<  2 << "\t" <<  3 << "\t"
            <<  24.708  << "\t" <<  10  << "\t" <<  0 << "\t" <<  0 << endl;

    //Tree 28
    outfile << 84.6036 << "\t" <<  50.93 << "\t" <<  1 << "\t" <<  3 << "\t"
            <<  21.3454 << "\t" <<  10  << "\t" <<  0 << "\t" <<  0 << endl;

    //Tree 29
    outfile << 25.7016 << "\t" <<  54.1108 << "\t" <<  2 << "\t" <<  3 << "\t"
            <<  20.7396 << "\t" <<  10  << "\t" <<  0 << "\t" <<  0 << endl;

    //Tree 30
    outfile << 21.2453 << "\t" <<  54.7161 << "\t" <<  2 << "\t" <<  3 << "\t"
            <<  12.1276 << "\t" <<  10  << "\t" <<  0 << "\t" <<  0 << endl;

    //Tree 31
    outfile << 14.3788 << "\t" <<  55.4155 << "\t" <<  0 << "\t" <<  2 << "\t"
            <<  5.12777 << "\t" <<  10  << "\t" <<  0 << "\t" <<  0 << endl;

    //Tree 32
    outfile << 60.6626 << "\t" <<  55.657  << "\t" <<  0 << "\t" <<  3 << "\t"
            <<  16.8162 << "\t" <<  10  << "\t" <<  0 << "\t" <<  0 << endl;

    //Tree 33
    outfile << 71.3062 << "\t" <<  56.5974 << "\t" <<  2 << "\t" <<  3 << "\t"
            <<  24.7457 << "\t" <<  10  << "\t" <<  0 << "\t" <<  0 << endl;

    //Tree 35
    outfile << 27.1944 << "\t" <<  63.1713 << "\t" <<  2 << "\t" <<  3 << "\t"
            <<  26.0429 << "\t" <<  10  << "\t" <<  0 << "\t" <<  0 << endl;

    //Tree 36
    outfile << 61.7164 << "\t" <<  66.0961 << "\t" <<  0 << "\t" <<  3 << "\t"
            <<  17.1742 << "\t" <<  10  << "\t" <<  0 << "\t" <<  0 << endl;

    //Tree 37
    outfile << 34.2957 << "\t" <<  67.5466 << "\t" <<  1 << "\t" <<  3 << "\t"
            <<  16.9941 << "\t" <<  10  << "\t" <<  0 << "\t" <<  0 << endl;

    //Tree 38
    outfile << 41.5812 << "\t" <<  71.8411 << "\t" <<  2 << "\t" <<  2 << "\t"
            << 8.04589 << "\t" <<  10  << "\t" <<  0 << "\t" <<  0 << endl;

    //Tree 39
    outfile << 28.2031 << "\t" <<  72.6295 << "\t" <<  1 << "\t" <<  3 << "\t"
            <<  23.4028 << "\t" <<  10  << "\t" <<  0 << "\t" <<  0 << endl;

    //Tree 40
    outfile << 6.33182 << "\t" <<  75.0587 << "\t" <<  2 << "\t" <<  2 << "\t"
            <<  5.14863 << "\t" <<  10  << "\t" <<  0 << "\t" <<  0 << endl;

    //Tree 41
    outfile << 63.196  << "\t" <<  77.6672 << "\t" <<  1 << "\t" <<  3 << "\t"
            <<  24.5384 << "\t" <<  10  << "\t" <<  0 << "\t" <<  0 << endl;

    //Tree 42
    outfile << 47.198  << "\t" <<  77.8982 << "\t" <<  1 << "\t" <<  3 << "\t"
            <<  24.5211 << "\t" <<  10  << "\t" <<  0 << "\t" <<  0 << endl;

    //Tree 43
    outfile << 1.12617 << "\t" <<  78.3586 << "\t" <<  2 << "\t" <<  3 << "\t"
            <<  25.6215 << "\t" <<  10  << "\t" <<  0 << "\t" <<  0 << endl;

    //Tree 44
    outfile << 74.3191 << "\t" <<  81.1496 << "\t" <<  1 << "\t" <<  3 << "\t"
            <<  27.4837 << "\t" <<  10  << "\t" <<  0 << "\t" <<  0 << endl;

    //Tree 45
    outfile << 23.3972 << "\t" <<  82.7297 << "\t" <<  1 << "\t" <<  3 << "\t"
            <<  24.9638 << "\t" <<  10  << "\t" <<  0 << "\t" <<  0 << endl;

    //Tree 46
    outfile << 15.6913 << "\t" <<  84.3219 << "\t" <<  2 << "\t" <<  3 << "\t"
            <<  24.791  << "\t" <<  10  << "\t" <<  0 << "\t" <<  0 << endl;

    //Tree 47
    outfile << 38.6781 << "\t" <<  84.8195 << "\t" <<  2 << "\t" <<  3 << "\t"
            <<  25.1718 << "\t" <<  10  << "\t" <<  0 << "\t" <<  0 << endl;

    //Tree 49
    outfile << 37.5938 << "\t" <<  87.2484 << "\t" <<  2 << "\t" <<  3 << "\t"
            <<  15.9924 << "\t" <<  10  << "\t" <<  0 << "\t" <<  0 << endl;

    //Tree 51
    outfile << 55.9163 << "\t" <<  90.0189 << "\t" <<  0 << "\t" <<  3 << "\t"
            <<  12.9417 << "\t" <<  10  << "\t" <<  0 << "\t" <<  0 << endl;

    //Tree 52
    outfile << 97.7476 << "\t" <<  94.7417 << "\t" <<  2 << "\t" <<  3 << "\t"
            <<  25.3651 << "\t" <<  10  << "\t" <<  0 << "\t" <<  0 << endl;

    //Tree 53
    outfile << 51.7177 << "\t" <<  95.4606 << "\t" <<  2 << "\t" <<  3 << "\t"
            <<  12.6799 << "\t" <<  10  << "\t" <<  0 << "\t" <<  0 << endl;

    //Tree 54
    outfile << 64.2286 << "\t" <<  98.6715 << "\t" <<  2 << "\t" <<  3 << "\t"
            <<  25.688  << "\t" <<  10  << "\t" <<  0 << "\t" <<  0 << endl;

    //Tree 55
    outfile << 96.6835 << "\t" <<  98.7591 << "\t" <<  0 << "\t" <<  3 << "\t"
            <<  17.3889 << "\t" <<  10  << "\t" <<  0 << "\t" <<  0 << endl;

    outfile.close();

  } else if (3 == iTs) {

    //Check the file - should have no trees
    char cTemp[100];
    int iNumLines = 0;
    while (!infile.eof()) {
      infile.getline(cTemp,100);
      if (strlen(cTemp) > 1)
        iNumLines++;
    }
    infile.close();

    //Write a fake list of harvested trees with no trees in
    sprintf(cPath, "%s%s", TESTPATH, "Cut File 2.txt");
    ofstream outfile (cPath);
    outfile << 3 << "\t" << 3 << "\n";
    outfile << "X\tY\tSpecies\tType\tDiam\tHeight\tGrowth\tLight\n";
    outfile.close();

    if (2 != iNumLines) {
      //Divide by zero to throw an error
      int iTemp = (7 - 6) - 1;
      int iTemp2 = 2 / iTemp;
    }
  } else {
    //Purposefully crash
    int iTemp = (7 - 6) - 1;
    int iTemp2 = 2 / iTemp;
  }

  return 0;
}
