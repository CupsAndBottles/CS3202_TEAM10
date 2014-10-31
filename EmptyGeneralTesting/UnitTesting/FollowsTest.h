#define FollowsTest_h

#include <cppunit\extensions\HelperMacros.h>

class FollowsTest : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE(FollowsTest);
	CPPUNIT_TEST(testConstructor);
	// add other methods to test here
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void testConstructor();
	// add other methods to test here

};