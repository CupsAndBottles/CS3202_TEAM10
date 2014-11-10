#pragma once

#include <cppunit\extensions\HelperMacros.h>

class QueryEvaluatorToPKBTest : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE(QueryEvaluatorToPKBTest);
	CPPUNIT_TEST(TestSelectAll);
	CPPUNIT_TEST(TestParent);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void TestSelectAll();
	void TestParent();
};

