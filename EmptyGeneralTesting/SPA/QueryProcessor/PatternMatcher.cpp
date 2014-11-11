#include <string>
#include <vector>
#include "PatternMatcher.h"
#include "../Program/TNode/TNode.h"
#include "../Program/TNode/ProcedureTNode.h"
#include "../Program/TNode/AssignmentTNode.h"
#include "../Program/TNode/WhileTNode.h"
#include "../Program/Program.h"

#include <iostream>
#include <stdio.h>

using namespace std;
/*
vector<int> PatternMatcher::MatchPatternAtLeaves(TNode* node, QueryObject object) {
    vector<int> results;
    TNode current = node;

    if (!current.GetChildren().empty()) {
        vector<TNode*> children = current.GetChildren();    

        for (int i=0 ; i<children.size(); i++) {
            TNode* child = children.at(i);
            if (child->GetType() == TNode::Type::ASSIGNMENT) {
                if (child->GetChild(0).GetContent() == object.leftVar) {
                    //condition true
                }
                if (child->GetChild(1).GetContent() == object.rightVar) {
                    //condition true
                }

                //get line number;
                int stmt = dynamic_cast<StmtTNode*>(child)->GetLineNumber();
                results.push_back(stmt);
            }

            if (child->GetType() == TNode::Type::WHILE) {
            }
        
            PatternMatcher::MatchPatternAtLeaves(child, object);
        }
    }
    return results;
}

vector<int> PatternMatcher::MatchPatternFromRoot(QueryObject object) {
    printf("1 %s 2 %s 3 %s\n", object.expr.c_str(), object.leftVar.c_str(), object.rightVar.c_str());

    //TNode* current = root;

    ProgramTNode root = Program::GetASTRootNode();

    return PattterMatcher::MatchPatternAtLeaves(root, object);
}


int main() {

    QueryObject dummy;
    dummy.expr = "plus";
    dummy.leftVar = "x";
    dummy.rightVar = "y";

    string name = "testproc";

    //ProcedureTNode::ProcedureTNode root = new ProcedureTNode::TNode(name);
    //if(dummy.rightVar=="") printf("empty string!\n");
    PatternMatcher::MatchPattern(NULL, dummy);

    return 0;
}*/
