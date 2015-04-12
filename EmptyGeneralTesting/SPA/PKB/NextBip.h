#pragma once

class NextBip {
public:
	// default constructor
	NextBip();

	// API
	static void setReturnPoint(int procedure, int returnPoint);
	static void setEndOfProc(int procedure, int endOfProc);
	static vector<int> GetNextAfter(int progLineBefore);
	static vector<int> GetNextBefore(int progLineAfter);

	static bool IsNextT(int progLineBefore, int progLineAfter);
	static vector<int> GetNextTAfter(int progLineBefore);
	static vector<int> GetNextTBefore(int progLineAfter);

	static void ClearData();

private:
	static map <int, vector<int>> returnPoints;
	static map <int, vector<int>> endsOfProcs
};

