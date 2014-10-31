#define ParentTest_h

#include <cppunit\extensions\HelperMacros.h>

class ParentTest : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE(ParentTest);
	CPPUNIT_TEST(testConstructor);
	CPPUNIT_TEST(testSetParent);
	CPPUNIT_TEST(testIsParent);
	CPPUNIT_TEST(testGetParentOf);
	CPPUNIT_TEST(testGetChildrenOf);
	// add other methods to test here
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void testConstructor();
	void testSetParent();
	void testIsParent();
	void testGetParentOf();
	void testGetChildrenOf();
	// add other methods to test here

};