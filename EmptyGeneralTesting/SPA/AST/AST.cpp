#pragma once

#include "AST.h"
#include "Token.h"
#include "TNode\ProcedureTNode.h"
#include "TNode\AssignmentTNode.h"
#include "TNode\ConstantTNode.h"
#include "TNode\IfTNode.h"
#include "TNode\WhileTNode.h"
#include "TNode\CallTNode.h"

AST::AST() {}

ProgramTNode& AST::getRootNode() {
	return program;
}

