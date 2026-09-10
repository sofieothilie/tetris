#include "Pieces.hpp"

// Matrix that stores all pieces and their rotations as 2D matrixes
// 7 pieces, where each has 4 rotations, and each piece is a 5x5 matrix.
const char mPieces[7][4][5][5] = {
    // SQUARE Square
    {{{0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 2, 1, 0},
      {0, 0, 1, 1, 0},
      {0, 0, 0, 0, 0}},
     {{0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 2, 1, 0},
      {0, 0, 1, 1, 0},
      {0, 0, 0, 0, 0}},
     {{0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 2, 1, 0},
      {0, 0, 1, 1, 0},
      {0, 0, 0, 0, 0}},
     {{0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 2, 1, 0},
      {0, 0, 1, 1, 0},
      {0, 0, 0, 0, 0}}},

    // I
    {{{0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 1, 2, 1, 1},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0}},
     {{0, 0, 0, 0, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 2, 0, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 1, 0, 0}},
     {{0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {1, 1, 2, 1, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0}},
     {{0, 0, 1, 0, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 2, 0, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 0, 0, 0}}},
    // L
    {{{0, 0, 0, 0, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 2, 0, 0},
      {0, 0, 1, 1, 0},
      {0, 0, 0, 0, 0}},
     {{0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 1, 2, 1, 0},
      {0, 1, 0, 0, 0},
      {0, 0, 0, 0, 0}},
     {{0, 0, 0, 0, 0},
      {0, 1, 1, 0, 0},
      {0, 0, 2, 0, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 0, 0, 0}},
     {{0, 0, 0, 0, 0},
      {0, 0, 0, 1, 0},
      {0, 1, 2, 1, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0}}},
    // L mirrored
    {{{0, 0, 0, 0, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 2, 0, 0},
      {0, 1, 1, 0, 0},
      {0, 0, 0, 0, 0}},
     {{0, 0, 0, 0, 0},
      {0, 1, 0, 0, 0},
      {0, 1, 2, 1, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0}},
     {{0, 0, 0, 0, 0},
      {0, 0, 1, 1, 0},
      {0, 0, 2, 0, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 0, 0, 0}},
     {{0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 1, 2, 1, 0},
      {0, 0, 0, 1, 0},
      {0, 0, 0, 0, 0}}},
    // N
    {{{0, 0, 0, 0, 0},
      {0, 0, 0, 1, 0},
      {0, 0, 2, 1, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 0, 0, 0}},
     {{0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 1, 2, 0, 0},
      {0, 0, 1, 1, 0},
      {0, 0, 0, 0, 0}},
     {{0, 0, 0, 0, 0},
      {0, 0, 1, 0, 0},
      {0, 1, 2, 0, 0},
      {0, 1, 0, 0, 0},
      {0, 0, 0, 0, 0}},

     {{0, 0, 0, 0, 0},
      {0, 1, 1, 0, 0},
      {0, 0, 2, 1, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0}}},
    // N mirrored
    {{{0, 0, 0, 0, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 2, 1, 0},
      {0, 0, 0, 1, 0},
      {0, 0, 0, 0, 0}},
     {{0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 2, 1, 0},
      {0, 1, 1, 0, 0},
      {0, 0, 0, 0, 0}},
     {{0, 0, 0, 0, 0},
      {0, 1, 0, 0, 0},
      {0, 1, 2, 0, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 0, 0, 0}},
     {{0, 0, 0, 0, 0},
      {0, 0, 1, 1, 0},
      {0, 1, 2, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0}}},
    // T
    {{{0, 0, 0, 0, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 2, 1, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 0, 0, 0}},
     {{0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 1, 2, 1, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 0, 0, 0}},
     {{0, 0, 0, 0, 0},
      {0, 0, 1, 0, 0},
      {0, 1, 2, 0, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 0, 0, 0}},
     {{0, 0, 0, 0, 0},
      {0, 0, 1, 0, 0},
      {0, 1, 2, 1, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0}}}};

// Matrix that stores all pieces and their initial position as 2D matrixes
// 7 pieces, 4 rotations and 2 coordinates (x,y)
const int mPiecesInitialPosition[][4][2] = {
    /* Square */
    {{-2, -3}, {-2, -3}, {-2, -3}, {-2, -3}},
    /* I */
    {{-2, -2}, {-2, -3}, {-2, -2}, {-2, -3}},
    /* L */
    {{-2, -3}, {-2, -3}, {-2, -3}, {-2, -2}},
    /* L mirrored */
    {{-2, -3}, {-2, -2}, {-2, -3}, {-2, -3}},
    /* N */
    {{-2, -3}, {-2, -3}, {-2, -3}, {-2, -2}},
    /* N mirrored */
    {{-2, -3}, {-2, -3}, {-2, -3}, {-2, -2}},
    /* T */
    {{-2, -3}, {-2, -3}, {-2, -3}, {-2, -2}},
};

/**
 * @brief Creates the piece definition provider.
 *
 * Piece layouts and their initial positions are stored as static data.
 */
Pieces::Pieces() = default;

/**
* @brief Gets a pieces block type for a position given position
* @param int pPiece: Piece to draw
* @param int pRotation: 1 of the 4 possible rotations
* @param int pX: Horizontal position in blocks
* @param int pY: Vertical position in blocks
* @return blcoktype as int: 0 = no-block, 1 = normal block, 2 = pivot
block
*/
int Pieces::GetBlockType(int pPiece, int pRotation, int pX, int pY) const {
  return mPieces[pPiece][pRotation][pY][pX];
}

/**
* @brief Returns the horizontal displacement of the piece that has to be
applied in order to create it in the correct position.
* @param int pPiece: Piece to draw
* @param int pRotation: 1 of the 4 possible rotations
* @return X Position as int
*/
int Pieces::GetXInitialPosition(int pPiece, int pRotation) const {
  return mPiecesInitialPosition[pPiece][pRotation][0];
}

/**
 * @brief Returns the vertical displacement of the piece that has to be applied
in order to create it in the correct position.
* @param int pPiece: Piece to draw
* @param int pRotation: 1 of the 4 possible rotations
* @return Y Position as int
*/
int Pieces::GetYInitialPosition(int pPiece, int pRotation) const {
  return mPiecesInitialPosition[pPiece][pRotation][1];
}
