#include <fstream>
#include <math.h>

#ifdef linux
#define TESTPATH "/home/lora/SORTIE/Core_Model_Tester/"
#else
#define TESTPATH "c:\\Code\\Core_Model_Tester\\"
#endif

//This is for harvest interface testing.  It just writes a tree file with
//no checking of input.
//Arguments: 1 = write fake harvest file likely to produce an "unrecognized
//tree" error; 2 = write empty harvest file, plus update file likely to produce
//an "unrecognized tree" error
int main ( int argc, char * argv[] ) {
  using namespace std;

  //Write a fake list of harvested trees
  char cPath[500];
  sprintf(cPath, "%s%s", TESTPATH, "cutfile.txt");
  ofstream outfile (cPath);

  //Fake header
  outfile << 1 << "\t" << 3 << "\n";
  outfile << "X\tY\tSpecies\tType\tDiam\tHeight\n";

  if (strcmp(argv[1], "2") == 0) {
    outfile.close();
  } else {

    outfile << 74.4779 << "\t" << 2.86341 << "\t" << 1 << "\t" << 3 << "\t"
            << 26.2185 << "\t" << 10 << endl;

    outfile << 36.3822 << "\t" << 2.95831 << "\t" << 2 << "\t" << 3 << "\t"
            << 21.2419 << "\t" << 10 << endl;

    outfile << 72.0387 << "\t" << 13.9719 << "\t" << 1 << "\t" << 3 << "\t"
            << 12.3629 << "\t" << 10 << endl;

    outfile << 28.4697 << "\t" << 22.4661 << "\t" << 0 << "\t" << 1 << "\t"
            << 1.14 << "\t" << 10 << endl;

    outfile << 74.1404 << "\t" << 39.8158 << "\t" << 2 << "\t" << 3 << "\t"
            << 24.7286 << "\t" << 10 << endl;

    outfile << 90.0865 << "\t" << 40.4886 << "\t" << 1 << "\t" << 3 << "\t"
            << 28.1205 << "\t" << 10 << endl;

    outfile << 94.9792 << "\t" << 40.9522 << "\t" << 2 << "\t" << 3 << "\t"
            << 24.5678 << "\t" << 10 << endl;

    outfile << 36.0762 << "\t" << 42.6468 << "\t" << 2 << "\t" << 3 << "\t"
            << 20.4855 << "\t" << 10 << endl;

    outfile << 9.38922 << "\t" << 59.3884 << "\t" << 2 << "\t" << 3 << "\t"
            << 19.1746 << "\t" << 10 << endl;

    outfile << 91.4707 << "\t" << 86.3797 << "\t" << 2 << "\t" << 2 << "\t"
            << 8.31 << "\t" << 10 << endl;

    outfile << 36.6376 << "\t" << 87.5301 << "\t" << 2 << "\t" << 2 << "\t"
            << 6.8901 << "\t" << 10 << endl;

    outfile.close();
  }

  //Write an update file
  sprintf(cPath, "%s%s", TESTPATH, "Update File 3.txt");
  ofstream update ( cPath );
  update << 2 << "\t" << 6 << "\n";
  update << "X\tY\tSpecies\tType\tDiam\tHeight\ttest 2\tTree Age\ttest 1\tdead\ttest 3" << endl;

  //Tree 6
  update << 27.794 << "\t" << 8.64942 << "\t" //X, Y
         << 1 << "\t" << 3 << "\t" //Species, type
         << 28.5256 << "\t" << 10 << "\t" //diam, height
         << 0.54 << "\t" //test 2
         << 0 << "\t"  //tree age
         << 0.491 << "\t" //test 1
         << true << "\t" //dead
         << 0.483 << endl; //test 3

  //Tree 10
  update << 18.4304 << "\t" << 15.3092 << "\t" //X, Y
         << 0 << "\t" << 3 << "\t" //Species, type
         << 13.8248 << "\t" << 10 << "\t" //diam, height
         << 0.36 << "\t" //test 2
         << 100 << "\t"  //tree age
         << 0.373 << "\t" //test 1
         << false << "\t" //dead
         << 0.44 << endl; //test 3

  //Tree 28
  update << 84.6036 << "\t" << 50.93 << "\t" //X, Y
         << 1 << "\t" << 3 << "\t" //Species, type
         << 21.3454 << "\t" << 10 << "\t" //diam, height
         << 23 << "\t" //test 2
         << -10 << "\t"  //tree age
         << 23 << "\t" //test 1
         << false << "\t" //dead
         << 23 << endl; //test 3

  //Tree 34
  update << 9.38922 << "\t" << 59.3884 << "\t" //X, Y
         << 2 << "\t" << 3 << "\t" //Species, type
         << 19.1746 << "\t" << 10 << "\t" //diam, height
         << 23.81 << "\t" //test 2
         << -10 << "\t"  //tree age
         << 33.352 << "\t" //test 1
         << false << "\t" //dead
         << 19.76 << endl; //test 3

  update << 6.33182 << "\t" << 75.0587 << "\t" //X, Y
         << 2 << "\t" << 2 << "\t" //Species, type
         << 4.24863 << "\t" << 10 << "\t" //diam, height
         << 0 << "\t" //test 2
         << -10 << "\t"  //tree age
         << -0.23 << "\t" //test 1
         << false << "\t" //dead
         << 15.66 << endl; //test 3

  //Tree 50
  update << 36.6376 << "\t" << 87.5301 << "\t" //X, Y
         << 2 << "\t" << 2 << "\t" //Species, type
         << 6.8901 << "\t" << 10 << "\t" //diam, height
         << 0.075 << "\t" //test 2
         << -10 << "\t"  //tree age
         << 0.011 << "\t" //test 1
         << false << "\t" //dead
         << 0.086 << endl; //test 3

    update.close();

  return 0;
}
