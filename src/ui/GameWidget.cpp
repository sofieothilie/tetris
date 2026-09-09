#include "GameWidget.hpp"
#include "Game.hpp"

#include <QColor>
#include <QKeyEvent>
#include <QLabel>
#include <QPainter>
#include <QTimer>

GameWidget::GameWidget(QWidget *parent)
    : QWidget(parent), mPieces(), mBoard(new Board(mPieces)),
      mGame(new Game(mBoard, mPieces)), mTimer(this) {
  connect(&mTimer, &QTimer::timeout, this, [this] {
    mGame->Update();
    update();
  });

  setFocusPolicy(Qt::StrongFocus);
  setFocus();

  mTimer.start(WAIT_TIME);
}

void GameWidget::paintEvent(QPaintEvent *) {
  QPainter painter(this);
  DrawScene(painter);
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
void GameWidget::DrawPiece(QPainter &painter, int pX, int pY, int pPiece,
                           int pRotation) {

  // Obtain the position in pixel in the screen of the block we want to draw
  int mPixelsX = GetXPosInPixels(pX);
  int mPixelsY = GetYPosInPixels(pY);

  // Travel the matrix of blocks of the piece and draw the blocks that are
  // filled
  for (int i = 0; i < PIECE_BLOCKS; i++) {
    for (int j = 0; j < PIECE_BLOCKS; j++) {
      int blockType = mPieces->GetBlockType(pPiece, pRotation, i, j);
      if (blockType == 0) {
        continue;
      }
      QColor mColour = blockType == 1 ? Qt::green : Qt::blue;
      painter.fillRect(mPixelsX + i * BLOCK_SIZE, mPixelsY + j * BLOCK_SIZE,
                       BLOCK_SIZE - 1, BLOCK_SIZE - 1, mColour);
    }
  }
}

/*
======================================
Draw board

Draw the two lines that delimit the board
======================================
*/
void GameWidget::DrawBoard(QPainter &painter) {

  // Calculate the limits of the board in pixels
  const int boardWidth = BLOCK_SIZE * BOARD_WIDTH;
  const int mX1 = (width() - boardWidth) / 2;
  const int mX2 = mX1 + boardWidth;
  const int mY = GetBoardTop();
  assert(mY > MIN_VERTICAL_MARGIN);

  int boardBottom = mY + BLOCK_SIZE * BOARD_HEIGHT;

  // Colourise the outer edges of the board
  // Left edge
  painter.fillRect(mX1 - BOARD_LINE_WIDTH - 1, mY, BOARD_LINE_WIDTH,
                   boardBottom + BOARD_LINE_WIDTH - mY, Qt::blue);

  // Right edge
  painter.fillRect(mX2, mY, BOARD_LINE_WIDTH,
                   boardBottom + BOARD_LINE_WIDTH - mY, Qt::blue);

  // Bottom edge
  painter.fillRect(mX1 - BOARD_LINE_WIDTH - 1, boardBottom,
                   mX2 + BOARD_LINE_WIDTH - (mX1 - BOARD_LINE_WIDTH - 1),
                   BOARD_LINE_WIDTH, Qt::blue);
  // Bottom edge
  painter.fillRect(mX1 - BOARD_LINE_WIDTH, GetBoardTop(),
                   mX2 + BOARD_LINE_WIDTH - (mX1 - BOARD_LINE_WIDTH - 1),
                   BOARD_LINE_WIDTH, Qt::blue);

  // Colourise the occupied blocks inside the board
  for (int i = 0; i < BOARD_WIDTH; i++) {
    for (int j = 0; j < BOARD_HEIGHT; j++) {
      if (!(mBoard->IsFreeBlock(i, j))) {
        painter.fillRect(mX1 + i * BLOCK_SIZE, mY + j * BLOCK_SIZE,
                         BLOCK_SIZE - 1, BLOCK_SIZE - 1, Qt::red);
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
void GameWidget::DrawScene(QPainter &painter) {
  DrawBoard(
      painter); // Draw the delimitation lines and blocks stored in the board
  DrawPiece(painter, mGame->mPosX, mGame->mPosY, mGame->mPiece,
            mGame->mRotation); // Draw the playing piece
  DrawPiece(painter, mGame->mNextPosX, mGame->mNextPosY, mGame->mNextPiece,
            mGame->mNextRotation); // Draw the next piece
}

void GameWidget::keyPressEvent(QKeyEvent *event) {
  switch (event->key()) {
  case Qt::Key_Escape:
    return;
  case Qt::Key_Left:
  case Qt::Key_A:
    mGame->MoveLeft();
    break;

  case Qt::Key_Right:
  case Qt::Key_D:
    mGame->MoveRight();
    break;

  case Qt::Key_Down:
  case Qt::Key_S:
    mGame->MoveDown();
    break;

  case Qt::Key_Space:
  case Qt::Key_X:
    mGame->Drop();
    break;

  case Qt::Key_Z:
  case Qt::Key_Up:
  case Qt::Key_W:
    mGame->Rotate();
    break;

  default:
    QWidget::keyPressEvent(event);
    return;
  }

  update();
}

/*
======================================
Returns the horizontal position (in pixels) of the block given like parameter

Parameters:

>> pPos: Horizontal position of the block in the board
======================================
*/
int GameWidget::GetXPosInPixels(int pPos) {
  const int boardWidth = BLOCK_SIZE * BOARD_WIDTH;
  const int boardLeft = (width() - boardWidth) / 2;

  return boardLeft + pPos * BLOCK_SIZE;
}
/*
======================================
Returns the vertical position (in pixels) of the block given like parameter

Parameters:

>> pPos: Vertical position of the block in the board
======================================
*/
int GameWidget::GetYPosInPixels(int pPos) {
  return GetBoardTop() + pPos * BLOCK_SIZE;
}

/*
======================================
Returns the vertical height of the board in pixels.
======================================
*/
int GameWidget::GetBoardTop() {
  return (this->height() - (BLOCK_SIZE * BOARD_HEIGHT + BOARD_LINE_WIDTH)) / 2;
}