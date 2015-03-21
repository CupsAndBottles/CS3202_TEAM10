#include "Affects.h"
#include "StmtTypeTable.h"
#include "Next.h"
#include "Modifies.h"
#include "Uses.h"
#include "Follows.h"

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
					return CheckCFG(stmtAffecting, stmtAffected, varModified);
				}
			} 
		}
	}

	return false;

}

vector<int> Affects::GetStmtsAffectedBy(int stmtAffecting) {
	if(1 <= stmtAffecting && stmtAffecting <= StmtTypeTable::GetNoOfStmts()) {
		if (StmtTypeTable::CheckIfStmtOfType(stmtAffecting, ASSIGN)) {
			int varModified = Modifies::GetVarModifiedByStmt(stmtAffecting).at(0);
			return TraverseDownCFG(stmtAffecting, varModified);
		}	
	}

	vector<int> emptyVector;
	return emptyVector;

}

bool Affects::CheckCFG(int stmtAffecting, int stmtAffected, int varModified) {
	queue<int> uncheckedStmts;
	vector<bool> stmtsIsChecked(StmtTypeTable::GetNoOfStmts() + 1, false);
	
	vector<int> nextOfCurrStmt = Next::GetNextAfter(stmtAffecting);
	uncheckedStmts.push(nextOfCurrStmt.at(0));

	int currStmt, endOfIfElse;
	
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
				endOfIfElse = Follows::GetFollowsAfter(currStmt);
				
				if (stmtAffected < nextOfCurrStmt.at(1)) {
					if (!Modifies::IsStmtModifyingVar(currStmt, varModified)) {
						return true;
					} else {
						uncheckedStmts.push(nextOfCurrStmt.at(0));	
					}
				} else if (stmtAffected >= nextOfCurrStmt.at(1) && stmtAffected < endOfIfElse) {
					if (!Modifies::IsStmtModifyingVar(currStmt, varModified)) {
						return true;
					} else {
						uncheckedStmts.push(nextOfCurrStmt.at(1));	
					}
				} else if (stmtAffected >= endOfIfElse && !Modifies::IsStmtModifyingVar(currStmt, varModified)) {
					// skip all if-else
					uncheckedStmts.push(Follows::GetFollowsAfter(currStmt));
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

vector<int> Affects::TraverseDownCFG(int stmtAffecting, int varModified) {
	queue<int> uncheckedStmts;
	vector<bool> stmtsIsChecked(StmtTypeTable::GetNoOfStmts() + 1, false);
	
	vector<int> nextOfCurrStmt = Next::GetNextAfter(stmtAffecting);
	uncheckedStmts.push(nextOfCurrStmt.at(0));

	int currStmt;

	vector<int> affectedStmts;

	while (!uncheckedStmts.empty()) {
		currStmt = uncheckedStmts.front();
		//cout << "\n currStmt: " << currStmt << "\n";
		if (!stmtsIsChecked.at(currStmt)) {
			switch (StmtTypeTable::GetStmtTypeOf(currStmt)) {
			case ASSIGN:
				if (Uses::IsStmtUsingVar(currStmt, varModified)) {
					affectedStmts.push_back(currStmt);
				}
				
				if (Modifies::IsStmtModifyingVar(currStmt, varModified)) {
					// don't check for anything after this stmt
				} else {
					nextOfCurrStmt = Next::GetNextAfter(currStmt);
					if (!nextOfCurrStmt.empty()) {
						uncheckedStmts.push(nextOfCurrStmt.at(0));
					}
				}
				break;
			case WHILE:
				nextOfCurrStmt = Next::GetNextAfter(currStmt);
				if (Uses::IsStmtUsingVar(currStmt, varModified)) {
					// find a way to check that the used variable occurs in the stmtLst contained by while, 
					// not used as a control variable in while
					uncheckedStmts.push(nextOfCurrStmt.at(0));
				}
				uncheckedStmts.push(nextOfCurrStmt.at(1));
				break;
			case IF:
				nextOfCurrStmt = Next::GetNextAfter(currStmt);
				
				if (!Modifies::IsStmtModifyingVar(currStmt, varModified) && !Uses::IsStmtUsingVar(currStmt, varModified)) {
					uncheckedStmts.push(Follows::GetFollowsAfter(currStmt));
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
				break;
			}

			stmtsIsChecked.at(currStmt) = true;
		}
		
		uncheckedStmts.pop();

	}

	return affectedStmts;

}

Affects::~Affects(void) {
}
