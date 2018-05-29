//===--- SemaFlow.cpp - Semantic Analysis for Flow constructs -------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
/// \file
/// This file implements semantic analysis for Flow directives and
/// clauses.
///
//===----------------------------------------------------------------------===//

#include "clang/AST/StmtFlow.h"
#include "clang/Sema/Sema.h"

using namespace clang;

StmtResult
Sema::ActOnFlowExecutableDirective(FlowDirectiveKind Kind,
                                   Stmt *AStmt,
                                   SourceLocation StartLoc,
                                   SourceLocation EndLoc) {
  switch (Kind) {
  case FLOWD_REGION:
    return ActOnFlowRegionDirective(AStmt, StartLoc, EndLoc);
  case FLOWD_OFFLOAD:
    return ActOnFlowOffloadDirective(AStmt, StartLoc, EndLoc);
  case FLOWD_UNKNOWN:
  default:
    llvm_unreachable("unkown flow directive");
  }
}

StmtResult
Sema::ActOnFlowRegionDirective(Stmt *AStmt,
                               SourceLocation StartLoc,
                               SourceLocation EndLoc) {
  return FlowRegionDirective::Create(Context, StartLoc, EndLoc, AStmt);
}

StmtResult
Sema::ActOnFlowOffloadDirective(Stmt *AStmt,
                                SourceLocation StartLoc,
                                SourceLocation EndLoc) {
  return FlowOffloadDirective::Create(Context, StartLoc, EndLoc, AStmt);
}
