#include "Affects.h"
#include "StmtTypeTable.h"
#include "Next.h"
#include "Modifies.h"
#include "Uses.h"

#include <iostream>

Affects::Affects(void) {
}

bool Affects::IsAffects(int stmtAffecting, int stmtAffected) {
	if (1 <= stmtAffecting && 1 <= stmtAffected && stmtAffecting <= StmtTypeTable::GetNoOfStmts() && stmtAffected <= StmtTypeTable::GetNoOfStmts()) {
		if (StmtTypeTable::CheckIfStmtOfType(stmtAffecting, ASSIGN) && StmtTypeTable::CheckIfStmtOfType(stmtAffected, ASSIGN)) {
			vector<int> modifiedVars = Modifies::GetVarModifiedByStmt(stmtAffecting);
			if (!modifiedVars.empty()) {
				int varModified = modifiedVars.at(0);
				if (Uses::IsStmtUsingVar(stmtAffected, varModified)) {
					return TraverseCFG(stmtAffecting, stmtAffected, varModified);
				}
			} 
		}
	}

	return false;

}

bool Affects::TraverseCFG(int stmtAffecting, int stmtAffected, int varModified) {
	queue<int> uncheckedStmts;
	vector<bool> stmtsIsChecked(StmtTypeTable::GetNoOfStmts() + 1, false);
	
	vector<int> nextOfCurrStmt = Next::GetNextAfter(stmtAffecting);
	uncheckedStmts.push(nextOfCurrStmt.at(0));

	int currStmt;
	

	while (!uncheckedStmts.empty()) {
		currStmt = uncheckedStmts.front();

		if (!stmtsIsChecked.at(currStmt)) {
			switch (StmtTypeTable::GetStmtTypeOf(currStmt)) {
			case ASSIGN:
				if (currStmt == stmtAffected) {
					return true;
				}
				
				if (Modifies::IsStmtModifyingVar(currStmt, varModified)) {
					// don't check for anything after this stmt
				} else {
					nextOfCurrStmt = Next::GetNextAfter(currStmt);
					uncheckedStmts.push(nextOfCurrStmt.at(0));
				}	
				break;
			case WHILE:
				nextOfCurrStmt = Next::GetNextAfter(currStmt);
				if (stmtAffected >= nextOfCurrStmt.at(1)) {
					uncheckedStmts.push(nextOfCurrStmt.at(1));
				} else if (stmtAffected < nextOfCurrStmt.at(1) && !Modifies::IsStmtModifyingVar(currStmt, varModified)) {
					return true;
				} else {
					uncheckedStmts.push(nextOfCurrStmt.at(0));
				}
				break;
			case IF:
				nextOfCurrStmt = Next::GetNextAfter(currStmt);
				if (stmtAffected < nextOfCurrStmt.at(1) && !Modifies::IsStmtModifyingVar(currStmt, varModified)) {
					return true;
				} else if (stmtAffected < nextOfCurrStmt.at(1)) {
					uncheckedStmts.push(nextOfCurrStmt.at(1));
				} else if (stmtAffected >= nextOfCurrStmt.at(1) && !Modifies::IsStmtModifyingVar(currStmt, varModified)) {
					// find a way to skip out of if-else segment and push the next stmt to check in
					// longer method:
					uncheckedStmts.push(nextOfCurrStmt.at(0));
					uncheckedStmts.push(nextOfCurrStmt.at(1));
				} else {
					uncheckedStmts.push(nextOfCurrStmt.at(0));
					uncheckedStmts.push(nextOfCurrStmt.at(1));
				}
				break;
			case CALL:
				nextOfCurrStmt = Next::GetNextAfter(currStmt);
				uncheckedStmts.push(nextOfCurrStmt.at(0));
				break;
			default:
				//1. "longer method, without using bitvector"
				//2. do bit vector optimisaion of while and if
				return false;
			}

			stmtsIsChecked.at(currStmt) = true;
		}
		
		uncheckedStmts.pop();

	}

	return false;

}

Affects::~Affects(void) {
}
