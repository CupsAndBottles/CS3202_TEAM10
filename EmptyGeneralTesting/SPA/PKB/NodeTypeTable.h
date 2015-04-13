#pragma once

#include "..\Program\TNode\TNode.h"

#include <vector>

using namespace std;

class NodeTypeTable {
public:
	NodeTypeTable();

	enum NodeType {
		ASSIGN,
		WHILE,
		WHILEBODY,
		IF,
		THENBODY,
		ELSEBODY,
		VARIABLE,
		CONSTANT,
		PLUS,
		MINUS,
		MULTIPLY,
		PROCEDURE,
		PROGRAM
	};

	//API-Query
	static vector<int> GetAllNodesOfType(NodeType type);
	static vector<int> GetAllVarNodesOfVar(int varTableIndex);
	static vector<int> GetAllConstNodesOfConst(int constTableIndex);
	static NodeType GetNodeTypeOf(int nodeIndex);
	static bool CheckIfNodeOfType(int nodeIndex, NodeType type);
	static TNode* GetPtrToNode(int nodeIndex);

	//API-PKB and DE
	static void Insert(TNode* nodeptr); // automagically filter the var and const types

	static int GetNoOfNodes();
	static int GetNoOfNodexOfType(NodeType type);
	static int GetMaxNodeIndex();

	static void ClearData();
};

