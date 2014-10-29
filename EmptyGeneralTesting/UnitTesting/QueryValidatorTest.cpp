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
}

void QueryValidatorTest::TokenizeTest()
{
}

void QueryValidatorTest::ClauseValidationTest()
{
	/*QueryValidator qv;
	//QueryData qd;
	Synonym syn;
	syn.value = "a";

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
	CPPUNIT_ASSERT(syn.type == INVALID_SYNONYM_TYPE);*/

	//duplicated declaration
	/*qd.InsertDeclaration(Synonym("a",ASSIGN));
	qd.InsertDeclaration(Synonym("w",WHILE));

	syn.type = INVALID_SYNONYM_TYPE;
	valid = qv.ValidateDeclaration(syn, "assign");
	CPPUNIT_ASSERT(valid == false);
	CPPUNIT_ASSERT(syn.type == INVALID_SYNONYM_TYPE);

	syn.value = "w";
	syn.type = INVALID_SYNONYM_TYPE;
	valid = qv.ValidateDeclaration(syn, "while");
	CPPUNIT_ASSERT(valid == false);
	CPPUNIT_ASSERT(syn.type == INVALID_SYNONYM_TYPE);*/
}

void QueryValidatorTest::ArgumentValidationTest()
{
	QueryValidator qd;

	//Function in test : bool IsExpression(std::string)
	bool matched = qd.IsExpression("\"x\"");
	CPPUNIT_ASSERT(matched == true);
	
	matched = qd.IsExpression("\"xyz\"");
	CPPUNIT_ASSERT(matched == true);

	matched = qd.IsExpression("\"x50\"");
	CPPUNIT_ASSERT(matched == true);

	matched = qd.IsExpression("\"x388x3fg\"");
	CPPUNIT_ASSERT(matched == true);

	matched = qd.IsExpression("\"45\"");
	CPPUNIT_ASSERT(matched == true);

	matched = qd.IsExpression("\"0\"");
	CPPUNIT_ASSERT(matched == true);

	matched = qd.IsExpression("\"25jj\"");
	CPPUNIT_ASSERT(matched == false);

	matched = qd.IsExpression("\"=\"");
	CPPUNIT_ASSERT(matched == false);

	matched = qd.IsExpression("\"ss3=\"");
	CPPUNIT_ASSERT(matched == false);

	matched = qd.IsExpression("\"-58\"");
	CPPUNIT_ASSERT(matched == false);

	matched = qd.IsExpression("\"x+y\"");
	CPPUNIT_ASSERT(matched == true);

	matched = qd.IsExpression("\" x + y \"");
	CPPUNIT_ASSERT(matched == true);

	matched = qd.IsExpression("\" 5 + 7\"");
	CPPUNIT_ASSERT(matched == true);

	matched = qd.IsExpression("\"4+a1\"");
	CPPUNIT_ASSERT(matched == true);

	matched = qd.IsExpression("\" w +2\"");
	CPPUNIT_ASSERT(matched == true);

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