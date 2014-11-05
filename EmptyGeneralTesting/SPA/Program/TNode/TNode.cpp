#include "TNode.h"

const string TNode::enumStringDeclarations[] = {
	"Procedure",
	"Program",
	"Assignment",
	"Variable",
	"Constant",
	"BinaryOperator",
	"StmtList",
	"While",
};

TNode::TNode(Type type)
	: type(type) {
}

TNode::TNode(Type type, string content)
	: type(type), content(content) {
}

void TNode::ThrowUnsupportedOperationException() {
	throw(string) "Unsupported Operation";
}

TNode* TNode::GetDirectParent() {
	return directParent;
}

TNode* TNode::GetRightSibling() {
	return rightSibling;
}

vector<TNode*> TNode::GetChildren() {
	return children;
}

TNode& TNode::GetChild(int index) {
	return *children[index];
}

TNode::Type TNode::GetType() {
	return type;
}

bool TNode::IsType(Type testType) {
	return (type == testType);
}

void TNode::SetDirectParent(TNode* parent) {
	directParent = parent;
}

void TNode::SetRightSibling(TNode* rightSibling) {
	rightSibling = rightSibling;
}

void TNode::AddChild(TNode* child) {
	if (child == nullptr) {
		throw(string) "Null pointer!";
	}
	if (children.size() > 0) {
		children.back()->SetRightSibling(child);
	}
	child->SetDirectParent(this);
	children.push_back(child);
}

string TNode::GetName() {
	return name;
}

string TNode::GetContent() {
	return content;
}

void TNode::BuildName(string str) {
	name = str.append(name);
}

string TNode::EnumToString(TNode::Type type) {
	return enumStringDeclarations[type];
}


