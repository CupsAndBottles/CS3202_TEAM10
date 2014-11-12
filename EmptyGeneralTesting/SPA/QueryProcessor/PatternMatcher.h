#include <string>
#include <vector>
#include "../Program/TNode/TNode.h"

using namespace std;

struct Pattern {
	string expr;
	Pattern* leftPattern;
	Pattern* rightPattern;
	bool partialMatch;

	Pattern(string e, Pattern* l, Pattern* r, bool p) : 
	expr(e), leftPattern(l), rightPattern(r), partialMatch(p) {}
};

class PatternMatcher {
    public:
        PatternMatcher() { };

		static vector<int> MatchPatternFromRoot(Pattern object);
		static bool MatchPatternAtLeaves(TNode* node, Pattern object);
};
