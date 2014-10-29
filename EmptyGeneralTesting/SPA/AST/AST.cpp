#pragma once

#include "AST.h"
#include "Token.h"
#include "TNode\ProcedureTNode.h"
#include "TNode\AssignmentTNode.h"
#include "TNode\ConstantTNode.h"
#include "TNode\IfTNode.h"
#include "TNode\WhileTNode.h"
#include "TNode\CallTNode.h"

AST::AST() {}

void AST::InitNewProgram(ProgramTNode program) {
	programs.push_back(program);
}

template<typename T>
T AST::typecast(TNode node) {
	return dynamic_cast<T>(node);
}
//
//TNode AST::CreateTNode(TNode::Type type, ...) {
//	va_list args;
//	va_start(args, type);
//
//	switch (type) {
//		case TNode::Procedure:
//			return ProcedureTNode(va_arg(args, TNode*), va_arg(args, ProcedureTNode*), va_arg(args, string), va_arg(args, StmtListTNode));
//		case TNode::Program:
//			return ProgramTNode(va_arg(args, vector<ProcedureTNode>));
//		case TNode::Assignment:
//			return AssignmentTNode(va_arg(args, StmtListTNode*), va_arg(args, StmtTNode*), va_arg(args, int), va_arg(args, StmtTNode*), va_arg(args, VariableTNode), va_arg(args, TNode));
//		case TNode::Variable:
//			return VariableTNode(va_arg(args, TNode*), va_arg(args, TNode*), va_arg(args, string));
//		case TNode::Constant:
//			return ConstantTNode(va_arg(args, BinaryTNode*), va_arg(args, TNode*), va_arg(args, int));
//		case TNode::BinaryOperator:
//			return BinaryTNode(va_arg(args, TNode*), va_arg(args, TNode*), va_arg(args, string), va_arg(args, TNode), va_arg(args, TNode));
//		case TNode::StmtList:
//			return StmtListTNode(va_arg(args, TNode*), va_arg(args, StmtListTNode*), va_arg(args, string), va_arg(args, vector<StmtTNode>));
//		case TNode::If:
//			return IfTNode(va_arg(args, StmtListTNode*), va_arg(args, StmtTNode*), va_arg(args, int), va_arg(args, StmtTNode*), va_arg(args, VariableTNode), va_arg(args, StmtListTNode), va_arg(args, StmtListTNode));
//		case TNode::While:
//			return WhileTNode(va_arg(args, StmtListTNode*), va_arg(args, StmtTNode*), va_arg(args, int), va_arg(args, StmtTNode*), va_arg(args, VariableTNode), va_arg(args, StmtListTNode));
//		case TNode::Call:
//			return CallTNode(va_arg(args, StmtListTNode*), va_arg(args, StmtTNode*), va_arg(args, int), va_arg(args, StmtTNode*), va_arg(args, string));
//		default:
//			throw (string) "Unexpected type.";
//	}
//}