#include "Board.hpp"

Board::Board(Pieces &pPieces) : mPieces(pPieces) { InitBoard(); };
/*
======================================
Init the board blocks with free positions
======================================
*/
void Board::InitBoard() {
  for (int i = 0; i < BOARD_WIDTH; i++) {
    for (int j = 0; j < BOARD_HEIGHT; j++) {
      mBoard[i][j] = POS_FREE;
    }
  }
}

/*
======================================
Store a piece in the board by filling the blocks

Parameters:

>> pX: Horizontal position in blocks
>> pY: Vertical position in blocks
>> pPiece: Piece to draw
>> pRotation: 1 of the 4 possible rotations
======================================
*/
void Board::StorePiece(int pX, int pY, int pPiece, int pRotation) {
  for (int i1 = pX, i2 = 0; i1 < pX + PIECE_BLOCKS; i1++, i2++) {
    for (int j1 = pY, j2 = 0; j1 < pY + PIECE_BLOCKS; j1++, j2++) {
      if (i1 >= 0 && i1 < BOARD_WIDTH && j1 >= 0 && j1 < BOARD_HEIGHT &&
          mPieces.GetBlockType(pPiece, pRotation, i2, j2) > 0) {
        mBoard[i1][j1] = POS_FILLED;
      }
    }
  }
}

/*
======================================
Delete a line of the board by moving all above lines down

Parameters:

>> pY: Vertical position in blocks of the line to delete
======================================
*/
void Board::DeleteLine(int pY) {
  for (int i = 0; i < BOARD_WIDTH; i++) {
    for (int j = pY; j > 0; j--) {
      mBoard[i][j] = mBoard[i][j - 1];
    }
    mBoard[i][0] = POS_FREE;
  }
}

/*
======================================
Returns 1 (true) if the this block of the board is empty, 0 if it is filled

Parameters:

>> pX: Horizontal position in blocks
>> pY: Vertical position in blocks
======================================
*/
bool Board::IsFreeBlock(int pX, int pY) const {
  return mBoard[pX][pY] == POS_FREE;
}

/*
======================================
Check if the piece can be stored at this position without any collision
Returns true if the movement is possible, false if it not possible

Parameters:

>> pX: Horizontal position in blocks
>> pY: Vertical position in blocks
>> pPiece: Piece to draw
>> pRotation: 1 of the 4 possible rotations
======================================
*/
bool Board::IsPossibleMovement(int pX, int pY, int pPiece,
                               int pRotation) const {

  for (int i1 = pX, i2 = 0; i1 < pX + PIECE_BLOCKS; i1++, i2++) {
    for (int j1 = pY, j2 = 0; j1 < pY + PIECE_BLOCKS; j1++, j2++) {
      bool pieceFilled = mPieces.GetBlockType(pPiece, pRotation, i2, j2);

      // Check if piece is outside board
      if (pieceFilled && (i1 < 0 || i1 >= BOARD_WIDTH || j1 >= BOARD_HEIGHT)) {
        return false;
      }

      // Check if block is already occupied and piece covers block.
      // Bypasses j1 to allow pieces to enter the board before they are checked.
      if (pieceFilled && j1 >= 0 && !IsFreeBlock(i1, j1)) {
        return false;
      }
    }
  }
  return true;
}

/*
======================================
Delete all the lines that should be removed
======================================
*/
void Board::DeletePossibleLines() {
  // NOTE: Iterates over the height first, hence why indexing here is [j][i]
  for (int i = 0; i < BOARD_HEIGHT; i++) {
    bool filled = true;
    for (int j = 0; j < BOARD_WIDTH; j++) {
      if (mBoard[j][i] != POS_FILLED) {
        filled = false;
        break;
      }
    }
    if (filled) {
      DeleteLine(i);
      i--;
    }
  }
}

/*
======================================
Check if the game is over becase a piece have achived the upper position

Returns true or false
======================================
*/
bool Board::IsGameOver() const {
  for (int i = 0; i < BOARD_WIDTH; i++) {
    if (mBoard[i][0] == POS_FILLED) {
      return true;
    }
  }
  return false;
}