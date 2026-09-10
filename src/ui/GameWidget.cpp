#include "GameWidget.hpp"
#include "BoardRenderer.hpp"
#include "Game.hpp"

#include <QKeyEvent>
#include <QTimer>
#include <QVBoxLayout>

/**
 * @brief Widget responsible for displaying and controlling a Tetris game.
 *
 * Owns the game model, updates it through a timer, handles keyboard input,
 * and renders the board and active pieces.
 * @param QWidget parent: Optional Qt parent widget.
 */
GameWidget::GameWidget(QWidget *parent)
    : QWidget(parent), mPieces(), mBoard(mPieces), mGame(mBoard, mPieces),
      mTimer(), mBoardRenderer(new BoardRenderer(mGame, mBoard, mPieces)) {

  auto *layout = new QVBoxLayout(this);
  layout->setContentsMargins(0, 0, 0, 0);
  layout->addWidget(mBoardRenderer);

  mBoardRenderer->setMinimumHeight(368);

  mBoardRenderer->setFocusPolicy(Qt::NoFocus);
  setFocusPolicy(Qt::StrongFocus);
  setFocus();

  connect(&mTimer, &QTimer::timeout, this, [this] {
    mGame.MoveDown();
    update();
  });

  setFocusPolicy(Qt::StrongFocus);
  setFocus();

  mTimer.start(WAIT_TIME);
}

/**s
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

  mBoardRenderer->update();
}
