#include <string>
#include <vector>
#include "../Program/TNode/TNode.h"

using namespace std;

struct Pattern {
	string expr;
	Pattern* leftPattern;
	Pattern* rightPattern;
	bool partialMatch;
};

class PatternMatcher {
    public:
        PatternMatcher() { };

		static vector<int> MatchPatternFromRoot(Pattern object);
		static bool MatchPatternAtLeaves(TNode* node, Pattern object);
};
