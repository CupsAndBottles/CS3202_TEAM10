#include "PKBCleaner.h"


PKBCleaner::PKBCleaner(void)
{
}


PKBCleaner::~PKBCleaner(void)
{
}

void PKBCleaner::ClearAll() {
	Calls::ClearData();
	ConstTable::ClearData();
	Follows::ClearData();
	Modifies::ClearData();
	Next::ClearData();
	NextBip::ClearData();
	NodeTypeTable::ClearData();
	Parent::ClearData();
	ProcTable::ClearData();
	StmtTypeTable::ClearData();
	Uses::ClearData();
	VarTable::ClearData();

}
