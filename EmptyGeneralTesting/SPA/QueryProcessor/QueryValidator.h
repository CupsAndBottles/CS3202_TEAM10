#pragma once
#include <string>
#include <vector>
#include "QueryData.h"


class QueryValidator
{

private:
	static const std::string de[];
	static const std::string rel[];

public:
	QueryValidator(void);
	~QueryValidator(void);

	bool ValidateQuery(std::string, QueryData&);
	void Tokenize(std::string, std::vector<std::string>&, std::string);
	bool IsDeclaration(std::string);
	bool IsSelect(std::string);
	bool IsSemiColon(std::string);
	bool IsSuchThat(std::string);
	bool IsPattern(std::string);
	bool IsWith(std::string);
	bool IsAnd(std::string);
	bool IsOpenBracket(std::string);
	bool IsCloseBracket(std::string);
	bool IsRelationship(std::string);
	bool IsUnderScore(std::string);
	
	bool ValidateDeclaration(Synonym&, std::string);
	bool ValidateSelect(Synonym&, bool);
	bool ValidateRelationship(std::string, Relationship&, Argument&, Argument&);
	bool ValidatePattern(Synonym, Argument&, Argument&, Argument&);
	bool ValidateWith(std::string, std::string);

	bool ValidateModifies(Argument&, Argument&);
	bool ValidateParent(Argument&, Argument&);
	bool ValidateFollows(Argument&, Argument&);
	
	bool IsInteger(const std::string&);
	bool IsString(const std::string&);
	bool IsBoolean(std::string);
	bool IsExpression(std::string);
	bool IsIdent(std::string);
	bool IsName(std::string);
	bool GetSynonymType(std::string, SynonymType&); 
};

