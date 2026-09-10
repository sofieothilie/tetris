#include "MainWindow.hpp"

#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), pGameWidget(new GameWidget(this)) {
  setWindowTitle("Tetris");

  resize(400, 600);

  // pGameWidget->setFixedSize(400, 600);

  // auto *container = new QWidget(this);
  // auto *layout = new QVBoxLayout(container);

  // layout->addWidget(pGameWidget, 0, Qt::AlignCenter);

  setCentralWidget(pGameWidget);
}
