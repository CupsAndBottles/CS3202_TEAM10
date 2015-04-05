#include "Affects.h"
#include "StmtTypeTable.h"
#include "Next.h"
#include "Modifies.h"
#include "Uses.h"
#include "Follows.h"
#include "ProcTable.h"
#include "..\Program\Program.h"
//#include "VarTable.h"

#include <iostream>
#include <set>

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
				if ((int) nextOfCurrStmt.size() > 1 && stmtAffected >= nextOfCurrStmt.at(1)) {
					uncheckedStmts.push(nextOfCurrStmt.at(1));
				} else if ((int) nextOfCurrStmt.size() > 1 && !Modifies::IsStmtModifyingVar(currStmt, varModified)) {
					return true;
				} else {
					uncheckedStmts.push(nextOfCurrStmt.at(0));
				}
				break;
			case IF:
				nextOfCurrStmt = Next::GetNextAfter(currStmt);
				endOfIfElse = Follows::GetFollowsAfter(currStmt);
				
				if (stmtAffected < nextOfCurrStmt.at(1)) {
					// modification in 1st block
					if (!Modifies::IsStmtModifyingVar(currStmt, varModified)) {
						return true;
					} else {
						uncheckedStmts.push(nextOfCurrStmt.at(0));	
					}
				} else if (endOfIfElse > 0 && stmtAffected >= nextOfCurrStmt.at(1) && stmtAffected < endOfIfElse) {
					// modification in 2nd block
					if (!Modifies::IsStmtModifyingVar(currStmt, varModified)) {
						return true;
					} else {
						uncheckedStmts.push(nextOfCurrStmt.at(1));	
					}
				} else if (endOfIfElse > 0 && stmtAffected >= endOfIfElse && !Modifies::IsStmtModifyingVar(currStmt, varModified)) {
					// if-else does not modify at all, skip all if-else
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
				if ((int) nextOfCurrStmt.size() > 1) {
					uncheckedStmts.push(nextOfCurrStmt.at(1));
				}
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


/*---------------------------------------------------------------------------------------------------------------------*/
/*                                                                                                                     */
/*                                                 AFFECTS*                                                            */
/*                                                                                                                     */
/*---------------------------------------------------------------------------------------------------------------------*/

bool stmtWalker(int startStmt, int var, int endStmt);

bool Affects::IsAffectsT(int stmtAffecting, int stmtAffected) {
	// TODO do error checking to check if stmts are in the same procedures.
	if (!StmtTypeTable::CheckIfStmtOfType(stmtAffecting, SynonymType::ASSIGN) ||
		!StmtTypeTable::CheckIfStmtOfType(stmtAffected, SynonymType::ASSIGN)) throw (string) "stmt of wrong type";
	// stmtAffecting is guaranteed to be assignment
	int varModified = Modifies::GetVarModifiedByStmt(stmtAffecting)[0];

	return stmtWalker(stmtAffecting, varModified, stmtAffected);
}

int getLastStmtInListFrom(int stmt) {
	// loop until no follows
	// perform actions depending on the type of stmt last one is
	// keyword is FOLLOWS
	int followingStmt = stmt;

	do {
		stmt = followingStmt;
		followingStmt = Follows::GetFollowsAfter(stmt);
	} while (followingStmt != -1);

	if (StmtTypeTable::CheckIfStmtOfType(stmt, SynonymType::WHILE)) {
		getLastStmtInListFrom(stmt + 1); // a bit of cheating
	} else if (StmtTypeTable::CheckIfStmtOfType(stmt, SynonymType::IF)) {
		vector<int> followingStmts = Next::GetNextAfter(stmt);
		getLastStmtInListFrom(max(followingStmts[0], followingStmts[1]));
	} else {
		return stmt;
	}
}

bool stmtWalker(int currentStmt, int var, int endStmt) {
	/*
		tail recursive
		calls itself upon finding next stmt in chain, updating stmtAffecting with new stmtAffecting
		if while is found, continue tail call with start of stmtlist
		this means that if encounter next < currentStmt, end of loop has been reached, update next accordingly
		if else is found, perform 2 tail calls
		update currentStmt with stmt numbers of beginnings of each branch
		return or of results
		*/

	if (currentStmt > endStmt) return false; // overshot

	if (StmtTypeTable::CheckIfStmtOfType(currentStmt, SynonymType::WHILE)) {
		// if while is found, continue tail call with start of stmtlist
		vector<int> followingStmts = Next::GetNextAfter(currentStmt);
		if (!Uses::IsStmtUsingVar(currentStmt, var)) { // optimisation
			if (followingStmts.size() == 2) {
				return stmtWalker(max(followingStmts[0], followingStmts[1]), var, endStmt); // false branch of while
			} else {
				return false; // end of proc reached
			}
		} else {
			return stmtWalker(currentStmt + 1, var, endStmt); // start of stmtlist
		}

	} else if (StmtTypeTable::CheckIfStmtOfType(currentStmt, SynonymType::IF)) {
		// if else is found, perform 2 tail calls

		if (!Uses::IsStmtUsingVar(currentStmt, var)) { // optimisation
			return stmtWalker(getLastStmtInListFrom(currentStmt) + 1, var, endStmt);
		}

		vector<int> followingStmts = Next::GetNextAfter(currentStmt);
		return stmtWalker(followingStmts[0], var, endStmt) || stmtWalker(followingStmts[1], var, endStmt);

	} else if (StmtTypeTable::CheckIfStmtOfType(currentStmt, SynonymType::CALL)) {
		// check if call type modifies variable
		// if it does, break
		if (Modifies::IsProcModifyingVar(ProcTable::GetIndexOfProc(Program::GetStmtFromNumber(currentStmt).GetContent()), var)) {
			return false;
		} else {
			return stmtWalker(Next::GetNextAfter(currentStmt)[0], var, endStmt);
		}
	} else {
		// stmt found was assignment stmt
		// this is where you do the checking for the truth val
		// endStmt guaranteed to be assignment

		vector<int> nextStmts = Next::GetNextAfter(currentStmt);
		int nextStmt;
		if (nextStmts.size() == 0) { // check if is end of proc or not
			nextStmt = endStmt + 1; // must end by next iteration
		} else {
			nextStmt = Next::GetNextAfter(currentStmt)[0]; // carry on
			if (nextStmt < currentStmt) { // skip while
				vector<int> nextAfterWhile = Next::GetNextAfter(nextStmt);
				if (nextStmts.size() != 2) { // check if end or not
					nextStmt = endStmt + 1; // must end by next iteration
				} else {
					nextStmt = max(nextStmts[0], nextStmts[1]);
				}
			}
		}

		if (Uses::IsStmtUsingVar(currentStmt, var)) { // check uses first, because stmt can modify and use the same variable
			if (currentStmt == endStmt) {
				return true; // stmt found
			} else {
				int varModified = Modifies::GetVarModifiedByStmt(currentStmt)[0];
				return stmtWalker(nextStmt, varModified, endStmt);
			}
		} else if (Modifies::IsStmtModifyingVar(currentStmt, var)) {
			return false; // another valid modifies was found
		} else {
			return stmtWalker(nextStmt, var, endStmt);
		}

	}
}

// WARNING, RESULT MAY BE UNSORTED
vector<int> Affects::GetStmtsAffectedTBy(int stmtAffecting) {

	class StmtsHelper {
		vector<bool> mappedAffects;
		
	public:
		set<int> affectedStmts;
		StmtsHelper() {
			mappedAffects = vector<bool>(StmtTypeTable::GetNoOfStmts() + 1, false);
		};

		void findAffectedStmts(int currentStmt, int var) {
			if (currentStmt > StmtTypeTable::GetNoOfStmts()) return; // done
			if (mappedAffects[currentStmt]) return; // optimisation (some form of memoization)

			if (StmtTypeTable::CheckIfStmtOfType(currentStmt, SynonymType::WHILE)) {
				// if while is found, continue tail call with start of stmtlist
				vector<int> followingStmts = Next::GetNextAfter(currentStmt);
				if (!Uses::IsStmtUsingVar(currentStmt, var)) { // optimisation
					if (followingStmts.size() == 2) {
						findAffectedStmts(max(followingStmts[0], followingStmts[1]), var); // false branch of while
					} else {
						return; // end of proc reached
					}
				} else {
					findAffectedStmts(currentStmt + 1, var); // start of stmtlist
				}

			} else if (StmtTypeTable::CheckIfStmtOfType(currentStmt, SynonymType::IF)) {
				// if else is found, perform 2 tail calls

				if (!Uses::IsStmtUsingVar(currentStmt, var)) { // optimisation
					return findAffectedStmts(getLastStmtInListFrom(currentStmt), var);
				}

				vector<int> followingStmts = Next::GetNextAfter(currentStmt);
				findAffectedStmts(followingStmts[0], var);
				findAffectedStmts(followingStmts[1], var);

			} else if (StmtTypeTable::CheckIfStmtOfType(currentStmt, SynonymType::CALL)) {
				// check if call type modifies variable
				// if it does, break
				if (Modifies::IsProcModifyingVar(ProcTable::GetIndexOfProc(Program::GetStmtFromNumber(currentStmt).GetContent()), var)) {
					return;
				} else {
					return findAffectedStmts(Next::GetNextAfter(currentStmt)[0], var);
				}
			} else {
				// stmt found was assignment
				// this is where you do the checking for the truth val

				vector<int> nextStmts = Next::GetNextAfter(currentStmt);
				int nextStmt;
				if (nextStmts.size() == 0) { // check if is end of proc or not
					nextStmt = currentStmt + 1; // must end by next iteration
				} else {
					nextStmt = Next::GetNextAfter(currentStmt)[0]; // carry on
					if (nextStmt < currentStmt) { // skip while
						vector<int> nextAfterWhile = Next::GetNextAfter(nextStmt);
						if (nextStmts.size() != 2) { // check if end or not
							nextStmt = currentStmt + 1; // must end by next iteration
						} else {
							nextStmt = max(nextStmts[0], nextStmts[1]);
						}
					}
				}

				if (Uses::IsStmtUsingVar(currentStmt, var)) { // check uses first, because stmt can modify and use the same variable
					mappedAffects[currentStmt] = true;
					affectedStmts.insert(currentStmt);
					int varModified = Modifies::GetVarModifiedByStmt(currentStmt)[0];
					return findAffectedStmts(nextStmt, varModified);
				} else if (Modifies::IsStmtModifyingVar(currentStmt, var)) {
					return; // another valid modifies was found
				} else {
					return findAffectedStmts(nextStmt, var);
				}
			}
		}
	};

	// guarantee that stmt is assignment.
	if (!StmtTypeTable::CheckIfStmtOfType(stmtAffecting, SynonymType::ASSIGN)) throw (string) "stmt of wrong type";

	StmtsHelper helper;
	helper.findAffectedStmts(stmtAffecting, Modifies::GetVarModifiedByStmt(stmtAffecting)[0]);
	return vector<int>(helper.affectedStmts.begin(), helper.affectedStmts.end());
}

vector<int> Affects::GetStmtsAffectingT(int stmtAffected) {
	/*
		Get all used by stmt affected.
		Walk up the next chain, once var modified is found, break for that var
		repeat for every var
		add stmts to result, recurse for every stmt.
	*/
	class StmtsHelper {
		vector<bool> mappedAffects;

	public:
		set<int> affectingStmts;
		StmtsHelper() {
			mappedAffects = vector<bool>(StmtTypeTable::GetNoOfStmts() + 1, false);
		};
		
		// have to use loops cos current algo is not tail optimisable
		// keep track of previous node
		void findAffectingStmts(int affectedStmt, int varUsed, int nextStmt) {
			vector<int> currentStmts;
			currentStmts.push_back(affectedStmt);

			while (currentStmts.size() != 0) {
				if (currentStmts.size() > 1) {
					for each (int currentStmt in currentStmts) {
						findAffectingStmts(currentStmt, varUsed, nextStmt);
					}
				} else {
					int currentStmt = currentStmts[0];
					vector<int> prevStmts;
					if (StmtTypeTable::CheckIfStmtOfType(currentStmt, SynonymType::WHILE)) {
						if (currentStmt == nextStmt - 1) { // reached start of loop
							prevStmts = Next::GetNextBefore(currentStmt);
						} else { // came from outside the loop
							if (Modifies::IsStmtModifyingVar(currentStmt, varUsed)) { 
								for each (int stmt in Next::GetNextBefore(currentStmt)) {
									if (stmt > currentStmt) { // enter loop
										prevStmts.push_back(stmt);
									}
								}
							} else { // optimised call
								for each (int stmt in Next::GetNextBefore(currentStmt)) {
									if (stmt < currentStmt) { // exit loop
										prevStmts.push_back(stmt);
									}
								}
							}
						}
					} else if (StmtTypeTable::CheckIfStmtOfType(currentStmt, SynonymType::IF)) {
						// no check for modifies if in if, just skip
						prevStmts = Next::GetNextBefore(currentStmt);
					} else if (StmtTypeTable::CheckIfStmtOfType(currentStmt, SynonymType::CALL)) {
						// if call modifies var, break
						if (Modifies::IsProcModifyingVar(ProcTable::GetIndexOfProc(Program::GetStmtFromNumber(currentStmt).GetContent()), varUsed)) {
							continue;
						} else {
							prevStmts = Next::GetNextBefore(currentStmt);
						}
					} else {
						// stmt found is assign
						if (mappedAffects[currentStmt]) {
							continue; // this stmt has already been mapped.
						} else {
							// perform checking here.
							if (Modifies::IsStmtModifyingVar(currentStmt, varUsed)) {
								affectingStmts.insert(currentStmt);
								mappedAffects[currentStmt] = true;
								return findAffectingStmts(currentStmt); // end here, subject found
							} else {
								prevStmts = Next::GetNextBefore(currentStmt);
							}
						}
					}

					nextStmt = currentStmt;
					currentStmts = prevStmts;
				}
			}
		}

		void findAffectingStmts(int affectedStmt) {
			// guaranteed that every affectedStmt is an assignment

			vector<int> varsUsed = Uses::GetVarUsedByStmt(affectedStmt);
			vector<int> previousStmts = Next::GetNextBefore(affectedStmt);

			for each (int var in varsUsed) {
				for each (int stmt in previousStmts) {
					findAffectingStmts(stmt, var, affectedStmt);
				}
			}
		}
	};

	// guarantee that stmt is assignment.
	if (!StmtTypeTable::CheckIfStmtOfType(stmtAffected, SynonymType::ASSIGN)) throw (string) "stmt of wrong type";

	StmtsHelper helper;
	helper.findAffectingStmts(stmtAffected);
	return vector<int>(helper.affectingStmts.begin(), helper.affectingStmts.end());
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