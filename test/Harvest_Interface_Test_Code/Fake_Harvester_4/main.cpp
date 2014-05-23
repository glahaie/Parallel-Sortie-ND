#include <fstream>
#include <math.h>

#ifdef linux
#define TESTPATH "/home/lora/SORTIE/Core_Model_Tester/"
#else
#define TESTPATH "c:\\Code\\Core_Model_Tester\\"
#endif

//This file, for its return harvest file, simply makes a copy of the harvest
//file.
int main () {
  using namespace std;
  char cPath[500];

  ifstream infile( "test4harvest.txt" );
  int iTs;

  //Which timestep are we on?
  infile >> iTs;
  infile.close();

  if (3 == iTs) {

    //Re-write the file
    char cTemp[100];

    ifstream infile2( "test4harvest.txt" );
    sprintf(cPath, "%s%s", TESTPATH, "cutfile4.txt");
    ofstream outfile (cPath);

    while (!infile2.eof()) {
      infile2.getline(cTemp,100);
      outfile << cTemp << endl;
    }

    infile2.close();
    outfile.close();

  } else {
    //Purposefully crash
    int iTemp = (7 - 6) - 1;
    int iTemp2 = 2 / iTemp;
  }

  return 0;
}
