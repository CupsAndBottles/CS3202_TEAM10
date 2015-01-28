#ifndef PARENT_H
#define PARENT_H

#include <utility>
#include <vector>

using namespace std;

class Parent {
public:
	// Default constructor
	Parent();

    // API
	static void SetParent(unsigned int parentStmtIndex, unsigned int childStmtIndex);
	static bool IsParent(unsigned int parentStmtIndex, unsigned int childStmtIndex);
	static unsigned int GetParentOf(unsigned int childStmtIndex);
	static vector<unsigned int> GetChildrenOf(unsigned int parentStmtIndex);
	static bool IsParentT(unsigned int parentStmtIndex, unsigned int childStmtIndex);
	static vector<unsigned int> GetParentTOf(unsigned int childStmtIndex);
	static vector<unsigned int> GetChildrenTOf(unsigned int parentStmtIndex);
	
	static bool HasAnyParents();

	// helper methods for testing
	static unsigned int SizeOfParent();
	static void ClearData();

private:
	static vector<pair<unsigned int, unsigned int>> parentTable;	// List of Parent(s1, s2) relationships
	
	static bool AlreadyInserted(pair<unsigned int, unsigned int> newPair);
	// insert other private methods here


};
#endif