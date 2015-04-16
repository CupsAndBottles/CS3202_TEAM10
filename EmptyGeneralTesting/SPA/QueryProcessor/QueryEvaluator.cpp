#include "QueryEvaluator.h"
#include "..\PKB\Parent.h"
#include "..\PKB\Follows.h"
#include "..\PKB\Modifies.h"
#include "..\PKB\Uses.h"
#include "..\PKB\StmtTypeTable.h"
#include "..\PKB\ConstTable.h"
#include "..\PKB\VarTable.h"
#include "..\PKB\ProcTable.h"
#include "..\PKB\Affects.h"
#include "..\PKB\Next.h"
#include "..\PKB\Calls.h"
#include "..\QueryProcessor\QueryPreProcessor.h"
#include "..\QueryProcessor\QueryData.h"
#include <iostream>
#include <algorithm>
#include <iterator> 
#include <sstream>
#include "..\..\AutoTester\source\AbstractWrapper.h"

using namespace std;

QueryEvaluator::QueryEvaluator(void) {}

bool QueryEvaluator::EvaluateQuery(QueryData queryData, list<string> &resultList)
{
	vector<Declaration> declarations = queryData.GetDeclarations();
	vector<SelectClause> selects = queryData.GetSelects();
	vector<PatternClause> patterns = queryData.GetPatterns();
	vector<SuchThatClause> suchThats = queryData.GetSuchThats();
	vector<WithClause> withs = queryData.GetWiths();
	std::vector<std::pair<ClauseType,int>> clauseSequence = queryData.GetClauseSequence();
	bool hasAnswer = true;
	bool isSelectAll = false;

	//only select, no suchthat/pattern/with
	if(patterns.size() == 0 && suchThats.size() == 0 && withs.size() == 0)
		isSelectAll = true;

	//Initialize result table with declared synonyms
	intermediateResult.Initialize(declarations);

	//if there is no such that/pattern/with, just skip
	if(!isSelectAll)
	{
		cout << "claus size : " << clauseSequence.size() << "\n";
		//loop clause sequence
		for(std::vector<std::pair<ClauseType,int>>::iterator it = clauseSequence.begin(); it != clauseSequence.end(); ++it)
		{
			PrintIntermediateResult();

			ClauseType clauseType = it->first;
			int clauseIndex = it->second;

			cout << "clause " << it->first << "\n";
			cout << "clause index" << it->second<< "\n";

			if(clauseType == SUCHTHAT)
			{
				SuchThatClause suchThat = suchThats.at(clauseIndex);

				switch (suchThat.relationship)
				{
					case MODIFIES:
					case USES:
						hasAnswer = EvaluateModifies(suchThat);
						break;

					case PARENT:
					case PARENTT:
						hasAnswer = EvaluateParent(suchThat);
						break;

					case FOLLOWS:
					case FOLLOWST:
						hasAnswer = EvaluateFollows(suchThat);
						break;

					case CALLS:
					case CALLST:
						hasAnswer = EvaluateCalls(suchThat);
						break;

					case NEXT:
					case NEXTT:
						hasAnswer = EvaluateNext(suchThat);
						break;

					case AFFECTS:
					case AFFECTST:
						hasAnswer = EvaluateAffects(suchThat);
						break;

					case CONTAINS:
					case CONTAINST:
						hasAnswer = EvaluateContains(suchThat);
						break;

					case SIBLING:
						hasAnswer = EvaluateSibling(suchThat);
						break;

					case AFFECTSBIP:
						hasAnswer = EvaluateAffectsBip(suchThat);
						break;

					case NEXTBIP:
					case NEXTBIPT:
						hasAnswer = EvaluateNextBip(suchThat);
						break;

					case INVALID_RELATIONSHIP_TYPE:
					default:
						cout << "No matching relationship in Such That clause.\n";
						resultList.clear();
						return true;
				}

				if(!hasAnswer) {
					cout << "No answer in Such That clause.\n";
					break;
					//return true;
				}
			}

			else if(clauseType == PATTERN)
			{	
				hasAnswer = EvaluatePattern(patterns[clauseIndex]);

				if(!hasAnswer) 
				{
					cout << "No answer in Pattern clause.\n";
					break;
				}
			}
			
			else if(clauseType == WITH)
			{
				hasAnswer = EvaluateWith(withs[clauseIndex]);
				
				if(!hasAnswer) 
				{
					cout << "No answer in With clause.\n";
					break;
				}
			}

			else 
			{
				cout << "In EvaluateQuery: invalid clause type.\n";
				return false;
			}

			if(AbstractWrapper::GlobalStop)	return false;
		}		
	}

	//select all
	else
	{
		//if BOOLEAN, no need waste time insert PKB data
		if(!selects.empty() && selects[0].synonym.type != BOOLEAN)
		{
			for(int i=0; i < selects.size(); ++i)
			{
				Synonym selectSyn = selects[i].synonym;

				if(selectSyn.type == ASSIGN || selectSyn.type == STMT || selectSyn.type == WHILE ||
					selectSyn.type == IF || selectSyn.type == CALL|| selectSyn.type == PROG_LINE)
				{
					//stmtTypeTable
					vector<int> result_int;
					vector<string> result;
					result_int = StmtTypeTable::GetAllStmtsOfType(selectSyn.type);

					//remove duplicate
					set<int> s( result_int.begin(), result_int.end() );
					result_int.assign( s.begin(), s.end() );

					/*cout << "\nInput list into table: ";
					for(int i=0; i<result_int.size(); ++i)
						cout << result_int[i] << " ";
					cout << "\n";*/

					intermediateResult.InsertList(selectSyn.value , result_int);
					intermediateResult.Print();
				}

				else if(selectSyn.type == CONSTANT)
				{
					//constTable
					vector<int> result_int;
					vector<string> result;
					result_int = ConstTable::GetAllConst();

					//remove duplicate
					set<int> s( result_int.begin(), result_int.end() );
					result_int.assign( s.begin(), s.end() );

					intermediateResult.InsertList(selectSyn.value , result_int);
					intermediateResult.Print();
				}

				else if(selectSyn.type == PROCEDURE)
				{
					//procTable
					vector<string> result = ProcTable::GetAllProcNames();
					intermediateResult.InsertList(selectSyn.value , result);
					intermediateResult.Print();
				}

				else if(selectSyn.type == VARIABLE)
				{
					//varTable
					vector<string> result = VarTable::GetAllVarNames(); 
					intermediateResult.InsertList(selectSyn.value , result);
					intermediateResult.Print();
				}

				else
				{
					cout << "In EvaluateQuery: Invalid select type.\n";
					resultList.clear();
					return false;
				}		
			}
		}
	}
	
	//select single
	if(selects.size() == 1)
	{
		Synonym selectSyn = selects[0].synonym;

		//BOOLEAN
		if(selectSyn.type == BOOLEAN)
		{	
			//select BOOLEAN
			if(isSelectAll)
			{
				resultList.push_back("true");
				return true;
			}

			//select BOOLEAN such that...
			else
			{
				if(hasAnswer)
				{
					resultList.push_back("true");
					return true;
				}

				else
				{
					resultList.push_back("false");
					return true;
				}			
			}
		}

		//All the other SynonymType
		else 
		{
			//select a
			//select a such that...
			if(hasAnswer)
			{
				intermediateResult.GetResultSingle(selectSyn.value ,resultList);

				
				//if hasAnswre has result is empty that means select a such that parent(w,s)
				//select synonym does not occur in any clause
				//get all data of select synonym from pkb and return this
				if(resultList.empty())
				{
					vector<string> data = GetDataFromPKB(selectSyn);
					copy( data.begin(), data.end(), back_inserter( resultList ) );
					resultList.sort();
				}


			}
			else
			{
				resultList.clear();
				return true;
			}
		}
	}

	//select <tuple>
	else if(selects.size() > 1)
	{
		vector<string> selectSynList;
		for(int i=0; i < selects.size(); ++i)
			selectSynList.push_back(selects[i].synonym.value);

		//select <a,w,v> , return all possible permutation of synonyms
		//select <a,w,v> such that...
		if(hasAnswer)
		{
			//intermediateResult.GetResultTuple(selectSynList ,resultList);
		}

		else
		{
			resultList.clear();
			return true;
		}
	}

	else
	{
		cout << "In EvaluateQuery: Invalid select size.\n";
		resultList.clear();
		return false;
	}

	//resultList.sort();
	//resultList.unique();

	return true;
}


bool QueryEvaluator::EvaluateParent(SuchThatClause suchThat)
{
	Argument arg1 = suchThat.arg1;
	Argument arg2 = suchThat.arg2;
	Synonym arg1Syn = suchThat.arg1.syn;
	Synonym arg2Syn = suchThat.arg2.syn;
	RelationshipType rel = suchThat.relationship;
	
	cout << "Evaluating Parent( " << arg1.value << " , " << arg2.value << ")\n";

	if(arg1.type == SYNONYM) 
	{
		int validCount = 0;

		if(arg2.type == SYNONYM)
		{
			if(arg1Syn.value == arg2Syn.value) {
				cout << "In EvaluateParent, both arg1 and arg2 has the same synonym\n";
				return false;
			}

			vector<int> parent, child;
			bool valid = false;
			bool usingIntermediateResult_parent = false, usingIntermediateResult_child = false;

			//get appropriate stmt, while, if, prog_line
			if(intermediateResult.IsListEmpty(arg1.syn))
			{
				std::cout << "No intermediate result for " << arg1.syn.value << ", get all stmts\n";
				parent = StmtTypeTable::GetAllStmtsOfType(arg1.syn.type);
			}

			else 
			{
				std::cout << "Get " << arg1.syn.value << " from intermediate result table";
				intermediateResult.GetList(arg1.syn.value , parent);
				usingIntermediateResult_parent = true;
			}

			//get appropriate stmt, assign, while, if, prog_line, call
			if(intermediateResult.IsListEmpty(arg2.syn))
			{
				std::cout << "No intermediate result for " << arg2.syn.value << ", get all stmts\n";
				child = StmtTypeTable::GetAllStmtsOfType(arg2.syn.type);
			}

			else 
			{
				std::cout << "Get " << arg2.syn.value << " from intermediate result table";
				intermediateResult.GetList(arg2.syn.value , child);
				usingIntermediateResult_child = true;
			}

			//loop parent.size() * child.size() times, if all invalid, validCount will be 0, return false
			validCount = parent.size() * child.size();

			for(vector<int>::iterator it_parent = parent.begin(); it_parent != parent.end(); ++it_parent) 
			{
				for(vector<int>::iterator it_child = child.begin(); it_child != child.end(); ++it_child) 
				{
					bool isParent = false;
					//convert int to string to use with intermediateResult
					string parent_str = ITOS(*it_parent);
					string child_str = ITOS(*it_child);
		
					if(rel == PARENT)	isParent = Parent::IsParent(*it_parent, *it_child);
					else				isParent = Parent::IsParentT(*it_parent, *it_child);
				
					//both synonym list taken from result, so both must exist in result, question is whether there is a link between them
					if(usingIntermediateResult_parent && usingIntermediateResult_child)
					{
						if(isParent) {
							//check HasLink(), if yes, do nothing, else make pair
							bool isDirectLink;
							if(!intermediateResult.HasLinkBetweenColumns(arg1Syn.value, parent_str, arg2Syn.value, child_str , isDirectLink))
							{
								//if has link, do nothing, 
								//if no link && (1 and 2 both has no links), insert pair
								//if no link && (either 1 or 2 both has links), insert pair
								//if no link && (1 and 2 both have links)		
								//		if HasDirectLink(1 has link to synonym of 2 or vice versa), insert pair
								//		if HasIndirectLink(1 has no link to synonym of 2), do nothing

								//HasLink will return an bool hasDirectLink to state whether the link is direct or indirect
								//true = direct, false = indirect, only correct if HasLink is true


								//both have links
								if(intermediateResult.HasLink(arg1Syn.value, parent_str) && intermediateResult.HasLink(arg2Syn.value, child_str))
								{
									if(isDirectLink)
									{
										intermediateResult.InsertPair(arg1Syn.value, parent_str, arg2Syn.value, child_str);
									}

									else
									{
										//indirect link, do nothing
									}
								}

								//at least one no links
								else
								{
									intermediateResult.InsertPair(arg1Syn.value, parent_str, arg2Syn.value, child_str);
								}
							}
						}
						else 
						{
							//dont remove, if has link just remove the link, if no link do nothing, update table to remove excess
							bool dummy;
							if(intermediateResult.HasLinkBetweenColumns(arg1Syn.value, parent_str, arg2Syn.value, child_str, dummy))
								intermediateResult.Unlink(arg1Syn.value, parent_str, arg2Syn.value, child_str);

							//intermediateResult.RemovePair(arg1Syn.value, *it_parent, arg2Syn.value, *it_child);
							--validCount;
						}
					}

					//at least one of the synonym list is new, or both
					else
					{
						if(isParent) {
							//insert pair
							intermediateResult.InsertPair(arg1Syn.value, *it_parent, arg2Syn.value, *it_child);
						}
						else 
						{
							//do nothing
							--validCount;
						}
					}
				}
			}

			//after looping, do a update to remove any element without link between this 2 column
			if(usingIntermediateResult_parent && usingIntermediateResult_child)
			{
				intermediateResult.RemoveElementsWithoutLink(arg1Syn.value , arg2Syn.value);
			}
		}

		else if(arg2.type == INTEGER)
		{
			vector<int> stmts;
			bool valid = false;
			bool usingIntermediateResult = false;

			if(intermediateResult.IsListEmpty(arg1.syn))
			{
				stmts = StmtTypeTable::GetAllStmtsOfType(arg1.syn.type);
			}

			else 
			{
				intermediateResult.GetList(arg1.syn.value , stmts);
				usingIntermediateResult = true;
			}

			validCount = stmts.size();
			for(vector<int>::iterator it = stmts.begin(); it != stmts.end(); ++it) 
			{
				int arg2Value = atoi(arg2.value.c_str());
				bool isParent = false;

				if(rel == PARENT)	isParent = Parent::IsParent(*it, arg2Value);
				else				isParent = Parent::IsParentT(*it, arg2Value);

				if(usingIntermediateResult)
				{
					if(isParent) {}
					else 
					{
						intermediateResult.Remove(arg1.value , *it);
						--validCount;
					}
				}
				else
				{
					if(isParent) intermediateResult.Insert(arg1.value , *it);
					else --validCount;
				}
			}
		}

		else if(arg2.type == UNDERSCORE)
		{
			vector<int> stmts;
			bool valid = false;
			bool usingIntermediateResult = false;

			if(intermediateResult.IsListEmpty(arg1.syn))
			{
				stmts = StmtTypeTable::GetAllStmtsOfType(arg1.syn.type);
			}

			else 
			{
				intermediateResult.GetList(arg1.syn.value , stmts);
				usingIntermediateResult = true;
			}

			validCount = stmts.size();

			for(vector<int>::iterator it = stmts.begin(); it != stmts.end(); ++it) 
			{
				vector<int> children;
			
				if(rel == PARENT)	children = Parent::GetChildrenOf(*it);
				else				children = Parent::GetChildrenTOf(*it);
			
				if(usingIntermediateResult)
				{
					if(!children.empty()) {}
					else 
					{
						intermediateResult.Remove(arg1.value , *it);
						--validCount;
					}
				}
				else
				{
					if(!children.empty()) intermediateResult.Insert(arg1.value , *it);
					else --validCount;
				}
			}
		}

		else 
		{
			cout << "\nIn EvaluateParent, invalid Parent argument 2 type.\n";
			return false;
		}

		//all statements do not satisfy Parent()
		if(validCount == 0) 
		{
			cout << "Parent() is not satisfied.\n";			
			return false;
		}
		return true;
	}

	else if(arg2.type == SYNONYM)
	{
		vector<int> stmts;
		bool usingIntermediateResult = false;

		if(intermediateResult.IsListEmpty(arg2.syn))
		{
			stmts = StmtTypeTable::GetAllStmtsOfType(arg2.syn.type);
		}

		else 
		{
			intermediateResult.GetList(arg2.syn.value , stmts);
			usingIntermediateResult = true;
		}

		int validCount = stmts.size();

		for(vector<int>::iterator it = stmts.begin(); it != stmts.end(); ++it) 
		{
			if(arg1.type == INTEGER)
			{
				int arg1Value = STOI(arg1.value);
				bool isParent = false;

				if(rel == PARENT)	isParent = Parent::IsParent(arg1Value, *it);
				else				isParent = Parent::IsParentT(arg1Value, *it);

				//add another function HasLink(arg1, arg2) for intermediateresult, need?

				if(usingIntermediateResult)
				{
					//remove if invalid, do nothing if valid
					if(isParent) {}
					else
					{
						intermediateResult.Remove(arg2Syn.value , *it);
						--validCount;
					}
				}

				else
				{
					//insert if valid, do nothing if invalid
					if(isParent) intermediateResult.Insert(arg2Syn.value , *it);
					else --validCount;
				}
			}

			//Parent(_ , a)
			else if(arg1.type == UNDERSCORE)
			{
				if(rel == PARENT) {
					int parent = Parent::GetParentOf(*it);

					if(usingIntermediateResult)
					{
						//remove if invalid, do nothing if valid
						if(parent != -1) {}
						else 
						{
							intermediateResult.Remove(arg2Syn.value , *it);
							--validCount;
						}
					}
					else
					{
						//insert if valid, do nothing if invalid
						if(parent != -1) intermediateResult.Insert(arg2Syn.value , *it);
						else --validCount;
					}
				}

				else {
					vector<int> parent = Parent::GetParentTOf(*it);

					if(usingIntermediateResult)
					{
						if(!parent.empty())	 {}
						else 
						{
							intermediateResult.Remove(arg2Syn.value , *it);
							--validCount;
						}
					}
					else
					{
						if(!parent.empty())	 intermediateResult.Insert(arg2Syn.value , *it);
						else --validCount;
					}
				}
			}

			else 
			{
				cout << "\nIn EvaluateParent, invalid Parent argument 1 type.\n";
				return false;
			}
		}

		//all statements do not satisfy Parent()
		if(validCount == 0)
		{
			cout << "Parent() is not satisfied.\n";			
			return false;
		}
		return true;
	}

	else if(arg1.type == UNDERSCORE && arg2.type == INTEGER)
	{
		int arg2Value = STOI(arg2.value);

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
		int arg1Value = STOI(arg1.value);

		vector<int> children;
		if(rel == PARENT)	children = Parent::GetChildrenOf(arg1Value);
		else				children = Parent::GetChildrenTOf(arg1Value);

		if(children.empty()) return false;

		return true;
	}

	else if(arg1.type == INTEGER && arg2.type == INTEGER)
	{
		int arg1Value = STOI(arg1.value);
		int arg2Value = STOI(arg2.value);
		
		if(rel == PARENT)	return Parent::IsParent(arg1Value, arg2Value);
		else				return Parent::IsParentT(arg1Value, arg2Value);
	}

	else if(arg1.type == UNDERSCORE && arg2.type == UNDERSCORE)
	{
		return Parent::HasAnyParents();
	}

	else {
		cout << "In EvaluateParent, no matching arguments.\n";		
		return false;
	}
}


bool QueryEvaluator::EvaluateFollows(SuchThatClause suchThat)
{
	Argument arg1 = suchThat.arg1;
	Argument arg2 = suchThat.arg2;
	Synonym arg1Syn = suchThat.arg1.syn;
	Synonym arg2Syn = suchThat.arg2.syn;
	RelationshipType rel = suchThat.relationship;

	cout << "Evaluating Follows( " << arg1.value << " , " << arg2.value << ")\n";

	if (arg1.type == SYNONYM) {
		int validCount = 0;

		if (arg2.type == SYNONYM) {

			if(arg1Syn.value == arg2Syn.value) {
				cout << "In EvaluateFollows, both arg1 and arg2 has the same synonym\n";
				return false;
			}

			vector<int> beforeStmt, afterStmt;
			bool valid = false;
			bool usingIntermediateResult_after = false, usingIntermediateResult_before = false;

			//get appropriate stmt, while, if, prog_line
			if (intermediateResult.IsListEmpty(arg1.syn)) {
				std::cout << "No intermediate result for " << arg1.syn.value << ", get all stmts\n";
				beforeStmt = StmtTypeTable::GetAllStmtsOfType(arg1.syn.type);
			}

			else {
				std::cout << "Get " << arg1.syn.value << " from intermediate result table";
				intermediateResult.GetList(arg1.syn.value, beforeStmt);
				usingIntermediateResult_before = true;
			}

			//get appropriate stmt, assign, while, if, prog_line, call
			if (intermediateResult.IsListEmpty(arg2.syn)) {
				std::cout << "No intermediate result for " << arg2.syn.value << ", get all stmts\n";
				afterStmt = StmtTypeTable::GetAllStmtsOfType(arg2.syn.type);
			}

			else {
				std::cout << "Get " << arg2.syn.value << " from intermediate result table";
				intermediateResult.GetList(arg2.syn.value, afterStmt);
				usingIntermediateResult_after = true;
			}

			//loop afterStmt.size() * beforeStmt.size() times, if all invalid, validCount will be 0, return false
			validCount = beforeStmt.size() * afterStmt.size();
			cout << "valid: " <<  beforeStmt.size() << " x " << afterStmt.size() <<"\n";

			for (vector<int>::iterator it_before = beforeStmt.begin(); it_before != beforeStmt.end(); ++it_before) {
				for (vector<int>::iterator it_after = afterStmt.begin(); it_after != afterStmt.end(); ++it_after) {
					bool isFollows = false;
					//convert int to string to use with intermediateResult
					string before_str = ITOS(*it_before);
					string after_str = ITOS(*it_after);

					if (rel == FOLLOWS)	isFollows = Follows::IsFollows(*it_before, *it_after);
					else				isFollows = Follows::IsFollowsT(*it_before, *it_after);

					cout << "follows*(" << *it_before << "," << *it_after << ") is " << isFollows << "\n";

					//both synonym list taken from result, so both must exist in result, question is whether there is a link between them
					if (usingIntermediateResult_after && usingIntermediateResult_before) {
						if (isFollows) {
							//check HasLink(), if yes, do nothing, else make pair
							bool isDirectLink;
							if (!intermediateResult.HasLinkBetweenColumns(arg1Syn.value, before_str, arg2Syn.value, after_str, isDirectLink)) {
								//both have links
								if (intermediateResult.HasLink(arg1Syn.value, before_str) && intermediateResult.HasLink(arg2Syn.value, after_str)) {
									if (isDirectLink) {
										intermediateResult.InsertPair(arg1Syn.value, before_str, arg2Syn.value, after_str);
									}
									else {
										//indirect link, do nothing
									}
								}

								//at least one no links
								else {
									intermediateResult.InsertPair(arg1Syn.value, before_str, arg2Syn.value, after_str);
								}
							}
						} 
						else {
							//dont remove, if has link just remove the link, if no link do nothing, update table to remove excess
							bool dummy;
							if (intermediateResult.HasLinkBetweenColumns(arg1Syn.value, before_str, arg2Syn.value, after_str, dummy))
								intermediateResult.Unlink(arg1Syn.value, before_str, arg2Syn.value, after_str);

							//intermediateResult.RemovePair(arg1Syn.value, *it_after, arg2Syn.value, *it_before);
							--validCount;
						}
					}

					//at least one of the synonym list is new, or both
					else {
						if (isFollows) {
							//insert pair
							intermediateResult.InsertPair(arg1Syn.value, *it_before, arg2Syn.value, *it_after);
						} else {
							//do nothing
							--validCount;
						}
					}
				}
			}

			//after looping, do a update to remove any element without link between this 2 column
			//if (usingIntermediateResult_after && usingIntermediateResult_before) {
				intermediateResult.RemoveElementsWithoutLink(arg1Syn.value, arg2Syn.value);
			//}
		}

		//Follows(a,5)
		else if (arg2.type == INTEGER) {
			vector<int> stmts;
			bool valid = false;
			bool usingIntermediateResult = false;

			if (intermediateResult.IsListEmpty(arg1.syn)) {
				stmts = StmtTypeTable::GetAllStmtsOfType(arg1.syn.type);
			}

			else {
				intermediateResult.GetList(arg1.syn.value, stmts);
				usingIntermediateResult = true;
			}

			validCount = stmts.size();
			for (vector<int>::iterator it = stmts.begin(); it != stmts.end(); ++it) {
				int arg2Value = atoi(arg2.value.c_str());
				bool isFollows = false;

				if (rel == FOLLOWS)	isFollows = Follows::IsFollows(*it, arg2Value);
				else				isFollows = Follows::IsFollowsT(*it, arg2Value);

				if (usingIntermediateResult) {
					if (isFollows) {} else {
						intermediateResult.Remove(arg1Syn.value, *it);
						--validCount;
					}
				} else {
					if (isFollows) intermediateResult.Insert(arg1Syn.value, *it);
					else --validCount;
				}
			}
		}

		// Follows(a, _)
		else if (arg2.type == UNDERSCORE) {
			vector<int> stmts;
			bool valid = false;
			bool usingIntermediateResult = false;

			if (intermediateResult.IsListEmpty(arg1.syn)) {
				stmts = StmtTypeTable::GetAllStmtsOfType(arg1.syn.type);
			}

			else {
				intermediateResult.GetList(arg1.syn.value, stmts);
				usingIntermediateResult = true;
			}

			validCount = stmts.size();

			for (vector<int>::iterator it = stmts.begin(); it != stmts.end(); ++it) {
				bool isFollows;

				if (rel == FOLLOWS)	isFollows = Follows::GetFollowsAfter(*it) != -1;
				else				isFollows = !Follows::GetFollowsTAfter(*it).empty();

				if (usingIntermediateResult) {
					if (isFollows) {} else {
						intermediateResult.Remove(arg1Syn.value, *it);
						--validCount;
					}
				} else {
					if (isFollows) intermediateResult.Insert(arg1Syn.value, *it);
					else --validCount;
				}
			}
		}

		else {
			cout << "\nIn EvaluateFollows, invalid Follows argument 2 type.\n";
			return false;
		}

		//all statements do not satisfy Follows()
		if (validCount == 0) {
			cout << "Follows() is not satisfied.\n";
			return false;
		}
		return true;
	}

	//Follows (smth, syn)
	else if (arg2.type == SYNONYM) {
		vector<int> stmts;
		bool usingIntermediateResult = false;

		if (intermediateResult.IsListEmpty(arg2.syn)) {
			stmts = StmtTypeTable::GetAllStmtsOfType(arg2.syn.type);
		}

		else {
			intermediateResult.GetList(arg2.syn.value, stmts);
			usingIntermediateResult = true;
		}

		int validCount = stmts.size();

		for (vector<int>::iterator it = stmts.begin(); it != stmts.end(); ++it) {
			bool isFollows = false;

			// Follows(1, syn)
			if (arg1.type == INTEGER) {
				int arg1Value = STOI(arg1.value);

				if (rel == FOLLOWS)	isFollows = Follows::IsFollows(arg1Value, *it);
				else				isFollows = Follows::IsFollowsT(arg1Value, *it);
			}

			//Follows(_ , syn)
			else if (arg1.type == UNDERSCORE) {
				if (rel == FOLLOWS)	isFollows = Follows::GetFollowsBefore(*it) != -1;
				else				isFollows = !Follows::GetFollowsTBefore(*it).empty();
			}

			else {
				cout << "\nIn EvaluateFollows, invalid argument 1 type.\n";
				return false;
			}

			if (usingIntermediateResult) {
				//remove if invalid, do nothing if valid
				if (isFollows) {} 
				else {
					intermediateResult.Remove(arg2Syn.value, *it);
					--validCount;
				}
			} else {
				//insert if valid, do nothing if invalid
				if (isFollows) intermediateResult.Insert(arg2Syn.value, *it);
				else --validCount;
			}
		}

		//all statements do not satisfy Follows()
		if (validCount == 0) {
			cout << "Follows() is not satisfied.\n";
			return false;
		}
		return true;
	}

	else if (arg1.type == UNDERSCORE && arg2.type == INTEGER) {
		int arg2Value = STOI(arg2.value);
		bool isFollowing;

		if (rel == FOLLOWS)	isFollowing = Follows::GetFollowsBefore(arg2Value) != -1;
		else				isFollowing = !Follows::GetFollowsTBefore(arg2Value).empty();

		return isFollowing;
	}

	else if (arg1.type == INTEGER && arg2.type == UNDERSCORE) {
		int arg1Value = STOI(arg1.value);
		bool isFollows;

		if (rel == FOLLOWS)	isFollows = Follows::GetFollowsAfter(arg1Value) != -1;
		else				isFollows = !Follows::GetFollowsTAfter(arg1Value).empty();

		return isFollows;
	}

	else if (arg1.type == INTEGER && arg2.type == INTEGER) {
		int arg1Value = STOI(arg1.value);
		int arg2Value = STOI(arg2.value);

		if (rel == FOLLOWS)	return Follows::IsFollows(arg1Value, arg2Value);
		else				return Follows::IsFollowsT(arg1Value, arg2Value);
	}

	else if (arg1.type == UNDERSCORE && arg2.type == UNDERSCORE) {
		return Follows::HasAnyFollows();
	}

	else {
		cout << "In EvaluateFollows, no matching arguments.\n";
		return false;
	}
}


bool QueryEvaluator::EvaluateModifies(SuchThatClause suchThat)
{
	cout << "In EvaluateModifies\n";
	Argument arg1 = suchThat.arg1;
	Argument arg2 = suchThat.arg2;
	Synonym arg1Syn = suchThat.arg1.syn;
	Synonym arg2Syn = suchThat.arg2.syn;
	RelationshipType rel = suchThat.relationship;

	//Modifies(a/s/w/if/call/n,v)
	if(arg1.type == SYNONYM && (arg1Syn.type == ASSIGN || arg1Syn.type == STMT || arg1Syn.type == WHILE || 
								arg1Syn.type == IF || arg1Syn.type == CALL || arg1Syn.type == PROG_LINE))
	{
		if(arg2.type == SYNONYM)
		{
			//------------Get intermediate result of type arg1------------
			vector<int> stmts;
			bool usingIntermediateResult_stmts = false;

			if (intermediateResult.IsListEmpty(arg1.syn)) {
				//std::cout << "No intermediate result for " << arg1.syn.value << ", get all stmts\n";
				stmts = StmtTypeTable::GetAllStmtsOfType(arg1Syn.type);
			}

			else {
				//std::cout << "Get " << arg1.syn.value << " from intermediate result table";
				intermediateResult.GetList(arg1Syn.value, stmts);
				usingIntermediateResult_stmts = true;
			}

			//------------Get intermediate result of type arg2------------
			vector<string> vars;
			bool usingIntermediateResult_vars = false;

			if(intermediateResult.IsListEmpty(arg2.syn)) {
				vars = VarTable::GetAllVarNames();
			}

			else {
				intermediateResult.GetList(arg2Syn.value , vars);
				usingIntermediateResult_vars = true;
			}


			//loop afterStmt.size() * beforeStmt.size() times, if all invalid, validCount will be 0, return false
			int validCount = stmts.size() * vars.size();

			for (vector<int>::iterator it_stmts = stmts.begin(); it_stmts != stmts.end(); ++it_stmts) {
				for (vector<string>::iterator it_vars = vars.begin(); it_vars != vars.end(); ++it_vars) {

					int varIndex = VarTable::GetIndexOfVar(*it_vars);

					bool doesModifiesOrUses = false;
		
					if(rel == MODIFIES)		doesModifiesOrUses = Modifies::IsStmtModifyingVar(*it_stmts,varIndex);
					else					doesModifiesOrUses = Uses::IsStmtUsingVar(*it_stmts,varIndex);

					//both synonym list taken from result, so both must exist in result, question is whether there is a link between them
					if (usingIntermediateResult_stmts && usingIntermediateResult_vars) {
						if (doesModifiesOrUses) {
							bool isDirectLink;
							if (!intermediateResult.HasLinkBetweenColumns(arg1Syn.value, *it_stmts, arg2Syn.value, *it_vars, isDirectLink)) {
								//both have links
								if (intermediateResult.HasLink(arg1Syn.value, *it_stmts) && intermediateResult.HasLink(arg2Syn.value, *it_vars)) {
									if (isDirectLink) {
										intermediateResult.InsertPair(arg1Syn.value, *it_stmts, arg2Syn.value, *it_vars);
									}
									else {
										//indirect link, do nothing
									}
								}

								//at least one no links
								else {
									intermediateResult.InsertPair(arg1Syn.value, *it_stmts, arg2Syn.value, *it_vars);
								}
							}
						} 
						else {
							//dont remove, if has link just remove the link, if no link do nothing, update table to remove excess
							bool dummy;
							if (intermediateResult.HasLinkBetweenColumns(arg1Syn.value, *it_stmts, arg2Syn.value, *it_vars, dummy))
								intermediateResult.Unlink(arg1Syn.value, *it_stmts, arg2Syn.value, *it_vars);

							//intermediateResult.RemovePair(arg1Syn.value, *it_after, arg2Syn.value, *it_before);
							--validCount;
						}
					}

					//at least one of the synonym list is new, or both
					else {
						if (doesModifiesOrUses) {
							intermediateResult.InsertPair(arg1Syn.value, *it_stmts, arg2Syn.value, *it_vars);
						} 
						else {
							--validCount;
						}
					}
				}
			}

			//after looping, do a update to remove any element without link between this 2 column
			//if (usingIntermediateResult_stmts && usingIntermediateResult_vars) {
				intermediateResult.RemoveElementsWithoutLink(arg1Syn.value, arg2Syn.value);
			//}
		}

		else if(arg2.type == IDENT)
		{
			//------------Get arg2 Var index------------
			string ident_var = arg2.value;
			ident_var.erase(std::remove_if(ident_var.begin(), ident_var.end(), [](char x){return isspace(x);}), ident_var.end());
	
			//eliminates " " and get the content
			ident_var = ident_var.substr(1, ident_var.length()-2);

			//get index of ident
			int varIndex = VarTable::GetIndexOfVar(ident_var);
			if(varIndex == -1) return false;

			vector<int> stmts;
			bool usingIntermediateResult = false;

			if(intermediateResult.IsListEmpty(arg1.syn))
			{
				stmts = StmtTypeTable::GetAllStmtsOfType(arg1Syn.type);
			}

			else 
			{
				intermediateResult.GetList(arg1.value , stmts);
				usingIntermediateResult = true;
			}

			int validCount = stmts.size();

			for(vector<int>::iterator it = stmts.begin(); it != stmts.end(); ++it) 
			{
				bool doesModifiesOrUses = false;

				if(rel == MODIFIES)	doesModifiesOrUses = Modifies::IsStmtModifyingVar(*it, varIndex);
				else				doesModifiesOrUses = Uses::IsStmtUsingVar(*it, varIndex);

				if(usingIntermediateResult)
				{
					//remove if invalid, do nothing if valid
					if(doesModifiesOrUses) {}
					else
					{
						intermediateResult.Remove(arg1Syn.value , *it);
						--validCount;
					}
				}

				else
				{
					//insert if valid, do nothing if invalid
					if(doesModifiesOrUses) intermediateResult.Insert(arg1Syn.value , *it);
					else --validCount;
				}
			}

			if(validCount == 0)
			{
				cout << "Modifies() or Uses() is not satisfied.\n";			
				return false;
			}

			return true;
		}

		//Modifies(a,_)
		else if(arg2.type == UNDERSCORE)
		{
			vector<int> stmts;
			bool usingIntermediateResult = false;

			if(intermediateResult.IsListEmpty(arg1.syn))
			{
				stmts = StmtTypeTable::GetAllStmtsOfType(arg1Syn.type);
			}

			else 
			{
				intermediateResult.GetList(arg1.value , stmts);
				usingIntermediateResult = true;
			}

			int validCount = stmts.size();

			for(vector<int>::iterator it = stmts.begin(); it != stmts.end(); ++it) 
			{
				vector<int> var;

				if(rel == MODIFIES)	var = Modifies::GetVarModifiedByStmt(*it);
				else				var = Uses::GetVarUsedByStmt(*it);

				if(usingIntermediateResult)
				{
					//remove if invalid, do nothing if valid
					if(!var.empty()) {}
					else
					{
						intermediateResult.Remove(arg1Syn.value , *it);
						--validCount;
					}
				}

				else
				{
					//insert if valid, do nothing if invalid
					if(!var.empty())	intermediateResult.Insert(arg1Syn.value , *it);
					else --validCount;
				}
			}

			if(validCount == 0)
			{
				cout << "Modifies() or Uses() is not satisfied.\n";			
				return false;
			}

			return true;
		}

		else 
		{
			cout << "\nIn EvaluateModifies, invalid Modifies argument 2 type.\n";
			return false;
		}
	}

	//Modifies(p,v)
	else if(arg1.type == SYNONYM && arg1Syn.type == PROCEDURE)
	{
		//------------Get intermediate result of type arg1------------
		vector<string> procs;
		bool usingIntermediateResult_procs = false;

		if (intermediateResult.IsListEmpty(arg1.syn)) {
			//std::cout << "No intermediate result for " << arg1.syn.value << ", get all stmts\n";
			procs = ProcTable::GetAllProcNames();
		}

		else {
			//std::cout << "Get " << arg1.syn.value << " from intermediate result table";
			intermediateResult.GetList(arg1Syn.value, procs);
			usingIntermediateResult_procs = true;
		}

		//Modifies(p,v)
		if(arg2.type == SYNONYM)
		{
			//------------Get intermediate result of type arg2------------
			vector<string> vars;
			bool usingIntermediateResult_vars = false;

			if(intermediateResult.IsListEmpty(arg2.syn)) {
				vars = VarTable::GetAllVarNames();
			}

			else {
				intermediateResult.GetList(arg2Syn.value , vars);
				usingIntermediateResult_vars = true;
			}


			//loop afterStmt.size() * beforeStmt.size() times, if all invalid, validCount will be 0, return false
			int validCount = procs.size() * vars.size();

			for (vector<string>::iterator it_procs = procs.begin(); it_procs != procs.end(); ++it_procs) {
				for (vector<string>::iterator it_vars = vars.begin(); it_vars != vars.end(); ++it_vars) {

					int varIndex = VarTable::GetIndexOfVar(*it_vars);
					int procIndex = ProcTable::GetIndexOfProc(*it_procs);

					bool doesModifiesOrUses = false;
		
					if(rel == MODIFIES)		doesModifiesOrUses = Modifies::IsProcModifyingVar(procIndex,varIndex);
					else					doesModifiesOrUses = Uses::IsProcUsingVar(procIndex,varIndex);

					//both synonym list taken from result, so both must exist in result, question is whether there is a link between them
					if (usingIntermediateResult_procs && usingIntermediateResult_vars) {
						if (doesModifiesOrUses) {
							bool isDirectLink;
							if (!intermediateResult.HasLinkBetweenColumns(arg1Syn.value, *it_procs, arg2Syn.value, *it_vars, isDirectLink)) {
								//both have links
								if (intermediateResult.HasLink(arg1Syn.value, *it_procs) && intermediateResult.HasLink(arg2Syn.value, *it_vars)) {
									if (isDirectLink) {
										intermediateResult.InsertPair(arg1Syn.value, *it_procs, arg2Syn.value, *it_vars);
									}
									else {
										//indirect link, do nothing
									}
								}

								//at least one no links
								else {
									intermediateResult.InsertPair(arg1Syn.value, *it_procs, arg2Syn.value, *it_vars);
								}
							}
						} 
						else {
							//dont remove, if has link just remove the link, if no link do nothing, update table to remove excess
							bool dummy;
							if (intermediateResult.HasLinkBetweenColumns(arg1Syn.value, *it_procs, arg2Syn.value, *it_vars, dummy))
								intermediateResult.Unlink(arg1Syn.value, *it_procs, arg2Syn.value, *it_vars);

							//intermediateResult.RemovePair(arg1Syn.value, *it_after, arg2Syn.value, *it_before);
							--validCount;
						}
					}

					//at least one of the synonym list is new, or both
					else {
						if (doesModifiesOrUses) {
							intermediateResult.InsertPair(arg1Syn.value, *it_procs, arg2Syn.value, *it_vars);
						} 
						else {
							--validCount;
						}
					}
				}
			}

			//after looping, do a update to remove any element without link between this 2 column
			//if (usingIntermediateResult_procs && usingIntermediateResult_vars) {
				intermediateResult.RemoveElementsWithoutLink(arg1Syn.value, arg2Syn.value);
			//}
		}

		//Modifies(p,"x")
		else if(arg2.type == IDENT)
		{
			//------------Get arg2 Var index------------
			string ident_var = arg2.value;
			ident_var.erase(std::remove_if(ident_var.begin(), ident_var.end(), [](char x){return isspace(x);}), ident_var.end());
	
			//eliminates " " and get the content
			ident_var = ident_var.substr(1, ident_var.length()-2);

			//get index of ident
			int varIndex = VarTable::GetIndexOfVar(ident_var);
			if(varIndex == -1) return false;

			int validCount = procs.size();

			for(vector<string>::iterator it = procs.begin(); it != procs.end(); ++it) 
			{
				bool doesModifiesOrUses = false;
				int procIndex = ProcTable::GetIndexOfProc(*it);

				if(rel == MODIFIES)	doesModifiesOrUses = Modifies::IsProcModifyingVar(procIndex, varIndex);
				else				doesModifiesOrUses = Uses::IsProcUsingVar(procIndex, varIndex);

				if(usingIntermediateResult_procs)
				{
					//remove if invalid, do nothing if valid
					if(doesModifiesOrUses) {}
					else
					{
						intermediateResult.Remove(arg1Syn.value , *it);
						--validCount;
					}
				}

				else
				{
					//insert if valid, do nothing if invalid
					if(doesModifiesOrUses) intermediateResult.Insert(arg1Syn.value , *it);
					else --validCount;
				}
			}

			if(validCount == 0)
			{
				cout << "Modifies() or Uses() is not satisfied.\n";			
				return false;
			}

			return true;
		}

		//Modifies(p,_)
		else if(arg2.type == UNDERSCORE)
		{
			int validCount = procs.size();

			for(vector<string>::iterator it = procs.begin(); it != procs.end(); ++it) 
			{
				vector<int> var;
				int procIndex = ProcTable::GetIndexOfProc(*it);

				if(rel == MODIFIES)	var = Modifies::GetVarModifiedByProc(procIndex);
				else				var = Uses::GetVarUsedByProc(procIndex);

				if(usingIntermediateResult_procs)
				{
					//remove if invalid, do nothing if valid
					if(!var.empty()) {}
					else
					{
						intermediateResult.Remove(arg1Syn.value , *it);
						--validCount;
					}
				}

				else
				{
					//insert if valid, do nothing if invalid
					if(!var.empty())	intermediateResult.Insert(arg1Syn.value , *it);
					else --validCount;
				}
			}

			if(validCount == 0)
			{
				cout << "Modifies() or Uses() is not satisfied.\n";			
				return false;
			}

			return true;
		}

		else 
		{
			cout << "\nIn EvaluateModifies, invalid Modifies argument 2 type.\n";
			return false;
		}
	}

	else if(arg1.type == INTEGER)
	{
		//Modifies(5,v)
		if(arg2.type == SYNONYM)
		{
			vector<string> vars;
			bool usingIntermediateResult = false;

			if(intermediateResult.IsListEmpty(arg2.syn))
			{
				vars = VarTable::GetAllVarNames();
			}

			else 
			{
				intermediateResult.GetList(arg2.value , vars);
				usingIntermediateResult = true;
			}

			int validCount = vars.size();

			for(vector<string>::iterator it = vars.begin(); it != vars.end(); ++it) 
			{
				int arg1Value = STOI(arg1.value);
				int varIndex = VarTable::GetIndexOfVar(*it);

				bool doesModifiesOrUses = false;
		
				if(rel == MODIFIES)		doesModifiesOrUses = Modifies::IsStmtModifyingVar(arg1Value,varIndex);
				else					doesModifiesOrUses = Uses::IsStmtUsingVar(arg1Value,varIndex);

				if(usingIntermediateResult)
				{
					//remove if invalid, do nothing if valid
					if(doesModifiesOrUses) {}
					else
					{
						intermediateResult.Remove(arg2Syn.value , *it);
						--validCount;
					}
				}

				else
				{
					//insert if valid, do nothing if invalid
					if(doesModifiesOrUses) intermediateResult.Insert(arg2Syn.value , *it);
					else --validCount;
				}
			}

			if(validCount == 0)
			{
				cout << "Modifies() or Uses() is not satisfied.\n";			
				return false;
			}

			return true;
		}

		//Modifies(5,"x")
		else if(arg2.type == IDENT)
		{
			string ident = arg2.value;
			ident.erase(std::remove_if(ident.begin(), ident.end(), [](char x){return isspace(x);}), ident.end());
	
			//eliminates " " and get the content
			ident = ident.substr(1, ident.length()-2);

			//get index of ident
			int varIndex = VarTable::GetIndexOfVar(ident);
			if(varIndex == -1) return false;

			int arg1Value = atoi(arg1.value.c_str());
			bool doesModifiesOrUses = false;

			if(rel == MODIFIES)	doesModifiesOrUses = Modifies::IsStmtModifyingVar(arg1Value, varIndex);
			else				doesModifiesOrUses = Uses::IsStmtUsingVar(arg1Value, varIndex);

			if(doesModifiesOrUses)	return true;
		
			else return true;
		}

		//Modifies(5,_)
		else if(arg2.type == UNDERSCORE)
		{
			int arg1Value = atoi(arg1.value.c_str());

			vector<int> var;
			if(rel == MODIFIES)	var = Modifies::GetVarModifiedByStmt(arg1Value);
			else				var = Uses::GetVarUsedByStmt(arg1Value);

			if(var.empty()) return false;

			return true;
		}

		else 
		{
			cout << "\nIn EvaluateModifies, invalid Modifies argument 2 type.\n";
			return false;
		}
	}
	
	else if(arg1.type == IDENT) //for procedure name, Modifies("procedure",v) etc
	{
		//------------Get arg1 Proc index------------
		string ident = arg1.value;
		ident.erase(std::remove_if(ident.begin(), ident.end(), [](char x){return isspace(x);}), ident.end());
	
		//eliminates " " and get the content
		ident = ident.substr(1, ident.length()-2);

		//get index of ident
		int procIndex = ProcTable::GetIndexOfProc(ident);
		if(procIndex == -1) return false;


		//Modifies("Solo",v)
		if(arg2.type == SYNONYM)
		{
			//------------Get intermediate result of type arg2------------
			vector<string> vars;
			bool usingIntermediateResult = false;

			if(intermediateResult.IsListEmpty(arg2.syn))
			{
				vars = VarTable::GetAllVarNames();
			}

			else 
			{
				intermediateResult.GetList(arg2.value , vars);
				usingIntermediateResult = true;
			}

			int validCount = vars.size();

			//------------Check if Modifies("proc",v) or Uses("proc",v)-----------
			for(vector<string>::iterator it = vars.begin(); it != vars.end(); ++it) 
			{
				int varIndex = VarTable::GetIndexOfVar(*it);

				bool doesModifiesOrUses = false;
		
				if(rel == MODIFIES)		doesModifiesOrUses = Modifies::IsProcModifyingVar(procIndex,varIndex);
				else					doesModifiesOrUses = Uses::IsProcUsingVar(procIndex,varIndex);

				if(usingIntermediateResult)
				{
					//remove if invalid, do nothing if valid
					if(doesModifiesOrUses) {}
					else
					{
						intermediateResult.Remove(arg2Syn.value , *it);
						--validCount;
					}
				}

				else
				{
					//insert if valid, do nothing if invalid
					if(doesModifiesOrUses) intermediateResult.Insert(arg2Syn.value , *it);
					else --validCount;
				}
			}

			if(validCount == 0)
			{
				cout << "Modifies() or Uses() is not satisfied.\n";			
				return false;
			}

			return true;
		}

		//Modifies("Solo","x")
		else if(arg2.type == IDENT)
		{
			//------------Get arg2 Var index------------
			string ident_var = arg2.value;
			ident_var.erase(std::remove_if(ident_var.begin(), ident_var.end(), [](char x){return isspace(x);}), ident_var.end());
	
			//eliminates " " and get the content
			ident_var = ident_var.substr(1, ident_var.length()-2);

			//get index of ident
			int varIndex = VarTable::GetIndexOfVar(ident_var);
			if(varIndex == -1) return false;

			//------------Check if Modifies("proc","x") or Uses("proc","x")-----------
			bool doesModifiesOrUses = false;

			if(rel == MODIFIES)	doesModifiesOrUses = Modifies::IsProcModifyingVar(procIndex, varIndex);
			else				doesModifiesOrUses = Uses::IsProcUsingVar(procIndex, varIndex);

			if(doesModifiesOrUses)	return true;
		
			else return true;
		}

		//Modifies("Solo",_)
		else if(arg2.type == UNDERSCORE)
		{
			//------------Check if Modifies("proc",_) or Uses("proc",_)-----------
			vector<int> var;
			if(rel == MODIFIES)	var = Modifies::GetVarModifiedByProc(procIndex);
			else				var = Uses::GetVarUsedByProc(procIndex);

			if(var.empty()) return false;

			return true;
		}

		else 
		{
			cout << "\nIn EvaluateModifies, invalid Modifies argument 2 type.\n";
			return false;
		}
	}

	else 
	{
		cout << "\nIn EvaluateModifies, invalid Modifies argument 1 type.\n";
		return false;
	}
}


bool QueryEvaluator::EvaluateCalls(SuchThatClause suchThat)
{
	Argument arg1 = suchThat.arg1;
	Argument arg2 = suchThat.arg2;
	Synonym arg1Syn = suchThat.arg1.syn;
	Synonym arg2Syn = suchThat.arg2.syn;
	RelationshipType rel = suchThat.relationship;

	cout << "Evaluating Calls( " << arg1.value << " , " << arg2.value << ")\n";

	if (arg1.type == SYNONYM) {
		int validCount = 0;

		if (arg2.type == SYNONYM) {
			if (arg1.value == arg2.value) {
				cout << "In EvaluateCalls, both arg1 and arg2 has the same synonym\n";
				return false;
			}

			vector<string> callingProc, calledProc;
			bool usingIntermediateResult_calling = false, usingIntermediateResult_called = false;

			//get appropriate proc
			if (intermediateResult.IsListEmpty(arg1.syn)) {
				std::cout << "No intermediate result for " << arg1.syn.value << ", get all procs\n";
				callingProc = ProcTable::GetAllProcNames();
			}

			else {
				std::cout << "Get " << arg1.syn.value << " from intermediate result table";
				intermediateResult.GetList(arg1.syn.value, callingProc);
				usingIntermediateResult_calling = true;
			}

			//get appropriate proc
			if (intermediateResult.IsListEmpty(arg2.syn)) {
				std::cout << "No intermediate result for " << arg2.syn.value << ", get all procs\n";
				calledProc = ProcTable::GetAllProcNames();
			}

			else {
				std::cout << "Get " << arg2.syn.value << " from intermediate result table";
				intermediateResult.GetList(arg2.syn.value, calledProc);
				usingIntermediateResult_called = true;
			}

			//loop calledProc.size() * callingProc.size() times, if all invalid, validCount will be 0, return false
			validCount = callingProc.size() * calledProc.size();

			for (vector<string>::iterator it_calling = callingProc.begin(); it_calling != callingProc.end(); ++it_calling) {
				for (vector<string>::iterator it_called = calledProc.begin(); it_called != calledProc.end(); ++it_called) {
					bool isCalls = false;

					int procIndex1 = ProcTable::GetIndexOfProc(*it_calling);
					int procIndex2 = ProcTable::GetIndexOfProc(*it_called);

					if (rel == CALLS)	isCalls = Calls::IsCalls(procIndex1, procIndex2);
					else				isCalls = Calls::IsCallsT(procIndex1, procIndex2);

					//both synonym list taken from result, so both must exist in result, question is whether there is a link between them
					if (usingIntermediateResult_calling && usingIntermediateResult_called) {
						if (isCalls) {
							//check HasLink(), if yes, do nothing, else make pair
							bool isDirectLink;
							if (!intermediateResult.HasLinkBetweenColumns(arg1Syn.value, *it_calling, arg2Syn.value, *it_called, isDirectLink)) {
								//both have links
								if (intermediateResult.HasLink(arg1Syn.value, *it_calling) && intermediateResult.HasLink(arg2Syn.value, *it_called)) {
									if (isDirectLink) {
										intermediateResult.InsertPair(arg1Syn.value, *it_calling, arg2Syn.value, *it_called);
									}

									else {
										//indirect link, do nothing
									}
								}

								//at least one no links
								else {
									intermediateResult.InsertPair(arg1Syn.value, *it_calling, arg2Syn.value, *it_called);
								}
							}
						} else {
							//dont remove, if has link just remove the link, if no link do nothing, update table to remove excess
							bool dummy;
							if (intermediateResult.HasLinkBetweenColumns(arg1Syn.value, *it_calling, arg2Syn.value, *it_called, dummy))
								intermediateResult.Unlink(arg1Syn.value, *it_calling, arg2Syn.value, *it_called);
							--validCount;
						}
					}

					//at least one of the synonym list is new, or both
					else {
						if (isCalls) {
							//insert pair
							intermediateResult.InsertPair(arg1Syn.value, *it_calling, arg2Syn.value, *it_called);
						} else {
							//do nothing
							--validCount;
						}
					}
				}
			}

			//after looping, do a update to remove any element without link between this 2 column
			//if (usingIntermediateResult_called && usingIntermediateResult_calling) {
				intermediateResult.RemoveElementsWithoutLink(arg1Syn.value, arg2Syn.value);
			//}
		}

		//Calls(p,"proc2")
		else if (arg2.type == IDENT) {
			vector<string> procs;
			bool usingIntermediateResult = false;

			if (intermediateResult.IsListEmpty(arg1.syn)) {
				procs = ProcTable::GetAllProcNames();
			}

			else {
				intermediateResult.GetList(arg1.value, procs);
				usingIntermediateResult = true;
			}

			validCount = procs.size();

			for (vector<string>::iterator it = procs.begin(); it != procs.end(); ++it) {
				int procIndex1 = ProcTable::GetIndexOfProc(*it);
				int procIndex2 = ProcTable::GetIndexOfProc(arg2.value);

				bool isCalls = false;

				if (rel == CALLS)	isCalls = Calls::IsCalls(procIndex1, procIndex2);
				else				isCalls = Calls::IsCallsT(procIndex1, procIndex2);

				if (usingIntermediateResult) {
					if (isCalls) {} else {
						intermediateResult.Remove(arg1.value, *it);
						--validCount;
					}
				} else {
					if (isCalls) intermediateResult.Insert(arg1.value, *it);
					else --validCount;
				}
			}
		}

		//Calls(p,_)
		else if (arg2.type == UNDERSCORE) {
			vector<string> procs;
			bool usingIntermediateResult = false;

			if (intermediateResult.IsListEmpty(arg1.syn)) {
				procs = ProcTable::GetAllProcNames();
			}

			else {
				intermediateResult.GetList(arg1.value, procs);
				usingIntermediateResult = true;
			}

			validCount = procs.size();

			for (vector<string>::iterator it = procs.begin(); it != procs.end(); ++it) {
				vector<int> procIndices;
				int procIndex = ProcTable::GetIndexOfProc(*it);

				if (rel == CALLS)	procIndices = Calls::GetProcsCalledBy(procIndex);
				else				procIndices = Calls::GetProcsCalledTBy(procIndex);

				if (usingIntermediateResult) {
					if (!procIndices.empty()) {} else {
						intermediateResult.Remove(arg1.value, *it);
						--validCount;
					}
				} else {
					if (!procIndices.empty()) intermediateResult.Insert(arg1.value, *it);
					else --validCount;
				}
			}
		}

		else {
			cout << "\nIn EvaluateCalls, invalid Calls argument 2 type.\n";
			return false;
		}

		//all statements do not satisfy Calls()
		if (validCount == 0) {
			cout << "Calls() is not satisfied.\n";
			return false;
		}
		return true;
	}

	//Calls("proc1"/_, q)
	else if (arg2.type == SYNONYM) {
		vector<string> procs;
		bool usingIntermediateResult = false;

		if (intermediateResult.IsListEmpty(arg2.syn)) {
			procs = ProcTable::GetAllProcNames();
		}

		else {
			intermediateResult.GetList(arg2.syn.value, procs);
			usingIntermediateResult = true;
		}

		int validCount = procs.size();

		for (vector<string>::iterator it = procs.begin(); it != procs.end(); ++it) {
			bool isCalls = false;
			int procIndex2 = ProcTable::GetIndexOfProc(*it);

			// Calls("proc1",q)
			if (arg1.type == IDENT) {
				int procIndex1 = ProcTable::GetIndexOfProc(arg1.value);

				if (rel == CALLS)	isCalls = Calls::IsCalls(procIndex1, procIndex2);
				else				isCalls = Calls::IsCallsT(procIndex1, procIndex2);
			}

			//Calls(_,q)
			else if (arg1.type == UNDERSCORE) {
				if (rel == CALLS)	isCalls = !(Calls::GetProcsCalling(procIndex2).empty());
				else				isCalls = !(Calls::GetProcsCallingT(procIndex2).empty());
			}

			else {
				cout << "\nIn EvaluateCalls, invalid argument 1 type.\n";
				return false;
			}

			if (usingIntermediateResult) {
				//remove if invalid, do nothing if valid
				if (isCalls) {} else {
					intermediateResult.Remove(arg2.value, *it);
					--validCount;
				}
			} else {
				//insert if valid, do nothing if invalid
				if (isCalls) intermediateResult.Insert(arg2.value, *it);
				else --validCount;
			}
		}

		//all statements do not satisfy Calls()
		if (validCount == 0) {
			cout << "Calls() is not satisfied.\n";
			return false;
		}
		return true;
	}

	//Calls(_,"proc2")
	else if (arg1.type == UNDERSCORE && arg2.type == IDENT) {
		int procIndex2 = ProcTable::GetIndexOfProc(arg2.value);

		if(procIndex2 == -1)	return false;

		vector<int> prev;
		if (rel == CALLS)	prev = Calls::GetProcsCalling(procIndex2);
		else				prev = Calls::GetProcsCallingT(procIndex2);

		if(prev.empty()) return false;

		return true;
	}

	//Calls("proc1",_)
	else if (arg1.type == IDENT && arg2.type == UNDERSCORE) {
		int procIndex1 = ProcTable::GetIndexOfProc(arg1.value);

		if(procIndex1 == -1)	return false;

		vector<int> Calls;
		if (rel == CALLS)	Calls = Calls::GetProcsCalledBy(procIndex1);
		else				Calls = Calls::GetProcsCalledTBy(procIndex1);

		if(Calls.empty()) return false;

		return true;
	}

	//Calls("proc1","proc2")
	else if (arg1.type == IDENT && arg2.type == IDENT) {
		int procIndex1 = ProcTable::GetIndexOfProc(arg1.value);
		int procIndex2 = ProcTable::GetIndexOfProc(arg2.value);

		if(procIndex1 == -1 || procIndex2 == -1)	return false;

		if (rel == CALLS)	return Calls::IsCalls(procIndex1, procIndex2);
		else				return Calls::IsCallsT(procIndex1, procIndex2);
	}

	//Calls(_,_)
	else if (arg1.type == UNDERSCORE && arg2.type == UNDERSCORE) {
		return Calls::HasAnyCalls();
	}

	else {
		cout << "In EvaluateCalls, no matching arguments.\n";
		return false;
	}
}


bool QueryEvaluator::EvaluateNext(SuchThatClause suchThat)
{
	Argument arg1 = suchThat.arg1;
	Argument arg2 = suchThat.arg2;
	Synonym arg1Syn = suchThat.arg1.syn;
	Synonym arg2Syn = suchThat.arg2.syn;
	RelationshipType rel = suchThat.relationship;

	cout << "Evaluating Next( " << arg1.value << " , " << arg2.value << ")\n";

	if (arg1.type == SYNONYM) {
		int validCount = 0;

		if (arg2.type == SYNONYM) {
			if (rel == NEXT && arg1Syn.value == arg2Syn.value) {
				cout << "In EvaluateNext, both arg1 and arg2 has the same synonym\n";
				return false;
			}

			vector<int> prevStmt, nextStmt;
			bool usingIntermediateResult_prev = false, usingIntermediateResult_next = false;

			//get appropriate stmt, while, if, prog_line
			if (intermediateResult.IsListEmpty(arg1.syn)) {
				std::cout << "No intermediate result for " << arg1.syn.value << ", get all stmts\n";
				prevStmt = StmtTypeTable::GetAllStmtsOfType(arg1.syn.type);
			}

			else {
				std::cout << "Get " << arg1.syn.value << " from intermediate result table";
				intermediateResult.GetList(arg1.syn.value, prevStmt);
				usingIntermediateResult_next = true;
			}

			//get appropriate stmt, assign, while, if, prog_line, call
			if (intermediateResult.IsListEmpty(arg2.syn)) {
				std::cout << "No intermediate result for " << arg2.syn.value << ", get all stmts\n";
				nextStmt = StmtTypeTable::GetAllStmtsOfType(arg2.syn.type);
			}

			else {
				std::cout << "Get " << arg2.syn.value << " from intermediate result table";
				intermediateResult.GetList(arg2.syn.value, nextStmt);
				usingIntermediateResult_prev = true;
			}

			//loop nextStmt.size() * prevStmt.size() times, if all invalid, validCount will be 0, return false
			validCount = prevStmt.size() * nextStmt.size();

			for (vector<int>::iterator it_prev = prevStmt.begin(); it_prev != prevStmt.end(); ++it_prev) {
				for (vector<int>::iterator it_next = nextStmt.begin(); it_next != nextStmt.end(); ++it_next) {
					bool isNext = false;
	
					string next_str = ITOS(*it_prev);
					string prev_str = ITOS(*it_next);

					if (rel == NEXT)	isNext = Next::IsNext(*it_prev, *it_next);
					else				isNext = Next::IsNextT(*it_prev, *it_next);

					//both synonym list taken from result, so both must exist in result, question is whether there is a link between them
					if (usingIntermediateResult_next && usingIntermediateResult_prev) {
						if (isNext) {
							//check HasLink(), if yes, do nothing, else make pair
							bool isDirectLink;
							if (!intermediateResult.HasLinkBetweenColumns(arg1Syn.value, prev_str, arg2Syn.value, next_str, isDirectLink)) {

								//both have links
								if (intermediateResult.HasLink(arg1Syn.value, prev_str) && intermediateResult.HasLink(arg2Syn.value, next_str)) {
									if (isDirectLink) {
										intermediateResult.InsertPair(arg1Syn.value, prev_str, arg2Syn.value, next_str);
									}
									else {
										//indirect link, do nothing
									}
								}

								//at least one no links
								else {
									intermediateResult.InsertPair(arg1Syn.value, prev_str, arg2Syn.value, next_str);
								}
							}
						} else {
							//dont remove, if has link just remove the link, if no link do nothing, update table to remove excess
							bool dummy;
							if (intermediateResult.HasLinkBetweenColumns(arg1Syn.value, prev_str, arg2Syn.value, next_str, dummy))
								intermediateResult.Unlink(arg1Syn.value, prev_str, arg2Syn.value, next_str);

							//intermediateResult.RemovePair(arg1Syn.value, *it_next, arg2Syn.value, *it_prev);
							--validCount;
						}
					}

					//at least one of the synonym list is new, or both
					else {
						if (isNext) {
							//insert pair
							intermediateResult.InsertPair(arg1Syn.value, prev_str, arg2Syn.value, next_str);
						} else {
							//do nothing
							--validCount;
						}
					}
				}
			}

			//after looping, do a update to remove any element without link between this 2 column
			//if (usingIntermediateResult_next && usingIntermediateResult_prev) {
				intermediateResult.RemoveElementsWithoutLink(arg1Syn.value, arg2Syn.value);
			//}
		}

		// Next(a,2)
		else if (arg2.type == INTEGER) {
			vector<int> stmts;
			bool usingIntermediateResult = false;

			if (intermediateResult.IsListEmpty(arg1.syn)) {
				stmts = StmtTypeTable::GetAllStmtsOfType(arg1.syn.type);
			}

			else {
				intermediateResult.GetList(arg1.syn.value, stmts);
				usingIntermediateResult = true;
			}

			validCount = stmts.size();

			for (vector<int>::iterator it = stmts.begin(); it != stmts.end(); ++it) {
				int arg2Value = atoi(arg2.value.c_str());
				bool isNext = false;

				if (rel == NEXT)	isNext = Next::IsNext(*it, arg2Value);
				else				isNext = Next::IsNextT(*it, arg2Value);

				if (usingIntermediateResult) {
					if (isNext) {} else {
						intermediateResult.Remove(arg1Syn.value, *it);
						--validCount;
					}
				} else {
					if (isNext) intermediateResult.Insert(arg1Syn.value, *it);
					else --validCount;
				}
			}
		}

		// Next(a,_)
		else if (arg2.type == UNDERSCORE) {
			vector<int> stmts;
			bool usingIntermediateResult = false;

			if (intermediateResult.IsListEmpty(arg1.syn)) {
				stmts = StmtTypeTable::GetAllStmtsOfType(arg1.syn.type);
			}

			else {
				intermediateResult.GetList(arg1.syn.value, stmts);
				usingIntermediateResult = true;
			}

			validCount = stmts.size();

			for (vector<int>::iterator it = stmts.begin(); it != stmts.end(); ++it) {
				vector<int> Next;

				if (rel == NEXT)	Next = Next::GetNextAfter(*it);
				else				Next = Next::GetNextTAfter(*it);

				if (usingIntermediateResult) {
					if (!Next.empty()) {} else {
						intermediateResult.Remove(arg1Syn.value, *it);
						--validCount;
					}
				} else {
					if (!Next.empty()) intermediateResult.Insert(arg1Syn.value, *it);
					else --validCount;
				}
			}
		}

		else {
			cout << "\nIn EvaluateNext, invalid Next argument 2 type.\n";
			return false;
		}

		//all statements do not satisfy Next()
		if (validCount == 0) {
			cout << "Next() is not satisfied.\n";
			return false;
		}
		return true;
	}

	//Next (smth, syn)
	else if (arg2.type == SYNONYM) {
		vector<int> stmts;
		bool usingIntermediateResult = false;

		if (intermediateResult.IsListEmpty(arg2.syn)) {
			stmts = StmtTypeTable::GetAllStmtsOfType(arg2Syn.type);
		}

		else {
			intermediateResult.GetList(arg2.syn.value, stmts);
			usingIntermediateResult = true;
		}

		int validCount = stmts.size();

		for (vector<int>::iterator it = stmts.begin(); it != stmts.end(); ++it) {
			bool isNext = false;

			// Next(1, a)
			if (arg1.type == INTEGER) {
				int arg1Value = STOI(arg1.value);

				if (rel == NEXT)	isNext = Next::IsNext(arg1Value, *it);
				else				isNext = Next::IsNextT(arg1Value, *it);
			}

			//Next(_ , a)
			else if (arg1.type == UNDERSCORE) {
				if (rel == NEXT)	isNext = !(Next::GetNextBefore(*it).empty());
				else				isNext = !(Next::GetNextTBefore(*it).empty());
			}

			else {
				cout << "\nIn EvaluateNext, invalid argument 1 type.\n";
				return false;
			}

			if (usingIntermediateResult) {
				//remove if invalid, do nothing if valid
				if (isNext) {} else {
					intermediateResult.Remove(arg2Syn.value, *it);
					--validCount;
				}
			} else {
				//insert if valid, do nothing if invalid
				if (isNext) intermediateResult.Insert(arg2Syn.value, *it);
				else --validCount;
			}
		}

		//all statements do not satisfy Next()
		if (validCount == 0) {
			cout << "Next() is not satisfied.\n";
			return false;
		}
		return true;
	}

	//Next(_,2)
	else if (arg1.type == UNDERSCORE && arg2.type == INTEGER) {
		int arg2Value = STOI(arg2.value);

		vector<int> prev;
		if (rel == NEXT)	prev = Next::GetNextBefore(arg2Value);
		else				prev = Next::GetNextTBefore(arg2Value);

		if (prev.empty()) return false;

		return true;
	}

	//Next(1,_)
	else if (arg1.type == INTEGER && arg2.type == UNDERSCORE) {
		int arg1Value = STOI(arg1.value);

		vector<int> next;
		if (rel == NEXT)	next = Next::GetNextAfter(arg1Value);
		else				next = Next::GetNextTAfter(arg1Value);

		if (next.empty()) return false;

		return true;
	}

	//Next(1,2)
	else if (arg1.type == INTEGER && arg2.type == INTEGER) {
		int arg1Value = STOI(arg1.value);
		int arg2Value = STOI(arg2.value);

		if (rel == NEXT)	return Next::IsNext(arg1Value, arg2Value);
		else				return Next::IsNextT(arg1Value, arg2Value);
	}

	//Next(_,_)
	else if (arg1.type == UNDERSCORE && arg2.type == UNDERSCORE) {
		return Next::HasAnyNext();
	}

	else {
		cout << "In EvaluateNext, no matching arguments.\n";
		return false;
	}
}


bool QueryEvaluator::EvaluateAffects(SuchThatClause suchThat)
{
	Argument arg1 = suchThat.arg1;
	Argument arg2 = suchThat.arg2;
	Synonym arg1Syn = suchThat.arg1.syn;
	Synonym arg2Syn = suchThat.arg2.syn;
	RelationshipType rel = suchThat.relationship;

	cout << "Evaluating Affects( " << arg1.value << " , " << arg2.value << ")\n";

	if (arg1.type == SYNONYM) {
		int validCount = 0;

		if (arg2.type == SYNONYM) {
			if (arg1Syn.value == arg2Syn.value) {
				cout << "In EvaluateAffects, both arg1 and arg2 has the same synonym\n";
				return false;
			}

			vector<int> affectingStmt, affectedStmt;
			bool usingIntermediateResult_affecting = false, usingIntermediateResult_affected = false;

			//get appropriate stmt, while, if, prog_line
			if (intermediateResult.IsListEmpty(arg1.syn)) {
				std::cout << "No intermediate result for " << arg1.syn.value << ", get all stmts\n";
				affectingStmt = StmtTypeTable::GetAllStmtsOfType(arg1.syn.type);
			}

			else {
				std::cout << "Get " << arg1.syn.value << " from intermediate result table";
				intermediateResult.GetList(arg1.syn.value, affectingStmt);
				usingIntermediateResult_affecting = true;
			}

			//get appropriate stmt, assign, while, if, prog_line, call
			if (intermediateResult.IsListEmpty(arg2.syn)) {
				std::cout << "No intermediate result for " << arg2.syn.value << ", get all stmts\n";
				affectedStmt = StmtTypeTable::GetAllStmtsOfType(arg2.syn.type);
			}

			else {
				std::cout << "Get " << arg2.syn.value << " from intermediate result table";
				intermediateResult.GetList(arg2.syn.value, affectedStmt);
				usingIntermediateResult_affected = true;
			}

			//loop affectedStmt.size() * affectingStmt.size() times, if all invalid, validCount will be 0, return false
			validCount = affectingStmt.size() * affectedStmt.size();

			for (vector<int>::iterator it_affecting = affectingStmt.begin(); it_affecting != affectingStmt.end(); ++it_affecting) {
				for (vector<int>::iterator it_affected = affectedStmt.begin(); it_affected != affectedStmt.end(); ++it_affected) {
					bool isAffects = false;

					string affecting_str = ITOS(*it_affecting);
					string affected_str = ITOS(*it_affected);

					if (rel == AFFECTS)	isAffects = Affects::IsAffects(*it_affecting, *it_affected);
					else				isAffects = Affects::IsAffectsT(*it_affecting, *it_affected);

					//both synonym list taken from result, so both must exist in result, question is whether there is a link between them
					if (usingIntermediateResult_affecting && usingIntermediateResult_affected) {
						if (isAffects) {
							//check HasLink(), if yes, do nothing, else make pair
							bool isDirectLink;
							if (!intermediateResult.HasLinkBetweenColumns(arg1Syn.value, affecting_str, arg2Syn.value, affected_str, isDirectLink)) {

								//both have links
								if (intermediateResult.HasLink(arg1Syn.value, affecting_str) && intermediateResult.HasLink(arg2Syn.value, affected_str)) {
									if (isDirectLink) {
										intermediateResult.InsertPair(arg1Syn.value, affecting_str, arg2Syn.value, affected_str);
									}

									else {
										//indirect link, do nothing
									}
								}

								//at least one no links
								else {
									intermediateResult.InsertPair(arg1Syn.value, affecting_str, arg2Syn.value, affected_str);
								}
							}
						} else {
							//dont remove, if has link just remove the link, if no link do nothing, update table to remove excess
							bool dummy;
							if (intermediateResult.HasLinkBetweenColumns(arg1Syn.value, affecting_str, arg2Syn.value, affected_str, dummy))
								intermediateResult.Unlink(arg1Syn.value, affecting_str, arg2Syn.value, affected_str);

							//intermediateResult.RemovePair(arg1Syn.value, *it_affected, arg2Syn.value, *it_affecting);
							--validCount;
						}
					}

					//at least one of the synonym list is new, or both
					else {
						if (isAffects) {
							//insert pair
							intermediateResult.InsertPair(arg1Syn.value, affecting_str, arg2Syn.value, affected_str);
						} else {
							//do nothing
							--validCount;
						}
					}
				}
			}

			//after looping, do a update to remove any element without link between this 2 column
			//if (usingIntermediateResult_affected && usingIntermediateResult_affecting) {
				intermediateResult.RemoveElementsWithoutLink(arg1Syn.value, arg2Syn.value);
			//}
		}

		//Affects(a,2)
		else if (arg2.type == INTEGER) {
			vector<int> stmts;
			bool usingIntermediateResult = false;

			if (intermediateResult.IsListEmpty(arg1.syn)) {
				stmts = StmtTypeTable::GetAllStmtsOfType(arg1.syn.type);
			}

			else {
				intermediateResult.GetList(arg1.syn.value, stmts);
				usingIntermediateResult = true;
			}

			validCount = stmts.size();

			for (vector<int>::iterator it = stmts.begin(); it != stmts.end(); ++it) {
				int arg2Value = atoi(arg2.value.c_str());
				bool isAffects = false;

				if (rel == AFFECTS)	isAffects = Affects::IsAffects(*it, arg2Value);
				else				isAffects = Affects::IsAffectsT(*it, arg2Value);

				if (usingIntermediateResult) {
					if (isAffects) {} else {
						intermediateResult.Remove(arg1Syn.value, *it);
						--validCount;
					}
				} else {
					if (isAffects) intermediateResult.Insert(arg1Syn.value, *it);
					else --validCount;
				}
			}
		}

		//Affects(a,_)
		else if (arg2.type == UNDERSCORE) {
			vector<int> stmts;
			bool usingIntermediateResult = false;

			if (intermediateResult.IsListEmpty(arg1.syn)) {
				stmts = StmtTypeTable::GetAllStmtsOfType(arg1.syn.type);
			}

			else {
				intermediateResult.GetList(arg1.syn.value, stmts);
				usingIntermediateResult = true;
			}

			validCount = stmts.size();

			for (vector<int>::iterator it = stmts.begin(); it != stmts.end(); ++it) {
				vector<int> affects;

				if (rel == AFFECTS)	affects = Affects::GetStmtsAffectedBy(*it);
				else				affects = Affects::GetStmtsAffectedTBy(*it);

				if (usingIntermediateResult) {
					if (!affects.empty()) {} else {
						intermediateResult.Remove(arg1Syn.value, *it);
						--validCount;
					}
				} else {
					if (!affects.empty()) intermediateResult.Insert(arg1Syn.value, *it);
					else --validCount;
				}
			}
		}

		else {
			cout << "\nIn EvaluateAffects, invalid Affects argument 2 type.\n";
			return false;
		}

		//all statements do not satisfy Affects()
		if (validCount == 0) {
			cout << "Affects() is not satisfied.\n";
			return false;
		}
		return true;
	}

	//Affects(_, a)
	//Affects(1,a)
	else if (arg2.type == SYNONYM) {
		vector<int> stmts;
		bool usingIntermediateResult = false;

		if (intermediateResult.IsListEmpty(arg2.syn)) {
			stmts = StmtTypeTable::GetAllStmtsOfType(arg2.syn.type);
		}

		else {
			intermediateResult.GetList(arg2.syn.value, stmts);
			usingIntermediateResult = true;
		}

		int validCount = stmts.size();

		for (vector<int>::iterator it = stmts.begin(); it != stmts.end(); ++it) {
			bool isAffects = false;
			
			//Affects(_, a)
			if (arg1.type == INTEGER) {
				int arg1Value = STOI(arg1.value);

				if (rel == AFFECTS)	isAffects = Affects::IsAffects(arg1Value, *it);
				else				isAffects = Affects::IsAffectsT(arg1Value, *it);
			}

			//Affects(1,a)
			else if (arg1.type == UNDERSCORE) {
				if (rel == AFFECTS)	isAffects = !Affects::GetStmtsAffecting(*it).empty();
				else				isAffects = !Affects::GetStmtsAffectingT(*it).empty();
			}

			else {
				cout << "\nIn EvaluateAffects, invalid argument 1 type.\n";
				return false;
			}

			if (usingIntermediateResult) {
				//remove if invalid, do nothing if valid
				if (isAffects) {} else {
					intermediateResult.Remove(arg2Syn.value, *it);
					--validCount;
				}
			} else {
				//insert if valid, do nothing if invalid
				if (isAffects) intermediateResult.Insert(arg2Syn.value, *it);
				else --validCount;
			}
		}

		//all statements do not satisfy Affects()
		if (validCount == 0) {
			cout << "Affects() is not satisfied.\n";
			return false;
		}
		return true;
	}

	//Affects(_,2)
	else if (arg1.type == UNDERSCORE && arg2.type == INTEGER) {
		int arg2Value = STOI(arg2.value);

		vector<int> affecting;
		if (rel == AFFECTS)	affecting = Affects::GetStmtsAffecting(arg2Value);
		else				affecting = Affects::GetStmtsAffectingT(arg2Value);

		if (affecting.empty()) return false;

		return true;
	}

	//Affects(1,_)
	else if (arg1.type == INTEGER && arg2.type == UNDERSCORE) {
		int arg1Value = STOI(arg1.value);

		vector<int> affected;
		if (rel == AFFECTS)	affected = Affects::GetStmtsAffectedBy(arg1Value);
		else				affected = Affects::GetStmtsAffectedTBy(arg1Value);

		if (affected.empty()) return false;

		return true;
	}

	//Affects(1,2)
	else if (arg1.type == INTEGER && arg2.type == INTEGER) {
		int arg1Value = STOI(arg1.value);
		int arg2Value = STOI(arg2.value);

		if (rel == AFFECTS)	return Affects::IsAffects(arg1Value, arg2Value);
		else				return Affects::IsAffectsT(arg1Value, arg2Value);
	}

	//Affects(_,_)
	else if (arg1.type == UNDERSCORE && arg2.type == UNDERSCORE) {
		// extremely computationally expensive
		for (int stmt = 1; stmt < StmtTypeTable::GetMaxStmtIndex(); stmt++) {
			if (Affects::GetStmtsAffectedBy(stmt).size() != 0) return true;
		}

		return false;
	}

	else {
		cout << "In EvaluateAffects, no matching arguments.\n";
		return false;
	}
}


bool QueryEvaluator::EvaluateContains(SuchThatClause)
{
	return true;
}


bool QueryEvaluator::EvaluateSibling(SuchThatClause)
{
	return true;
}


bool QueryEvaluator::EvaluateAffectsBip(SuchThatClause)
{
	return true;
}


bool QueryEvaluator::EvaluateNextBip(SuchThatClause)
{
	return true;
}


bool QueryEvaluator::EvaluatePattern(PatternClause pattern)
{
	Synonym patternSyn = pattern.synonym;
	Argument arg1 = pattern.arg1;
	Argument arg2 = pattern.arg2;
	Synonym arg1Syn = pattern.arg1.syn;
	Synonym arg2Syn = pattern.arg2.syn;
	ArgumentType arg1Type = pattern.arg1.type;
	ArgumentType arg2Type = pattern.arg2.type;
	string arg1Value = pattern.arg1.value;
	string arg2Value = pattern.arg2.value;
	
	if(patternSyn.type == ASSIGN)
	{
		vector<int> stmts;
		bool usingIntermediateResult_assign = false;
		int validCount = 0;

		//get appropriate stmt, while, if, prog_line
		if (intermediateResult.IsListEmpty(patternSyn)) {
			cout << "No intermediate result for " << patternSyn.value << ", get all stmts\n";
			stmts = StmtTypeTable::GetAllStmtsOfType(patternSyn.type);
		}

		else {
			cout << "Get " << arg1.syn.value << " from intermediate result table";
			intermediateResult.GetList(patternSyn.value, stmts);
			usingIntermediateResult_assign = true;
		}

		//pattern a(_,_)
		//pattern a(v,_)
		//pattern a("x",_)
		if(arg2Type == UNDERSCORE)
		{
			vector<int> tempResult;

			//pattern a(_,_)
			if(arg1Type == UNDERSCORE)
			{					
				for(vector<int>::iterator it = stmts.begin(); it != stmts.end(); ++it)
				{
					if(usingIntermediateResult_assign)
					{
						//do nothing, no need to remove anything
					}
					else
					{
						//add all stmts to table
						intermediateResult.Insert(patternSyn.value , *it);
					}
				}
				return true;
			}

			//pattern a(v,_)
			else if(arg1Type == SYNONYM && arg1Syn.type == VARIABLE)
			{
				//------------Get intermediate result of type arg2------------
				vector<string> vars;
				bool usingIntermediateResult_vars = false;

				if(intermediateResult.IsListEmpty(arg1.syn)) {
					vars = VarTable::GetAllVarNames();
				}

				else {
					intermediateResult.GetList(arg1Syn.value , vars);
					usingIntermediateResult_vars = true;
				}


				//loop afterStmt.size() * beforeStmt.size() times, if all invalid, validCount will be 0, return false
				validCount = stmts.size() * vars.size();

				for (vector<int>::iterator it_stmts = stmts.begin(); it_stmts != stmts.end(); ++it_stmts) {
					for (vector<string>::iterator it_vars = vars.begin(); it_vars != vars.end(); ++it_vars) {

						int varIndex = VarTable::GetIndexOfVar(*it_vars);

						bool isModifies = Modifies::IsStmtModifyingVar(*it_stmts,varIndex);

						if (usingIntermediateResult_assign && usingIntermediateResult_vars) {
							if (isModifies) {
								bool isDirectLink;
								if (!intermediateResult.HasLinkBetweenColumns(patternSyn.value, *it_stmts, arg1Syn.value, *it_vars, isDirectLink)) {
									if (intermediateResult.HasLink(patternSyn.value, *it_stmts) && intermediateResult.HasLink(arg1Syn.value, *it_vars)) {
										if (isDirectLink) {
											intermediateResult.InsertPair(patternSyn.value, *it_stmts, arg1Syn.value, *it_vars);
										}
										else {
											//indirect link, do nothing
										}
									}

									//at least one no links
									else {
										intermediateResult.InsertPair(patternSyn.value, *it_stmts, arg1Syn.value, *it_vars);
									}
								}
							} 
							else {
								bool dummy;
								if (intermediateResult.HasLinkBetweenColumns(patternSyn.value, *it_stmts, arg1Syn.value, *it_vars, dummy))
									intermediateResult.Unlink(patternSyn.value, *it_stmts, arg1Syn.value, *it_vars);
								--validCount;
							}
						}

						//at least one of the synonym list is new, or both
						else {
							if (isModifies) {
								intermediateResult.InsertPair(patternSyn.value, *it_stmts, arg1Syn.value, *it_vars);
							} 
							else {
								--validCount;
							}
						}
					}
				}

				//after looping, do a update to remove any element without link between this 2 column
				//if (usingIntermediateResult_assign && usingIntermediateResult_vars) {
					intermediateResult.RemoveElementsWithoutLink(patternSyn.value, arg1Syn.value);
				//}
			}
			  
			//pattern a("x",_)
			else if(arg1Type == IDENT)
			{
				string ident = arg1Value;
				ident.erase(remove_if(ident.begin(), ident.end(), [](char x){return isspace(x);}), ident.end());
				ident = ident.substr(1, ident.length()-2);

				int varIndex = VarTable::GetIndexOfVar(ident);
				
				if(varIndex != -1)
				{
					validCount = stmts.size();
					for(vector<int>::iterator it = stmts.begin(); it != stmts.end(); ++it) 
					{
						int arg2Value = atoi(arg2.value.c_str());
						bool isModified = false;

						isModified = Modifies::IsStmtModifyingVar((*it), varIndex);

						if(usingIntermediateResult_assign)
						{
							if(isModified) {}
							else 
							{
								intermediateResult.Remove(patternSyn.value , *it);
								--validCount;
							}
						}
						else
						{
							if(isModified) intermediateResult.Insert(patternSyn.value , *it);
							else --validCount;
						}
					}
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

			//all statements do not satisfy Parent()
			if(validCount == 0) 
			{
				cout << "Pattern is not satisfied.\n";			
				return false;
			}
			return true;
		}

		//pattern a(v,_"x+y"_)
		//pattern a("x",_"x+y"_)
		//pattern a(_,_"x+y"_)
		else if(arg2Type == EXPRESSION)
		{
			vector<int> tempResult;

			vector<int> rightResult = PatternMatcher::MatchPatternFromRoot(arg2Value);
			if(rightResult.empty())		return false;
			
			//pattern a(_,_"x+y"_)
			if(arg1Type == UNDERSCORE)
			{
				validCount = stmts.size();
				if(usingIntermediateResult_assign)
				{
					//narrow the table with right result
					for(vector<int>::iterator it = stmts.begin(); it != stmts.end(); ++it)
					{
						//if found, do nothing, else remove it
						if(find(rightResult.begin() , rightResult.end() , *it) == rightResult.end())
						{
							intermediateResult.Remove(patternSyn.value , *it);
							--validCount;
						}
					}
				}
				else
				{
					//insert all right result into table
					for(vector<int>::iterator it = rightResult.begin(); it != rightResult.end(); ++it)
						intermediateResult.Insert(patternSyn.value , *it);

					return true;
				}		
			}

			//pattern a(v,_"x+y"_)
			else if(arg1Type == SYNONYM)
			{
				//Do a pattern a(v,_) first, then do pattern a(_,_"x+y")

				//------------Get intermediate result of type arg2------------
				vector<string> vars;
				bool usingIntermediateResult_vars = false;

				if(intermediateResult.IsListEmpty(arg1.syn)) {
					vars = VarTable::GetAllVarNames();
				}

				else {
					intermediateResult.GetList(arg1Syn.value , vars);
					usingIntermediateResult_vars = true;
				}

				//loop afterStmt.size() * beforeStmt.size() times, if all invalid, validCount will be 0, return false
				validCount = stmts.size() * vars.size();
				cout << "validCount : " <<stmts.size() << " x " << vars.size() <<"\n";
				for (vector<int>::iterator it_stmts = stmts.begin(); it_stmts != stmts.end(); ++it_stmts) {
					for (vector<string>::iterator it_vars = vars.begin(); it_vars != vars.end(); ++it_vars) {

						int varIndex = VarTable::GetIndexOfVar(*it_vars);

						bool isModifies = Modifies::IsStmtModifyingVar(*it_stmts,varIndex);

						if (usingIntermediateResult_assign && usingIntermediateResult_vars) {
							if (isModifies) {
								bool isDirectLink;
								if (!intermediateResult.HasLinkBetweenColumns(patternSyn.value, *it_stmts, arg1Syn.value, *it_vars, isDirectLink)) {
									if (intermediateResult.HasLink(patternSyn.value, *it_stmts) && intermediateResult.HasLink(arg1Syn.value, *it_vars)) {
										if (isDirectLink) {
											intermediateResult.InsertPair(patternSyn.value, *it_stmts, arg1Syn.value, *it_vars);
										}
										else {
											//indirect link, do nothing
										}
									}

									//at least one no links
									else {
										intermediateResult.InsertPair(patternSyn.value, *it_stmts, arg1Syn.value, *it_vars);
									}
								}
								break;
							} 
							else {
								bool dummy;
								if (intermediateResult.HasLinkBetweenColumns(patternSyn.value, *it_stmts, arg1Syn.value, *it_vars, dummy))
									intermediateResult.Unlink(patternSyn.value, *it_stmts, arg1Syn.value, *it_vars);
								--validCount;
							}
						}

						//at least one of the synonym list is new, or both
						else {
							if (isModifies) {
								intermediateResult.InsertPair(patternSyn.value, *it_stmts, arg1Syn.value, *it_vars);
							} 
							else {
								--validCount;
							}
						}
					}
				}

				//after looping, do a update to remove any element without link between this 2 column
				//if (usingIntermediateResult_assign && usingIntermediateResult_vars) {
					intermediateResult.RemoveElementsWithoutLink(patternSyn.value, arg1Syn.value);
				//}


				//update stmts
				intermediateResult.GetList(patternSyn.value, stmts);
				intermediateResult.Print();
				validCount = stmts.size();
				cout << "validCount : " <<stmts.size() <<"\n";

					//narrow the table with right result
					for(vector<int>::iterator it = stmts.begin(); it != stmts.end(); ++it)
					{cout << "here\n";
						//if found, do nothing, else remove it
						if(find(rightResult.begin() , rightResult.end() , *it) == rightResult.end())
						{
							cout << "here\n";
							intermediateResult.Remove(patternSyn.value , *it);
							--validCount;
						}
						cout << "here\n";
					}
				/*}
				else
				{
					//insert all right result into table
					for(vector<int>::iterator it = rightResult.begin(); it != rightResult.end(); ++it)
						intermediateResult.Insert(patternSyn.value , *it);

					return true;
				}*/		
			}

			//pattern a("x",_"x+y"_)
			else if(arg1Type == IDENT)
			{
				//get leftResult
				vector<int> leftResult;

				string ident = arg1Value;
				ident.erase(remove_if(ident.begin(), ident.end(), [](char x){return isspace(x);}), ident.end());
				ident = ident.substr(1, ident.length()-2);

				int varIndex = VarTable::GetIndexOfVar(ident);
				
				if(varIndex != -1)
				{
					vector<int> temp = Modifies::GetStmtModifyingVar(varIndex);

					if(!temp.empty())
					{
						for(vector<int>::iterator it = temp.begin(); it != temp.end(); ++it)
						{
							if(StmtTypeTable::CheckIfStmtOfType(*it,ASSIGN))
								leftResult.push_back(*it);
						}
					}

					else return false;

					if(leftResult.empty())	return false;

					vector<int> tempResult;
					set_intersection(leftResult.begin(), leftResult.end(), rightResult.begin(), rightResult.end(), back_inserter(tempResult));

					if(tempResult.empty())	return false;

					validCount = stmts.size();
					if(usingIntermediateResult_assign)
					{
						//narrow the table with right result

						for(vector<int>::iterator it = stmts.begin(); it != stmts.end(); ++it)
						{
							//if found, do nothing, else remove it
							if(find(tempResult.begin() , tempResult.end() , *it) == tempResult.end())
							{
								intermediateResult.Remove(patternSyn.value , *it);
								--validCount;
							}
						}
					}
					else
					{
						//insert all right result into table
						for(vector<int>::iterator it = tempResult.begin(); it != tempResult.end(); ++it)
							intermediateResult.Insert(patternSyn.value , *it);

						return true;
					}
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

			if(validCount == 0) 
			{
				cout << "Pattern is not satisfied.\n";			
				return false;
			}
			return true;
		}

		else
		{
			cout << "\nIn EvaluatePattern, invalid pattern argument 2 type.\n";
			return false;
		}
	}

	else if(patternSyn.type == WHILE)
	{
		vector<int> stmts;
		bool usingIntermediateResult_while = false;
		int validCount = 0;

		//get appropriate stmt, while, if, prog_line
		if (intermediateResult.IsListEmpty(patternSyn)) {
			cout << "No intermediate result for " << patternSyn.value << ", get all stmts\n";
			stmts = StmtTypeTable::GetAllStmtsOfType(patternSyn.type);
		}

		else {
			cout << "Get " << patternSyn.value << " from intermediate result table";
			intermediateResult.GetList(patternSyn.value, stmts);
			usingIntermediateResult_while = true;
		}

		//pattern w(_,_)
		if(arg1Type == UNDERSCORE)
		{
			//get all the while
			for(vector<int>::iterator it = stmts.begin(); it != stmts.end(); ++it)
			{
				if(usingIntermediateResult_while)
				{
					//do nothing, no need to remove anything
				}
				else
				{
					//add all stmts to table
					intermediateResult.Insert(patternSyn.value , *it);
				}
			}
			return true;
		}

		//pattern w(v,_)
		else if(arg1Type == IDENT)
		{
			//------------Get intermediate result of type arg2------------
			vector<string> vars;
			bool usingIntermediateResult_vars = false;

			if(intermediateResult.IsListEmpty(arg1.syn)) {
				vars = VarTable::GetAllVarNames();
			}

			else {
				intermediateResult.GetList(arg1Syn.value , vars);
				usingIntermediateResult_vars = true;
			}

			//loop afterStmt.size() * beforeStmt.size() times, if all invalid, validCount will be 0, return false
			validCount = stmts.size() * vars.size();

			for (vector<int>::iterator it_stmts = stmts.begin(); it_stmts != stmts.end(); ++it_stmts) {
				for (vector<string>::iterator it_vars = vars.begin(); it_vars != vars.end(); ++it_vars) {

					int varIndex = VarTable::GetIndexOfVar(*it_vars);

					bool isUses = Uses::IsStmtUsingVar(*it_stmts,varIndex);

					if (usingIntermediateResult_while && usingIntermediateResult_vars) {
						if (isUses) {
							bool isDirectLink;
							if (!intermediateResult.HasLinkBetweenColumns(patternSyn.value, *it_stmts, arg1Syn.value, *it_vars, isDirectLink)) {
								if (intermediateResult.HasLink(patternSyn.value, *it_stmts) && intermediateResult.HasLink(arg1Syn.value, *it_vars)) {
									if (isDirectLink) {
										intermediateResult.InsertPair(patternSyn.value, *it_stmts, arg1Syn.value, *it_vars);
									}
									else {
										//indirect link, do nothing
									}
								}

								//at least one no links
								else {
									intermediateResult.InsertPair(patternSyn.value, *it_stmts, arg1Syn.value, *it_vars);
								}
							}
						} 
						else {
							bool dummy;
							if (intermediateResult.HasLinkBetweenColumns(patternSyn.value, *it_stmts, arg1Syn.value, *it_vars, dummy))
								intermediateResult.Unlink(patternSyn.value, *it_stmts, arg1Syn.value, *it_vars);
							--validCount;
						}
					}

					//at least one of the synonym list is new, or both
					else {
						if (isUses) {
							intermediateResult.InsertPair(patternSyn.value, *it_stmts, arg1Syn.value, *it_vars);
						} 
						else {
							--validCount;
						}
					}
				}
			}

			//after looping, do a update to remove any element without link between this 2 column
			//if (usingIntermediateResult_while && usingIntermediateResult_vars) {
				intermediateResult.RemoveElementsWithoutLink(patternSyn.value, arg1Syn.value);
			//}
		}

		//pattern w("x",_)
		else if(arg1Type == SYNONYM && arg1Syn.type == VARIABLE)
		{
			string ident = arg1Value;
			ident.erase(remove_if(ident.begin(), ident.end(), [](char x){return isspace(x);}), ident.end());
			ident = ident.substr(1, ident.length()-2);

			int varIndex = VarTable::GetIndexOfVar(ident);
				
			if(varIndex != -1)
			{
				validCount = stmts.size();
				for(vector<int>::iterator it_stmts = stmts.begin(); it_stmts != stmts.end(); ++it_stmts) 
				{
					bool isUses = Uses::IsStmtUsingVar(*it_stmts,varIndex);

					if(usingIntermediateResult_while)
					{
						if(isUses) {}
						else 
						{
							intermediateResult.Remove(patternSyn.value , *it_stmts);
							--validCount;
						}
					}
					else
					{
						if(isUses) intermediateResult.Insert(patternSyn.value , *it_stmts);
						else --validCount;
					}
				}
			}

			else
			{
				cout << "\nIn EvaluatePattern, pattern argument 1 IDENT not found.\n";
				return false;
			}
		}

		else
		{
			cout << "\nIn EvaluatePattern, invalid pattern argument 2 type.\n";
			return false;
		}

		if(validCount == 0) 
		{
			cout << "Pattern while is not satisfied.\n";			
			return false;
		}
		return true;
	}

	else if(patternSyn.type == IF)
	{
		vector<int> stmts;
		bool usingIntermediateResult_if = false;
		int validCount = 0;

		//get appropriate stmt, while, if, prog_line
		if (intermediateResult.IsListEmpty(patternSyn)) {
			//cout << "No intermediate result for " << patternSyn.value << ", get all stmts\n";
			stmts = StmtTypeTable::GetAllStmtsOfType(patternSyn.type);
		}

		else {
			//cout << "Get " << patternSyn.value << " from intermediate result table";
			intermediateResult.GetList(patternSyn.value, stmts);
			usingIntermediateResult_if = true;
		}

		//pattern ifs(_,_,_)
		if(arg1Type == UNDERSCORE)
		{
			//get all the while
			for(vector<int>::iterator it = stmts.begin(); it != stmts.end(); ++it)
			{
				if(usingIntermediateResult_if)
				{
					//do nothing, no need to remove anything
				}
				else
				{
					//add all stmts to table
					intermediateResult.Insert(patternSyn.value , *it);
				}
			}
			return true;
		}

		//pattern ifs("x",_,_)
		else if(arg1Type == IDENT)
		{
			//------------Get intermediate result of type arg2------------
			vector<string> vars;
			bool usingIntermediateResult_vars = false;

			if(intermediateResult.IsListEmpty(arg1.syn)) {
				vars = VarTable::GetAllVarNames();
			}

			else {
				intermediateResult.GetList(arg1Syn.value , vars);
				usingIntermediateResult_vars = true;
			}

			//loop afterStmt.size() * beforeStmt.size() times, if all invalid, validCount will be 0, return false
			validCount = stmts.size() * vars.size();

			for (vector<int>::iterator it_stmts = stmts.begin(); it_stmts != stmts.end(); ++it_stmts) {
				for (vector<string>::iterator it_vars = vars.begin(); it_vars != vars.end(); ++it_vars) {

					int varIndex = VarTable::GetIndexOfVar(*it_vars);

					bool isUses = Uses::IsStmtUsingVar(*it_stmts,varIndex);

					if (usingIntermediateResult_if && usingIntermediateResult_vars) {
						if (isUses) {
							bool isDirectLink;
							if (!intermediateResult.HasLinkBetweenColumns(patternSyn.value, *it_stmts, arg1Syn.value, *it_vars, isDirectLink)) {
								if (intermediateResult.HasLink(patternSyn.value, *it_stmts) && intermediateResult.HasLink(arg1Syn.value, *it_vars)) {
									if (isDirectLink) {
										intermediateResult.InsertPair(patternSyn.value, *it_stmts, arg1Syn.value, *it_vars);
									}
									else {
										//indirect link, do nothing
									}
								}

								//at least one no links
								else {
									intermediateResult.InsertPair(patternSyn.value, *it_stmts, arg1Syn.value, *it_vars);
								}
							}
						} 
						else {
							bool dummy;
							if (intermediateResult.HasLinkBetweenColumns(patternSyn.value, *it_stmts, arg1Syn.value, *it_vars, dummy))
								intermediateResult.Unlink(patternSyn.value, *it_stmts, arg1Syn.value, *it_vars);
							--validCount;
						}
					}

					//at least one of the synonym list is new, or both
					else {
						if (isUses) {
							intermediateResult.InsertPair(patternSyn.value, *it_stmts, arg1Syn.value, *it_vars);
						} 
						else {
							--validCount;
						}
					}
				}
			}

			//after looping, do a update to remove any element without link between this 2 column
			//if (usingIntermediateResult_if && usingIntermediateResult_vars) {
				intermediateResult.RemoveElementsWithoutLink(patternSyn.value, arg1Syn.value);
			//}
		}

		//pattern ifs(v,_,_)
		else if(arg1Type == SYNONYM && arg1Syn.type == VARIABLE)
		{
			string ident = arg1Value;
			ident.erase(remove_if(ident.begin(), ident.end(), [](char x){return isspace(x);}), ident.end());
			ident = ident.substr(1, ident.length()-2);

			int varIndex = VarTable::GetIndexOfVar(ident);
				
			if(varIndex != -1)
			{
				validCount = stmts.size();
				for(vector<int>::iterator it_stmts = stmts.begin(); it_stmts != stmts.end(); ++it_stmts) 
				{
					bool isUses = Uses::IsStmtUsingVar(*it_stmts,varIndex);

					if(usingIntermediateResult_if)
					{
						if(isUses) {}
						else 
						{
							intermediateResult.Remove(patternSyn.value , *it_stmts);
							--validCount;
						}
					}
					else
					{
						if(isUses) intermediateResult.Insert(patternSyn.value , *it_stmts);
						else --validCount;
					}
				}
			}

			else
			{
				cout << "\nIn EvaluatePattern, pattern argument 1 IDENT not found.\n";
				return false;
			}
		}

		else
		{
			cout << "\nIn EvaluatePattern, invalid pattern argument 2 type.\n";
			return false;
		}

		if(validCount == 0) 
		{
			cout << "Pattern while is not satisfied.\n";			
			return false;
		}
		return true;
	}

	else 
	{
		cout << "\nIn EvaluatePattern, invalid pattern synonym type.\n";
		return false; //only pattern a() in assignment 4
	}

	return true;
}


bool QueryEvaluator::EvaluateWith(WithClause with)
{

	return true;
}	

void QueryEvaluator::ClearIntermediateResult()
{
	intermediateResult.Clear();
}

//get data of a particular synonym from pkn
vector<string> QueryEvaluator::GetDataFromPKB(Synonym syn)
{
	vector<string> data;

	if(syn.type == ASSIGN || syn.type == STMT || syn.type == WHILE ||
		syn.type == IF || syn.type == CALL|| syn.type == PROG_LINE)
	{
		//stmtTypeTable
		vector<int> result_int;
		vector<string> result;
		result_int = StmtTypeTable::GetAllStmtsOfType(syn.type);

		//remove duplicate
		set<int> s( result_int.begin(), result_int.end() );
		result_int.assign( s.begin(), s.end() );

		data = ITOS(result_int);
		return data;
	}

	else if(syn.type == CONSTANT)
	{
		//constTable
		vector<int> result_int;
		vector<string> result;
		result_int = ConstTable::GetAllConst();

		//remove duplicate
		set<int> s( result_int.begin(), result_int.end() );
		result_int.assign( s.begin(), s.end() );

		data = ITOS(result_int);
		return data;
	}

	else if(syn.type == PROCEDURE)
	{
		//procTable
		vector<string> result = ProcTable::GetAllProcNames();
		return result;
	}

	else if(syn.type == VARIABLE)
	{
		//varTable
		vector<string> result = VarTable::GetAllVarNames(); 
		 
		return result;

	}

	else
	{
		cout << "In GetDataFromPKB: Invalid select type.\n";
		return vector<string>();
	}		

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


string QueryEvaluator::ITOS(int num)
{
	return to_string(long long(num));
}

vector<string> QueryEvaluator::ITOS(vector<int> intList)
{
	vector<string> strList;

	for(int i=0; i < intList.size(); ++i)
		strList.push_back(ITOS(intList[i]));
	
	return strList;
}

int QueryEvaluator::STOI(string s)
{
	int i;
    istringstream ss(s);
    ss >> i;
    
	return i;
}

vector<int> QueryEvaluator::STOI(vector<string> strList)
{
	vector<int> intList;

	for(int i=0; i < strList.size(); ++i)
		intList.push_back(STOI(strList[i]));

	return intList;
}
