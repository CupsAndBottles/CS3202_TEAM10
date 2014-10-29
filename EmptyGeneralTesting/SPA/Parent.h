#include <utility>
#include <vector>

using namespace std;

class Parent {
public:
	// Default constructor
	Parent();

    // API for final Parent
    // stashed away for now, will be used when <TNode> API is well tested
    /*
    void SetParent(TNode parentStmt, TNode parentStmt);
    bool IsParent(TNode parentStmt, TNode parentStmt);
    TNode GetParentOf(TNode childStmt);
    TNode GetChildOf(TNode parentStmt);
    vector<TNode> GetParentTOf(TNode childStmt);
    vector<TNode> GetChildrenTOf(TNode parentStmt);
    vector<TNode> GetParentTOf(TNode::Type type);
    vector<TNode> GetChildrenTOf(TNode::Type type);
    */

    // API for development
	void SetParent(int parentStmtIndex, int childStmtIndex);
	bool IsParent(int parentStmtIndex, int childStmtIndex);
	int GetParentOf(int parentStmtIndex);
	int GetChildOf(int childStmtIndex);
	vector<int> GetParentTOf(int childStmtIndex);
	vector<int> GetChildrenTOf(int parentStmtIndex);


private:
	vector<pair<int, int>> parentTable;	// List of Parent(s1, s2) relationships
	
	bool AlreadyInserted(pair<int, int> newPair);
	// insert other private methods here


};
