#ifndef _GAME_
#define _GAME_

#include "Board.hpp"
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
  Board &mBoard;
  Pieces &mPieces;

  int mPosX, mPosY;         // Position of the piece that is falling down
  int mPiece, mRotation;    // Kind and rotation of the piece thats falling down
  int mNextPosX, mNextPosY; // Position of the next piece
  int mNextPiece, mNextRotation; // Kind and rotation of next piece

  int GetRand(int pA, int pB);
  void InitGame();
  void StorePieceUpdateGame();
  void CreateNewPiece();

public:
  Game(Board &pBoard, Pieces &pPieces);
  void MoveLeft();
  void MoveRight();
  void MoveDown();
  void Drop();
  void Rotate();

  int GetPositionX() const; 
  int GetPositionY() const;
  int GetPiece() const;
  int GetRotation() const;
  int GetNextPositionX() const;
  int GetNextPositionY() const;
  int GetNextPiece() const;
  int GetNextRotation() const;
};
#endif