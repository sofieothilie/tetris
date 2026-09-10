#pragma once
#include "Game.hpp"
#include <QTimer>
#include <QWidget>

#define BOARD_LINE_WIDTH                                                       \
  6                   // Width of each of the two lines that delimit the board
#define BLOCK_SIZE 16 // Width and Height of each block of a piece
#define MIN_VERTICAL_MARGIN 20 // Minimum vertical margin for the board limit
#define MIN_HORIZONTAL_MARGIN                                                  \
  20 // Minimum horizontal margin for the board limit

class GameWidget : public QWidget {
  Q_OBJECT

public:
  explicit GameWidget(QWidget *parent = nullptr);

protected:
  void paintEvent(QPaintEvent *event) override;
  void keyPressEvent(QKeyEvent *event) override;

private:
  Pieces mPieces;
  Board mBoard;
  Game mGame;
  QTimer mTimer;

  int GetXPosInPixels(int pPos) const;
  int GetYPosInPixels(int pPos) const;
  int GetBoardTop() const;

  void DrawPiece(QPainter &painter, int pX, int pY, int pPiece, int pRotation);
  void DrawBoard(QPainter &painter);
  void DrawScene(QPainter &painter);
};