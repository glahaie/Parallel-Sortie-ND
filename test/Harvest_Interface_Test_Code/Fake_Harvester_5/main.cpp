#include <fstream>
#include <math.h>

#ifdef linux
#define TESTPATH "/home/lora/SORTIE/Core_Model_Tester/"
#else
#define TESTPATH "c:\\Code\\Core_Model_Tester\\"
#endif

//Harvest executable for testing.  There should be one argument.  If the
//argument is "yes", this expects the presence of the file "parameters5.txt",
//which it will test for correctness.  It will then write a file whose name
//is based on the run number it finds in "parameters5.txt".  If the argument
//is "no", it will not look for "parameters5.txt", and instead will always
//write a file called "batch.txt".
int main (int argc, char * argv[]) {
  using namespace std;

  if (2 != argc) {
    //Purposefully crash
    int iTemp = (7 - 6) - 1;
    int iTemp2 = 2 / iTemp;
  }

  char cTemp[100];
  char cPath[500];

  if (argc > 1 && strcmp(argv[1], "yes") == 0) {
    sprintf(cPath, "%s%s", TESTPATH, "parameters5.txt");
    ifstream infile( cPath );
    //Make sure that there's only one line
    infile.getline(cTemp, 100);
    infile.getline(cTemp, 100);
    if (!infile.eof()) {
      //Purposefully crash
      int iTemp = (7 - 6) - 1;
      int iTemp2 = 2 / iTemp;
    }
    infile.close();

    ifstream infile2( cPath );
    float fFakeParam;
    int iRun, iFakeParam;

    infile2 >> iRun >> iFakeParam >> fFakeParam;
    infile2.close();

    if (1 == iRun) {

      if (30 != iFakeParam) {
        //Purposefully crash
        int iTemp = (7 - 6) - 1;
        int iTemp2 = 2 / iTemp;
      }

      if (fabs(32.676 - fFakeParam) > 0.01) {
        //Purposefully crash
        int iTemp = (7 - 6) - 1;
        int iTemp2 = 2 / iTemp;
      }

      sprintf(cPath, "%s%s", TESTPATH, "batch1.txt");
      ofstream outfile (cPath);
      outfile << "Saw the first run.";
      outfile.close();

    } else if (2 == iRun) {

      if (86 != iFakeParam) {
        //Purposefully crash
        int iTemp = (7 - 6) - 1;
        int iTemp2 = 2 / iTemp;
      }

      if (fabs(65.333 - fFakeParam) > 0.01) {
        //Purposefully crash
        int iTemp = (7 - 6) - 1;
        int iTemp2 = 2 / iTemp;
      }

      sprintf(cPath, "%s%s", TESTPATH, "batch2.txt");
      ofstream outfile (cPath);
      outfile << "Saw the first run.";
      outfile.close();

    } else if (3 == iRun) {

      if (0 != iFakeParam) {
        //Purposefully crash
        int iTemp = (7 - 6) - 1;
        int iTemp2 = 2 / iTemp;
      }

      if (fabs(-0.34 - fFakeParam) > 0.01) {
        //Purposefully crash
        int iTemp = (7 - 6) - 1;
        int iTemp2 = 2 / iTemp;
      }

      sprintf(cPath, "%s%s", TESTPATH, "batch3.txt");
      ofstream outfile (cPath);
      outfile << "Saw the first run.";
      outfile.close();

    } else {
      //Purposefully crash
      int iTemp = (7 - 6) - 1;
      int iTemp2 = 2 / iTemp;
    }
  } else if (argc > 1 && strcmp(argv[1], "no") == 0) {
    sprintf(cPath, "%s%s", TESTPATH, "batch.txt");
    ofstream outfile (cPath);
    outfile << "Saw the batch run.";
    outfile.close();
  } else {
    //Purposefully crash
    int iTemp = (7 - 6) - 1;
    int iTemp2 = 2 / iTemp;
  }

  //Copy the harvest file
  sprintf(cPath, "%s%s", TESTPATH, "test5harvest.txt");
  ifstream infile3( cPath );
  sprintf(cPath, "%s%s", TESTPATH, "cutfile5.txt");
  ofstream outfile2 ( cPath );

  while (!infile3.eof()) {
    infile3.getline(cTemp,100);
    outfile2 << cTemp << endl;
  }

  infile3.close();
  outfile2.close();

  return 0;
}
