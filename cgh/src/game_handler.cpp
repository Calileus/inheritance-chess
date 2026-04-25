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
#include <iostream>
#include <algorithm>

namespace Chess
{

  ChessGameHandler::ChessGameHandler()
      : board_manager_(std::make_unique<ChessBoardManager>()), pieces_logic_(std::make_unique<ChessPiecesLogic>()),
        translation_unit_(std::make_unique<ChessTranslationUnit>()), event_system_(std::make_unique<ChessEventSystem>())
  {
  }

  void ChessGameHandler::start_new_game()
  {
    current_grid_.initialize_standard_position();
    session_.game_id = "game_" + std::to_string(std::time(nullptr));
    session_.move_history.clear();
    session_.state      = GameState::ONGOING;
    session_.white_time = std::chrono::milliseconds(600000); // 10 minutes
    session_.black_time = std::chrono::milliseconds(600000); // 10 minutes
    
    // Emit game started event
    event_system_->emit_game_started(current_grid_);
  }

  void ChessGameHandler::load_game_from_fen(const std::string& fen)
  {
    current_grid_ = translation_unit_->fen_to_internal(fen);
    session_.move_history.clear();
    session_.state = GameState::ONGOING;
  }

  bool ChessGameHandler::make_move(const std::string& algebraic_move)
  {
    try
    {
      Move move = translation_unit_->algebraic_to_move(algebraic_move, current_grid_);
      return make_move(move);
    }
    catch (const std::exception& e)
    {
      std::cerr << "Invalid move: " << algebraic_move << " - " << e.what() << std::endl;
      return false;
    }
  }

  bool ChessGameHandler::make_move(const Move& move)
  {
    // Validate move using board manager
    if (!board_manager_->validate_move(current_grid_, move))
    {
      return false;
    }

    // Execute move on grid
    if (!execute_move_on_grid(move))
    {
      return false;
    }

    // Add to move history
    session_.move_history.push_back(move);

    // Emit move executed event
    event_system_->emit_move_executed(current_grid_, move, current_grid_.current_turn);

    // Switch turns
    Color old_turn = current_grid_.current_turn;
    current_grid_.switch_turn();

    // Emit turn changed event
    event_system_->emit_turn_changed(current_grid_, current_grid_.current_turn);

    // Check for game end conditions
    update_game_state();

    return true;
  }

  std::string ChessGameHandler::get_current_fen() const { return translation_unit_->internal_to_fen(current_grid_); }

  std::vector<Move> ChessGameHandler::get_legal_moves() const { return get_legal_moves(current_grid_); }

  std::vector<Move> ChessGameHandler::get_legal_moves(const Grid& grid) const
  {
    std::vector<Move> legal_moves;

    // Iterate through all squares on the board
    for (int file = 0; file < 8; ++file)
    {
      for (int rank = 0; rank < 8; ++rank)
      {
        Position pos(file, rank);

        // Check if square is occupied
        if (!grid.is_occupied(pos))
        {
          continue;
        }

        const auto& piece = grid.get_piece(pos);
        if (!piece.has_value())
        {
          continue;
        }

        // Only generate moves for the current player's pieces
        if (piece->color != grid.current_turn)
        {
          continue;
        }

        // Get raw logical moves from pieces logic
        auto raw_moves = pieces_logic_->list_raw_logical_moves(grid, pos);

        // Filter through board manager to ensure moves are legal (don't leave king in check)
        for (const auto& move : raw_moves)
        {
          if (board_manager_->validate_move(grid, move))
          {
            legal_moves.push_back(move);
          }
        }
      }
    }

    return legal_moves;
  }

  GameState ChessGameHandler::get_game_state() const { return session_.state; }

  void ChessGameHandler::start_timer(Color color)
  {
    // TODO: Implement timer functionality
    // This would require integrating with a timing library
  }

  void ChessGameHandler::stop_timer(Color color)
  {
    // TODO: Implement timer functionality
    // This would require integrating with a timing library
  }

  std::chrono::milliseconds ChessGameHandler::get_time_remaining(Color color) const
  {
    return (color == Color::WHITE) ? session_.white_time : session_.black_time;
  }

  void ChessGameHandler::display_board() const
  {
    // Simple text display adapted from existing Board patterns
    std::cout << "\n  a b c d e f g h\n";
    std::cout << " +-----------------+\n";

    for (int rank = 7; rank >= 0; --rank)
    {
      std::cout << rank + 1 << "|";
      for (int file = 0; file < 8; ++file)
      {
        Position    pos(file, rank);
        const auto& piece = current_grid_.get_piece(pos);

        if (piece.has_value())
        {
          char piece_char = get_piece_display_char(piece->type, piece->color);
          std::cout << " " << piece_char;
        }
        else
        {
          std::cout << " .";
        }
      }
      std::cout << " |\n";
    }

    std::cout << " +-----------------+\n";
    std::cout << "Turn: " << (current_grid_.current_turn == Color::WHITE ? "White" : "Black") << "\n";
  }

  const Grid& ChessGameHandler::get_current_grid() const { return current_grid_; }

  ChessEventSystem& ChessGameHandler::get_event_system() { return *event_system_; }

  bool ChessGameHandler::execute_move_on_grid(const Move& move)
  {
    // Get piece at start position
    auto piece = current_grid_.get_piece_at(move.start_pos);
    if (!piece)
    {
      return false;
    }

    // Handle special moves
    if (move.flags == SpecialFlags::CASTLE_KINGSIDE || move.flags == SpecialFlags::CASTLE_QUEENSIDE)
    {
      return execute_castling(move);
    }
    else if (move.flags == SpecialFlags::EN_PASSANT)
    {
      return execute_en_passant(move);
    }
    else if (move.flags == SpecialFlags::PROMOTION)
    {
      return execute_promotion(move);
    }

    // Regular move
    return execute_regular_move(move);
  }

  bool ChessGameHandler::execute_regular_move(const Move& move)
  {
    // Get piece at start position BEFORE clearing
    auto piece = current_grid_.get_piece_at(move.start_pos);
    if (!piece)
    {
      return false;
    }
    
    // Clear start position
    current_grid_.clear_square(move.start_pos);
    
    // Set piece at end position
    piece->set_position(move.end_pos);
    current_grid_.set_piece_for_test(move.end_pos, 
        Chess::PieceProperties{piece->get_type(), piece->get_color(), move.end_pos, true, false});
    
    return true;
  }

  bool ChessGameHandler::execute_castling(const Move& move)
  {
    // Move the king first
    auto king = current_grid_.get_piece_at(move.start_pos);
    if (!king)
    {
      return false;
    }
    
    // Clear king's starting position
    current_grid_.clear_square(move.start_pos);
    
    // Move king to end position
    king->set_position(move.end_pos);
    current_grid_.set_piece_for_test(move.end_pos, 
        Chess::PieceProperties{king->get_type(), king->get_color(), move.end_pos, true, false});
    
    // Determine rook movement based on castling type
    Position rook_start;
    Position rook_end;
    int rank = move.start_pos.rank; // Same rank as king
    
    if (move.flags == SpecialFlags::CASTLE_KINGSIDE)
    {
      // Kingside castling: Rook moves from h-file to f-file
      rook_start = Position(7, rank); // h-file
      rook_end = Position(5, rank);   // f-file
    }
    else // CASTLE_QUEENSIDE
    {
      // Queenside castling: Rook moves from a-file to d-file
      rook_start = Position(0, rank); // a-file
      rook_end = Position(3, rank);   // d-file
    }
    
    // Move the rook
    auto rook = current_grid_.get_piece_at(rook_start);
    if (rook)
    {
      current_grid_.clear_square(rook_start);
      rook->set_position(rook_end);
      current_grid_.set_piece_for_test(rook_end, 
          Chess::PieceProperties{rook->get_type(), rook->get_color(), rook_end, true, false});
    }
    
    return true;
  }

  bool ChessGameHandler::execute_en_passant(const Move& move)
  {
    // Move the pawn
    auto pawn = current_grid_.get_piece_at(move.start_pos);
    if (!pawn)
    {
      return false;
    }
    
    // Clear pawn's starting position
    current_grid_.clear_square(move.start_pos);
    
    // Move pawn to end position (empty square)
    pawn->set_position(move.end_pos);
    current_grid_.set_piece_for_test(move.end_pos, 
        Chess::PieceProperties{pawn->get_type(), pawn->get_color(), move.end_pos, true, false});
    
    // Capture the enemy pawn on the original rank
    // The captured pawn is at (end_pos.file, start_pos.rank)
    Position captured_pawn_pos(move.end_pos.file, move.start_pos.rank);
    current_grid_.clear_square(captured_pawn_pos);
    
    return true;
  }

  bool ChessGameHandler::execute_promotion(const Move& move)
  {
    // TODO: Implement promotion logic
    // This would involve replacing pawn with promotion piece
    return execute_regular_move(move);
  }

  void ChessGameHandler::update_game_state()
  {
    Chess::Color current_color  = current_grid_.current_turn;
    Chess::Color opponent_color = (current_color == Chess::Color::WHITE) ? Chess::Color::BLACK : Chess::Color::WHITE;

    // Check for checkmate
    if (board_manager_->is_checkmate(current_grid_, opponent_color))
    {
      session_.state = GameState::CHECKMATE;
      return;
    }

    // Check for stalemate
    if (board_manager_->is_stalemate(current_grid_, opponent_color))
    {
      session_.state = GameState::STALEMATE;
      return;
    }

    // Check for draw
    if (board_manager_->is_draw(current_grid_, current_color))
    {
      session_.state = GameState::DRAW_INSUFFICIENT_MATERIAL; // Default to insufficient material draw
      return;
    }

    // Game continues
    session_.state = GameState::ONGOING;
  }

  char ChessGameHandler::get_piece_display_char(Chess::PieceType type, Chess::Color color) const
  {
    // White pieces: uppercase, Black pieces: lowercase
    char base_char = ' ';
    switch (type)
    {
    case Chess::PieceType::PAWN:
      base_char = 'P';
      break;
    case Chess::PieceType::KNIGHT:
      base_char = 'N';
      break;
    case Chess::PieceType::BISHOP:
      base_char = 'B';
      break;
    case Chess::PieceType::ROOK:
      base_char = 'R';
      break;
    case Chess::PieceType::QUEEN:
      base_char = 'Q';
      break;
    case Chess::PieceType::KING:
      base_char = 'K';
      break;
    }

    return (color == Chess::Color::WHITE) ? base_char : static_cast<char>(tolower(base_char));
  }

} // namespace Chess
