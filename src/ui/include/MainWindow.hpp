#pragma once

#include "GameWidget.hpp"
#include <QMainWindow>

class MainWindow : public QMainWindow {
  Q_OBJECT
private:
  GameWidget *pGameWidget;

public:
  explicit MainWindow(QWidget *parent = nullptr);
};
