#ifndef FOLLOWS_H
#define FOLLOWS_H

#include <utility>
#include <vector>
#include <map>

using namespace std;

class Follows {
public:
	// Default constructor
	Follows();

<<<<<<< HEAD
	// API
	static void SetFollows(int stmtBefore, int stmtAfter);
	static bool IsFollows(int stmtBefore, int stmtAfter);
	static int GetFollowsBefore(int stmtAfter);
	static int GetFollowsAfter(int stmtBefore);
	
	static bool IsFollowsT(int stmtBefore, int stmtAfter);
	static vector<int> GetFollowsTBefore(int stmtAfter);
	static vector<int> GetFollowsTAfter(int stmtBefore);
	
=======
	// API for development
    // Return objects are of unsigned int types instead of <TNode> types
	static void SetFollows(unsigned int stmtBefore, unsigned int stmtAfter);
	static bool IsFollows(unsigned int stmtBefore, unsigned int stmtAfter);
	static unsigned int GetFollowsBefore(unsigned int stmtAfter);
	static unsigned int GetFollowsAfter(unsigned int stmtBefore);
	
	static bool IsFollowsT(unsigned int stmtBefore, unsigned int stmtAfter);
	static vector<unsigned int> GetFollowsTBefore(unsigned int stmtAfter);
	static vector<unsigned int> GetFollowsTAfter(unsigned int stmtBefore);
>>>>>>> bbe6fe90522bfe645f1f6114866d0fb778b4dde8
	static bool HasAnyFollows();

	// helper methods for testing
	static unsigned int SizeOfFollows();
	static void ClearData();

private:
<<<<<<< HEAD
	static map <int, int> beforeToAfterTable;
	static map <int, int> afterToBeforeTable;
=======
	static vector<pair<unsigned int, unsigned int>> followsTable;	// List of Follows(s1, s2) relationships
	
	static bool AlreadyInserted(pair<unsigned int, unsigned int> newPair);
	// insert other private methods here
>>>>>>> bbe6fe90522bfe645f1f6114866d0fb778b4dde8

	static bool NoRelationshipConflicts(int stmtBefore, int stmtAfter);
	static bool HasNoStmtAfter(int stmtBefore);
	static bool HasNoStmtBefore(int stmtAfter);

};
#endif