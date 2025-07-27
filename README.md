# Chess

A fully functional text-based chess game implemented in C, built with a focus on clean logic, robust move validation, and a structured approach to piece movement. This project emphasizes precision in game mechanics while maintaining an easy-to-use terminal interface.

---

## Features
- **Complete 8x8 Chessboard**: Dynamically rendered after every move.
- **Turn-based Gameplay**: Alternating turns for White and Black, with clear prompts.
- **Input Validation**: Ensures valid piece selection and legal moves per chess rules specific for every piece.
- **Check and Checkmate Indicators**: Supports manual check (`+`) and checkmate (`#`) declarations.
- **Structured Implementation**: Piece positions and board state are efficiently managed using structures and arrays.

---

## How to Play
1. Moves must be entered in the format `A2` for initial position and `A4` for the destination square.
2. Add `+` at the end of the move if it results in a check (e.g., `E5+`).
3. Add `#` at the end of the move if it results in checkmate (e.g., `H8#`).
4. Inputs are **case-insensitive** but must not include spaces.

### Example Gameplay
```text
WHITE'S TURN
enter initial position of piece to move: E2
enter position to move to: E4
```
The board updates after every move, reflecting the new state.

---

## Key Design Highlights
- **Readable and Modular Code**: Functions are designed for specific tasks such as validating moves, identifying pieces, and updating positions.
- **Error Handling**: Invalid moves are rejected with descriptive messages, guiding the player to input correctly.
- **Lightweight Implementation**: No external dependencies; purely written in C for speed and portability.

---

## Future Improvements
- Implementation of advanced chess rules like castling, en passant, and pawn promotion.
- Automated check/checkmate detection.
- Potential GUI integration for an enhanced user experience.

---

This is for when you want to have a terminal-based, simple but functional chess experience.
## Authors
Developed with ❤️ by [@dsdeshna](https://github.com/dsdeshna) & [@shaundcm](https://github.com/shaundcm)
