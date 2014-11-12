#include "QueryEvaluator.h"
#include "PKB\Parent.h"
#include "PKB\Follows.h"
#include "PKB\Modifies.h"
#include "PKB\Uses.h"
#include "PKB\StmtTypeTable.h"
#include "PKB\VarTable.h"
#include "QueryProcessor\QueryValidator.h"
#include <iostream>
#include <algorithm>
#include <iterator> 
#include <sstream>
//#include "AbstractWrapper.h"

using namespace std;

QueryEvaluator::QueryEvaluator(void) {}

bool QueryEvaluator::EvaluateQuery(QueryData queryData, list<string> &resultList){

	vector<string> modifiesResult;
	vector<string> usesResult;
	vector<string> suchThatResult;
	vector<string> patternResult;
	vector<string> selectResult;

	bool suchThatHasAnswer = false, patternHasAnswer = false;
	bool hasSuchThat = true, hasPattern = true;

	vector<Declaration> declarations = queryData.GetDeclarations();
	SelectClause select = queryData.GetSelects().at(0);	//only 1 select
	vector<PatternClause> patterns = queryData.GetPatterns();
	vector<SuchThatClause> suchThats = queryData.GetSuchThats();
	

	//evaluate select
	selectResult = EvaluateSelect(select);

	//evaluate such that
	if(!suchThats.empty())
	{
		SuchThatClause suchThat = suchThats.at(0);
		switch (suchThat.relationship)
		{
		case MODIFIES:
			suchThatHasAnswer = EvaluateModifies(select, suchThat, suchThatResult);
			break;

		case USES:
			suchThatHasAnswer = EvaluateModifies(select, suchThat, suchThatResult);
			break;

		case PARENT:
			suchThatHasAnswer = EvaluateParent(select, suchThat, suchThatResult);
			break;

		case PARENTT:
			suchThatHasAnswer = EvaluateParent(select, suchThat, suchThatResult);
			break;

		case FOLLOWS:
			suchThatHasAnswer = EvaluateFollows(select, suchThat, suchThatResult);
			break;

		case FOLLOWST:
			suchThatHasAnswer = EvaluateFollows(select, suchThat, suchThatResult);
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
		PatternClause pattern = patterns.at(0);;
		patternHasAnswer = EvaluatePattern(select, pattern, patternResult);
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
	if(!hasSuchThat && !hasPattern) 
		copy(selectResult.begin(), selectResult.end(), back_inserter(resultList));
	
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

	resultList.sort();

	cout<< "\nFinal result list: ";
	for(list<string>::iterator it = resultList.begin(); it != resultList.end(); ++it)
		cout << *it << " ";
	cout<< "\n";

	return true;
}

//Evaluate Select
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
bool QueryEvaluator::EvaluateParent(SelectClause select, SuchThatClause suchThat, vector<string> &result)
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
bool QueryEvaluator::EvaluateFollows(SelectClause select, SuchThatClause suchThat, vector<string> &result)
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
					
					if(followsAfter == -1) {}
					
					else if(StmtTypeTable::CheckIfStmtOfType(followsAfter, arg2Syn.type)) 
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

					if(followsBefore == -1) {}
					
					else if(StmtTypeTable::CheckIfStmtOfType(followsBefore, arg1Syn.type))
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
					
					if(followsAfter == -1) {}

					else if(StmtTypeTable::CheckIfStmtOfType(followsAfter, arg2Syn.type)) 
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

//Evaluate Modifies and Uses
bool QueryEvaluator::EvaluateModifies(SelectClause select, SuchThatClause suchThat, vector<string> &result)
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
				vector<int> vars;

				if(rel == MODIFIES)	vars = Modifies::GetVarModifiedByStmt(*i);
				else				vars = Uses::GetVarUsedByStmt(*i);

				if(!vars.empty())	result.push_back(ToString(*i));
			}

			if(result.empty()) return false;

			return true;
		}

		else if(arg2Syn.value == selectSyn.value)
		{	
			vector<int> stmts = StmtTypeTable::GetAllStmtsOfType(arg1Syn.type);

			for(vector<int>::iterator i = stmts.begin(); i != stmts.end(); ++i) {
				vector<int> vars;

				if(rel == MODIFIES)	vars = Modifies::GetVarModifiedByStmt(*i);
				else				vars = Uses::GetVarUsedByStmt(*i);

				if(!vars.empty())	{
					vector<string> varString;

					for(vector<int>::iterator j = vars.begin(); j != vars.end(); ++j) 
						varString.push_back(VarTable::GetVarName(*j));	

					result.insert(result.end(),varString.begin(),varString.end());
				}
			}

			if(result.empty()) return false;

			set<string> s( result.begin(), result.end() );
			result.assign( s.begin(), s.end() );

			return true;
		}
		
		else
		{
			vector<int> stmts = StmtTypeTable::GetAllStmtsOfType(arg1Syn.type);

			for(vector<int>::iterator i = stmts.begin(); i != stmts.end(); ++i) {
				vector<int> vars;

				if(rel == MODIFIES)	vars = Modifies::GetVarModifiedByStmt(*i);
				else				vars = Uses::GetVarUsedByStmt(*i);

				if(!vars.empty())	return true;
			}

			return false;
		}
	}

	else if(arg1.type == SYNONYM && arg2.type == UNDERSCORE)
	{		
		vector<string> tempResult;
		vector<int> stmts = StmtTypeTable::GetAllStmtsOfType(arg1Syn.type);

		for(vector<int>::iterator it = stmts.begin(); it != stmts.end(); ++it) {
			vector<int> var;
			
			if(rel == MODIFIES)	var = Modifies::GetVarModifiedByStmt(*it);
			else				var = Uses::GetVarUsedByStmt(*it);
			
			if(!var.empty())
				tempResult.push_back(ToString(*it));
		}

		if(arg1Syn.value == selectSyn.value)
			result = tempResult;

		if(tempResult.empty()) return false;

		return true;
	}

	else if(arg1.type == SYNONYM && arg2.type == IDENT)
	{
		string ident = arg2.value;
		ident.erase(std::remove_if(ident.begin(), ident.end(), [](char x){return isspace(x);}), ident.end());
		ident = ident.substr(1, ident.length()-2);

		int varIndex = VarTable::GetIndexOf(ident);
			
		if(varIndex == -1) return false;


		vector<string> tempResult;
		vector<int> stmts = StmtTypeTable::GetAllStmtsOfType(arg1Syn.type);

		for(vector<int>::iterator it = stmts.begin(); it != stmts.end(); ++it) 
		{
			bool doesModifiesOrUses = false;

			if(rel == MODIFIES)	doesModifiesOrUses = Modifies::IsStmtModifyingVar(*it, varIndex);
			else				doesModifiesOrUses = Uses::IsStmtUsingVar(*it, varIndex);

			if(doesModifiesOrUses)	tempResult.push_back(ToString(*it));
		}

		if(arg1Syn.value == selectSyn.value)
			result = tempResult;

		if(tempResult.empty()) return false;

		return true;
	}

	else if(arg1.type == INTEGER && arg2.type == SYNONYM)
	{
		vector<string> tempResult;
		vector<string> vars;

		if(arg2.syn.type == VARIABLE)
			vars = VarTable::GetAllVar();

		else return false;
		
		for(vector<string>::iterator it = vars.begin(); it != vars.end(); ++it) {
			int arg1Value = atoi(arg1.value.c_str());
			int varIndex = VarTable::GetIndexOf(*it);

			bool doesModifiesOrUses = false;
		
			if(rel == MODIFIES)		doesModifiesOrUses = Modifies::IsStmtModifyingVar(arg1Value,varIndex);
			else					doesModifiesOrUses = Uses::IsStmtUsingVar(arg1Value,varIndex);

			if(doesModifiesOrUses)	tempResult.push_back(*it);
		}

		if(arg2Syn.value == selectSyn.value)
			result = tempResult;

		if(tempResult.empty()) return false;

		return true;
	}

	else if(arg1.type == INTEGER && arg2.type == IDENT)
	{
		string ident = arg2.value;
		ident.erase(std::remove_if(ident.begin(), ident.end(), [](char x){return isspace(x);}), ident.end());
	
		//eliminates " " and get the content
		ident = ident.substr(1, ident.length()-2);

		//get index of ident
		int varIndex = VarTable::GetIndexOf(ident);

		int arg1Value = atoi(arg1.value.c_str());
		bool doesModifiesOrUses = false;

		if(rel == MODIFIES)	doesModifiesOrUses = Modifies::IsStmtModifyingVar(arg1Value, varIndex);
		else				doesModifiesOrUses = Uses::IsStmtUsingVar(arg1Value, varIndex);

		if(doesModifiesOrUses)	return true;
		
		else return true;
	}

	else if(arg1.type == INTEGER && arg2.type == UNDERSCORE)
	{
		int arg1Value = atoi(arg1.value.c_str());

		vector<int> var;
		if(rel == MODIFIES)	var = Modifies::GetVarModifiedByStmt(arg1Value);
		else				var = Uses::GetVarUsedByStmt(arg1Value);

		if(var.empty()) return false;

		return true;
	}

	else return false;
}

//Evaluate Pattern
bool QueryEvaluator::EvaluatePattern(SelectClause select, PatternClause pattern, vector<string> &result)
{
	Synonym selectSyn = select.synonym;
	Synonym patternSyn = pattern.synonym;
	Argument arg1 = pattern.arg1;
	Argument arg2 = pattern.arg2;
	ArgumentType arg1Type = pattern.arg1.type;
	ArgumentType arg2Type = pattern.arg2.type;
	string arg1Value = pattern.arg1.value;
	string arg2Value = pattern.arg2.value;
	
	if(patternSyn.type == ASSIGN)
	{
		if(arg2Type == UNDERSCORE)
		{
			vector<string> tempResult;

			if(arg1Type == UNDERSCORE || arg1Type == SYNONYM)
			{
				vector<int> stmts = StmtTypeTable::GetAllStmtsOfType(ASSIGN);

				for(vector<int>::iterator it = stmts.begin(); it != stmts.end(); ++it)
					tempResult.push_back(ToString(*it));
				
				if(patternSyn.value == selectSyn.value)
					result = tempResult;

				if(tempResult.empty())	return false;
				else					return true;
			}

			else if(arg1Type == IDENT)
			{
				string ident = arg1Value;
				ident.erase(remove_if(ident.begin(), ident.end(), [](char x){return isspace(x);}), ident.end());
				ident = ident.substr(1, ident.length()-2);

				int varIndex = VarTable::GetIndexOf(ident);
				
				if(varIndex != -1)
				{
					vector<int> stmts = Modifies::GetStmtModifyingVar(varIndex);

					if(!stmts.empty())
					{
						for(vector<int>::iterator it = stmts.begin(); it != stmts.end(); ++it)
						{
							if(StmtTypeTable::CheckIfStmtOfType(*it,ASSIGN))
								tempResult.push_back(ToString(*it));
						}
					}

					else return false;

					if(patternSyn.value == selectSyn.value)
						result = tempResult;

					if(tempResult.empty())	return false;
					else					return true;
				}

				else
				{
					cout << "\nIn EvaluatePattern, pattern argument 1 IDENT not found.\n";
					return false;
				}
			}

			else 
			{
				cout << "\nIn EvaluatePattern, invalid pattern argument 1 type.\n";
				return false;
			}
		}

		else if(arg2Type == EXPRESSION)
		{
			vector<string> tempResult;

			Pattern patternObj = CreatePatternObject(arg2Value);
			if(patternObj.expr == "")	return false;

			//cout << "\nhere1\n";
			vector<int> rightResultInt = PatternMatcher::MatchPatternFromRoot(patternObj,true);
			if(rightResultInt.empty())		return false;
			//cout << "\nhere2\n";
			vector<string> rightResult;
			for(vector<int>::iterator it = rightResultInt.begin(); it != rightResultInt.end(); ++it)
				rightResult.push_back(ToString(*it));
			//cout << "\nhere3\n";
			if(arg1Type == UNDERSCORE || SYNONYM)
			{
				//cout << "\nhere4\n";
				tempResult = rightResult;
				return true;
			}

			else if(arg1Type == IDENT)
			{
				vector<string> leftResult;

				string ident = arg1Value;
				ident.erase(remove_if(ident.begin(), ident.end(), [](char x){return isspace(x);}), ident.end());
				ident = ident.substr(1, ident.length()-2);

				int varIndex = VarTable::GetIndexOf(ident);
				
				if(varIndex != -1)
				{
					vector<int> stmts = Modifies::GetStmtModifyingVar(varIndex);

					if(!stmts.empty())
					{
						for(vector<int>::iterator it = stmts.begin(); it != stmts.end(); ++it)
						{
							if(StmtTypeTable::CheckIfStmtOfType(*it,ASSIGN))
								leftResult.push_back(ToString(*it));
						}
					}

					else return false;

					if(leftResult.empty())	return false;

					set_intersection(leftResult.begin(), leftResult.end(), rightResult.begin(), rightResult.end(), back_inserter(tempResult));

					if(patternSyn.value == selectSyn.value)
						result = tempResult;

					if(tempResult.empty())	return false;
					else					return true;
				}

				else
				{
					cout << "\nIn EvaluatePattern, pattern argument 1 IDENT not found.\n";
					return false;
				}
			}

			else 
			{
				cout << "\nIn EvaluatePattern, invalid pattern argument 1 type.\n";
				return false;
			}
		}

		else
		{
			cout << "\nIn EvaluatePattern, invalid pattern argument 2 type.\n";
			return false;
		}
	}

	else 
	{
		cout << "\nIn EvaluatePattern, invalid pattern synonym type.\n";
		return false; //only pattern a() in assignment 4
	}

	return true;
}

//Merge Select && Such That && Pattern
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

//Merge Select && Pattern or Select && Such That
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

//Convert interger to string
string QueryEvaluator::ToString(int i)
{
	string s;
	stringstream out;
	out << i;
	s = out.str();

	return s;
}

//Construct Pattern struct
Pattern QueryEvaluator::CreatePatternObject(string expr)
{
	//remove white spaces and get expression content
	expr.erase(remove_if(expr.begin(), expr.end(), [](char x){return isspace(x);}), expr.end());
	int length = expr.length() - 4;
	expr = expr.substr(2, length);

	vector<string> tokenList;
	string delim = "+";

	QueryValidator::Tokenize(expr, tokenList, delim);

	if(tokenList.size() == 1)
	{
		return Pattern(tokenList.at(0), NULL, NULL);
	}

	else if(tokenList.size() == 2)
	{
		Pattern *left = new Pattern(tokenList.at(0), NULL, NULL);
		Pattern *right = new Pattern(tokenList.at(1), NULL, NULL);
		Pattern p("+", left, right);
		return p;
	}

	else
	{
		cout << "\nIn CreatePatternObject, invalid expression\n";
		return Pattern("", NULL, NULL);
	}
}