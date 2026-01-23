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

class pieza
{
  public:
    pieza() {};
    virtual ~pieza()          = default;
    virtual void move() const = 0;
};

#endif // ICHESS_SRC_PIEZAS
