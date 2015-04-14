#pragma once

#include "NodeTypeTable.h"
#include <vector>

using namespace std;

class Contains {
public:
	Contains();

	// General API
	static bool IsContains(int nodeContaining, int nodeContained);
	static bool IsContains(NodeType nodetypeContaining, NodeType nodetypeContained);
	static bool IsContains(int nodeContaining, NodeType nodetypeContained);
	static bool IsContains(NodeType nodetypeContaining, int nodeContained);

	static bool IsContainsVar(int nodeContaining, int varIndex);
	static bool IsContainsConst(int nodeContaining, int constant);
	static bool IsContainsVar(NodeType nodetypeContaining, int varIndex);
	static bool IsContainsConst(NodeType nodetypeContaining, int constant);

	static int GetNodeContaining(int nodeContained);
	static vector<int> GetNodesContained(int nodeContaining);
	static vector<int> GetNodesContaining(NodeType nodetypeContained);
	static vector<int> GetNodesContained(NodeType nodetypeContaining);
	static vector<int> GetNodesContainingVar(int varIndex);
	static vector<int> GetNodesContainingConst(int constantw);


	static bool IsContainsT(int nodeContaining, int nodeContained);
	static bool IsContainsT(NodeType nodetypeContaining, NodeType nodetypeContained);
	static bool IsContainsT(int nodeContaining, NodeType nodetypeContained);
	static bool IsContainsT(NodeType nodetypeContaining, int nodeContained);

	static vector<int> GetNodesContainingT(int nodeContained);
	static vector<int> GetNodesContainedT(int nodeContaining);
	static vector<int> GetNodesContainingT(NodeType nodetypeContained);
	static vector<int> GetNodesContainedT(NodeType nodetypeContaining);

	// helpers
	static vector<int> FilterNodesBy(vector<int> nodes, NodeType filterType);
	static bool DoesNodeNumberExistIn(vector<int> nodes, int nodeIndex);

	// specialisations, feel free to add your own or make them
	static bool IsContainsStmt(NodeType nodetypeContaining, int stmtNumber);
	static bool IsStmtContains(int stmtNumber, NodeType nodetypeContained);

};

