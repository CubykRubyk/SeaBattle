#include "gamemenu.h"

GameMenu::GameMenu(QWidget *parent) : QWidget(parent)
{
    //aranjamentul widget-ului

    QVBoxLayout *layout = new QVBoxLayout(this);
    QHBoxLayout *nameLayout = new QHBoxLayout();
    gameLabel = new QLabel(tr("*SEA BATTLE*"));
    QFont font;
    font.setBold(true);
    font.setPixelSize(25);
    gameLabel->setFont(font);
    createGame = new QPushButton(tr("New Game"));
    connectToGame = new QPushButton(tr("Connect"));

    nameLayout->addStretch();
    nameLayout->addWidget(gameLabel);
    nameLayout->addStretch();
    layout->addLayout(nameLayout);
    //adaugam butoanele
    layout->addWidget(createGame);
    layout->addWidget(connectToGame);

    layout->addStretch();

    //conectam semnalele si slot-urile
    connect(createGame,SIGNAL(clicked()),this,SIGNAL(createGameClicked()));
    connect(connectToGame,SIGNAL(clicked()),this,SIGNAL(connectToGameClicked()));

}
