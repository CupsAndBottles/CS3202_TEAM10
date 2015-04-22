#pragma once

#include <iostream>
#include <string>
#include "Program\Program.h"
#include "Parser\Parser.h"
#include "PKB\Modifies.h"

using namespace std;

void main() {
	Program::ClearAll();

	Parser::Parse("Source.txt");

	vector<int> varsModified = Modifies::GetVarModifiedByStmt(4);
}


