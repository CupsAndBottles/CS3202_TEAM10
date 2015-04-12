#pragma once

#include <cppunit\extensions\HelperMacros.h>

class AffectsTTest : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE(AffectsTTest);

	CPPUNIT_TEST(TestIsAffectsT);
	CPPUNIT_TEST(TestGetStmtsAffectedTBy);
	CPPUNIT_TEST(TestGetStmtsAffectingT);

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void TestIsAffectsT();
	void TestGetStmtsAffectedTBy();
	void TestGetStmtsAffectingT();
};