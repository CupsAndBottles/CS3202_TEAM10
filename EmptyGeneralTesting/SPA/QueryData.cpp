#include "QueryData.h"


QueryData::QueryData(void)
{
}

void QueryData::InsertDeclaration(std::string type, std::string synonym)
{
	declarations.push_back(Declaration(type, synonym));
}

void QueryData::InsertSelect(std::string type, std::string synonym)
{
	selectClauses.push_back(SelectClause(type, synonym));;
}

void QueryData::InsertPattern(std::string type, std::string arg1, std::string arg2)
{
	patternClauses.push_back(PatternClause(type, arg1, arg2));
}

void QueryData::InsertSuchThat(std::string condition, std::string arg1, std::string arg2)
{
	suchThatClauses.push_back(SuchThatClause(condition, arg1, arg2));
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

bool QueryData::IsSynonymExist(std::string synonym, std::string type)
{
	for(std::vector<Declaration>::iterator it = declarations.begin(); it != declarations.end(); ++it)
	{
		if((*it).synonym == synonym && (*it).type == type)
				return true;
	}

	return false;
}

bool QueryData::IsSynonymExist(std::string synonym, std::string *type)
{
	for(std::vector<Declaration>::iterator it = declarations.begin(); it != declarations.end(); ++it)
	{
		if((*it).synonym == synonym) {
			*type = (*it).type;
			return true;
		}
	}

	return false;
}