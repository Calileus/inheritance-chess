# CGH: Chess Game Handler

## Overview

The Chess Game Handler (CGH) module is the orchestrator that manages the lifecycle of a chess game session and coordinates all other modules.

## Role: The "Orchestrator"

CGH is the entry point and main interface for the application. It instantiates all necessary modules and manages game flow, metadata, and time control.

## Core Responsibilities

1. **Game Lifecycle Management**
   - Start new games from standard position
   - Load games from FEN notation
   - Execute moves with full validation
   - Track game state and history

2. **Module Coordination**
   - Create and manage instances of CCI, CPL, CBM, CTU
   - Orchestrate module interactions
   - Provide unified interface to game logic

3. **Game Metadata**
   - Maintain unique game IDs
   - Track move history
   - Manage player information
   - Record time control settings

4. **Time Control**
   - Track player clocks
   - Handle timeout conditions
   - Support various time controls (blitz, rapid, classical)

## Key Classes

### GameSession

Structure holding game metadata:

```cpp
struct GameSession {
    std::string game_id;
    std::vector<Move> move_history;
    std::chrono::milliseconds white_time;
    std::chrono::milliseconds black_time;
    GameState state;
};
```

### ChessGameHandler

Main class with public interface:

```cpp
class ChessGameHandler {
public:
    void start_new_game();
    void load_game_from_fen(const std::string& fen);
    bool make_move(const std::string& algebraic_move);
    bool make_move(const Move& move);
    std::string get_current_fen() const;
    std::vector<Move> get_legal_moves() const;
    GameState get_game_state() const;
    void start_timer(Color color);
    void stop_timer(Color color);
    std::chrono::milliseconds get_time_remaining(Color color) const;
private:
    std::unique_ptr<ChessBoardManager> board_manager_;
    std::unique_ptr<ChessPiecesLogic> pieces_logic_;
    std::unique_ptr<ChessTranslationUnit> translation_unit_;
};
```

## Game Flow

1. **Initialization**
   - Create new game or load from FEN
   - Initialize all modules
   - Set game metadata

2. **Move Execution**
   - Receive move in algebraic or Move format
   - Validate move legality (CPL + CBM)
   - Update board state
   - Check for game end conditions

3. **Game State Queries**
   - Get current position as FEN
   - Get list of legal moves
   - Query game state (ongoing, checkmate, stalemate, etc.)

4. **Time Management**
   - Track clock times for each player
   - Handle time increments/decrements
   - Detect timeout conditions

## Dependencies

- **CCI**: Uses all CCI structures
- **CBM**: Board management and rule enforcement
- **CPL**: Piece logic and move generation
- **CTU**: Notation conversion

## File Structure

```
cgh/
├── include/
│   └── game_handler.h
├── src/
│   └── game_handler.cpp
└── tests/
    ├── test_game_handler.cpp
    ├── test_integration.cpp
    └── test_performance.cpp
```

## Implementation Notes

- Implements facade pattern for clean API
- Maintains separation of concerns with module coordination
- Provides thread-safe game state access
- Supports both UCI and algebraic notation

## Usage Example

```cpp
ChessGameHandler game;

// Start a new game
game.start_new_game();

// Make moves
bool success = game.make_move("e2e4");

// Get game state
GameState state = game.get_game_state();

// Get legal moves
std::vector<Move> moves = game.get_legal_moves();

// Convert to FEN
std::string fen = game.get_current_fen();
```

## Future Enhancements

- Save/load game to/from PGN format
- Move time estimation
- Engine evaluation integration
- GUI event handler support
- Network game support
