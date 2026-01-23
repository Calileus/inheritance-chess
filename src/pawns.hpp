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

class pawn : public pieza
{
  public:
    pawn() {};
    virtual ~pawn() override {};
    virtual void move() const override;
};

#endif // ICHESS_SRC_PAWNS
