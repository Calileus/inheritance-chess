/// ---------------------------------------------------------------------------------
/// @file      pawns.cpp
/// @author    Calileus (https://github.com/Calileus/inheritance-chess)
/// @brief     Pawn piece implementation for chess engine.
/// @version   1.0
/// @date      2026-01-01
/// @copyright MIT License - see LICENSE file for details
/// ---------------------------------------------------------------------------------
#include <iostream>
#include "pawns.hpp"

void pawn::move() const { std::cout << "Pawn moves forward one or two squares." << std::endl; }
