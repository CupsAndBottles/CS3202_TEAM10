#include "optimizer.h"
#include "../PKB/ConstTable.h"
#include "../PKB/StmtTypeTable.h"
#include "../PKB/ProcTable.h"
#include "../PKB/vartable.h"
#include "../PKB/Modifies.h"
#include "../PKB/Calls.h"
#include "../PKB/Next.h"
#include "../PKB/Follows.h"
#include "../PKB/Parent.h"
#include "../PKB/Uses.h"

#define WEIGHTOFUNDERSCORE 9999



Optimizer::Optimizer(){
	numOfCon = ConstTable::SizeOfConstTable();
	numOfProgLine = numOfStmt = StmtTypeTable::GetNoOfStmts();
	numOfProc = ProcTable::GetNoOfProcs();
	numOfVar = VarTable::GetNoOfVars();
	numOfIf = StmtTypeTable::GetNoOfStmtsOfType(IF);
	numOfWhile = StmtTypeTable::GetNoOfStmtsOfType(WHILE);
	numOfAssign = StmtTypeTable::GetNoOfStmtsOfType(ASSIGN);
	numOfModifies = Modifies::SizeOfModifies();
	numOfCall = Calls::SizeOfCalls();
	numOfNext = Next::SizeOfNext();
	numOfFollows = Follows::SizeOfFollows();
	numOfParent = Parent::SizeOfParent();
	numOfUses = Uses::SizeOfUses();
}

bool strict_weak_ordering(const pair<pair<ClauseType,int>, int> a, const pair<pair<ClauseType,int>, int> b)
{
	return a.second < b.second;
}

vector<pair<ClauseType,int>> Optimizer::optimize(QueryData qd){
	vector<pair<ClauseType,int>> tempSequence = qd.GetClauseSequence();
	vector<SuchThatClause> tempSuchThats = qd.GetSuchThats();
	vector<PatternClause> tempPatterns = qd.GetPatterns();
	vector<WithClause> tempWiths = qd.GetWiths();

	vector<pair<pair<ClauseType,int>,int>> weightMap;

	for(vector<pair<ClauseType,int>>::iterator iter=tempSequence.begin();iter!=tempSequence.end();++iter)  
    {  
		switch((*iter).first){
		case SUCHTHAT:{
			int weight = weightSuchThat(tempSuchThats[(*iter).second]);
			weightMap.push_back(pair<pair<ClauseType,int>,int>((*iter),weight));
			break;
					  }
		case WITH:{
			int weight = weightWith(tempWiths[(*iter).second]);
			weightMap.push_back(pair<pair<ClauseType,int>,int>((*iter),weight));
			break;
				  }
		case PATTERN:{
			int weight = weightPattern(tempPatterns[(*iter).second]);
			weightMap.push_back(pair<pair<ClauseType,int>,int>((*iter),weight));
			break;
					 }
		default:{
			cout << "wrong clausetype./n";
			break;
				}
		}
    }  

	sort(weightMap.begin(), weightMap.end(), strict_weak_ordering);

	vector<pair<ClauseType,int>> finalSequence;

	for(vector<pair<pair<ClauseType,int>,int>>::iterator iter=weightMap.begin();iter!=weightMap.end();++iter) {
		cout << (*iter).first.second;
		finalSequence.push_back((*iter).first); 
	}

	return finalSequence;
}



int Optimizer::weightWith(WithClause wc){

	//lhs can be a.stmt# , c.value , p.procName , v.varName , n
	//rhs can be a.stmt# , c.value , p.procName , v.varName , "ident" , 5

	int weight,weight1,weight2;
	switch (wc.arg1.type)
	{
	case SYNONYM:
		{
			switch(wc.arg1.syn.type)
			{
			case STMT:
				{
				weight1 = numOfStmt;
				break;
				}
			case ASSIGN:
				{
				weight1 = numOfAssign;
				break;
				}
			case WHILE:
				{
				weight1 = numOfWhile;
				break;
				}
			case IF:
				{
				weight1 = numOfIf;
				break;
				}
			case CALL:
				{
				weight1 = numOfCall;
				break;
				}
			case BOOLEAN:
				{
				weight1 = 1;
				break;
				}
			case PROG_LINE:
				{
				weight1 = numOfProgLine;
				break;
				}
			case CONSTANT:
				{
				weight1 = numOfCon;
				break;
				}
			case PROCEDURE:
				{
				weight1 = numOfProc;
				break;
				}
			case VARIABLE:
				{
				weight1 = numOfVar;
				break;
				}
			default:
				{
				cout << "arg1 synonym wrong type./n";
				break;
				}
			}
			break;
		}
	case IDENT:
		{
			weight1 = 1;
			break;
		}
	case INTEGER:
		{
			weight1 = 1;
			break;
		}
	default:
		{
			cout <<"arg1 wrong type./n";
			break;
		}

	}

	switch (wc.arg2.type)
	{
	case SYNONYM:
		{
			switch(wc.arg1.syn.type)
			{
			case ASSIGN:
				{
				weight2 = numOfAssign;
				break;
				}
			case WHILE:
				{
				weight2 = numOfWhile;
				break;
				}
			case IF:
				{
				weight2 = numOfIf;
				break;
				}
			case CALL:
				{
				weight2 = numOfCall;
				break;
				}
			case BOOLEAN:
				{
				weight2 = 1;
				break;
				}
			case STMT:
				{
				weight2 = numOfStmt;
				break;
				}
			case PROG_LINE:
				{
				weight2 = numOfProgLine;
				break;
				}
			case CONSTANT:
				{
				weight2 = numOfCon;
				break;
				}
			case PROCEDURE:
				{
				weight2 = numOfProc;
				break;
				}
			case VARIABLE:
				{
				weight2 = numOfVar;
				break;
				}
			default:
				{
				cout << "arg2 synonym wrong type./n";
				break;
				}
			}
			break;
		}
	case IDENT:
		{
			weight2 = 1;
			break;
		}
	case INTEGER:
		{
			weight2 = 1;
			break;
		}
	default:
		{
		cout << "arg2 wrong type./n";
		break;
		}
	}

	weight = weight1*weight2;
	return weight;
}

int Optimizer::weightSuchThat(SuchThatClause sc){
	int weight;
	
	switch(sc.relationship){
	case(MODIFIES):{
		weight = min(numOfModifies,weightStars(sc.arg1,sc.arg2));
		break;
				   }
	case(USES):{
		weight = min(numOfUses,weightStars(sc.arg1,sc.arg2));
		break;
				   }
	case(FOLLOWS):{
		weight = min(numOfFollows,weightStars(sc.arg1,sc.arg2));
		break;
				   }
	case(PARENT):{
		weight = min(numOfParent,weightStars(sc.arg1,sc.arg2));
		break;
				 }
	case(CALLS):{
		weight = min(numOfCall,weightStars(sc.arg1,sc.arg2));
		break;
				}
	case(NEXT):{
		weight = min(numOfNext,weightStars(sc.arg1,sc.arg2));
		break;
			   }
	case(PARENTT):
	case(FOLLOWST):
	case(CALLST):
	case(NEXTT):
	case(CONTAINS):
	case(CONTAINST):
	case(SIBLING):
	case(AFFECTS):
	case(AFFECTSBIP):
	case(NEXTBIP):
	case(NEXTBIPT):{
		weight = weightStars(sc.arg1,sc.arg2);
		break;
				 }
	case(AFFECTST):{
		weight = INT_MAX;
		break;
	}
	default:{
		cout << "Wronge such that clause./n";
		break;
			}
	}
	//weight = weight1 * weight2 * weight3;
	return weight;
}

int Optimizer::weightStars(Argument arg1,Argument arg2){
	int weight1,weight2;
	switch(arg1.type){
	case(SYNONYM):{
		if(arg1.syn.type == VARIABLE) weight1 = numOfVar;
		else weight1 = StmtTypeTable::GetNoOfStmtsOfType(arg1.syn.type);
		break;
					}
	case(UNDERSCORE):{
		weight1 = WEIGHTOFUNDERSCORE;
		break;
						}
	case(IDENT):{
		weight1 = 1;
		break;
				}
	case(INTEGER):{
		weight1 = 1;
		break;
					}
	case(EXPRESSION):{
		weight1 = 1;
		break;
					 }
	default:{
		cout<<"Bug in stars./n";
		break;
			}
	}

	
	switch(arg2.type){
	case(SYNONYM):{
		if(arg2.syn.type == VARIABLE) weight2 = numOfVar;
		else weight2 = StmtTypeTable::GetNoOfStmtsOfType(arg2.syn.type);
		break;
					}
	case(UNDERSCORE):{
		weight2 = WEIGHTOFUNDERSCORE;
		break;
						}
	case(IDENT):{
		weight2 = 1;
		break;
				}
	case(INTEGER):{
		weight2 = 1;
		break;
					}
	case(EXPRESSION):{
		weight1 = 1;
		break;
					 }
	default:{
		cout<<"Bug in stars./n";
		break;
			}
	}

	return weight1*weight2;
}



int Optimizer::weightPattern(PatternClause pc){
	int weight1;//,weight2,weight3 = 1;
	switch (pc.synonym.type){
	case ASSIGN:{//assign
		weight1 = numOfAssign;
		/*switch (pc.arg1.type){
		case underscore:{
			weight2 = weightofunderscore;
			break;
						}
		case synonym:{
			weight2 = 
					 }
		case ident:{
				   }
		default:{
			cout << "pattern assign wrong type./n";
			break;
				}*/
		break;
				}
	case IF:{
		weight1 = numOfIf;
		break;
			}
	case WHILE:{
		weight1 = numOfWhile;
		break;
			   }
	}
	return weight1;

}