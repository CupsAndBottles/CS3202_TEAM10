#include "QueryEvaluator.h"
#include "Modifies.h"


QueryEvaluator::QueryEvaluator(void)
{
}


std::vector<Synonym> QueryEvaluator::evaluateQuery(QueryData queryData){
	
	
	std::vector<std::vector<Synonym>> finalResult;
	std::vector<std::vector<Synonym>> modifiesResult;

	std::vector<Declaration> declarations = queryData.GetDeclarations();
	std::vector<SelectClause> selects = queryData.GetSelects();


   //To process suchthatClause
    std::vector<SuchThatClause> suchThats = queryData.GetSuchThats();
	std::vector<SuchThatClause>::iterator iter;
    for (iter = suchThats.begin();iter != suchThats.end();iter++ )
    {
	    SuchThatClause token = *iter;
	    switch(token.relationship){
		case MODIFIES:
			modifiesResult = checkModifies(token,selects,declarations);
			break;
		case USES:
			break;
		case PARENT:
			break;
		case PARENTT:
			break;
		case FOLLOWS:
			break;
		case FOLLOWST:
			break;
		case INVALID_RELATIONSHIP_TYPE:
			break;
		default:
			break;
		}
    }

}



std::vector<std::vector<Synonym>> checkModifies(SuchThatClause suchThat,std::vector<SelectClause> select,std::vector<Declaration> declaration){
	
}
