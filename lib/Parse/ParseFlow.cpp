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

#include "clang/Parse/ParseDiagnostic.h"
#include "clang/Parse/Parser.h"
#include <iostream>

using namespace clang;

namespace clang {
enum FlowDirectiveKind {
  FLOWD_REGION,
  FLOWD_OFFLOAD,
  FLOWD_UNKNOWN
};
} // end namespace clang

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

  SourceLocation Loc = ConsumeAnnotationToken();
  Token Tok = getCurToken();
  auto DKind =
    Tok.isAnnotation()
      ? FLOWD_UNKNOWN
      : getFlowDirectiveKind(getPreprocessor().getSpelling(Tok));

  switch (DKind) {
  case FLOWD_REGION:
    break;
  case FLOWD_OFFLOAD:
    break;
  case FLOWD_UNKNOWN:
  default:
    Diag(Loc, diag::err_flow_unknown_directive);
    SkipUntil(tok::annot_pragma_flow_end);
    break;
  }

  return Directive;
}
