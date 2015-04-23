#pragma once

#include <iostream>
#include <string>
#include "Program\Program.h"
#include "Parser\Parser.h"
#include "PKB\Modifies.h"
#include "PKB\Affects.h"
#include "PKB\StmtTypeTable.h"

#include <set>

using namespace std;

void main() {
	Program::ClearAll();

	Parser::Parse("ultimate-source.txt");

	//vector<int> result;
	//for each (int stmt in StmtTypeTable::GetAllStmtsOfType(ASSIGN)) {
	//	if (Affects::IsAffects(stmt, 10)) {
	//		result.push_back(stmt);
	//	}
	//}
	//vector<int> wow = result;

	Affects::IsAffects(23, 10);
}


