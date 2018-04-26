#include "term.h"
#include <iostream>

Term::Term()
{

}

Term::Term(string query, long weight)
{
	this->query = query;
	this->weight = weight;
}

int Term::byPrefixOrder(Term that, int r)
{
	//creates a temp value that compares the 2 terms to 'r'th lenght
	string curr = that.query;
	string first_r = curr.substr(0, r);
	string key = this->query;

	transform(first_r.begin(), first_r.end(), first_r.begin(), toupper);
	transform(key.begin(), key.end(), key.begin(), toupper);

	if (key < first_r) {
		return 1;
	}
	else if (key > first_r) {
		return -1;
	}
	else {
		return 0;
	}
}

void Term::print()
{
	cout << weight << "\t" << query << endl;
}
