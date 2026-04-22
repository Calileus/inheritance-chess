/// @file      grid.h
/// @namespace Chess
/// @brief     Chess Common Interface (CCI) - Grid Structure.
/// @author    Calileus
/// @date      2026-01-22
/// @copyright 2026 Obsidian Honor Coders. Licensed under Apache 2.0.
/// @see       https://github.com/ObsidianHonorCoders/inheritance-chess
/// @details   Defines the Grid struct which represents the complete chess board
///            state with 8x8 piece positions and game metadata.

#ifndef ICHESS_CCI_GRID
#define ICHESS_CCI_GRID

#include "chess_types.h"
#include "position.h"
#include <array>
#include <optional>

namespace Chess
{

  /// @struct PieceProperties
  /// @brief  Represents a piece on the board with its metadata.
  struct PieceProperties
  {
      PieceType type  = PieceType::PAWN;
      Color     color = Color::WHITE;
      Position  position;
      bool      has_moved             = false; ///< Used for castling and pawn double-move rules
      bool      en_passant_vulnerable = false; ///< Set when pawn can be captured en passant

      /// @brief Check if square is empty (default state).
      bool is_empty() const { return type == PieceType::PAWN && color == Color::WHITE && !has_moved; }
  };

  /// @struct Grid
  /// @brief  Represents the complete state of a chess board.
  /// @details The grid is an 8x8 array where board[file][rank] represents a square.
  ///          File: 0-7 (a-h, columns), Rank: 0-7 (1-8, rows).
  struct Grid
  {
      std::array<std::array<std::optional<PieceProperties>, 8>, 8> board;

      Color     current_turn = Color::WHITE; ///< Whose turn it is
      GameFlags flags;                       ///< Castling rights, en passant, halfmove/fullmove counters

      /// @brief Get piece at a specific position (if any).
      const std::optional<PieceProperties>& get_piece(const Position& pos) const
      {
        if (!pos.is_valid())
        {
          static const std::optional<PieceProperties> empty;
          return empty;
        }
        return board[pos.file][pos.rank];
      }

      /// @brief Set piece at a specific position.
      void set_piece(const Position& pos, const std::optional<PieceProperties>& piece)
      {
        if (pos.is_valid())
        {
          board[pos.file][pos.rank] = piece;
        }
      }

      /// @brief Clear a square (remove the piece).
      void clear_square(const Position& pos)
      {
        if (pos.is_valid())
        {
          board[pos.file][pos.rank] = std::nullopt;
        }
      }

      /// @brief Check if a square is occupied.
      bool is_occupied(const Position& pos) const
      {
        if (!pos.is_valid())
          return false;
        return board[pos.file][pos.rank].has_value();
      }

      /// @brief Check if a square is attacked by a color (to be implemented by CBM).
      bool is_square_attacked_by(const Position& pos, Color attacking_color) const;

      /**
       * @brief Switch the current turn
       */
      void switch_turn() { current_turn = (current_turn == Color::WHITE) ? Color::BLACK : Color::WHITE; }

      /// @brief Initialize grid to standard starting position.
      void initialize_standard_position();
  };

} // namespace Chess

#endif // ICHESS_CCI_GRID
