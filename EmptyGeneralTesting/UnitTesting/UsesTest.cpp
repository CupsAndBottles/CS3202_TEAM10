#include "UsesTest.h"
#include "PKB\Uses.h"

void UsesTest::setUp() {}
void UsesTest::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(UsesTest);

UsesTest::UsesTest() {
}

void UsesTest::TestSingleStmt() {
	Uses::ClearData();
	CPPUNIT_ASSERT(Uses::HasAnyUses() == false);

	Uses::SetStmtUsesVar(1, 0);

	CPPUNIT_ASSERT(Uses::HasAnyUses() == true);
	CPPUNIT_ASSERT(Uses::SizeOfUses() == 1);
	CPPUNIT_ASSERT(Uses::IsStmtUsingVar(1, 0));

	vector<int> stmtsUsingVar0 = Uses::GetStmtUsingVar(0);
	CPPUNIT_ASSERT(stmtsUsingVar0.size() == 1);
	CPPUNIT_ASSERT(stmtsUsingVar0[0] == 1);

	vector<int> varsUsedByStmt1 = Uses::GetVarUsedByStmt(1);
	CPPUNIT_ASSERT(varsUsedByStmt1.size() == 1);
	CPPUNIT_ASSERT(varsUsedByStmt1[0] == 0);

	Uses::ClearData();
	CPPUNIT_ASSERT(Uses::HasAnyUses() == false);
	
}

void UsesTest::TestMultipleStmts() {
	Uses::ClearData();
	CPPUNIT_ASSERT(Uses::HasAnyUses() == false);

	Uses::SetStmtUsesVar(1, 0);
	Uses::SetStmtUsesVar(2, 1);
	Uses::SetStmtUsesVar(3, 2);
	Uses::SetStmtUsesVar(4, 3);

	CPPUNIT_ASSERT(Uses::HasAnyUses() == true);
	CPPUNIT_ASSERT(Uses::SizeOfUses() == 4);
	CPPUNIT_ASSERT(Uses::IsStmtUsingVar(1, 0));
	CPPUNIT_ASSERT(Uses::IsStmtUsingVar(2, 1));
	CPPUNIT_ASSERT(Uses::IsStmtUsingVar(3, 2));
	CPPUNIT_ASSERT(Uses::IsStmtUsingVar(4, 3));

	vector<int> stmtsUsingVar0 = Uses::GetStmtUsingVar(0);
	CPPUNIT_ASSERT(stmtsUsingVar0.size() == 1);
	CPPUNIT_ASSERT(stmtsUsingVar0[0] == 1);

	vector<int> stmtsUsingVar1 = Uses::GetStmtUsingVar(1);
	CPPUNIT_ASSERT(stmtsUsingVar1.size() == 1);
	CPPUNIT_ASSERT(stmtsUsingVar1[0] == 2);

	vector<int> stmtsUsingVar2 = Uses::GetStmtUsingVar(2);
	CPPUNIT_ASSERT(stmtsUsingVar2.size() == 1);
	CPPUNIT_ASSERT(stmtsUsingVar2[0] == 3);

	vector<int> stmtsUsingVar3 = Uses::GetStmtUsingVar(3);
	CPPUNIT_ASSERT(stmtsUsingVar3.size() == 1);
	CPPUNIT_ASSERT(stmtsUsingVar3[0] == 4);

	vector<int> varsUsedByStmt1 = Uses::GetVarUsedByStmt(1);
	CPPUNIT_ASSERT(varsUsedByStmt1.size() == 1);
	CPPUNIT_ASSERT(varsUsedByStmt1[0] == 0);

	vector<int> varsUsedByStmt2 = Uses::GetVarUsedByStmt(2);
	CPPUNIT_ASSERT(varsUsedByStmt2.size() == 1);
	CPPUNIT_ASSERT(varsUsedByStmt2[0] == 1);

	vector<int> varsUsedByStmt3 = Uses::GetVarUsedByStmt(3);
	CPPUNIT_ASSERT(varsUsedByStmt3.size() == 1);
	CPPUNIT_ASSERT(varsUsedByStmt3[0] == 2);

	vector<int> varsUsedByStmt4 = Uses::GetVarUsedByStmt(4);
	CPPUNIT_ASSERT(varsUsedByStmt4.size() == 1);
	CPPUNIT_ASSERT(varsUsedByStmt4[0] == 3);

	Uses::ClearData();
	CPPUNIT_ASSERT(Uses::HasAnyUses() == false);

}

void UsesTest::TestMultipleStmtsUsingSingleVar() {
	Uses::ClearData();
	CPPUNIT_ASSERT(Uses::HasAnyUses() == false);

	Uses::SetStmtUsesVar(1, 0);
	Uses::SetStmtUsesVar(2, 0);
	Uses::SetStmtUsesVar(3, 0);
	Uses::SetStmtUsesVar(4, 0);

	CPPUNIT_ASSERT(Uses::HasAnyUses() == true);
	CPPUNIT_ASSERT(Uses::SizeOfUses() == 4);
	CPPUNIT_ASSERT(Uses::IsStmtUsingVar(1, 0));
	CPPUNIT_ASSERT(Uses::IsStmtUsingVar(2, 0));
	CPPUNIT_ASSERT(Uses::IsStmtUsingVar(3, 0));
	CPPUNIT_ASSERT(Uses::IsStmtUsingVar(4, 0));

	vector<int> stmtsUsingVar0 = Uses::GetStmtUsingVar(0);
	CPPUNIT_ASSERT(stmtsUsingVar0.size() == 4);
	CPPUNIT_ASSERT(stmtsUsingVar0[0] == 1);
	CPPUNIT_ASSERT(stmtsUsingVar0[1] == 2);
	CPPUNIT_ASSERT(stmtsUsingVar0[2] == 3);
	CPPUNIT_ASSERT(stmtsUsingVar0[3] == 4);

	vector<int> varsUsedByStmt1 = Uses::GetVarUsedByStmt(1);
	CPPUNIT_ASSERT(varsUsedByStmt1.size() == 1);
	CPPUNIT_ASSERT(varsUsedByStmt1[0] == 0);

	vector<int> varsUsedByStmt2 = Uses::GetVarUsedByStmt(2);
	CPPUNIT_ASSERT(varsUsedByStmt2.size() == 1);
	CPPUNIT_ASSERT(varsUsedByStmt2[0] == 0);

	vector<int> varsUsedByStmt3 = Uses::GetVarUsedByStmt(3);
	CPPUNIT_ASSERT(varsUsedByStmt3.size() == 1);
	CPPUNIT_ASSERT(varsUsedByStmt3[0] == 0);

	vector<int> varsUsedByStmt4 = Uses::GetVarUsedByStmt(4);
	CPPUNIT_ASSERT(varsUsedByStmt4.size() == 1);
	CPPUNIT_ASSERT(varsUsedByStmt4[0] == 0);

	Uses::ClearData();
	CPPUNIT_ASSERT(Uses::HasAnyUses() == false);
}

void UsesTest::TestSingleStmtUsingMultipleVars() {
	Uses::ClearData();
	CPPUNIT_ASSERT(Uses::HasAnyUses() == false);

	Uses::SetStmtUsesVar(1, 0);
	Uses::SetStmtUsesVar(1, 1);
	Uses::SetStmtUsesVar(1, 2);
	Uses::SetStmtUsesVar(1, 3);

	CPPUNIT_ASSERT(Uses::HasAnyUses() == true);
	CPPUNIT_ASSERT(Uses::SizeOfUses() == 1);
	CPPUNIT_ASSERT(Uses::IsStmtUsingVar(1, 0));
	CPPUNIT_ASSERT(Uses::IsStmtUsingVar(1, 1));
	CPPUNIT_ASSERT(Uses::IsStmtUsingVar(1, 2));
	CPPUNIT_ASSERT(Uses::IsStmtUsingVar(1, 3));

	vector<int> stmtsUsingVar0 = Uses::GetStmtUsingVar(0);
	CPPUNIT_ASSERT(stmtsUsingVar0.size() == 1);
	CPPUNIT_ASSERT(stmtsUsingVar0[0] == 1);

	vector<int> stmtsUsingVar1 = Uses::GetStmtUsingVar(1);
	CPPUNIT_ASSERT(stmtsUsingVar1.size() == 1);
	CPPUNIT_ASSERT(stmtsUsingVar1[0] == 1);

	vector<int> stmtsUsingVar2 = Uses::GetStmtUsingVar(2);
	CPPUNIT_ASSERT(stmtsUsingVar2.size() == 1);
	CPPUNIT_ASSERT(stmtsUsingVar2[0] == 1);

	vector<int> stmtsUsingVar3 = Uses::GetStmtUsingVar(3);
	CPPUNIT_ASSERT(stmtsUsingVar3.size() == 1);
	CPPUNIT_ASSERT(stmtsUsingVar3[0] == 1);

	vector<int> varsUsedByStmt1 = Uses::GetVarUsedByStmt(1);
	CPPUNIT_ASSERT(varsUsedByStmt1.size() == 4);
	CPPUNIT_ASSERT(varsUsedByStmt1[0] == 0);
	CPPUNIT_ASSERT(varsUsedByStmt1[1] == 1);
	CPPUNIT_ASSERT(varsUsedByStmt1[2] == 2);
	CPPUNIT_ASSERT(varsUsedByStmt1[3] == 3);

	Uses::ClearData();
	CPPUNIT_ASSERT(Uses::HasAnyUses() == false);
}

void UsesTest::TestUses() {

}

