#include "QueryValidator.h"
#include <sstream>
#include <algorithm>
#include <iostream>

const std::string QueryValidator::de[] = {"procedure", "stmt", "stmtLst", "assign", "call", "while", "if", "variable", "prog_line", "constant"};
const std::string QueryValidator::rel[] = { "Modifies", "Uses", "Calls", "Calls*", "Parent", "Parent*", "Follows", "Follows*", "Next", "Next*", "Affects", "Affects*" };
 
QueryValidator::QueryValidator(void) {}

bool QueryValidator::ValidateQuery(std::string query, QueryData &queryData)
{
	std::vector<std::string> tokenList;
	std::string token;
	std::string delim = " ,<>()=";

	//tokenize query
	Tokenize(query,tokenList,delim);

	std::vector<std::string>::iterator it = tokenList.begin();
	token = *it;

	//validate declaration
	while(IsDeclaration(token) && !IsSelect(token))	//if token is design entity and not select
	{
		std::string type = token;

		if(++it == tokenList.end())	return false;
		token = *it;

		//get the synonym
		while(!IsSemiColon(token))
		{
			Synonym synonym;
			synonym.synonym = token;

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

		if(IsOpenBracket(token)) //<
		{
			if(++it == tokenList.end())	return false;
			token = *it;

			//if <> without synonym in it
			if(IsCloseBracket(token))	return false;

			while(!IsCloseBracket(token)) //>
			{
				Synonym synonym;
				synonym.synonym = token;

				if(!ValidateSelect(synonym,"true"))	return false;
				
				queryData.InsertSelect(synonym);

				if(++it == tokenList.end())	return false;
				token = *it;
			}

			if(++it == tokenList.end())	return false;
			token = *it;
		}

		else 
		{
			Synonym synonym;
			synonym.synonym = token;

			if(!ValidateSelect(synonym,"false"))	return false;
			
			else queryData.InsertSelect(synonym);
		}
	}

	//no select
	else return false;

	//validate such that, pattern, with
	while(IsSuchThat(token) || IsPattern(token) || IsWith(token)) 
	{
		bool endOfQuery = false;

		while(IsSuchThat(token) || IsAnd(token))	//such that or and
		{
			if(IsSuchThat(token))	//"such"
			{
				if(++it == tokenList.end())	return false;	//ignore "that"
				token = *it;
			}

			if(++it == tokenList.end())	return false;	//get relationship
			token = *it;

			Argument arg1, arg2;

			if(IsRelationship(token)) //uses, modifies, parents, etc.
			{
				std::string relationship = token;			

				if(++it == tokenList.end())	return false;	//get arg1
				token = *it;
				arg1.value = token;

				if(++it == tokenList.end())	return false;	//get arg2
				token = *it;
				arg2.value = token;

				Relationship rel_enum;

				if(!ValidateRelationship(relationship, rel_enum, arg1, arg2))	return false;
				queryData.InsertSuchThat(rel_enum, arg1, arg2);
			}

			else return false;

			if(++it == tokenList.end())
			{
				endOfQuery = true;
				break;	//if no more token = end of query
			}
			token = *it;
		}

		if(endOfQuery)	return true;

		while(IsPattern(token) || IsAnd(token))	//pattern or and
		{			

				Argument arg1, arg2, arg3;
				Synonym synonym;

				if(++it == tokenList.end())	return false;	//get type
				token = *it;
				synonym.synonym = token;

				if(++it == tokenList.end())	return false;	//get arg1
				token = *it;
				arg1.value = token;

				if(++it == tokenList.end())	return false;	//get arg2
				token = *it;
				arg2.value = token;

				if(QueryData::IsSynonymExist(synonym.synonym, synonym.type))		
				{
					if(synonym.type == IF)	//if pattern if(var,_,_), get arg3
					{
						if(++it == tokenList.end())	return false;	//get arg3
						token = *it;
						arg3.value = token;
					}

					if(!ValidatePattern(synonym, arg1, arg2, arg3))	
						return false;

					queryData.InsertPattern(synonym, arg1, arg2);
				}

				else return false;

				if(++it == tokenList.end())
				{
					endOfQuery = true;
					break;	//if no more token = end of query
				}
				token = *it;
		}

		if(endOfQuery)	return true;
		/*
		while(IsWith(token) || IsAnd(token))	//with or and
		{			
			if(++it == tokenList.end())	return false;	//get arg1
			token = *it;
			std::string arg1 = token;

			if(++it == tokenList.end())	return false;	//get arg2
			token = *it;
			std::string arg2 = token;

			if(!ValidateWith(arg1,arg2))	return false;
			queryData.InsertWith(arg1,arg2);
				
			if(++it == tokenList.end())
			{
				endOfQuery = true;
				break;	//if no more token = end of query
			}
			token = *it;
		}

		if(endOfQuery)	return true;*/
	}

	return true;
}

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
	if(QueryData::IsSynonymExist(synonym.synonym, synonym.type))
		return false;

	//convert type(string) to enum
	if(!GetSynonymType(type,synonym.type)) {
		std::cout << "Invalid Query: No matched design entity type for declaration.\n";
		return false;
	}

	//Design entity must be one of the following
	const SynonymType list[] = {ASSIGN, STMT, WHILE, IF, VARIABLE, CONSTANT, PROCEDURE, PROG_LINE, CALL};
	std::vector<SynonymType> list_vec(list, list + sizeof(list));

	if(std::find(list_vec.begin(), list_vec.end(), synonym.type) != list_vec.end())
		return true;

	return false;
}

/*
- Check if select BOOLEAN, if yes return synonym=type="BOOLEAN"
- Otherwise, check if synonym is declared in declaration, if yes get the type and return type
*/
bool QueryValidator::ValidateSelect(Synonym &synonym, bool hasBracket)
{
	//can have attrRef

	//cannot have BOOLEAN inside <>
	if(hasBracket && IsBoolean(synonym.synonym))
		return false;

	else if(IsBoolean(synonym.synonym)) {
		synonym.type = BOOLEAN;
		return true;
	}

	//pass reference twice, not sure will work or not
	else if(QueryData::IsSynonymExist(synonym.synonym, &synonym.type))
		return true;

	else return false;
}

/*
pattern a	 ( Synonym | _ | "Ident" , _ | "Expression" | _"Expression"_ )
pattern if	 ( Synonym | _ | "Ident" , _ )
pattern while( Synonym | _ | "Ident" , _ )
*/
bool QueryValidator::ValidatePattern(Synonym synonym, Argument &arg1, Argument &arg2, Argument &arg3)
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
		
		else if(QueryData::IsSynonymExist(arg2.value, VARIABLE)) 
		{
			arg2.type = SYNONYM;
			arg2.syn = Synonym(arg2.value, VARIABLE);
		}

		else if(IsExpression(arg2.value)) arg2.type = EXPRESSION;

		else return false;

		return true;
	}

	else if(synonym.type == IF)
	{
		if(arg1.value == "_") arg1.type = UNDERSCORE;
		
		else if(QueryData::IsSynonymExist(arg1.value, VARIABLE))	//must be variable
		{
			arg1.type = SYNONYM;
			arg1.syn = Synonym(arg1.value, VARIABLE);
		}
			
		else if(IsIdent(arg1.value)) arg1.type = IDENT;

		else return false;

		if(arg2.value == "_" && arg3.value == "_") 
		{
			arg2.type = UNDERSCORE;
			arg3.type = UNDERSCORE;
		}

		else return false;

		return true;
	}

	else if(synonym.type == WHILE)
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

		else return false;

		return true;
	}

	else return false;
}

bool QueryValidator::ValidateWith(std::string arg1, std::string arg2)
{/*
	//if arg1 = __.__, e.g. p.procname, tokenize it, else it must be prog_line synonym
	if(arg1.find(".") != std::string::npos)
	{
		std::string delim = ".";
		std::vector<std::string> arg1_tokens;
		Tokenize(arg1,arg1_tokens,delim);

		//only 2 tokens separated by .
		if(arg1_tokens.size() != 2) {
			std::cout << "Invalid attrRef in With\n";
			return false;
		}

		//if p.procName, p must be declared as procedure
		if((arg1_tokens.back() == "procName" && QueryData::IsSynonymExist(arg1_tokens.front(), "procedure")) ||
			(arg1_tokens.back() == "varName"  && QueryData::IsSynonymExist(arg1_tokens.front(), "variable")))
		{
			//if arg2 = p.procName or v.varName, tokenize it, else it must a "string"
			if(arg2.find(".") != std::string::npos)
			{
				std::string delim = ".";
				std::vector<std::string> arg2_tokens;
				Tokenize(arg2,arg2_tokens,delim);

				//only 2 tokens separated by .
				if(arg2_tokens.size() != 2) {
					std::cout << "Invalid attrRef in With\n";
					return false;
				}

				if(arg2_tokens.back() == "procName" && QueryData::IsSynonymExist(arg2_tokens.front(), "procedure")) {}

				else if(arg2_tokens.back() == "varName" && QueryData::IsSynonymExist(arg2_tokens.front(), "variable")) {}
					
				else return false; // should throw exception
			}

			else if(IsString(arg2)) {}

			else return false;
		}

		else if((arg1_tokens.back() == "value" && QueryData::IsSynonymExist(arg1_tokens.front(), "constant")) ||
			(arg1_tokens.back() == "stmt#"  && (QueryData::IsSynonymExist(arg1_tokens.front(), "stmt")	 || 
												QueryData::IsSynonymExist(arg1_tokens.front(), "assign") ||
												QueryData::IsSynonymExist(arg1_tokens.front(), "if") ||
												QueryData::IsSynonymExist(arg1_tokens.front(), "while") ||
												QueryData::IsSynonymExist(arg1_tokens.front(), "call"))))
		{
			if(arg2.find(".") != std::string::npos)
			{
				std::string delim = ".";
				std::vector<std::string> arg2_tokens;
				Tokenize(arg2,arg2_tokens,delim);

				//only 2 tokens separated by .
				if(arg2_tokens.size() != 2) {
					std::cout << "Invalid attrRef in With\n";
					return false;
				}

				if(arg2_tokens.back() == "stmt#" && (QueryData::IsSynonymExist(arg2_tokens.front(), "stmt")	 || 
													QueryData::IsSynonymExist(arg2_tokens.front(), "assign") ||
													QueryData::IsSynonymExist(arg2_tokens.front(), "if") ||
													QueryData::IsSynonymExist(arg2_tokens.front(), "while") ||
													QueryData::IsSynonymExist(arg2_tokens.front(), "call"))) {}

				else if(arg2_tokens.back() == "value" && QueryData::IsSynonymExist(arg2_tokens.front(), "constant")) {}
					
				else return false; // should throw exception
			}

			else if(IsInteger(arg2)) {}

			else if(QueryData::IsSynonymExist(arg2, "prog_line")) {}

			else return false;
		}

		else return false;
	}

	
	else if(QueryData::IsSynonymExist(arg1, "prog_line"))
	{
		if(arg1.find(".") != std::string::npos)
		{
			std::string delim = ".";
			std::vector<std::string> arg2_tokens;
			Tokenize(arg2,arg2_tokens,delim);

			//only 2 tokens separated by .
			if(arg2_tokens.size() != 2) {
				std::cout << "Invalid attrRef in With\n";
				return false;
			}

			if(arg2_tokens.back() == "stmt#" && (QueryData::IsSynonymExist(arg2_tokens.front(), "stmt")	 || 
												QueryData::IsSynonymExist(arg2_tokens.front(), "assign") ||
												QueryData::IsSynonymExist(arg2_tokens.front(), "if") ||
												QueryData::IsSynonymExist(arg2_tokens.front(), "while") ||
												QueryData::IsSynonymExist(arg2_tokens.front(), "call"))) {}

			else if(arg2_tokens.back() == "value" && QueryData::IsSynonymExist(arg2_tokens.front(), "constant")) {}

			else return false;
		}

		else if(IsInteger(arg2)) {}
			
		else if(QueryData::IsSynonymExist(arg2, "prog_line")) {}

		else return false;
	}
	
	else return false;*/

	return false; //delete this line after uncomment
}
	
bool QueryValidator::ValidateRelationship(std::string rel, Relationship &rel_enum, Argument &arg1, Argument &arg2)
{
	//switch relationship and call function respectively
	if(rel == "Modifies") {
		rel_enum = MODIFIES;
		return ValidateModifies(arg1,arg2);
	}

	else if(rel == "Uses") {
		rel_enum = USES;
		return ValidateModifies(arg1,arg2);
	}

	else if(rel == "Parent") {
		rel_enum = PARENT;
		return ValidateParent(arg1,arg2);
	}

	else if(rel == "Parent*") {
		rel_enum = PARENTT;
		return ValidateParent(arg1,arg2);
	}

	else if(rel == "Follows") {
		rel_enum = FOLLOWS;
		return ValidateFollows(arg1,arg2);
	}

	else if(rel == "Follows*") {
		rel_enum = FOLLOWST;
		return ValidateFollows(arg1,arg2);
	}

	else return false;
}

/*
Modifies(Synonym | Integer | "Ident" , Synonym | _ | "Ident")
Uses	(Synonym | Integer | "Ident" , Synonym | _ | "Ident")
Argument 1 synonym - stmt, assign, while, if, prog_line, call, procedure
Argument 2 synonym - variable
*/
bool QueryValidator::ValidateModifies(Argument &arg1, Argument &arg2)
{
	const SynonymType list[] = {STMT, ASSIGN, WHILE, IF, PROG_LINE, CALL, PROCEDURE};
 
	std::vector<SynonymType> typeList(list, list + sizeof(list));

	SynonymType temp;

	//validate argument 1
	if(QueryData::IsSynonymExist(arg1.value, &temp)) {
		if(std::find(typeList.begin(), typeList.end(), temp) != typeList.end()) {
			arg1.type = SYNONYM;
			arg1.syn = Synonym(arg1.value, temp);
		}

		else return false;
	}
		
	else if(IsInteger(arg1.value)) arg1.type = INTEGER;

	else if(IsIdent(arg1.value)) arg1.type = IDENT;

	else return false;

	//validate argument 2
	if(arg2.value == "_") arg2.type = UNDERSCORE;
		
	else if(QueryData::IsSynonymExist(arg2.value, VARIABLE))	//must be variable
	{
		arg2.type = SYNONYM;
		arg2.syn = Synonym(arg2.value, VARIABLE);
	}
			
	else if(IsIdent(arg2.value)) arg2.type = IDENT;

	else return false;

	return true;
}

/*
Parent (Synonym | _ | Integer , Synonym | _ | Integer)
Parent*(Synonym | _ | Integer , Synonym | _ | Integer)
Argument 1 synonym - stmt, while, if, prog_line
Argument 2 synonym - stmt, assign, while, if, prog_line, call
*/
bool QueryValidator::ValidateParent(Argument &arg1, Argument &arg2)
{ 
	const SynonymType list1[] = {STMT, WHILE, IF, PROG_LINE};
	const SynonymType list2[] = {STMT, ASSIGN, WHILE, IF, PROG_LINE, CALL};

	std::vector<SynonymType> typeList1(list1, list1 + sizeof(list1));
	std::vector<SynonymType> typeList2(list2, list2 + sizeof(list2));

	SynonymType temp;

	//validate argument 1
	if(QueryData::IsSynonymExist(arg1.value, &temp)) {
		if(std::find(typeList1.begin(), typeList1.end(), temp) != typeList1.end()) {
			arg1.type = SYNONYM;
			arg1.syn = Synonym(arg1.value, temp);
		}

		else return false;
	}
		
	else if(IsInteger(arg1.value)) arg1.type = INTEGER;

	else if(arg1.value == "_") arg1.type = UNDERSCORE;

	else return false;

	//validate argument 2
	if(QueryData::IsSynonymExist(arg2.value, &temp))	
	{
		if(std::find(typeList2.begin(), typeList2.end(), temp) != typeList2.end()) {
			arg2.type = SYNONYM;
			arg2.syn = Synonym(arg2.value, temp);
		}

		else return false;
	}

	else if(IsInteger(arg2.value)) arg2.type = INTEGER;

	else if(arg2.value == "_") arg2.type = UNDERSCORE;

	else return false;

	return true;
}

/*
Follows (Synonym | _ | Integer , Synonym | _ | Integer)
Follows*(Synonym | _ | Integer , Synonym | _ | Integer)
Argument 1 synonym - stmt, assign, while, if, prog_line, call
Argument 2 synonym - stmt, assign, while, if, prog_line, call
*/
bool QueryValidator::ValidateFollows(Argument &arg1, Argument &arg2)
{
	const SynonymType list[] = {STMT, ASSIGN, WHILE, IF, PROG_LINE, CALL};

	std::vector<SynonymType> typeList(list, list + sizeof(list));

	SynonymType temp;

	//validate argument 1
	if(QueryData::IsSynonymExist(arg1.value, &temp)) {
		if(std::find(typeList.begin(), typeList.end(), temp) != typeList.end()) {
			arg1.type = SYNONYM;
			arg1.syn = Synonym(arg1.value, temp);
		}

		else return false;
	}
		
	else if(IsInteger(arg1.value)) arg1.type = INTEGER;

	else if(arg1.value == "_") arg1.type = UNDERSCORE;

	else return false;

	//validate argument 2
	if(QueryData::IsSynonymExist(arg2.value, &temp))	
	{
		if(std::find(typeList.begin(), typeList.end(), temp) != typeList.end()) {
			arg2.type = SYNONYM;
			arg2.syn = Synonym(arg2.value, temp);
		}

		else return false;
	}

	else if(IsInteger(arg2.value)) arg2.type = INTEGER;

	else if(arg2.value == "_") arg2.type = UNDERSCORE;

	else return false;

	return true;
}

bool QueryValidator::IsDeclaration(std::string str)
{
	std::vector<std::string> DesignEntity(de, de + sizeof(de));

	if (std::find(DesignEntity.begin(), DesignEntity.end(), str) != DesignEntity.end())
		return true;

	return false;
}

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

bool QueryValidator::IsWith(std::string str)
{
	if(str == "with")	return true;
	return false;
}

bool QueryValidator::IsAnd(std::string str)
{
	if(str == "and")	return true;
	return false;
}

bool QueryValidator::IsOpenBracket(std::string str)
{
	if(str == "<")	return true;
	return false;
}

bool QueryValidator::IsCloseBracket(std::string str)
{
	if(str == ">")	return true;
	return false;
}

bool QueryValidator::IsUnderScore(std::string str)
{
	if(str == "_")	return true;
	return false;
}

bool QueryValidator::IsRelationship(std::string str)
{
	std::vector<std::string> Relationship(rel, rel + sizeof(rel));

	if (std::find(Relationship.begin(), Relationship.end(), str) != Relationship.end())
		return true;

	return false;
}

bool QueryValidator::IsBoolean(std::string str)
{
	if(str == "BOOLEAN")	return true;
	return false;
}

bool QueryValidator::IsExpression(std::string str)
{
	/*
	"x", "x+y" , _"x+y"_ , _"x"_ , _ , "6" , "6+6", "x+6", "6+x"
	*/
	//remove white spaces
	str.erase(std::remove_if(str.begin(), str.end(), [](char x){return isspace(x);}), str.end());
	
	//eliminates " " or _" "_ and get the content
	if(str.at(0) == '\"' && str.at(str.length()-1) == '\"')		//"..."
		str = str.substr(1, str.length()-2);

	else if (str.at(0) == '_' && str.at(str.length()-1) == '_')	//_..._
	{
		if(str.at(1) == '\"' && str.at(str.length()-2) == '\"')	//_"..."_
		{
			int length = (str.length()-2)-2;
			str = str.substr(2, length);
		}

		else return false;
	}

	else return false;

	std::vector<std::string> tokenList;
	std::string token;
	std::string delim = "+*";	//might include () in the future

	//tokenize
	Tokenize(str,tokenList,delim);
	
	//for each factor, check if it is NAME or INTEGER
	for(std::vector<std::string>::iterator it = tokenList.begin(); it != tokenList.end(); ++it)
	{
		token = *it;

		if(!(IsName(*it) || IsInteger(*it)))
			return false;
	}
	
	return true;
}

bool QueryValidator::IsIdent(std::string str)
{
	/*
	alphabet followed by alpanumeric or #
	"x" , "x2", "xy" , "x123", "x#"
	*/

	//remove white spaces
	str.erase(std::remove_if(str.begin(), str.end(), [](char x){return isspace(x);}), str.end());
	
	//eliminates " " and get the content
	if(str.at(0) == '\"' && str.at(str.length()-1) == '\"')		//"..."
		str = str.substr(1, str.length()-2);

	else return false;

	std::string::iterator it = str.begin();
	
	//first character must be alphabet
	if(it != str.end() && isalpha(*it))	++it;
	else return false;

	//subsequent character must be alphanumeric or "#"
	while (it != str.end() && (isalnum(*it) || (*it) == '#')) ++it;
    return !str.empty() && it == str.end();

	return false;
}

bool QueryValidator::IsName(std::string s)
{
	/*
	alphabet followed by alpanumeric
	x , x2, xy , x123
	no ""
	*/
	std::string::iterator it = s.begin();

	//first character must be alphabet
	if(it != s.end() && isalpha(*it))	++it;
	else return false;

	//subsequent character must be alphanumeric
	while (it != s.end() && (isalnum(*it))) ++it;
    return !s.empty() && it == s.end();

	return false;
}

bool QueryValidator::IsInteger(const std::string& s)
{
    std::string::const_iterator it = s.begin();

    while (it != s.end() && isdigit(*it)) ++it;

    return !s.empty() && it == s.end();
}

/*
Convert synonym type string to enum
*/
bool QueryValidator::GetSynonymType(std::string type, SynonymType &enumType) 
{
	if(type == "assign")			enumType = ASSIGN;
	else if(type == "stmt")			enumType = STMT;
	else if(type == "while")		enumType = WHILE;
	else if(type == "if")			enumType = IF;
	else if(type == "variable")		enumType = VARIABLE;
	else if(type == "constant")		enumType = CONSTANT;
	else if(type == "procedure")	enumType = PROCEDURE;
	else if(type == "prog_line")	enumType = PROG_LINE;
	else if(type == "call")			enumType = CALL;
	else if(type == "BOOLEAN")		enumType = BOOLEAN;
	else return false;

	return true;
}