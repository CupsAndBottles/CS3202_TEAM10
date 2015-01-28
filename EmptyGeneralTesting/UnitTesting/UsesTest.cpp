#include "UsesTest.h"
#include "..\SPA\PKB\Uses.h"
#include "..\SPA\PKB\Parent.h"

void UsesTest::setUp() { 
	Uses::ClearData();
	Parent::ClearData();
}

void UsesTest::tearDown() {
	Uses::ClearData();
}

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

	vector<unsigned int> stmtsUsingVar0 = Uses::GetStmtUsingVar(0);
	CPPUNIT_ASSERT(stmtsUsingVar0.size() == 1);
	CPPUNIT_ASSERT(stmtsUsingVar0[0] == 1);

	vector<unsigned int> varsUsedByStmt1 = Uses::GetVarUsedByStmt(1);
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

	vector<unsigned int> stmtsUsingVar0 = Uses::GetStmtUsingVar(0);
	CPPUNIT_ASSERT_EQUAL(1, (unsigned int)stmtsUsingVar0.size());
	CPPUNIT_ASSERT_EQUAL(1, stmtsUsingVar0[0]);

	vector<unsigned int> stmtsUsingVar1 = Uses::GetStmtUsingVar(1);
	CPPUNIT_ASSERT_EQUAL(1, (unsigned int)stmtsUsingVar1.size());
	CPPUNIT_ASSERT(stmtsUsingVar1[0] == 2);

	vector<unsigned int> stmtsUsingVar2 = Uses::GetStmtUsingVar(2);
	CPPUNIT_ASSERT(stmtsUsingVar2.size() == 1);
	CPPUNIT_ASSERT(stmtsUsingVar2[0] == 3);

	vector<unsigned int> stmtsUsingVar3 = Uses::GetStmtUsingVar(3);
	CPPUNIT_ASSERT(stmtsUsingVar3.size() == 1);
	CPPUNIT_ASSERT(stmtsUsingVar3[0] == 4);

	vector<unsigned int> varsUsedByStmt1 = Uses::GetVarUsedByStmt(1);
	CPPUNIT_ASSERT(varsUsedByStmt1.size() == 1);
	CPPUNIT_ASSERT(varsUsedByStmt1[0] == 0);

	vector<unsigned int> varsUsedByStmt2 = Uses::GetVarUsedByStmt(2);
	CPPUNIT_ASSERT(varsUsedByStmt2.size() == 1);
	CPPUNIT_ASSERT(varsUsedByStmt2[0] == 1);

	vector<unsigned int> varsUsedByStmt3 = Uses::GetVarUsedByStmt(3);
	CPPUNIT_ASSERT(varsUsedByStmt3.size() == 1);
	CPPUNIT_ASSERT(varsUsedByStmt3[0] == 2);

	vector<unsigned int> varsUsedByStmt4 = Uses::GetVarUsedByStmt(4);
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

	vector<unsigned int> stmtsUsingVar0 = Uses::GetStmtUsingVar(0);
	CPPUNIT_ASSERT(stmtsUsingVar0.size() == 4);
	CPPUNIT_ASSERT(stmtsUsingVar0[0] == 1);
	CPPUNIT_ASSERT(stmtsUsingVar0[1] == 2);
	CPPUNIT_ASSERT(stmtsUsingVar0[2] == 3);
	CPPUNIT_ASSERT(stmtsUsingVar0[3] == 4);

	vector<unsigned int> varsUsedByStmt1 = Uses::GetVarUsedByStmt(1);
	CPPUNIT_ASSERT(varsUsedByStmt1.size() == 1);
	CPPUNIT_ASSERT(varsUsedByStmt1[0] == 0);

	vector<unsigned int> varsUsedByStmt2 = Uses::GetVarUsedByStmt(2);
	CPPUNIT_ASSERT(varsUsedByStmt2.size() == 1);
	CPPUNIT_ASSERT(varsUsedByStmt2[0] == 0);

	vector<unsigned int> varsUsedByStmt3 = Uses::GetVarUsedByStmt(3);
	CPPUNIT_ASSERT(varsUsedByStmt3.size() == 1);
	CPPUNIT_ASSERT(varsUsedByStmt3[0] == 0);

	vector<unsigned int> varsUsedByStmt4 = Uses::GetVarUsedByStmt(4);
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
	CPPUNIT_ASSERT(Uses::SizeOfUses() == 4);
	CPPUNIT_ASSERT(Uses::IsStmtUsingVar(1, 0));
	CPPUNIT_ASSERT(Uses::IsStmtUsingVar(1, 1));
	CPPUNIT_ASSERT(Uses::IsStmtUsingVar(1, 2));
	CPPUNIT_ASSERT(Uses::IsStmtUsingVar(1, 3));

	vector<unsigned int> stmtsUsingVar0 = Uses::GetStmtUsingVar(0);
	CPPUNIT_ASSERT(stmtsUsingVar0.size() == 1);
	CPPUNIT_ASSERT(stmtsUsingVar0[0] == 1);

	vector<unsigned int> stmtsUsingVar1 = Uses::GetStmtUsingVar(1);
	CPPUNIT_ASSERT(stmtsUsingVar1.size() == 1);
	CPPUNIT_ASSERT(stmtsUsingVar1[0] == 1);

	vector<unsigned int> stmtsUsingVar2 = Uses::GetStmtUsingVar(2);
	CPPUNIT_ASSERT(stmtsUsingVar2.size() == 1);
	CPPUNIT_ASSERT(stmtsUsingVar2[0] == 1);

	vector<unsigned int> stmtsUsingVar3 = Uses::GetStmtUsingVar(3);
	CPPUNIT_ASSERT(stmtsUsingVar3.size() == 1);
	CPPUNIT_ASSERT(stmtsUsingVar3[0] == 1);

	vector<unsigned int> varsUsedByStmt1 = Uses::GetVarUsedByStmt(1);
	CPPUNIT_ASSERT(varsUsedByStmt1.size() == 4);
	CPPUNIT_ASSERT(varsUsedByStmt1[0] == 0);
	CPPUNIT_ASSERT(varsUsedByStmt1[1] == 1);
	CPPUNIT_ASSERT(varsUsedByStmt1[2] == 2);
	CPPUNIT_ASSERT(varsUsedByStmt1[3] == 3);

	Uses::ClearData();
	CPPUNIT_ASSERT(Uses::HasAnyUses() == false);
}

void UsesTest::TestUses() {
	Uses::ClearData();
	CPPUNIT_ASSERT(Uses::HasAnyUses() == false);

	Uses::SetStmtUsesVar(1, 0);
	Uses::SetStmtUsesVar(2, 0);
	Uses::SetStmtUsesVar(3, 0);
	Uses::SetStmtUsesVar(4, 0);

	Uses::SetStmtUsesVar(1, 1);
	Uses::SetStmtUsesVar(2, 1);
	Uses::SetStmtUsesVar(3, 1);
	Uses::SetStmtUsesVar(4, 1);

	Uses::SetStmtUsesVar(1, 2);
	Uses::SetStmtUsesVar(2, 2);
	Uses::SetStmtUsesVar(3, 2);
	Uses::SetStmtUsesVar(4, 2);

	Uses::SetStmtUsesVar(1, 3);
	Uses::SetStmtUsesVar(2, 3);
	Uses::SetStmtUsesVar(3, 3);
	Uses::SetStmtUsesVar(4, 3);

	Uses::SetStmtUsesVar(5, 4);
	Uses::SetStmtUsesVar(10, 15);

	CPPUNIT_ASSERT(Uses::HasAnyUses() == true);
	CPPUNIT_ASSERT(Uses::SizeOfUses() == 18);

	CPPUNIT_ASSERT(Uses::IsStmtUsingVar(1, 0));
	CPPUNIT_ASSERT(Uses::IsStmtUsingVar(1, 1));
	CPPUNIT_ASSERT(Uses::IsStmtUsingVar(1, 2));
	CPPUNIT_ASSERT(Uses::IsStmtUsingVar(1, 3));

	CPPUNIT_ASSERT(Uses::IsStmtUsingVar(2, 0));
	CPPUNIT_ASSERT(Uses::IsStmtUsingVar(2, 1));
	CPPUNIT_ASSERT(Uses::IsStmtUsingVar(2, 2));
	CPPUNIT_ASSERT(Uses::IsStmtUsingVar(2, 3));

	CPPUNIT_ASSERT(Uses::IsStmtUsingVar(3, 0));
	CPPUNIT_ASSERT(Uses::IsStmtUsingVar(3, 1));
	CPPUNIT_ASSERT(Uses::IsStmtUsingVar(3, 2));
	CPPUNIT_ASSERT(Uses::IsStmtUsingVar(3, 3));

	CPPUNIT_ASSERT(Uses::IsStmtUsingVar(4, 0));
	CPPUNIT_ASSERT(Uses::IsStmtUsingVar(4, 1));
	CPPUNIT_ASSERT(Uses::IsStmtUsingVar(4, 2));
	CPPUNIT_ASSERT(Uses::IsStmtUsingVar(4, 3));

	CPPUNIT_ASSERT(Uses::IsStmtUsingVar(5, 4));
	CPPUNIT_ASSERT(Uses::IsStmtUsingVar(10, 15));

	vector<unsigned int> stmtsUsingVar0 = Uses::GetStmtUsingVar(0);
	CPPUNIT_ASSERT(stmtsUsingVar0.size() == 4);
	CPPUNIT_ASSERT(stmtsUsingVar0[0] == 1);
	CPPUNIT_ASSERT(stmtsUsingVar0[1] == 2);
	CPPUNIT_ASSERT(stmtsUsingVar0[2] == 3);
	CPPUNIT_ASSERT(stmtsUsingVar0[3] == 4);

	vector<unsigned int> stmtsUsingVar1 = Uses::GetStmtUsingVar(1);
	CPPUNIT_ASSERT(stmtsUsingVar1.size() == 4);
	CPPUNIT_ASSERT(stmtsUsingVar1[0] == 1);
	CPPUNIT_ASSERT(stmtsUsingVar1[1] == 2);
	CPPUNIT_ASSERT(stmtsUsingVar1[2] == 3);
	CPPUNIT_ASSERT(stmtsUsingVar1[3] == 4);

	vector<unsigned int> stmtsUsingVar2 = Uses::GetStmtUsingVar(2);
	CPPUNIT_ASSERT(stmtsUsingVar2.size() == 4);
	CPPUNIT_ASSERT(stmtsUsingVar2[0] == 1);
	CPPUNIT_ASSERT(stmtsUsingVar2[1] == 2);
	CPPUNIT_ASSERT(stmtsUsingVar2[2] == 3);
	CPPUNIT_ASSERT(stmtsUsingVar2[3] == 4);

	vector<unsigned int> stmtsUsingVar3 = Uses::GetStmtUsingVar(3);
	CPPUNIT_ASSERT(stmtsUsingVar3.size() == 4);
	CPPUNIT_ASSERT(stmtsUsingVar3[0] == 1);
	CPPUNIT_ASSERT(stmtsUsingVar3[1] == 2);
	CPPUNIT_ASSERT(stmtsUsingVar3[2] == 3);
	CPPUNIT_ASSERT(stmtsUsingVar3[3] == 4);

	vector<unsigned int> stmtsUsingVar4 = Uses::GetStmtUsingVar(4);
	CPPUNIT_ASSERT(stmtsUsingVar4.size() == 1);
	CPPUNIT_ASSERT(stmtsUsingVar4[0] == 5);

	vector<unsigned int> stmtsUsingVar15 = Uses::GetStmtUsingVar(15);
	CPPUNIT_ASSERT(stmtsUsingVar15.size() == 1);
	CPPUNIT_ASSERT(stmtsUsingVar15[0] == 10);

	vector<unsigned int> varsUsedByStmt1 = Uses::GetVarUsedByStmt(1);
	CPPUNIT_ASSERT(varsUsedByStmt1.size() == 4);
	CPPUNIT_ASSERT(varsUsedByStmt1[0] == 0);
	CPPUNIT_ASSERT(varsUsedByStmt1[1] == 1);
	CPPUNIT_ASSERT(varsUsedByStmt1[2] == 2);
	CPPUNIT_ASSERT(varsUsedByStmt1[3] == 3);

	vector<unsigned int> varsUsedByStmt2 = Uses::GetVarUsedByStmt(2);
	CPPUNIT_ASSERT(varsUsedByStmt2.size() == 4);
	CPPUNIT_ASSERT(varsUsedByStmt2[0] == 0);
	CPPUNIT_ASSERT(varsUsedByStmt2[1] == 1);
	CPPUNIT_ASSERT(varsUsedByStmt2[2] == 2);
	CPPUNIT_ASSERT(varsUsedByStmt2[3] == 3);

	vector<unsigned int> varsUsedByStmt3 = Uses::GetVarUsedByStmt(3);
	CPPUNIT_ASSERT(varsUsedByStmt3.size() == 4);
	CPPUNIT_ASSERT(varsUsedByStmt3[0] == 0);
	CPPUNIT_ASSERT(varsUsedByStmt3[1] == 1);
	CPPUNIT_ASSERT(varsUsedByStmt3[2] == 2);
	CPPUNIT_ASSERT(varsUsedByStmt3[3] == 3);

	vector<unsigned int> varsUsedByStmt4 = Uses::GetVarUsedByStmt(4);
	CPPUNIT_ASSERT(varsUsedByStmt4.size() == 4);
	CPPUNIT_ASSERT(varsUsedByStmt4[0] == 0);
	CPPUNIT_ASSERT(varsUsedByStmt4[1] == 1);
	CPPUNIT_ASSERT(varsUsedByStmt4[2] == 2);
	CPPUNIT_ASSERT(varsUsedByStmt4[3] == 3);

	vector<unsigned int> varsUsedByStmt5 = Uses::GetVarUsedByStmt(5);
	CPPUNIT_ASSERT(varsUsedByStmt5.size() == 1);
	CPPUNIT_ASSERT(varsUsedByStmt5[0] == 4);

	vector<unsigned int> varsUsedByStmt10 = Uses::GetVarUsedByStmt(10);
	CPPUNIT_ASSERT(varsUsedByStmt10.size() == 1);
	CPPUNIT_ASSERT(varsUsedByStmt10[0] == 15);

	Uses::ClearData();
	CPPUNIT_ASSERT(Uses::HasAnyUses() == false);

}

