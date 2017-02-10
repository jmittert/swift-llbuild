//===- unittests/BuildSystem/BuildValueTest.cpp ---------------------------===//
//
// This source file is part of the Swift.org open source project
//
// Copyright (c) 2016 Apple Inc. and the Swift project authors
// Licensed under Apache License v2.0 with Runtime Library Exception
//
// See http://swift.org/LICENSE.txt for license information
// See http://swift.org/CONTRIBUTORS.txt for the list of Swift project authors
//
//===----------------------------------------------------------------------===//

#include "llbuild/BuildSystem/BuildValue.h"

#include "gtest/gtest.h"

using namespace llbuild;
using namespace llbuild::buildsystem;
using namespace llvm;

namespace {

TEST(BuildValueTest, virtualValueSerialization) {
  // Check that two identical values are equivalent.
  {
    BuildValue a = BuildValue::makeVirtualInput();
    EXPECT_EQ(a.toData(), BuildValue::makeVirtualInput().toData());
  }

  // Check that a moved complex value is equivalent.
  {
    BuildValue tmp = BuildValue::makeVirtualInput();
    BuildValue a = std::move(tmp);
    EXPECT_EQ(a.toData(), BuildValue::makeVirtualInput().toData());
  }

  // Check that an rvalue initialized complex value is equivalent.
  {
    BuildValue tmp = BuildValue::makeVirtualInput();
    BuildValue a{ std::move(tmp) };
    EXPECT_EQ(a.toData(), BuildValue::makeVirtualInput().toData());
  }

  // Check that a round-tripped value is equivalent.
  EXPECT_EQ(BuildValue::makeVirtualInput().toData(),
            BuildValue::fromData(
                BuildValue::makeVirtualInput().toData()).toData());
}

TEST(BuildValueTest, commandValueSingleOutputSerialization) {
  uint64_t signature = 0xDEADBEEF;
  basic::FileInfo infos[1] = {};
  infos[0].size = 1;
  
  // Check that two identical values are equivalent.
  {
    BuildValue a = BuildValue::makeSuccessfulCommand(infos, signature);
    EXPECT_EQ(a.toData(),
              BuildValue::makeSuccessfulCommand(infos, signature).toData());
  }

  // Check that a moved complex value is equivalent.
  {
    BuildValue tmp = BuildValue::makeSuccessfulCommand(infos, signature);
    BuildValue a = std::move(tmp);
    EXPECT_EQ(a.toData(),
              BuildValue::makeSuccessfulCommand(infos, signature).toData());
  }

  // Check that an rvalue initialized complex value is equivalent.
  {
    BuildValue tmp = BuildValue::makeSuccessfulCommand(infos, signature);
    BuildValue a{ std::move(tmp) };
    EXPECT_EQ(a.toData(),
              BuildValue::makeSuccessfulCommand(infos, signature).toData());
  }

  // Check that a round-tripped value is equivalent.
  EXPECT_EQ(BuildValue::makeSuccessfulCommand(infos, signature).toData(),
            BuildValue::fromData(
                BuildValue::makeSuccessfulCommand(
                    infos, signature).toData()).toData());
}

TEST(BuildValueTest, commandValueMultipleOutputsSerialization) {
  uint64_t signature = 0xDEADBEEF;
  basic::FileInfo infos[2] = {};
  infos[0].size = 1;
  infos[1].size = 2;
  
  // Check that two identical values are equivalent.
  {
    BuildValue a = BuildValue::makeSuccessfulCommand(infos, signature);
    EXPECT_EQ(a.toData(),
              BuildValue::makeSuccessfulCommand(infos, signature).toData());
  }

  // Check that a moved complex value is equivalent.
  {
    BuildValue tmp = BuildValue::makeSuccessfulCommand(infos, signature);
    BuildValue a = std::move(tmp);
    EXPECT_EQ(a.toData(),
              BuildValue::makeSuccessfulCommand(infos, signature).toData());
  }

  // Check that an rvalue initialized complex value is equivalent.
  {
    BuildValue tmp = BuildValue::makeSuccessfulCommand(infos, signature);
    BuildValue a{ std::move(tmp) };
    EXPECT_EQ(a.toData(),
              BuildValue::makeSuccessfulCommand(infos, signature).toData());
  }

  // Check that a round-tripped value is equivalent.
  EXPECT_EQ(BuildValue::makeSuccessfulCommand(infos, signature).toData(),
            BuildValue::fromData(
                BuildValue::makeSuccessfulCommand(
                    infos, signature).toData()).toData());
}

}
