#ifndef NEXT_H
#define NEXT_H

#include <utility>
#include <vector>
#include <map>

using namespace std;

class Next {
public:
	// Default constructor
	Next();

	// API
	static void SetNext(int stmtBefore, int stmtAfter);
	static bool IsNext(int stmtBefore, int stmtAfter);
	static int GetNextBefore(int stmtAfter);
	static int GetNextAfter(int stmtBefore);
	
	static bool IsNextT(int stmtBefore, int stmtAfter);
	static vector<int> GetNextTBefore(int stmtAfter);
	static vector<int> GetNextTAfter(int stmtBefore);
	

	static bool HasAnyFollows();

	// helper methods for testing
	static int SizeOfNext();
	static void ClearData();

private:
	static map <int, int> beforeToAfterTable;
	static map <int, int> afterToBeforeTable;

	static bool NoRelationshipConflicts(int stmtBefore, int stmtAfter);
	static bool HasNoStmtAfter(int stmtBefore);
	static bool HasNoStmtBefore(int stmtAfter);

};
#endif