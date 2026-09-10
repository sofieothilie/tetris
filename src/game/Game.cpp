#include <Board.hpp>
#include <Game.hpp>
#include <Pieces.hpp>

#include <cassert>
#include <iostream>
#include <random>
using namespace std;

/**
 * @brief Creates a game using the supplied board and piece definitions.
 *
 * The game keeps references to both objects but does not own them.
 *
 * @param pBoard Board used for collision detection and storing pieces.
 * @param pPieces Piece definitions used to create and position pieces.
 */
Game::Game(Board &pBoard, Pieces &pPieces) : mBoard(pBoard), mPieces(pPieces) {
  InitGame();
};

/**
 * @brief Get a random int between to integers
 * @param int pA: First number
 * @param int pB: Second number
 */
int Game::GetRand(int pA, int pB) {

  // Initialize a random number generator
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> distrib(pA, pB);

  // Generate random number in the range [min, max]
  return distrib(gen);
}

/**
 * @brief Sets initial parameters of the game
 */
void Game::InitGame() {
  // Initialise the first piece with rotation and position
  mPiece = GetRand(0, MAX_PIECES);
  mRotation = GetRand(0, MAX_ROTATION);
  mPosX = (BOARD_WIDTH / 2) + mPieces.GetXInitialPosition(mPiece, mRotation);
  mPosY = mPieces.GetYInitialPosition(mPiece, mRotation);

  // Initialise the next piece with rotation. Sets position outside the board
  // for now.
  mNextPiece = GetRand(0, MAX_PIECES);
  mNextRotation = GetRand(0, MAX_ROTATION);
  mNextPosX = BOARD_WIDTH + 1;
  mNextPosY = 1;
}

/**
 * @brief Create a random piece
 */
void Game::CreateNewPiece() {
  // The new piece
  mPiece = mNextPiece;
  mRotation = mNextRotation;
  mPosX = (BOARD_WIDTH / 2) + mPieces.GetXInitialPosition(mPiece, mRotation);
  mPosY = mPieces.GetYInitialPosition(mPiece, mRotation);

  mNextPiece = GetRand(0, MAX_PIECES);
  mNextRotation = GetRand(0, MAX_ROTATION);
}

/**
 * @brief Moves a piece to the left
 */
void Game::MoveLeft() {
  if (mBoard.IsPossibleMovement(mPosX - 1, mPosY, mPiece, mRotation)) {
    mPosX--;
  }
}

/**
 * @brief Moves a piece to the right
 */
void Game::MoveRight() {
  if (mBoard.IsPossibleMovement(mPosX + 1, mPosY, mPiece, mRotation)) {
    mPosX++;
  }
}

/**
 * @brief Moves a piece to down. Thereafter stores the piece, and updates the
 * game
 */
void Game::MoveDown() {

  if (mBoard.IsPossibleMovement(mPosX, mPosY + 1, mPiece, mRotation)) {
    mPosY++;
  } else {
    StorePieceUpdateGame();
  }
}

/**
 * @brief Drops a piece. Thereafter stores the piece, and updates the
 * game
 */
void Game::Drop() {
  while (mBoard.IsPossibleMovement(mPosX, mPosY + 1, mPiece, mRotation)) {
    mPosY++;
  }
  StorePieceUpdateGame();
}

/**
 * @brief Rotates a piece.
 */
void Game::Rotate() {
  if (mBoard.IsPossibleMovement(mPosX, mPosY, mPiece, (mRotation + 1) % 4)) {
    mRotation = (mRotation + 1) % 4;
  }
}

/**
 * @brief Stores a piece, deletes possible lines, checks if game over, and
 * creates a new piece if not.
 */
void Game::StorePieceUpdateGame() {
  mBoard.StorePiece(mPosX, mPosY, mPiece, mRotation);
  mBoard.DeletePossibleLines();

  if (mBoard.IsGameOver()) {
    // mIO.Getkey();
    // exit(0);
  } else {
    CreateNewPiece();
  }
}

/**
 * @brief Gets the X position of the current piece
 * @return read-only X position as int
 */
int Game::GetPositionX() const { return mPosX; }

/**
 * @brief Gets the Y position of the current piece
 * @return read-only Y position as int
 */
int Game::GetPositionY() const { return mPosY; }

/**
 * @brief Gets the current piece
 * @return read-only current piece as int
 */
int Game::GetPiece() const { return mPiece; }

/**
 * @brief Gets the rotation of the current piece
 * @return read-only rotation of current piece as int
 */
int Game::GetRotation() const { return mRotation; }

/**
 * @brief Gets the X position of the next piece
 * @return read-only X position as int
 */
int Game::GetNextPositionX() const { return mNextPosX; }

/**
 * @brief Gets the Y position of the next piece
 * @return read-only Y position as int
 */
int Game::GetNextPositionY() const { return mNextPosY; }

/**
 * @brief Gets the next piece
 * @return read-only next piece as int
 */
int Game::GetNextPiece() const { return mNextPiece; }

/**
 * @brief Gets the rotation of the next piece
 * @return read-only rotation of next piece as int
 */
int Game::GetNextRotation() const { return mNextRotation; }