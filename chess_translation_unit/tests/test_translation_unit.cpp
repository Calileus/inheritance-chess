/// @file      test_translation_unit.cpp
/// @namespace Chess
/// @brief     Unit tests for Chess Translation Unit.
/// @author    Calileus
/// @date      2026-01-22
/// @copyright 2026 Obsidian Honor Coders. Licensed under Apache 2.0.
/// @see       https://github.com/ObsidianHonorCoders/inheritance-chess
/// @details   Tests for notation conversion and parsing.

#include <gtest/gtest.h>
#include "../include/translation_unit.h"

using namespace Chess;

class TranslationUnitTest : public ::testing::Test
{
  protected:
    ChessTranslationUnit translator;

    void SetUp() override {}
};

TEST_F(TranslationUnitTest, FENToInternal)
{
  // TODO: Test FEN parsing
  // std::string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  // Grid grid = translator.fen_to_internal(fen);
}

TEST_F(TranslationUnitTest, InternalToFEN)
{
  // TODO: Test grid to FEN conversion
}
