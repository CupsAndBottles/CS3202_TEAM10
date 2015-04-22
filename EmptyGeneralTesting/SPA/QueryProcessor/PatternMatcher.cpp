#include <string>
#include <vector>
#include "PatternMatcher.h"
#include "..\Program\TNode\TNode.h"
#include "..\Program\Program.h"
#include "..\PKB\StmtTypeTable.h"
#include "..\Parser\Tokenizer.h"
#include "..\Parser\Parser.h"
#include "Grammar.h"

#include <iostream>
#include <stdio.h>

using namespace std;

bool PatternMatcher::MatchPatternAtLeaves(TNode* node, Pattern object, bool partialMatch) {
	// match tree
	// if no need to match children, return match
	
	bool match = (node->GetContent() == object.expr);

	// check for children
	// if both empty, return match
	// if pattern has children but not tree, return false
	// if tree has children but not pattern. return partialMatch && match
	// if both have children, match left tree and right tree

	bool hasChildNodes = false;
	vector<TNode*> children;

	if (node->HasChildren()) {
		children = node->GetChildren();
		if (children.size() != 2) {
			hasChildNodes = false;
		} else {
			hasChildNodes = true;
		}
	}

	bool hasChildPatterns = (object.leftPattern != nullptr) && (object.rightPattern != nullptr);
	if (hasChildPatterns && hasChildNodes) {
		// match subtrees
		match = (match && MatchPatternAtLeaves(children[0], *object.leftPattern, false) && MatchPatternAtLeaves(children[1], *object.rightPattern, false));
		if (!match && partialMatch) {
			// recursive call
			bool matchLeft = MatchPatternAtLeaves(children[0], object, partialMatch);
			bool matchRight = MatchPatternAtLeaves(children[1], object, partialMatch);

			return (matchLeft || matchRight);
		} else {
			return match;
		}
	} else if (!hasChildPatterns && hasChildNodes) {
		if (match && partialMatch) {
			return true;
		} else if (!match && partialMatch) {
			// recursive call
			bool matchLeft = MatchPatternAtLeaves(children[0], object, partialMatch);
			bool matchRight = MatchPatternAtLeaves(children[1], object, partialMatch);

			return (matchLeft || matchRight);
		} else {
			return false;
		}
	} else if (hasChildPatterns && !hasChildNodes) {
		return false;
	} else if (!hasChildPatterns && !hasChildNodes) {
		return match;
	} else {
		return false;
	}
}

vector<int> PatternMatcher::MatchPatternFromRoot(Pattern object, bool partialMatch) {
	vector<int> assignmentStmts = StmtTypeTable::GetAllStmtsOfType(SynonymType::ASSIGN);
	return MatchPatternFromRoot(object, partialMatch, assignmentStmts);
}

vector<int> PatternMatcher::MatchPatternFromRoot(Pattern object, bool partialMatch, vector<int> stmtsToMatch) {
	// printf("1 %s 2 %s 3 %s\n", object.expr.c_str(), object.leftPattern->expr.c_str(), object.rightPattern->expr.c_str());

	vector<int> results;

	if (object.expr == "") return results; // malformed object, or blank object.

	for each (int currentStmt in stmtsToMatch) {
		if (!StmtTypeTable::CheckIfStmtOfType(currentStmt, ASSIGN)) continue;
		TNode& currentStmtTNode = Program::GetStmtFromNumber(currentStmt);
		// go to RHS (ignore left of assignment statement. Match expression)
		if (MatchPatternAtLeaves(&currentStmtTNode.GetChild(1), object, partialMatch)) {
			results.push_back(currentStmt);
		}
	}

	return results;
}

Pattern PatternMatcher::CreatePatternObject(string expr)
{
	class Helper {
		deque<Token> tokens;
		Pattern* emptyPattern;
	public:
		Helper(string expr) {
			expr.push_back(';');
			vector<Token> tokenVector = Tokenizer::Tokenize(expr);
			tokens = deque<Token>(tokenVector.begin(), tokenVector.end());
			emptyPattern = new Pattern();
		}

		Token PeekAtTopToken() {
			return tokens.front();
		}

		Token ConsumeTopToken() {
			Token token = tokens.front();
			tokens.pop_front();
			return token;
		}

		bool TopTokenIsType(Token::Type type) {
			return (tokens.front().type == type);
		}

		Token ConsumeTopTokenOfType(Token::Type type) {
			// verifies that top token is of given type
			// then consumes it
			if (!TopTokenIsType(type)) throw (string) "Error in parsing pattern.";
			return ConsumeTopToken();
		}

		Pattern* ParseExpr(bool isBracket) {
			Token::Type terminatingCondition = isBracket ? Token::CLOSE_BRACE : Token::END_OF_STMT;
			Pattern* result = emptyPattern;
			while (!TopTokenIsType(terminatingCondition)) {
				if (result->expr == "") { // empty pattern
					if (TopTokenIsType(Token::OPEN_BRACE)) {
						ConsumeTopTokenOfType(Token::OPEN_BRACE);
						result = ParseExpr(true);
					} else {
						result = new Pattern(ConsumeTopToken().content);
					}
				} else {
					result = ParseExpr(result, isBracket);
				}
			}
			ConsumeTopTokenOfType(terminatingCondition);
			return result;
		}

		Pattern* ParseExpr(Pattern* LHS, bool isBracket) {
			// if next op is of lower precedence, construct RHS and return
			// if next op is of equal precedence, construct and loop
			// if next op is of higher precedence, perform recursive call
			// since all operations are left associative, no attempt to worry about
			//		assoiciativity is made

			Token::Type terminatingCondition = isBracket ? Token::CLOSE_BRACE : Token::END_OF_STMT;

			if (PeekAtTopToken().type == terminatingCondition) {
				return LHS;
			}

			// TODO combine operator token types into one type for type checking.
			Token op1 = ConsumeTopToken();
			Pattern* RHS;
			if (TopTokenIsType(Token::OPEN_BRACE)) {
				ConsumeTopTokenOfType(Token::OPEN_BRACE);
				RHS = ParseExpr(true);
			} else {
				RHS = new Pattern(ConsumeTopToken().content);
			}

			Token nextOp = PeekAtTopToken(); // peek
			int comparison = Parser::compare(op1.type, nextOp.type);

			if (comparison < 0) { // nextOp is of lower precedence than currentOp
				RHS = ParseExpr(RHS, isBracket);
			}
			Pattern* expression = new Pattern(op1.content, LHS, RHS);
			if (comparison > 0) { // nextOp is of higher precedence than currentOp
				return expression;
			} else { // equal precedence
				return ParseExpr(expression, isBracket);
			}
		}
	};

	Helper helper(expr);
	return *helper.ParseExpr(false);
}

vector<int> PatternMatcher::MatchPatternFromRoot(string expr) {
	vector<int> assignmentStmts = StmtTypeTable::GetAllStmtsOfType(SynonymType::ASSIGN);
	return MatchPatternFromRoot(expr, assignmentStmts);
}

vector<int> PatternMatcher::MatchPatternFromRoot(string expr, vector<int> stmtsToMatch) {
	Pattern patternObj = Pattern();
	bool notExactMatch = false;
	if (expr.length() != 0) {
		notExactMatch = expr.at(0) == '_';
		vector<char> resultantExpr;
		for each (char c in expr) {
			if (c != '\"' && c != '_') resultantExpr.push_back(c);
		}
		patternObj = CreatePatternObject(string(resultantExpr.begin(), resultantExpr.end()));
	}

	return MatchPatternFromRoot(patternObj, notExactMatch, stmtsToMatch);
}