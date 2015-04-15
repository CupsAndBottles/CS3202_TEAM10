#pragma once

#include <vector>
#include <map>
#include <queue>
#include <stack>

using namespace std;

class NextBip {
public:
	// default constructor
	NextBip();

	// API
	static void setReturnPoint(int procedure, int returnPoint);
	static void setEndOfProc(int procedure, int endOfProc);
	static bool IsNext(int progLineBefore, int progLineAfter);
	static vector<int> GetNextAfter(int progLineBefore);
	static vector<int> GetNextBefore(int progLineAfter);
	static vector<int> GetReturnsTo(int calledProc, int callingProc); // returns the return point in the calling proc from the called proc
	static vector<int> GetEntryPoints(int calledProc, int callingProc); // returns the entry call stmt in the calling proc calling the called proc
	static vector<int> GetAllEntryPoints(int calledProc);
	static vector<int> GetAllReturnPoints(int calledProc);
	static vector<int> GetEndPoints(int proc);
	static bool IsEndPoint(int stmt, int procedure);

	static bool IsNextBipT(int progLineBefore, int progLineAfter);
	static vector<int> GetNextBipTAfter(int progLineBefore);
	static vector<int> GetNextBipTBefore(int progLineAfter);

	static void ClearData();

private:
	static map <int, vector<int>> returnPoints;
	static map <int, vector<int>> endsOfProcs;
	static queue<int> AddToQueue(queue<int> linesToCheck, vector<int> additions);

};

