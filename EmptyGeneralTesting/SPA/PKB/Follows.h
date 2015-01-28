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
    // Return objects are of unsigned int types instead of <TNode> types
	static void SetFollows(unsigned int stmtBefore, unsigned int stmtAfter);
	static bool IsFollows(unsigned int stmtBefore, unsigned int stmtAfter);
	static unsigned int GetFollowsBefore(unsigned int stmtAfter);
	static unsigned int GetFollowsAfter(unsigned int stmtBefore);
	
	static bool IsFollowsT(unsigned int stmtBefore, unsigned int stmtAfter);
	static vector<unsigned int> GetFollowsTBefore(unsigned int stmtAfter);
	static vector<unsigned int> GetFollowsTAfter(unsigned int stmtBefore);
	static bool HasAnyFollows();

	// helper methods for testing
	static unsigned int SizeOfFollows();
	static void ClearData();

private:
	static vector<pair<unsigned int, unsigned int>> followsTable;	// List of Follows(s1, s2) relationships
	
	static bool AlreadyInserted(pair<unsigned int, unsigned int> newPair);
	// insert other private methods here

};

#endif