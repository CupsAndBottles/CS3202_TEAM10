#include "ParserToPKBTest2.h"

#include "..\SPA\Parser\Parser.h"
#include "..\SPA\PKB\VarTable.h"
#include "..\SPA\PKB\StmtTypeTable.h"
#include "..\SPA\PKB\ConstTable.h"
#include "..\SPA\PKB\Follows.h"
#include "..\SPA\PKB\Parent.h"
#include "..\SPA\PKB\Modifies.h"
#include "..\SPA\PKB\Uses.h"
#include "..\SPA\PKB\Next.h"
#include "..\SPA\PKB\ProcTable.h"
#include "..\SPA\Program\Program.h"
#include "..\SPA\Parser\ParserTester.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <stdint.h>

CPPUNIT_TEST_SUITE_REGISTRATION(ParserToPKBTest2);

const string TESTFILE_DIRECTORY = "ParserTestFiles/";

ParserToPKBTest2::ParserToPKBTest2() {
	Program::ClearAll();
}

void ParserToPKBTest2::setUp() {
	Program::ClearAll();
	ParserTester tester(TESTFILE_DIRECTORY);
	tester.ParseSource("Source.txt");
}

void ParserToPKBTest2::tearDown() {
	Program::ClearAll();
}

bool IsVarIn(string var, vector<int> variables) {
	int currentVar = VarTable::GetIndexOfVar(var);
	return find(variables.begin(), variables.end(), currentVar) != variables.end();
}

void ParserToPKBTest2::TestModifies() {
	vector<int> varsModified;

	// call Quartet;
	varsModified = Modifies::GetVarModifiedByStmt(15);
	CPPUNIT_ASSERT((int)varsModified.size() == 1);
	CPPUNIT_ASSERT(IsVarIn("z", varsModified));

	varsModified = Modifies::GetVarModifiedByStmt(6);
	CPPUNIT_ASSERT((int)varsModified.size() == 1);
	CPPUNIT_ASSERT(IsVarIn("z", varsModified));

	// call Trio;
	varsModified = Modifies::GetVarModifiedByStmt(20);
	CPPUNIT_ASSERT((int)varsModified.size() == 3);
	CPPUNIT_ASSERT(IsVarIn("m", varsModified));
	CPPUNIT_ASSERT(IsVarIn("x", varsModified));
	CPPUNIT_ASSERT(IsVarIn("y", varsModified));

	varsModified = Modifies::GetVarModifiedByStmt(4);
	CPPUNIT_ASSERT((int)varsModified.size() == 3);
	CPPUNIT_ASSERT(IsVarIn("m", varsModified));
	CPPUNIT_ASSERT(IsVarIn("x", varsModified));
	CPPUNIT_ASSERT(IsVarIn("y", varsModified));

	// call Duo;
	varsModified = Modifies::GetVarModifiedByStmt(17);
	CPPUNIT_ASSERT((int)varsModified.size() == 4);
	CPPUNIT_ASSERT(IsVarIn("m", varsModified));
	CPPUNIT_ASSERT(IsVarIn("x", varsModified));
	CPPUNIT_ASSERT(IsVarIn("y", varsModified));
	CPPUNIT_ASSERT(IsVarIn("z", varsModified));
}

void ParserToPKBTest2::TestUses(){
	vector<int> varsUsed;

	varsUsed = Uses::GetVarUsedByStmt(15);
	CPPUNIT_ASSERT((int)varsUsed.size() == 2);
	CPPUNIT_ASSERT(IsVarIn("z", varsUsed));
	CPPUNIT_ASSERT(IsVarIn("x", varsUsed));

	varsUsed = Uses::GetVarUsedByStmt(6);
	CPPUNIT_ASSERT((int)varsUsed.size() == 2);
	CPPUNIT_ASSERT(IsVarIn("z", varsUsed));
	CPPUNIT_ASSERT(IsVarIn("x", varsUsed));

	varsUsed = Uses::GetVarUsedByStmt(20);
	CPPUNIT_ASSERT((int)varsUsed.size() == 5);
	CPPUNIT_ASSERT(IsVarIn("m", varsUsed));
	CPPUNIT_ASSERT(IsVarIn("x", varsUsed));
	CPPUNIT_ASSERT(IsVarIn("z", varsUsed));
	CPPUNIT_ASSERT(IsVarIn("k", varsUsed));
	CPPUNIT_ASSERT(IsVarIn("n", varsUsed));

	varsUsed = Uses::GetVarUsedByStmt(4);
	CPPUNIT_ASSERT((int)varsUsed.size() == 5);
	CPPUNIT_ASSERT(IsVarIn("m", varsUsed));
	CPPUNIT_ASSERT(IsVarIn("x", varsUsed));
	CPPUNIT_ASSERT(IsVarIn("z", varsUsed));
	CPPUNIT_ASSERT(IsVarIn("k", varsUsed));
	CPPUNIT_ASSERT(IsVarIn("n", varsUsed));

	varsUsed = Uses::GetVarUsedByStmt(17);
	CPPUNIT_ASSERT((int)varsUsed.size() == 6);
	CPPUNIT_ASSERT(IsVarIn("m", varsUsed));
	CPPUNIT_ASSERT(IsVarIn("x", varsUsed));
	CPPUNIT_ASSERT(IsVarIn("z", varsUsed));
	CPPUNIT_ASSERT(IsVarIn("k", varsUsed));
	CPPUNIT_ASSERT(IsVarIn("n", varsUsed));
	CPPUNIT_ASSERT(IsVarIn("y", varsUsed));
}

void ParserToPKBTest2::TestModifiesForProcs(){
	vector<int> varsModified;
		
	varsModified = Modifies::GetVarModifiedByProc(ProcTable::GetIndexOfProc("Quartet"));
	CPPUNIT_ASSERT((int)varsModified.size() == 1);
	CPPUNIT_ASSERT(IsVarIn("z", varsModified));

	varsModified = Modifies::GetVarModifiedByProc(ProcTable::GetIndexOfProc("Trio"));
	CPPUNIT_ASSERT((int)varsModified.size() == 3);
	CPPUNIT_ASSERT(IsVarIn("m", varsModified));
	CPPUNIT_ASSERT(IsVarIn("x", varsModified));
	CPPUNIT_ASSERT(IsVarIn("y", varsModified));

	varsModified = Modifies::GetVarModifiedByProc(ProcTable::GetIndexOfProc("Duo"));
	CPPUNIT_ASSERT((int)varsModified.size() == 4);
	CPPUNIT_ASSERT(IsVarIn("m", varsModified));
	CPPUNIT_ASSERT(IsVarIn("x", varsModified));
	CPPUNIT_ASSERT(IsVarIn("y", varsModified));
	CPPUNIT_ASSERT(IsVarIn("z", varsModified));

	varsModified = Modifies::GetVarModifiedByProc(ProcTable::GetIndexOfProc("Solo"));
	CPPUNIT_ASSERT((int)varsModified.size() == 6);
	CPPUNIT_ASSERT(IsVarIn("m", varsModified));
	CPPUNIT_ASSERT(IsVarIn("x", varsModified));
	CPPUNIT_ASSERT(IsVarIn("y", varsModified));
	CPPUNIT_ASSERT(IsVarIn("z", varsModified));
	CPPUNIT_ASSERT(IsVarIn("n", varsModified));
	CPPUNIT_ASSERT(IsVarIn("k", varsModified));
}

void ParserToPKBTest2::TestUsesForProcs() {
	vector<int> varsUsed;

	varsUsed = Uses::GetVarUsedByProc(ProcTable::GetIndexOfProc("Quartet"));
	CPPUNIT_ASSERT((int)varsUsed.size() == 2);
	CPPUNIT_ASSERT(IsVarIn("z", varsUsed));
	CPPUNIT_ASSERT(IsVarIn("x", varsUsed));

	varsUsed = Uses::GetVarUsedByProc(ProcTable::GetIndexOfProc("Trio"));
	CPPUNIT_ASSERT((int)varsUsed.size() == 5);
	CPPUNIT_ASSERT(IsVarIn("m", varsUsed));
	CPPUNIT_ASSERT(IsVarIn("x", varsUsed));
	CPPUNIT_ASSERT(IsVarIn("z", varsUsed));
	CPPUNIT_ASSERT(IsVarIn("k", varsUsed));
	CPPUNIT_ASSERT(IsVarIn("n", varsUsed));

	varsUsed = Uses::GetVarUsedByProc(ProcTable::GetIndexOfProc("Duo"));
	CPPUNIT_ASSERT((int)varsUsed.size() == 6);
	CPPUNIT_ASSERT(IsVarIn("m", varsUsed));
	CPPUNIT_ASSERT(IsVarIn("x", varsUsed));
	CPPUNIT_ASSERT(IsVarIn("z", varsUsed));
	CPPUNIT_ASSERT(IsVarIn("k", varsUsed));
	CPPUNIT_ASSERT(IsVarIn("n", varsUsed));
	CPPUNIT_ASSERT(IsVarIn("y", varsUsed));

	varsUsed = Uses::GetVarUsedByProc(ProcTable::GetIndexOfProc("Solo"));
	CPPUNIT_ASSERT((int)varsUsed.size() == 6);
	CPPUNIT_ASSERT(IsVarIn("m", varsUsed));
	CPPUNIT_ASSERT(IsVarIn("x", varsUsed));
	CPPUNIT_ASSERT(IsVarIn("z", varsUsed));
	CPPUNIT_ASSERT(IsVarIn("k", varsUsed));
	CPPUNIT_ASSERT(IsVarIn("n", varsUsed));
	CPPUNIT_ASSERT(IsVarIn("y", varsUsed));
}

void ParserToPKBTest2::TestAffects(){}

void ParserToPKBTest2::TestAffectsT(){}
