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

    //���������ӿͻ���
    connect(this, SIGNAL(newClient(qintptr socketDescriptor)), mServer, SLOT(incomingConnection(qintptr socketDescriptor)));
    connect(mServer, SIGNAL(newConnection()), this, SLOT(newConnectionSignal()));//������˵�newConnection�źźͲۺ�����
    connect(mServer, &myServer::SendMsg, this, &Service::readyReadSignal);//ת����Ϣ
    connect(mServer, SIGNAL(myServer::passSocket(QTcpSocket*)), this, SLOT(setCli(QTcpSocket*)));
}

void Service::showIpAddress()
{
    QList<QHostAddress> ipList = QNetworkInterface::allAddresses();//ȡ�����л�ԾIP
    QStringList address;
    address.clear();
    for (int index = 0; index < ipList.size(); index++)
    {
        if (ipList.at(index).isNull())   continue;      
        QAbstractSocket::NetworkLayerProtocol protocol = ipList.at(index).protocol();//��ȡ��ǰip��Э��
        if (protocol != QAbstractSocket::IPv4Protocol)   continue;//ֻȡIPV4
        address.append(ipList.at(index).toString());
    }
    ui.comboBox_Address->addItems(address);//��ӵ������˵�
}
void Service::on_listen_clicked()
{
    QString serverAddressStr = ui.comboBox_Address->currentText();//��ȡ������Ŀ��ip��ַ
    quint16 port = ui.lineEdit_port->text().toInt();//��ȡ������Ŀ��˿�
    QHostAddress serverAddress = QHostAddress(serverAddressStr);//��ʼ��Э����

    if (mServer->isListening())
    {
        //�ڼ���״̬ ȡ������
        mServer->close();
        ui.pushButton_listen->setText(QString::fromLocal8Bit("����"));
    }
    else
    {
        //���ڼ���״̬ ��ʼ����
        if (mServer->listen(serverAddress, port))
        {
            ui.pushButton_listen->setText(QString::fromLocal8Bit("ֹͣ����"));
        }
        
    }
}
void Service::newConnectionSignal()//���û�����ʱ���͵��ź�
{
    mClient = mServer->cli;
    QString client_msg; 
    mClientList.append(mClient);
    //mClient = mServer->nextPendingConnection();
    //assert(mClient != nullptr);
    //emit newClient(mClient->socketDescriptor());//���淢���źŸ�myServer
    client_msg = mClient->peerAddress().toString() + ":" + QString::number(mClient->peerPort());
    ui.listWidget_client->addItem(client_msg);
    ui.textBrowser_recv->append(client_msg + QString::fromLocal8Bit("��������"));
    //connect(mClient, SIGNAL(readyRead()), this, SLOT(readyReadSignal()));//������Ϣ�źźͲۺ�����
    connect(mClient, SIGNAL(disconnected()), this, SLOT(disconnectedSignal(mClient)));//�Ͽ������źźͲۺ�����
}
void Service::readyReadSignal(qintptr Des, QByteArray data)
{
    
    //QByteArray recvArray;
    QTcpSocket* current = nullptr;
    if (!mClientList.isEmpty())
    {
        //���տͻ�������
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
        //ת���������ͻ���
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
    Client_msg += QString::fromLocal8Bit("�ѶϿ�");
    ui.textBrowser_recv->append(Client_msg);
}
void Service::on_send_clicked()
{
    QString sendString = ui.plainTextEdit_send->toPlainText();
    QByteArray send_msg = sendString.toLocal8Bit();

    //Ⱥ�������пͻ�������
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
