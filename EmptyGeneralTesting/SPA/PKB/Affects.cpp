#include "Affects.h"
#include "StmtTypeTable.h"
#include "Next.h"
#include "Modifies.h"
#include "Uses.h"
#include "Follows.h"
#include "ProcTable.h"
#include "VarTable.h"
#include "Calls.h"
#include "..\Program\Program.h"

#include <iostream>
#include <set>
#include <ctime>

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

	if (!nextOfCurrStmt.empty()) {
		uncheckedStmts.push(nextOfCurrStmt.at(0));
	}

	int currStmt;
	
	while (!uncheckedStmts.empty()) {
		currStmt = uncheckedStmts.front();
		//cout << "\ncheck CFG currstmt: " << currStmt;
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
					if (!nextOfCurrStmt.empty()) {
						uncheckedStmts.push(nextOfCurrStmt.at(0));
					}
				}	
				break;
			case WHILE:
				nextOfCurrStmt = Next::GetNextAfter(currStmt);
				if ((int) nextOfCurrStmt.size() > 1 && stmtAffected >= nextOfCurrStmt.at(1)) {
					uncheckedStmts.push(nextOfCurrStmt.at(1));
				} else if ((int) nextOfCurrStmt.size() > 1 && !Modifies::IsStmtModifyingVar(currStmt, varModified)) {
					return true;
				} else {
					if (!nextOfCurrStmt.empty()) {
						uncheckedStmts.push(nextOfCurrStmt.at(0));
					}
				}
				break;
			case IF: {
				nextOfCurrStmt = Next::GetNextAfter(currStmt);
				int endOfIfElse = Follows::GetFollowsAfter(currStmt);
				
				if((int) nextOfCurrStmt.size() > 1) {
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
				}

			} break;
			case CALL: {
				int procCalled = ProcTable::GetIndexOfProc(Program::GetStmtFromNumber(currStmt).GetContent());
				if (Modifies::IsProcModifyingVar(procCalled, varModified)) {
					// don't check for anything after this stmt
				} else {
					nextOfCurrStmt = Next::GetNextAfter(currStmt);
					if (!nextOfCurrStmt.empty()) {
						uncheckedStmts.push(nextOfCurrStmt.at(0));
					}
				}
			} break;
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

	if (!nextOfCurrStmt.empty()) {
		uncheckedStmts.push(nextOfCurrStmt.at(0));
	}

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
					if (!nextOfCurrStmt.empty()) {
						uncheckedStmts.push(nextOfCurrStmt.at(0));
					}
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
					if ((int) nextOfCurrStmt.size() > 1) {
						uncheckedStmts.push(nextOfCurrStmt.at(0));
						uncheckedStmts.push(nextOfCurrStmt.at(1));
					}
				}
				break;
			case CALL: {
				int procCalled = ProcTable::GetIndexOfProc(Program::GetStmtFromNumber(currStmt).GetContent());
				
				if (procCalled >= 0 && Modifies::IsProcModifyingVar(procCalled, varModified)) {
					// don't check for anything after this stmt
				} else {
					nextOfCurrStmt = Next::GetNextAfter(currStmt);
					if (!nextOfCurrStmt.empty()) {
						uncheckedStmts.push(nextOfCurrStmt.at(0));
					}
				}
			} break;
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

	//cout << "\nRecurTraverseUpCFG currStmt: " << currStmt;

	if (StmtTypeTable::GetStmtTypeOf(currStmt) == ASSIGN) {
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
	} else if (StmtTypeTable::GetStmtTypeOf(currStmt) == WHILE) {
		vector<int>::iterator it = nextBeforeCurrStmt.begin();
		if (!stmtsIsChecked.at(currStmt)) {
			stmtsIsChecked.at(currStmt) = true;

		} else {
			nextBeforeCurrStmt.clear();
		}

	} else if (StmtTypeTable::GetStmtTypeOf(currStmt) == IF) {
		vector<int> nextAfterIf = Next::GetNextAfter(currStmt);
		if ((int) nextAfterIf.size() == 2) {
			if (stmtsIsChecked.at(nextAfterIf.at(0)) && stmtsIsChecked.at(nextAfterIf.at(1))) {
				stmtsIsChecked.at(currStmt) = true;
			} 
		}
	} else if (StmtTypeTable::GetStmtTypeOf(currStmt) == CALL) {
		int procCalled = ProcTable::GetIndexOfProc(Program::GetStmtFromNumber(currStmt).GetContent());
		if (!stmtsIsChecked.at(currStmt)) {
			vector<int> varsModifiedByCurr = Modifies::GetVarModifiedByProc(procCalled);
			sort(varsModifiedByCurr.begin(), varsModifiedByCurr.end());
			sort(varsUsed.begin(), varsUsed.end());

			vector<int>::iterator varsModifiedIt = varsModifiedByCurr.begin();
			vector<int>::iterator varsUsedIt = varsUsed.begin();

			while(varsModifiedIt != varsModifiedByCurr.end() && varsUsedIt != varsUsed.end()) {
				if (*varsModifiedIt == *varsUsedIt) {
					varsUsedIt = varsUsed.erase(varsUsedIt);
					varsModifiedIt++;
				} else if (*varsModifiedIt > *varsUsedIt) {
					varsUsedIt++;
				} else {
					varsModifiedIt++;
				}
			}
			stmtsIsChecked.at(currStmt) = true;

		} else {
			nextBeforeCurrStmt.clear();
		}
	} else {
		cout << "unable to determine stmttype of stmt# " << currStmt;
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

bool Affects::IsAffectsT(int stmtAffecting, int stmtAffected) {

	class StmtsHelper {
		vector<bool> checkedStmts; // keeps track of stmts that have been checked for modifies but have led nowhere
		int endPoint;

	public:
		StmtsHelper(int affectedStmt) {
			checkedStmts = vector<bool>(StmtTypeTable::GetNoOfStmts() + 1, false);
			endPoint = affectedStmt;
		};

		bool findAffectedStmt(int currentStmt) {
			checkedStmts[currentStmt] = true;
			vector<int> nextStmts = Next::GetNextAfter(currentStmt);
			if (nextStmts.empty()) return false;
			int nextStmt = Next::GetNextAfter(currentStmt)[0];
			int varModified = Modifies::GetVarModifiedByStmt(currentStmt)[0];
			return findAffectedStmt(currentStmt, nextStmt, varModified, vector<bool>(StmtTypeTable::GetNoOfStmts() + 1, false));
		}

		bool findAffectedStmt(int initialStmt, int comingStmt, int var, vector<bool> checkedWhile) {
			/*
			tail recursive
			calls itself upon finding next stmt in chain, updating stmtAffecting with new stmtAffecting
			if while is found, continue tail call with start of stmtlist
			this means that if encounter next < currentStmt, end of loop has been reached, update next accordingly
			if else is found, perform 2 tail calls
			update currentStmt with stmt numbers of beginnings of each branch
			return or of results
			*/

			vector<int> currentStmts;
			currentStmts.push_back(comingStmt);
			bool result = false;

			while (currentStmts.size() != 0) {
				if (result) return true; // immediately return 
				vector<int> nextStmts;
				int currentStmt = currentStmts[0]; // guaranteed

				if (StmtTypeTable::CheckIfStmtOfType(currentStmt, SynonymType::WHILE)) {
					// if while is found, continue tail call with start of stmtlist
					vector<int> followingStmts = Next::GetNextAfter(currentStmt);
					if (checkedWhile[currentStmt] || !Uses::IsStmtUsingVar(currentStmt, var)) {
						for each (int stmt in followingStmts) {
							if (stmt > currentStmt + 1) { // step out of loop
								nextStmts.push_back(stmt);
							}
						}
					} else {
						vector<bool> stepOut = checkedWhile;
						checkedWhile[currentStmt] = true;
						for each (int stmt in followingStmts) {
							if (stmt == currentStmt + 1) {
								result |= findAffectedStmt(initialStmt, stmt, var, checkedWhile);
							} else {
								result |= findAffectedStmt(initialStmt, stmt, var, stepOut);
							}
						}
						currentStmts.clear();
					}
				} else if (StmtTypeTable::CheckIfStmtOfType(currentStmt, SynonymType::IF)) {
					// if else is found, perform 2 tail calls

					if (!Uses::IsStmtUsingVar(currentStmt, var) && !Modifies::IsStmtModifyingVar(currentStmt, var)) { // optimisation
						int afterStmtList = Follows::GetFollowsAfter(currentStmt);

						if (afterStmtList != -1) {
							nextStmts.push_back(afterStmtList);
						}
					} else {
						for each (int stmt in Next::GetNextAfter(currentStmt)) {
							result |= findAffectedStmt(initialStmt, stmt, var, checkedWhile);
						}
						currentStmts.clear();
					}
				} else if (StmtTypeTable::CheckIfStmtOfType(currentStmt, SynonymType::CALL)) {
					// check if call type modifies variable
					// if it does, break
					int calledProcIndex = ProcTable::GetIndexOfProc(Program::GetStmtFromNumber(currentStmt).GetContent());
					if (!Modifies::IsProcModifyingVar(calledProcIndex, var)) {
						nextStmts = Next::GetNextAfter(currentStmt);
					}
				} else {
					// stmt found was assignment
					// this is where you do the checking for the truth val

					if (Uses::IsStmtUsingVar(currentStmt, var)) { // check uses first, because stmt can modify and use the same variable
						if (currentStmt == endPoint) {
							result = true;
						} else {
							if (!checkedStmts[currentStmt]) {
								checkedStmts[currentStmt] = true;
								int varModified = Modifies::GetVarModifiedByStmt(currentStmt)[0];
								if (varModified == var) {
									return findAffectedStmt(currentStmt);
								} else {
									result |= findAffectedStmt(currentStmt);
								}
							}
						}
					} else if (Modifies::IsStmtModifyingVar(currentStmt, var)) {
						if (currentStmt != initialStmt) { // ran into not same stmt 
							return false; // another valid modifies was found
						}
					}
					nextStmts = Next::GetNextAfter(currentStmt);
				}
				currentStmts = nextStmts;
			}
			return result;
		}
	};

	// TODO do error checking to check if stmts are in the same procedures.
	if (!StmtTypeTable::CheckIfStmtOfType(stmtAffecting, SynonymType::ASSIGN) ||
		!StmtTypeTable::CheckIfStmtOfType(stmtAffected, SynonymType::ASSIGN)) return false;
	// stmtAffecting is guaranteed to be assignment
	StmtsHelper helper = StmtsHelper(stmtAffected);
	return helper.findAffectedStmt(stmtAffecting);
}

// WARNING, RESULT MAY BE UNSORTED
vector<int> Affects::GetStmtsAffectedTBy(int stmtAffecting) {

	class StmtsHelper {
		vector<bool> mappedAffects;
		int currentProc;
		
	public:
		set<int> affectedStmts;
		StmtsHelper(int startingStmt) {
			mappedAffects = vector<bool>(StmtTypeTable::GetNoOfStmts() + 1, false);
			currentProc = ProcTable::GetProcOfStmt(startingStmt);
		};

		void findAffectedStmts(int currentStmt) {
			mappedAffects[currentStmt] = true;
			vector<int> nextStmts = Next::GetNextAfter(currentStmt);
			if (nextStmts.empty()) return;
			int nextStmt = Next::GetNextAfter(currentStmt)[0];
			int varModified = Modifies::GetVarModifiedByStmt(currentStmt)[0];
			return findAffectedStmts(currentStmt, nextStmt, varModified, vector<bool>(StmtTypeTable::GetNoOfStmts() + 1, false));
		}

		// add case, if currentStmt = examinedStmt, skip
		void findAffectedStmts(int initialStmt, int comingStmt, int var, vector<bool> checkedWhile) {
			vector<int> currentStmts;
			currentStmts.push_back(comingStmt);

			while (currentStmts.size() != 0) {
				vector<int> nextStmts;
				int currentStmt = currentStmts[0]; // guaranteed

				if (StmtTypeTable::CheckIfStmtOfType(currentStmt, SynonymType::WHILE)) {
					// if while is found, continue tail call with start of stmtlist
					vector<int> followingStmts = Next::GetNextAfter(currentStmt);
					if (checkedWhile[currentStmt] || !Uses::IsStmtUsingVar(currentStmt, var)) {
						for each (int stmt in followingStmts) {
							if (stmt > currentStmt + 1) { // step out of loop
								nextStmts.push_back(stmt);
							}
						}
					} else {
						vector<bool> stepOut = checkedWhile;
						checkedWhile[currentStmt] = true;
						for each (int stmt in followingStmts) {
							if (stmt == currentStmt + 1) {
								findAffectedStmts(initialStmt, stmt, var, checkedWhile);
							} else {
								findAffectedStmts(initialStmt, stmt, var, stepOut);
							}
						}
						currentStmts.clear();
					}
				} else if (StmtTypeTable::CheckIfStmtOfType(currentStmt, SynonymType::IF)) {
					// if else is found, perform 2 tail calls

					if (!Uses::IsStmtUsingVar(currentStmt, var) && !Modifies::IsStmtModifyingVar(currentStmt, var)) { // optimisation
						int afterStmtList = Follows::GetFollowsAfter(currentStmt);

						if (afterStmtList != -1) {
							nextStmts.push_back(afterStmtList);
						}
					} else {
						for each (int stmt in Next::GetNextAfter(currentStmt)) {
							findAffectedStmts(initialStmt, stmt, var, checkedWhile);
						}
						currentStmts.clear();
					}
				} else if (StmtTypeTable::CheckIfStmtOfType(currentStmt, SynonymType::CALL)) {
					// check if call type modifies variable
					// if it does, break
					int calledProcIndex = ProcTable::GetIndexOfProc(Program::GetStmtFromNumber(currentStmt).GetContent());
					if (!Modifies::IsProcModifyingVar(calledProcIndex, var)) {
						nextStmts = Next::GetNextAfter(currentStmt);
					}
				} else {
					// stmt found was assignment
					// this is where you do the checking for the truth val

					if (Uses::IsStmtUsingVar(currentStmt, var)) { // check uses first, because stmt can modify and use the same variable
						if (mappedAffects[currentStmt]) {
							if (currentStmt == initialStmt) {
								affectedStmts.insert(currentStmt);
							}
							nextStmts = Next::GetNextAfter(currentStmt);
						} else {
							mappedAffects[currentStmt] = true;
							affectedStmts.insert(currentStmt);
							int varModified = Modifies::GetVarModifiedByStmt(currentStmt)[0];
							if (varModified == var) {
								return findAffectedStmts(currentStmt);
							} else {
								findAffectedStmts(currentStmt);
								nextStmts = Next::GetNextAfter(currentStmt);
							}
						}
					} else if (Modifies::IsStmtModifyingVar(currentStmt, var)) {
						if (currentStmt == initialStmt) { // ran into same stmt 
							nextStmts = Next::GetNextAfter(currentStmt);
						} else {
							return; // another valid modifies was found
						}
					} else {
						nextStmts = Next::GetNextAfter(currentStmt);
					}
				}

				currentStmts = nextStmts;
			}
		}
	};

	// guarantee that stmt is assignment.
	if (!StmtTypeTable::CheckIfStmtOfType(stmtAffecting, SynonymType::ASSIGN)) return vector<int>();

	StmtsHelper helper(stmtAffecting);
	helper.findAffectedStmts(stmtAffecting);
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
		int startStmt;

	public:
		set<int> affectingStmts;
		StmtsHelper(int startStmt) : startStmt(startStmt) {
			mappedAffects = vector<bool>(StmtTypeTable::GetNoOfStmts() + 1, false);
		};

		void findAffectingStmts(int affectedStmt) {
			// guaranteed that every affectedStmt is an assignment

			vector<int> varsUsed = Uses::GetVarUsedByStmt(affectedStmt);
			vector<int> previousStmts = Next::GetNextBefore(affectedStmt);

			for each (int var in varsUsed) {
				for each (int stmt in previousStmts) {
					findAffectingStmts(affectedStmt, stmt, var, vector<bool>(StmtTypeTable::GetNoOfStmts() + 1, false));
				}
			}
		}

		// have to use loops cos current algo is not tail optimisable
		// keep track of previous node
		void findAffectingStmts(int initialStmt, int prevStmt, int varUsed, vector<bool> checkedWhile) {
			vector<int> currentStmts;
			currentStmts.push_back(prevStmt);

			while (currentStmts.size() != 0) {
				if (currentStmts.size() > 1) {
					for each (int currentStmt in currentStmts) {
						findAffectingStmts(initialStmt, currentStmt, varUsed, checkedWhile);
					}
					return;
				} else {
					int currentStmt = currentStmts[0];
					vector<int> prevStmts;
					if (StmtTypeTable::CheckIfStmtOfType(currentStmt, SynonymType::WHILE)) {
						if (checkedWhile[currentStmt]) { // loop has been checked before
							for each (int stmt in Next::GetNextBefore(currentStmt)) {
								if (stmt < currentStmt) prevStmts.push_back(stmt); // exit loop
							}
						} else {
							for each (int stmt in Next::GetNextBefore(currentStmt)) {
								if (stmt < currentStmt) prevStmts.push_back(stmt); // exit loop
							}
							if (Modifies::IsStmtModifyingVar(currentStmt, varUsed)) {
								checkedWhile[currentStmt] = true;
								for each (int stmt in Next::GetNextBefore(currentStmt)) {
									if (stmt > currentStmt) prevStmts.push_back(stmt); // enter loop
								}
							}
						}
					} else if (StmtTypeTable::CheckIfStmtOfType(currentStmt, SynonymType::IF)) {
						// no check for modifies if in if, just skip
						prevStmts = Next::GetNextBefore(currentStmt);
					} else if (StmtTypeTable::CheckIfStmtOfType(currentStmt, SynonymType::CALL)) {
						// if call modifies var, break
						if (!Modifies::IsProcModifyingVar(ProcTable::GetIndexOfProc(Program::GetStmtFromNumber(currentStmt).GetContent()), varUsed)) {
							prevStmts = Next::GetNextBefore(currentStmt);
						}
					} else {
						// stmt found is assign
						// perform checking here.
						if (Modifies::IsStmtModifyingVar(currentStmt, varUsed)) {
							if (mappedAffects[currentStmt]) {
								if (currentStmt == initialStmt) {
									affectingStmts.insert(currentStmt);
								} else {
									return;
								}
							} else {
								affectingStmts.insert(currentStmt);
								mappedAffects[currentStmt] = true;
								return findAffectingStmts(currentStmt); // end here, subject found
							}
						}
						prevStmts = Next::GetNextBefore(currentStmt);
					}
					currentStmts = prevStmts;
				}
			}
		}
	};

	// guarantee that stmt is assignment.
	if (!StmtTypeTable::CheckIfStmtOfType(stmtAffected, SynonymType::ASSIGN)) return vector<int>();

	StmtsHelper helper(stmtAffected);
	helper.findAffectingStmts(stmtAffected);
	return vector<int>(helper.affectingStmts.begin(), helper.affectingStmts.end());
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