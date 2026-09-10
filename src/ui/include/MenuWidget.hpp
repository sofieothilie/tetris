#pragma once

#include <QWidget>

class QPushButton;

class MenuWidget : public QWidget {
  Q_OBJECT

public:
  explicit MenuWidget(QWidget *parent = nullptr);
  void ShowMenu();

signals:
  void newGameClicked();
  void continueClicked();
  void highscoreClicked();
  void settingsClicked();
  void quitClicked();

private:
  QPushButton *newGameButton;
  QPushButton *continueButton;
  QPushButton *highscoreButton;
  QPushButton *settingsButton;
  QPushButton *quitButton;
};