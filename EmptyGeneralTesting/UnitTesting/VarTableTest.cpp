#include <cppunit\config\SourcePrefix.h>
#include "VarTable.h"
#include "VarTableTest.h"
#include "IndexNotFoundException.h"

#include <iostream>
#include <string>

void VarTableTest::setUp() {
	// empty body
}

void VarTableTest::tearDown() {
	// empty body
}

//CPPUNIT_TEST_SUITE_REGISTRATION(VarTableTest);
/*
// method to test the constructor
void VarTableTest::testConstructor() {
	// create a VarTable object
	VarTable varTableTest;

	int size = varTableTest.GetSize();
	CPPUNIT_ASSERT_EQUAL(0, size);
	 
}

void VarTableTest::testInsert() {
	VarTable varTableTest;
	int size = 0, varIndex = 0; 
	string varName;

	// insert a new variable to a new VarTable
	varIndex = varTableTest.InsertVar("x2");
	CPPUNIT_ASSERT_EQUAL(0, varIndex);
	varIndex = varTableTest.InsertVar("x1");
	CPPUNIT_ASSERT_EQUAL(1, varIndex);
	varIndex = varTableTest.InsertVar("abcedfghijklmnop");
	CPPUNIT_ASSERT_EQUAL(2, varIndex);

	// x2 inserted first to check that the order of x1 and x2 are nto being rearranged
	
	size = varTableTest.GetSize();
	CPPUNIT_ASSERT_EQUAL(3, size);
	
	varName = varTableTest.GetVarName(0);
	CPPUNIT_ASSERT(varName == "x2");

	varName = varTableTest.GetVarName(1);
	CPPUNIT_ASSERT(varName == "x1");
	
	// insert a variable that already exists in the VarTable
	int newIndex;
	newIndex = varTableTest.InsertVar("x2");
	CPPUNIT_ASSERT_EQUAL(0, newIndex);
	CPPUNIT_ASSERT_EQUAL(3, size);
	
	newIndex = varTableTest.InsertVar("x1");
	CPPUNIT_ASSERT_EQUAL(1, newIndex);
	CPPUNIT_ASSERT_EQUAL(3, size);

	// test white spaces...

}

void VarTableTest::testGetIndexOf() {
	VarTable varTableTest;
	int varIndex;

	// test for repeated insertions 
	// test that indexes are assigned based on the order variables are inserted
	varTableTest.InsertVar("b");
	varTableTest.InsertVar("a");
	varTableTest.InsertVar("b");
	varTableTest.InsertVar("c");
	varTableTest.InsertVar("123");

	varIndex = varTableTest.GetIndexOf("b");
	CPPUNIT_ASSERT_EQUAL(0, varIndex);
	varIndex = varTableTest.GetIndexOf("a");
	CPPUNIT_ASSERT_EQUAL(1, varIndex);
	varIndex = varTableTest.GetIndexOf("123");
	CPPUNIT_ASSERT_EQUAL(3, varIndex);

	// test for variables that do not exist
	varIndex = varTableTest.GetIndexOf("z");
	CPPUNIT_ASSERT_EQUAL(-1, varIndex);
	
	// test white spaces...

}

void VarTableTest::testGetSize() {
	VarTable varTableTest;
	int size;

	// test for empty varTable
	size =  varTableTest.GetSize();
	CPPUNIT_ASSERT_EQUAL(0, size);

	// test for repeated insertions
	varTableTest.InsertVar("a");
	varTableTest.InsertVar("a");
	varTableTest.InsertVar("b");
	varTableTest.InsertVar("a");
	size = varTableTest.GetSize();
	CPPUNIT_ASSERT_EQUAL(2, size);

}

void VarTableTest::testGetVarName() {
	VarTable varTableTest;
	string varName;

	// test get a non-existent variable
	CPPUNIT_ASSERT_THROW(varTableTest.GetVarName(0), IndexNotFoundException);
	CPPUNIT_ASSERT_THROW(varTableTest.GetVarName(-1), IndexNotFoundException);

	varTableTest.InsertVar("a");
	varTableTest.InsertVar("a");
	varTableTest.InsertVar("b");
	varTableTest.InsertVar("a");

	// regular GetVarName
	varName = varTableTest.GetVarName(1);
	CPPUNIT_ASSERT("b" == varName);


}*/

// insert other methods below here
// add a comment before each method to indicate its purpose