#include "QueryValidatorTest.h"
#include <cppunit/config/SourcePrefix.h>
#include "QueryProcessor\QueryValidator.h"

using namespace std;

void QueryValidatorTest::setUp() {};
void QueryValidatorTest::tearDown() {};

CPPUNIT_TEST_SUITE_REGISTRATION(QueryValidatorTest);

QueryValidatorTest::QueryValidatorTest(void) {}

void QueryValidatorTest::ActualValidationTest()
{
	QueryValidator qv;
	QueryData qd;

	std::string query = "assign a;while w;Select a";
	//std::string query = "assign a;while w;Select a such that Parent(w,a)";
	qd.ClearData();

	bool valid = qv.ValidateQuery(query, qd);
	CPPUNIT_ASSERT(valid == true);
	
	int size = qd.GetDeclarations().size();
	CPPUNIT_ASSERT(size == 2);

	CPPUNIT_ASSERT(qd.GetDeclarations().at(0).synonym.value == "a");
	CPPUNIT_ASSERT(qd.GetDeclarations().at(0).synonym.type == ASSIGN);
	CPPUNIT_ASSERT(qd.GetDeclarations().at(1).synonym.value == "W");
	CPPUNIT_ASSERT(qd.GetDeclarations().at(1).synonym.type == WHILE);

	size = qd.GetSelects().size();
	CPPUNIT_ASSERT(size == 1);

	CPPUNIT_ASSERT(qd.GetSelects().at(0).synonym.value == "a");
	CPPUNIT_ASSERT(qd.GetSelects().at(0).synonym.type == ASSIGN);
	/*
	size = qd.GetSuchThats().size();
	CPPUNIT_ASSERT(size == 1);

	CPPUNIT_ASSERT(qd.GetSuchThats().at(0).relationship == PARENT);
	CPPUNIT_ASSERT(qd.GetSuchThats().at(0).arg1.value == "w");
	CPPUNIT_ASSERT(qd.GetSuchThats().at(0).arg1.type == SYNONYM);
	CPPUNIT_ASSERT(qd.GetSuchThats().at(0).arg1.syn.value == "w");
	CPPUNIT_ASSERT(qd.GetSuchThats().at(0).arg1.syn.type == WHILE);
	CPPUNIT_ASSERT(qd.GetSuchThats().at(0).arg2.value == "a");
	CPPUNIT_ASSERT(qd.GetSuchThats().at(0).arg2.type == SYNONYM);
	CPPUNIT_ASSERT(qd.GetSuchThats().at(0).arg2.syn.value == "a");
	CPPUNIT_ASSERT(qd.GetSuchThats().at(0).arg2.syn.type == ASSIGN);
	
	size = qd.GetPatterns().size();
	CPPUNIT_ASSERT(size == 0);*/


	/*
	query = "assign a ; Select a such that Modifies(a,5) pattern a(_ , _\" x+ y\" _)";
	qd.ClearData();

	valid = qv.ValidateQuery(query, qd);
	CPPUNIT_ASSERT(valid == true);
	
	size = qd.GetDeclarations().size();
	CPPUNIT_ASSERT(size == 1);

	CPPUNIT_ASSERT(qd.GetDeclarations().at(0).synonym.value == "a");
	CPPUNIT_ASSERT(qd.GetDeclarations().at(0).synonym.type == ASSIGN);

	size = qd.GetSelects().size();
	CPPUNIT_ASSERT(size == 1);

	CPPUNIT_ASSERT(qd.GetSelects().at(0).synonym.value == "a");
	CPPUNIT_ASSERT(qd.GetSelects().at(0).synonym.type == ASSIGN);

	size = qd.GetSuchThats().size();
	CPPUNIT_ASSERT(size == 1);

	CPPUNIT_ASSERT(qd.GetSuchThats().at(0).relationship == MODIFIES);
	CPPUNIT_ASSERT(qd.GetSuchThats().at(0).arg1.value == "a");
	CPPUNIT_ASSERT(qd.GetSuchThats().at(0).arg1.type == SYNONYM);
	CPPUNIT_ASSERT(qd.GetSuchThats().at(0).arg1.syn.value == "a");
	CPPUNIT_ASSERT(qd.GetSuchThats().at(0).arg1.syn.type == ASSIGN);
	CPPUNIT_ASSERT(qd.GetSuchThats().at(0).arg2.value == "5");
	CPPUNIT_ASSERT(qd.GetSuchThats().at(0).arg2.type == INTEGER);
	CPPUNIT_ASSERT(qd.GetSuchThats().at(0).arg2.syn.value == "");
	CPPUNIT_ASSERT(qd.GetSuchThats().at(0).arg2.syn.type == INVALID_SYNONYM_TYPE);
	
	size = qd.GetPatterns().size();
	CPPUNIT_ASSERT(size == 1);

	CPPUNIT_ASSERT(qd.GetPatterns().at(0).synonym.value == "a");
	CPPUNIT_ASSERT(qd.GetPatterns().at(0).synonym.type == ASSIGN);
	CPPUNIT_ASSERT(qd.GetPatterns().at(0).arg1.value == "_");
	CPPUNIT_ASSERT(qd.GetPatterns().at(0).arg1.type == UNDERSCORE);
	CPPUNIT_ASSERT(qd.GetPatterns().at(0).arg1.syn.value == "");
	CPPUNIT_ASSERT(qd.GetPatterns().at(0).arg1.syn.type == INVALID_SYNONYM_TYPE);
	CPPUNIT_ASSERT(qd.GetPatterns().at(0).arg2.value == "_\" x+ y\" _");
	CPPUNIT_ASSERT(qd.GetPatterns().at(0).arg2.type == EXPRESSION);
	CPPUNIT_ASSERT(qd.GetPatterns().at(0).arg2.syn.value == "");
	CPPUNIT_ASSERT(qd.GetPatterns().at(0).arg2.syn.type == INVALID_SYNONYM_TYPE);*/
}

void QueryValidatorTest::TokenizeTest()
{
	QueryValidator qv;
	std::vector<std::string> tokenList;
	std::string query = "assign a;while w;Select a such that Parent(w,a)";

	//tokenize query
	qv.Tokenize(query,tokenList);

	int size = tokenList.size();

	CPPUNIT_ASSERT(size == 13);
	CPPUNIT_ASSERT(tokenList.at(0) == "assign");
	CPPUNIT_ASSERT(tokenList.at(1) == "a");
	CPPUNIT_ASSERT(tokenList.at(2) == ";");
	CPPUNIT_ASSERT(tokenList.at(3) == "while");
	CPPUNIT_ASSERT(tokenList.at(4) == "w");
	CPPUNIT_ASSERT(tokenList.at(5) == ";");
	CPPUNIT_ASSERT(tokenList.at(6) == "Select");
	CPPUNIT_ASSERT(tokenList.at(7) == "a");
	CPPUNIT_ASSERT(tokenList.at(8) == "such");
	CPPUNIT_ASSERT(tokenList.at(9) == "that");
	CPPUNIT_ASSERT(tokenList.at(10) == "Parent");
	CPPUNIT_ASSERT(tokenList.at(11) == "w");
	CPPUNIT_ASSERT(tokenList.at(12) == "a");


	tokenList.clear();
	query = "assign  a  ;    Select a pattern a ( \" x \" , _ \" y + 5 \" _  )";

	qv.Tokenize(query,tokenList);

	size = tokenList.size();
	cout << "\n" << size << "\n";
	for(std::vector<std::string>::iterator it = tokenList.begin(); it!=tokenList.end(); ++it)
		cout << *it << "\n";

	CPPUNIT_ASSERT(size == 9);
	CPPUNIT_ASSERT(tokenList.at(0) == "assign");
	CPPUNIT_ASSERT(tokenList.at(1) == "a");
	CPPUNIT_ASSERT(tokenList.at(2) == ";");
	CPPUNIT_ASSERT(tokenList.at(3) == "Select");
	CPPUNIT_ASSERT(tokenList.at(4) == "a");
	CPPUNIT_ASSERT(tokenList.at(5) == "pattern");
	CPPUNIT_ASSERT(tokenList.at(6) == "a");
	CPPUNIT_ASSERT(tokenList.at(7) == "\" x \"");
	CPPUNIT_ASSERT(tokenList.at(8) == "_ \" y + 5 \" _");

	
	tokenList.clear();
	query = "assign a;while w;Select a such that Parent(w,a) pattern a(_,_\"y+5\"_)";

	//tokenize query
	qv.Tokenize(query,tokenList);

	size = tokenList.size();
	CPPUNIT_ASSERT(size == 17);
	CPPUNIT_ASSERT(tokenList.at(0) == "assign");
	CPPUNIT_ASSERT(tokenList.at(1) == "a");
	CPPUNIT_ASSERT(tokenList.at(2) == ";");
	CPPUNIT_ASSERT(tokenList.at(3) == "while");
	CPPUNIT_ASSERT(tokenList.at(4) == "w");
	CPPUNIT_ASSERT(tokenList.at(5) == ";");
	CPPUNIT_ASSERT(tokenList.at(6) == "Select");
	CPPUNIT_ASSERT(tokenList.at(7) == "a");
	CPPUNIT_ASSERT(tokenList.at(8) == "such");
	CPPUNIT_ASSERT(tokenList.at(9) == "that");
	CPPUNIT_ASSERT(tokenList.at(10) == "Parent");
	CPPUNIT_ASSERT(tokenList.at(11) == "w");
	CPPUNIT_ASSERT(tokenList.at(12) == "a");
	CPPUNIT_ASSERT(tokenList.at(13) == "pattern");
	CPPUNIT_ASSERT(tokenList.at(14) == "a");
	CPPUNIT_ASSERT(tokenList.at(15) == "_");
	CPPUNIT_ASSERT(tokenList.at(16) == "_\"y+5\"_");


	tokenList.clear();
	query = "assign a  ; while w , w1 ;  variable v  ;  Select w such that Modifies( 3 , w1 ) pattern a( \"  y  \"  , _ \" y + 5  \" _)";

	qv.Tokenize(query,tokenList);

	size = tokenList.size();

	CPPUNIT_ASSERT(size == 21);
	CPPUNIT_ASSERT(tokenList.at(0) == "assign");
	CPPUNIT_ASSERT(tokenList.at(1) == "a");
	CPPUNIT_ASSERT(tokenList.at(2) == ";");
	CPPUNIT_ASSERT(tokenList.at(3) == "while");
	CPPUNIT_ASSERT(tokenList.at(4) == "w");
	CPPUNIT_ASSERT(tokenList.at(5) == "w1");
	CPPUNIT_ASSERT(tokenList.at(6) == ";");
	CPPUNIT_ASSERT(tokenList.at(7) == "variable");
	CPPUNIT_ASSERT(tokenList.at(8) == "v");
	CPPUNIT_ASSERT(tokenList.at(9) == ";");
	CPPUNIT_ASSERT(tokenList.at(10) == "Select");
	CPPUNIT_ASSERT(tokenList.at(11) == "w");
	CPPUNIT_ASSERT(tokenList.at(12) == "such");
	CPPUNIT_ASSERT(tokenList.at(13) == "that");
	CPPUNIT_ASSERT(tokenList.at(14) == "Modifies");
	CPPUNIT_ASSERT(tokenList.at(15) == "3");
	CPPUNIT_ASSERT(tokenList.at(16) == "w1");
	CPPUNIT_ASSERT(tokenList.at(17) == "pattern");
	CPPUNIT_ASSERT(tokenList.at(18) == "a");
	CPPUNIT_ASSERT(tokenList.at(19) == "\"  y  \"");
	CPPUNIT_ASSERT(tokenList.at(20) == "_ \" y + 5  \" _");
}

void QueryValidatorTest::ClauseValidationTest()
{
	QueryValidator qv;
	QueryData qd;
	Synonym syn;
	syn.value = "a";

	qd.ClearData();

	bool valid = qv.ValidateDeclaration(syn, "assign");
	CPPUNIT_ASSERT(valid == true);
	CPPUNIT_ASSERT(syn.type == ASSIGN);

	syn.type = INVALID_SYNONYM_TYPE;
	valid = qv.ValidateDeclaration(syn, "stmt");
	CPPUNIT_ASSERT(valid == true);
	CPPUNIT_ASSERT(syn.type == STMT);

	syn.type = INVALID_SYNONYM_TYPE;
	valid = qv.ValidateDeclaration(syn, "while");
	CPPUNIT_ASSERT(valid == true);
	CPPUNIT_ASSERT(syn.type == WHILE);

	syn.type = INVALID_SYNONYM_TYPE;
	valid = qv.ValidateDeclaration(syn, "variable");
	CPPUNIT_ASSERT(valid == true);
	CPPUNIT_ASSERT(syn.type == VARIABLE);

	syn.type = INVALID_SYNONYM_TYPE;
	valid = qv.ValidateDeclaration(syn, "constant");
	CPPUNIT_ASSERT(valid == true);
	CPPUNIT_ASSERT(syn.type == CONSTANT);

	syn.type = INVALID_SYNONYM_TYPE;
	valid = qv.ValidateDeclaration(syn, "prog_line");
	CPPUNIT_ASSERT(valid == true);
	CPPUNIT_ASSERT(syn.type == PROG_LINE);

	syn.type = INVALID_SYNONYM_TYPE;
	valid = qv.ValidateDeclaration(syn, "LOL");
	CPPUNIT_ASSERT(valid == false);
	CPPUNIT_ASSERT(syn.type == INVALID_SYNONYM_TYPE);

	//duplicated declaration
	qd.InsertDeclaration(Synonym("a",ASSIGN));
	qd.InsertDeclaration(Synonym("w",WHILE));

	syn.type = INVALID_SYNONYM_TYPE;
	valid = qv.ValidateDeclaration(syn, "assign");
	CPPUNIT_ASSERT(valid == false);
	CPPUNIT_ASSERT(syn.type == INVALID_SYNONYM_TYPE);

	syn.value = "w";
	syn.type = INVALID_SYNONYM_TYPE;
	valid = qv.ValidateDeclaration(syn, "while");
	CPPUNIT_ASSERT(valid == false);
	CPPUNIT_ASSERT(syn.type == INVALID_SYNONYM_TYPE);
}

void QueryValidatorTest::ArgumentValidationTest()
{
	QueryValidator qd;

	//Function in test : bool IsExpression(std::string)
	bool matched = qd.IsExpression("\"x\"");
	CPPUNIT_ASSERT(matched == false);
	
	matched = qd.IsExpression("\"xyz\"");
	CPPUNIT_ASSERT(matched == false);

	matched = qd.IsExpression("\"x50\"");
	CPPUNIT_ASSERT(matched == false);

	matched = qd.IsExpression("\"x388x3fg\"");
	CPPUNIT_ASSERT(matched == false);

	matched = qd.IsExpression("\"45\"");
	CPPUNIT_ASSERT(matched == false);

	matched = qd.IsExpression("\"0\"");
	CPPUNIT_ASSERT(matched == false);

	matched = qd.IsExpression("\"25jj\"");
	CPPUNIT_ASSERT(matched == false);

	matched = qd.IsExpression("\"=\"");
	CPPUNIT_ASSERT(matched == false);

	matched = qd.IsExpression("\"ss3=\"");
	CPPUNIT_ASSERT(matched == false);

	matched = qd.IsExpression("\"-58\"");
	CPPUNIT_ASSERT(matched == false);

	matched = qd.IsExpression("\"x+y\"");
	CPPUNIT_ASSERT(matched == false);

	matched = qd.IsExpression("\" x + y \"");
	CPPUNIT_ASSERT(matched == false);

	matched = qd.IsExpression("\" 5 + 7\"");
	CPPUNIT_ASSERT(matched == false);

	matched = qd.IsExpression("\"4+a1\"");
	CPPUNIT_ASSERT(matched == false);

	matched = qd.IsExpression("\" w +2\"");
	CPPUNIT_ASSERT(matched == false);

	matched = qd.IsExpression("_");
	CPPUNIT_ASSERT(matched == false);

	matched = qd.IsExpression("_\"\"_");		//_""_
	CPPUNIT_ASSERT(matched == false);

	matched = qd.IsExpression("_\" \"_");		//_" "_
	CPPUNIT_ASSERT(matched == false);

	matched = qd.IsExpression("_\"  _");		//_"  _
	CPPUNIT_ASSERT(matched == false);
	
	matched = qd.IsExpression("__");			//__
	CPPUNIT_ASSERT(matched == false);

	matched = qd.IsExpression("_\"x\"_");
	CPPUNIT_ASSERT(matched == true);

	matched = qd.IsExpression("_\"50\"_");
	CPPUNIT_ASSERT(matched == true);

	matched = qd.IsExpression("_\"a50\"_");
	CPPUNIT_ASSERT(matched == true);

	matched = qd.IsExpression("_\"x+y\"_");
	CPPUNIT_ASSERT(matched == true);

	matched = qd.IsExpression("_ \" x + y \" _");
	CPPUNIT_ASSERT(matched == true);

	matched = qd.IsExpression("_\"x*y\"_");
	CPPUNIT_ASSERT(matched == false);

	matched = qd.IsExpression("_\"x+y\"");
	CPPUNIT_ASSERT(matched == false);

	matched = qd.IsExpression("\"x+y\"_");
	CPPUNIT_ASSERT(matched == false);

	matched = qd.IsExpression("_\"=,-9,v=0,5\"");
	CPPUNIT_ASSERT(matched == false);

	//Function in test : IsIdent(std::string)
	matched = qd.IsIdent("\"x\"");
	CPPUNIT_ASSERT(matched == true);
	
	matched = qd.IsIdent("\"xyz\"");
	CPPUNIT_ASSERT(matched == true);

	matched = qd.IsIdent("\"x50\"");
	CPPUNIT_ASSERT(matched == true);

	matched = qd.IsIdent("\"x388x3fg\"");
	CPPUNIT_ASSERT(matched == true);

	matched = qd.IsIdent("\"45\"");
	CPPUNIT_ASSERT(matched == false);

	matched = qd.IsIdent("\"25jj\"");
	CPPUNIT_ASSERT(matched == false);

	matched = qd.IsIdent("\"=\"");
	CPPUNIT_ASSERT(matched == false);

	matched = qd.IsIdent("\"ss3=\"");
	CPPUNIT_ASSERT(matched == false);
	
	
	//Function in test : bool IsName(std::string)
	matched = qd.IsName("x");
	CPPUNIT_ASSERT(matched == true);

	matched = qd.IsName("xyz");
	CPPUNIT_ASSERT(matched == true);

	matched = qd.IsName("x50");
	CPPUNIT_ASSERT(matched == true);

	matched = qd.IsName("x388x3fg");
	CPPUNIT_ASSERT(matched == true);

	matched = qd.IsName("45");
	CPPUNIT_ASSERT(matched == false);

	matched = qd.IsName("25jj");
	CPPUNIT_ASSERT(matched == false);

	matched = qd.IsName("=");
	CPPUNIT_ASSERT(matched == false);

	matched = qd.IsName("ss3=");
	CPPUNIT_ASSERT(matched == false);


	//Function in test : bool IsInteger(const std::string&);

	matched = qd.IsInteger("5");
	CPPUNIT_ASSERT(matched == true);

	matched = qd.IsInteger("0");
	CPPUNIT_ASSERT(matched == true);

	matched = qd.IsInteger("25jj");
	CPPUNIT_ASSERT(matched == false);

	matched = qd.IsInteger("50x");
	CPPUNIT_ASSERT(matched == false);

	matched = qd.IsInteger("x");
	CPPUNIT_ASSERT(matched == false);

	matched = qd.IsInteger("=");
	CPPUNIT_ASSERT(matched == false);

	matched = qd.IsInteger("-24");
	CPPUNIT_ASSERT(matched == false);

	matched = qd.IsInteger("0.4");
	CPPUNIT_ASSERT(matched == false);
}

void QueryValidatorTest::StringMatchingFunctionTest()
{
	QueryValidator qv;

	//Function in test : bool IsDeclaration(std::string);
	
	bool matched = qv.IsDeclaration("stmt");
	CPPUNIT_ASSERT(matched == true);

	matched = qv.IsDeclaration("assign");
	CPPUNIT_ASSERT(matched == true);

	matched = qv.IsDeclaration("while");
	CPPUNIT_ASSERT(matched == true);

	matched = qv.IsDeclaration("variable");
	CPPUNIT_ASSERT(matched == true);

	matched = qv.IsDeclaration("prog_line");
	CPPUNIT_ASSERT(matched == true);

	matched = qv.IsDeclaration("constant");
	CPPUNIT_ASSERT(matched == true);

	matched = qv.IsDeclaration("lol");
	CPPUNIT_ASSERT(matched == false);

	
	//Function in test : bool IsDeclaration(std::string);
	
	matched = qv.IsRelationship("Modifies");
	CPPUNIT_ASSERT(matched == true);

	matched = qv.IsRelationship("Uses");
	CPPUNIT_ASSERT(matched == true);

	matched = qv.IsRelationship("Parent");
	CPPUNIT_ASSERT(matched == true);

	matched = qv.IsRelationship("Parent*");
	CPPUNIT_ASSERT(matched == true);

	matched = qv.IsRelationship("Follows");
	CPPUNIT_ASSERT(matched == true);

	matched = qv.IsRelationship("Follows*");
	CPPUNIT_ASSERT(matched == true);

	matched = qv.IsDeclaration("lol");
	CPPUNIT_ASSERT(matched == false);


	//Function in test : bool IsSelect(std::string);
	
	matched = qv.IsSelect("Select");
	CPPUNIT_ASSERT(matched == true);

	matched = qv.IsSelect("lol");
	CPPUNIT_ASSERT(matched == false);


	//Function in test : bool IsSemiColon(std::string);
	
	matched = qv.IsSemiColon(";");
	CPPUNIT_ASSERT(matched == true);

	matched = qv.IsSemiColon("lol");
	CPPUNIT_ASSERT(matched == false);


	//Function in test : bool IsPattern(std::string);
	
	matched = qv.IsPattern("pattern");
	CPPUNIT_ASSERT(matched == true);

	matched = qv.IsPattern("lol");
	CPPUNIT_ASSERT(matched == false);


	//Function in test : bool IsSuchThat(std::string);
	
	matched = qv.IsSuchThat("such");
	CPPUNIT_ASSERT(matched == true);

	matched = qv.IsSuchThat("lol");
	CPPUNIT_ASSERT(matched == false);

	
	//Function in test : bool IsUnderscore(std::string);
	
	matched = qv.IsUnderscore("_");
	CPPUNIT_ASSERT(matched == true);

	matched = qv.IsUnderscore("lol");
	CPPUNIT_ASSERT(matched == false);
}

void QueryValidatorTest::HelperFunctionTest()
{
	QueryValidator qv;
	
	//Function in test : bool GetEnumRelationshipType(std::string, RelationshipType&);
	
	RelationshipType rt = INVALID_RELATIONSHIP_TYPE;
	bool exist = qv.GetEnumRelationshipType("Modifies", rt);
	CPPUNIT_ASSERT(rt == MODIFIES);
	CPPUNIT_ASSERT(exist == true);

	rt = INVALID_RELATIONSHIP_TYPE;
	exist = qv.GetEnumRelationshipType("Uses", rt);
	CPPUNIT_ASSERT(rt == USES);
	CPPUNIT_ASSERT(exist == true);

	rt = INVALID_RELATIONSHIP_TYPE;
	exist = qv.GetEnumRelationshipType("Parent", rt);
	CPPUNIT_ASSERT(rt == PARENT);
	CPPUNIT_ASSERT(exist == true);

	rt = INVALID_RELATIONSHIP_TYPE;
	exist = qv.GetEnumRelationshipType("Parent*", rt);
	CPPUNIT_ASSERT(rt == PARENTT);
	CPPUNIT_ASSERT(exist == true);

	rt = INVALID_RELATIONSHIP_TYPE;
	exist = qv.GetEnumRelationshipType("Follows", rt);
	CPPUNIT_ASSERT(rt == FOLLOWS);
	CPPUNIT_ASSERT(exist == true);

	rt = INVALID_RELATIONSHIP_TYPE;
	exist = qv.GetEnumRelationshipType("Follows*", rt);
	CPPUNIT_ASSERT(rt == FOLLOWST);
	CPPUNIT_ASSERT(exist == true);

	//Invalid
	rt = INVALID_RELATIONSHIP_TYPE;
	exist = qv.GetEnumRelationshipType("LOL", rt);
	CPPUNIT_ASSERT(rt == INVALID_RELATIONSHIP_TYPE);
	CPPUNIT_ASSERT(exist == false);


	//Function in test : bool GetEnumSynonymType(std::string, SynonymType&)
	
	SynonymType st = INVALID_SYNONYM_TYPE;
	exist = qv.GetEnumSynonymType("assign", st);
	CPPUNIT_ASSERT(st == ASSIGN);
	CPPUNIT_ASSERT(exist == true);

	st = INVALID_SYNONYM_TYPE;
	exist = qv.GetEnumSynonymType("stmt", st);
	CPPUNIT_ASSERT(st == STMT);
	CPPUNIT_ASSERT(exist == true);

	st = INVALID_SYNONYM_TYPE;
	exist = qv.GetEnumSynonymType("while", st);
	CPPUNIT_ASSERT(st == WHILE);
	CPPUNIT_ASSERT(exist == true);

	st = INVALID_SYNONYM_TYPE;
	exist = qv.GetEnumSynonymType("variable", st);
	CPPUNIT_ASSERT(st == VARIABLE);
	CPPUNIT_ASSERT(exist == true);

	st = INVALID_SYNONYM_TYPE;
	exist = qv.GetEnumSynonymType("prog_line", st);
	CPPUNIT_ASSERT(st == PROG_LINE);
	CPPUNIT_ASSERT(exist == true);

	st = INVALID_SYNONYM_TYPE;
	exist = qv.GetEnumSynonymType("constant", st);
	CPPUNIT_ASSERT(st == CONSTANT);
	CPPUNIT_ASSERT(exist == true);

	//Invalid
	st = INVALID_SYNONYM_TYPE;
	exist = qv.GetEnumSynonymType("lol", st);
	CPPUNIT_ASSERT(st == INVALID_SYNONYM_TYPE);
	CPPUNIT_ASSERT(exist == false);
}