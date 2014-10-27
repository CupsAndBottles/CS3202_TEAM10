#pragma once

#include "AST\TNode\TNode.h"
#include "AST\TNode\ProgramTNode.h"

#include <cstdarg>

class AST {
public:
	void initNewProgram(ProgramTNode);
	TNode CreateTNode(TNode::Type, ...);

	template<typename T>
	static T typecast(TNode);
private:
	AST();	
};

