#include "TNode.h"

const string TNode::enumStringDeclarations[] = {
	"Procedure",
	"Program",
	"Assignment",
	"Variable",
	"Constant",
	"BinaryOperator",
	"StmtList",
	"If",
	"While",
	"Call"
};

TNode::TNode(Type type)
	: type(type) {
}

TNode::TNode(Type type, string content)
	: type(type), content(content) {
}

void TNode::throwUnsupportedOperationException() {
	throw(string) "Unsupported Operation";
}

TNode* TNode::getDirectParent() {
	return directParent;
}

TNode* TNode::getRightSibling() {
	return rightSibling;
}

vector<TNode*> TNode::getChildren() {
	return children;
}

TNode& TNode::getChild(int index) {
	return *children[index];
}

TNode::Type TNode::getType() {
	return type;
}

bool TNode::isType(Type testType) {
	return (type == testType);
}

void TNode::setDirectParent(TNode* parent) {
	directParent = parent;
}

void TNode::setRightSibling(TNode* rightSibling) {
	rightSibling = rightSibling;
}

void TNode::addChild(TNode* child) {
	if (child == nullptr) {
		throw(string) "Null pointer!";
	}
	if (children.size() > 0) {
		children.back()->setRightSibling(child);
	}
	child->setDirectParent(this);
	children.push_back(child);
}

string TNode::getName() {
	return name;
}

string TNode::getContent() {
	return content;
}

void TNode::buildName(string str) {
	name = str.append(name);
}

string TNode::enumToString(TNode::Type type) {
	return enumStringDeclarations[type];
}


