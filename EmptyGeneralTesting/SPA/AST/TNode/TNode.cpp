#pragma once

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

deque<TNode> TNode::getChildren() {
	return children;
}

TNode& TNode::getChild(int index) {
	return children.at(index);
}

string TNode::getName() {
	return name;
}

string TNode::getContent() {
	throw(string) "Unsupported Operation";
}

void TNode::buildName(string str) {
	name = str.append(name);
}

void TNode::throwUnsupportedOperationException() {
	throw(string) "Unsupported Operation";
}

string TNode::enumToString(TNode::Type type) {
	return enumStringDeclarations[type];
}

template<class T1, class T2>
static T2 TNode::typecast(T1 obj) {
	return dynamic_cast<T2>(obj);
}

template<class T1, class T2>
static deque<T2> TNode::dequeCaster(deque<T1> deque) {
	deque<T2> result;
	while (deque.size != 0)
		result.push_back(typecast<T1, T2>(deque.front));
	deque.pop_front;
}


