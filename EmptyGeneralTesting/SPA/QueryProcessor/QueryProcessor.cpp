#include "QueryProcessor.h"
#include "QueryData.h"
#include "QueryEvaluator.h"
#include "QueryValidator.h"

#include <string>
#include <list>
#include <iostream>

QueryProcessor::QueryProcessor(void) {}

std::list<std::string> QueryProcessor::ProcessQuery(std::string query) {
	QueryData queryData;
	std::list<std::string> result;
	QueryEvaluator QE;
	QueryValidator QV;

	queryData.ClearData();

	if(QV.ValidateQuery(query, queryData)) {
		QE.EvaluateQuery(queryData, result);

		return result;
	}
	
	std::cout << "\nInvalid Query.\n";

	return result;
}