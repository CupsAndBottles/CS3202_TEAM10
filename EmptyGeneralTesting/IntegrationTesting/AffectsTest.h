#pragma once

#define AffectsTest_h

#include <cppunit\extensions\HelperMacros.h>

class AffectsTest : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE(AffectsTest);

	CPPUNIT_TEST(TestIsAffects);
	CPPUNIT_TEST(TestGetStmtsAffectedBy);
	CPPUNIT_TEST(TestGetStmtsAffecting);

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void TestIsAffects();
	void TestGetStmtsAffectedBy();
	void TestGetStmtsAffecting();

private:
	void ClearAllData();

	// misc methods to create stubs from pre-determined code
	void MimicCodeWithAssignOnly();
	void MimicCodeWithAssignWhile();
	void MimicCodeWithAssignIf();
};

