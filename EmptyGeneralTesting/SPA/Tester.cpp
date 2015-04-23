#pragma once

#include <iostream>
#include <string>
#include "Program\Program.h"
#include "Parser\Parser.h"
#include "PKB\Modifies.h"
#include "PKB\Affects.h"

using namespace std;

void main() {
	Program::ClearAll();

	Parser::Parse("Source.txt");

	Affects::IsAffectsT(1, 5);
}


