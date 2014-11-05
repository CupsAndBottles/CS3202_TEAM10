#include "QueryProcessor.h"
#include "QueryData.h"
#include <string>


QueryProcessor::QueryProcessor(void)
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