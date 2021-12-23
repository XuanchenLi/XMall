#pragma once

#include <QThread>
#include <QNetworkInterface>
#include <QAbstractSocket>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>
#include <QDateTime>
class mySocket;
//Q_DECLARE_METATYPE(qintptr);
class SerThread : public QThread
{
	Q_OBJECT

public:
	SerThread(QObject *parent , qintptr socket,QTcpSocket*);
	~SerThread();
private:
	qintptr p;//Des
	QTcpSocket* cli;
	mySocket* socket;
	virtual void run();
signals:
	void recDateSingal(qintptr, QByteArray);
public slots:
	void sendDateSlot(qintptr, QByteArray);

};
