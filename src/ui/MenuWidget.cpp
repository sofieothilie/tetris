#include "MenuWidget.hpp"

#include <QPushButton>
#include <QVBoxLayout>

MenuWidget::MenuWidget(QWidget *parent)
    : QWidget(parent), newGameButton(new QPushButton("New Game", this)),
      continueButton(new QPushButton("Continue Game", this)),
      highscoreButton(new QPushButton("High Score", this)),
      settingsButton(new QPushButton("Settings", this)),
      quitButton(new QPushButton("Quit", this)) {
  auto *layout = new QVBoxLayout(this);

  layout->addWidget(newGameButton);
  layout->addWidget(continueButton);
  layout->addWidget(highscoreButton);
  layout->addWidget(settingsButton);
  layout->addWidget(quitButton);

  connect(newGameButton, &QPushButton::clicked, this,
          &MenuWidget::newGameClicked);

  connect(continueButton, &QPushButton::clicked, this,
          &MenuWidget::continueClicked);
  connect(highscoreButton, &QPushButton::clicked, this,
          &MenuWidget::highscoreClicked);
  connect(settingsButton, &QPushButton::clicked, this,
          &MenuWidget::settingsClicked);

  connect(quitButton, &QPushButton::clicked, this, &MenuWidget::quitClicked);
}

