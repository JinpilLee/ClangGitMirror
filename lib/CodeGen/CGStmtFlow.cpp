//===--- CGStmtFlow.cpp - Emit LLVM Code from Statements ------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This contains code to emit Flow nodes as LLVM code.
//
//===----------------------------------------------------------------------===//

#include "CodeGenFunction.h"
#include "clang/AST/StmtFlow.h"

using namespace clang;
using namespace CodeGen;

void CodeGenFunction::EmitFlowOffloadDirective(const FlowOffloadDirective &S) {
// FIXME implement
  return;
}
