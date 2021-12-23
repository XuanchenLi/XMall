#include "SerThread.h"
#include"mySocket.h"
SerThread::SerThread(QObject *parent, qintptr sock,QTcpSocket*c)
	: QThread(parent)
{
	this->p = sock;
    cli = c;
    socket = new mySocket(0, this->p, this->cli);
    socket->setSocketDescriptor(this->p);
    connect(socket, &mySocket::disconnected, this, &SerThread::quit, Qt::DirectConnection);
    bool s = connect(socket, &mySocket::CliSend, this, &SerThread::sendDateSlot);//向上传消息
    assert(s == true);
	connect(this, SIGNAL(finished()), SLOT(deletLater()));
}

SerThread::~SerThread()
{
}
void SerThread::sendDateSlot(qintptr data, QByteArray d)
{
    emit recDateSingal(data,d);
}
void SerThread::run()
{
    //socket = new mySocket(0, this->p,this->cli);
    //socket->setSocketDescriptor(this->p);
    //connect(socket, &mySocket::disconnected, this, &SerThread::quit, Qt::DirectConnection);
    //bool s=connect(socket, &mySocket::CliSend, this, &SerThread::sendDateSlot);//向上传消息
    //assert(s == true);
    this->exec();
}
