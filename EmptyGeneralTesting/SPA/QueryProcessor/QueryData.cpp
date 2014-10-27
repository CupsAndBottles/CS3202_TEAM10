#include "QueryData.h"

std::vector<Declaration> QueryData::declarations;
std::vector<SelectClause> QueryData::selectClauses;	
std::vector<SuchThatClause> QueryData::suchThatClauses;
std::vector<PatternClause>QueryData::patternClauses;
std::vector<WithClause>QueryData::withClauses;

void QueryData::InsertDeclaration(Synonym synonym)
{
	declarations.push_back(Declaration(synonym));
}

void QueryData::InsertSelect(Synonym synonym)
{
	selectClauses.push_back(SelectClause(synonym));
}

void QueryData::InsertPattern(Synonym synonym, Argument arg1, Argument arg2)
{
	patternClauses.push_back(PatternClause(synonym, arg1, arg2));
}

void QueryData::InsertSuchThat(Relationship relationship, Argument arg1, Argument arg2)
{
	suchThatClauses.push_back(SuchThatClause(relationship, arg1, arg2));
}

void QueryData::InsertWith(std::string arg1, std::string arg2)
{
	withClauses.push_back(WithClause(arg1, arg2));
}

std::vector<Declaration> QueryData::GetDeclarations()
{
	return declarations;
}

std::vector<SelectClause> QueryData::GetSelects()
{
	return selectClauses;
}

std::vector<PatternClause> QueryData::GetPatterns()
{
	return patternClauses;
}

std::vector<SuchThatClause> QueryData::GetSuchThats()
{
	return suchThatClauses;
}

std::vector<WithClause> QueryData::GetWiths()
{
	return withClauses;
}

bool QueryData::IsSynonymExist(std::string synonym, SynonymType type)
{
	for(std::vector<Declaration>::iterator it = declarations.begin(); it != declarations.end(); ++it)
	{
		if((*it).synonym.synonym == synonym && (*it).synonym.type == type)
				return true;
	}

	return false;
}

bool QueryData::IsSynonymExist(std::string synonym, SynonymType *type)
{
	for(std::vector<Declaration>::iterator it = declarations.begin(); it != declarations.end(); ++it)
	{
		if((*it).synonym.synonym == synonym) {
			*type = (*it).synonym.type;
			return true;
		}
	}

	return false;
}

bool QueryData::IsSynonymExist(std::string synonym, std::vector<SynonymType> typeList)
{
	for(std::vector<Declaration>::iterator i = declarations.begin(); i != declarations.end(); ++i)
	{
		if((*i).synonym.synonym == synonym) {
			for(std::vector<SynonymType>::iterator j = typeList.begin(); j != typeList.end(); ++j)
			{
				if((*i).synonym.type == (*j))
					return true;
			}
		}
	}

	return false;
}