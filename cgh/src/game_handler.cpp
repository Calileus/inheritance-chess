/// @file      game_handler.cpp
/// @namespace Chess
/// @brief     Implementation for Chess Game Handler (CGH).
/// @author    Calileus
/// @date      2026-01-22
/// @copyright 2026 Obsidian Honor Coders. Licensed under Apache 2.0.
/// @see       https://github.com/ObsidianHonorCoders/inheritance-chess
/// @details   Implements game orchestration and lifecycle management.

#include "game_handler.h"
#include <ctime>

namespace Chess
{

  ChessGameHandler::ChessGameHandler()
      : board_manager_(std::make_unique<ChessBoardManager>()), pieces_logic_(std::make_unique<ChessPiecesLogic>()),
        translation_unit_(std::make_unique<ChessTranslationUnit>())
  {
  }

  void ChessGameHandler::start_new_game()
  {
    current_grid_.initialize_standard_position();
    session_.game_id = "game_" + std::to_string(std::time(nullptr));
    session_.move_history.clear();
    session_.state = GameState::ONGOING;
  }

  void ChessGameHandler::load_game_from_fen(const std::string& fen)
  {
    current_grid_ = translation_unit_->fen_to_internal(fen);
    session_.move_history.clear();
    session_.state = GameState::ONGOING;
  }

  bool ChessGameHandler::make_move(const std::string& algebraic_move)
  {
    // TODO: Convert algebraic to Move and call make_move(const Move&)
    return false;
  }

  bool ChessGameHandler::make_move(const Move& move)
  {
    // TODO: Validate move, update grid, check for game end conditions
    return false;
  }

  std::string ChessGameHandler::get_current_fen() const { return translation_unit_->internal_to_fen(current_grid_); }

  std::vector<Move> ChessGameHandler::get_legal_moves() const
  {
    // TODO: Get all raw moves and filter by legality
    return {};
  }

  GameState ChessGameHandler::get_game_state() const { return session_.state; }

  void ChessGameHandler::start_timer(Color color)
  {
    // TODO: Start clock for color
  }

  void ChessGameHandler::stop_timer(Color color)
  {
    // TODO: Stop clock for color
  }

  std::chrono::milliseconds ChessGameHandler::get_time_remaining(Color color) const
  {
    return (color == Color::WHITE) ? session_.white_time : session_.black_time;
  }

} // namespace Chess
