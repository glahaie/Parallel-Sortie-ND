#include <fstream>
#include <math.h>

#ifdef linux
#define TESTPATH "/home/lora/Documents/"
#else
#define TESTPATH "c:\\documents and settings\\lora\\my documents\\"
#endif

//Fake tester for run 3 of the harvest interface test.
int main () {
  using namespace std;
  
  char cFile[100];
       
  sprintf(cFile, "%s%s", TESTPATH, "Test 3 SORTIE Input.txt");
  ifstream infile( cFile );
  int iTs;
  
  //Which timestep are we on?
  infile >> iTs;
  
  
  
  //**********************************************
  // Timestep 2
  //**********************************************
  if (2 == iTs) {
    
    //Check the header
    char cTemp[100];
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
    //infile >> sHeaderColumn;
    //These names have spaces - so have to get them a different way
    infile.get();
    infile.get(cTemp, 100, '\t');
    if (0 != strcmp(cTemp, "test 2")) {
      //Divide by zero to throw an error
      int iTemp = (7 - 6) - 1;
      int iTemp2 = 2 / iTemp; 
    }
    infile.get();
    infile.get(cTemp, 100, '\t');
    if (0 != strcmp(cTemp, "Tree Age")) {
      //Divide by zero to throw an error
      int iTemp = (7 - 6) - 1;
      int iTemp2 = 2 / iTemp; 
    }
    infile.get();
    infile.get(cTemp, 100, '\t');
    if (0 != strcmp(cTemp, "test 1")) {
      //Divide by zero to throw an error
      int iTemp = (7 - 6) - 1;
      int iTemp2 = 2 / iTemp; 
    }
    infile.get();
    infile.get(cTemp, 100, '\t');
    if (0 != strcmp(cTemp, "dead")) {
      //Divide by zero to throw an error
      int iTemp = (7 - 6) - 1;
      int iTemp2 = 2 / iTemp; 
    }
    infile.get();
    infile.get(cTemp, 100, '\n');
    if (0 != strcmp(cTemp, "test 3")) {
      //Divide by zero to throw an error
      int iTemp = (7 - 6) - 1;
      int iTemp2 = 2 / iTemp; 
    }
    infile.get();
    
    //Verify the first line (should be tree # 40)
    float fVal;
    int iVal;
    bool bVal;
    
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
    //test 2 - initial value is 0
    infile >> fVal;
    if (fabs(fVal - 0) > 0.001) {
      //Divide by zero to throw an error
      int iTemp = (7 - 6) - 1;
      int iTemp2 = 2 / iTemp; 
    }
    //Tree Age 
    infile >> iVal;
    if (iVal != 2) {
      //Divide by zero to throw an error
      int iTemp = (7 - 6) - 1;
      int iTemp2 = 2 / iTemp; 
    }
    //test 1 - initial value of 0
    infile >> fVal;
    if (fabs(fVal - 0) > 0.001) {
      //Divide by zero to throw an error
      int iTemp = (7 - 6) - 1;
      int iTemp2 = 2 / iTemp; 
    }
    //dead - initial value of false
    infile >> bVal;
    if (bVal != false) {
      //Divide by zero to throw an error
      int iTemp = (7 - 6) - 1;
      int iTemp2 = 2 / iTemp; 
    }
    //test 3 - initial value of 0
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
  
    //Write a harvest file - no trees
    sprintf(cFile, "%s%s", TESTPATH, "Cut File 3.txt");
    ofstream harvest ( cFile );
    harvest << 2 << "\t" << 6 << "\n";
    harvest << "X\tY\tSpecies\tType\tDiam\tHeight\ttest 2\tTree Age\ttest 1\tdead\ttest 3" << endl;
    harvest.close();
    
    //Write an update file - and outrageously try to update some things
    //we have no right to update
    sprintf(cFile, "%s%s", TESTPATH, "Update File 3.txt");
    ofstream update ( cFile );
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
  
  
  
  
  //**********************************************
  // Timestep 4
  //**********************************************
  } else if (4 == iTs) {
    
    //Check the header
    char cTemp[100];
    
    infile.getline(cTemp,100); //eliminate the rest of the first line
    infile.getline(cTemp,100); //eliminate the header - we already tested it
    
    //Verify the first line (should be tree # 40)
    float fVal;
    int iVal;
    bool bVal;
    
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
    //test 2
    infile >> fVal;
    if (fabs(fVal - 0) > 0.001) {
      //Divide by zero to throw an error
      int iTemp = (7 - 6) - 1;
      int iTemp2 = 2 / iTemp; 
    }
    //Tree Age
    infile >> iVal;
    if (iVal != 6) {
      //Divide by zero to throw an error
      int iTemp = (7 - 6) - 1;
      int iTemp2 = 2 / iTemp; 
    }
    //test 1 - initial value
    infile >> fVal;
    if (fabs(fVal - -0.23) > 0.001) {
      //Divide by zero to throw an error
      int iTemp = (7 - 6) - 1;
      int iTemp2 = 2 / iTemp; 
    }
    //dead
    infile >> bVal;
    if (bVal != false) {
      //Divide by zero to throw an error
      int iTemp = (7 - 6) - 1;
      int iTemp2 = 2 / iTemp; 
    }
    //test 3
    infile >> fVal;
    if (fabs(fVal - 15.66) > 0.001) {
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
  
    //Write a harvest file 
    sprintf(cFile, "%s%s", TESTPATH, "Cut File 3.txt");
    ofstream harvest ( cFile );
    harvest << 2 << "\t" << 6 << "\n";
    harvest << "X\tY\tSpecies\tType\tDiam\tHeight\ttest 2\tTree Age\ttest 1\tdead\ttest 3" << endl;
    //Tree 2
    harvest << 74.4779 << "\t" << 2.86341 << "\t" //X, Y 
            << 1 << "\t" << 3 << "\t" //Species, type
            << 26.2185 << "\t" << 10 << "\t" //diam, height
            << 0 << "\t" //test 2 
            << 0 << "\t"  //tree age
            << 0 << "\t" //test 1
            << true << "\t" //dead
            << 0 << endl; //test 3
     
    harvest.close();
    
    //Write an update file - no trees
    sprintf(cFile, "%s%s", TESTPATH, "Update File 3.txt");
    ofstream update ( cFile );
    update << 2 << "\t" << 6 << "\n";
    update << "X\tY\tSpecies\tType\tDiam\tHeight\ttest 2\tTree Age\ttest 1\tdead\ttest 3" << endl;      
    update.close();
    
    
    
    
  //**********************************************
  // Timestep 6
  //**********************************************  
  } else if (6 == iTs) {
    
    //Check the header
    char cTemp[100];
        
    infile.getline(cTemp,100); //eliminate the rest of the first line
    infile.getline(cTemp,100); //eliminate the header - we already tested it
    
    //Count the lines of the input file and make sure there are 54 trees
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
  
    //Write a harvest file
    sprintf(cFile, "%s%s", TESTPATH, "Cut File 3.txt");
    ofstream harvest ( cFile );
    harvest << 6 << "\t" << 6 << "\n";
    harvest << "X\tY\tSpecies\tType\tDiam\tHeight\ttest 2\tTree Age\ttest 1\tdead\ttest 3" << endl;
    
    //Tree 1
    harvest << 42.0525 << "\t" << 2.21632 << "\t" //X, Y 
            << 1 << "\t" << 3 << "\t" //Species, type
            << 20.5095 << "\t" << 10 << "\t" //diam, height
            << 0 << "\t" << 0 << "\t" << 0 << "\t" << false << "\t" << 0 << endl;
           
    //Tree 3
    harvest << 36.3822 << "\t" << 2.95831 << "\t" //X, Y 
            << 2 << "\t" << 3 << "\t" //Species, type
            << 21.2419 << "\t" << 10 << "\t" //diam, height
            << 0 << "\t" << 0 << "\t" << 0 << "\t" << false << "\t" << 0 << endl;       
           
    //Tree 9
    harvest << 72.0387 << "\t" << 13.9719 << "\t" //X, Y 
            << 1 << "\t" << 3 << "\t" //Species, type
            << 12.3629 << "\t" << 10 << "\t" //diam, height
            << 0 << "\t" << 0 << "\t" << 0 << "\t" << false << "\t" << 0 << endl;
           
    //Tree 15
    harvest << 28.4697 << "\t" << 22.4661 << "\t" //X, Y 
            << 0 << "\t" << 1 << "\t" //Species, type
            << 1.14 << "\t" << 10 << "\t" //diam, height
            << 0 << "\t" << 0 << "\t" << 0 << "\t" << false << "\t" << 0 << endl;
           
    //Tree 19
    harvest << 74.1404 << "\t" << 39.8158 << "\t" //X, Y 
            << 2 << "\t" << 3 << "\t" //Species, type
            << 24.7286 << "\t" << 10 << "\t" //diam, height
            << 0 << "\t" << 0 << "\t" << 0 << "\t" << false << "\t" << 0 << endl;
           
    //Tree 20
    harvest << 90.0865 << "\t" << 40.4886 << "\t" //X, Y 
            << 1 << "\t" << 3 << "\t" //Species, type
            << 28.1205 << "\t" << 10 << "\t" //diam, height
            << 0 << "\t" << 0 << "\t" << 0 << "\t" << false << "\t" << 0 << endl;
           
    //Tree 28
    harvest << 84.6036 << "\t" << 50.93 << "\t" //X, Y 
            << 1 << "\t" << 3 << "\t" //Species, type
            << 21.3454 << "\t" << 10 << "\t" //diam, height
            << 0 << "\t" << 0 << "\t" << 0 << "\t" << false << "\t" << 0 << endl;       
           
    harvest.close();
    
    //Write an update file
    sprintf(cFile, "%s%s", TESTPATH, "Update File 3.txt");
    ofstream update ( cFile );
    update << 6 << "\t" << 6 << "\n";
    update << "X\tY\tSpecies\tType\tDiam\tHeight\ttest 2\tTree Age\ttest 1\tdead\ttest 3" << endl;    
  
    //Tree 34
    update << 9.38922 << "\t" << 59.3884 << "\t" //X, Y 
           << 2 << "\t" << 3 << "\t" //Species, type
           << 19.1746 << "\t" << 10 << "\t" //diam, height
           << 0.033 << "\t" //test 2 
           << 0 << "\t"  //tree age
           << 1.239 << "\t" //test 1
           << false << "\t" //dead
           << 2.447 << endl; //test 3                   
           
    //Tree 35
    update << 27.1944 << "\t" << 63.1713 << "\t" //X, Y 
           << 2 << "\t" << 3 << "\t" //Species, type
           << 26.0429 << "\t" << 10 << "\t" //diam, height
           << 16.391 << "\t" //test 2 
           << 100 << "\t"  //tree age
           << 46.485 << "\t" //test 1
           << false << "\t" //dead
           << -0.369 << endl; //test 3
           
    //Tree 36
    update << 61.7164 << "\t" << 66.0961 << "\t" //X, Y 
           << 0 << "\t" << 3 << "\t" //Species, type
           << 17.1742 << "\t" << 10 << "\t" //diam, height
           << 0 << "\t" //test 2 
           << -10 << "\t"  //tree age
           << 0 << "\t" //test 1
           << false << "\t" //dead
           << 0.657 << endl; //test 3
           
    //Tree 47
    update << 38.6781 << "\t" << 84.8195 << "\t" //X, Y 
           << 2 << "\t" << 3 << "\t" //Species, type
           << 25.1718 << "\t" << 10 << "\t" //diam, height
           << 0.0084 << "\t" //test 2 
           << -10 << "\t"  //tree age
           << 10 << "\t" //test 1
           << false << "\t" //dead
           << -0.254 << endl; //test 3
           
    //Tree 49
    update << 37.5938 << "\t" << 87.2484 << "\t" //X, Y 
           << 2 << "\t" << 3 << "\t" //Species, type
           << 15.9924 << "\t" << 10 << "\t" //diam, height
           << 0.01 << "\t" //test 2 
           << -10 << "\t"  //tree age
           << 0 << "\t" //test 1
           << false << "\t" //dead
           << 0.828 << endl; //test 3
           
    //Tree 50
    update << 36.6376 << "\t" << 87.5301 << "\t" //X, Y 
           << 2 << "\t" << 2 << "\t" //Species, type
           << 6.8901 << "\t" << 10 << "\t" //diam, height
           << 0 << "\t" //test 2 
           << -10 << "\t"  //tree age
           << 2.883 << "\t" //test 1
           << false << "\t" //dead
           << -3.976 << endl; //test 3
           
    //Tree 52
    update << 97.7476 << "\t" << 94.7417 << "\t" //X, Y 
           << 2 << "\t" << 3 << "\t" //Species, type
           << 25.3651 << "\t" << 10 << "\t" //diam, height
           << 10 << "\t" //test 2 
           << -10 << "\t"  //tree age
           << 0.109 << "\t" //test 1
           << false << "\t" //dead
           << 2.132 << endl; //test 3
          
    update.close(); 
  } else {
    //Purposefully crash 
    int iTemp = (7 - 6) - 1;
    int iTemp2 = 2 / iTemp;
  }
               
  return 0;
}
