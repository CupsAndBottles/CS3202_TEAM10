#include "QueryValidator.h"
#include <sstream>
#include <algorithm>
#include <iostream>
#include "RelTable.h"

const std::string QueryValidator::de[] = {"stmt", "assign", "while", "variable", "prog_line", "constant"};
const std::string QueryValidator::rel[] = {"Modifies", "Uses", "Parent", "Parent*", "Follows", "Follows*"};
 
QueryValidator::QueryValidator(void) {}

bool QueryValidator::ValidateQuery(std::string query, QueryData &queryData)
{
	std::vector<std::string> tokenList;
	std::string token;
	std::string delim = " ,()";

	//tokenize query
	Tokenize(query,tokenList,delim);

	std::vector<std::string>::iterator it = tokenList.begin();
	token = *it;

	//validate declaration
	if(IsDeclaration(token))	//if token is design entity
	{
		std::string type = token;

		if(++it == tokenList.end())	return false;
		token = *it;

		//get the synonym
		while(!IsSemiColon(token))
		{
			Synonym synonym;
			synonym.value = token;

			//validate declaration
			if(!ValidateDeclaration(synonym, type))	return false;

			//save declaration
			queryData.InsertDeclaration(synonym);

			if(++it == tokenList.end())	return false;
			token = *it;
		}

		if(++it == tokenList.end())	return false;
		token = *it;
	}

	//no declaration
	else return false;
	
	//check if declaration is empty
	if(queryData.GetDeclarations().empty()) {
		std::cout << "Invalid Query: No declaration.\n";
		return false;
	}

	//check if next token is select, and validate select
	if(IsSelect(token))
	{
		if(++it == tokenList.end())	return false;
		token = *it;
		
		Synonym synonym;
		synonym.value = token;

		if(!ValidateSelect(synonym))	return false;
			
		else queryData.InsertSelect(synonym);
	}

	//no select
	else return false;

	//get next token
	if(++it == tokenList.end())	return true;
	token = *it;

	//validate such that, pattern
	while(IsSuchThat(token) || IsPattern(token)) 
	{
		bool endOfQuery = false, hasSuchThat = false, hasPattern = false;

		if(IsSuchThat(token))	//such that or and
		{
			if(IsSuchThat(token))	//"such"
			{
				if(++it == tokenList.end())	return false;	//ignore "that"
				token = *it;
			}

			if(++it == tokenList.end())	return false;	//get RelationshipType
			token = *it;

			Argument arg1, arg2;

			if(IsRelationship(token)) //uses, modifies, parents, etc.
			{
				std::string rel = token;			

				if(++it == tokenList.end())	return false;	//get arg1
				token = *it;
				arg1.value = token;

				if(++it == tokenList.end())	return false;	//get arg2
				token = *it;
				arg2.value = token;

				RelationshipType rel_enum;

				if(!ValidateRelationship(rel, rel_enum, arg1, arg2))	return false;

				queryData.InsertSuchThat(rel_enum, arg1, arg2);
			}

			else return false;
			
			hasSuchThat = true;

			if(++it == tokenList.end())
				endOfQuery = true; //if no more token = end of query

			else token = *it;
		}

		//to ensure maximum 1 such that and 1 pattern in query
		if(endOfQuery || (hasSuchThat && hasPattern))	return true;

		if(IsPattern(token))	//pattern or and
		{			
			Argument arg1, arg2;
			Synonym synonym;

			if(++it == tokenList.end())	return false;	//get type
			token = *it;
			synonym.value = token;

			if(++it == tokenList.end())	return false;	//get arg1
			token = *it;
			arg1.value = token;

			if(++it == tokenList.end())	return false;	//get arg2
			token = *it;
			arg2.value = token;

			if(QueryData::IsSynonymExist(synonym.value, ASSIGN))	//only assign, a("x","x+y")	
			{
				synonym.type = ASSIGN;

				if(!ValidatePattern(synonym, arg1, arg2))	
					return false;

				queryData.InsertPattern(synonym, arg1, arg2);
			}

			else return false;

			hasPattern = true;

			if(++it == tokenList.end())
				endOfQuery = true;	//if no more token = end of query

			else token = *it;
		}

		if(endOfQuery || (hasSuchThat && hasPattern))	return true;
	}

	return false;
}

//does not take care of whitespace in expression, need to implement that
//pattern a(" x ", " x + y ")
void QueryValidator::Tokenize(std::string str, std::vector<std::string> &tokens, std::string delim)
{
	std::stringstream stringStream(str);
	std::string line;
	
	while(std::getline(stringStream, line)) 
	{
		std::size_t prev = 0, pos;
		while ((pos = line.find_first_of(delim, prev)) != std::string::npos)
		{
			if (pos > prev)
				tokens.push_back(line.substr(prev, pos-prev));
			prev = pos+1;
		}
		if (prev < line.length())
			tokens.push_back(line.substr(prev, std::string::npos));
	}
}

/*
- Check if there is any duplicated synonym in declaration. E.g. assign a1; while a1;
- Design entities allowed in declaration are stmt, assign, while, if, variable, constant, procedure, prog_line, call
  (Although assignnment 4 only have stmt, assign, while, variable, constant, prog_line)
*/
bool QueryValidator::ValidateDeclaration(Synonym &synonym, std::string type)
{
	//check duplicated declaration
	if(QueryData::IsSynonymExist(synonym.value))
		return false;

	//convert type(string) to enum
	if(!GetEnumSynonymType(type,synonym.type)) {
		std::cout << "Invalid Query: No matching design entity type for declaration.\n";
		return false;
	}

	//Design entity must be one of the following
	const SynonymType list[] = {ASSIGN, STMT, WHILE, VARIABLE, CONSTANT, PROG_LINE};
	std::vector<SynonymType> list_vec(list, list + sizeof(list) / sizeof(list[0]));

	if(std::find(list_vec.begin(), list_vec.end(), synonym.type) != list_vec.end())
		return true;

	return false;
}

/*
- Check if select BOOLEAN, if yes return synonym=type="BOOLEAN"
- Otherwise, check if synonym is declared in declaration, if yes get the type and return type
*/
bool QueryValidator::ValidateSelect(Synonym &synonym)
{
	//pass reference twice, not sure will work or not
	if(QueryData::IsSynonymExist(synonym.value, &synonym.type))
		return true;

	else return false;
}

/*
pattern a( Synonym | _ | "Ident" , _ | "Expression" | _"Expression"_ )
*/
bool QueryValidator::ValidatePattern(Synonym synonym, Argument &arg1, Argument &arg2)
{
	if(synonym.type == ASSIGN)
	{
		if(arg1.value == "_") arg1.type = UNDERSCORE;
		
		else if(QueryData::IsSynonymExist(arg1.value, VARIABLE))	//must be variable
		{
			arg1.type = SYNONYM;
			arg1.syn = Synonym(arg1.value, VARIABLE);
		}
			
		else if(IsIdent(arg1.value)) arg1.type = IDENT;

		else return false;

		if(arg2.value == "_") arg2.type = UNDERSCORE;

		else if(IsExpression(arg2.value)) arg2.type = EXPRESSION;

		else return false;

		return true;
	}

	else return false;
}

bool QueryValidator::ValidateRelationship(std::string rel, RelationshipType &rel_enum, Argument &arg1, Argument &arg2)
{
	//convert relationship string to enum
	if(!GetEnumRelationshipType(rel,rel_enum)) {
		std::cout << "Invalid Query: No matching relationship type for such that.\n";
		return false;
	}

	SynonymType synonymType;

	//validate argument 1
	if(IsUnderscore(arg1.value))	arg1.type = UNDERSCORE;

	else if(IsInteger(arg1.value))	arg1.type = INTEGER;

	else if(IsIdent(arg1.value))	arg1.type = IDENT;

	else if(QueryData::IsSynonymExist(arg1.value, &synonymType)) {
		arg1.type = SYNONYM;
		arg1.syn = Synonym(arg1.value, synonymType);
	}
		
	else return false;
	
	try {
		//get stored argument type
		std::vector<ArgumentType> argType = RelTable::GetRelArgType(rel_enum, ARG1);
		std::vector<SynonymType> argSynonymType = RelTable::GetRelArgSynonymType(rel_enum, ARG1);

		//check whether arg1.type is one of the allowed type
		if(std::find(argType.begin(), argType.end(), arg1.type) != argType.end()) {
			//if type is synonym
			if(arg1.type == SYNONYM) {
				//check whether synonym type is one of the allowed type
				if(std::find(argSynonymType.begin(), argSynonymType.end(), synonymType) != argSynonymType.end()) {}
				else return false;
			}
		}

		else return false;


		//validate argument 2
		if(IsUnderscore(arg2.value))	arg2.type = UNDERSCORE;

		else if(IsInteger(arg2.value))	arg2.type = INTEGER;

		else if(IsIdent(arg2.value))	arg2.type = IDENT;

		else if(QueryData::IsSynonymExist(arg2.value, &synonymType)) {
			arg2.type = SYNONYM;
			arg2.syn = Synonym(arg2.value, synonymType);
		}
		
		else return false;

		//get stored argument type
		argType = RelTable::GetRelArgType(rel_enum, ARG2);
		argSynonymType = RelTable::GetRelArgSynonymType(rel_enum, ARG2);
	
		//check whether arg1.type is one of the allowed type
		if(std::find(argType.begin(), argType.end(), arg2.type) != argType.end()) {
			//if type is synonym
			if(arg2.type == SYNONYM) {
				//check whether synonym type is one of the allowed type
				if(std::find(argSynonymType.begin(), argSynonymType.end(), synonymType) != argSynonymType.end()) {}
				else return false;
			}
		}

		else return false;

		return true;
	}
	catch(const std::invalid_argument &e) {
		std::cerr << e.what() << std::endl;
		return false;
	}
}

/*
"factor"
"factor+factor"
_"factor"_
_"factor+factor"_
_
factor : NAME | INTEGER
assume whitespace hasn't been remove
" x ", _ " x + y" _ are also valid
assume _ and " " is included, e.g. _"x"_
*/
bool QueryValidator::IsExpression(std::string str)
{
	//remove white spaces
	str.erase(std::remove_if(str.begin(), str.end(), [](char x){return isspace(x);}), str.end());
	
	//eliminates " " or _" "_ and get the content
	if(str.at(0) == '\"' && str.at(str.length()-1) == '\"')		//"..."
		str = str.substr(1, str.length()-2);

	else if (str.at(0) == '_' && str.at(str.length()-1) == '_')	//_..._
	{
		if(str.at(1) == '\"' && str.at(str.length()-2) == '\"')	//_"..."_
		{
			int length = str.length() - 4;
			str = str.substr(2, 
				length);
		}

		else return false;
	}

	else return false;

	std::vector<std::string> tokenList;
	std::string delim = "+";

	Tokenize(str, tokenList, delim);

	for(std::vector<std::string>::iterator it = tokenList.begin(); it != tokenList.end(); ++it) {
		if(!(IsName(*it) || IsInteger(*it)))
			return false;
	}
	
	return true;
}

/*
IDENT: LETTER (LETTER| DIGIT | '#')*
IDENT must be an alphabet followed by 0 or more times of alphanumeric character or '#'
assume " " is included, e.g. "x"
*/
bool QueryValidator::IsIdent(std::string str)
{
	//remove white spaces
	str.erase(std::remove_if(str.begin(), str.end(), [](char x){return isspace(x);}), str.end());
	
	//eliminates " " and get the content
	if(str.at(0) == '\"' && str.at(str.length()-1) == '\"')		//"..."
		str = str.substr(1, str.length()-2);

	else return false;

	std::string::iterator it = str.begin();
	
	//first character must be alphabet
	if(!str.empty() && isalpha(*it))	++it;
	else return false;

	//subsequent character must be alphanumeric or "#"
	while (it != str.end() && (isalnum(*it) || (*it) == '#')) ++it;
    return !str.empty() && it == str.end();
}

/*
Name : LETTER (LETTER | DIGIT)*
Name must be an alphabet followed by 0 or more times of alphanumeric character
*/
bool QueryValidator::IsName(std::string s)
{
	std::string::iterator it = s.begin();

	//first character must be alphabet
	if(!s.empty() && isalpha(*it))	++it;
	else return false;

	//subsequent character must be alphanumeric
	while (it != s.end() && (isalnum(*it))) ++it;
    return !s.empty() && it == s.end();
}

/*
Integer : DIGIT+
Integer must be repetition of 1 or more times of number
*/
bool QueryValidator::IsInteger(const std::string& s)
{
    std::string::const_iterator it = s.begin();

    while (it != s.end() && isdigit(*it)) ++it;

    return !s.empty() && it == s.end();
}

/*
Convert synonym type string to SynonymType enum
*/
bool QueryValidator::GetEnumSynonymType(std::string type, SynonymType &enumType) 
{
	if(type == "assign")			enumType = ASSIGN;
	else if(type == "stmt")			enumType = STMT;
	else if(type == "while")		enumType = WHILE;
	else if(type == "variable")		enumType = VARIABLE;
	else if(type == "prog_line")	enumType = PROG_LINE;
	else if(type == "constant")		enumType = CONSTANT;
	//else if(type == "if")			enumType = IF;
	//else if(type == "procedure")	enumType = PROCEDURE;
	//else if(type == "call")		enumType = CALL;
	//else if(type == "BOOLEAN")	enumType = BOOLEAN;
	else return false;

	return true;
}

/*
Convert relationship type string to SynonymType enum
*/
bool QueryValidator::GetEnumRelationshipType(std::string type, RelationshipType &enumType) 
{
	if(type == "Modifies")			enumType = MODIFIES;
	else if(type == "Uses")			enumType = USES;
	else if(type == "Parent")		enumType = PARENT;
	else if(type == "Parent*")		enumType = PARENTT;
	else if(type == "Follows")		enumType = FOLLOWS;
	else if(type == "Follows*")		enumType = FOLLOWST;
	//else if(type == "Calls")		enumType = CALLS;
	//else if(type == "Calls*")		enumType = CALLST;
	//else if(type == "Next")			enumType = NEXT;
	//else if(type == "Next*")		enumType = NEXTT;
	//else if(type == "Affects")		enumType = AFFECTS;
	//else if(type == "Affects&")		enumType = AFFECTST;
	else return false;

	return true;
}




//string matching functions
bool QueryValidator::IsSelect(std::string str)
{
	if(str == "Select")	return true;
	return false;
}

bool QueryValidator::IsSemiColon(std::string str)
{
	if(str == ";")	return true;
	return false;
}

bool QueryValidator::IsSuchThat(std::string str)
{
	if(str == "such")	return true;
	return false;
}

bool QueryValidator::IsPattern(std::string str)
{
	if(str == "pattern")	return true;
	return false;
}

bool QueryValidator::IsUnderscore(std::string str)
{
	if(str == "_")	return true;
	return false;
}

/*
Check whether string is one of the design entities
*/
bool QueryValidator::IsDeclaration(std::string str)
{
	std::vector<std::string> DesignEntity(de, de + sizeof(de) / sizeof(de[0]));

	if (std::find(DesignEntity.begin(), DesignEntity.end(), str) != DesignEntity.end())
		return true;

	return false;
}

/*
check whether string is one of the RelationshipType
*/
bool QueryValidator::IsRelationship(std::string str)
{
	std::vector<std::string> rel_vec(rel, rel + sizeof(rel) / sizeof(rel[0]));

	if (std::find(rel_vec.begin(), rel_vec.end(), str) != rel_vec.end())
		return true;

	return false;
}
