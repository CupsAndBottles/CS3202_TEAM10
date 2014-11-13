#ifndef FOLLOWS_H
#define FOLLOWS_H

#include <utility>
#include <vector>

using namespace std;

class Follows {
public:
	// Default constructor
	Follows();

	// API for development
    // Return objects are of int types instead of <TNode> types
	static void SetFollows(int stmtBefore, int stmtAfter);
	static bool IsFollows(int stmtBefore, int stmtAfter);
	static int GetFollowsBefore(int stmtAfter);
	static int GetFollowsAfter(int stmtBefore);
	
	static bool IsFollowsT(int stmtBefore, int stmtAfter);
	static vector<int> GetFollowsTBefore(int stmtAfter);
	static vector<int> GetFollowsTAfter(int stmtBefore);
	static bool HasAnyFollows();

	// helper methods for testing
	static int SizeOfFollows();
	static void ClearData();

private:
	static vector<pair<int, int>> followsTable;	// List of Follows(s1, s2) relationships
	
	static bool AlreadyInserted(pair<int, int> newPair);
	// insert other private methods here

};

#endif