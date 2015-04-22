#pragma once
#include <string>
#include <vector>
#include "..\Program\TNode\TNode.h"

using namespace std;

struct Pattern {
	Pattern(string e = "", Pattern* l = NULL, Pattern* r = NULL) :
		expr(e), leftPattern(l), rightPattern(r) {
	};

	string expr;
	Pattern* leftPattern;
	Pattern* rightPattern;

};

class PatternMatcher {
    public:
        PatternMatcher() {};

		static Pattern CreatePatternObject(string expr);
		static vector<int> MatchPatternFromRoot(string expr);
		static vector<int> MatchPatternFromRoot(string expr, vector<int> stmtsToMatch);
		static vector<int> MatchPatternFromRoot(Pattern object, bool partialMatch);
		static vector<int> MatchPatternFromRoot(Pattern object, bool partialMatch, vector<int> stmtsToMatch);
		static bool MatchPatternAtLeaves(TNode* node, Pattern object, bool partialMatch);
};
