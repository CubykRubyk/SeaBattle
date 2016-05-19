#ifndef CORABIEMENU_H
#define CORABIEMENU_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QGroupBox>
#include <QLineEdit>
#include "comun.h"

class CorabieMenu : public QWidget
{
    Q_OBJECT
private:
    QGroupBox *corabiiGB;
    //butoanele adaugarii corabiilor
    QPushButton *adaugaCorabie1;
    QPushButton *adaugaCorabie2;
    QPushButton *adaugaCorabie3;
    QPushButton *adaugaCorabie4;

    //label pt afisarea numarului de corabii
    QLabel *corabie1Label;
    QLabel *corabie2Label;
    QLabel *corabie3Label;
    QLabel *corabie4Label;

    //variabile care contin numarul de corabii pe cimp
    int corabie1PeCimp;
    int corabie2PeCimp;
    int corabie3PeCimp;
    int corabie4PeCimp;

    QPushButton *stergeCorabie;
    QPushButton *play;
    QPushButton *inapoi;
    QPushButton *roteste;
    QPushButton *random;

    QLabel *statusLabel; //pt afisarea informatiei despre a cui este miscarea

    QLineEdit *ipLineEdit; //pt introdus ip
    QLineEdit *portLineEdit; //pt introdus portul
    QLabel *ipLabel;
    QLabel *portLabel;

    int dimCorAct; //dimensiunea corabiei active
    bool conflict; //conflic la aranjare in cimp
    bool yesServer; //daca exemplarul programei este server

    QString *ipAdress;
    int *port;

public:
    explicit CorabieMenu(QString *_ipAdress,int *_port, QWidget *parent = 0);
    void setServer(bool val); //set-er pentru yesServer


signals:
    void inapoiClicked();
    void rotesteClicked();
    void adaugaCorabieClicked(int size);
    void stergeCorabieCimp();
    void genereazaRandom();
    void playClicked();
    void transmiteIP(QString ip);

public slots:
    void corabieActivata(bool val,int size); //slotul ce prelucreaza informatia despre activarea corabiei
    //sloturi ce prelucreaza apasarea
    //butonului pt adaugarea corabiilor
    void adaugaCorabie1Clicked();
    void adaugaCorabie2Clicked();
    void adaugaCorabie3Clicked();
    void adaugaCorabie4Clicked();
    void corabieConflict(bool val); //prelucreaza informatia despre conflict
    void stergeCorabieClicked();
    void reset();
    void genereazaRandomClicked();
    void updatePlayState(); //verifica daca toate corabiile au fost plasate
    void setStatusLabelText(QString text);
    void ipEditat(); //editarea cimpului IP
    void portEditat(); //editarea cimpului PORT
};

#endif // CORABIEMENU_H
