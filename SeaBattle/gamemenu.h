#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

//clasa meniului jocului

class GameMenu : public QWidget
{
    Q_OBJECT

private:
    QPushButton *createGame; //butonul "New Game"
    QPushButton *connectToGame; //butonul "Connect"

    QLabel      *gameLabel;

public:
    explicit GameMenu(QWidget *parent = 0);


signals:
    void createGameClicked(); //semnalul butonului "New Game"
    void connectToGameClicked(); //semnalul butonului "Connect"


public slots:
};

#endif // GAMEMENU_H
