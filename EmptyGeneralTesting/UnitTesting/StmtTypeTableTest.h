#pragma once
#define ConstTableTest_h

#include <cppunit\extensions\HelperMacros.h>

class StmtTypeTableTest : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE(StmtTypeTableTest);
	CPPUNIT_TEST_SUITE(GetAllStmtsOfTypeTest);
	CPPUNIT_TEST_SUITE(CheckIfStmtOfTypeTest);
	CPPUNIT_TEST_SUITE(InsertTest);

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