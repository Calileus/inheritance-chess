/// @file      test_game_handler.cpp
/// @namespace Chess
/// @brief     Unit tests for Chess Game Handler.
/// @author    Calileus
/// @date      2026-01-22
/// @copyright 2026 Obsidian Honor Coders. Licensed under Apache 2.0.
/// @see       https://github.com/ObsidianHonorCoders/inheritance-chess
/// @details   Tests for game lifecycle and handler operations.

#include <gtest/gtest.h>
#include "../include/game_handler.h"

using namespace Chess;

class GameHandlerTest : public ::testing::Test
{
  protected:
    ChessGameHandler handler;

    void SetUp() override {}
};

TEST_F(GameHandlerTest, StartNewGame)
{
  handler.start_new_game();
  EXPECT_EQ(handler.get_game_state(), GameState::ONGOING);
}

TEST_F(GameHandlerTest, LoadFromFEN)
{
  std::string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  handler.load_game_from_fen(fen);
  EXPECT_EQ(handler.get_game_state(), GameState::ONGOING);
}

TEST_F(GameHandlerTest, GetLegalMoves)
{
  handler.start_new_game();
  // TODO: Test legal move generation
  // std::vector<Move> moves = handler.get_legal_moves();
}
