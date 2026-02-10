/// @file      main.cpp
/// @author    Calileus (https://github.com/Calileus/inheritance-chess)
/// @brief     Entry point for the Inheritance Chess Engine application.
/// @details   Demonstrates basic chess engine functionality including board setup,
///            piece creation, and console-based board display using C++ inheritance
///            and polymorphism principles.
/// @version   1.0
/// @date      2025-12-30
/// @copyright MIT License - see LICENSE file for details

#include <iostream>
#include <string>
#include <memory>

#include "board.hpp"

/// @brief   Main entry point for the Inheritance Chess Engine.
/// @return  Exit status code (0 for success).
/// @details Initializes the chess board with the standard starting position.
int main()
{
  Board chessBoard;
  chessBoard.initializeStandardSetup();

  std::cout << "====================================" << std::endl;
  std::cout << "|  Inheritance Chess Engine v0.0   |" << std::endl;
  std::cout << "====================================" << std::endl;
  std::cout << "Starting Inheritance Chess!" << std::endl << std::endl;
  std::cout << "Chess Board successfully created and initialized." << std::endl;
  std::cout << "All further testing will be conducted via GTest." << std::endl;
  std::cout << "Communication protocol and usage: TBD." << std::endl << std::endl;
  std::cout << "Thanks for using our software!" << std::endl;
  std::cout << "                               - OHC team." << std::endl;

  return 0;
}
