/// @file      README.md
/// @namespace Chess
/// @brief     Chess Common Interface (CCI) Module Documentation.
/// @author    Calileus
/// @date      2026-01-22
/// @copyright 2026 Obsidian Honor Coders. Licensed under Apache 2.0.
/// @see       https://github.com/ObsidianHonorCoders/inheritance-chess

# CCI: Chess Common Interface

## Overview

The Chess Common Interface (CCI) module is the foundation of the chess engine architecture. It defines all common data types, structures, and enumerations that are used across all other modules.

## Role: The "Common Language"

CCI is a **passive layer** that contains only data structures and definitions. Other modules depend on CCI but CCI doesn't depend on any other game logic modules.

## Key Components

### Type Definitions (`chess_types.h`)

- **Color**: Enumeration for chess sides (WHITE, BLACK)
- **PieceType**: Enumeration for piece types (PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING)
- **SpecialFlags**: Enumeration for special moves (NONE, CASTLE_KINGSIDE, CASTLE_QUEENSIDE, EN_PASSANT, PROMOTION)
- **GameState**: Enumeration for game states (ONGOING, CHECKMATE, STALEMATE, etc.)
- **GameFlags**: Structure tracking castling rights and move counters

### Position Structure (`position.h`)

Represents a single square on the 8x8 chess board:
- `file`: 0-7 (a-h, columns)
- `rank`: 0-7 (1-8, rows)

Methods:
- `is_valid()`: Check if position is within board boundaries
- `operator==`, `operator<`: Comparison operators

### Move Structure (`move.h`)

Represents a single chess move with:
- `start_pos`: Source position
- `end_pos`: Destination position
- `flags`: Special move flags
- `promotion_piece`: Piece type for promotion (if applicable)

Methods:
- `is_promotion()`: Check if move is a promotion
- `is_castling()`: Check if move is castling
- `is_en_passant()`: Check if move is en passant capture

### Grid Structure (`grid.h`)

Represents the complete state of a chess board:
- `board`: 8x8 array of optional PieceProperties
- `current_turn`: Whose turn it is
- `flags`: GameFlags structure with castling rights

Includes methods:
- `get_piece(pos)`: Retrieve piece at position
- `set_piece(pos, piece)`: Place piece on square
- `is_occupied(pos)`: Check if square has a piece
- `initialize_standard_position()`: Set up starting position
- `switch_turn()`: Toggle current turn

## Design Principles

1. **Independence**: CCI has no dependencies on other modules
2. **Consistency**: All modules use CCI structures
3. **Simplicity**: Contains only data structures, no complex logic
4. **Documentation**: Well-documented interfaces for easy reference

## File Structure

```
cci/
├── include/
│   ├── chess_types.h    # Type definitions
│   ├── position.h       # Position structure
│   ├── move.h           # Move structure
│   └── grid.h           # Board state structure
├── src/
│   ├── chess_types.cpp  # Type helper functions
│   ├── position.cpp     # Position utilities
│   ├── move.cpp         # Move utilities
│   └── grid.cpp         # Grid initialization
└── tests/
    ├── test_chess_types.cpp
    ├── test_position.cpp
    ├── test_move.cpp
    └── test_grid.cpp
```

## Future Enhancements

- Optimization of Position hash function for caching
- Addition of move flags for additional special moves
- Compression of board representation for engine optimization
