//===--- StmtFlow.cpp - Classes for Flow directives -----------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements the subclesses of Stmt class declared in StmtFlow.h
//
//===----------------------------------------------------------------------===//

#include "clang/AST/StmtFlow.h"
#include "clang/AST/ASTContext.h"

using namespace clang;

FlowOffloadDirective *
FlowOffloadDirective::Create(const ASTContext &C,
                             SourceLocation StartLoc, SourceLocation EndLoc,
                             Stmt *AssociatedStmt) {
  void *Mem = C.Allocate(sizeof(FlowOffloadDirective));
  FlowOffloadDirective *Dir =
    new (Mem) FlowOffloadDirective(StartLoc, EndLoc, AssociatedStmt);
  return Dir;
}

FlowOffloadDirective *
FlowOffloadDirective::CreateEmpty(const ASTContext &C) {
  void *Mem = C.Allocate(sizeof(FlowOffloadDirective));
  FlowOffloadDirective *Dir =
    new (Mem) FlowOffloadDirective();
  return Dir;
}
