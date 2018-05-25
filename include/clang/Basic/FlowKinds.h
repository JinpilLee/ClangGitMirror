//===--- FlowKinds.h - Flow enums -------------------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Defines some Flow-specific enums and functions.
///
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_BASIC_FLOWKINDS_H
#define LLVM_CLANG_BASIC_FLOWKINDS_H

namespace clang {

enum FlowDirectiveKind {
  FLOWD_REGION,
  FLOWD_OFFLOAD,
  FLOWD_UNKNOWN
};

} // end namespace clang

#endif // LLVM_CLANG_BASIC_FLOWKINDS_H
