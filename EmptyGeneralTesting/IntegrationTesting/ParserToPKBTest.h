#define ParserToPKBTest_h

#include <cppunit\extensions\HelperMacros.h>

class ParserToPKBTest : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE(ParserToPKBTest);

	CPPUNIT_TEST(testNothing);
	CPPUNIT_TEST(testOneVarTable);
	CPPUNIT_TEST(testOneModifiesUses);
	CPPUNIT_TEST(testOneParentsFollows);
	// insert methods in here
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void testNothing();
	void testOneVarTable();
	void testOneModifiesUses();
	void testOneParentsFollows();

	// add other methods to test here

};