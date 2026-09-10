#include "BoardRenderer.hpp"

#include <QColor>
#include <QPainter>
#include <QPainterPath>

enum Colour {
  RED,         // N
  GREEN,       // N-inverted
  YELLOW,      // Square
  DARKMAGENTA, // L
  ORANGE,      // L inverted
  CYAN,        // I
  MAGENTA      // T
};

/**
 * @brief Widget responsible for displaying a Tetris game.
 *
 * Owns the game model, updates it through a timer, handles keyboard input,
 * and renders the board and active pieces.
 * @param Game &pGame: Reference to Game created by the game
 * @param Board &pBoard: Reference to Board created by the game
 * @param Pieces &pPieces: Reference to Pieces created by the game
 * @param QWidget parent: Optional Qt parent widget.
 */
BoardRenderer::BoardRenderer(Game &pGame, Board &pBoard, Pieces &pPieces,
                             QWidget *parent)
    : QWidget(parent), mGame(pGame), mBoard(pBoard), mPieces(pPieces) {}

/**
 * @brief Repaints the game widget.
 *
 * Qt calls this function whenever the widget needs to be redrawn. The current
 * board state and active pieces are rendered using a QPainter.
 *
 * @param event Paint event supplied by Qt.
 */
void BoardRenderer::paintEvent(QPaintEvent *) {
  QPainter painter(this);
  DrawScene(painter);
}

/**
 * @brief Draws the complete game scene.
 *
 * Renders the board and its occupied cells, followed by the currently falling
 * piece and the preview of the next piece.
 *
 * @param pPainter Painter used for rendering.
 */
void BoardRenderer::DrawScene(QPainter &pPainter) {
  DrawBoard(
      pPainter); // Draw the delimitation lines and blocks stored in the board
  DrawOccupiedBlocks(pPainter); // Draw occupied blocks
  DrawPiece(pPainter, mGame.GetPositionX(), mGame.GetPositionY(),
            mGame.GetPiece(),
            mGame.GetRotation()); // Draw the playing piece
  DrawPiece(pPainter, mGame.GetNextPositionX(), mGame.GetNextPositionY(),
            mGame.GetNextPiece(),
            mGame.GetNextRotation()); // Draw the next piece
}

/**
 * @brief Draws a piece on the board
 * @param pPainter Painter used for rendering.
 * @param pX: Horizontal position in blocks
 * @param pY: Vertical position in blocks
 * @param pPiece: Piece to draw
 * @param pRotation: 1 of the 4 possible rotations
 */
void BoardRenderer::DrawPiece(QPainter &painter, int pX, int pY, int pPiece,
                              int pRotation) {

  // Obtain the position in pixel in the screen of the block we want to draw
  int mPixelsX = GetXPosInPixels(pX);
  int mPixelsY = GetYPosInPixels(pY);

  // Travel the matrix of blocks of the piece and draw the blocks that are
  // filled
  for (int i = 0; i < PIECE_BLOCKS; i++) {
    for (int j = 0; j < PIECE_BLOCKS; j++) {
      int blockType = mPieces.GetBlockType(pPiece, pRotation, i, j);
      if (blockType == 0) {
        continue;
      }
      QColor mColour = blockType == 1 ? Qt::green : Qt::blue;
      painter.fillRect(mPixelsX + i * BLOCK_SIZE, mPixelsY + j * BLOCK_SIZE,
                       BLOCK_SIZE - 1, BLOCK_SIZE - 1, mColour);
    }
  }
}

/**
 * @brief Draws the board boundary and "Next Piece"-square.
 *
 * Calculates the board position within the widget, draws its borders and lines.
 *
 * @param pPainter Painter used for rendering.
 */
void BoardRenderer::DrawBoard(QPainter &pPainter) {

  // Calculate the limits of the board in pixels
  const int boardWidth = BLOCK_SIZE * BOARD_WIDTH;
  const int boardHeight = BLOCK_SIZE * BOARD_HEIGHT;
  const int mXleft = GetLeftPixelBoard() / 2;
  const int mXright = mXleft + boardWidth;
  const int mYtop = GetBoardTop();
  const int mYbottom = mYtop + boardHeight;

  assert(mYtop > MIN_VERTICAL_MARGIN);

  DrawRectangle(pPainter, mXleft, mXright, mYtop, mYbottom, BOARD_LINE_WIDTH);

  DrawRectangle(pPainter, mXright + BLOCK_SIZE,
                mXright + (PIECE_BLOCKS + 1) * BLOCK_SIZE, mYtop + BLOCK_SIZE,
                mYtop + (PIECE_BLOCKS + 1) * BLOCK_SIZE, BOARD_LINE_WIDTH);
}

/**
 * @brief Draws the board boundary and "Next Piece"-square.
 *
 * Calculates the board position within the widget, draws its borders and lines.
 *
 * @param pPainter Painter used for rendering.
 * @param int mXleft: left pixel corner of square to be drawn
 * @param int mXright: right pixel corner of square to be drawn
 * @param int mYtop: top pixel corner of square to be drawn
 * @param int mYbottom: bottom pixel corner of square to be drawn
 * @param int mThickness: line thickness inside the square
 */
void BoardRenderer::DrawRectangle(QPainter &pPainter, int mXleft, int mXright,
                                  int mYtop, int mYbottom, int mThickness) {

  // // Calculate the limits of the square in pixels
  const int RectangleWidth = mXright - mXleft;
  const int RectangleHeight = mYbottom - mYtop;

  pPainter.setBrush(QBrush(Qt::lightGray));
  pPainter.setPen(QPen(Qt::black, mThickness));

  pPainter.drawRect(mXleft - mThickness / 2, mYtop - mThickness / 2,
                    RectangleWidth + 2 * mThickness / 2,
                    RectangleHeight + 2 * mThickness / 2);

  pPainter.setPen(QPen(Qt::gray, 1));
  // Vertical board lines
  for (int i = 0; i < RectangleWidth / BLOCK_SIZE + 1; i++) {
    pPainter.drawLine(mXleft + i * BLOCK_SIZE - 0.5, mYtop,
                      mXleft + i * BLOCK_SIZE - 0.5, mYbottom - 1);
  }
  // Hortizontal boardlines
  for (int i = 0; i < RectangleHeight / BLOCK_SIZE + 1; i++) {
    pPainter.drawLine(mXleft - 1, mYtop + i * BLOCK_SIZE - 1, mXright - 1,
                      mYtop + i * BLOCK_SIZE - 1);
  }
}

/**
 * @brief Draws occupied blocks
 * @param pPainter Painter used for rendering.
 */
void BoardRenderer::DrawOccupiedBlocks(QPainter &pPainter) {
  const int mXleft = GetLeftPixelBoard() / 2;
  const int mYtop = GetBoardTop();

  // Color myColor = GREEN;

  // Colourise the occupied blocks inside the board
  for (int i = 0; i < BOARD_WIDTH; i++) {
    for (int j = 0; j < BOARD_HEIGHT; j++) {
      if (!(mBoard.IsFreeBlock(i, j))) {

        pPainter.fillRect(mXleft + i * BLOCK_SIZE, mYtop + j * BLOCK_SIZE,
                          BLOCK_SIZE - 1, BLOCK_SIZE - 1, Qt::red);
      }
    }
  }
}

/**
 * @brief Gets the left pixel inside the board
 * @return int
 */
int BoardRenderer::GetLeftPixelBoard() const {
  return (width() - BLOCK_SIZE * BOARD_WIDTH);
}

/**
 * @brief Returns the vertical height of the board in pixels.
 * @return Height of board in pixels as an int
 */
int BoardRenderer::GetBoardTop() const {
  return (this->height() - (BLOCK_SIZE * BOARD_HEIGHT + BOARD_LINE_WIDTH)) / 2;
}

/**
 * @brief Returns the horizontal position (in pixels) of the block given like
 * parameter
 * @param pPos: Horizontal position of the block in the board
 * @return X position in pixels as an int
 */
int BoardRenderer::GetXPosInPixels(int pPos) const {
  const int boardWidth = BLOCK_SIZE * BOARD_WIDTH;
  const int boardLeft = (this->width() - boardWidth) / 2;

  return boardLeft + pPos * BLOCK_SIZE;
}

/**
 * @brief Returns the vertical position (in pixels) of the block given like
parameter
* @param pPos: Vertical position of the block in the board
* @return Y position in pixels as an int
*/
int BoardRenderer::GetYPosInPixels(int pPos) const {
  return GetBoardTop() + pPos * BLOCK_SIZE;
}
