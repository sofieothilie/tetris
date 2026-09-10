#pragma once
#include "Game.hpp"
#include <QWidget>

#define BOARD_LINE_WIDTH                                                       \
  6                   // Width of each of the two lines that delimit the board
#define BLOCK_SIZE 16 // Width and Height of each block of a piece
#define MIN_VERTICAL_MARGIN 20 // Minimum vertical margin for the board limit
#define MIN_HORIZONTAL_MARGIN                                                  \
  20 // Minimum horizontal margin for the board limit

class BoardRenderer : public QWidget {
  Q_OBJECT

public:
  explicit BoardRenderer(Game &pGame, Board &pBoard, Pieces &pPieces,
                         QWidget *parent = nullptr);

protected:
  void paintEvent(QPaintEvent *event) override;

private:
  Game &mGame;
  Board &mBoard;
  Pieces &mPieces;

  int GetXPosInPixels(int pPos) const;
  int GetYPosInPixels(int pPos) const;
  int GetBoardTop() const;

  void DrawPiece(QPainter &pPainter, int pX, int pY, int pPiece, int pRotation);
  void DrawBoard(QPainter &pPainter);
  void DrawScene(QPainter &pPainter);
};