#include <cppunit\config\SourcePrefix.h>

#include "Follows.h"
#include "FollowsTest.h"

#include <iostream>
#include <string>
#include <stdint.h>

void FollowsTest::setUp() {
	// empty body
}

void FollowsTest::tearDown() {
	// empty body
}

CPPUNIT_TEST_SUITE_REGISTRATION(FollowsTest);

void FollowsTest::testConstructor() {
	Follows testFollows;

	CPPUNIT_ASSERT_EQUAL(0, testFollows.SizeOfFollows());

}

void FollowsTest::testSetFollows() {
	Follows testFollows;

	testFollows.SetFollows(1, 2);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("regular insert, size of table should increase by 1", 1, testFollows.SizeOfFollows());

	testFollows.SetFollows(1, 2);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("inserting a repeated relationship, size should remain the same", 1, testFollows.SizeOfFollows());

	// throws exception if > 1 stmt follows after/before

}

void FollowsTest::testIsFollows() {
	Follows testFollows;

	testFollows.SetFollows(3, 4);
	CPPUNIT_ASSERT_MESSAGE("regular check that's true", testFollows.IsFollows(3, 4));
	CPPUNIT_ASSERT_MESSAGE("regular check that's false", !testFollows.IsFollows(4, 3));
	CPPUNIT_ASSERT_MESSAGE("checking for a non-existent stmt", !testFollows.IsFollows(5, 3));

}

void FollowsTest::testGetFollowsBefore() {
	Follows testFollows;

	testFollows.SetFollows(3, 4);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("regular GetFollowsBefore", 3, testFollows.GetFollowsBefore(4));
	CPPUNIT_ASSERT_EQUAL_MESSAGE("regular no stmt before", -1, testFollows.GetFollowsBefore(3));
	CPPUNIT_ASSERT_EQUAL_MESSAGE("finding stmt before an element that doesn't exist", -1, testFollows.GetFollowsBefore(2));

}

void FollowsTest::testGetFollowsAfter() {
	Follows testFollows;

	testFollows.SetFollows(3, 4);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("regular GetFollowsAfter", 4, testFollows.GetFollowsAfter(3));
	CPPUNIT_ASSERT_EQUAL_MESSAGE("regular no stmt after", -1, testFollows.GetFollowsAfter(4));
	CPPUNIT_ASSERT_EQUAL_MESSAGE("finding stmt after an element that doesn't exist", -1, testFollows.GetFollowsAfter(2));

}

void FollowsTest::testIsFollowsT() {
	Follows testFollows;

	testFollows.SetFollows(3, 5);
	testFollows.SetFollows(5, 7);
	testFollows.SetFollows(2, 4);

	CPPUNIT_ASSERT_MESSAGE("regular check that's true for 1 layer", testFollows.IsFollowsT(3, 5));
	CPPUNIT_ASSERT_MESSAGE("regular check that's true for more than 1 layers", testFollows.IsFollowsT(3, 7));
	CPPUNIT_ASSERT_MESSAGE("regular check that's false", !testFollows.IsFollowsT(2, 3));

	// throw exception for non-existent stmt#?

}

void FollowsTest::testGetFollowsTBefore() {
	Follows testFollows;
	vector<int> resultTestFollows;
	int resultSize;

	testFollows.SetFollows(3, 4);
	testFollows.SetFollows(4, 6);

	resultTestFollows = testFollows.GetFollowsTBefore(4);
	resultSize = (int16_t) resultTestFollows.size();	// assumes 16-bit int
	CPPUNIT_ASSERT_EQUAL_MESSAGE("regular follows before for 1 layer", 1, resultSize);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("regular follows beforefor 1 layer", 3, resultTestFollows.at(0));

	resultTestFollows = testFollows.GetFollowsTBefore(6);
	resultSize = (int16_t) resultTestFollows.size();	// assumes 16-bit int
	CPPUNIT_ASSERT_EQUAL_MESSAGE("regular follows before for more than 1 layers", 2, resultSize);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("regular follows before for more than 1 layers", 4, resultTestFollows.at(0));
	CPPUNIT_ASSERT_EQUAL_MESSAGE("regular follows before for more than 1 layers", 3, resultTestFollows.at(1));

	resultTestFollows = testFollows.GetFollowsTBefore(3);
	resultSize = (int16_t) resultTestFollows.size();	// assumes 16-bit int
	CPPUNIT_ASSERT_EQUAL_MESSAGE("no stmt following before", 0, resultSize);

	resultTestFollows = testFollows.GetFollowsTBefore(2);
	resultSize = (int16_t) resultTestFollows.size();	// assumes 16-bit int
	CPPUNIT_ASSERT_EQUAL_MESSAGE("get stmt following before an element that doesn't exist", 0, resultSize);
	
}

void FollowsTest::testGetFollowsTAfter() {
	Follows testFollows;
	vector<int> resultTestFollows;
	int resultSize;

	testFollows.SetFollows(3, 5);
	testFollows.SetFollows(5, 7);
	testFollows.SetFollows(2, 4);

	resultTestFollows = testFollows.GetFollowsTAfter(2);
	resultSize = (int16_t) resultTestFollows.size();
	CPPUNIT_ASSERT_EQUAL_MESSAGE("regular follows after for 1 layer", 1, resultSize);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("regular follows after for 1 layer", 4, resultTestFollows.at(0));

	resultTestFollows = testFollows.GetFollowsTAfter(3);
	resultSize = (int16_t) resultTestFollows.size();	// assumes 16-bit int
	CPPUNIT_ASSERT_EQUAL_MESSAGE("regular follows after for more than 1 layers", 2, resultSize);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("regular follows after for more than 1 layers", 5, resultTestFollows.at(0));
	CPPUNIT_ASSERT_EQUAL_MESSAGE("regular follows after for more than 1 layers", 7, resultTestFollows.at(1));

	resultTestFollows = testFollows.GetFollowsTAfter(7);
	resultSize = (int16_t) resultTestFollows.size();	// assumes 16-bit int
	CPPUNIT_ASSERT_EQUAL_MESSAGE("no stmt following after", 0, resultSize);

	resultTestFollows = testFollows.GetFollowsTAfter(6);
	resultSize = (int16_t) resultTestFollows.size();	// assumes 16-bit int
	CPPUNIT_ASSERT_EQUAL_MESSAGE("get stmt following after an element that doesn't exist", 0, resultSize);

}

void FollowsTest::testHasAnyFollows() {
	Follows testFollows;

	CPPUNIT_ASSERT_MESSAGE("regular has no follows", !testFollows.HasAnyFollows());
	
	testFollows.SetFollows(3, 4);
	CPPUNIT_ASSERT_MESSAGE("regular has follows", testFollows.HasAnyFollows());

}
// insert other methods below here
// add a comment before each method to indicate its purpose