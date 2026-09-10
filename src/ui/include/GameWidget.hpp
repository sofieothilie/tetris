#pragma once
#include "BoardRenderer.hpp"
#include "Game.hpp"
#include <QTimer>
#include <QWidget>

class GameWidget : public QWidget {
  Q_OBJECT

public:
  explicit GameWidget(QWidget *parent = nullptr);

protected:
  void keyPressEvent(QKeyEvent *event) override;

private:
  Pieces mPieces;
  Board mBoard;
  Game mGame;
  QTimer mTimer;
  BoardRenderer *mBoardRenderer;
};