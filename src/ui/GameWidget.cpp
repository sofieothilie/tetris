#include "GameWidget.hpp"
#include "Game.hpp"

#include <QColor>
#include <QKeyEvent>
#include <QLabel>
#include <QPainter>
#include <QTimer>

/**
 * @brief Widget responsible for displaying and controlling a Tetris game.
 *
 * Owns the game model, updates it through a timer, handles keyboard input,
 * and renders the board and active pieces.
 * @param QWidget parent: Optional Qt parent widget.
 */
GameWidget::GameWidget(QWidget *parent)
    : QWidget(parent), mPieces(), mBoard(mPieces), mGame(mBoard, mPieces),
      mTimer() {
  connect(&mTimer, &QTimer::timeout, this, [this] {
    mGame.Update();
    update();
  });

  setFocusPolicy(Qt::StrongFocus);
  setFocus();

  mTimer.start(WAIT_TIME);
}

/**
 * @brief Repaints the game widget.
 *
 * Qt calls this function whenever the widget needs to be redrawn. The current
 * board state and active pieces are rendered using a QPainter.
 *
 * @param event Paint event supplied by Qt.
 */
void GameWidget::paintEvent(QPaintEvent *) {
  QPainter painter(this);
  DrawScene(painter);
}

/**
 * @brief Draws a piece on the board
 * @param pPainter Painter used for rendering.
 * @param pX: Horizontal position in blocks
 * @param pY: Vertical position in blocks
 * @param pPiece: Piece to draw
 * @param pRotation: 1 of the 4 possible rotations
 */
void GameWidget::DrawPiece(QPainter &painter, int pX, int pY, int pPiece,
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
 * @brief Draws the board boundary and occupied cells.
 *
 * Calculates the board position within the widget, draws its borders, and
 * renders every occupied board cell.
 *
 * @param pPainter Painter used for rendering.
 */
void GameWidget::DrawBoard(QPainter &pPainter) {

  // Calculate the limits of the board in pixels
  const int boardWidth = BLOCK_SIZE * BOARD_WIDTH;
  const int mX1 = (width() - boardWidth) / 2;
  const int mX2 = mX1 + boardWidth;
  const int mY = GetBoardTop();
  assert(mY > MIN_VERTICAL_MARGIN);

  int boardBottom = mY + BLOCK_SIZE * BOARD_HEIGHT;

  // Colourise the outer edges of the board
  // Left edge
  pPainter.fillRect(mX1 - BOARD_LINE_WIDTH - 1, mY, BOARD_LINE_WIDTH,
                    boardBottom + BOARD_LINE_WIDTH - mY, Qt::blue);

  // Right edge
  pPainter.fillRect(mX2, mY, BOARD_LINE_WIDTH,
                    boardBottom + BOARD_LINE_WIDTH - mY, Qt::blue);

  // Bottom edge
  pPainter.fillRect(mX1 - BOARD_LINE_WIDTH - 1, boardBottom,
                    mX2 + BOARD_LINE_WIDTH - (mX1 - BOARD_LINE_WIDTH - 1),
                    BOARD_LINE_WIDTH, Qt::blue);
  // Bottom edge
  pPainter.fillRect(mX1 - BOARD_LINE_WIDTH, GetBoardTop(),
                    mX2 + BOARD_LINE_WIDTH - (mX1 - BOARD_LINE_WIDTH - 1),
                    BOARD_LINE_WIDTH, Qt::blue);

  // Colourise the occupied blocks inside the board
  for (int i = 0; i < BOARD_WIDTH; i++) {
    for (int j = 0; j < BOARD_HEIGHT; j++) {
      if (!(mBoard.IsFreeBlock(i, j))) {
        pPainter.fillRect(mX1 + i * BLOCK_SIZE, mY + j * BLOCK_SIZE,
                          BLOCK_SIZE - 1, BLOCK_SIZE - 1, Qt::red);
      }
    }
  }
}

/**
 * @brief Draws the complete game scene.
 *
 * Renders the board and its occupied cells, followed by the currently falling
 * piece and the preview of the next piece.
 *
 * @param pPainter Painter used for rendering.
 */
void GameWidget::DrawScene(QPainter &pPainter) {
  DrawBoard(
      pPainter); // Draw the delimitation lines and blocks stored in the board
  DrawPiece(pPainter, mGame.GetPositionX(), mGame.GetPositionY(),
            mGame.GetPiece(),
            mGame.GetRotation()); // Draw the playing piece
  DrawPiece(pPainter, mGame.GetNextPositionX(), mGame.GetNextPositionY(),
            mGame.GetNextPiece(),
            mGame.GetNextRotation()); // Draw the next piece
}

/**
 * @brief Executes a task when a key is pressed
 * @param pEvent: triggered QKeyEvent
 */
void GameWidget::keyPressEvent(QKeyEvent *pEvent) {
  switch (pEvent->key()) {
  case Qt::Key_Escape:
    return;
  case Qt::Key_Left:
  case Qt::Key_A:
    mGame.MoveLeft();
    break;

  case Qt::Key_Right:
  case Qt::Key_D:
    mGame.MoveRight();
    break;

  case Qt::Key_Down:
  case Qt::Key_S:
    mGame.MoveDown();
    break;

  case Qt::Key_Space:
  case Qt::Key_X:
    mGame.Drop();
    break;

  case Qt::Key_Z:
  case Qt::Key_Up:
  case Qt::Key_W:
    mGame.Rotate();
    break;

  default:
    QWidget::keyPressEvent(pEvent);
    return;
  }

  update();
}

/**
 * @brief Returns the horizontal position (in pixels) of the block given like
 * parameter
 * @param pPos: Horizontal position of the block in the board
 * @return X position in pixels as an int
 */
int GameWidget::GetXPosInPixels(int pPos) const {
  const int boardWidth = BLOCK_SIZE * BOARD_WIDTH;
  const int boardLeft = (width() - boardWidth) / 2;

  return boardLeft + pPos * BLOCK_SIZE;
}
/**
 * @brief Returns the vertical position (in pixels) of the block given like
parameter
* @param pPos: Vertical position of the block in the board
* @return Y position in pixels as an int
*/
int GameWidget::GetYPosInPixels(int pPos) const {
  return GetBoardTop() + pPos * BLOCK_SIZE;
}

/**
 * @brief Returns the vertical height of the board in pixels.
 * @return Height of board in pixels as an int
 */
int GameWidget::GetBoardTop() const {
  return (this->height() - (BLOCK_SIZE * BOARD_HEIGHT + BOARD_LINE_WIDTH)) / 2;
}