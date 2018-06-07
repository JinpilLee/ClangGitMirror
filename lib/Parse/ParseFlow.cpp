//===--- ParseFlow.cpp - Flow directives parsing --------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
/// \file
/// This file implements parsing of all Flow directives and clauses.
///
//===----------------------------------------------------------------------===//

#include "clang/Basic/FlowKinds.h"
#include "clang/Parse/ParseDiagnostic.h"
#include "clang/Parse/Parser.h"

using namespace clang;

static FlowDirectiveKind getFlowDirectiveKind(StringRef Str) {
  return llvm::StringSwitch<FlowDirectiveKind>(Str)
           .Case("region", FLOWD_REGION)
           .Case("offload", FLOWD_OFFLOAD)
           .Default(FLOWD_UNKNOWN);
}

/// Parsing of executable Flow directives.
///
///       region-directive:
///         annot_pragma_flow 'region'
///         annot_pragma_flow_end
///
///       offload-directive:
///         annot_pragma_flow 'offload'
///         annot_pragma_openmp_end
///
StmtResult Parser::ParseFlowDirective() {
  StmtResult Directive = StmtError();

  SourceLocation Loc = ConsumeAnnotationToken(), EndLoc;
  Token Tok = getCurToken();
  auto DKind =
    Tok.isAnnotation()
      ? FLOWD_UNKNOWN
      : getFlowDirectiveKind(getPreprocessor().getSpelling(Tok));

  StmtResult AssociatedStmt;
  switch (DKind) {
  case FLOWD_REGION:
  case FLOWD_OFFLOAD:
    SkipUntil(tok::annot_pragma_flow_end, StopBeforeMatch);
    EndLoc = ConsumeAnnotationToken();
    AssociatedStmt = ParseStatement();
    return Actions.ActOnFlowExecutableDirective(DKind, AssociatedStmt.get(),
                                                Loc, EndLoc);
  case FLOWD_UNKNOWN:
  default:
    Diag(Loc, diag::err_flow_unknown_directive);
    SkipUntil(tok::annot_pragma_flow_end);
    break;
  }

  return Directive;
}
