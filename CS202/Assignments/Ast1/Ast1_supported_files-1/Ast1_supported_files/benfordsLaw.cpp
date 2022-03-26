/*
Name: Marcos Villanueva, 5006480097, CS 202 - 1002, ASSIGNMENT_1
Description: This program helps visualize benfords Law. The program
takes in a file name as a command line argument and opens the file and
reads all the numbers inside the file. After, it calculates how often the
first digit in each number appeared and displays it in the form of stars.
The program writes all of the results to a file, that is named after 
the input file.
Input: This program takes in a filename as a command line argument, if 
there isn't exactly two arguments then the program terminates with an
error message. If an invalid file name is given the program prompts the 
user for another file name.
Output: The program writes to a result file with information on how many 
data points it used, and it shows the frequency of each digit with stars.
*/

#include <iostream>
#include <iomanip>
#include <math.h>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
using namespace std;

/**
 * @brief findFirstDigit : Calculate the first digit of the given number
 * @param number
 */
int findFirstDigit(int number){
	if(number==0){
		return 0;
	}
	//finding amount of digits
	int digits = static_cast<int> (log10(number));
	//getting the first digit
	number = static_cast<int> (number / pow(10, digits));
	// return first digit
	return number;                   
}

/**
 * @brief findHundreds : Read the value from the second parameter and 
 * calculate the number of 100's of a given value
 *&param value- value passed from main() like the total count of 0's 
 * in the given input file
 * &param ofstream &resultFile- print the number of asterisks(stars)
 * based on the calculated value and also return value to the output file
 */
int findHundreds(ofstream &resultFile, double value){
	//number of hundreds
	int starNum;
	if(value < 100){
		starNum = 0;
	}
	else{
		starNum = round(value / 100);
	}
	
	//if value is 0
	if(!starNum){
		resultFile << "|-";
		return 0;
	}

	//writing to file
	resultFile << '|' << setw(starNum+1) << setfill('*') << '-';
	//return hundreds value; if value=220; then it should return 22
	return starNum; 
}

//personal function prototype
/*function to read data from file, count amount of numbers, and store
occurence of digits in array*/
void readData(ifstream &iFile, int &dataPoints, int digitCount[]);

int main(int argc, char *argv[]){
	//constants for amount of digits since there are only 10
	const int NUM_OF_DIGITS = 10;
	//size of input has to be 2
	const int VALID_INPUT_SIZE = 2;

	/*displaying error message if there aren't exactly 2 
	command line arguments*/
	if(argc != VALID_INPUT_SIZE){
		cout << "Usage: ./benFordsLaw <base filename>.txt" << endl;
		//terminating program
		return 0;
	}

	//creating a ifstream object to read and open the file given by user
	ifstream iFile;
	//string to store file name given by user
	string filename = argv[1];

	do
	{
		//opening the file given by  user
		iFile.open(filename);
		//if the file is invalid
		if(!iFile.is_open()){
			//displaying error message and prompting for another filename
			cout << "Error: You entered " << filename 
			<< " \nplease re-enter valid filename:\n";

			//take in filename
			cin >> filename;
		}
	//looping until valid file is given
	} while (!iFile.is_open());
	
	//creating ofstream object to write to result file
	ofstream oFile;

	//removing .txt from filename and making new result file name
	string resultFile;
	for(int i=0; i<static_cast<int>(filename.length()); i++){
		if(filename[i] == '.'){
			break;
		}
		resultFile += filename[i];
	}
	resultFile += "_results.txt";

	//creating result file
	oFile.open(resultFile);

	//writing header of result file
	oFile << "CS 202 - Assignment #1\n" <<"Benford's Law Program\n" <<
	"File Name: " << filename << endl << endl << '-' << setw(32) <<
	setfill('-') << '-' << endl;
	

	//storing the amount of occurunce for each digit initialized to zero
	int digitCount[NUM_OF_DIGITS] = {0};
	//variable for storing number of data
	int dataPoints = 0;

	//reading data from file
	readData(iFile, dataPoints, digitCount);

	//result banner
	oFile << "Benford's Law - Test Results: " << endl <<
	"Total Data Points: " << dataPoints << endl <<
	"First Digit:\n\n";

	//iterating over digitCount array to write information to result file
	for(int i=0; i<NUM_OF_DIGITS; i++){
		oFile << i << setw(8) << setfill(' ') << digitCount[i] <<
		findHundreds(oFile, digitCount[i]) << endl;
	}

	oFile << '-' << setw(32) << setfill('-') << '-' << endl;

	//closing files
	iFile.close();
	oFile.close();
	return 0;
}

//personal function definition
void readData(ifstream &iFile, int &dataPoints, int digitCount[]){
	const int INVALID_LINES = 5;
	string garbageData;
	int tempNum, firstDigit;

	//skipping the first 5 lines of header in the text files
	for(int i=0; i<INVALID_LINES; i++){
		getline(iFile, garbageData);
	}

	while(iFile >> garbageData >> garbageData >> tempNum){
		dataPoints++;
		//getting the first digit of the number
		firstDigit = findFirstDigit(tempNum);
		digitCount[firstDigit]++;
	}
}
