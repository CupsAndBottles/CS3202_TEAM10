#include "VariableTNode.h"

VariableTNode::VariableTNode(string identifier)
	: AtomicTNode(VARIABLE, identifier) {
		BuildName(EnumToString(VARIABLE).append(":"));
}
