#include <cppunit\config\SourcePrefix.h>

#include "NextBipTest.h"
#include "..\SPA\PKB\NextBip.h"
#include "..\SPA\PKB\Next.h"
#include "..\SPA\PKB\Calls.h"
#include "..\SPA\PKB\ProcTable.h"
#include "..\SPA\PKB\StmtTypeTable.h"
#include "..\SPA\Program\Program.h"

void NextBipTest::setUp() {
	ClearAllData();
}

void NextBipTest::tearDown() {
}

void NextBipTest::ClearAllData() {
	Program::ClearAll();
	StmtTypeTable::ClearData();
	ProcTable::ClearData();
	Calls::ClearData();
	Next::ClearData();
	NextBip::ClearData();
}

NextBipTest::NextBipTest(void) {
}


NextBipTest::~NextBipTest(void) {
}
