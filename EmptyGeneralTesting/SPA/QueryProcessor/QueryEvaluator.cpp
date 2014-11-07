#include "QueryEvaluator.h"
#include "PKB\Modifies.h"
#include "PKB\Uses.h"
#include "PKB\StmtTypeTable.h"
#include "PKB\VarTable.h"

using namespace std;

QueryEvaluator::QueryEvaluator(void) {}

vector<vector<Synonym>> QueryEvaluator::evaluateQuery(QueryData queryData){

	vector<vector<Synonym>> finalResult;
	vector<vector<Synonym>> modifiesResult;
	vector<vector<Synonym>> usesResult;
	vector<vector<Synonym>> parentResult;
	vector<vector<Synonym>> parenttResult;
	vector<vector<Synonym>> followsResult;
	vector<vector<Synonym>> followstResult;
		
	vector<Declaration> declarations = queryData.GetDeclarations();
	vector<SelectClause> selects = queryData.GetSelects();


	//To process suchthatClause
		
	vector<SuchThatClause> suchThats = queryData.GetSuchThats();
	vector<SuchThatClause>::iterator iter;
	for (iter = suchThats.begin(); iter != suchThats.end(); iter++)
	{
		SuchThatClause token = *iter;
		switch (token.relationship)
		{
		case MODIFIES:
			modifiesResult = checkModifies(token, selects, declarations);
			break;
		case USES:
			usesResult = checkUses(token, selects, declarations);
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
 		
	return mergeResult(modifiesResult);
}

vector<vector<Synonym>> QueryEvaluator::checkModifies(SuchThatClause suchThat, vector<SelectClause> select, vector<Declaration> declaration){
	vector<vector<int>> possibleResult;
	vector<vector<Synonym>> result;

			
	//to get all the possible result
	possibleResult = getAllPossibleResult(select);
				
	int arg1NeedSelect = -1;
	int arg2NeedSelect = -1;//-1 means no need to select
				
	for (unsigned int i = 0; i<select.size(); i++){
		if (suchThat.arg1.value == select[i].synonym.value)
				arg1NeedSelect = i;
		if (suchThat.arg2.value == select[i].synonym.value)
				arg2NeedSelect = i;
					
	}
				
	if (arg1NeedSelect == -1 && arg2NeedSelect == -1){
		for (unsigned int i = 0; i<possibleResult.size(); i++){ //need to check the Modifies first
			for (unsigned int j = 0; j<possibleResult[i].size(); j++){
				result[i].push_back(convertIntToSynonym(possibleResult[i][j], select[i].synonym.type));
							
			}
						
		}
		return result;			
	}

	else if (arg1NeedSelect != -1 && arg2NeedSelect == -1) {
		for (unsigned int i = 0; i < possibleResult.size(); i++) {
			if (i == arg1NeedSelect) {
				for (unsigned int j = 0; j < possibleResult[i].size(); j++) {
					if (Modifies::IsStmtModifiesVar(possibleResult[i][j], VarTable::GetIndexOf(suchThat.arg2.syn.value))){//arg2 may not be a specific variable name
						result[i].push_back(convertIntToSynonym(possibleResult[i][j], select[i].synonym.type));			
					}								
				}							
			}

			else if (i != arg1NeedSelect) {
				for (unsigned int j = 0; j < possibleResult[i].size(); j++) {
					result[i].push_back(convertIntToSynonym(possibleResult[i][j], select[i].synonym.type));			
				}						
			}					
		}					
	}

	else if (arg2NeedSelect == -1 && arg2NeedSelect != -1) {
		for (unsigned int i = 0; i < possibleResult.size(); i++) {
			if (i == arg2NeedSelect) {
				for (unsigned int j = 0; j < possibleResult[i].size(); j++) {
					if (Modifies::IsStmtModifiesVar(atoi(suchThat.arg1.syn.value.c_str()), possibleResult[i][j])) {//arg1 may not be a specific stmtline
						result[i].push_back(convertIntToSynonym(possibleResult[i][j], select[i].synonym.type));				
					}								
				}							
			}

			else if (i != arg1NeedSelect) {
				for (unsigned int j = 0; j < possibleResult[i].size(); j++) {
					result[i].push_back(convertIntToSynonym(possibleResult[i][j], select[i].synonym.type));								
				}							
			}						
		}					
	}
	
	// arg1NeedSelect&&arg2NeedSelect may be all != -1
	return result;			
}
/*			
vector<vector<Synonym>> QueryEvaluator::checkUses(SuchThatClause suchThat, vector<SelectClause> select, vector<Declaration> declaration)
{
	vector<vector<int>> possibleResult;
	vector<vector<Synonym>> result;	
					
	//to get all the possible result
	possibleResult = getAllPossibleResult(select);
				
	int arg1NeedSelect = -1;
	int arg2NeedSelect = -1;//-1 means no need to select
				
	for (int i = 0; i<select.size(); i++)
	{
		if (suchThat.arg1.value == select[i].synonym.value)
			arg1NeedSelect = i;
		if (suchThat.arg2.value == select[i].synonym.value)
			arg2NeedSelect = i;		
	}
				
	if (arg1NeedSelect == -1 && arg2NeedSelect == -1)
	{
		for (int i = 0; i<possibleResult.size(); i++) { //need to check the Uses first
			for (int j = 0; j<possibleResult[i].size(); j++) {
				result[i].push_back(convertIntToSynonym(possibleResult[i][j], select[i].synonym.type));				
			}				
		}
		return result;			
	}

	else if (arg1NeedSelect != -1 && arg2NeedSelect == -1)
	{
		for (int i = 0; i < possibleResult.size(); i++) {
			if (i == arg1NeedSelect) {
				for (int j = 0; j < possibleResult[i].size(); j++) {
					if (Uses::IsStmtUsingVar(possibleResult[i][j], VarTable::GetIndexOf(suchThat.arg2.syn.value))) {//arg2 may not be a specific variable name
						result[i].push_back(convertIntToSynonym(possibleResult[i][j], select[i].synonym.type));			
					}
								
				}
							
			}
			
			else if (i != arg1NeedSelect) {
				for (int j = 0; j < possibleResult[i].size(); j++) {
					result[i].push_back(convertIntToSynonym(possibleResult[i][j], select[i].synonym.type));				
				}					
			}				
		}			
	}

	else if (arg2NeedSelect == -1 && arg2NeedSelect != -1){
		for (int i = 0; i < possibleResult.size(); i++) {
			if (i == arg2NeedSelect) {
				for (int j = 0; j < possibleResult[i].size(); j++) {
					if (Uses::IsStmtUsingVar(atoi(suchThat.arg1.syn.value.c_str()), possibleResult[i][j])) {//arg1 may not be a specific stmtline
						result[i].push_back(convertIntToSynonym(possibleResult[i][j], select[i].synonym.type));					
					}							
				}					
			}
			
			else if (i != arg1NeedSelect) {
				for (int j = 0; j < possibleResult[i].size(); j++) {
					result[i].push_back(convertIntToSynonym(possibleResult[i][j], select[i].synonym.type));			
				}				
			}
		}			
	}

	// arg1NeedSelect&&arg2NeedSelect may be all != -1			
	return result;		
}
			
Synonym QueryEvaluator::convertIntToSynonym(int index, SynonymType type)
{
	if (type != VARIABLE)
	{				
		char* proglineNum;
		itoa(index, proglineNum, 10);
		Synonym progline = Synonym(proglineNum, type);
					
		return progline;				
	}
		
	else if (type == VARIABLE)
	{
		Synonym variable = Synonym(VarTable::GetVarName(index), VARIABLE);
		return variable;				
	}			
}
			
vector<vector<int>> getAllPossibleResult(vector<SelectClause> select)
{
	set<int> temp;
	vector<vector<int>> possibleResult;

	for (int i = 0; i<select.size(); i++) {
		if (select[i].synonym.type != VARIABLE) {
			temp = StmtTypeTable::GetAllStmtsOfType(select[i].synonym.type);
			set<int>::iterator it;
			for (it = temp.begin(); it != temp.end(); it++) {
				possibleResult[i].push_back((int)*it);				
			}
						
		}

		else if (select[i].synonym.type == VARIABLE) {
			for (int j = 0; j<VarTable::GetSize(); i++) {
				possibleResult[i].push_back(j);			
			}				
		}					
	}

	return possibleResult;		
}
*/