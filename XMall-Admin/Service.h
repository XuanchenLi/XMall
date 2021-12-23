#pragma once

#include <QtWidgets/QWidget>
#include "ui_Service.h"
#include <QNetworkInterface>
#include <QAbstractSocket>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>
#include <QDateTime>
#include"myServer.h"
using namespace std;

class Service : public QWidget
{
    Q_OBJECT

public:
    Service(QWidget *parent = Q_NULLPTR);
private:
    Ui::ServiceClass ui;
    void showIpAddress();               //ö�����ж˿�
    myServer* mServer;                //������socket
    QTcpSocket* mClient = nullptr;      //�ͻ���socket
    QList<QTcpSocket*>mClientList;     //�ͻ�������ʵ�ֶ�ͻ�
private slots:
    void on_listen_clicked();//��ʼ�����˿�
    void newConnectionSignal();//������
    void disconnectedSignal(QTcpSocket*);//�Ͽ�����
    void readyReadSignal(qintptr, QByteArray);//������Ϣ�Ĳۺ���
    void on_send_clicked();  //������Ϣ
    void setCli(QTcpSocket*);
signals:
    void newClient(qintptr socketDescriptor);
};
