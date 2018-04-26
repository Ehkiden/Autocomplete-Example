/*
* File:   autocomplete.cpp
* It provides the implementation of member functions of the Autocomplete class
*
* Author: Jared Rigdon
*/
#include <iostream>
#include "autocomplete.h"

// default constructor
Autocomplete::Autocomplete()
{
}

// inserts the newterm to the end of the vector   
void Autocomplete::insert(Term newterm)
{
	terms.push_back(newterm);
}

// Calling binary_searchHelper function to find one term with the query starting with key
// From the matched term in the vector, going forward and backward to find the firstIndex and lastIndex
// firstIndex: the index of the first query that equals the search key, or -1 if no such key
// lastIndex: the index of the last query that equals the search key, or -1 if no such key
void Autocomplete::Search(string key, int& firstIndex, int& lastIndex)
{

	int temp = binary_searchHelper(terms, key, firstIndex, lastIndex);
	//if the temp returns a -1 then not match was found
	if (temp == -1) {
		cout << "No match." << endl;
	}
	else {
		Matchedindexs.push_back(temp);

		bool rightfound = true;
		bool leftfound = true;

		Term termkey(key, 0);
		int r = key.length();

		int x = temp;
		int y = temp;

		while (rightfound == true) {
			x++;
			if (termkey.byPrefixOrder(terms[x], r) == 0) {
				//adds the matched term to the end of the vector
				Matchedindexs.push_back(x);
			}
			else {
				rightfound = false;
			}
		}

		while (leftfound == true) {
			y--;
			//add the macthed term to the begining of the vector
			if (termkey.byPrefixOrder(terms[y], r) == 0) {
				Matchedindexs.insert(Matchedindexs.begin(), y);
			}
			else {
				leftfound = false;
			}
		}
	}
}

// recursive helper function for binary search
// returns the index number of one matched term
int Autocomplete::binary_searchHelper(vector<Term> terms, string key, int left_index, int right_index)
{
	if (right_index < left_index)
	{
		const int KEY_NOT_FOUND = -1;
		return KEY_NOT_FOUND;
	}
	else
	{
		Term keyterm(key, 0);
		int r = key.length();
		int middle = (left_index + right_index) / 2;
		//this passes in the term that is in the middle of the vector
		//compares the strings up until the 'r'th character 
		if (keyterm.byPrefixOrder(terms[middle], r) > 0)
		{
			return binary_searchHelper(terms, key, left_index, middle - 1);

		}
		else if (keyterm.byPrefixOrder(terms[middle], r)  < 0)
		{
			return binary_searchHelper(terms, key, middle + 1, right_index);
		}
		else
		{
			return middle;
		}
	}

}

void Autocomplete::quickSort(long int left_o, long int right_o)
{
	long int left = left_o;
	long int right = right_o;

	long int tempW;
	string tempQ;

	string pivotQ = terms[(left + right) / 2].query;
	long pivotW = terms[(left + right) / 2].weight;

	while (left <= right)
	{
		while (terms[left].query < pivotQ)
		{
			left++;
		}
		while (terms[right].query > pivotQ)
		{
			right--;
		}
		//swaps both the wieght and the query
		if (left <= right)
		{
			tempQ = terms[left].query;
			tempW = terms[left].weight;

			terms[left].query = terms[right].query;
			terms[left].weight = terms[right].weight;

			terms[right].query = tempQ;
			terms[right].weight = tempW;

			left++;
			right--;
		}
	}

	if (left_o < right)
	{
		quickSort(left_o, right);
	}
	if (left < right_o)
	{
		quickSort(left, right_o);
	}
}

int Autocomplete::getSize()
{
	return terms.size();
}

// print all the terms which start with the given prefix, in its original order(lexicographical order of the query)
void Autocomplete::allMatches(string prefix, int k)
{
	limit = k;
	//calls the search function
	int firstindex = 0;
	int lastindex = terms.size() - 1;
	Search(prefix, firstindex, lastindex);

	//after all matching terms are found then call the functino to sort them by decreasing wieight value
	for (int i = 0; i < Matchedindexs.size() - 1; i++) {
		for (int j = 0; j < Matchedindexs.size() - 1; j++) {
			if (terms[Matchedindexs[j]].weight < terms[Matchedindexs[j + 1]].weight) {
				swap(Matchedindexs[j], Matchedindexs[j + 1]);
			}
		}
	}
	//then calls the print function
	print();
}

// display all the terms    
void Autocomplete::print()
{
	//if there are less matched terms than the limit value then print all matched terms
	if (Matchedindexs.size() < limit) {
		for (int i = 0; i < Matchedindexs.size(); i++) {
			terms[Matchedindexs[i]].print();
		}
	}
	//else print all matched terms until the limit is hit
	else {
		for (int i = 0; i < limit; i++) {
			terms[Matchedindexs[i]].print();
		}
	}
	Matchedindexs.clear();
}
