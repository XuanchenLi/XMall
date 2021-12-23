#include "Service.h"

#include "ui_service.h"
void Service::setCli(QTcpSocket* cli)
{
    mClient = cli;
}
Service::Service(QWidget* parent) :
    QWidget(parent)
{
    ui.setupUi(this);
    mServer = new myServer;
    showIpAddress();

    //处理新连接客户端
    connect(this, SIGNAL(newClient(qintptr socketDescriptor)), mServer, SLOT(incomingConnection(qintptr socketDescriptor)));
    connect(mServer, SIGNAL(newConnection()), this, SLOT(newConnectionSignal()));//将服务端的newConnection信号和槽函数绑定
    connect(mServer, &myServer::SendMsg, this, &Service::readyReadSignal);//转发消息
    connect(mServer, SIGNAL(myServer::passSocket(QTcpSocket*)), this, SLOT(setCli(QTcpSocket*)));
}

void Service::showIpAddress()
{
    QList<QHostAddress> ipList = QNetworkInterface::allAddresses();//取得所有活跃IP
    QStringList address;
    address.clear();
    for (int index = 0; index < ipList.size(); index++)
    {
        if (ipList.at(index).isNull())   continue;      
        QAbstractSocket::NetworkLayerProtocol protocol = ipList.at(index).protocol();//获取当前ip的协议
        if (protocol != QAbstractSocket::IPv4Protocol)   continue;//只取IPV4
        address.append(ipList.at(index).toString());
    }
    ui.comboBox_Address->addItems(address);//添加到下拉菜单
}
void Service::on_listen_clicked()
{
    QString serverAddressStr = ui.comboBox_Address->currentText();//获取服务器目标ip地址
    quint16 port = ui.lineEdit_port->text().toInt();//获取服务器目标端口
    QHostAddress serverAddress = QHostAddress(serverAddressStr);//初始化协议族

    if (mServer->isListening())
    {
        //在监听状态 取消监听
        mServer->close();
        ui.pushButton_listen->setText(QString::fromLocal8Bit("监听"));
    }
    else
    {
        //不在监听状态 开始监听
        if (mServer->listen(serverAddress, port))
        {
            ui.pushButton_listen->setText(QString::fromLocal8Bit("停止监听"));
        }
        
    }
}
void Service::newConnectionSignal()//新用户链接时发送的信号
{
    mClient = mServer->cli;
    QString client_msg; 
    mClientList.append(mClient);
    //mClient = mServer->nextPendingConnection();
    //assert(mClient != nullptr);
    //emit newClient(mClient->socketDescriptor());//界面发送信号给myServer
    client_msg = mClient->peerAddress().toString() + ":" + QString::number(mClient->peerPort());
    ui.listWidget_client->addItem(client_msg);
    ui.textBrowser_recv->append(client_msg + QString::fromLocal8Bit("加入聊天"));
    //connect(mClient, SIGNAL(readyRead()), this, SLOT(readyReadSignal()));//接收消息信号和槽函数绑定
    connect(mClient, SIGNAL(disconnected()), this, SLOT(disconnectedSignal(mClient)));//断开连接信号和槽函数绑定
}
void Service::readyReadSignal(qintptr Des, QByteArray data)
{
    
    //QByteArray recvArray;
    QTcpSocket* current = nullptr;
    if (!mClientList.isEmpty())
    {
        //接收客户端数据
        QString client_msg;
        for (int index = 0; index < mClientList.count(); index++)
        {
            current = mClientList.at(index);
            if (current->socketDescriptor()==Des)
            {
                client_msg = current->peerAddress().toString() + ":" + QString::number(current->peerPort());
                //recvArray = current->readAll();//recv
                if (data.isEmpty()) continue;
                QString str = QString(QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss")) +"["+client_msg+"]\n" + str.fromLocal8Bit(data.data());
                ui.textBrowser_recv->append(str);
                break;
            }
        }
        //转发给其他客户端
        for (int index = 0; index < mClientList.count(); index++)
        {
            QTcpSocket* temp = mClientList.at(index);
            if (current == temp) continue;
            if (temp->isWritable())
            {
                temp->write(data);//send
            }
        }
    }
    
}
void Service::disconnectedSignal(QTcpSocket*client)
{
    QString Client_msg= mClient->peerAddress().toString() + ":" + QString::number(mClient->peerPort());
    Client_msg += QString::fromLocal8Bit("已断开");
    ui.textBrowser_recv->append(Client_msg);
}
void Service::on_send_clicked()
{
    QString sendString = ui.plainTextEdit_send->toPlainText();
    QByteArray send_msg = sendString.toLocal8Bit();

    //群发给所有客户端连接
    if (!mClientList.isEmpty())
    {
        for (int index = 0; index < mClientList.count(); index++)
        {
            QTcpSocket* temp = mClientList.at(index);
            if (temp->isWritable())
            {
                temp->write(send_msg);
            }
        }
    }
    QString str = QString(QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss"))+ "[Service]:Send\n" + sendString;
    ui.textBrowser_recv->append(str);

}
