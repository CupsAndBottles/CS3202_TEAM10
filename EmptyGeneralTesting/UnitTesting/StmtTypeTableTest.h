#pragma once

#include <cppunit\extensions\HelperMacros.h>

class StmtTypeTableTest : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE(StmtTypeTableTest);
	CPPUNIT_TEST(GetAllStmtsOfTypeTest);
	CPPUNIT_TEST(CheckIfStmtOfTypeTest);
	CPPUNIT_TEST(InsertTest);

	//add other methods to test here
	CPPUNIT_TEST_SUITE_END();
	
public:
	void setUp();
	void tearDown();

	void GetAllStmtsOfTypeTest();
	void CheckIfStmtOfTypeTest();
	void InsertTest();
	//add other methods to test here
};