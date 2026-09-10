#include "MainWindow.hpp"
#include <QGridLayout>
#include <QLabel>
#include <QPaintEvent>
#include <QPainter>
#include <QVBoxLayout>
#include <QWidget>
#include <iostream>

/**
 * @brief Creates the main application window.
 *
 * Creates the game widget and assigns it as the central widget. Qt owns the
 * game widget through the parent-child relationship.
 *
 * @param QWidget parent Optional Qt parent widget.
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), pGameWidget(new GameWidget(this)),
      pMenuWidget(new MenuWidget(this)) {
  setWindowTitle("Tetris");

  auto *centralWidget = new QWidget(this);
  auto *layout = new QVBoxLayout(centralWidget);

  layout->addWidget(pMenuWidget);

  setCentralWidget(centralWidget);

  connect(pMenuWidget, &MenuWidget::newGameClicked, this,
          &MainWindow::startNewGame);

  connect(pMenuWidget, &MenuWidget::continueClicked, this,
          &MainWindow::continueGame);

  connect(pMenuWidget, &MenuWidget::highscoreClicked, this,
          &MainWindow::showHighscores);

  connect(pMenuWidget, &MenuWidget::settingsClicked, this,
          &MainWindow::showSettings);

  connect(pMenuWidget, &MenuWidget::quitClicked, this,
          &QMainWindow::close); // Add an "Are you sure?"-pop up?
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

void MainWindow::startNewGame() {
  std::cout << "New game clicked" << std::endl;
  // pGameWidget->startNewGame();
}

void MainWindow::continueGame() {
  std::cout << "Continue clicked" << std::endl;

  // pGameWidget->continueGame();
}

void MainWindow::showHighscores() {
  std::cout << "show highscore clicked" << std::endl;
  // Open or display the highscores view.
}

void MainWindow::showSettings() {
  std::cout << "show settings clicked" << std::endl;
  // Open or display the settings view.
}