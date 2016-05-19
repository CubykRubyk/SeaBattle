#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QWidget>
#include <corabiemenu.h>


class QBuffer;
class QSpinBox;
class QLineEdit;
class QTextEdit;
class QTcpSocket;
class QPushButton;

class ChatClient : public QWidget
{
    Q_OBJECT

public:
    ChatClient(QWidget *parent = 0, Qt::WindowFlags flags = 0);
    ~ChatClient();

private slots:
    void setConnected();
    void setDisconnected();
    void toggleConnection();
    void sendMessage();
    void receiveMessage();


private:

        QBuffer         *buffer;
        QSpinBox*		port;
        QLineEdit*		nick;
        QLineEdit*		server;
        QLineEdit*		message;
        QTextEdit*		chat;
        QTcpSocket*		socket;
        QPushButton*	conn;
        QPushButton*	send;
        bool ans;
        CorabieMenu *cor;
        QString ipAdress;
        int port1;

};

#endif // CHATCLIENT_H
