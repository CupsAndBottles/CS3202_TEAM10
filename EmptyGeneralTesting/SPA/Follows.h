#include <utility>
#include <vector>

using namespace std;

class Follows {
public:
	// Default constructor
	Follows();

	// Methods
	void SetFollows(int stmtBefore, int stmtAfter);
	bool IsFollows(int stmtBefore, int stmtAfter);
	int GetFollowsBefore(int stmtAfter);
	int GetFollowsAfter(int stmtBefore);
	// Follows*(_, s)
	// Follows*(s, _)

private:
	vector<pair<int, int>> followsTable;	// List of Follows(s1, s2) relationships
	// insert other private methods here

};