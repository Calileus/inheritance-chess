/// @file      pieces_logic.cpp
/// @namespace Chess
/// @brief     Implementation for Chess Pieces Logic (CPL).
/// @author    Calileus
/// @date      2026-01-22
/// @copyright 2026 Obsidian Honor Coders. Licensed under Apache 2.0.
/// @see       https://github.com/ObsidianHonorCoders/inheritance-chess
/// @details   Implements piece move generation and attack detection.

#include "pieces_logic.h"
#include "chess_pawn.h"
#include "chess_knight.h"
#include "chess_bishop.h"
#include "chess_rook.h"
#include "chess_queen.h"
#include "chess_king.h"
#include <memory>

namespace Chess
{

  bool ChessPiecesLogic::is_raw_logical_move(const Grid& grid, const Move& move) const
  {
    auto moves = list_raw_logical_moves(grid, move.start_pos);
    for (const auto& m : moves)
    {
      if (m.end_pos == move.end_pos && m.flags == move.flags)
      {
        return true;
      }
    }
    return false;
  }

  std::vector<Move> ChessPiecesLogic::list_raw_logical_moves(const Grid& grid, Position position) const
  {
    if (!grid.is_occupied(position))
    {
      return {};
    }

    const auto& piece = grid.get_piece(position);
    if (!piece.has_value())
    {
      return {};
    }

    switch (piece->type)
    {
    case PieceType::PAWN:
      return get_pawn_moves(grid, position);
    case PieceType::KNIGHT:
      return get_knight_moves(grid, position);
    case PieceType::BISHOP:
      return get_bishop_moves(grid, position);
    case PieceType::ROOK:
      return get_rook_moves(grid, position);
    case PieceType::QUEEN:
      return get_queen_moves(grid, position);
    case PieceType::KING:
      return get_king_moves(grid, position);
    default:
      return {};
    }
  }

  bool ChessPiecesLogic::is_square_attacked(const Grid& grid, Position square, Color by_color) const
  {
    // Check all pieces of the attacking color
    for (int file = 0; file < 8; file++)
    {
      for (int rank = 0; rank < 8; rank++)
      {
        Position pos(file, rank);
        if (grid.is_occupied(pos))
        {
          const auto& piece = grid.get_piece(pos);
          if (piece.has_value() && piece->color == by_color)
          {
            auto moves = list_raw_logical_moves(grid, pos);
            for (const auto& move : moves)
            {
              if (move.end_pos == square)
              {
                return true;
              }
            }
          }
        }
      }
    }
    return false;
  }

  std::vector<Move> ChessPiecesLogic::get_pawn_moves(const Grid& grid, Position pos) const
  {
    std::vector<Move> moves;
    const auto&       piece_opt = grid.get_piece(pos);
    if (!piece_opt.has_value())
    {
      return moves;
    }

    const auto& piece = piece_opt.value();
    auto        pawn  = std::make_unique<ChessPawn>(piece.color, pos);

    // Gather other pieces' positions and colors
    PositionList other_positions;
    ColorList    other_colors;

    for (int file = 0; file < 8; ++file)
    {
      for (int rank = 0; rank < 8; ++rank)
      {
        Position check_pos(file, rank);
        if (check_pos != pos && grid.is_occupied(check_pos))
        {
          const auto& other_piece = grid.get_piece(check_pos);
          if (other_piece.has_value())
          {
            other_positions.push_back(check_pos);
            other_colors.push_back(other_piece->color);
          }
        }
      }
    }

    PositionList pawn_moves;
    pawn->available_moves(pawn_moves, other_positions, other_colors, grid);

    // Convert PositionList to vector<Move>
    for (const auto& move_pos : pawn_moves)
    {
      Move move;
      move.start_pos = pos;
      move.end_pos   = move_pos;
      move.flags     = SpecialFlags::NONE;
      moves.push_back(move);
    }

    return moves;
  }

  std::vector<Move> ChessPiecesLogic::get_knight_moves(const Grid& grid, Position pos) const
  {
    std::vector<Move> moves;
    const auto&       piece_opt = grid.get_piece(pos);
    if (!piece_opt.has_value())
    {
      return moves;
    }

    const auto& piece  = piece_opt.value();
    auto        knight = std::make_unique<ChessKnight>(piece.color, pos);

    // Gather other pieces' positions and colors
    PositionList other_positions;
    ColorList    other_colors;

    for (int file = 0; file < 8; ++file)
    {
      for (int rank = 0; rank < 8; ++rank)
      {
        Position check_pos(file, rank);
        if (check_pos != pos && grid.is_occupied(check_pos))
        {
          const auto& other_piece = grid.get_piece(check_pos);
          if (other_piece.has_value())
          {
            other_positions.push_back(check_pos);
            other_colors.push_back(other_piece->color);
          }
        }
      }
    }

    PositionList knight_moves;
    knight->available_moves(knight_moves, other_positions, other_colors, grid);

    // Convert PositionList to vector<Move>
    for (const auto& move_pos : knight_moves)
    {
      Move move;
      move.start_pos = pos;
      move.end_pos   = move_pos;
      move.flags     = SpecialFlags::NONE;
      moves.push_back(move);
    }

    return moves;
  }

  std::vector<Move> ChessPiecesLogic::get_bishop_moves(const Grid& grid, Position pos) const
  {
    std::vector<Move> moves;
    const auto&       piece_opt = grid.get_piece(pos);
    if (!piece_opt.has_value())
    {
      return moves;
    }

    const auto& piece  = piece_opt.value();
    auto        bishop = std::make_unique<ChessBishop>(piece.color, pos);

    // Gather other pieces' positions and colors
    PositionList other_positions;
    ColorList    other_colors;

    for (int file = 0; file < 8; ++file)
    {
      for (int rank = 0; rank < 8; ++rank)
      {
        Position check_pos(file, rank);
        if (check_pos != pos && grid.is_occupied(check_pos))
        {
          const auto& other_piece = grid.get_piece(check_pos);
          if (other_piece.has_value())
          {
            other_positions.push_back(check_pos);
            other_colors.push_back(other_piece->color);
          }
        }
      }
    }

    PositionList bishop_moves;
    bishop->available_moves(bishop_moves, other_positions, other_colors, grid);

    // Convert PositionList to vector<Move>
    for (const auto& move_pos : bishop_moves)
    {
      Move move;
      move.start_pos = pos;
      move.end_pos   = move_pos;
      move.flags     = SpecialFlags::NONE;
      moves.push_back(move);
    }

    return moves;
  }

  std::vector<Move> ChessPiecesLogic::get_rook_moves(const Grid& grid, Position pos) const
  {
    std::vector<Move> moves;
    const auto&       piece_opt = grid.get_piece(pos);
    if (!piece_opt.has_value())
    {
      return moves;
    }

    const auto& piece = piece_opt.value();
    auto        rook  = std::make_unique<ChessRook>(piece.color, pos);

    // Gather other pieces' positions and colors
    PositionList other_positions;
    ColorList    other_colors;

    for (int file = 0; file < 8; ++file)
    {
      for (int rank = 0; rank < 8; ++rank)
      {
        Position check_pos(file, rank);
        if (check_pos != pos && grid.is_occupied(check_pos))
        {
          const auto& other_piece = grid.get_piece(check_pos);
          if (other_piece.has_value())
          {
            other_positions.push_back(check_pos);
            other_colors.push_back(other_piece->color);
          }
        }
      }
    }

    PositionList rook_moves;
    rook->available_moves(rook_moves, other_positions, other_colors, grid);

    // Convert PositionList to vector<Move>
    for (const auto& move_pos : rook_moves)
    {
      Move move;
      move.start_pos = pos;
      move.end_pos   = move_pos;
      move.flags     = SpecialFlags::NONE;
      moves.push_back(move);
    }

    return moves;
  }

  std::vector<Move> ChessPiecesLogic::get_queen_moves(const Grid& grid, Position pos) const
  {
    std::vector<Move> moves;
    const auto&       piece_opt = grid.get_piece(pos);
    if (!piece_opt.has_value())
    {
      return moves;
    }

    const auto& piece = piece_opt.value();
    auto        queen = std::make_unique<ChessQueen>(piece.color, pos);

    // Gather other pieces' positions and colors
    PositionList other_positions;
    ColorList    other_colors;

    for (int file = 0; file < 8; ++file)
    {
      for (int rank = 0; rank < 8; ++rank)
      {
        Position check_pos(file, rank);
        if (check_pos != pos && grid.is_occupied(check_pos))
        {
          const auto& other_piece = grid.get_piece(check_pos);
          if (other_piece.has_value())
          {
            other_positions.push_back(check_pos);
            other_colors.push_back(other_piece->color);
          }
        }
      }
    }

    PositionList queen_moves;
    queen->available_moves(queen_moves, other_positions, other_colors, grid);

    // Convert PositionList to vector<Move>
    for (const auto& move_pos : queen_moves)
    {
      Move move;
      move.start_pos = pos;
      move.end_pos   = move_pos;
      move.flags     = SpecialFlags::NONE;
      moves.push_back(move);
    }

    return moves;
  }

  std::vector<Move> ChessPiecesLogic::get_king_moves(const Grid& grid, Position pos) const
  {
    std::vector<Move> moves;
    const auto&       piece_opt = grid.get_piece(pos);
    if (!piece_opt.has_value())
    {
      return moves;
    }

    const auto& piece = piece_opt.value();
    auto        king  = std::make_unique<ChessKing>(piece.color, pos);

    // Gather other pieces' positions and colors
    PositionList other_positions;
    ColorList    other_colors;

    for (int file = 0; file < 8; ++file)
    {
      for (int rank = 0; rank < 8; ++rank)
      {
        Position check_pos(file, rank);
        if (check_pos != pos && grid.is_occupied(check_pos))
        {
          const auto& other_piece = grid.get_piece(check_pos);
          if (other_piece.has_value())
          {
            other_positions.push_back(check_pos);
            other_colors.push_back(other_piece->color);
          }
        }
      }
    }

    PositionList king_moves;
    king->available_moves(king_moves, other_positions, other_colors, grid);

    // Convert PositionList to vector<Move>
    for (const auto& move_pos : king_moves)
    {
      Move move;
      move.start_pos = pos;
      move.end_pos   = move_pos;
      move.flags     = SpecialFlags::NONE;
      moves.push_back(move);
    }

    return moves;
  }

  std::vector<Move> ChessPiecesLogic::get_sliding_moves(const Grid&                             grid,
                                                        Position                                pos,
                                                        const std::vector<std::pair<int, int>>& directions) const
  {
    // TODO: Implement sliding move logic (for bishops, rooks, queens)
    return {};
  }

} // namespace Chess
