#pragma once

#include <iostream>
#include <string>
#include "Program\Program.h"
#include "PKB\Affects.h"
#include "Parser\Parser.h"

using namespace std;

void main() {
	Program::ClearAll();

	Parser::Parse("AffectsTTest.txt");

	Affects::GetStmtsAffectingT(16);

	//// test sequential
	//cout << std::boolalpha << Affects::IsAffectsT(1, 2) << "\n";
	//cout << std::boolalpha << Affects::IsAffectsT(1, 3) << "\n";
	//cout << std::boolalpha << Affects::IsAffectsT(2, 4) << "\n";
	//cout << std::boolalpha << Affects::IsAffectsT(1, 4) << "\n";

	//// test whileLoop
	//cout << std::boolalpha << Affects::IsAffectsT(5, 7) << "\n";
	//cout << std::boolalpha << Affects::IsAffectsT(8, 8) << "\n";
	//cout << std::boolalpha << Affects::IsAffectsT(9, 10) << "\n";
	//cout << std::boolalpha << Affects::IsAffectsT(5, 10) << "\n";

	//// test ifStmt
	//cout << std::boolalpha << Affects::IsAffectsT(11, 13) << "\n";
	//cout << std::boolalpha << Affects::IsAffectsT(11, 14) << "\n";
	//cout << std::boolalpha << Affects::IsAffectsT(11, 15) << "\n";
	//cout << std::boolalpha << Affects::IsAffectsT(13, 16) << "\n";
	//cout << std::boolalpha << Affects::IsAffectsT(14, 17) << "\n";
	//cout << std::boolalpha << Affects::IsAffectsT(11, 16) << "\n";
	//cout << std::boolalpha << Affects::IsAffectsT(11, 17) << "\n";

	//// test ifInWhile
	//cout << std::boolalpha << Affects::IsAffectsT(19, 21) << "\n";
	//cout << std::boolalpha << Affects::IsAffectsT(19, 22) << "\n";
	//cout << std::boolalpha << Affects::IsAffectsT(22, 23) << "\n";
	//cout << std::boolalpha << Affects::IsAffectsT(23, 24) << "\n";
	//cout << std::boolalpha << Affects::IsAffectsT(22, 22) << "\n"; // heisenbug
}


