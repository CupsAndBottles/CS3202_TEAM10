#pragma once
#include <string>
#include <vector>
#include "Grammar.h"

/*
Class for storing query string data, accessed by QueryValidator and QueryEvaluator
*/
class QueryData
{
private:
	static std::vector<Declaration> declarations;
	static std::vector<SelectClause> selectClauses;	
	static std::vector<SuchThatClause> suchThatClauses;
	static std::vector<PatternClause> patternClauses;
	static std::vector<WithClause> withClauses;

public:
	QueryData(void);
	~QueryData(void);

	void InsertDeclaration(std::string, std::string);
	void InsertSelect(std::string, std::string);
	void InsertPattern(std::string, std::string, std::string);
	void InsertSuchThat(std::string, std::string, std::string);
	void InsertWith(std::string, std::string);

	std::vector<Declaration> GetDeclarations();
	std::vector<SelectClause> GetSelects();		//if empty = select BOOLEAN
	std::vector<SuchThatClause> GetSuchThats();
	std::vector<PatternClause> GetPatterns();
	std::vector<WithClause> GetWiths();

	static bool IsSynonymExist(std::string, std::string);
	static bool IsSynonymExist(std::string, std::string *);
};