/// @file         p_test_board.cpp
/// @brief        Unit tests for the Board class
/// @project      Inheritance Chess
/// @organization Obsidian Honor Coders
/// @author       Calileus
/// @details      Test suite for Board class functionality including initialization,
///               piece management, and board display operations.
/// @date         2026-02-09
/// @copyright    2026 Obsidian Honor Coders
/// @license      Apache License 2.0 - http://www.apache.org/licenses/LICENSE-2.0
/// @note         Licensed under the Apache License, Version 2.0 (the "License");
///               you may not use this file except in compliance with the License.

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "board.hpp"

class BoardTest : public ::testing::Test
{
  protected:
    void SetUp() override { p_test_board = new Board(); }
    void TearDown() override { delete p_test_board; }

    Board* p_test_board;
};

/// @brief   Test board creation
/// @details Verifies that a new board is not null.
TEST_F(BoardTest, CreationState)
{
  // Expect a valid pointer from the SetUp (Not Equal nullptr)
  EXPECT_NE(p_test_board, nullptr);
}

/// @brief   Test board display functionality
/// @details Verifies that the board display method executes without errors
TEST_F(BoardTest, DisplayEmptyBoard)
{
  // Test that display doesn't throw exceptions
  EXPECT_NO_THROW(p_test_board->display());
}

/// @brief   Test standard chess setup
/// @details Verifies that the board correctly initializes with standard chess pieces
TEST_F(BoardTest, DisplayStandardSetup)
{
  // The board should have 32 pieces in standard setup
  // This is a basic test - we can expand it to count pieces check specific positions
  // No exeptions are expected from this function
  EXPECT_NO_THROW(p_test_board->initializeStandardSetup());
  EXPECT_NO_THROW(p_test_board->display());
}
