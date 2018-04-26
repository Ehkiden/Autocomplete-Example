//course: CS216-005
//Project: Programming Assignment 2
//Date: 04/3/2017
//Assumption: read the sequence of terms from an input file, with the following format for each term:
//            weight(long integer)    query(string)
//            the data has not been sorted
//Purpose: ask the user to type a key to match
//         use the binary search algorithm to find a matched term from the sequence of terms reading from the input file
//         a matched term is defined as the one which contains exactly the user-input key as the prefix
//         It also calculates the time spending on searching operation.    
//Author: Jared Rigdon

//Note: This program was meant to be used in Linux terminal so it requires a command line prompt

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <algorithm>
#include "term.h"
#include "autocomplete.h"

using namespace std;

int main(int argc, char** argv)
{
	const int ARGUMENTS = 3;
	//checks for file (the dictionary i think)
	if (argc != ARGUMENTS)
	{
		cout << "Usage: " << argv[0] << " <filename>" << endl;
		return 1;
	}

	ifstream infile;
	infile.open(argv[1]);
	if (!infile.good())
	{
		cout << "Cannot open the file named " << argv[1] << endl;
		return 2;
	}

	int limit = atoi(argv[2]);

	Autocomplete autocomplete;
	long weight;
	string query;

	// read in the terms from the input file    
	while (infile >> weight)
	{
		infile >> ws;  // extract and ignore the blank space
		getline(infile, query);
		Term newterm(query, weight);
		autocomplete.insert(newterm);
	}
	infile.close();

	int Size = autocomplete.getSize() - 1;
	autocomplete.quickSort(0, Size);

	string prefix;
	cout << "Please input the search query(type \"exit\" to quit): " << endl;
	//get rid of any leading whitespace
	cin >> ws;
	getline(cin, prefix);

	while (prefix != "exit")
	{
		//replace all multiple whitespace with just one whitespace
		prefix.erase(unique(prefix.begin(), prefix.end(), [](char a, char b) { return a == ' ' && b == ' '; }), prefix.end());
		//capitalize the first character in the string aswell as all characters followed by a whitespace
		prefix[0] = toupper(prefix[0]);
		for (int i = 1; i < prefix.size(); i++) {
			if (prefix[i] == ' ') {
				prefix[i + 1] = toupper(prefix[i + 1]);
			}
		}
		clock_t tstart, tstop;
		tstart = clock();
		//pass in the limiting k value and prefix
		autocomplete.allMatches(prefix, limit);
		tstop = clock();
		double  elapsed = (double)(tstop - tstart) / CLOCKS_PER_SEC;
		cout << "Time for searching one prefix-matched term: " << elapsed << " seconds." << endl;
		cout << "Please input the search query(type \"exit\" to quit): " << endl;
		getline(cin, prefix);
	}
	return 0;
}

