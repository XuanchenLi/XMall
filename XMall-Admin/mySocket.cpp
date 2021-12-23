#include "mySocket.h"

mySocket::mySocket(QObject *parent, qintptr socket,QTcpSocket*c)
	: QTcpSocket(parent)
{
	this->socketDes = socket;
    cli = c;
    connect(this, &mySocket::readyRead,
        [=]()
        {
            //QString ip = peerAddress().toString().remove(0, 7);
            QByteArray dat = readAll();
            
            emit CliSend(socket,dat);
        });
}

mySocket::~mySocket()
{
}
