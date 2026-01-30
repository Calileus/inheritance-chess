/// ---------------------------------------------------------------------------------
/// @file      piezas.cpp
/// @author    Calileus (https://github.com/Calileus/inheritance-chess)
/// @brief     Basic Chess Engine demonstrating C++ inheritance and polymorphism.
/// @version   1.0
/// @date      2026-01-01
/// @copyright MIT License - see LICENSE file for details
/// ---------------------------------------------------------------------------------
#include "piezas.hpp"

Pieza::Pieza() {}

Pieza::Pieza(PieceColor col) : color(col) { set_position('a', '1'); }

bool Pieza::is_black() const { return color == PieceColor::BLACK; }
bool Pieza::is_white() const { return color == PieceColor::WHITE; }

void Pieza::set_position(char f, char r)
{
  position.file = f;
  position.rank = r;
}

char Pieza::get_representation() const
{
  char res;
  switch (color)
  {
  case PieceColor::WHITE:
    return static_cast<char>(representation);
  case PieceColor::BLACK:
    return static_cast<char>(std::tolower(static_cast<char>(representation)));
  default:
    return ' ';
  }
}
