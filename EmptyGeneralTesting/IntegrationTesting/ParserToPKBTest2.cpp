#include "ParserToPKBTest2.h"

#include "..\SPA\PKB\Modifies.h"
#include "..\SPA\PKB\Uses.h"
#include "..\SPA\PKB\Affects.h"
#include "..\SPA\PKB\ProcTable.h"
#include "..\SPA\PKB\VarTable.h"
#include "..\SPA\PKB\StmtTypeTable.h"
#include "..\SPA\Program\Program.h"
#include "..\SPA\Parser\ParserTester.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
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

bool IsStmtIn(int stmt, vector<int> stmts) {
	return find(stmts.begin(), stmts.end(), stmt) != stmts.end();
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


	varsModified = Modifies::GetVarModifiedByStmt(10);
	CPPUNIT_ASSERT((int)varsModified.size() == 2);
	CPPUNIT_ASSERT(IsVarIn("m", varsModified));
	CPPUNIT_ASSERT(IsVarIn("y", varsModified));

	varsModified = Modifies::GetVarModifiedByStmt(8);
	CPPUNIT_ASSERT((int)varsModified.size() == 5);
	CPPUNIT_ASSERT(IsVarIn("m", varsModified));
	CPPUNIT_ASSERT(IsVarIn("x", varsModified));
	CPPUNIT_ASSERT(IsVarIn("y", varsModified));
	CPPUNIT_ASSERT(IsVarIn("z", varsModified));
	CPPUNIT_ASSERT(IsVarIn("k", varsModified));
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

void ParserToPKBTest2::TestAffects(){
	// IsAffects

	int noOfStmts = StmtTypeTable::GetMaxStmtIndex();
	map<int, map<int, bool>> validResults;
	map<int, bool> excluded;

	// initialise
	map <int, bool> blankMap;
	for (int i = 1; i <= noOfStmts; i++) {
		blankMap[i] = false;
	}
	excluded = blankMap;
	for (int i = 1; i <= noOfStmts; i++) {
		validResults[i] = blankMap;
	}

	validResults[1][2] = true;
	validResults[1][3] = true;
	validResults[1][5] = true;
	validResults[2][3] = true;
	validResults[11][12] = true;
	validResults[11][13] = true;
	validResults[11][11] = true;
	validResults[19][22] = true;
	validResults[21][19] = true;
	validResults[25][26] = true;
	validResults[26][26] = true;
	validResults[26][27] = true;

	//excluded[22] = true;
	//excluded[27] = true;
	//excluded[28] = true;

	for (int affecting = 1; affecting <= noOfStmts; affecting++) {
		for (int affected = 1; affected <= noOfStmts; affected++) {
			if (!excluded[affecting] && !excluded[affected])
				CPPUNIT_ASSERT_EQUAL(validResults[affecting][affected], Affects::IsAffects(affecting, affected));
		}
	}

	// GetStmtsAffectedBy  

	// reinitialise
	excluded = blankMap;

	for (int affecting = 1; affecting <= noOfStmts; affecting++) {
		if (!excluded[affecting]) {
			vector<int> results = Affects::GetStmtsAffectedBy(affecting);
			for (int affected = 1; affected <= noOfStmts; affected++) {
				CPPUNIT_ASSERT_EQUAL(validResults[affecting][affected], IsStmtIn(affected, results));
			}
		}
	}
	
	// GetStmtsAffecting

	excluded = blankMap;

	//ofstream testFile;
	//testFile.open("results.txt");

	for (int affected = 1; affected <= noOfStmts; affected++) {
		if (!excluded[affected]) {
			//cout << "\nGet stmts affecting: " << affected;
			vector<int> results = Affects::GetStmtsAffecting(affected);
			for (int affecting = 1; affecting <= noOfStmts; affecting++) {
				//testFile << affecting << " " << affected << " " << validResults[affecting][affected] << " " << IsStmtIn(affecting, results) << "\n";
				//cout << "\n" << affecting << " " << affected << " " << validResults[affecting][affected] << " " << IsStmtIn(affecting, results);
				
				// false negative
				//if (affecting == 11 && affected == 11) continue;
				//if (affecting == 11 && affected == 13) continue;
				//if (affecting == 19 && affected == 22) continue;
				//if (affecting == 21 && affected == 19) continue;
				//if (affecting == 25 && affected == 26) continue;
				//if (affecting == 26 && affected == 26) continue;
				//if (affecting == 26 && affected == 27) continue;

				// false positive
				//if (affecting == 2 && affected == 5) continue;
				//if (affecting == 2 && affected == 7) continue;
				//if (affecting == 2 && affected == 9) continue;

				CPPUNIT_ASSERT_EQUAL(validResults[affecting][affected], IsStmtIn(affecting, results));
			}
		}
	}
	//testFile.close();
}

void ParserToPKBTest2::TestAffectsT() {
	int noOfStmts = StmtTypeTable::GetMaxStmtIndex();
	map<int, map<int, bool>> validResults;
	map<int, bool> excluded;

	// initialise
	map <int, bool> blankMap;
	for (int i = 1; i <= noOfStmts; i++) {
		blankMap[i] = false;
	}
	excluded = blankMap;
	for (int i = 1; i <= noOfStmts; i++) {
		validResults[i] = blankMap;
	}

	validResults[1][2] = true;
	validResults[1][3] = true;
	validResults[1][5] = true;
	validResults[2][3] = true;
	validResults[11][11] = true;
	validResults[11][12] = true;
	validResults[11][13] = true;
	validResults[19][22] = true;
	validResults[21][19] = true;
	validResults[21][22] = true;
	validResults[25][26] = true;
	validResults[26][26] = true;
	validResults[26][27] = true;
	validResults[25][27] = true;

	// IsAffectsT

	for (int affecting = 1; affecting <= noOfStmts; affecting++) {
		for (int affected = 1; affected <= noOfStmts; affected++) {
			if (!excluded[affecting] && !excluded[affected]) {
				CPPUNIT_ASSERT_EQUAL(validResults[affecting][affected], Affects::IsAffectsT(affecting, affected));
			}
		}
	}

	// GetStmtsAffectedTBy

	// reinitialise
	excluded = blankMap;

	for (int affecting = 1; affecting <= noOfStmts; affecting++) {
		if (!excluded[affecting]) {
			vector<int> results = Affects::GetStmtsAffectedTBy(affecting);
			for (int affected = 1; affected <= noOfStmts; affected++) {
				CPPUNIT_ASSERT_EQUAL(validResults[affecting][affected], IsStmtIn(affected, results));
			}
		}
	}

	// GetStmtsAffectingT

	excluded = blankMap;

	for (int affected = 1; affected <= noOfStmts; affected++) {
		if (!excluded[affected]) {
			vector<int> results = Affects::GetStmtsAffectingT(affected);
			for (int affecting = 1; affecting <= noOfStmts; affecting++) {
				CPPUNIT_ASSERT_EQUAL(validResults[affecting][affected], IsStmtIn(affecting, results));
			}
		}
	}
}
