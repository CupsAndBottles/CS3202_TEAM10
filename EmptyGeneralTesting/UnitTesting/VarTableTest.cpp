#include <cppunit\config\SourcePrefix.h>
#include "VarTable.h"
#include "VarTableTest.h"

#include <iostream>
#include <string>

void VarTableTest::setUp() {
	// empty body
}

void VarTableTest::tearDown() {
	// empty body
}

CPPUNIT_TEST_SUITE_REGISTRATION(VarTableTest);

// method to test the constructor
void VarTableTest::testConstructor() {
	// create a VarTable object
	VarTable varTableTest;

	int size = varTableTest.getSize();
	CPPUNIT_ASSERT_EQUAL(0, size);
	 
}


// insert other methods below here
// add a comment before each method to indicate its purpose