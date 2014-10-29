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
		Plus,
		Minus,
		Multiply,
		StmtList,
		If,
		Then,
		Else,
		While,
		Call
	};

	virtual TNode* getDirectParent();
	virtual TNode* getRightSibling();
	Type getType();
	
	virtual vector<TNode> getChildren();
	virtual TNode& getChild(int);
	string getName();
	virtual string getContent();
	static string enumToString(Type);

protected:
	TNode(TNode*, TNode*, Type);
	TNode(TNode*, TNode*, Type, string);
	
	Type type;
	TNode* directParent;
	vector<TNode> children;
	TNode* rightSibling;
	string name;
	string content;

	virtual void addChildren(vector<TNode>);
	virtual void addChild(TNode);
	void throwUnsupportedOperationException();

	void buildName(string);

	template<class T1, class T2>
	static T2 typecast(T1 obj);

	template<class T1, class T2>
	static vector<T2> vectorCaster(vector<T1> vector);

private:
	static const string enumStringDeclarations[];
};