#pragma once

#include <vector>

using namespace std;

class TNode {
public:
	enum Type {
		PROCEDURE = 0,
		PROGRAM,
		ASSIGNMENT,
		VARIABLE,
		CONSTANT,
		BINARY_OPERATOR,
		STMT_LIST,
		WHILE,
	};

	TNode(Type);
	TNode(Type, string);

	virtual TNode* GetDirectParent();
	virtual TNode* GetRightSibling();
	virtual vector<TNode*> GetChildren();
	virtual TNode& GetChild(int);
	Type GetType();
	bool IsType(Type);
	
	virtual void SetRightSibling(TNode*);
	virtual void AddChild(TNode*);
	string GetName();
	virtual string GetContent();

	static string EnumToString(Type);

protected:	
	Type type;
	TNode* directParent;
	vector<TNode*> children;
	TNode* rightSibling;
	string name;
	string content;

	void ThrowUnsupportedOperationException();

	virtual void SetDirectParent(TNode*);
	void BuildName(string);

private:
	static const string enumStringDeclarations[];

};