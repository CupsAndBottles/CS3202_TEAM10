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
	numOfModifies = Modifies::SizeOfModifies();
	//numOfModifiesT;
	numOfCall = Calls::SizeOfCalls();
	//numOfCallT;
	numOfNext = Next::SizeOfNext();
	//numOfNextT;
	numOfFollows = Follows::SizeOfFollows();
	//numOfFollowsT;
	numOfParent = Parent::SizeOfParent();
	//numOfParentT;
	numOfUses = Uses::SizeOfUses();
	//numOfUsesT;
	//numOfAffects;
}


int Optimizer::weightWith(WithClause wc){
	int weight;
	switch (wc.arg1.type)
	{
	case SYNONYM:
		{

		}

	}

	return weight;
}

int Optimizer::weightSuchThat(SuchThatClause sc){
	int weight;
	int weight1,weight2,weight3;
	switch(sc.arg1.type){
	case(SYNONYM):{
		weight1 = StmtTypeTable::GetNoOfStmtsOfType(sc.arg1.syn.type);
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
	}

	switch(sc.arg2.type){
	case(SYNONYM):{
		weight2 = StmtTypeTable::GetNoOfStmtsOfType(sc.arg1.syn.type);
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
	}
	
	switch(sc.relationship){
	case(MODIFIES):{
		weight3 = numOfModifies;
		break;
				   }
	case(USES):{
		weight3 = numOfUses;
		break;
				   }
	case(FOLLOWS):{
		weight3 = numOfFollows;
		break;
				   }
	case(PARENT):{
		weight3 = numOfParent;
		break;
				 }
    case(FOLLOWST):{
		weight3 = numOfFollowsT;
		break;
				   }
	case(PARENTT):{
		weight3 = numOfModifies;
		break;
				   }
	}
	weight = weight1 * weight2 * weight3;
	return weight;


}