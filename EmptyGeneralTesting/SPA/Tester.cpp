#pragma once

#include <iostream>
#include <string>
#include "Parser\Parser.h"
#include "Program\Program.h"
#include "PKB\Affects.h"

using namespace std;

void main() {
	Program::ClearAll();
	Parser::Parse("Test.txt");
	cout << (Program::GetStmtFromNumber(22).GetChild(0).GetContent());
	cout << Affects::IsAffectsT(22, 22);
}


