#pragma once

#include "cppunit\extensions\HelperMacros.h"

class UsesTest : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE(UsesTest);
	CPPUNIT_TEST(TestSingleStmt);
	CPPUNIT_TEST(TestMultipleStmts);
	CPPUNIT_TEST(TestMultipleStmtsUsingSingleVar);
	CPPUNIT_TEST(TestSingleStmtUsingMultipleVars);
	CPPUNIT_TEST(TestUses);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void TestSingleStmt();
	void TestMultipleStmts();
	void TestMultipleStmtsUsingSingleVar();
	void TestSingleStmtUsingMultipleVars();
	void TestUses();

	UsesTest();
};

