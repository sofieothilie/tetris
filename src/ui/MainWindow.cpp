#include "MainWindow.hpp"

#include <QGridLayout>
#include <QLabel>
#include <QPaintEvent>
#include <QPainter>
#include <QVBoxLayout>
#include <QWidget>

/**
 * @brief Creates the main application window.
 *
 * Creates the game widget and assigns it as the central widget. Qt owns the
 * game widget through the parent-child relationship.
 *
 * @param QWidget parent Optional Qt parent widget.
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), pGameWidget(new GameWidget(this)) {
  setWindowTitle("Tetris");

  auto *centralWidget = new QWidget(this);
  centralWidget->setFixedSize(488, 740);
  auto *grid = new QGridLayout(centralWidget);

  // auto *topWidget = new QWidget(centralWidget);
  // topWidget->setFixedHeight(100);

  // grid->addWidget(topWidget, 0, 0);
  grid->addWidget(pGameWidget, 0, 0);

  // Row 1 receives all extra space.
  // grid->setRowStretch(1, 1);

  setCentralWidget(centralWidget);
}

void MainWindow::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  QPixmap pixmap("resources/images/background.png");

  // Scale the image to fit the current widget size smoothly
  QPixmap scaledPixmap = pixmap.scaled(
      this->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

  painter.drawPixmap(0, 0, scaledPixmap);
  QWidget::paintEvent(event);
}
