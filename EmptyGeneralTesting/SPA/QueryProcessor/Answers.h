#pragma once
#include "QueryData.h"
#include "PatternMatcher.h"
#include "Grammar.h"

using namespace std;

class Answers{
private:
	Synonym name;
	vector<vector<Answers*>> links;

public:
	bool useful; //used when delete elements in a list (Biuld a new list)
	int ListIndex; //Which list is this synonym in.
	Answers(Synonym value,int index):name(value),ListIndex(index){};

	bool hasLinksWith(int index);	

	vector<Answers*> cleanLinks();
	//Delete all the links with other answers. Then, we can delete this answer. 
	//Return the list of answers that has no links with others (need to be delete) after this operation.

	vector<Answers*> getLinksOfList(int ListIndex);
	static void addLink(Answers answer1, Answers answer2);
}