#pragma once
#include <string>
#include <vector>
#include "QueryData.h"


class QueryValidator
{

private:
	static const std::string de[];
	static const std::string rel[];
	std::vector<std::string> DesignEntity;
	std::vector<std::string> Relationship;

public:
	QueryValidator(void);
	~QueryValidator(void);

	bool ValidateQuery(std::string, QueryData);
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

	bool ValidatePattern(std::string, std::string, std::string, std::string);
	bool ValidateWith(std::string, std::string);
	bool ValidateSelect(std::string, std::string&);
	
	bool IsInteger(const std::string&);
	bool IsString(const std::string&);
};

