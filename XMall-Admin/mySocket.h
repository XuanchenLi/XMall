#pragma once

#include <QTcpSocket>
//Q_DECLARE_METATYPE(qintptr);
class mySocket : public QTcpSocket
{
	Q_OBJECT

public:
	mySocket(QObject *parent,qintptr socket, QTcpSocket* c);
	~mySocket();
	QTcpSocket* cli;
	qintptr socketDes;
signals:
	void disconnected();
	void CliSend(qintptr, QByteArray);
};
