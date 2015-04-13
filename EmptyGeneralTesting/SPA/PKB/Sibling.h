#pragma once

#include <vector>

using namespace std;

class Sibling {
public:
	Sibling();

	// API 
	bool IsSibling(int nodeOne, int nodeTwo);
	vector<int> GetSiblings(int node);
};

