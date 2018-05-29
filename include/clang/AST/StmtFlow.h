//===- StmtFlow.h - Classes for Flow directives  -----------------*- C++ -*-==//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
 // end //===----------------------------------------------------------------------===//
/// \file
/// This file defines Flow AST classes for executable directives and clauses.
///
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_AST_STMTFLOW_H
#define LLVM_CLANG_AST_STMTFLOW_H

#include "clang/AST/Stmt.h"
#include "clang/Basic/FlowKinds.h"

namespace clang {

class FlowExecutableDirective : public Stmt {
private:
  FlowDirectiveKind Kind;
  SourceLocation StartLoc;
  SourceLocation EndLoc;
  Stmt *AssociatedStmt;

protected:
  FlowExecutableDirective(StmtClass SC, FlowDirectiveKind K,
                          SourceLocation StartLoc, SourceLocation EndLoc,
                          Stmt *S)
      : Stmt(SC), Kind(K),
        StartLoc(std::move(StartLoc)), EndLoc(std::move(EndLoc)) {
    AssociatedStmt = S;
  }

public:
  void setAssociatedStmt(Stmt *S) {
    AssociatedStmt = S;
  }

  void setLocStart(SourceLocation Loc) { StartLoc = Loc; }
  void setLocEnd(SourceLocation Loc) { EndLoc = Loc; }

  const Stmt *getAssociatedStmt() const {
    return AssociatedStmt;
  }

  Stmt *getAssociatedStmt() {
    return AssociatedStmt;
  }

  SourceLocation getLocStart() const { return StartLoc; }
  SourceLocation getLocEnd() const { return EndLoc; }
  child_range children() {
    return child_range(&AssociatedStmt, &AssociatedStmt + 1);
  }

  FlowDirectiveKind getDirectiveKind() const { return Kind; }

  static bool classof(const Stmt *S) {
    return S->getStmtClass() >= firstFlowExecutableDirectiveConstant &&
           S->getStmtClass() <= lastFlowExecutableDirectiveConstant;
  }
};

class FlowRegionDirective : public FlowExecutableDirective {
private:
  explicit FlowRegionDirective()
    : FlowExecutableDirective(FlowRegionDirectiveClass, FLOWD_REGION,
                              SourceLocation(), SourceLocation(), nullptr) {}

  FlowRegionDirective(SourceLocation StartLoc, SourceLocation EndLoc, Stmt *S)
    : FlowExecutableDirective(FlowRegionDirectiveClass, FLOWD_REGION,
                              StartLoc, EndLoc, S) {}

public:
  static FlowRegionDirective *
  Create(const ASTContext &C, SourceLocation StartLoc, SourceLocation EndLoc,
         Stmt *AssociatedStmt);

  static FlowRegionDirective *
  CreateEmpty(const ASTContext &C);

  static bool classof(const Stmt *T) {
    return T->getStmtClass() == FlowRegionDirectiveClass;
  }
};

class FlowOffloadDirective : public FlowExecutableDirective {
private:
  explicit FlowOffloadDirective()
    : FlowExecutableDirective(FlowOffloadDirectiveClass, FLOWD_OFFLOAD,
                              SourceLocation(), SourceLocation(), nullptr) {}

  FlowOffloadDirective(SourceLocation StartLoc, SourceLocation EndLoc, Stmt *S)
    : FlowExecutableDirective(FlowOffloadDirectiveClass, FLOWD_OFFLOAD,
                              StartLoc, EndLoc, S) {}

public:
  static FlowOffloadDirective *
  Create(const ASTContext &C, SourceLocation StartLoc, SourceLocation EndLoc,
         Stmt *AssociatedStmt);

  static FlowOffloadDirective *
  CreateEmpty(const ASTContext &C);

  static bool classof(const Stmt *T) {
    return T->getStmtClass() == FlowOffloadDirectiveClass;
  }
};

} // end namespace clang

#endif // LLVM_CLANG_AST_STMTFLOW_H
