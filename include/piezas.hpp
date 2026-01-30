/// ---------------------------------------------------------------------------------
/// @file      piezas.hpp
/// @author    Calileus (https://github.com/Calileus/inheritance-chess)
/// @brief     Basic Chess Engine demonstrating C++ inheritance and polymorphism.
/// @version   1.0
/// @date      2026-01-01
/// @copyright MIT License - see LICENSE file for details
/// ---------------------------------------------------------------------------------
#ifndef ICHESS_SRC_PIEZAS
#define ICHESS_SRC_PIEZAS
#include <vector>
#include <cctype>
#include "common.hpp"

class Pieza
{
  private:
    PieceColor          color;
    PiecePosition       position;
    PieceRepresentation representation;

    Pieza(); // Private constructor to prevent color-less instantiation

  public:
    Pieza(PieceColor col);

    bool is_black() const;
    bool is_white() const;
    void set_position(char f, char r);
    char get_representation() const;

    virtual ~Pieza()                                        = default;
    virtual void moves(std::vector<PiecePosition>& p) const = 0;
};

#endif // ICHESS_SRC_PIEZAS
