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
// insert other methods below here
// add a comment before each method to indicate its purpose