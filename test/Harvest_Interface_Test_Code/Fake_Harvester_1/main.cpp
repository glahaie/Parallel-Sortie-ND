#include <fstream>
#include <math.h>

#ifdef linux
#define TESTPATH "/home/lora/SORTIE/Core_Model_Tester/"
#else
#define TESTPATH "c:\\Code\\Core_Model_Tester\\"
#endif

int main () {
  using namespace std;

  char cPath[500];

  ifstream infile( "test1harvest.txt" );
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
    //infile >> cTest;
    //if (cTest != '\n') {
      //Divide by zero to throw an error
    //  int iTemp = (7 - 6) - 1;
    //  int iTemp2 = 2 / iTemp;
    //}


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
    //infile >> cTest;
    //if (cTest != '\n') {
      //Divide by zero to throw an error
    //  int iTemp = (7 - 6) - 1;
    //  int iTemp2 = 2 / iTemp;
   // }

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

    //Write a fake list of harvested trees
    sprintf(cPath, "%s%s", TESTPATH, "cutfile.txt");
    ofstream outfile (cPath);

    //Fake header
    outfile << 1 << "\t" << 3 << "\n";
    outfile << "X\tY\tSpecies\tType\tDiam\tHeight\n";

    //Tree 2
    outfile << 74.4779 << "\t" << 2.86341 << "\t" << 1 << "\t" << 3 << "\t"
            << 26.2185 << "\t" << 10 << endl;

    //Tree 3
    outfile << 36.3822 << "\t" << 2.95831 << "\t" << 2 << "\t" << 3 << "\t"
            << 21.2419 << "\t" << 10 << endl;

    //Tree 9
    outfile << 72.0387 << "\t" << 13.9719 << "\t" << 1 << "\t" << 3 << "\t"
            << 12.3629 << "\t" << 10 << endl;

    //Tree 15
    outfile << 28.4697 << "\t" << 22.4661 << "\t" << 0 << "\t" << 1 << "\t"
            << 1.14 << "\t" << 10 << endl;

    //Tree 19
    outfile << 74.1404 << "\t" << 39.8158 << "\t" << 2 << "\t" << 3 << "\t"
            << 24.7286 << "\t" << 10 << endl;

    //Tree 20
    outfile << 90.0865 << "\t" << 40.4886 << "\t" << 1 << "\t" << 3 << "\t"
            << 28.1205 << "\t" << 10 << endl;

    //Tree 21
    outfile << 90.0865 << "\t" << 40.4886 << "\t" << 1 << "\t" << 3 << "\t"
            << 28.1206 << "\t" << 10 << endl;

    //Tree 22
    outfile << 36.0762 << "\t" << 42.6468 << "\t" << 2 << "\t" << 3 << "\t"
            << 20.4855 << "\t" << 10 << endl;

    //Tree 34
    outfile << 9.38922 << "\t" << 59.3884 << "\t" << 2 << "\t" << 3 << "\t"
            << 19.1746 << "\t" << 10 << endl;

    //Tree 48
    outfile << 91.4707 << "\t" << 86.3797 << "\t" << 2 << "\t" << 2 << "\t"
            << 8.31 << "\t" << 10 << endl;

    //Tree 50
    outfile << 36.6376 << "\t" << 87.5301 << "\t" << 2 << "\t" << 2 << "\t"
            << 6.8901 << "\t" << 10 << endl;

    outfile.close();

  } else if (2 == iTs) {

    //Count the lines of the input file and make sure there are 44 plus a
    //2-line header

    char cTemp[100];
    int iNumLines = 0;
    while (!infile.eof()) {
      infile.getline(cTemp,100);
      if (strlen(cTemp) > 1)
        iNumLines++;
    }

    if (46 != iNumLines) {
      //Divide by zero to throw an error
      int iTemp = (7 - 6) - 1;
      int iTemp2 = 2 / iTemp;
    }

    //Write a fake list of harvested trees
    sprintf(cPath, "%s%s", TESTPATH, "cutfile.txt");
    ofstream outfile (cPath);

    //Fake header
    outfile << 2 << "\t" << 3 << "\n";
    outfile << "X\tY\tSpecies\tType\tDiam\tHeight\n";

    //Tree 1
    outfile << 42.0525 << "\t" << 2.21632 << "\t" << 1 << "\t" << 3 << "\t"
            << 20.5095 << "\t" << 10 << endl;

    //Tree 4
    outfile << 26.7469 << "\t" << 3.75704 << "\t" << 1 << "\t" << 3 << "\t"
            << 13.6089 << "\t" << 10 << endl;

    //Tree 30
    outfile << 21.2453 << "\t" << 54.7161 << "\t" << 2 << "\t" << 3 << "\t"
            << 12.1276 << "\t" << 10 << endl;

    //Tree 31
    outfile << 14.3788 << "\t" << 55.4155 << "\t" << 0 << "\t" << 2 << "\t"
            << 5.12777 << "\t" << 10 << endl;

    outfile.close();

  } else {
    //Purposefully crash
    int iTemp = (7 - 6) - 1;
    int iTemp2 = 2 / iTemp;
  }

  return 0;
}
