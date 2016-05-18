#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QtNetwork>
#include "cimplupta.h"
#include "gamemenu.h"
#include "corabiemenu.h"
#include "logmenu.h"
#include "statistica.h"
#include "chatclient.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:

        QHBoxLayout* centralWidgetLayout;
        CimpLupta* myBF; // cimpul meu
        CimpLupta* enemyBF; // cimpul ofonentului
        GameMenu* gMenu; // menu joc
        CorabieMenu* ssMenu; // meniu amplasare corabii
        LogMenu* lMenu; // log
        QLabel* myShips;
        QLabel* enemyShips;
        ChatClient *chatClient;

        char abc[10];

        bool isServer; // daca aplicatia este in calitate de server
        bool clientGata; // clientul e gata
        bool serverGata; // serverul e gata
        GAME_STATUS gstatus; // starea jocului
        Statistica statLupta; // statistica
        bool gameover; // GAME OVER

        //retea
        QString ipAdress; // IP
        int port; // port
        QTcpServer *tcpServer; // TCP server
        QTcpSocket *tcpSocket; // TCP port
        quint16 blockSize; // marimea pachetului

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;



public slots:
    void creazaJoc(); // joc nou
    void conectareLaJoc(); // conectare la joc
    void inapoiLaMenu(); // meniul jocului
    void startJoc(); // de la redactor la inceputul jocului
    void incearcaStartJoc(); // serverul verifica daca ambii jucatori sun gata
    void gameOver(PLAYERS pl); // sfirsit


    //retea
    void startServer(); // start TCP server
    void stopServer(); // stop TCP server
    void startClient(); // start TCP client
    void stopClient(); // stop TCP client
    bool conectareLaServer(); // conectare la sever
    void acceptaConexiune(); //accepta conexiune
    void citireDinSocket(); // citire date
    void transmiteRind(int x, int y); // transmitem miscarea oponentului
    void transmiteRindRaspuns(int x, int y, CELL_STATUS st, Corabie* s); // raspuns
    void transmiteGataServer(); // transmitem starea la server
    void transmiteStareJoc(GAME_STATUS st); // serverul decide a cui este I miscare
    void displayEroare(QAbstractSocket::SocketError socketError); // eroare
};

#endif // MAINWINDOW_H
