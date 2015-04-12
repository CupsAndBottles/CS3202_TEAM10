#pragma once
class Contains {
public:
	Contains();

	// API 
	bool IsContains(int nodeContaining, int nodeContained);
	vector<int> GetContaining(int nodeContaining);
	vector<int> GetContained(int nodeContaining);

	bool IsContainsT(int nodeContaining, int nodeContained);
	vector<int> GetContainingT(int nodeContaining);
	vector<int> GetContainedT(int nodeContaining);
};

