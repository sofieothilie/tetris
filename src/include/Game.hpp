#ifndef _GAME_
#define _GAME_

#include "Board.hpp"
#include "IO.hpp"
#include "Pieces.hpp"
#include <time.h>

// —— Defines —–

#define WAIT_TIME                                                              \
  700 // Number of milliseconds that the piece remains before going 1 block down
      // */
#define MAX_PIECES 6   // 0 indexed
#define MAX_ROTATION 3 // 0 indexed

// ——————————————————————————–
// Game
// ——————————————————————————–

class Game {
private:
  int mScreenHeight;             // Screen height in pixels
  int mNextPosX, mNextPosY;      // Position of the next piece
  int mNextPiece, mNextRotation; // Kind and rotation of next piece

  Board *mBoard;
  Pieces *mPieces;
  IO *mIO;

  int GetRand(int pA, int pB);
  void InitGame();
  void DrawPiece(int pX, int pY, int pPiece, int pRotation);
  void DrawBoard();

public:
  Game(Board *pBoard, Pieces *pPieces, IO *pIO, int pScreenHeight);
  ~Game();
  void DrawScene();
  void CreateNewPiece();

  int mPosX, mPosY;      // Position of the piece that is falling down
  int mPiece, mRotation; // Kind and rotation of the piece thats falling down
};
#endif