#include "QueryEvaluator.h"
#include "PKB\Parent.h"
#include "PKB\Follows.h"
#include "PKB\Modifies.h"
#include "PKB\Uses.h"
#include "PKB\StmtTypeTable.h"
#include "PKB\VarTable.h"
#include <iostream>
#include <algorithm>
#include <iterator> 
#include <sstream>

using namespace std;

QueryEvaluator::QueryEvaluator(void) {}

//resultInteger for select a,s,w,n , resultString for select v. for now assume no select v
bool QueryEvaluator::EvaluateQuery(QueryData queryData, list<string> &resultList){

	//vector<vector<Synonym>> modifiesResult;
	//vector<vector<Synonym>> usesResult;
	vector<string> suchThatResult;
	vector<string> patternResult;
	vector<string> selectResult;

	bool suchThatHasAnswer = false, patternHasAnswer = false;
	bool hasSuchThat = true, hasPattern = true;
		
	vector<Declaration> declarations = queryData.GetDeclarations();
	SelectClause select = queryData.GetSelects().at(0);	//only 1 select
	vector<PatternClause> patterns = queryData.GetPatterns();
	vector<SuchThatClause> suchThats = queryData.GetSuchThats();
	//vector<SelectClause> selects = queryData.GetSelects();
	
	//evaluate select
	selectResult = EvaluateSelect(select);

	//evaluate such that
	if(!suchThats.empty())
	{
		SuchThatClause suchThat = suchThats.at(0);
		switch (suchThat.relationship)
		{
		case MODIFIES:
			//suchThatResult = checkModifies(suchThat, selects, declarations);
			break;

		case USES:
			//suchThatResult = checkUses(suchThat, selects, declarations);
			break;

		case PARENT:
			suchThatHasAnswer = EvaluateParent(declarations, select, suchThat, suchThatResult);
			break;

		case PARENTT:
			suchThatHasAnswer = EvaluateParent(declarations, select, suchThat, suchThatResult);
			break;

		case FOLLOWS:
			suchThatHasAnswer = EvaluateFollows(declarations, select, suchThat, suchThatResult);
			break;

		case FOLLOWST:
			suchThatHasAnswer = EvaluateFollows(declarations, select, suchThat, suchThatResult);
			break;

		case INVALID_RELATIONSHIP_TYPE:
			return false;

		default:
			return false;
		}
	}
 		
	else hasSuchThat = false;

	///evaluate pattern
	if(!patterns.empty())
	{


	}
	
	else hasPattern = false;

	cout<< "\nSelect result list: ";
	for(vector<string>::iterator it = selectResult.begin(); it != selectResult.end(); ++it)
		cout << *it << " ";

	cout<< "\nSuch that result list: ";
	for(vector<string>::iterator it = suchThatResult.begin(); it != suchThatResult.end(); ++it)
		cout << *it << " ";

	cout<< "\nPattern result list: ";
	for(vector<string>::iterator it = patternResult.begin(); it != patternResult.end(); ++it)
		cout << *it << " ";

	//merge select, such that , pattern result and pass back to caller

	//only select, no such that no pattern
	if(!hasSuchThat && !hasPattern) {
		copy(selectResult.begin(), selectResult.end(), back_inserter(resultList));
	}

	else if(hasSuchThat && !hasPattern) {
		if(suchThatHasAnswer && !suchThatResult.empty()) 
			resultList = MergeResult(selectResult, suchThatResult);	

		else if(suchThatHasAnswer && suchThatResult.empty()) 
			copy(selectResult.begin(), selectResult.end(), back_inserter(resultList));

		else resultList.clear();
	}

	else if(!hasSuchThat && hasPattern) {
		if(patternHasAnswer && !patternResult.empty())	
			resultList = MergeResult(selectResult, patternResult);	

		else if(patternHasAnswer && patternResult.empty()) 
			copy(selectResult.begin(), selectResult.end(), back_inserter(resultList));

		else resultList.clear();
	}

	else if(hasSuchThat && hasPattern) {
		//both must have answer, if not then empty result
		if(suchThatHasAnswer && patternHasAnswer && !suchThatResult.empty() && !patternResult.empty())
			resultList = MergeResult(selectResult, suchThatResult, patternResult);	
		
		else if(suchThatHasAnswer && patternHasAnswer && !suchThatResult.empty() && patternResult.empty())
			resultList = MergeResult(selectResult, suchThatResult);	

		else if(suchThatHasAnswer && patternHasAnswer && suchThatResult.empty() && !patternResult.empty())
			resultList = MergeResult(selectResult, patternResult);	

		else if(suchThatHasAnswer && patternHasAnswer && suchThatResult.empty() && patternResult.empty())
			copy(selectResult.begin(), selectResult.end(), back_inserter(resultList));

		else resultList.clear();
	}

	cout<< "\nFinal result list: ";
	for(list<string>::iterator it = resultList.begin(); it != resultList.end(); ++it)
		cout << *it << " ";
	cout<< "\n";

	return true;
}


vector<string> QueryEvaluator::EvaluateSelect(SelectClause select)
{
	vector<int> stmts;
	vector<string> result;
	bool isVar = false;

	switch(select.synonym.type)
	{
		case ASSIGN:
			stmts = StmtTypeTable::GetAllStmtsOfType(ASSIGN);
			break;

		case STMT:
			stmts = StmtTypeTable::GetAllStmtsOfType(STMT);
			break;

		case WHILE:
			stmts = StmtTypeTable::GetAllStmtsOfType(WHILE);
			break;

		case VARIABLE:
			result = VarTable::GetAllVar();
			isVar = true;
			break;

		case PROG_LINE:
			stmts = StmtTypeTable::GetAllStmtsOfType(STMT);
			break;

		case INVALID_SYNONYM_TYPE:
			break;

		default:
			break;
	}

	if(isVar) return result;

	//convert vec<int> to vec<string>
	for(vector<int>::iterator it = stmts.begin(); it != stmts.end(); ++it)
		result.push_back(ToString(*it));

	return result;
}

//Evaluate Parent and Parent*
bool QueryEvaluator::EvaluateParent(vector<Declaration> declaration, SelectClause select, SuchThatClause suchThat, vector<string> &result)
{
	Argument arg1 = suchThat.arg1;
	Argument arg2 = suchThat.arg2;
	Synonym arg1Syn = suchThat.arg1.syn;
	Synonym arg2Syn = suchThat.arg2.syn;
	Synonym selectSyn = select.synonym;
	RelationshipType rel = suchThat.relationship;


	if(arg1.type == SYNONYM && arg2.type == SYNONYM)
	{
		if(arg1Syn.value == arg2Syn.value)
			return false;

		else if(arg1Syn.value == selectSyn.value)
		{
			vector<int> stmts = StmtTypeTable::GetAllStmtsOfType(arg1Syn.type);

			for(vector<int>::iterator i = stmts.begin(); i != stmts.end(); ++i) {
				vector<int> children;

				if(rel == PARENT)	children = Parent::GetChildrenOf(*i);
				else				children = Parent::GetChildrenTOf(*i);

				for(vector<int>::iterator j = children.begin(); j != children.end(); ++j) {
					if(StmtTypeTable::CheckIfStmtOfType(*j, arg2Syn.type)) {
						result.push_back(ToString(*i));
						break;
					}
				}
			}

			if(result.empty()) return false;

			return true;
		}

		else if(arg2Syn.value == selectSyn.value)
		{	
			vector<int> stmts = StmtTypeTable::GetAllStmtsOfType(arg2Syn.type);
			
			for(vector<int>::iterator i = stmts.begin(); i != stmts.end(); ++i) {
				if(rel == PARENT) {
					int parent = Parent::GetParentOf(*i);

					if(parent == -1) {}	//if no parent

					else if(StmtTypeTable::CheckIfStmtOfType(parent, arg1Syn.type))
						result.push_back(ToString(*i));
				}

				else {
					vector<int> parent = Parent::GetParentTOf(*i);

					for(vector<int>::iterator j = parent.begin(); j != parent.end(); ++j) {
						if(StmtTypeTable::CheckIfStmtOfType(*j, arg1Syn.type)) {
							result.push_back(ToString(*i));
							break;
						}
					}
				}
			}

			if(result.empty()) return false;

			return true;
		}
		
		else
		{
			vector<int> stmts = StmtTypeTable::GetAllStmtsOfType(arg1Syn.type);

			for(vector<int>::iterator i = stmts.begin(); i != stmts.end(); ++i) {
				vector<int> children;

				if(rel == PARENT)	children = Parent::GetChildrenOf(*i);
				else				children = Parent::GetChildrenTOf(*i);

				for(vector<int>::iterator j = children.begin(); j != children.end(); ++j) {
					if(StmtTypeTable::CheckIfStmtOfType(*j, arg2Syn.type)) 
						return true;

					else return false;
				}
			}
		}
	}

	else if(arg1.type == SYNONYM && arg2.type == UNDERSCORE)
	{		
		vector<string> tempResult;
		vector<int> stmts = StmtTypeTable::GetAllStmtsOfType(arg1Syn.type);

		for(vector<int>::iterator it = stmts.begin(); it != stmts.end(); ++it) {
			vector<int> children;
			
			if(rel == PARENT)	children = Parent::GetChildrenOf(*it);
			else				children = Parent::GetChildrenTOf(*it);
			
			if(!children.empty())
				tempResult.push_back(ToString(*it));
		}

		if(arg1Syn.value == selectSyn.value)
			result = tempResult;

		if(tempResult.empty()) return false;

		return true;
	}

	else if(arg1.type == UNDERSCORE && arg2.type == SYNONYM)
	{
		vector<string> tempResult;
		vector<int> stmts = StmtTypeTable::GetAllStmtsOfType(arg2Syn.type);

		for(vector<int>::iterator it = stmts.begin(); it != stmts.end(); ++it) 
		{
			if(rel == PARENT) {
				int parent = Parent::GetParentOf(*it);
				if(parent != -1)
					tempResult.push_back(ToString(*it));
			}

			else {
				vector<int> parent = Parent::GetParentTOf(*it);
				if(!parent.empty())	
					tempResult.push_back(ToString(*it));
			}
		}

		if(arg2Syn.value == selectSyn.value)
			result = tempResult;

		if(tempResult.empty()) return false;

		return true;
	}

	else if(arg1.type == SYNONYM && arg2.type == INTEGER)
	{
		vector<string> tempResult;
		vector<int> stmts = StmtTypeTable::GetAllStmtsOfType(arg1Syn.type);

		for(vector<int>::iterator it = stmts.begin(); it != stmts.end(); ++it) 
		{
			int arg2Value = atoi(arg2.value.c_str());
			bool isParent = false;

			if(rel == PARENT)	isParent = Parent::IsParent(*it, arg2Value);
			else				isParent = Parent::IsParentT(*it, arg2Value);

			if(isParent)		tempResult.push_back(ToString(*it));
		}

		if(arg1Syn.value == selectSyn.value)
			result = tempResult;

		if(tempResult.empty()) return false;

		return true;
	}

	else if(arg1.type == INTEGER && arg2.type == SYNONYM)
	{
		vector<string> tempResult;
		vector<int> stmts = StmtTypeTable::GetAllStmtsOfType(arg2Syn.type);

		for(vector<int>::iterator it = stmts.begin(); it != stmts.end(); ++it) {
			int arg1Value = atoi(arg1.value.c_str());
			bool isParent = false;

			if(rel == PARENT)	isParent = Parent::IsParent(arg1Value, *it);
			else				isParent = Parent::IsParentT(arg1Value, *it);

			if(isParent)		tempResult.push_back(ToString(*it));
		}

		if(arg2Syn.value == selectSyn.value)
			result = tempResult;

		if(tempResult.empty()) return false;

		return true;
	}

	else if(arg1.type == UNDERSCORE && arg2.type == INTEGER)
	{
		int arg2Value = atoi(arg2.value.c_str());

		if(rel == PARENT) {
			if(Parent::GetParentOf(arg2Value) == -1)
				return false;

			else return true;
		}

		else {
			vector<int> parent = Parent::GetParentTOf(arg2Value);
			if(parent.empty())	return false;
			else return true;
		}
	}

	else if(arg1.type == INTEGER && arg2.type == UNDERSCORE)
	{
		int arg1Value = atoi(arg1.value.c_str());

		vector<int> children;
		if(rel == PARENT)	children = Parent::GetChildrenOf(arg1Value);
		else				children = Parent::GetChildrenTOf(arg1Value);

		if(children.empty()) return false;

		return true;
	}

	else if(arg1.type == INTEGER && arg2.type == INTEGER)
	{
		int arg1Value = atoi(arg1.value.c_str());
		int arg2Value = atoi(arg2.value.c_str());
		
		if(rel == PARENT)	return Parent::IsParent(arg1Value, arg2Value);
		else				return Parent::IsParentT(arg1Value, arg2Value);
	}

	else if(arg1.type == UNDERSCORE && arg2.type == UNDERSCORE)
	{
		return Parent::HasAnyParents();
	}

	else return false;
}

//Evaluate Follows and Follows*
bool QueryEvaluator::EvaluateFollows(vector<Declaration> declaration, SelectClause select, SuchThatClause suchThat, vector<string> &result)
{
	Argument arg1 = suchThat.arg1;
	Argument arg2 = suchThat.arg2;
	Synonym arg1Syn = suchThat.arg1.syn;
	Synonym arg2Syn = suchThat.arg2.syn;
	Synonym selectSyn = select.synonym;
	RelationshipType rel = suchThat.relationship;


	if(arg1.type == SYNONYM && arg2.type == SYNONYM)
	{
		if(arg1Syn.value == arg2Syn.value)
			return false;

		else if(arg1Syn.value == selectSyn.value)
		{
			vector<int> stmts = StmtTypeTable::GetAllStmtsOfType(arg1Syn.type);

			for(vector<int>::iterator i = stmts.begin(); i != stmts.end(); ++i) {
				
				if(rel == FOLLOWS)	
				{
					int followsAfter = Follows::GetFollowsAfter(*i);
					if(StmtTypeTable::CheckIfStmtOfType(followsAfter, arg2Syn.type)) 
						result.push_back(ToString(*i));
				}

				else				
				{
					vector<int> followsAfter = Follows::GetFollowsTAfter(*i);

					for(vector<int>::iterator j = followsAfter.begin(); j != followsAfter.end(); ++j) {
						if(StmtTypeTable::CheckIfStmtOfType(*j, arg2Syn.type)) {
							result.push_back(ToString(*i));
							break;
						}
					}
				}	
			}

			if(result.empty()) return false;

			return true;
		}

		else if(arg2Syn.value == selectSyn.value)
		{
			vector<int> stmts = StmtTypeTable::GetAllStmtsOfType(arg2Syn.type);

			for(vector<int>::iterator i = stmts.begin(); i != stmts.end(); ++i) {
				if(rel == FOLLOWS) {
					int followsBefore = Follows::GetFollowsBefore(*i);

					if(StmtTypeTable::CheckIfStmtOfType(followsBefore, arg1Syn.type))
						result.push_back(ToString(*i));
				}

				else {
					vector<int> followsBefore = Follows::GetFollowsTBefore(*i);

					for(vector<int>::iterator j = followsBefore.begin(); j != followsBefore.end(); ++j) {
						if(StmtTypeTable::CheckIfStmtOfType(*j, arg1Syn.type)) {
							result.push_back(ToString(*i));
							break;
						}
					}
				}
			}

			if(result.empty()) return false;

			return true;
		}
		
		else
		{
			vector<int> stmts = StmtTypeTable::GetAllStmtsOfType(arg1Syn.type);

			for(vector<int>::iterator i = stmts.begin(); i != stmts.end(); ++i) 
			{
				if(rel == FOLLOWS)	
				{
					int followsAfter = Follows::GetFollowsAfter(*i);
					if(StmtTypeTable::CheckIfStmtOfType(followsAfter, arg2Syn.type)) 
						return true;
				}

				else				
				{
					vector<int> followsAfter = Follows::GetFollowsTAfter(*i);

					for(vector<int>::iterator j = followsAfter.begin(); j != followsAfter.end(); ++j) {
						if(StmtTypeTable::CheckIfStmtOfType(*j, arg2Syn.type))
							return true;
					}
				}	
			}

			return false;
		}
	}

	else if(arg1.type == SYNONYM && arg2.type == UNDERSCORE)
	{		
		vector<string> tempResult;
		vector<int> stmts = StmtTypeTable::GetAllStmtsOfType(arg1Syn.type);

		for(vector<int>::iterator it = stmts.begin(); it != stmts.end(); ++it) 
		{
			if(rel == FOLLOWS) {
				int followsAfter = Follows::GetFollowsAfter(*it);
				if(followsAfter != -1)
					tempResult.push_back(ToString(*it));
			}

			else {
				vector<int> followsAfter = Follows::GetFollowsTAfter(*it);
				if(!followsAfter.empty())	
					tempResult.push_back(ToString(*it));
			}
		}

		if(arg1Syn.value == selectSyn.value)
			result = tempResult;

		if(tempResult.empty()) return false;

		return true;
	}

	else if(arg1.type == UNDERSCORE && arg2.type == SYNONYM)
	{
		vector<string> tempResult;
		vector<int> stmts = StmtTypeTable::GetAllStmtsOfType(arg2Syn.type);

		for(vector<int>::iterator it = stmts.begin(); it != stmts.end(); ++it) 
		{
			if(rel == FOLLOWS) {
				int followsBefore = Follows::GetFollowsBefore(*it);
				if(followsBefore != -1)
					tempResult.push_back(ToString(*it));
			}

			else {
				vector<int> followsBefore = Follows::GetFollowsTBefore(*it);
				if(!followsBefore.empty())	
					tempResult.push_back(ToString(*it));
			}
		}

		if(arg2Syn.value == selectSyn.value)
			result = tempResult;

		if(tempResult.empty()) return false;

		return true;
	}

	else if(arg1.type == SYNONYM && arg2.type == INTEGER)
	{
		vector<string> tempResult;
		vector<int> stmts = StmtTypeTable::GetAllStmtsOfType(arg1Syn.type);

		for(vector<int>::iterator it = stmts.begin(); it != stmts.end(); ++it) 
		{
			int arg2Value = atoi(arg2.value.c_str());
			bool isFollows = false;

			if(rel == FOLLOWS)	isFollows = Follows::IsFollows(*it, arg2Value);
			else				isFollows = Follows::IsFollowsT(*it, arg2Value);

			if(isFollows)		tempResult.push_back(ToString(*it));
		}

		if(arg1Syn.value == selectSyn.value)
			result = tempResult;

		if(tempResult.empty()) return false;

		return true;
	}

	else if(arg1.type == INTEGER && arg2.type == SYNONYM)
	{
		vector<string> tempResult;
		vector<int> stmts = StmtTypeTable::GetAllStmtsOfType(arg2Syn.type);

		for(vector<int>::iterator it = stmts.begin(); it != stmts.end(); ++it) {
			int arg1Value = atoi(arg1.value.c_str());
			bool isFollows = false;

			if(rel == FOLLOWS)	isFollows = Follows::IsFollows(arg1Value, *it);
			else				isFollows = Follows::IsFollowsT(arg1Value, *it);

			if(isFollows)		tempResult.push_back(ToString(*it));
		}

		if(arg2Syn.value == selectSyn.value)
			result = tempResult;

		if(tempResult.empty()) return false;

		return true;
	}

	else if(arg1.type == UNDERSCORE && arg2.type == INTEGER)
	{
		int arg2Value = atoi(arg2.value.c_str());

		if(rel == FOLLOWS)	
		{
			int followsBefore = Follows::GetFollowsBefore(arg2Value);
			if(followsBefore == -1) return false;
		}
		else 
		{
			vector<int> followsBefore = Follows::GetFollowsTBefore(arg2Value);
			if(followsBefore.empty()) return false;
		}

		return true;
	}

	else if(arg1.type == INTEGER && arg2.type == UNDERSCORE)
	{
		int arg1Value = atoi(arg1.value.c_str());

		if(rel == FOLLOWS)	
		{
			int followsAfter = Follows::GetFollowsAfter(arg1Value);
			if(followsAfter == -1) return false;
		}
		else 
		{
			vector<int> followsAfter = Follows::GetFollowsTAfter(arg1Value);
			if(followsAfter.empty()) return false;
		}

		return true;
	}

	else if(arg1.type == INTEGER && arg2.type == INTEGER)
	{
		int arg1Value = atoi(arg1.value.c_str());
		int arg2Value = atoi(arg2.value.c_str());
		
		if(rel == FOLLOWS)	return Follows::IsFollows(arg1Value, arg2Value);
		else				return Follows::IsFollowsT(arg1Value, arg2Value);
	}

	else if(arg1.type == UNDERSCORE && arg2.type == UNDERSCORE)
	{
		return Follows::HasAnyFollows();
	}

	else return false;
}

list<string> QueryEvaluator::MergeResult(vector<string> selectResult, vector<string> suchThatResult, vector<string> patternResult)
{
	vector<string> intermediateResult, finalResult;
	list<string> resultList;

    sort(selectResult.begin(), selectResult.end());
    sort(suchThatResult.begin(), suchThatResult.end());
	sort(patternResult.begin(), patternResult.end());

    set_intersection(selectResult.begin(), selectResult.end(), suchThatResult.begin(), suchThatResult.end(), back_inserter(intermediateResult));
	set_intersection(intermediateResult.begin(), intermediateResult.end(), patternResult.begin(), patternResult.end(), back_inserter(finalResult));

	//copy vector to list (autotester use list)
	copy(finalResult.begin(), finalResult.end(), back_inserter(resultList));
    
	return resultList;
}

list<string> QueryEvaluator::MergeResult(vector<string> selectResult, vector<string> suchThatPatternResult)
{
	vector<string> finalResult;
	list<string> resultList;

    sort(selectResult.begin(), selectResult.end());
    sort(suchThatPatternResult.begin(), suchThatPatternResult.end());

    set_intersection(selectResult.begin(), selectResult.end(), suchThatPatternResult.begin(), suchThatPatternResult.end(), back_inserter(finalResult));

	copy(finalResult.begin(), finalResult.end(), back_inserter(resultList));
    
	return resultList;
}

string QueryEvaluator::ToString(int i)
{
	string s;
	stringstream out;
	out << i;
	s = out.str();

	return s;
}
/*
vector<vector<Synonym>> QueryEvaluator::checkModifies(SuchThatClause suchThat, vector<SelectClause> select, vector<Declaration> declaration){
	vector<vector<int>> possibleResult;
	vector<vector<Synonym>> result;

			
	//to get all the possible result
	possibleResult = getAllPossibleResult(select);
				
	int arg1NeedSelect = -1;
	int arg2NeedSelect = -1;//-1 means no need to select
				
	for (int i = 0; i<select.size(); i++){
		if (suchThat.arg1.value == select[i].synonym.value)
				arg1NeedSelect = i;
		if (suchThat.arg2.value == select[i].synonym.value)
				arg2NeedSelect = i;
					
	}
				
	if (arg1NeedSelect == -1 && arg2NeedSelect == -1){
		for (int i = 0; i<possibleResult.size(); i++){ //need to check the Modifies first
			for (int j = 0; j<possibleResult[i].size(); j++){
				result[i].push_back(convertIntToSynonym(possibleResult[i][j], select[i].synonym.type));
							
			}
						
		}
		return result;			
	}

	else if (arg1NeedSelect != -1 && arg2NeedSelect == -1) {
		for (int i = 0; i < possibleResult.size(); i++) {
			if (i == arg1NeedSelect) {
				for (int j = 0; j < possibleResult[i].size(); j++) {
					if (Modifies::IsStmtModifiesVar(possibleResult[i][j], VarTable::GetIndexOf(suchThat.arg2.syn.value))){//arg2 may not be a specific variable name
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

	else if (arg2NeedSelect == -1 && arg2NeedSelect != -1) {
		for (int i = 0; i < possibleResult.size(); i++) {
			if (i == arg2NeedSelect) {
				for (int j = 0; j < possibleResult[i].size(); j++) {
					if (Modifies::IsStmtModifiesVar(atoi(suchThat.arg1.syn.value.c_str()), possibleResult[i][j])) {//arg1 may not be a specific stmtline
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