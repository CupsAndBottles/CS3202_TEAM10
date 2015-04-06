#include "ModifiesUsesCallsParentTest.h"
#include <cppunit\config\SourcePrefix.h>

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
#include "..\SPA\PKB\Calls.h"
#include "..\SPA\Program\Program.h"

#include <iostream>
#include <vector>
#include <string>
#include <stdint.h>
using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION(ModifiesUsesCallsParentTest);

const string TESTFILE_DIRECTORY = "ParserTestFiles/";

void ModifiesUsesCallsParentTest::setUp() { 
	VarTable::ClearData();
	StmtTypeTable::ClearData();
	Parent::ClearData();
	Follows::ClearData();
	Uses::ClearData();
	Modifies::ClearData();

	Parser::Parse(string(TESTFILE_DIRECTORY).append("ModifiesUsesCallsParentText.txt"));
}

void ModifiesUsesCallsParentTest::tearDown() {}

/*
void ModifiesUsesCallsParentTest::TestSelectAll(){
}
*/

void ModifiesUsesCallsParentTest::TestCallsUses(){
	// for all procedures p called by q, if p uses v then q uses v
	std::vector<string> ProcNames = ProcTable::GetAllProcNames();
	std::vector<string> VarNames = VarTable::GetAllVarNames();
	std::vector<int> CallStmts = StmtTypeTable::GetAllStmtsOfType(CALL);

	for each(string ProcTarget in ProcNames){
		for each(string VarName in VarNames){
			for each(string ProcSubject in ProcNames){ //q are proc
				bool called = Calls::IsCallsT( ProcTable::GetIndexOfProc(ProcSubject), ProcTable::GetIndexOfProc(ProcTarget) ) ;
				bool uses = Uses::IsProcUsingVar( ProcTable::GetIndexOfProc(ProcTarget),  VarTable::GetIndexOfVar(VarName) ) ;
				bool uses2 = Uses::IsProcUsingVar( ProcTable::GetIndexOfProc(ProcSubject),  VarTable::GetIndexOfVar(VarName) ) ;
				CPPUNIT_ASSERT(( called && uses ) == uses2 ); 
			}
			for each(int CallStmt in CallStmts){ //q are stmt
				bool called = Calls::IsCalls( CallStmt, ProcTable::GetIndexOfProc(ProcTarget) ) ;
				bool uses = Uses::IsProcUsingVar( ProcTable::GetIndexOfProc(ProcTarget),  VarTable::GetIndexOfVar(VarName) ) ;
				bool uses2 = Uses::IsStmtUsingVar( CallStmt,  VarTable::GetIndexOfVar(VarName) ) ;
				CPPUNIT_ASSERT(( called && uses ) == uses2 );
			}
		}	
	}
}

void ModifiesUsesCallsParentTest::TestCallsModifies(){
	// for all procedures p called by q, if p modifies v then q modifies v
	std::vector<string> ProcNames = ProcTable::GetAllProcNames();
	std::vector<string> VarNames = VarTable::GetAllVarNames();
	std::vector<int> CallStmts = StmtTypeTable::GetAllStmtsOfType(CALL);

	for each(string ProcTarget in ProcNames){
		for each(string VarName in VarNames){
			for each(string ProcSubject in ProcNames){ //q are proc
				bool called = Calls::IsCallsT( ProcTable::GetIndexOfProc(ProcSubject), ProcTable::GetIndexOfProc(ProcTarget) ) ;
				bool modifies = Modifies::IsProcModifyingVar( ProcTable::GetIndexOfProc(ProcTarget),  VarTable::GetIndexOfVar(VarName) ) ;
				bool modifies2 = Modifies::IsProcModifyingVar( ProcTable::GetIndexOfProc(ProcSubject),  VarTable::GetIndexOfVar(VarName) ) ;
				CPPUNIT_ASSERT(( called && modifies ) == modifies2 ); 
			}
			for each(int CallStmt in CallStmts){ //q are stmt
				bool called = Calls::IsCalls( CallStmt, ProcTable::GetIndexOfProc(ProcTarget) ) ;
				bool modifies = Modifies::IsProcModifyingVar( ProcTable::GetIndexOfProc(ProcTarget),  VarTable::GetIndexOfVar(VarName) ) ;
				bool modifies2 = Modifies::IsStmtModifyingVar( CallStmt,  VarTable::GetIndexOfVar(VarName) ) ;
				CPPUNIT_ASSERT(( called && modifies ) == modifies2 );
			}
		}	
	}
}


void ModifiesUsesCallsParentTest::TestParentUses(){
	// for all statements p parented by q, if p uses v then q uses v

	std::vector<string> VarNames = VarTable::GetAllVarNames();
	std::vector<int> AssignStmts = StmtTypeTable::GetAllStmtsOfType(ASSIGN);
	std::vector<int> WhileStmts = StmtTypeTable::GetAllStmtsOfType(WHILE);
	std::vector<int> IfStmts = StmtTypeTable::GetAllStmtsOfType(IF);
	std::vector<int> CallStmts = StmtTypeTable::GetAllStmtsOfType(CALL);

	std::vector<int> Statements;
	Statements.insert(Statements.end(),AssignStmts.begin(),AssignStmts.end());
	Statements.insert(Statements.end(),WhileStmts.begin(),WhileStmts.end());
	Statements.insert(Statements.end(),IfStmts.begin(),IfStmts.end());
	Statements.insert(Statements.end(),CallStmts.begin(),CallStmts.end());

	for each(int Statement in Statements){		
			int parent = Parent::GetParentOf(Statement);
			for each(string VarName in VarNames){
				bool parentOf = Parent::IsParent( parent, Statement ) ;
				bool uses = Uses::IsStmtUsingVar( Statement,  VarTable::GetIndexOfVar(VarName) ) ;
				bool uses2 = Uses::IsStmtUsingVar( parent,  VarTable::GetIndexOfVar(VarName) ) ;
				CPPUNIT_ASSERT(( parentOf && uses ) == uses2 );
			}
	}
}




void ModifiesUsesCallsParentTest::TestParentModifies(){
	// for all statements p parented by q, if p modifies v then q modifies v

	std::vector<string> VarNames = VarTable::GetAllVarNames();
	std::vector<int> AssignStmts = StmtTypeTable::GetAllStmtsOfType(ASSIGN);
	std::vector<int> WhileStmts = StmtTypeTable::GetAllStmtsOfType(WHILE);
	std::vector<int> IfStmts = StmtTypeTable::GetAllStmtsOfType(IF);
	std::vector<int> CallStmts = StmtTypeTable::GetAllStmtsOfType(CALL);

	std::vector<int> Statements;
	Statements.insert(Statements.end(),AssignStmts.begin(),AssignStmts.end());
	Statements.insert(Statements.end(),WhileStmts.begin(),WhileStmts.end());
	Statements.insert(Statements.end(),IfStmts.begin(),IfStmts.end());
	Statements.insert(Statements.end(),CallStmts.begin(),CallStmts.end());

	for each(int Statement in Statements){		
			int parent = Parent::GetParentOf(Statement);
			for each(string VarName in VarNames){
				bool parentOf = Parent::IsParent( parent, Statement ) ;
				bool modifies = Modifies::IsStmtModifyingVar( Statement,  VarTable::GetIndexOfVar(VarName) ) ;
				bool modifies2 = Modifies::IsStmtModifyingVar( parent,  VarTable::GetIndexOfVar(VarName) ) ;
				CPPUNIT_ASSERT(( parentOf && modifies ) == modifies2 );
			}
	}
}

/*
void ModifiesUsesCallsParentTest::TestCallsParent(){
}

void ModifiesUsesCallsParentTest::TestUsesModifies(){
}
*/