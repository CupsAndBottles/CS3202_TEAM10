#include <string>
#include <vector>
#include "PatternMatcher.h"
#include "../Program/TNode/TNode.h"
#include "../Program/TNode/ProcedureTNode.h"
#include "../Program/TNode/AssignmentTNode.h"
#include "../Program/TNode/WhileTNode.h"
#include "../Program/Program.h"
#include "../PKB/StmtTypeTable.h"

#include <iostream>
#include <stdio.h>

using namespace std;

bool PatternMatcher::MatchPatternAtLeaves(TNode* node, Pattern object) {
	// match tree
	// if no need to match children, return match
	// if
	
	bool match = (node->GetContent() == object.expr);

	// check for children
	// if both empty, return match
	// if pattern has children but not tree, return false
	// if tree has children but not pattern. return partialMatch && match
	// if both have children, match left tree and right tree

	vector<TNode*> children = node->GetChildren();
	bool hasChildPatterns = (object.leftPattern != nullptr) && (object.rightPattern != nullptr);
	bool hasChildNodes = children.size() == 2;
	if (hasChildPatterns && hasChildNodes) {
		// match subtrees
		match = (match && MatchPatternAtLeaves(children[0], *object.leftPattern) && MatchPatternAtLeaves(children[1], *object.rightPattern));
		if (!match) {
			// recursive call
			bool matchLeft = MatchPatternAtLeaves(children[0], object);
			bool matchRight = MatchPatternAtLeaves(children[1], object);

			return (matchLeft || matchRight);
		} else {
			return match;
		}
	} else if (!hasChildPatterns && hasChildNodes) {
		return (match && object.partialMatch);
	} else if (hasChildPatterns && !hasChildNodes) {
		return false;
	} else if (!hasChildPatterns && !hasChildNodes) {
		return match;
	} else {
		return false;
	}
}

vector<int> PatternMatcher::MatchPatternFromRoot(Pattern object) {
	// printf("1 %s 2 %s 3 %s\n", object.expr.c_str(), object.leftPattern->expr.c_str(), object.rightPattern->expr.c_str());

	vector<int> assignmentStmts = StmtTypeTable::GetAllStmtsOfType(SynonymType::ASSIGN);
	vector<int> results;

	for (int currentStmt = 0; currentStmt < assignmentStmts.size(); currentStmt++) {
		StmtTNode& currentStmtTNode = Program::GetStmtFromNumber(assignmentStmts[currentStmt]);
		if (MatchPatternAtLeaves(&currentStmtTNode, object)) {
			results.push_back(assignmentStmts[currentStmt]);
		}
	}

	return results;
}
