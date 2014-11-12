#include "ModifiesTest.h"
#include "PKB\Modifies.h"

void ModifiesTest::setUp() {
	Modifies::ClearData();
}
void ModifiesTest::tearDown() {
	Modifies::ClearData();
}

CPPUNIT_TEST_SUITE_REGISTRATION(ModifiesTest);

ModifiesTest::ModifiesTest() {
}

void ModifiesTest::TestSingleStmt() {

	Modifies::ClearData();
	CPPUNIT_ASSERT(Modifies::HasAnyModifies() == false);

	Modifies::SetStmtModifiesVar(1, 0);

	CPPUNIT_ASSERT(Modifies::HasAnyModifies() == true);
	CPPUNIT_ASSERT(Modifies::SizeOfModifies() == 1);
	CPPUNIT_ASSERT(Modifies::IsStmtModifyingVar(1, 0));

	vector<int> stmtsModifyingVar0 = Modifies::GetStmtModifyingVar(0);
	CPPUNIT_ASSERT(stmtsModifyingVar0.size() == 1);
	CPPUNIT_ASSERT(stmtsModifyingVar0[0] == 1);

	vector<int> varsModifiedByStmt1 = Modifies::GetVarModifiedByStmt(1);
	CPPUNIT_ASSERT(varsModifiedByStmt1.size() == 1);
	CPPUNIT_ASSERT(varsModifiedByStmt1[0] == 0);

	Modifies::ClearData();
	CPPUNIT_ASSERT(Modifies::HasAnyModifies() == false);
}

void ModifiesTest::TestMultipleStmts() {
	Modifies::ClearData();
	CPPUNIT_ASSERT(Modifies::HasAnyModifies() == false);

	Modifies::SetStmtModifiesVar(1, 0);
	Modifies::SetStmtModifiesVar(2, 1);
	Modifies::SetStmtModifiesVar(3, 2);
	Modifies::SetStmtModifiesVar(4, 3);

	CPPUNIT_ASSERT(Modifies::HasAnyModifies() == true);
	CPPUNIT_ASSERT(Modifies::SizeOfModifies() == 4);
	CPPUNIT_ASSERT(Modifies::IsStmtModifyingVar(1, 0));
	CPPUNIT_ASSERT(Modifies::IsStmtModifyingVar(2, 1));
	CPPUNIT_ASSERT(Modifies::IsStmtModifyingVar(3, 2));
	CPPUNIT_ASSERT(Modifies::IsStmtModifyingVar(4, 3));

	vector<int> stmtsModifiesVar0 = Modifies::GetStmtModifyingVar(0);
	CPPUNIT_ASSERT(stmtsModifiesVar0.size() == 1);
	CPPUNIT_ASSERT(stmtsModifiesVar0[0] == 1);

	vector<int> stmtsModifiesVar1 = Modifies::GetStmtModifyingVar(1);
	CPPUNIT_ASSERT(stmtsModifiesVar1.size() == 1);
	CPPUNIT_ASSERT(stmtsModifiesVar1[0] == 2);

	vector<int> stmtsModifiesVar2 = Modifies::GetStmtModifyingVar(2);
	CPPUNIT_ASSERT(stmtsModifiesVar2.size() == 1);
	CPPUNIT_ASSERT(stmtsModifiesVar2[0] == 3);

	vector<int> stmtsModifiesVar3 = Modifies::GetStmtModifyingVar(3);
	CPPUNIT_ASSERT(stmtsModifiesVar3.size() == 1);
	CPPUNIT_ASSERT(stmtsModifiesVar3[0] == 4);

	vector<int> varsModifiedByStmt1 = Modifies::GetVarModifiedByStmt(1);
	CPPUNIT_ASSERT(varsModifiedByStmt1.size() == 1);
	CPPUNIT_ASSERT(varsModifiedByStmt1[0] == 0);

	vector<int> varsModifiedByStmt2 = Modifies::GetVarModifiedByStmt(2);
	CPPUNIT_ASSERT(varsModifiedByStmt2.size() == 1);
	CPPUNIT_ASSERT(varsModifiedByStmt2[0] == 1);

	vector<int> varsModifiedByStmt3 = Modifies::GetVarModifiedByStmt(3);
	CPPUNIT_ASSERT(varsModifiedByStmt3.size() == 1);
	CPPUNIT_ASSERT(varsModifiedByStmt3[0] == 2);

	vector<int> varsModifiedByStmt4 = Modifies::GetVarModifiedByStmt(4);
	CPPUNIT_ASSERT(varsModifiedByStmt4.size() == 1);
	CPPUNIT_ASSERT(varsModifiedByStmt4[0] == 3);

	Modifies::ClearData();
	CPPUNIT_ASSERT(Modifies::HasAnyModifies() == false);

}

void ModifiesTest::TestMultipleStmtsModifyingSingleVar() {

	Modifies::ClearData();
	CPPUNIT_ASSERT(Modifies::HasAnyModifies() == false);

	Modifies::SetStmtModifiesVar(1, 0);
	Modifies::SetStmtModifiesVar(2, 0);
	Modifies::SetStmtModifiesVar(3, 0);
	Modifies::SetStmtModifiesVar(4, 0);

	CPPUNIT_ASSERT(Modifies::HasAnyModifies() == true);
	CPPUNIT_ASSERT(Modifies::SizeOfModifies() == 4);
	CPPUNIT_ASSERT(Modifies::IsStmtModifyingVar(1, 0));
	CPPUNIT_ASSERT(Modifies::IsStmtModifyingVar(2, 0));
	CPPUNIT_ASSERT(Modifies::IsStmtModifyingVar(3, 0));
	CPPUNIT_ASSERT(Modifies::IsStmtModifyingVar(4, 0));

	vector<int> stmtsModifyingVar0 = Modifies::GetStmtModifyingVar(0);
	CPPUNIT_ASSERT(stmtsModifyingVar0.size() == 4);
	CPPUNIT_ASSERT(stmtsModifyingVar0[0] == 1);
	CPPUNIT_ASSERT(stmtsModifyingVar0[1] == 2);
	CPPUNIT_ASSERT(stmtsModifyingVar0[2] == 3);
	CPPUNIT_ASSERT(stmtsModifyingVar0[3] == 4);

	vector<int> varsModifiedByStmt1 = Modifies::GetVarModifiedByStmt(1);
	CPPUNIT_ASSERT(varsModifiedByStmt1.size() == 1);
	CPPUNIT_ASSERT(varsModifiedByStmt1[0] == 0);

	vector<int> varsModifiedByStmt2 = Modifies::GetVarModifiedByStmt(2);
	CPPUNIT_ASSERT(varsModifiedByStmt2.size() == 1);
	CPPUNIT_ASSERT(varsModifiedByStmt2[0] == 0);

	vector<int> varsModifiedByStmt3 = Modifies::GetVarModifiedByStmt(3);
	CPPUNIT_ASSERT(varsModifiedByStmt3.size() == 1);
	CPPUNIT_ASSERT(varsModifiedByStmt3[0] == 0);

	vector<int> varsModifiedByStmt4 = Modifies::GetVarModifiedByStmt(4);
	CPPUNIT_ASSERT(varsModifiedByStmt4.size() == 1);
	CPPUNIT_ASSERT(varsModifiedByStmt4[0] == 0);

	Modifies::ClearData();
	CPPUNIT_ASSERT(Modifies::HasAnyModifies() == false);
}

void ModifiesTest::TestSingleStmtModifyingMultipleVars() {

	Modifies::ClearData();
	CPPUNIT_ASSERT(Modifies::HasAnyModifies() == false);

	Modifies::SetStmtModifiesVar(1, 0);
	Modifies::SetStmtModifiesVar(1, 1);
	Modifies::SetStmtModifiesVar(1, 2);
	Modifies::SetStmtModifiesVar(1, 3);

	CPPUNIT_ASSERT(Modifies::HasAnyModifies() == true);
	CPPUNIT_ASSERT(Modifies::SizeOfModifies() == 1);
	CPPUNIT_ASSERT(Modifies::IsStmtModifyingVar(1, 0));
	CPPUNIT_ASSERT(Modifies::IsStmtModifyingVar(1, 1));
	CPPUNIT_ASSERT(Modifies::IsStmtModifyingVar(1, 2));
	CPPUNIT_ASSERT(Modifies::IsStmtModifyingVar(1, 3));

	vector<int> stmtsModifyingVar0 = Modifies::GetStmtModifyingVar(0);
	CPPUNIT_ASSERT(stmtsModifyingVar0.size() == 1);
	CPPUNIT_ASSERT(stmtsModifyingVar0[0] == 1);

	vector<int> stmtsModifyingVar1 = Modifies::GetStmtModifyingVar(1);
	CPPUNIT_ASSERT(stmtsModifyingVar1.size() == 1);
	CPPUNIT_ASSERT(stmtsModifyingVar1[0] == 1);

	vector<int> stmtsModifyingVar2 = Modifies::GetStmtModifyingVar(2);
	CPPUNIT_ASSERT(stmtsModifyingVar2.size() == 1);
	CPPUNIT_ASSERT(stmtsModifyingVar2[0] == 1);

	vector<int> stmtsModifyingVar3 = Modifies::GetStmtModifyingVar(3);
	CPPUNIT_ASSERT(stmtsModifyingVar3.size() == 1);
	CPPUNIT_ASSERT(stmtsModifyingVar3[0] == 1);

	vector<int> varsModifiedByStmt1 = Modifies::GetVarModifiedByStmt(1);
	CPPUNIT_ASSERT(varsModifiedByStmt1.size() == 4);
	CPPUNIT_ASSERT(varsModifiedByStmt1[0] == 0);
	CPPUNIT_ASSERT(varsModifiedByStmt1[1] == 1);
	CPPUNIT_ASSERT(varsModifiedByStmt1[2] == 2);
	CPPUNIT_ASSERT(varsModifiedByStmt1[3] == 3);

	Modifies::ClearData();
	CPPUNIT_ASSERT(Modifies::HasAnyModifies() == false);
}

void ModifiesTest::TestModifies() {
	Modifies::ClearData();
	CPPUNIT_ASSERT(Modifies::HasAnyModifies() == false);

	Modifies::SetStmtModifiesVar(1, 0);
	Modifies::SetStmtModifiesVar(2, 0);
	Modifies::SetStmtModifiesVar(3, 0);
	Modifies::SetStmtModifiesVar(4, 0);

	Modifies::SetStmtModifiesVar(1, 1);
	Modifies::SetStmtModifiesVar(2, 1);
	Modifies::SetStmtModifiesVar(3, 1);
	Modifies::SetStmtModifiesVar(4, 1);

	Modifies::SetStmtModifiesVar(1, 2);
	Modifies::SetStmtModifiesVar(2, 2);
	Modifies::SetStmtModifiesVar(3, 2);
	Modifies::SetStmtModifiesVar(4, 2);

	Modifies::SetStmtModifiesVar(1, 3);
	Modifies::SetStmtModifiesVar(2, 3);
	Modifies::SetStmtModifiesVar(3, 3);
	Modifies::SetStmtModifiesVar(4, 3);

	Modifies::SetStmtModifiesVar(5, 4);
	Modifies::SetStmtModifiesVar(10, 15);

	CPPUNIT_ASSERT(Modifies::HasAnyModifies() == true);
	CPPUNIT_ASSERT(Modifies::SizeOfModifies() == 6);

	CPPUNIT_ASSERT(Modifies::IsStmtModifyingVar(1, 0));
	CPPUNIT_ASSERT(Modifies::IsStmtModifyingVar(1, 1));
	CPPUNIT_ASSERT(Modifies::IsStmtModifyingVar(1, 2));
	CPPUNIT_ASSERT(Modifies::IsStmtModifyingVar(1, 3));

	CPPUNIT_ASSERT(Modifies::IsStmtModifyingVar(2, 0));
	CPPUNIT_ASSERT(Modifies::IsStmtModifyingVar(2, 1));
	CPPUNIT_ASSERT(Modifies::IsStmtModifyingVar(2, 2));
	CPPUNIT_ASSERT(Modifies::IsStmtModifyingVar(2, 3));

	CPPUNIT_ASSERT(Modifies::IsStmtModifyingVar(3, 0));
	CPPUNIT_ASSERT(Modifies::IsStmtModifyingVar(3, 1));
	CPPUNIT_ASSERT(Modifies::IsStmtModifyingVar(3, 2));
	CPPUNIT_ASSERT(Modifies::IsStmtModifyingVar(3, 3));

	CPPUNIT_ASSERT(Modifies::IsStmtModifyingVar(4, 0));
	CPPUNIT_ASSERT(Modifies::IsStmtModifyingVar(4, 1));
	CPPUNIT_ASSERT(Modifies::IsStmtModifyingVar(4, 2));
	CPPUNIT_ASSERT(Modifies::IsStmtModifyingVar(4, 3));

	CPPUNIT_ASSERT(Modifies::IsStmtModifyingVar(5, 4));
	CPPUNIT_ASSERT(Modifies::IsStmtModifyingVar(10, 15));

	vector<int> stmtsModifyingVar0 = Modifies::GetStmtModifyingVar(0);
	CPPUNIT_ASSERT(stmtsModifyingVar0.size() == 4);
	CPPUNIT_ASSERT(stmtsModifyingVar0[0] == 1);
	CPPUNIT_ASSERT(stmtsModifyingVar0[1] == 2);
	CPPUNIT_ASSERT(stmtsModifyingVar0[2] == 3);
	CPPUNIT_ASSERT(stmtsModifyingVar0[3] == 4);

	vector<int> stmtsModifyingVar1 = Modifies::GetStmtModifyingVar(1);
	CPPUNIT_ASSERT(stmtsModifyingVar1.size() == 4);
	CPPUNIT_ASSERT(stmtsModifyingVar1[0] == 1);
	CPPUNIT_ASSERT(stmtsModifyingVar1[1] == 2);
	CPPUNIT_ASSERT(stmtsModifyingVar1[2] == 3);
	CPPUNIT_ASSERT(stmtsModifyingVar1[3] == 4);

	vector<int> stmtsModifyingVar2 = Modifies::GetStmtModifyingVar(2);
	CPPUNIT_ASSERT(stmtsModifyingVar2.size() == 4);
	CPPUNIT_ASSERT(stmtsModifyingVar2[0] == 1);
	CPPUNIT_ASSERT(stmtsModifyingVar2[1] == 2);
	CPPUNIT_ASSERT(stmtsModifyingVar2[2] == 3);
	CPPUNIT_ASSERT(stmtsModifyingVar2[3] == 4);

	vector<int> stmtsModifyingVar3 = Modifies::GetStmtModifyingVar(3);
	CPPUNIT_ASSERT(stmtsModifyingVar3.size() == 4);
	CPPUNIT_ASSERT(stmtsModifyingVar3[0] == 1);
	CPPUNIT_ASSERT(stmtsModifyingVar3[1] == 2);
	CPPUNIT_ASSERT(stmtsModifyingVar3[2] == 3);
	CPPUNIT_ASSERT(stmtsModifyingVar3[3] == 4);

	vector<int> stmtsModifyingVar4 = Modifies::GetStmtModifyingVar(4);
	CPPUNIT_ASSERT(stmtsModifyingVar4.size() == 1);
	CPPUNIT_ASSERT(stmtsModifyingVar4[0] == 5);

	vector<int> stmtsModifyingVar15 = Modifies::GetStmtModifyingVar(15);
	CPPUNIT_ASSERT(stmtsModifyingVar15.size() == 1);
	CPPUNIT_ASSERT(stmtsModifyingVar15[0] == 10);

	vector<int> varsModifiedByStmt1 = Modifies::GetVarModifiedByStmt(1);
	CPPUNIT_ASSERT(varsModifiedByStmt1.size() == 4);
	CPPUNIT_ASSERT(varsModifiedByStmt1[0] == 0);
	CPPUNIT_ASSERT(varsModifiedByStmt1[1] == 1);
	CPPUNIT_ASSERT(varsModifiedByStmt1[2] == 2);
	CPPUNIT_ASSERT(varsModifiedByStmt1[3] == 3);

	vector<int> varsModifiedByStmt2 = Modifies::GetVarModifiedByStmt(2);
	CPPUNIT_ASSERT(varsModifiedByStmt2.size() == 4);
	CPPUNIT_ASSERT(varsModifiedByStmt2[0] == 0);
	CPPUNIT_ASSERT(varsModifiedByStmt2[1] == 1);
	CPPUNIT_ASSERT(varsModifiedByStmt2[2] == 2);
	CPPUNIT_ASSERT(varsModifiedByStmt2[3] == 3);

	vector<int> varsModifiedByStmt3 = Modifies::GetVarModifiedByStmt(3);
	CPPUNIT_ASSERT(varsModifiedByStmt3.size() == 4);
	CPPUNIT_ASSERT(varsModifiedByStmt3[0] == 0);
	CPPUNIT_ASSERT(varsModifiedByStmt3[1] == 1);
	CPPUNIT_ASSERT(varsModifiedByStmt3[2] == 2);
	CPPUNIT_ASSERT(varsModifiedByStmt3[3] == 3);

	vector<int> varsModifiedByStmt4 = Modifies::GetVarModifiedByStmt(4);
	CPPUNIT_ASSERT(varsModifiedByStmt4.size() == 4);
	CPPUNIT_ASSERT(varsModifiedByStmt4[0] == 0);
	CPPUNIT_ASSERT(varsModifiedByStmt4[1] == 1);
	CPPUNIT_ASSERT(varsModifiedByStmt4[2] == 2);
	CPPUNIT_ASSERT(varsModifiedByStmt4[3] == 3);

	vector<int> varsModifiedByStmt5 = Modifies::GetVarModifiedByStmt(5);
	CPPUNIT_ASSERT(varsModifiedByStmt5.size() == 1);
	CPPUNIT_ASSERT(varsModifiedByStmt5[0] == 4);

	vector<int> varsModifiedByStmt10 = Modifies::GetVarModifiedByStmt(10);
	CPPUNIT_ASSERT(varsModifiedByStmt10.size() == 1);
	CPPUNIT_ASSERT(varsModifiedByStmt10[0] == 15);

	Modifies::ClearData();
	CPPUNIT_ASSERT(Modifies::HasAnyModifies() == false);


}
