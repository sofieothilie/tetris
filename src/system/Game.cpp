#include <Board.hpp>
#include <Game.hpp>
#include <Pieces.hpp>

#include <cassert>
#include <iostream>
#include <random>
using namespace std;

Game::Game(Board *pBoard, Pieces *pPieces, IO *pIO, int pScreenHeight) {
  mBoard = pBoard;
  mPieces = pPieces;
  mIO = pIO;
  mScreenHeight = pScreenHeight;

  InitGame();
};
Game::~Game() = default;

/*
======================================
Get a random int between to integers

Parameters:
>> pA: First number
>> pB: Second number
======================================
*/
int Game::GetRand(int pA, int pB) {

  // Initialize a random number generator
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> distrib(pA, pB);

  // Generate random number in the range [min, max]
  return distrib(gen);
}

/*
======================================
Initial parameters of the game
======================================
*/
void Game::InitGame() {
  // Initialise the first piece with rotation and position
  mPiece = GetRand(0, MAX_PIECES);
  mRotation = GetRand(0, MAX_ROTATION);
  mPosX = (BOARD_WIDTH / 2) + mPieces->GetXInitialPosition(mPiece, mRotation);
  mPosY = mPieces->GetYInitialPosition(mPiece, mRotation);

  // Initialise the next piece with rotation. Sets position outside the board
  // for now.
  mNextPiece = GetRand(0, MAX_PIECES);
  mNextRotation = GetRand(0, MAX_ROTATION);
  mNextPosX = BOARD_WIDTH + 5;
  mNextPosY = 5;
}

/*
======================================
Create a random piece
======================================
*/
void Game::CreateNewPiece() {
  // The new piece
  mPiece = mNextPiece;
  mRotation = mNextRotation;
  mPosX = (BOARD_WIDTH / 2) + mPieces->GetXInitialPosition(mPiece, mRotation);
  mPosY = mPieces->GetYInitialPosition(mPiece, mRotation);

  mNextPiece = GetRand(0, MAX_PIECES);
  mNextRotation = GetRand(0, MAX_ROTATION);
}

/*
======================================
Draw piece

Parameters:

>> pX: Horizontal position in blocks
>> pY: Vertical position in blocks
>> pPiece: Piece to draw
>> pRotation: 1 of the 4 possible rotations
======================================
*/
void Game::DrawPiece(int pX, int pY, int pPiece, int pRotation) {
  colour mColour;

  // Obtain the position in pixel in the screen of the block we want to draw
  int mPixelsX = mBoard->GetXPosInPixels(pX);
  int mPixelsY = mBoard->GetYPosInPixels(pY);

  // Travel the matrix of blocks of the piece and draw the blocks that are
  // filled
  for (int i = 0; i < PIECE_BLOCKS; i++) {
    for (int j = 0; j < PIECE_BLOCKS; j++) {
      int blockType = mPieces->GetBlockType(pPiece, pRotation, i, j);
      if (blockType == 0) {
        continue;
      }

      mColour = blockType == 1 ? GREEN : BLUE;

      mIO->DrawRectangle(mPixelsX + i * BLOCK_SIZE, mPixelsY + j * BLOCK_SIZE,
                         mPixelsX + (i + 1) * BLOCK_SIZE - 1,
                         mPixelsY + (j + 1) * BLOCK_SIZE - 1, mColour);
    }
  }
}

/*
======================================
Draw board

Draw the two lines that delimit the board
======================================
*/
void Game::DrawBoard() {

  // Calculate the limits of the board in pixels
  int mX1 = BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2));
  int mX2 = BOARD_POSITION + (BLOCK_SIZE * (BOARD_WIDTH / 2));
  int mY = mScreenHeight - BOARD_VERTICAL_OFFSET - BOARD_LINE_WIDTH -
           (BLOCK_SIZE * BOARD_HEIGHT);
  assert(mY > MIN_VERTICAL_MARGIN);

  int boardBottom = mY + BLOCK_SIZE * BOARD_HEIGHT;
  int borderBottom = boardBottom + BOARD_LINE_WIDTH;

  // Colourise the outer edges of the board
  mIO->DrawRectangle(mX1 - BOARD_LINE_WIDTH - 1, mY, mX1 - 1, borderBottom - 1,
                     BLUE);

  mIO->DrawRectangle(mX2, mY, mX2 + BOARD_LINE_WIDTH, borderBottom - 1, BLUE);
  mIO->DrawRectangle(mX1 - BOARD_LINE_WIDTH - 1, boardBottom,
                     mX2 + BOARD_LINE_WIDTH, borderBottom - 1, BLUE);

  // Colourise the occupied blocks inside the board
  for (int i = 0; i < BOARD_WIDTH; i++) {
    for (int j = 0; j < BOARD_HEIGHT; j++) {
      if (!(mBoard->IsFreeBlock(i, j))) {
        mIO->DrawRectangle(mX1 + i * BLOCK_SIZE, mY + j * BLOCK_SIZE,
                           mX1 + (i + 1) * BLOCK_SIZE - 1,
                           mY + (j + 1) * BLOCK_SIZE - 1, RED);
      }
    }
  }
}

/*
======================================
Draw scene

Draw all the objects of the scene
======================================
*/
void Game::DrawScene() {
  DrawBoard(); // Draw the delimitation lines and blocks stored in the board
  DrawPiece(mPosX, mPosY, mPiece, mRotation); // Draw the playing piece
  DrawPiece(mNextPosX, mNextPosY, mNextPiece,
            mNextRotation); // Draw the next piece
}