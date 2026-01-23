/// ---------------------------------------------------------------------------------
/// @file      board.cpp
/// @author    Calileus (https://github.com/Calileus/inheritance-chess)
/// @brief     Chess board console representation and display.
/// @version   1.0
/// @date      2026-01-22
/// @copyright MIT License - see LICENSE file for details
/// ---------------------------------------------------------------------------------
#include "board.hpp"

static void clearBoard(Board& B)
{
  for (int i = 0; i < Board::BOARD_SIZE; i++)
  {
    for (int j = 0; j < Board::BOARD_SIZE; j++)
    {
      B.setPiece(i, j, Board::PieceCharID::EMPTY);
    }
  }
}

Board::Board() { clearBoard(*this); }

void Board::initializeStandardSetup()
{
  clearBoard(*this);

  for (int i = 0; i < BOARD_SIZE; ++i)
  {
    grid[1][i] = PieceCharID::PAWN_BLACK;
    grid[6][i] = PieceCharID::PAWN_WHITE;
  }

  grid[0][0] = PieceCharID::ROOK_BLACK;
  grid[0][1] = PieceCharID::KNIGHT_BLACK;
  grid[0][2] = PieceCharID::BISHOP_BLACK;
  grid[0][3] = PieceCharID::QUEEN_BLACK;
  grid[0][4] = PieceCharID::KING_BLACK;
  grid[0][5] = PieceCharID::BISHOP_BLACK;
  grid[0][6] = PieceCharID::KNIGHT_BLACK;
  grid[0][7] = PieceCharID::ROOK_BLACK;

  grid[7][0] = PieceCharID::ROOK_WHITE;
  grid[7][1] = PieceCharID::KNIGHT_WHITE;
  grid[7][2] = PieceCharID::BISHOP_WHITE;
  grid[7][3] = PieceCharID::QUEEN_WHITE;
  grid[7][4] = PieceCharID::KING_WHITE;
  grid[7][5] = PieceCharID::BISHOP_WHITE;
  grid[7][6] = PieceCharID::KNIGHT_WHITE;
  grid[7][7] = PieceCharID::ROOK_WHITE;
}

void Board::display() const
{
  for (int row = 0; row < BOARD_SIZE; row++)
  {
    std::cout << std::endl << "  +---+---+---+---+---+---+---+---+" << std::endl;
    std::cout << (8 - row) << " |";
    for (int col = 0; col < BOARD_SIZE; col++)
    {
      if ((row + col) % 2 == 0)
      {
        std::cout << " " << static_cast<char>(grid[row][col]) << " |";
      }
      else
      {
        std::cout << "-" << static_cast<char>(grid[row][col]) << "-|";
      }
    }
  }
  std::cout << std::endl << "  +---+---+---+---+---+---+---+---+" << std::endl;
  std::cout << "    a   b   c   d   e   f   g   h" << std::endl << std::endl;
}

void Board::setPiece(int row, int col, PieceCharID piece)
{
  if (0 <= row && row < BOARD_SIZE && 0 <= col && col < BOARD_SIZE)
  {
    grid[row][col] = piece;
  }
}

Board::PieceCharID Board::getPiece(int row, int col) const
{
  PieceCharID result = PieceCharID::EMPTY;
  if (0 <= row && row < BOARD_SIZE && 0 <= col && col < BOARD_SIZE)
  {
    result = grid[row][col];
  }
  return result;
}
