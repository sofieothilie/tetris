#include <Board.hpp>
#include <Game.hpp>
#include <Pieces.hpp>

#include <cassert>
#include <iostream>
#include <random>
using namespace std;

Game::Game(Board &pBoard, Pieces &pPieces) : mBoard(pBoard), mPieces(pPieces) {
  InitGame();
};

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
  mPosX = (BOARD_WIDTH / 2) + mPieces.GetXInitialPosition(mPiece, mRotation);
  mPosY = mPieces.GetYInitialPosition(mPiece, mRotation);

  // Initialise the next piece with rotation. Sets position outside the board
  // for now.
  mNextPiece = GetRand(0, MAX_PIECES);
  mNextRotation = GetRand(0, MAX_ROTATION);
  mNextPosX = BOARD_WIDTH + 1;
  mNextPosY = 1;
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
  mPosX = (BOARD_WIDTH / 2) + mPieces.GetXInitialPosition(mPiece, mRotation);
  mPosY = mPieces.GetYInitialPosition(mPiece, mRotation);

  mNextPiece = GetRand(0, MAX_PIECES);
  mNextRotation = GetRand(0, MAX_ROTATION);
}

void Game::MoveLeft() {
  if (mBoard.IsPossibleMovement(mPosX - 1, mPosY, mPiece, mRotation)) {
    mPosX--;
  }
}
void Game::MoveRight() {
  if (mBoard.IsPossibleMovement(mPosX + 1, mPosY, mPiece, mRotation)) {
    mPosX++;
  }
}
void Game::MoveDown() {

  if (mBoard.IsPossibleMovement(mPosX, mPosY + 1, mPiece, mRotation)) {
    mPosY++;
  } else {
    mBoard->StorePiece(mPosX, mPosY, mPiece, mRotation);
    mBoard->DeletePossibleLines();

    if (mBoard->IsGameOver()) {
      // mIO.Getkey();
      // exit(0);
    }
    CreateNewPiece();
  }
}
void Game::Drop() {
  while (mBoard.IsPossibleMovement(mPosX, mPosY + 1, mPiece, mRotation)) {
    mPosY++;
  }
  mBoard->StorePiece(mPosX, mPosY, mPiece, mRotation);
  mBoard->DeletePossibleLines();

  if (mBoard->IsGameOver()) {
    // mIO.Getkey();
    // exit(0);
  }
  CreateNewPiece();
}

void Game::Rotate() {
  if (mBoard.IsPossibleMovement(mPosX, mPosY, mPiece, (mRotation + 1) % 4)) {
    mRotation = (mRotation + 1) % 4;
  }
}

void Game::Update() {
  // Move piece, detect collisions, store pieces, etc.
  if (mBoard.IsPossibleMovement(mPosX, mPosY + 1, mPiece, mRotation)) {
    mPosY++;
  } else {
    mBoard->StorePiece(mPosX, mPosY, mPiece, mRotation);
    mBoard->DeletePossibleLines();

    if (mBoard->IsGameOver()) {
      return;
    }
    CreateNewPiece();
  }
}
