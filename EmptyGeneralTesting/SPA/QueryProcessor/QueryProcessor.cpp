#include "QueryProcessor.h"
#include "QueryData.h"
#include "QueryEvaluator.h"
#include "QueryPreProcessor.h"

#include <string>
#include <list>
#include <iostream>

QueryProcessor::QueryProcessor(void) {}

std::list<std::string> QueryProcessor::ProcessQuery(std::string query) {
	QueryData queryData;
	std::list<std::string> result;
	QueryEvaluator QE;
	QueryPreProcessor QV;

	queryData.ClearData();
	//cout << "\nHERE\n";
	if(QV.ValidateQuery(query, queryData)) {
		//cout << "\nInside validate Query.\n";
		QE.EvaluateQuery(queryData, result);
		//cout << "\nafter evaluate Query.\n";
		return result;
	}
	
	//cout << "\nLOL Invalid Query.\n";

	return result;
}