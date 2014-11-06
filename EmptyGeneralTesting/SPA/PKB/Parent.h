#include <utility>
#include <vector>

using namespace std;

class Parent {
public:
	// Default constructor
	Parent();

    // API
	static void SetParent(int parentStmtIndex, int childStmtIndex);
	static bool IsParent(int parentStmtIndex, int childStmtIndex);
	static int GetParentOf(int childStmtIndex);
	static vector<int> GetChildrenOf(int parentStmtIndex);
	static bool IsParentT(int parentStmtIndex, int childStmtIndex);
	static vector<int> GetParentTOf(int childStmtIndex);
	static vector<int> GetChildrenTOf(int parentStmtIndex);
	
	static bool HasAnyParents();

	// helper methods for testing
	static int SizeOfParent();
	static void ClearData();

private:
	static vector<pair<int, int>> parentTable;	// List of Parent(s1, s2) relationships
	
	static bool AlreadyInserted(pair<int, int> newPair);
	// insert other private methods here


};
