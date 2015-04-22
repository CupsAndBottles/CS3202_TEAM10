#pragma once

#include <cppunit\extensions\HelperMacros.h>

class ParserToPKBTest2 : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE(ParserToPKBTest2);

	CPPUNIT_TEST(TestModifies);
	CPPUNIT_TEST(TestUses);
	CPPUNIT_TEST(TestModifiesForProcs);
	CPPUNIT_TEST(TestUsesForProcs);
	CPPUNIT_TEST(TestAffects);
	CPPUNIT_TEST(TestAffectsT);

	// insert methods in here
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	ParserToPKBTest2();

	void TestModifies();
	void TestUses();
	void TestModifiesForProcs();
	void TestUsesForProcs();
	void TestAffects();
	void TestAffectsT();

	// add other methods to test here

};

