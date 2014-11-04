#pragma once

#include <vector>

using namespace std;

class TNode {
public:
	enum Type {
		Procedure = 0,
		Program,
		Assignment,
		Variable,
		Constant,
		BinaryOperator,
		StmtList,
		If,
		While,
		Call
	};

	TNode(Type);
	TNode(Type, string);

	virtual TNode* getDirectParent();
	virtual TNode* getRightSibling();
	virtual vector<TNode> getChildren();
	virtual TNode& getChild(int);
	Type getType();
	bool isType(Type);
	
	
	virtual void setRightSibling(TNode*);
	virtual void addChild(TNode);
	string getName();
	virtual string getContent();

	static string enumToString(Type);

protected:	
	Type type;
	TNode* directParent;
	vector<TNode> children;
	TNode* rightSibling;
	string name;
	string content;

	void throwUnsupportedOperationException();

	virtual void setDirectParent(TNode*);
	void buildName(string);

private:
	static const string enumStringDeclarations[];

};