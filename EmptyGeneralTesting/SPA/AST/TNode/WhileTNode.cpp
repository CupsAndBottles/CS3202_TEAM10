#include "WhileTNode.h"

WhileTNode::WhileTNode(StmtListTNode* directParent, int lineNumber, StmtTNode* logicalParent) 
	: TNode(directParent, While)
	, ConditionalTNode(directParent, While, lineNumber, logicalParent) {
}

StmtListTNode& WhileTNode::getBody() {
	return TNode::typecast<TNode, StmtListTNode>(getChild(1));
}
