#include <string>
#include <vector>
#include "../Program/TNode/TNode.h"

using namespace std;

struct QueryObject {
    string expr;
    string leftVar;
    string rightVar;
    bool underscoreBefore;
    bool underscoreAfter;
};

class PatternMatcher {
    public:
        PatternMatcher() { };

        static vector<int> MatchPatternFromRoot(TNode* root, QueryObject object);
};
