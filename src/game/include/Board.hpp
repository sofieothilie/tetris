#ifndef _BOARD_
#define _BOARD_

// —— Includes —–

#include "Pieces.hpp"

// —— Defines —–

#define BOARD_WIDTH 10  // Board width in blocks
#define BOARD_HEIGHT 20 // Board height in blocks
#define PIECE_BLOCKS                                                           \
  5 // Number of horizontal and vertical blocks of a matrix piece

// ——————————————————————————–
// Board
// ——————————————————————————–

class Board {
private:
  enum { POS_FREE, POS_FILLED };
  int mBoard[BOARD_WIDTH][BOARD_HEIGHT];
  Pieces *mPieces;

  void InitBoard();
  void DeleteLine(int pY);

public:
  Board(Pieces *pPieces);
  ~Board();
  bool IsFreeBlock(int pX, int pY);
  bool IsPossibleMovement(int pX, int pY, int pPiece, int pRotation);
  void StorePiece(int pX, int pY, int pPiece, int pRotation);
  void DeletePossibleLines();
  bool IsGameOver();
};

#endif