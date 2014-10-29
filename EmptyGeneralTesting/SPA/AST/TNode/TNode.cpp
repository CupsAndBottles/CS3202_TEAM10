#include "TNode.h"

const string enumStringDeclarations[] = {
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

vector<TNode> TNode::getChildren() {
	return children;
}

TNode& TNode::getChild(int index) {
	return children[index];
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

void TNode::addChild(TNode child) {
	if (children.size() > 0) {
		children.back().setRightSibling(&child);
	}
	children.push_back(child);
	child.setDirectParent(this);
}

string TNode::getName() {
	return name;
}

string TNode::getContent() {
	throwUnsupportedOperationException();
	return content;
}

void TNode::buildName(string str) {
	name = str.append(name);
}

string TNode::enumToString(TNode::Type type) {
	return enumStringDeclarations[type];
}

template <class T>
T TNode::typecast(TNode obj) {
	return dynamic_cast<T>(obj);
}

template <class Tptr>
Tptr TNode::typecast(TNode* obj) {
	return dynamic_cast<Tptr>(obj);
}

template <class T>
vector<T> TNode::vectorCaster(vector<TNode> vector) {
	vector<T> result;
	for (int i = 0; i < vector.size; i++) {
		result.push_back(typecast<T>(vector[i]));
	}
	return vector;
}


