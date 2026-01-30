/// ---------------------------------------------------------------------------------
/// @file      pawns.hpp
/// @author    Calileus (https://github.com/Calileus/inheritance-chess)
/// @brief     Pawn piece implementation for chess engine.
/// @version   1.0
/// @date      2026-01-01
/// @copyright MIT License - see LICENSE file for details
/// ---------------------------------------------------------------------------------
#ifndef ICHESS_SRC_PAWNS
#define ICHESS_SRC_PAWNS

#include "piezas.hpp"

class Pawn : public Pieza
{
  public:
    Pawn(char file, char rank, PieceColor color) : Pieza(color, PieceType::PAWN) { set_position(file, rank); }

    virtual ~Pawn() override {};
    virtual void moves(std::vector<PiecePosition>& p) const override
    {
      if (is_black())
      {
      }
      else if (is_white())
      {
      }
      else
      {
        throw std::runtime_error("Invalid piece color");
      }
    }
};

#endif // ICHESS_SRC_PAWNS
