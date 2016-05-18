#include "logmenu.h"
#include "QPalette"

LogMenu::LogMenu(GAME_STATUS *_status, Statistica *_statLuipta, QWidget *parent) : QWidget(parent)
{   gstatus=_status; //atribuim pointer la variabila statusul jocului din MainWindow
    statLupta=_statLupta; //atribuim pointer la obiectul clasei Statistica din MainWindow

    //aranjamentul windgetului
    QVBoxLayout *layout=new QVBoxLayout(this);
    logText=new QTextBrowser();
    QLabel *logLabel=new QLabel(tr("Game Log:"));
    layout->addWidget(logLabel);
    layout->addWidget(logText);
    statusLabel=new Qlabel();
    layout->addWidget(statusLab);
    enemyCorabiiGB=new QGroupBox(tr("Enemy Ships:"));
    QVBoxLayout *eShipsGBLayout=new QVBoxLayout();
    enemyCorabiiLabel=new QLabel();
    eShipsGBLayout->addWidget(enemyCorabiiLabel);
    enemyCorabiiGB->setLayout(eShipsGBLayout);
    myCorabiiGB=new QGroupBox(tr("My Ships:"));
    QVBoxLayout *mShipsGBLayout=new QVBoxLayout();
    myCorabiiLabel= new QLabel;
    mShipsGBLayout->addWidget(myCorabiiLabel);
    myCorabiiGB->setLayout(mShipsGBLayout);
    layout->addWidget(enemyCorabiiGB);
    layout->addWidget(myCorabiiGB);
    updateStatusLabel();
}

void LogMenu::adaugaLogString(QString text)
{
    logText->append(text);
}

void LogMenu::updateStatusLabel()
{
    QFont font;
    font.setBold(true);
    font.setPixelSize(15);
    statusLabel->setFont(font);
    statusLabel->setAlignment(Qt::AlignCenter);
    QPalette palette = statusLabel->palette();
    switch (*gstatus)
    {
    case READY:
        palette.setColor(QPalette::Disabled, QPalette::Foreground, Qt::darkYellow);
        palette.setColor(QPalette::Active, QPalette::Foreground, Qt::darkYellow);
        palette.setColor(QPalette::Inactive, QPalette::Foreground, Qt::darkYellow);
        statusLabel->setPalette(palette);
        statusLabel->setText("WAITING FOR OPPONENT");
        break;
    case YOUR_TURN:
        palette.setColor(QPalette::Normal, QPalette::Foreground, Qt::blue);
        palette.setColor(QPalette::Active, QPalette::Foreground, Qt::blue);
        palette.setColor(QPalette::Inactive, QPalette::Foreground, Qt::blue);
        statusLabel->setPalette(palette);
        statusLabel->setText(tr("YOUR TURN"));
        break;
    case ENEMY_TURN:
        palette.setColor(QPalette::Normal, QPalette::Foreground, Qt::red);
        palette.setColor(QPalette::Active, QPalette::Foreground, Qt::red);
        palette.setColor(QPalette::Inactive, QPalette::Foreground, Qt::red);
        statusLabel->setPalette(palette);
        statusLabel->setText(tr("ENEMY TURN"));
        break;
    }

       enemyCorabiiLabel->setText(tr("Submarine:\t %1/%2\n"
                                     "Destroyer:\t %3/%4\n"
                                     "Cruiser:\t\t %5/%6\n"
                                     "Battleship:\t %7/%8\n")
                             .arg(statLupta->statisticaCorabii(ENEMY, CORABIE1))
                             .arg(CORABIE1_AMOUNT)
                             .arg(statLupta->statisticaCorabii(ENEMY, CORABIE2))
                             .arg(CORABIE2_AMOUNT)
                             .arg(statLupta->statisticaCorabii(ENEMY, CORABIE3))
                             .arg(CORABIE3_AMOUNT)
                             .arg(statLupta->statisticaCorabii(ENEMY, CORABIE4))
                             .arg(CORABIE4_AMOUNT));
      myCorabiiLabel->setText(tr("Submarine:\t %1/%2\n"
                                 "Destroyer:\t %3/%4\n"
                                 "Cruiser:\t\t %5/%6\n"
                                 "Battleship:\t %7/%8\n")
                             .arg(statLupta->statisticaCorabii(ME, CORABIE1))
                             .arg(CORABIE1_AMOUNT)
                             .arg(statLupta->statisticaCorabii(ME, CORABIE2))
                             .arg(CORABIE2_AMOUNT)
                             .arg(statLupta->statisticaCorabii(ME, CORABIE3))
                             .arg(CORABIE3_AMOUNT)
                             .arg(statLupta->statisticaCorabii(ME, CORABIE4))
                             .arg(CORABIE4_AMOUNT));
}
