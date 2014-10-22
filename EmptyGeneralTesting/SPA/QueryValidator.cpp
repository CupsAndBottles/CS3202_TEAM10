#include "QueryValidator.h"
#include <sstream>
#include <algorithm>
#include <iostream>

const std::string QueryValidator::de[] = {"procedure", "stmt", "stmtLst", "assign", "call", "while", "if", "variable", "prog_line", "constant"};
const std::string QueryValidator::rel[] = { "Modifies", "Uses", "Calls", "Calls*", "Parent", "Parent*", "Follows", "Follows*", "Next", "Next*", "Affects", "Affects*" };
 
QueryValidator::QueryValidator(void)
{
	DesignEntity.assign(de, de + sizeof(de));
	Relationship.assign(rel, rel + sizeof(rel));
}

bool QueryValidator::ValidateQuery(std::string query, QueryData queryData)
{
	std::vector<std::string> tokenList;
	std::string token;
	std::string delim = " ,<>()";

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
			queryData.InsertDeclaration(type,token);

			if(++it == tokenList.end())	return false;
			token = *it;
		}

		if(++it == tokenList.end())	return false;
		token = *it;
	}
	//check declaration empty?


	//validate select
	if(IsSelect(token))
	{
		if(++it == tokenList.end())	return false;
		token = *it;

		if(IsOpenBracket(token)) //<
		{
			if(++it == tokenList.end())	return false;
			token = *it;

			while(!IsCloseBracket(token)) //>
			{
				std::string type;
				if(!ValidateSelect(token,type))	return false;
				
				queryData.InsertSelect(type,token);

				if(++it == tokenList.end())	return false;
				token = *it;
			}

			if(++it == tokenList.end())	return false;
			token = *it;
		}

		else 
		{
			std::string type;
			if(!ValidateSelect(token,type))	return false;
			
			queryData.InsertSelect(type, token);
		}
	}

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

			if(IsRelationship(token)) //uses, modifies, parents, etc.
			{
				std::string relationship = token;			

				if(++it == tokenList.end())	return false;	//get arg1
				token = *it;
				std::string arg1 = token;

				if(++it == tokenList.end())	return false;	//get arg2
				token = *it;
				std::string arg2 = token;

				//if(!ValidateRelationship(token,arg1,arg2))	return false;
				queryData.InsertSuchThat(relationship,arg1,arg2);
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
				if(++it == tokenList.end())	return false;	//get type
				token = *it;
				std::string type = token;

				if(++it == tokenList.end())	return false;	//get arg1
				token = *it;
				std::string arg1 = token;

				if(++it == tokenList.end())	return false;	//get arg2
				token = *it;
				std::string arg2 = token;

				std::string arg3 = "";

				if(!QueryData::IsSynonymExist(type, "if"))		//if is pattern if(var,_,_), get arg3
				{
					if(++it == tokenList.end())	return false;	//get arg3
					token = *it;
					std::string arg3 = token;
				}

				if(!ValidatePattern(type, arg1, arg2, arg3))	return false;

				queryData.InsertPattern(type,arg1,arg2);
				
				if(++it == tokenList.end())
				{
					endOfQuery = true;
					break;	//if no more token = end of query
				}
				token = *it;
		}

		if(endOfQuery)	return true;

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

		if(endOfQuery)	return true;
	}

	return true;
}


//all synonym must be declared



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

bool QueryValidator::ValidateSelect(std::string synonym, std::string &type)
{
	if(QueryData::IsSynonymExist(synonym, type))
		return true;

	return false;
}

/*
pattern a( synonym | _ | "string" , _ | "string" | _"string"_ )
pattern if( synonym | _ | "string" , _ )
pattern while( synonym | _ | "string" , _ )
*/
bool QueryValidator::ValidatePattern(std::string synonym, std::string arg1, std::string arg2, std::string arg3)
{
	if(QueryData::IsSynonymExist(synonym,"assign"))
	{
		if(arg1 == "_" || QueryData::IsSynonymExist(arg1, "variable") || IsString(arg1)) {}

		else return false;

		if(arg2 == "_" || IsString(arg2) || arg2.substr(0,2) == "_\"" && arg2.substr(arg2.length()-2,2) == "\"_") {}

		else return false;

		return true;
	}

	else if(QueryData::IsSynonymExist(synonym,"if"))
	{
		if(arg1 == "_" || QueryData::IsSynonymExist(arg1, "variable") || IsString(arg1)) {}

		else return false;

		if(arg2 == "_" && arg3 == "_") {}

		else return false;

		return true;
	}

	else if(QueryData::IsSynonymExist(synonym,"while"))
	{		
		if(arg1 == "_" || QueryData::IsSynonymExist(arg1, "variable") || IsString(arg1)) {}

		else return false;

		if(arg2 == "_") {}

		else return false;

		return true;
	}

	else return false;
}

/*

*/
bool QueryValidator::ValidateWith(std::string arg1, std::string arg2)
{
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
	
	else return false;
}
	

bool QueryValidator::IsInteger(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

bool QueryValidator::IsString(const std::string& s)
{
	if(s.front() == char("\"") && s.back() == char("\""))
		return true;

	return false;
}

bool QueryValidator::IsDeclaration(std::string str)
{
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

bool QueryValidator::IsRelationship(std::string str)
{
	if (std::find(Relationship.begin(), Relationship.end(), str) != Relationship.end())
		return true;

	return false;
}