#include "corabiemenu.h"
#include <QRegExp>
#include <QRegExpValidator>
#include <QFontMetrics>

CorabieMenu::CorabieMenu(QString *_ipAdress,int *_port, QWidget *parent) : QWidget(parent)
{
    ipAdress = _ipAdress;
    port = _port;

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QGridLayout *layout = new QGridLayout();

    corabiiGB = new QGroupBox(tr("Add Ship"));
    QGridLayout *gbLayout = new QGridLayout(corabiiGB);
    adaugaCorabie1 = new QPushButton(tr("Submarine"));
    adaugaCorabie2 = new QPushButton(tr("Destroyer"));
    adaugaCorabie3 = new QPushButton(tr("Cruiser"));
    adaugaCorabie4 = new QPushButton(tr("Battleship"));

    corabie1PeCimp=corabie2PeCimp=corabie3PeCimp=corabie4PeCimp=0;

    corabie1Label = new QLabel(QString::number(corabie1PeCimp) + "/" + QString::number(CORABIE1_AMOUNT));
    corabie2Label = new QLabel(QString::number(corabie2PeCimp) + "/" + QString::number(CORABIE2_AMOUNT));
    corabie3Label = new QLabel(QString::number(corabie3PeCimp) + "/" + QString::number(CORABIE3_AMOUNT));
    corabie4Label = new QLabel(QString::number(corabie4PeCimp) + "/" + QString::number(CORABIE4_AMOUNT));

    gbLayout->addWidget(adaugaCorabie1,0,0,1,1);
    gbLayout->addWidget(corabie1Label,0,1,1,1);
    gbLayout->addWidget(adaugaCorabie2,1,0,1,1);
    gbLayout->addWidget(corabie2Label,1,1,1,1);
    gbLayout->addWidget(adaugaCorabie3,2,0,1,1);
    gbLayout->addWidget(corabie3Label,2,1,1,1);
    gbLayout->addWidget(adaugaCorabie4,3,0,1,1);
    gbLayout->addWidget(corabie4Label,3,1,1,1);

    stergeCorabie = new QPushButton(tr("Delete"));
    roteste = new QPushButton(tr("Rotate"));
    random = new QPushButton(tr("Random"));
    play = new QPushButton(tr("Play"));

    layout->addWidget(corabiiGB,0,0,1,2);
    layout->addWidget(stergeCorabie,1,0,1,1);
    layout->addWidget(roteste,1,1,1,1);
    layout->addWidget(random,2,0,1,1);
    layout->addWidget(play,2,1,1,1);

    statusLabel = new QLabel();
    inapoi = new QPushButton(tr("Back"));

    mainLayout->addLayout(layout);
    mainLayout->addWidget(statusLabel);

    QGridLayout *netLayout = new QGridLayout();
    ipLabel = new QLabel(tr("IP"));
    ipLineEdit = new QLineEdit();
    QRegExp ipRegExp( "\\b(([01]?\\d?\\d|2[0-4]\\d|25[0-5])\\.){3}([01]?\\d?\\d|2[0-4]\\d|25[0-5])\\b" );

       QFontMetrics fm(ipLineEdit->font());
       ipLineEdit->setFixedWidth(fm.size(0, QString("000.000.000.000;_")).width());
       ipLineEdit->setText("127.0.0.1");                                                //
       *ipAdress = ipLineEdit->text();
       emit transmiteIP(*ipAdress);
       netLayout->addWidget(ipLabel, 0, 0, 1, 1);
       netLayout->addWidget(ipLineEdit, 0, 1, 1, 1);
       portLabel = new QLabel(tr("Port:"));
       portLineEdit = new QLineEdit();
       portLineEdit->setFixedWidth(fm.size(0, QString("000.000.000.000;_")).width());
   #ifdef FIXED_PORT
       portLineEdit->setText(QString::number(PORT));
   #endif
       *port = portLineEdit->text().toInt();
       netLayout->addWidget(portLabel, 1, 0, 1, 1);
       netLayout->addWidget(portLineEdit, 1, 1, 1, 1);

       mainLayout->addLayout(netLayout);
       mainLayout->addStretch();
       mainLayout->addWidget(inapoi);

       stergeCorabie->setEnabled(false);
       roteste->setEnabled(false);
       play->setEnabled(false);

       conflict = false;

          connect(inapoi, SIGNAL(clicked()), this, SIGNAL(inapoiClicked()));
          connect(roteste, SIGNAL(clicked()), this, SIGNAL(rotesteClicked()));
          connect(adaugaCorabie1, SIGNAL(clicked()), this, SLOT(adaugaCorabie1Clicked()));
          connect(adaugaCorabie2, SIGNAL(clicked()), this, SLOT(adaugaCorabie2Clicked()));
          connect(adaugaCorabie3, SIGNAL(clicked()), this, SLOT(adaugaCorabie3Clicked()));
          connect(adaugaCorabie4, SIGNAL(clicked()), this, SLOT(adaugaCorabie4Clicked()));
          connect(stergeCorabie, SIGNAL(clicked()), this, SLOT(stergeCorabieClicked()));
          connect(random, SIGNAL(clicked()), this, SLOT(genereazaRandomClicked()));
          connect(play, SIGNAL(clicked()), this, SIGNAL(playClicked()));
          connect(ipLineEdit, SIGNAL(editingFinished()), this, SLOT(ipEditat()));
          connect(portLineEdit, SIGNAL(editingFinished()), this, SLOT(portEditat()));
}

void CorabieMenu::corabieActivata(bool val, int size)
{
    stergeCorabie->setEnabled(val);
    roteste->setEnabled(val);
    dimCorAct=size;
}

void CorabieMenu::adaugaCorabie1Clicked()
{
    corabie1PeCimp++;
    corabie1Label->setText(QString::number(corabie1PeCimp) + "/" + QString::number(CORABIE1_AMOUNT));
    if(corabie1PeCimp == CORABIE1_AMOUNT)
        adaugaCorabie1->setEnabled(false);
    updatePlayState();
    emit adaugaCorabieClicked(CORABIE1);
}

void CorabieMenu::adaugaCorabie2Clicked()
{
   corabie2PeCimp++;
    corabie2Label->setText(QString::number(corabie2PeCimp) + "/" + QString::number(CORABIE2_AMOUNT));
    if(corabie2PeCimp == CORABIE2_AMOUNT)
        adaugaCorabie2->setEnabled(false);
    updatePlayState();
    emit adaugaCorabieClicked(CORABIE2);
}

void CorabieMenu::adaugaCorabie3Clicked()
{
    corabie3PeCimp++;
    corabie3Label->setText(QString::number(corabie3PeCimp) + "/" + QString::number(CORABIE3_AMOUNT));
    if(corabie3PeCimp == CORABIE3_AMOUNT)
        adaugaCorabie3->setEnabled(false);
    updatePlayState();
    emit adaugaCorabieClicked(CORABIE3);
}

void CorabieMenu::adaugaCorabie4Clicked()
{
    corabie4PeCimp++;
    corabie4Label->setText(QString::number(corabie4PeCimp) + "/" + QString::number(CORABIE4_AMOUNT));
    if(corabie4PeCimp == CORABIE4_AMOUNT)
        adaugaCorabie4->setEnabled(false);
    updatePlayState();
    emit adaugaCorabieClicked(CORABIE4);
}

void CorabieMenu::corabieConflict(bool val)
{
    conflict = val;
    if(conflict){
        adaugaCorabie1->setEnabled(false);
        adaugaCorabie2->setEnabled(false);
        adaugaCorabie3->setEnabled(false);
        adaugaCorabie4->setEnabled(false);
    } else{
        if(corabie1PeCimp<CORABIE1_AMOUNT)
            adaugaCorabie1->setEnabled(true);
        if(corabie2PeCimp<CORABIE2_AMOUNT)
            adaugaCorabie2->setEnabled(true);
        if(corabie3PeCimp<CORABIE3_AMOUNT)
            adaugaCorabie3->setEnabled(true);
        if(corabie4PeCimp<CORABIE4_AMOUNT)
            adaugaCorabie4->setEnabled(true);
    }
    updatePlayState();
}

void CorabieMenu::stergeCorabieClicked()
{
  switch(dimCorAct)
  {
  case 1:
          corabie1PeCimp--;
          if(corabie1PeCimp < CORABIE1_AMOUNT)
              adaugaCorabie1->setEnabled(true);
          corabie1Label->setText(QString::number(corabie1PeCimp) + "/" + QString::number(CORABIE1_AMOUNT));
          break;
      case 2:
          corabie2PeCimp--;
          if(corabie2PeCimp < CORABIE2_AMOUNT)
              adaugaCorabie2->setEnabled(true);
          corabie2Label->setText(QString::number(corabie2PeCimp) + "/" + QString::number(CORABIE2_AMOUNT));
          break;
      case 3:
          corabie3PeCimp--;
          if(corabie3PeCimp < CORABIE3_AMOUNT)
              adaugaCorabie3->setEnabled(true);
          corabie3Label->setText(QString::number(corabie3PeCimp) + "/" + QString::number(CORABIE3_AMOUNT));
          break;
      case 4:
          corabie4PeCimp--;
          if(corabie4PeCimp < CORABIE4_AMOUNT)
              adaugaCorabie4->setEnabled(true);
          corabie4Label->setText(QString::number(corabie4PeCimp) + "/" + QString::number(CORABIE4_AMOUNT));
          break;
  }
  updatePlayState();
  emit stergeCorabieCimp();
}

void CorabieMenu::reset()
{
    corabie1PeCimp =  corabie2PeCimp =  corabie3PeCimp =  corabie4PeCimp = 0;
    adaugaCorabie1->setEnabled(true);
    adaugaCorabie2->setEnabled(true);
    adaugaCorabie3->setEnabled(true);
    adaugaCorabie4->setEnabled(true);
    corabie1Label->setText(QString::number( corabie1PeCimp) + "/" + QString::number(CORABIE1_AMOUNT));
    corabie2Label->setText(QString::number( corabie2PeCimp) + "/" + QString::number(CORABIE1_AMOUNT));
    corabie3Label->setText(QString::number( corabie3PeCimp) + "/" + QString::number(CORABIE1_AMOUNT));
    corabie4Label->setText(QString::number( corabie4PeCimp) + "/" + QString::number(CORABIE1_AMOUNT));
    updatePlayState();
}

void CorabieMenu::genereazaRandomClicked()
{
    reset();
    corabie1PeCimp = CORABIE1_AMOUNT;
    corabie2PeCimp = CORABIE2_AMOUNT;
    corabie3PeCimp = CORABIE3_AMOUNT;
    corabie4PeCimp = CORABIE4_AMOUNT;
    adaugaCorabie1->setEnabled(false);
    adaugaCorabie2->setEnabled(false);
    adaugaCorabie3->setEnabled(false);
    adaugaCorabie4->setEnabled(false);
    corabie1Label->setText(QString::number( corabie1PeCimp) + "/" + QString::number(CORABIE1_AMOUNT));
    corabie2Label->setText(QString::number( corabie2PeCimp) + "/" + QString::number(CORABIE2_AMOUNT));
    corabie3Label->setText(QString::number( corabie3PeCimp) + "/" + QString::number(CORABIE3_AMOUNT));
    corabie4Label->setText(QString::number( corabie4PeCimp) + "/" + QString::number(CORABIE4_AMOUNT));
    emit genereazaRandom();
    updatePlayState();
}

void CorabieMenu::updatePlayState()
{
    if( corabie1PeCimp != CORABIE1_AMOUNT)
    {
        play->setEnabled(false);
        return;
    }
    if( corabie2PeCimp != CORABIE2_AMOUNT)
    {
        play->setEnabled(false);
        return;
    }
    if( corabie3PeCimp != CORABIE3_AMOUNT)
    {
        play->setEnabled(false);
        return;
    }
    if( corabie4PeCimp != CORABIE4_AMOUNT)
    {
        play->setEnabled(false);
        return;
    }
    if(conflict == true)
    {
        play->setEnabled(false);
        return;
    }
    play->setEnabled(true);
}

void CorabieMenu::setServer(bool val)
{
    yesServer = val;
    if(yesServer)
    {
        ipLabel->hide();
        ipLineEdit->hide();
        portLabel->hide();
        portLineEdit->hide();
        statusLabel->show();
    }
    else
    {
        ipLabel->show();
        ipLineEdit->show();
        portLabel->show();
        portLineEdit->show();
        statusLabel->hide();
    }
}

void CorabieMenu::setStatusLabelText(QString text)
{
    statusLabel->setText(text);
}

void CorabieMenu::ipEditat()
{
    *ipAdress = ipLineEdit->text();
}

void CorabieMenu::portEditat()
{
    *port = portLineEdit->text().toInt();
}
