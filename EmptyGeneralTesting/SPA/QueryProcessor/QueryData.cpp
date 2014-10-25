#include "QueryData.h"

std::vector<Declaration> QueryData::declarations;
std::vector<SelectClause> QueryData::selectClauses;	
std::vector<SuchThatClause> QueryData::suchThatClauses;
std::vector<PatternClause>QueryData::patternClauses;
std::vector<WithClause>QueryData::withClauses;

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

bool QueryData::IsSynonymExist(std::string synonym, std::vector<std::string> typeList)
{
	for(std::vector<Declaration>::iterator i = declarations.begin(); i != declarations.end(); ++i)
	{
		if((*i).synonym == synonym) {
			for(std::vector<std::string>::iterator j = typeList.begin(); j != typeList.end(); ++j)
			{
				if((*i).type == (*j))
					return true;
			}
		}
	}

	return false;
}