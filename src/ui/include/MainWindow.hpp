#pragma once

#include "GameWidget.hpp"
#include <QMainWindow>

class MainWindow : public QMainWindow {
  Q_OBJECT
private:
  GameWidget *pGameWidget;

protected:
  void paintEvent(QPaintEvent *event) override;

public:
  explicit MainWindow(QWidget *parent = nullptr);
};
