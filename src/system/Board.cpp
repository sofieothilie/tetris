#include "Board.hpp"

Board::Board(Pieces *pPieces, int pScreenHeight) {
  mPieces = pPieces;
  mScreenHeight = pScreenHeight;

  InitBoard();
};
Board::~Board() = default;
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
      if (mPieces->GetBlockType(pPiece, pRotation, i2, j2) != 0) {
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
    for (int j = pY; j < BOARD_HEIGHT; j++) {
      mBoard[i][j] = mBoard[i][j - 1];
    }
  }
}

/*
======================================
Returns the horizontal position (in pixels) of the block given like parameter

Parameters:

>> pPos: Horizontal position of the block in the board
======================================
*/
int Board::GetXPosInPixels(int pPos) {
  return ((BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2))) +
          (pPos * BLOCK_SIZE));
}

/*
======================================
Returns the vertical position (in pixels) of the block given like parameter

Parameters:

>> pPos: Vertical position of the block in the board
======================================
*/
int Board::GetYPosInPixels(int pPos) {
  return ((BOARD_POSITION - (BLOCK_SIZE * (BOARD_HEIGHT / 2))) +
          (pPos * BLOCK_SIZE));
}
/*
======================================
Returns 1 (true) if the this block of the board is empty, 0 if it is filled

Parameters:

>> pX: Horizontal position in blocks
>> pY: Vertical position in blocks
======================================
*/
bool Board::IsFreeBlock(int pX, int pY) { return mBoard[pX][pY] == POS_FREE; }

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
bool Board::IsPossibleMovement(int pX, int pY, int pPiece, int pRotation) {

  for (int i1 = pX, i2 = 0; i1 < pX + PIECE_BLOCKS; i1++, i2++) {
    for (int j1 = pY, j2 = 0; j1 < pY + PIECE_BLOCKS; j1++, j2++) {
      bool pieceFilled = mPieces->GetBlockType(pPiece, pRotation, i2, j2);

      // Check if piece is outside board
      if ((i1 < 0 || i1 > BOARD_WIDTH - 1 || j2 > BOARD_HEIGHT - 1) &&
          pieceFilled) {
        return false;
      }

      // Check if block is already occupied and piece covers block.
      // Bypasses j1 to allow pieces to enter the board before they are checked.
      if (j1 > 0 || !IsFreeBlock(i1, j1) && pieceFilled) {
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
  for (int i = 0; i < BOARD_HEIGHT; i++) {
    bool filled = true;
    for (int j = 0; i < BOARD_WIDTH; i++) {
      if (mBoard[i][j] != POS_FILLED)
        filled = false;
      break;
    }
    if (filled) {
      DeleteLine(i);
    }
  }
}

/*
======================================
Check if the game is over becase a piece have achived the upper position

Returns true or false
======================================
*/
bool Board::IsGameOver() {
  for (int i = 0; i < BOARD_WIDTH; i++) {
    if (mBoard[i][0] == POS_FILLED) {
      return true;
    }
  }
  return false;
}