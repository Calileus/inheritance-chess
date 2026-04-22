/// @file      game_handler.h
/// @namespace Chess
/// @brief     Chess Game Handler (CGH) - The Orchestrator.
/// @author    Calileus
/// @date      2026-01-22
/// @copyright 2026 Obsidian Honor Coders. Licensed under Apache 2.0.
/// @see       https://github.com/ObsidianHonorCoders/inheritance-chess
/// @details   Manages the lifecycle of a chess game session and coordinates
///            all modules. Entry point for the application with unified interface
///            to game logic.

#ifndef ICHESS_CGH_GAME_HANDLER
#define ICHESS_CGH_GAME_HANDLER

#include "../cci/include/grid.h"
#include "../cci/include/move.h"
#include "../cbm/include/board_manager.h"
#include "../cpl/include/pieces_logic.h"
#include "../ctu/include/translation_unit.h"
#include <chrono>
#include <memory>
#include <string>
#include <vector>

namespace Chess
{

  /// @struct GameSession
  /// @brief  Metadata for a chess game session.
  struct GameSession
  {
      std::string               game_id;                    ///< Unique game identifier
      std::vector<Move>         move_history;               ///< History of all moves played
      std::chrono::milliseconds white_time{600000};         ///< White player time (default 10 min)
      std::chrono::milliseconds black_time{600000};         ///< Black player time (default 10 min)
      GameState                 state = GameState::ONGOING; ///< Current game state
  };

  /// @class   ChessGameHandler
  /// @brief   Orchestrates chess game flow and coordinates all modules.
  /// @details The ChessGameHandler acts as the main entry point, managing game
  ///          lifecycle, coordinating CCI, CPL, CBM, and CTU modules, and
  ///          handling time control. Provides facade pattern interface.
  class ChessGameHandler
  {
    public:
      /// @brief Constructor - initializes all submodules.
      ChessGameHandler();

      /// @brief Start a new game from standard position.
      void start_new_game();

      /// @brief Load game from FEN string.
      void load_game_from_fen(const std::string& fen);

      /// @brief Make a move using algebraic notation.
      bool make_move(const std::string& algebraic_move);

      /// @brief Make a move using Move structure.
      bool make_move(const Move& move);

      /// @brief Get current position as FEN.
      std::string get_current_fen() const;

      /// @brief Get all legal moves in current position.
      std::vector<Move> get_legal_moves() const;

      /// @brief Get current game state.
      GameState get_game_state() const;

      /// @brief Start timer for a color.
      void start_timer(Color color);

      /// @brief Stop timer for a color.
      void stop_timer(Color color);

      /// @brief Get time remaining for a color.
      std::chrono::milliseconds get_time_remaining(Color color) const;

    private:
      std::unique_ptr<ChessBoardManager>    board_manager_;    ///< Board rule enforcement
      std::unique_ptr<ChessPiecesLogic>     pieces_logic_;     ///< Piece move generation
      std::unique_ptr<ChessTranslationUnit> translation_unit_; ///< Notation translation

      Grid        current_grid_; ///< Current board state
      GameSession session_;      ///< Game session metadata
  };

} // namespace Chess

#endif // ICHESS_CGH_GAME_HANDLER
