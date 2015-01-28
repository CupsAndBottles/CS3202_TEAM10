#ifndef PARENT_H
#define PARENT_H

#include <utility>
#include <vector>
#include <map>

using namespace std;

class Parent {
public:
	// Default constructor
	Parent();

    // API
<<<<<<< HEAD
	static void SetParent(int parentStmtIndex, int childStmtIndex);
	static bool IsParent(int parentStmtIndex, int childStmtIndex);
	static int GetParentOf(int childStmtIndex);
	static vector<int> GetChildrenOf(int parentStmtIndex);
	
	static bool IsParentT(int parentStmtIndex, int childStmtIndex);
	static vector<int> GetParentTOf(int childStmtIndex);
	static vector<int> GetChildrenTOf(int parentStmtIndex);
=======
	static void SetParent(unsigned int parentStmtIndex, unsigned int childStmtIndex);
	static bool IsParent(unsigned int parentStmtIndex, unsigned int childStmtIndex);
	static unsigned int GetParentOf(unsigned int childStmtIndex);
	static vector<unsigned int> GetChildrenOf(unsigned int parentStmtIndex);
	static bool IsParentT(unsigned int parentStmtIndex, unsigned int childStmtIndex);
	static vector<unsigned int> GetParentTOf(unsigned int childStmtIndex);
	static vector<unsigned int> GetChildrenTOf(unsigned int parentStmtIndex);
>>>>>>> bbe6fe90522bfe645f1f6114866d0fb778b4dde8
	
	static bool HasAnyParents();

	// helper methods for testing
	static unsigned int SizeOfParent();
	static void ClearData();

private:
<<<<<<< HEAD
	static map <int, vector<int>> parentToChildrenTable;
	static map <int, int> childToParentTable;
	
	static bool AlreadyInserted(int parentStmtIndex, int childStmtIndex);
	static bool HasNoParent(int childStmtIndex);
	
=======
	static vector<pair<unsigned int, unsigned int>> parentTable;	// List of Parent(s1, s2) relationships
	
	static bool AlreadyInserted(pair<unsigned int, unsigned int> newPair);
	// insert other private methods here


>>>>>>> bbe6fe90522bfe645f1f6114866d0fb778b4dde8
};
#endif