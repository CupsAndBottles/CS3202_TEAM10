#pragma once

#include "PKB\Calls.h"
#include "PKB\ConstTable.h"
#include "PKB\Follows.h"
#include "PKB\Modifies.h"
#include "PKB\Next.h"
#include "PKB\NextBip.h"
#include "PKB\NodeTypeTable.h"
#include "PKB\Parent.h"
#include "PKB\ProcTable.h"
#include "PKB\StmtTypeTable.h"
#include "PKB\Uses.h"
#include "PKB\VarTable.h"

class PKBCleaner {
public:
	PKBCleaner(void);
	~PKBCleaner(void);

	static void ClearAll();
};

