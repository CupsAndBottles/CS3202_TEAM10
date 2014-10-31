#include <cppunit\config\SourcePrefix.h>

#include "Parent.h"
#include "ParentTest.h"

#include <iostream>
#include <string>
#include <stdint.h>

void ParentTest::setUp() {
	// empty body
}

void ParentTest::tearDown() {
	// empty body
}

CPPUNIT_TEST_SUITE_REGISTRATION(ParentTest);

void ParentTest::testConstructor() {
	Parent testParent;

	CPPUNIT_ASSERT_EQUAL(0, testParent.SizeOfParent());

}

void ParentTest::testSetParent() {
	Parent testParent;

	testParent.SetParent(1, 2);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("regular insert, size of table should increase by 1", 1, testParent.SizeOfParent());

	testParent.SetParent(1, 2);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("inserting a repeated relationship, size should remain the same", 1, testParent.SizeOfParent());

	// try inserting setting a non-integer

}

void ParentTest::testIsParent() {
	Parent testParent;

	testParent.SetParent(3, 4);
	CPPUNIT_ASSERT_MESSAGE("regular check that's true", testParent.IsParent(3, 4));
	CPPUNIT_ASSERT_MESSAGE("regular check that's false", !testParent.IsParent(4, 3));
	CPPUNIT_ASSERT_MESSAGE("checking for a non-existent stmt", !testParent.IsParent(5, 3));

}

void ParentTest::testGetParentOf() {
	Parent testParent;

	testParent.SetParent(3, 4);
	testParent.SetParent(3, 5);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("regular GetParent", 3, testParent.GetParentOf(4));
	CPPUNIT_ASSERT_EQUAL_MESSAGE("regular GetParent", 3, testParent.GetParentOf(5));
	CPPUNIT_ASSERT_EQUAL_MESSAGE("regular no Parent", -1, testParent.GetParentOf(3));
	CPPUNIT_ASSERT_EQUAL_MESSAGE("finding parent of an element that doesn't exist", -1, testParent.GetParentOf(2));

}

void ParentTest::testGetChildrenOf() {
	Parent testParent;
	vector<int> resultTestParent;
	int resultSize;

	testParent.SetParent(3, 4);
	testParent.SetParent(3, 5);
	resultTestParent = testParent.GetChildrenOf(3);
	resultSize = (int16_t) resultTestParent.size();	// assumes 16-bit int
	CPPUNIT_ASSERT_EQUAL_MESSAGE("regular GetChildren", 2, resultSize);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("regular GetChildren", 4, resultTestParent.at(0));
	CPPUNIT_ASSERT_EQUAL_MESSAGE("regular GetChildren", 5, resultTestParent.at(1));

	resultTestParent = testParent.GetChildrenOf(4);
	resultSize = (int16_t) resultTestParent.size();	// assumes 16-bit int
	CPPUNIT_ASSERT_EQUAL_MESSAGE("regular GetChildren from an element with not children", 0, resultSize);

	resultTestParent = testParent.GetChildrenOf(2);
	resultSize = (int16_t) resultTestParent.size();	// assumes 16-bit int
	CPPUNIT_ASSERT_EQUAL_MESSAGE("regular GetChildren from an element that doesn't exist", 0, resultSize);

}

void ParentTest::testIsParentT() {
	Parent testParent;

	testParent.SetParent(3, 4);
	testParent.SetParent(3, 5);
	testParent.SetParent(4, 6);
	testParent.SetParent(5, 7);

	CPPUNIT_ASSERT_MESSAGE("regular check that's true for 1 generation", testParent.IsParentT(3, 5));
	CPPUNIT_ASSERT_MESSAGE("regular check that's true for more than 1 generation", testParent.IsParentT(3, 6));
	CPPUNIT_ASSERT_MESSAGE("regular check that's false", !testParent.IsParentT(5, 6));

}

void ParentTest::testGetParentTOf() {
	Parent testParent;
	vector<int> resultTestParent;
	int resultSize;

	testParent.SetParent(3, 4);
	testParent.SetParent(3, 5);
	testParent.SetParent(4, 6);
	testParent.SetParent(5, 7);
	testParent.SetParent(7, 8);

	resultTestParent = testParent.GetParentTOf(4);
	resultSize = (int16_t) resultTestParent.size();	// assumes 16-bit int
	CPPUNIT_ASSERT_EQUAL_MESSAGE("regular parent for 1 generation", resultSize, 1);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("regular parent for 1 generation", resultTestParent.at(0), 3);

	resultTestParent = testParent.GetParentTOf(8);
	resultSize = (int16_t) resultTestParent.size();	// assumes 16-bit int
	CPPUNIT_ASSERT_EQUAL_MESSAGE("regular parent for more than 1 generation", 3, resultSize);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("regular parent for more than 1 generation", 7, resultTestParent.at(0));
	CPPUNIT_ASSERT_EQUAL_MESSAGE("regular parent for more than 1 generation", 5, resultTestParent.at(1));
	CPPUNIT_ASSERT_EQUAL_MESSAGE("regular parent for more than 1 generation", 3, resultTestParent.at(2));

	resultTestParent = testParent.GetParentTOf(3);
	resultSize = (int16_t) resultTestParent.size();	// assumes 16-bit int
	CPPUNIT_ASSERT_EQUAL_MESSAGE("no parent exists", 0, resultSize);

	resultTestParent = testParent.GetParentTOf(2);
	resultSize = (int16_t) resultTestParent.size();	// assumes 16-bit int
	CPPUNIT_ASSERT_EQUAL_MESSAGE("get parent of an element that doesn't exist", 0, resultSize);

}

void ParentTest::testGetChildrenTOf() {
	Parent testParent;
	vector<int> resultTestParent;
	int resultSize;

	testParent.SetParent(3, 4);
	testParent.SetParent(3, 5);
	testParent.SetParent(4, 6);
	testParent.SetParent(5, 7);
	testParent.SetParent(7, 8);

	resultTestParent = testParent.GetChildrenTOf(5);
	resultSize = (int16_t) resultTestParent.size();	// assumes 16-bit int
	CPPUNIT_ASSERT_EQUAL_MESSAGE("regular children for more than 1 generation", 2, resultSize);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("regular children for more than 1 generation", 7, resultTestParent.at(0));
	CPPUNIT_ASSERT_EQUAL_MESSAGE("regular children for more than 1 generation", 8, resultTestParent.at(1));

	resultTestParent = testParent.GetChildrenTOf(4);
	resultSize = (int16_t) resultTestParent.size();	// assumes 16-bit int
	CPPUNIT_ASSERT_EQUAL_MESSAGE("regular children for 1 generation", 1, resultSize);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("regular children for 1 generation", 6, resultTestParent.at(0));

	resultTestParent = testParent.GetChildrenTOf(6);
	resultSize = (int16_t) resultTestParent.size();	// assumes 16-bit int
	CPPUNIT_ASSERT_EQUAL_MESSAGE("no children exists", 0, resultSize);

	resultTestParent = testParent.GetChildrenTOf(2);
	resultSize = (int16_t) resultTestParent.size();	// assumes 16-bit int
	CPPUNIT_ASSERT_EQUAL_MESSAGE("get children of an element that doesn't exist", 0, resultSize);
	
}

void ParentTest::testHasAnyParents() {
	Parent testParent;

	CPPUNIT_ASSERT_MESSAGE("regular has no parent", !testParent.HasAnyParents());
	testParent.SetParent(3, 4);
	CPPUNIT_ASSERT_MESSAGE("regular has parent", testParent.HasAnyParents());

}

// insert other methods below here
// add a comment before each method to indicate its purpose