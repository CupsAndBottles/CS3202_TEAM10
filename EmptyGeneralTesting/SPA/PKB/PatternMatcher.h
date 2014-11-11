#pragma once

#include "Program\Program.h"
#include "Program\TNode\TNode.h"

class PatternMatcher {

public:
	PatternMatcher(void);
	~PatternMatcher(void);

private:
	TNode* currentNode();

};

