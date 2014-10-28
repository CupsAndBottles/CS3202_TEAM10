#pragma once

#include "Parser.h"
#include "PKB.h"
#include "Tokenizer.h"
#include "AST/AST.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int Parse (string source) {
	vector<Token> tokens = Tokenizer::tokenize(source);
	return Parse(tokens);
}

int Parse(vector<Token> tokens) {
	deque<ProcedureTNode> procedures;

	ProgramTNode program = AST::CreateTNode(TNode::Program, procedures);

	return 1;
}