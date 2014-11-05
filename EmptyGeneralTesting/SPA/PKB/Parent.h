#include <utility>
#include <vector>

using namespace std;

class Parent {
public:
	// Default constructor
	Parent();

    // API
	void SetParent(int parentStmtIndex, int childStmtIndex);
	bool IsParent(int parentStmtIndex, int childStmtIndex);
	int GetParentOf(int childStmtIndex);
	vector<int> GetChildrenOf(int parentStmtIndex);
	bool IsParentT(int parentStmtIndex, int childStmtIndex);
	vector<int> GetParentTOf(int childStmtIndex);
	vector<int> GetChildrenTOf(int parentStmtIndex);
	
	bool HasAnyParents();

	// helper methods for testing
	int SizeOfParent();

private:
	vector<pair<int, int>> parentTable;	// List of Parent(s1, s2) relationships
	
	bool AlreadyInserted(pair<int, int> newPair);
	// insert other private methods here


};
