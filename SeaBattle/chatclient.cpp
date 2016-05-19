#include "chatclient.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QLabel>
#include <QLineEdit>
#include <QTcpSocket>
#include <QBuffer>
#include <QSpinBox>
#include <QErrorMessage>
#include <mainwindow.h>
#include <QPalette>

static const quint16 DEFAULT_PORT = 6667;

ChatClient::ChatClient(QWidget *parent, Qt::WindowFlags flags)
    : QWidget(parent,flags)
{   cor = new CorabieMenu(&ipAdress,&port1);
    QVBoxLayout *main = new QVBoxLayout(this);
    QGridLayout *top  = new QGridLayout;
    QHBoxLayout *bottom = new QHBoxLayout;

    QLabel *label = new QLabel("Server",this);
    server = new QLineEdit(this);
    port = new QSpinBox(this);
    conn = new QPushButton("Connect:",this);
    port->setRange(1,32767);
    port->setValue(DEFAULT_PORT);
    server->setText(ipAdress);
    top->addWidget(label,0,0);
    top->addWidget(server,0,1);
    top->addWidget(port,0,2);

    label = new QLabel("Nick:",this);
    nick = new QLineEdit(this);
    nick->setText("Anonymus");
    top->addWidget(label,1,0);
    top->addWidget(nick,1,1);
    top->addWidget(conn,1,2);

    chat = new QTextEdit(this);
    chat->setReadOnly(true);

    label = new QLabel("Message:",this);
    message = new QLineEdit(this);
    send = new QPushButton("Send",this);
    send->setDefault(true);
    bottom->addWidget(label);
    bottom->addWidget(message);
    bottom->addWidget(send);

    main->addLayout(top);
    main->addWidget(chat);
    main->addLayout(bottom);
    setLayout(main);

    buffer = new QBuffer(this);
    socket = new QTcpSocket(this);
    buffer->open(QIODevice::ReadWrite);

   

}

ChatClient::~ChatClient()
{
    
}

void ChatClient::setConnected()
{
   
}

void ChatClient::setDisconnected()
{
    
}

void ChatClient::toggleConnection()
{
    
}

void ChatClient::sendMessage()
{
    
}

void ChatClient::receiveMessage()
{
   
}

