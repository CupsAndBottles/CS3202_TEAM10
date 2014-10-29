#include "TNode.h"

const string enumStringDeclarations[] = {
	"Procedure",
	"Program",
	"Assignment",
	"Variable",
	"Constant",
	"Plus",
	"Minus",
	"Multiply",
	"StmtList",
	"If",
	"Then",
	"Else",
	"While",
	"Call"
};

TNode::TNode(TNode* parent, TNode* rightSibling, Type type)
	: directParent(parent), rightSibling(rightSibling), type(type), name(""), content("") {
}

TNode::TNode(TNode* parent, TNode* rightSibling, Type type, string content)
	: directParent(parent), rightSibling(rightSibling), type(type), name(content), content(content) {
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

TNode::Type TNode::getType() {
	return type;
}

void TNode::addChild(TNode child) {
	children.push_back(child);
}

void TNode::addChildren(vector<TNode> newChildren) {
	for (int i = 0; i < newChildren.size(); i++) {
		addChild(newChildren[i]);
	}
}

vector<TNode> TNode::getChildren() {
	return children;
}

TNode& TNode::getChild(int index) {
	return children[index];
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

template<class T1, class T2>
static T2 TNode::typecast(T1 obj) {
	return dynamic_cast<T2>(obj);
}

template<class T1, class T2>
static vector<T2> TNode::vectorCaster(vector<T1> vector) {
	vector<T2> result;
	for (int i = 0; i < vector.size; i++) {
		result.push_back(typecast<T1, T2>(vector[i]));
	}
	return vector;
}


