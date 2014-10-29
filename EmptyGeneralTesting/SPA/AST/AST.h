#pragma once

#include "Token.h"
#include "AST\TNode\TNode.h"
#include "AST\TNode\ProgramTNode.h"

#include <cstdarg>

class AST {
public:
	AST();

	void InitNewProgram(ProgramTNode);
	static TNode CreateTNode(TNode::Type, ...);
	static TNode::Type GetTNodeTypeFrom(Token::Type);

	template<typename T>
	static T typecast(TNode);
private:
	vector<ProgramTNode> programs;
};

