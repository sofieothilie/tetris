#include "MainWindow.hpp"

#include <QLabel>
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

  resize(400, 600);

  setCentralWidget(pGameWidget);
}
