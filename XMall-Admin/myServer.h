#pragma once

#include <QTcpServer>
#include"SerThread.h"
//Q_DECLARE_METATYPE(qintptr);
class myServer : public QTcpServer
{
	Q_OBJECT

private:

public:
	myServer(QObject *parent = Q_NULLPTR);
	virtual void incomingConnection(qintptr socketDescriptor);
	~myServer();
	QTcpSocket* cli;
signals:
	void SendMsg(qintptr, QByteArray);
	void passSocket(QTcpSocket*);
public slots:
	void recDateSlot(qintptr, QByteArray);
};
