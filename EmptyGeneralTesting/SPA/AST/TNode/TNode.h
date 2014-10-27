#pragma once

#include <deque>

using namespace std;

class TNode
{
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
	
	virtual deque<TNode> getChildren();
	virtual TNode& getChild(int);
	string getName();
	virtual string getContent();
	static string enumToString(Type);

protected:
	TNode(TNode*, TNode*, Type);
	TNode(TNode*, TNode*, Type, string);
	
	Type type;
	TNode* directParent;
	deque<TNode> children;
	TNode* rightSibling;
	string name;
	string content;

	virtual void addChild(TNode);
	void throwUnsupportedOperationException();

	void buildName(string);

	template<class T1, class T2>
	static T2 typecast(T1 obj);

	template<class T1, class T2>
	static deque<T2> dequeCaster(deque<T1> deque);

private:
	static const string enumStringDeclarations[];
};