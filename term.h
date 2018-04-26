/*
* File:   term.h
* The declaration of the term class
* Author: Jared Rigdon
*/

#ifndef TERM_H
#define	TERM_H

#include <string>
#include <algorithm>

using namespace std;

class Term
{
public:
	// default constructor
	Term();

	// initializes a term with the given query string and weight
	Term(string query, long weight);

	// compares the two terms in lexicographic order 
	// but using only the first r characters of each query
	int byPrefixOrder(Term that, int r);

	// displays the term in the following format:
	// the weight, followed by a tab key, followed by the query
	void print();

	friend class Autocomplete;

private:
	string query;
	long weight;
};

#endif	/* TERM_H */

