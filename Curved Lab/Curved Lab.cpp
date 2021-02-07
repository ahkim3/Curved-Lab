/*
Name: Andrew Kim
Date: February 5, 2021
Program: Curved Lab

I hereby certify that this program represents my
work and that the design and logic was completed
without outside assistance.

Signature: Andrew Kim
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>
#include <iomanip>

using namespace std;

void fill(string, vector<string>&, vector<double>&);
double average(vector<double>);
double standardDev(vector<double>);
void computeLetterGrades(vector<double>, vector<char>&);


int main()
{
	vector<string> nameVec;
	vector<double> scoreVec;
	vector<char> gradeVec;
	string scoresFile;
	unsigned int maxNameLength = 0;

	// Asks user for name of score file
	cout << "Enter the name of the scores file: ";
	cin >> scoresFile;

	fill(scoresFile, nameVec, scoreVec); // Copies data from file to vectors
	
	// Prints average and standard deviation
	cout << endl;
	cout << "Mean score: " << average(scoreVec) << endl;
	cout << "Standard deviation: " << standardDev(scoreVec) << endl << endl;
	
	computeLetterGrades(scoreVec, gradeVec);

	// Determines the length of the longest name
	for (unsigned int i = 0; i < nameVec.size(); i++)
	{
		if (nameVec.at(i).length() > maxNameLength)
			maxNameLength = nameVec.at(i).length();
	}
	maxNameLength++; // Adds one to make name field slightly wider

	cout << left; // Left-justifies text in each field

	// Prints out a table of students' names, scores, and grades based on curve
	for (unsigned int i = 0; i < gradeVec.size(); i++)
	{
		cout << setw(maxNameLength) << nameVec.at(i) << setw(8) 
			<< scoreVec.at(i) << gradeVec.at(i) << endl;
	}
}


// Fills two empty vectors with data from input file
void fill(string inputFileName, vector<string>& nameVec, 
	vector<double>& scoreVec)
{
	string name;
	double score;
	ifstream input;

	// Reads file and stores data in vectors
	input.open(inputFileName, ios::in);
	if (input.is_open())
	{
		while (!input.eof())
		{
			input >> name;
			input >> score;
			nameVec.push_back(name);
			scoreVec.push_back(score);
		}
		input.close();
	}
}


// Calculates and returns average of values in vector
double average(vector<double> vec)
{
	double sum = 0, average = -1;

	if (vec.size() > 0) // Ensures vector contains values
	{
		// Totals up all values
		for (unsigned int i = 0; i < vec.size(); i++)
			sum += vec.at(i);

		average = sum / vec.size(); // Calculates average
	}
	else
		cout << "Could not calculate average. Vector is empty." << endl;
	
	return average; // Returns -1 if vector was empty
}


// Computes and returns standard deviation of vector
double standardDev(vector<double> vec)
{
	double mean, standardDeviation = -1;

	if (vec.size() > 0) // Ensures vector contains values
	{
		mean = average(vec);
		standardDeviation++; // Increases to start at 0

		// Finds the sum of the square of each data point's distance to mean
		for (unsigned int i = 0; i < vec.size(); i++)
			standardDeviation += pow((vec.at(i) - mean), 2);
		
		// Divides by number of data points and takes square root
		standardDeviation /= vec.size();
		standardDeviation = sqrt(standardDeviation);
	}
	else
	{
		cout << "Could not calculate standard deviation. Vector is empty."
			<< endl;
	}
	
	return standardDeviation; // Returns -1 if vector was empty
}


// Computes appropriate letter grade using the "grading-on-the-curve" approach
void computeLetterGrades(vector<double> scoreVec, vector<char>& gradeVec)
{
	double score, cutoffFour, cutoffThree, cutoffTwo, cutoffOne, 
		mean = average(scoreVec), standardDeviation = standardDev(scoreVec);
	
	// Calculates cutoffs
	cutoffFour = mean - 1.5 * standardDeviation;
	cutoffThree = mean - 0.5 * standardDeviation;
	cutoffTwo = mean + 0.5 * standardDeviation;
	cutoffOne = mean + 1.5 * standardDeviation;

	// Assigns letter grades based off scores and cutoffs
	for (unsigned int i = 0; i < scoreVec.size(); i++)
	{
		score = scoreVec.at(i);

		// Trickles down grades and assigns when a matching tier is found
		if (score >= cutoffOne)
			gradeVec.push_back('A');
		else if (score >= cutoffTwo)
			gradeVec.push_back('B');
		else if (score >= cutoffThree)
			gradeVec.push_back('C');
		else if (score >= cutoffFour)
			gradeVec.push_back('D');
		else
			gradeVec.push_back('F');
	}
}
