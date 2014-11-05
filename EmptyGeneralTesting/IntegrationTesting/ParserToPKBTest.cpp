#include <cppunit\config\SourcePrefix.h>

#include "ParserToPKBTest.h"

#include "PKB\VarTable.h"
#include "PKB\StmtTypeTable.h"
#include "PKB\Follows.h"
#include "PKB\Parent.h"
#include "PKB\Modifies.h"
#include "PKB\Uses.h"

#include <iostream>
#include <string>
#include <stdint.h>

void ParserToPKBTest::setUp() { 
	// empty body
}

void ParserToPKBTest::tearDown() {
	// empty body
}

CPPUNIT_TEST_SUITE_REGISTRATION(ParserToPKBTest);

void ParserToPKBTest::testNothing() {
	CPPUNIT_ASSERT_EQUAL(0, 1);
}

// insert other methods below here
// add a comment before each method to indicate its purpose