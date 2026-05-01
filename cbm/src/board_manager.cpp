/// @file      board_manager.cpp
/// @namespace Chess
/// @brief     Implementation for Chess Board Manager (CBM).
/// @author    Calileus
/// @date      2026-01-22
/// @copyright 2026 Obsidian Honor Coders. Licensed under Apache 2.0.
/// @see       https://github.com/ObsidianHonorCoders/inheritance-chess
/// @details   Implements board management and game rule enforcement.

#include "board_manager.h"
#include <cmath>

namespace Chess
{

  bool ChessBoardManager::is_white_king_in_check(const Grid& grid) const
  {
    // TODO: Implementation requires CPL module for square attack detection
    return false;
  }

  bool ChessBoardManager::is_black_king_in_check(const Grid& grid) const
  {
    // TODO: Implementation requires CPL module for square attack detection
    return false;
  }

  bool ChessBoardManager::is_draw(const Grid& grid, Color color_turn) const
  {
    // TODO: Check for insufficient material, threefold repetition, fifty-move rule
    return false;
  }

  bool ChessBoardManager::validate_move(const Grid& grid, const Move& move) const
  {
    // Check if start position is valid and contains a piece
    if (!move.start_pos.is_valid() || !move.end_pos.is_valid())
    {
      return false;
    }

    const auto& piece_opt = grid.get_piece(move.start_pos);
    if (!piece_opt.has_value())
    {
      return false; // No piece at start position
    }

    const auto& piece_props = piece_opt.value();

    // Piece must belong to current player
    if (piece_props.color != grid.current_turn)
    {
      return false;
    }

    // Check if end position is either empty or contains opponent piece
    const auto& end_piece_opt = grid.get_piece(move.end_pos);
    if (end_piece_opt.has_value() && end_piece_opt->color == piece_props.color)
    {
      return false; // Can't capture own piece
    }

    // Validate piece-specific movement rules
    int file_diff = std::abs(move.end_pos.file - move.start_pos.file);
    int rank_diff = std::abs(move.end_pos.rank - move.start_pos.rank);

    switch (piece_props.type)
    {
    case PieceType::PAWN:
    {
      // Pawn moves forward based on color
      int direction = (piece_props.color == Color::WHITE) ? 1 : -1;
      int rank_move = move.end_pos.rank - move.start_pos.rank;

      // Must move in the correct direction
      if ((direction > 0 && rank_move <= 0) || (direction < 0 && rank_move >= 0))
      {
        return false;
      }

      // Check if it's a capture move
      if (end_piece_opt.has_value())
      {
        // Diagonal capture: move 1 square diagonally
        if (file_diff != 1 || std::abs(rank_move) != 1)
        {
          return false;
        }
      }
      else
      {
        // Non-capture: must move straight forward
        if (file_diff != 0)
        {
          return false;
        }

        // Can move 1 or 2 squares from starting position
        int max_move = (piece_props.has_moved) ? 1 : 2;
        if (std::abs(rank_move) > max_move || std::abs(rank_move) == 0)
        {
          return false;
        }

        // Check if path is clear for 2-square moves
        if (std::abs(rank_move) == 2)
        {
          Position mid(move.start_pos.file, move.start_pos.rank + direction);
          if (grid.is_occupied(mid))
          {
            return false;
          }
        }
      }
      break;
    }

    case PieceType::KNIGHT:
    {
      // Knight moves in L-shape: 2 squares in one direction, 1 in the other
      if (!((file_diff == 2 && rank_diff == 1) || (file_diff == 1 && rank_diff == 2)))
      {
        return false;
      }
      break;
    }

    case PieceType::BISHOP:
    {
      // Bishop moves diagonally
      if (file_diff != rank_diff || file_diff == 0)
      {
        return false;
      }
      // Check if path is clear
      int file_step = (move.end_pos.file > move.start_pos.file) ? 1 : -1;
      int rank_step = (move.end_pos.rank > move.start_pos.rank) ? 1 : -1;
      for (int f = move.start_pos.file + file_step, r = move.start_pos.rank + rank_step; f != move.end_pos.file;
           f += file_step, r += rank_step)
      {
        if (grid.is_occupied(Position(f, r)))
        {
          return false;
        }
      }
      break;
    }

    case PieceType::ROOK:
    {
      // Rook moves horizontally or vertically
      if ((file_diff == 0 && rank_diff == 0) || (file_diff != 0 && rank_diff != 0))
      {
        return false;
      }
      // Check if path is clear
      if (file_diff > 0)
      {
        int step = (move.end_pos.file > move.start_pos.file) ? 1 : -1;
        for (int f = move.start_pos.file + step; f != move.end_pos.file; f += step)
        {
          if (grid.is_occupied(Position(f, move.start_pos.rank)))
          {
            return false;
          }
        }
      }
      if (rank_diff > 0)
      {
        int step = (move.end_pos.rank > move.start_pos.rank) ? 1 : -1;
        for (int r = move.start_pos.rank + step; r != move.end_pos.rank; r += step)
        {
          if (grid.is_occupied(Position(move.start_pos.file, r)))
          {
            return false;
          }
        }
      }
      break;
    }

    case PieceType::QUEEN:
    {
      // Queen moves like rook or bishop
      if (file_diff == 0 && rank_diff == 0)
      {
        return false;
      }
      if (file_diff != 0 && rank_diff != 0 && file_diff != rank_diff)
      {
        return false;
      }
      // Check diagonal path
      if (file_diff == rank_diff && file_diff != 0)
      {
        int file_step = (move.end_pos.file > move.start_pos.file) ? 1 : -1;
        int rank_step = (move.end_pos.rank > move.start_pos.rank) ? 1 : -1;
        for (int f = move.start_pos.file + file_step, r = move.start_pos.rank + rank_step; f != move.end_pos.file;
             f += file_step, r += rank_step)
        {
          if (grid.is_occupied(Position(f, r)))
          {
            return false;
          }
        }
      }
      // Check straight path
      if (file_diff > 0)
      {
        int step = (move.end_pos.file > move.start_pos.file) ? 1 : -1;
        for (int f = move.start_pos.file + step; f != move.end_pos.file; f += step)
        {
          if (grid.is_occupied(Position(f, move.start_pos.rank)))
          {
            return false;
          }
        }
      }
      if (rank_diff > 0)
      {
        int step = (move.end_pos.rank > move.start_pos.rank) ? 1 : -1;
        for (int r = move.start_pos.rank + step; r != move.end_pos.rank; r += step)
        {
          if (grid.is_occupied(Position(move.start_pos.file, r)))
          {
            return false;
          }
        }
      }
      break;
    }

    case PieceType::KING:
    {
      // King moves 1 square in any direction
      if (file_diff > 1 || rank_diff > 1)
      {
        return false;
      }
      // King must actually move
      if (file_diff == 0 && rank_diff == 0)
      {
        return false;
      }
      break;
    }

    default:
      return false;
    }

    // TODO: Verify move doesn't leave king in check
    return true;
  }

  bool ChessBoardManager::is_checkmate(const Grid& grid, Color color) const
  {
    // TODO: Check if king is in check and has no legal moves
    return false;
  }

  bool ChessBoardManager::is_stalemate(const Grid& grid, Color color) const
  {
    // TODO: Check if king is not in check but has no legal moves
    return false;
  }

  bool ChessBoardManager::is_king_in_check(const Grid& grid, Color king_color) const
  {
    // TODO: Find king position and check if attacked
    return false;
  }

} // namespace Chess
