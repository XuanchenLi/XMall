#include "myServer.h"
#include"SerThread.h"
myServer::myServer(QObject *parent)
	: QTcpServer(parent)
{
}

myServer::~myServer()
{
}
void myServer::recDateSlot(qintptr data, QByteArray d)
{
	emit SendMsg(data,d);
}
void myServer::incomingConnection(qintptr socketDescriptor)
{
	cli = new QTcpSocket(this);
	cli->setSocketDescriptor(socketDescriptor);
	assert(cli != nullptr);
	SerThread* thread = new SerThread(nullptr, socketDescriptor,cli);
	//emit passSocket(cli);

	//connect(thread, &SerThread::socketDes, this, &myServer::dealsocketDes)
	bool s=connect(thread, &SerThread::recDateSingal, this, &myServer::recDateSlot);
	assert(s == true);
	thread->start();//Æô¶¯Ïß³Ì
}

