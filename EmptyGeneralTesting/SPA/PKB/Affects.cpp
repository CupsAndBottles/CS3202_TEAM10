#include "Affects.h"
#include "StmtTypeTable.h"
#include "Next.h"
#include "Modifies.h"
#include "Uses.h"
#include "Follows.h"
//#include "VarTable.h"

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

vector<int> Affects::GetStmtsAffecting(int stmtAffected) {
	if(1 <= stmtAffected && stmtAffected <= StmtTypeTable::GetNoOfStmts()) {
		if (StmtTypeTable::CheckIfStmtOfType(stmtAffected, ASSIGN)) {
			vector<int> varsUsed = Uses::GetVarUsedByStmt(stmtAffected);
			return TraverseUpCFG(stmtAffected, varsUsed);
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

vector<int> Affects::TraverseUpCFG(int stmtAffected, vector<int> varsUsed) {
	vector<bool> stmtsIsChecked(StmtTypeTable::GetNoOfStmts() + 1, false);
	vector<int> nextBeforeCurrStmt = Next::GetNextBefore(stmtAffected);
	vector<int> affectedStmts;
	
	if (!varsUsed.empty()) {
		for (vector<int>::iterator it = nextBeforeCurrStmt.begin(); it != nextBeforeCurrStmt.end(); it++) {
			pair<vector<int>, vector<bool>> subAns = RecurTraverseUpCFG(*it, varsUsed, stmtsIsChecked);
			vector<int> subAffectedStmts = subAns.first;
			affectedStmts = OrOperationOnVects(affectedStmts, subAffectedStmts);
			vector<bool> subStmtsIsChecked = subAns.second;
			subStmtsIsChecked = OrOperationOnBoolVects(subStmtsIsChecked, stmtsIsChecked);
		}
	
	}

	return affectedStmts;
}

pair<vector<int>, vector<bool>> Affects::RecurTraverseUpCFG(int currStmt, vector<int> varsUsed, vector<bool> stmtsIsChecked) {
	vector<int> affectedStmts;
	vector<int> nextBeforeCurrStmt = Next::GetNextBefore(currStmt);

	//cout << "\n currStmt: " << currStmt << "\n";

	switch(StmtTypeTable::GetStmtTypeOf(currStmt)) {
	case ASSIGN: {
		if (!stmtsIsChecked.at(currStmt)) {
			int varModified = Modifies::GetVarModifiedByStmt(currStmt).at(0);
			vector<int>::iterator it = varsUsed.begin();
			while (it != varsUsed.end()) {
				if (varModified == *it) {
					affectedStmts.push_back(currStmt);
					it = varsUsed.erase(it);
				} else {
					it++;
				}
			}
			stmtsIsChecked.at(currStmt) = true;
		} else {
			nextBeforeCurrStmt.clear();
		}
	} break;
	case WHILE: {
		vector<int>::iterator it = nextBeforeCurrStmt.begin();
		if (!stmtsIsChecked.at(currStmt)) {
			while (it != nextBeforeCurrStmt.end()) {
				if (*it > currStmt) {
					nextBeforeCurrStmt.erase(it, nextBeforeCurrStmt.end());
					it = nextBeforeCurrStmt.end();
				} else {
					it++;
				}
			}
			stmtsIsChecked.at(currStmt) = true;
		} else {
			nextBeforeCurrStmt.clear();
		}

	} break;
	case IF: {
		vector<int> nextAfterIf = Next::GetNextAfter(currStmt);
		if ((int) nextAfterIf.size() == 2) {
			if (stmtsIsChecked.at(nextAfterIf.at(0)) && stmtsIsChecked.at(nextAfterIf.at(1))) {
				stmtsIsChecked.at(currStmt) = true;
			} 
		}
	}
	case CALL:
		stmtsIsChecked.at(currStmt) = true;
		break;
	default:
		cout << "unable to determine stmttype of stmt# " << currStmt;
		break;
	}

	if (!varsUsed.empty()) {
		for (vector<int>::iterator it = nextBeforeCurrStmt.begin(); it != nextBeforeCurrStmt.end(); it++) {
			pair<vector<int>, vector<bool>> subAns = RecurTraverseUpCFG(*it, varsUsed, stmtsIsChecked);
			vector<int> subAffectedStmts = subAns.first;
			affectedStmts = OrOperationOnVects(affectedStmts, subAffectedStmts);
			vector<bool> subStmtsIsChecked = subAns.second;
			stmtsIsChecked = OrOperationOnBoolVects(subStmtsIsChecked, stmtsIsChecked);
		}
	
	}

	return make_pair(affectedStmts, stmtsIsChecked);
}

bool Affects::NoVarsOverlap(vector<int> varsVect1, vector<int> varsVect2) {
	sort(varsVect1.begin(), varsVect1.end());
	sort(varsVect2.begin(), varsVect2.end());
	vector<int>::iterator it1 = varsVect1.begin(), it2 = varsVect2.begin();

	while (it1 != varsVect1.end() && it2 != varsVect2.end()) {
		if (*it1 == *it2) {
			return false;
		} else if (*it1 > *it2) {
			it2++;
		} else {
			it1++;
		}
	}

	return true;
}

vector<int> Affects::OrOperationOnVects(vector<int> vect1, vector<int> vect2) {
	vector<int> combinedVect;

	sort(vect1.begin(), vect1.end());
	sort(vect2.begin(), vect2.end());
	vector<int>::iterator it1 = vect1.begin(), it2 = vect2.begin();

	while (it1 != vect1.end() || it2 != vect2.end()) {
		if (it1 == vect1.end()) {
			combinedVect.insert(combinedVect.end(), it2, vect2.end());
			return combinedVect;
		} else if (it2 == vect2.end()) {
			combinedVect.insert(combinedVect.end(), it1, vect1.end());
			return combinedVect;
		} else if (*it1 == *it2) {
			combinedVect.push_back(*it1);
			it1++;
			it2++;
		} else if (*it1 > *it2) {
			combinedVect.push_back(*it2);
			it2++;
		} else {
			combinedVect.push_back(*it1);
			it1++;
		}
	
	}

	return combinedVect;
}

vector<bool> Affects::OrOperationOnBoolVects(vector<bool> boolVect1, vector<bool> boolVect2) { 
	if (boolVect1.size() == boolVect2.size()) {
		vector<bool>::iterator it1 = boolVect1.begin(), it2 = boolVect2.begin();
		vector<bool> boolVect3(boolVect1.size() > boolVect2.size() ? boolVect1.size() : boolVect2.size());
		for (vector<bool>::iterator it3 = boolVect3.begin(); it3 != boolVect3.end(); it3++) {
			if (*it1 || *it2) {
				*it3 = true;
			}
			it1++;
			it2++;
		}
		return boolVect3;
	} else {
		cout << "problem: bool vectors different sizes";
		return boolVect2;
	}
}

Affects::~Affects(void) {
}

//void main(){
//	StmtTypeTable::Insert(1, ASSIGN);
//	Modifies::SetStmtModifiesVar(1, VarTable::InsertVar("a"));
//	Uses::SetStmtUsesVar(1, VarTable::InsertVar("b"));
//	Uses::SetStmtUsesVar(1, VarTable::InsertVar("c"));
//	Next::SetNext(1, 2);
//
//	StmtTypeTable::Insert(2, ASSIGN);
//	Modifies::SetStmtModifiesVar(2, VarTable::InsertVar("b"));
//	Uses::SetStmtUsesVar(2, VarTable::InsertVar("a"));
//	Next::SetNext(2, 3);
//
//	StmtTypeTable::Insert(3, WHILE);
//	Modifies::SetStmtModifiesVar(3, VarTable::InsertVar("a"));
//	Modifies::SetStmtModifiesVar(3, VarTable::InsertVar("k"));
//	Uses::SetStmtUsesVar(3, VarTable::InsertVar("b"));
//	Uses::SetStmtUsesVar(3, VarTable::InsertVar("a"));
//	Next::SetNext(3, 4);
//	Next::SetNext(3, 6);
//
//	StmtTypeTable::Insert(4, ASSIGN);
//	Modifies::SetStmtModifiesVar(4, VarTable::InsertVar("a"));
//	Next::SetNext(4, 5);
//
//	StmtTypeTable::Insert(5, ASSIGN);
//	Modifies::SetStmtModifiesVar(5, VarTable::InsertVar("k"));
//	Uses::SetStmtUsesVar(5, VarTable::InsertVar("a"));
//	Next::SetNext(5, 6);
//	Next::SetNext(5, 3);
//
//	StmtTypeTable::Insert(6, ASSIGN);
//	Modifies::SetStmtModifiesVar(6, VarTable::InsertVar("x"));
//	Uses::SetStmtUsesVar(6, VarTable::InsertVar("y"));
//	Uses::SetStmtUsesVar(6, VarTable::InsertVar("z"));
//	Uses::SetStmtUsesVar(6, VarTable::InsertVar("a"));
//	Next::SetNext(6, 7);
//
//	StmtTypeTable::Insert(7, WHILE);
//	Modifies::SetStmtModifiesVar(7, VarTable::InsertVar("k"));
//	Uses::SetStmtUsesVar(7, VarTable::InsertVar("k"));
//	Uses::SetStmtUsesVar(7, VarTable::InsertVar("x"));
//	Uses::SetStmtUsesVar(7, VarTable::InsertVar("a"));
//	Next::SetNext(7, 8);
//	Next::SetNext(7, 10);
//
//	StmtTypeTable::Insert(8, ASSIGN);
//	Modifies::SetStmtModifiesVar(8, VarTable::InsertVar("k"));
//	Uses::SetStmtUsesVar(8, VarTable::InsertVar("x"));
//	Next::SetNext(8, 9);
//
//	StmtTypeTable::Insert(9, ASSIGN);
//	Modifies::SetStmtModifiesVar(9, VarTable::InsertVar("k"));
//	Uses::SetStmtUsesVar(9, VarTable::InsertVar("a"));
//	Next::SetNext(9, 7);
//	Next::SetNext(9, 10);
//
//	StmtTypeTable::Insert(10, ASSIGN);
//	Modifies::SetStmtModifiesVar(10, VarTable::InsertVar("x"));
//	Uses::SetStmtUsesVar(10, VarTable::InsertVar("x"));
//
//	vector<int> stmtsAffecting6 = Affects::GetStmtsAffecting(6);
//}