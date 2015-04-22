#pragma once

#include "..\QueryProcessor\Grammar.h"
#include <vector>

using namespace std;

class Sibling {
public:
	Sibling();

	// API 
	static bool IsSibling(int nodeOne, int nodeTwo);
	static bool IsSibling(int nodeOne, NodeType nodeTwo);
	static bool IsSibling(NodeType nodeOne, int nodeTwo);
	static bool IsSibling(NodeType nodeOne, NodeType nodeTwo);

	static vector<int> GetSiblings(int node);
	static vector<int> GetSiblings(NodeType node);
};

