#include "QueryProcessor.h"
#include "QueryData.h"
#include <string>


QueryProcessor::QueryProcessor(void)
{
}


QueryProcessor::~QueryProcessor(void)
{
}

std::string QueryProcessor::ProcessQuery(std::string query) {
	QueryData queryData;
	std::string result = "";
	//QueryEvaluator QE;
	//QueryValidator QV;

	/*
	if(QV.ValidateQuery(query, queryData)) {

		//call queryeval
		result = QE.EvaluateQuery(queryData);

		//format result

		return result;
	}
	*/

	return "Invalid query.";
}








//receive whole query string
//pass query string to validator
//if valid, pass query to evaluator with declaration struct and condition struct as arguments
//	receive result as string (list of integers/string)
//	format result and return result string (if select boolean, then convert result to true and false)

//if invalid, return "Invalid"