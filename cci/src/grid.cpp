/// @file      grid.cpp
/// @namespace Chess
/// @brief     Implementation for Chess Common Interface Grid structure.
/// @author    Calileus
/// @date      2026-01-22
/// @copyright 2026 Obsidian Honor Coders. Licensed under Apache 2.0.
/// @see       https://github.com/ObsidianHonorCoders/inheritance-chess
/// @details   Implements grid initialization and management functions.

#include "grid.h"

namespace Chess
{

  /// @brief Check if a square is attacked by a color.
  /// @note This is a placeholder. The actual implementation will be
  ///       provided by the ChessPiecesLogic (CPL) module.
  bool Grid::is_square_attacked_by(const Position& pos, Color attacking_color) const
  {
    // TODO: This will be implemented by CPL module
    // For now, return false
    return false;
  }

  /// @brief Initialize grid to standard starting position.
  void Grid::initialize_standard_position()
  {
    // Clear the board
    for (int file = 0; file < 8; file++)
    {
      for (int rank = 0; rank < 8; rank++)
      {
        board[file][rank] = std::nullopt;
      }
    }

    // Set up pawns (rank 1 for white, rank 6 for black)
    for (int file = 0; file < 8; file++)
    {
      board[file][1] = PieceProperties{PieceType::PAWN, Color::WHITE, Position{file, 1}, false, false};
      board[file][6] = PieceProperties{PieceType::PAWN, Color::BLACK, Position{file, 6}, false, false};
    }

    // Helper lambda to setup back ranks
    auto setup_back_rank = [this](int rank, Color color)
    {
      board[0][rank] = PieceProperties{PieceType::ROOK, color, Position{0, rank}};
      board[1][rank] = PieceProperties{PieceType::KNIGHT, color, Position{1, rank}};
      board[2][rank] = PieceProperties{PieceType::BISHOP, color, Position{2, rank}};
      board[3][rank] = PieceProperties{PieceType::QUEEN, color, Position{3, rank}};
      board[4][rank] = PieceProperties{PieceType::KING, color, Position{4, rank}};
      board[5][rank] = PieceProperties{PieceType::BISHOP, color, Position{5, rank}};
      board[6][rank] = PieceProperties{PieceType::KNIGHT, color, Position{6, rank}};
      board[7][rank] = PieceProperties{PieceType::ROOK, color, Position{7, rank}};
    };

    setup_back_rank(0, Color::WHITE);
    setup_back_rank(7, Color::BLACK);

    current_turn = Color::WHITE;
    flags        = GameFlags{}; // Reset to default castling rights
  }

} // namespace Chess
