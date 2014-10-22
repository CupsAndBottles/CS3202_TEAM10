#pragma once
#include <string>

struct Declaration {	//assign a1,a2; while w1,w2;
	std::string type;
	std::string synonym;

	Declaration(std::string t, std::string s) : type(t) , synonym(s) {}
};

struct SelectClause {
	std::string type;
	std::string synonym;

	SelectClause(std::string t, std::string s) : type(t) , synonym(s) {}
};

struct PatternClause {
	std::string type, arg1, arg2;

	PatternClause(std::string t, std::string a1, std::string a2) : type(t) , arg1(a1) , arg2(a2) {}
};

struct SuchThatClause {
	std::string condition, arg1, arg2;

	SuchThatClause(std::string c, std::string a1, std::string a2) : condition(c) , arg1(a1) , arg2(a2) {}
};

struct WithClause {
	std::string arg1, arg2;
	
	WithClause(std::string a1, std::string a2) : arg1(a1) , arg2(a2) {}
};


/*
assign a1,a2; while w1,w2;
Select a2 pattern a1("x",_) and a2("x",_"x"_) such that Affects(a1,a2) and Parent*(w2,a2) and Parent*(w1,w2) with a1.stmt#=5

vector declarations
{
	declaration
	{
		type: assign
		synonym: a1
	},
	declaration
	{
		type: assign
		synonym: a2
	},
	declaration
	{
		type: while
		synonym: w1
	},
	declaration
	{
		type: while
		synonym: w2
	}
}

vector selectClauses
{
	selectClause
	{
		select: a2
	}
}

vector patternClauses
{
	patternClause
	{
		type: a1
		arg1: "x"
		arg2: _
	},
	patternClause
	{	
		type: a2
		arg1: "x"
		arg2: _"x"_
	}
}

vector suchThatClauses
{
	suchThatClause
	{
		type: Affects
		arg1: a1
		arg2: a2
	},
	suchThatClause
	{
		type: Parent*
		arg1: w2
		arg2: a2
	},
	suchThatClause
	{
		type: Parent*
		arg1: w1
		arg2: w2
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



*/