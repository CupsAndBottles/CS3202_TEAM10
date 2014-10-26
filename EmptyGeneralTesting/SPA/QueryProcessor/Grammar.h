#pragma once
#include <string>

enum Relationship {
	MODIFIES,
	USES,
	FOLLOWS,
	FOLLOWST,
	PARENT,
	PARENTT,
	CALLS,
	CALLST,
	NEXT,
	NEXTT,
	AFFECTS,
	AFFECTST
};

enum ArgumentType {
	SYNONYM,
	UNDERSCORE,
	IDENT,
	EXPRESSION,
	INTEGER,
	NO_ARGUMENT
};

enum SynonymType {
	ASSIGN,
	STMT,
	WHILE,
	IF,
	VARIABLE,
	CONSTANT,
	PROCEDURE,
	PROG_LINE,
	CALL,
	BOOLEAN,
	NO_SYNONYM
};


struct Synonym {
	std::string synonym;
	SynonymType type;

	Synonym() : synonym(""), type(NO_SYNONYM) {};
	Synonym(std::string s, SynonymType t) : synonym(s) , type(t) {}
};

struct Argument {
	std::string value;
	ArgumentType type;
	Synonym syn;

	Argument() : value(""), type(NO_ARGUMENT), syn() {};
	Argument(std::string v, ArgumentType t) : value(v) , type(t) {}
	Argument(Synonym s) : syn(s) {}
	Argument(std::string v) : value(v) {}
};

struct Declaration {	//assign a1,a2; while w1,w2;
	Synonym synonym;

	Declaration(Synonym s) : synonym(s) {}
};

struct SelectClause {	//if BOOLEAN, then synonym = BOOLEAN, type = BOOLEAN
	Synonym synonym;

	SelectClause(Synonym s) : synonym(s) {}
};

struct PatternClause {	//2 argument for IF
	Synonym synonym;
	Argument arg1, arg2;

	PatternClause(Synonym s, Argument a1, Argument a2) : synonym(s) , arg1(a1) , arg2(a2) {}
};

struct SuchThatClause {
	Relationship relationship;
	Argument arg1, arg2;

	SuchThatClause(Relationship r, Argument a1, Argument a2) : relationship(r) , arg1(a1), arg2(a2) {}
};

struct WithClause {
	std::string arg1, arg2;
	
	WithClause(std::string a1, std::string a2) : arg1(a1) , arg2(a2) {}
};


/*
assign a1,a2; while w1,w2;
Select a2 pattern a1("x",_) and a2("x",_"x"_) such that Affects(a1,7) and Parent*(w2,a2) and Parent*(w1,_) with a1.stmt#=5

vector declarations
{
	declaration
	{
		synonym: a1
		type: assign
	},
	declaration
	{
		synonym: a2
		type: assign
	},
	declaration
	{
		synonym: w1
		type: while
	},
	declaration
	{
		synonym: w2
		type: while
	}
}

vector selectClauses
{
	selectClause
	{
		synonym: a2
		type : assign	
	}
}

vector patternClauses
{
	patternClause
	{
		synonym: a1
		synonym_type: assign
		arg1: "x"
		arg1_type: string
		arg2: _
		arg2_type: underscore
	},
	patternClause
	{	
		synonym: a2
		synonym_type
		arg1: "x"
		arg1_type: variable
		arg2: _"x+y"_
		arg2_type: expression
	}
}

vector suchThatClauses
{
	suchThatClause
	{
		type: Affects
		arg1: a1
		arg1_type: synonym
		arg2: 7
		arg2_type: integer
	},
	suchThatClause
	{
		type: Parent*
		arg1: w2
		arg1_type: synonym
		arg2: a2
		arg2_type: synonym
	},
	suchThatClause
	{
		type: Parent*
		arg1: w1
		arg1_type: synonym
		arg2: _
		arg2_type: underscore
	}
}

vector withClauses
{
	withClause
	{
		arg1: a1.stmt
		arg2: 5
	}
}

arg: _
arg_type: underscore

arg: "x+y" / "x" / "x*y"
arg_type: expression

arg: 5
arg_type: integer

arg: a1
arg_type: synonym

*/