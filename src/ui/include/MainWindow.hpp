#pragma once

#include "GameWidget.hpp"
#include "MenuWidget.hpp"
#include <QMainWindow>

class MainWindow : public QMainWindow {
  Q_OBJECT
private:
  GameWidget *pGameWidget;
  MenuWidget *pMenuWidget;

private slots:
  void startNewGame();
  void continueGame();
  void showHighscores();
  void showSettings();

protected:
  void paintEvent(QPaintEvent *event) override;

public:
  explicit MainWindow(QWidget *parent = nullptr);
};
