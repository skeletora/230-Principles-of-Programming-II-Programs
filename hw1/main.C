//Rebecca Aloisio
//CSCI 230 002
//Homework Assignment #1

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

const string MASTER_FILE_NAME = "files.in";

void ProcessFile(string inputFileName);
void OpenMasterFile(ifstream & masterFile);
void ProcessIntegerFile(ifstream & dataFile);
void ProcessFloatFile(ifstream & dataFile);
void StatsReport(int count, float sum);

int main() {
    ifstream masterFile;
    string inputFileName;
    
    // open the  master list
    OpenMasterFile(masterFile);
    if (!masterFile) {
	//inputFileName has not been assigned a value at this point, so
	//  there would be an error should this if statement execute.
        cout << "Unable to open " << inputFileName << " exiting" << endl;
    } else {

        // prime the lcv, attempt to read a file name.
        masterFile >> inputFileName;

        // while there is data in the master file
        while(masterFile) {
            ProcessFile(inputFileName);
            masterFile >> inputFileName;
        }

        // close the master file.
        masterFile.close();
    }

    return 0;
}

void ProcessIntegerFile(ifstream & dataFile){
//Reads the width of the values and the values themselves from the 
//  file and outputs them to the screen.  It also adds the values 
//  to the sum and increments the count.
    int width;
    int input;
    int sum = 0;
    int count = 0;

    dataFile >> width;

    cout << "The data file contains the following input: " << endl;
    dataFile >> input;
    while (dataFile) {
        cout << " " << setw(width) << input;
	sum += input;
	count ++;
        dataFile >> input;
    } 

    cout << endl;

    StatsReport(count, sum);
    
    return;
}

void StatsReport(int count, float sum) {
//Outputs the final count, sum, and average of the data in the file.
//  It also checks that there was data in the file and displays a 
//  message if there wasn't.
    cout << fixed << setprecision(2);

    if (count > 0) {
        cout << "There were " << count << " input values." << endl;
	cout << "The sum is " << sum <<  "." << endl;
	cout << "The average is " << float(sum) /float(count) <<  "."  << endl;
    } else {
        cout << "There were no input values." << endl;
    }
}


void ProcessFloatFile(ifstream & dataFile){
//Reads data from the file and outputs it to the screen.  Also
//  reads the width and precision of the values from the file
//  and sets them for the output.  It then sends the sum and
//  count to another function to be processed.
    int width, precision;
    float input;
    float sum = 0;
    int count = 0;

    dataFile >> width >> precision;

    cout << fixed << setprecision(precision);

    cout << "The data file contains the following input: " << endl;
    dataFile >> input;
    while (dataFile) {
        cout << " " << setw(width) << input;
	sum += input;
	count ++;
        dataFile >> input;
    } 

    cout << endl;

    StatsReport(count, sum);

    return;
}

void ProcessFile(string inputFileName){
//Determines what type of data the specified file contains and then
// sends the data to be processed if it is a valid type.
     ifstream dataFile;
     string fileType;
     bool validFile = true;

     cout << endl;
     cout << "Processing " << inputFileName << endl;
     dataFile.open(inputFileName.c_str());
     if (! dataFile) {
         cout << "Unable to open " << inputFileName << endl;
	 validFile = false;
     }

     if (validFile) {
         dataFile >> fileType;

         if (fileType == "integer") {
             ProcessIntegerFile(dataFile);
         } else if (fileType == "real") {
             ProcessFloatFile(dataFile);
         } else {
             cout << "Unknown file type " << fileType << endl;
         }
     } 

     dataFile.close();

     return;
}

void OpenMasterFile(ifstream & masterFile){
//Opens the file specified in MASTER_FILE_NAME and checks to see if 
//  there was a file with the specified name.  If there isn't, a 
//  message is produced.
     masterFile.open(MASTER_FILE_NAME.c_str());

     if (not masterFile) {
         cout << "Error, could not open " << MASTER_FILE_NAME << endl;
     }

     return;
}
