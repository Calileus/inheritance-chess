/// @file      test_fen_parsing.cpp
/// @namespace Chess
/// @brief     Unit tests for FEN notation parsing.
/// @author    Calileus
/// @date      2026-01-22
/// @copyright 2026 Obsidian Honor Coders. Licensed under Apache 2.0.
/// @see       https://github.com/ObsidianHonorCoders/inheritance-chess
/// @details   Tests for Forsyth-Edwards Notation parsing and generation.

#include <gtest/gtest.h>
#include "../include/translation_unit.h"

using namespace Chess;

class FENParsingTest : public ::testing::Test
{
  protected:
    ChessTranslationUnit translator;

    void SetUp() override {}
};

TEST_F(FENParsingTest, StandardStartingPosition)
{
  // TODO: Test parsing standard starting position FEN
}

TEST_F(FENParsingTest, AfterOneMove)
{
  // TODO: Test parsing FEN after one move
}

TEST_F(FENParsingTest, ComplexPosition)
{
  // TODO: Test parsing complex mid-game position
}
