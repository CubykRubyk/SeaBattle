#ifndef LOGMENU_H
#define LOGMENU_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QTextBrowser>
#include <QGroupBox>
#include "comun.h"
#include "statistica.h"

class LogMenu : public QWidget
{
    Q_OBJECT
private:
    QTextBrowser *logText; //text browser unde se afiseaza log-ul
    GAME_STATUS *gstatus; //pointer la statutul jocului
    Statistica *statLupta; //pointer la obiect din clasa statisticii
    QLabel *statusLabel;
    QGroupBox *myCorabiiGB;
    QGroupBox *enemyCorabiiGB;
    QLabel *myCorabiiLabel;
    QLabel *enemyCorabiiLabel;
public:
    explicit LogMenu( GAME_STATUS *_gstatus,  Statistica *_statLupta, QWidget *parent = 0);
signals:

public slots:
    void adaugaLogString(QString text); //adaugam text in log
    void updateStatusLabel(); //update la statistica
};




#endif // LOGMENU_H
