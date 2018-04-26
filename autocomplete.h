/*
* File:   autocomplete.h
* The declaration of the Autocomplete class
*
* Author: Jared Rigdon
*/

#ifndef AUTOCOMPLETE_H
#define	AUTOCOMPLETE_H

#include <vector>
#include <string>
#include "term.h"

using namespace std;

class Autocomplete
{
public:
	// default constructor
	Autocomplete();

	// inserts the newterm to the end of the current vector   
	void insert(Term newterm);

	// print all the terms which start with the given prefix, in its original order(lexicographical order of the query)
	void allMatches(string prefix, int k);

	// firstIndex: the index of the first query that equals the search key, or -1 if no such key
	// lastIndex: the index of the last query that equals the search key, or -1 if no such key
	void Search(string key, int& firstIndex, int& lastIndex);

	// recursive helper function for binary search
	// returns the index number of one matched term
	int binary_searchHelper(vector<Term> terms, string key, int left_index, int right_index);

	//sorts the pressumably unsorted terms by lexographical order
	void quickSort(long int left_o, long int right_o);

	//gets the size of the terms vector
	int getSize();

	// display all the terms
	void print();

private:
	vector<Term> terms;
	int limit;
	vector<int>Matchedindexs;
};


#endif	/* AUTOCOMPLETE_H */
