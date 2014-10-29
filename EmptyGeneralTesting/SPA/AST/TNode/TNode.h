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

	TNode(TNode*, Type);
	TNode(TNode*, Type, string);

	virtual TNode* getDirectParent();
	virtual TNode* getRightSibling();
	virtual vector<TNode> getChildren();
	virtual TNode& getChild(int);
	Type getType();
	
	
	void setRightSibling(TNode*);
	virtual void addChildren(vector<TNode>);
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

	void buildName(string);

	template<class T1, class T2>
	static T2 typecast(T1 obj);

	template<class T1, class T2>
	static vector<T2> vectorCaster(vector<T1> vector);

private:
	static const string enumStringDeclarations[];

};