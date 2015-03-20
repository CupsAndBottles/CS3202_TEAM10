#include <cppunit\config\SourcePrefix.h>

#include "..\SPA\PKB\Affects.h"
#include "AffectsTest.h"
#include "..\SPA\PKB\StmtTypeTable.h"
#include "..\SPA\PKB\VarTable.h"
#include "..\SPA\PKB\Next.h"
#include "..\SPA\PKB\Modifies.h"
#include "..\SPA\PKB\Uses.h"

#include <iostream>

void AffectsTest::setUp() {
}

void AffectsTest::tearDown() {
}

CPPUNIT_TEST_SUITE_REGISTRATION(AffectsTest);

void AffectsTest::TestIsAffects() {
	ClearAllData();
	MimicCodeWithAssignOnly();

	CPPUNIT_ASSERT(Affects::IsAffects(1, 3));
	CPPUNIT_ASSERT(!Affects::IsAffects(2, 4));
	CPPUNIT_ASSERT(Affects::IsAffects(3, 4));
	CPPUNIT_ASSERT(!Affects::IsAffects(3, 5));

	ClearAllData();
	MimicCodeWithAssignWhile();

	CPPUNIT_ASSERT(Affects::IsAffects(1, 2));
	CPPUNIT_ASSERT(!Affects::IsAffects(1, 5));
	CPPUNIT_ASSERT(Affects::IsAffects(1, 6));

	CPPUNIT_ASSERT(Affects::IsAffects(6, 8));
	CPPUNIT_ASSERT(Affects::IsAffects(6, 10));

	ClearAllData();
	MimicCodeWithAssignIf();

	// var only modified in one of the 2 stmtLsts
	CPPUNIT_ASSERT(!Affects::IsAffects(1, 4));
	CPPUNIT_ASSERT(Affects::IsAffects(1, 6));
	CPPUNIT_ASSERT(Affects::IsAffects(1, 7));

	// var is modified in both stmtLsts
	CPPUNIT_ASSERT(!Affects::IsAffects(7, 10));
	CPPUNIT_ASSERT(!Affects::IsAffects(7, 12));
	CPPUNIT_ASSERT(!Affects::IsAffects(7, 13));

	// var is not modified in both stmtLsts
	CPPUNIT_ASSERT(Affects::IsAffects(13, 15));
	CPPUNIT_ASSERT(Affects::IsAffects(13, 16));
	CPPUNIT_ASSERT(Affects::IsAffects(13, 17));

	// misc odd cases
	CPPUNIT_ASSERT(!Affects::IsAffects(0, 1));
	CPPUNIT_ASSERT(!Affects::IsAffects(13, 18));

}

void AffectsTest::MimicCodeWithAssignOnly() {
	// 1. x = y + 4
	// 2. z = 2
	// 3. y = x + x
	// 4. y = 1 + y
	// 5. z = y + 2

	StmtTypeTable::Insert(1, ASSIGN);
	Modifies::SetStmtModifiesVar(1, VarTable::InsertVar("x"));
	Uses::SetStmtUsesVar(1, VarTable::InsertVar("y"));

	StmtTypeTable::Insert(2, ASSIGN);
	Modifies::SetStmtModifiesVar(2, VarTable::InsertVar("z"));

	StmtTypeTable::Insert(3, ASSIGN);
	Modifies::SetStmtModifiesVar(3, VarTable::InsertVar("y"));
	Uses::SetStmtUsesVar(3, VarTable::InsertVar("x"));

	StmtTypeTable::Insert(4, ASSIGN);
	Modifies::SetStmtModifiesVar(4, VarTable::InsertVar("y"));
	Uses::SetStmtUsesVar(4, VarTable::InsertVar("y"));

	StmtTypeTable::Insert(5, ASSIGN);
	Modifies::SetStmtModifiesVar(5, VarTable::InsertVar("z"));
	Uses::SetStmtUsesVar(5, VarTable::InsertVar("y"));

	Next::SetNext(1, 2);
	Next::SetNext(2, 3);
	Next::SetNext(3, 4);
	Next::SetNext(4, 5);

	cout << "\nSIMPLE-code-with-assign-only successfully created\n";

}

void AffectsTest::MimicCodeWithAssignWhile() {
	// 1.	a = b + c
	// 2.	b = a
	// 3.	while b {
	// 4.		a = 3
	// 5.		k = a }
	// 6.	x = y + z + a
	// 7.	while k {
	// 8.		k = x
	// 9.		k = a }
	// 10.	x = x

	StmtTypeTable::Insert(1, ASSIGN);
	Modifies::SetStmtModifiesVar(1, VarTable::InsertVar("a"));
	Uses::SetStmtUsesVar(1, VarTable::InsertVar("b"));
	Uses::SetStmtUsesVar(1, VarTable::InsertVar("c"));
	Next::SetNext(1, 2);

	StmtTypeTable::Insert(2, ASSIGN);
	Modifies::SetStmtModifiesVar(2, VarTable::InsertVar("b"));
	Uses::SetStmtUsesVar(2, VarTable::InsertVar("a"));
	Next::SetNext(2, 3);

	StmtTypeTable::Insert(3, WHILE);
	Modifies::SetStmtModifiesVar(3, VarTable::InsertVar("a"));
	Modifies::SetStmtModifiesVar(3, VarTable::InsertVar("k"));
	Uses::SetStmtUsesVar(3, VarTable::InsertVar("b"));
	Uses::SetStmtUsesVar(3, VarTable::InsertVar("a"));
	Next::SetNext(3, 4);
	Next::SetNext(3, 6);

	StmtTypeTable::Insert(4, ASSIGN);
	Modifies::SetStmtModifiesVar(4, VarTable::InsertVar("a"));
	Next::SetNext(4, 5);

	StmtTypeTable::Insert(5, ASSIGN);
	Modifies::SetStmtModifiesVar(5, VarTable::InsertVar("k"));
	Uses::SetStmtUsesVar(5, VarTable::InsertVar("a"));
	Next::SetNext(5, 6);

	StmtTypeTable::Insert(6, ASSIGN);
	Modifies::SetStmtModifiesVar(6, VarTable::InsertVar("x"));
	Uses::SetStmtUsesVar(6, VarTable::InsertVar("y"));
	Uses::SetStmtUsesVar(6, VarTable::InsertVar("z"));
	Uses::SetStmtUsesVar(6, VarTable::InsertVar("a"));
	Next::SetNext(6, 7);

	StmtTypeTable::Insert(7, WHILE);
	Modifies::SetStmtModifiesVar(7, VarTable::InsertVar("k"));
	Uses::SetStmtUsesVar(7, VarTable::InsertVar("k"));
	Uses::SetStmtUsesVar(7, VarTable::InsertVar("x"));
	Uses::SetStmtUsesVar(7, VarTable::InsertVar("a"));
	Next::SetNext(7, 8);
	Next::SetNext(7, 10);

	StmtTypeTable::Insert(8, ASSIGN);
	Modifies::SetStmtModifiesVar(8, VarTable::InsertVar("k"));
	Uses::SetStmtUsesVar(8, VarTable::InsertVar("x"));
	Next::SetNext(8, 9);

	StmtTypeTable::Insert(9, ASSIGN);
	Modifies::SetStmtModifiesVar(9, VarTable::InsertVar("k"));
	Uses::SetStmtUsesVar(9, VarTable::InsertVar("a"));
	Next::SetNext(9, 10);

	StmtTypeTable::Insert(10, ASSIGN);
	Modifies::SetStmtModifiesVar(10, VarTable::InsertVar("x"));
	Uses::SetStmtUsesVar(10, VarTable::InsertVar("x"));
	
	cout << "\nSIMPLE-code-with-assign-while successfully created\n";
}

void AffectsTest::MimicCodeWithAssignIf() {
	// 1.	a = 6
	// 2.	if b then {	// a only modified in one
	// 3.		a = 3
	// 4.		k = a }
	//		else {
	// 5.		k = x
	// 6.		k = a }
	// 7.	a = a + 2
	// 8.	if b then {	// a modified in both
	// 9.		a = 3
	// 10.		k = a }
	//		else {
	// 11.		a = 2
	// 12.		k = a }
	// 13.	a = a + 2
	// 14.	if b then {	// a modified in none
	// 15.		k = a }
	//		else {
	// 16.		h = a }
	// 17.	x = a

	StmtTypeTable::Insert(1, ASSIGN);
	Modifies::SetStmtModifiesVar(1, VarTable::InsertVar("a"));
	Next::SetNext(1, 2);

	StmtTypeTable::Insert(2, IF);
	Uses::SetStmtUsesVar(2, VarTable::InsertVar("b"));
	Modifies::SetStmtModifiesVar(2, VarTable::InsertVar("a"));
	Modifies::SetStmtModifiesVar(2, VarTable::InsertVar("k"));
	Uses::SetStmtUsesVar(2, VarTable::InsertVar("a"));
	Uses::SetStmtUsesVar(2, VarTable::InsertVar("x"));
	Next::SetNext(2, 3);
	Next::SetNext(2, 5);
	
	StmtTypeTable::Insert(3, ASSIGN);
	Modifies::SetStmtModifiesVar(3, VarTable::InsertVar("a"));
	Next::SetNext(3, 4);
	
	StmtTypeTable::Insert(4, ASSIGN);
	Modifies::SetStmtModifiesVar(4, VarTable::InsertVar("k"));
	Uses::SetStmtUsesVar(4, VarTable::InsertVar("a"));
	Next::SetNext(4, 7);

	StmtTypeTable::Insert(5, ASSIGN);
	Modifies::SetStmtModifiesVar(5, VarTable::InsertVar("k"));
	Uses::SetStmtUsesVar(5, VarTable::InsertVar("x"));
	Next::SetNext(5, 6);

	StmtTypeTable::Insert(6, ASSIGN);
	Modifies::SetStmtModifiesVar(6, VarTable::InsertVar("k"));
	Uses::SetStmtUsesVar(6, VarTable::InsertVar("a"));
	Next::SetNext(6, 7);

	StmtTypeTable::Insert(7, ASSIGN);
	Modifies::SetStmtModifiesVar(7, VarTable::InsertVar("a"));
	Uses::SetStmtUsesVar(7, VarTable::InsertVar("a"));
	Next::SetNext(7, 8);

	StmtTypeTable::Insert(8, IF);
	Uses::SetStmtUsesVar(8, VarTable::InsertVar("b"));
	Modifies::SetStmtModifiesVar(8, VarTable::InsertVar("a"));
	Modifies::SetStmtModifiesVar(8, VarTable::InsertVar("k"));
	Uses::SetStmtUsesVar(8, VarTable::InsertVar("a"));
	Next::SetNext(8, 9);
	Next::SetNext(8, 11);

	StmtTypeTable::Insert(9, ASSIGN);
	Modifies::SetStmtModifiesVar(9, VarTable::InsertVar("a"));
	Next::SetNext(9, 10);

	StmtTypeTable::Insert(10, ASSIGN);
	Modifies::SetStmtModifiesVar(10, VarTable::InsertVar("k"));
	Uses::SetStmtUsesVar(10, VarTable::InsertVar("a"));
	Next::SetNext(10, 13);
	
	StmtTypeTable::Insert(11, ASSIGN);
	Modifies::SetStmtModifiesVar(11, VarTable::InsertVar("a"));
	Next::SetNext(11, 12);

	StmtTypeTable::Insert(12, ASSIGN);
	Modifies::SetStmtModifiesVar(12, VarTable::InsertVar("k"));
	Uses::SetStmtUsesVar(12, VarTable::InsertVar("a"));
	Next::SetNext(12, 13);

	StmtTypeTable::Insert(13, ASSIGN);
	Modifies::SetStmtModifiesVar(13, VarTable::InsertVar("a"));
	Uses::SetStmtUsesVar(13, VarTable::InsertVar("a"));
	Next::SetNext(13, 14);

	StmtTypeTable::Insert(14, IF);
	Uses::SetStmtUsesVar(14, VarTable::InsertVar("b"));
	Modifies::SetStmtModifiesVar(14, VarTable::InsertVar("k"));
	Modifies::SetStmtModifiesVar(14, VarTable::InsertVar("h"));
	Uses::SetStmtUsesVar(14, VarTable::InsertVar("a"));
	Next::SetNext(14, 15);
	Next::SetNext(14, 16);

	StmtTypeTable::Insert(15, ASSIGN);
	Modifies::SetStmtModifiesVar(15, VarTable::InsertVar("k"));
	Uses::SetStmtUsesVar(15, VarTable::InsertVar("a"));
	Next::SetNext(15, 17);

	StmtTypeTable::Insert(16, ASSIGN);
	Modifies::SetStmtModifiesVar(16, VarTable::InsertVar("h"));
	Uses::SetStmtUsesVar(16, VarTable::InsertVar("a"));
	Next::SetNext(16, 17);
	
	StmtTypeTable::Insert(17, ASSIGN);
	Modifies::SetStmtModifiesVar(11, VarTable::InsertVar("x"));
	Uses::SetStmtUsesVar(17, VarTable::InsertVar("a"));

	cout << "\nSIMPLE-code-with-assign-if successfully created\n";
}

void AffectsTest::ClearAllData() {
	StmtTypeTable::ClearData();
	VarTable::ClearData();
	Next::ClearData();
	Modifies::ClearData();
	Uses::ClearData();
}