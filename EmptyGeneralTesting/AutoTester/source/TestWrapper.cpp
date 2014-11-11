#include "TestWrapper.h"

const string TESTFILE_DIRECTORY = "SIMPLESource/";

// implementation code of WrapperFactory - do NOT modify the next 5 lines
AbstractWrapper* WrapperFactory::wrapper = 0;
AbstractWrapper* WrapperFactory::createWrapper() {
  if (wrapper == 0) wrapper = new TestWrapper;
  return wrapper;
}
// Do not modify the following line
volatile bool TestWrapper::GlobalStop = false;

// a default constructor
TestWrapper::TestWrapper() {
  // create any objects here as instance variables of this class
  // as well as any initialization required for your spa program
}

// method for parsing the SIMPLE source
void TestWrapper::parse(string filename) {
	// call your parser to do the parsing
	// ...rest of your code...
	ifstream sourceFile(string(TESTFILE_DIRECTORY).append(filename));
	stringstream buffer;
	buffer << sourceFile.rdbuf();
	sourceFile.close();
	Parser::Parse(buffer.str());

}

// method to evaluating a query
void TestWrapper::evaluate(string query, list<std::string>& results){
	// call your evaluator to evaluate the query here
	// ...code to evaluate query...
	
	// store the answers to the query in the results list (it is initially empty)
	// each result must be a string.

	results = QueryProcessor::ProcessQuery(query);
}
