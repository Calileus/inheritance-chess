/// @file      translation_unit.cpp
/// @namespace Chess
/// @brief     Implementation for Chess Translation Unit (CTU).
/// @author    Calileus
/// @date      2026-01-22
/// @copyright 2026 Obsidian Honor Coders. Licensed under Apache 2.0.
/// @see       https://github.com/ObsidianHonorCoders/inheritance-chess
/// @details   Implements notation parsing and conversion utilities.

#include "translation_unit.h"
#include <cctype>
#include <ctime>
#include <stdexcept>

namespace Chess
{

  Grid ChessTranslationUnit::fen_to_internal(const std::string& fen_string) const
  {
    // TODO: Parse FEN string and create initial Grid
    Grid grid;
    grid.initialize_standard_position();
    return grid;
  }

  std::string ChessTranslationUnit::internal_to_fen(const Grid& grid) const
  {
    // TODO: Convert Grid to FEN notation
    return "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  }

  Move ChessTranslationUnit::algebraic_to_move(const std::string& algebraic, const Grid& grid) const
  {
    // Handle long algebraic notation: e2e4, a7a5, etc.
    // Format: source_file (a-h) + source_rank (1-8) + dest_file (a-h) + dest_rank (1-8)
    
    if (algebraic.length() == 4)
    {
      // Parse source square
      char src_file_char = std::tolower(algebraic[0]);
      char src_rank_char = algebraic[1];
      
      // Parse destination square
      char dst_file_char = std::tolower(algebraic[2]);
      char dst_rank_char = algebraic[3];
      
      // Validate characters
      if (src_file_char >= 'a' && src_file_char <= 'h' &&
          src_rank_char >= '1' && src_rank_char <= '8' &&
          dst_file_char >= 'a' && dst_file_char <= 'h' &&
          dst_rank_char >= '1' && dst_rank_char <= '8')
      {
        // Convert to 0-based indices
        // Files: a-h -> 0-7
        // Ranks: 1-8 -> 0-7 (rank 1 is index 0, rank 8 is index 7)
        int src_file = src_file_char - 'a';
        int src_rank = src_rank_char - '1';
        int dst_file = dst_file_char - 'a';
        int dst_rank = dst_rank_char - '1';
        
        return Move(Position(src_file, src_rank), Position(dst_file, dst_rank));
      }
    }
    
    // TODO: Implement other algebraic notation formats
    // - Short algebraic (e4, Nf3, etc.)
    // - Castling (O-O, O-O-O)
    // - Captures and check notation (exd5+, etc.)
    
    return Move(); // Return empty move if parsing fails
  }

  std::string ChessTranslationUnit::move_to_algebraic(const Move& move, const Grid& grid) const
  {
    // Convert move to long algebraic notation: e2e4, a7a5, etc.
    // Format: source_file (a-h) + source_rank (1-8) + dest_file (a-h) + dest_rank (1-8)
    
    std::string result;
    
    // Validate move positions
    if (!move.start_pos.is_valid() || !move.end_pos.is_valid())
    {
      return ""; // Invalid move
    }
    
    // Convert source position to algebraic notation
    result += static_cast<char>('a' + move.start_pos.file);  // file (a-h)
    result += static_cast<char>('1' + move.start_pos.rank);  // rank (1-8)
    
    // Convert destination position to algebraic notation
    result += static_cast<char>('a' + move.end_pos.file);    // file (a-h)
    result += static_cast<char>('1' + move.end_pos.rank);    // rank (1-8)
    
    return result;
  }

  PieceType ChessTranslationUnit::char_to_piece_type(char c) const
  {
    switch (std::tolower(c))
    {
    case 'p':
      return PieceType::PAWN;
    case 'n':
      return PieceType::KNIGHT;
    case 'b':
      return PieceType::BISHOP;
    case 'r':
      return PieceType::ROOK;
    case 'q':
      return PieceType::QUEEN;
    case 'k':
      return PieceType::KING;
    default:
      throw std::invalid_argument("Invalid piece character");
    }
  }

  Color ChessTranslationUnit::char_to_color(char c) const { return std::isupper(c) ? Color::WHITE : Color::BLACK; }

  Position ChessTranslationUnit::algebraic_to_position(const std::string& pos) const
  {
    // TODO: Implement algebraic position parsing
    return Position(0, 0);
  }

  char ChessTranslationUnit::piece_type_to_char(PieceType type, Color color) const
  {
    char base;
    switch (type)
    {
    case PieceType::PAWN:
      base = 'P';
      break;
    case PieceType::KNIGHT:
      base = 'N';
      break;
    case PieceType::BISHOP:
      base = 'B';
      break;
    case PieceType::ROOK:
      base = 'R';
      break;
    case PieceType::QUEEN:
      base = 'Q';
      break;
    case PieceType::KING:
      base = 'K';
      break;
    default:
      base = '?';
      break;
    }
    return (color == Color::WHITE) ? base : (char)std::tolower(base);
  }

} // namespace Chess
