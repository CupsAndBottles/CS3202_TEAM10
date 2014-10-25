#include <utility>
#include <vector>

using namespace std;

class Parent {
public:
	// Default constructor
	Parent();

	// Methods
	void SetParent(int parentStmtIndex, int childStmtIndex);
	bool IsParent(int parentStmtIndex, int childStmtIndex);
	int GetChildrenOf(int parentStmtIndex);
	int GetParentOf(int childStmtIndex);
	// Parent*(_, s)
	// Parent*(s, _)

private:
	vector<pair<int, int>> parentTable;	// List of Parent(s1, s2) relationships
	// insert other private methods here

};