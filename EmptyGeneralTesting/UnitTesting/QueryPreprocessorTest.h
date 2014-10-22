#pragma once

#include "cppunit/extensions/HelperMacros.h"

class QueryPreprocessorTest : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE(QueryPreprocessorTest);
	CPPUNIT_TEST(TestQuerySuchthat);
	CPPUNIT_TEST(TestQueryPattern);
	CPPUNIT_TEST(TestComplexQuery);
	CPPUNIT_TEST_SUITE_END();
public:
	void setUp();
	void tearDown();

	void TestQuerySuchthat();
	void TestQueryPattern();
	void TestComplexQuery();
};