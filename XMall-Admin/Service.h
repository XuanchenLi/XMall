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
    void showIpAddress();               //枚举所有端口
    myServer* mServer;                //服务器socket
    QTcpSocket* mClient = nullptr;      //客户端socket
    QList<QTcpSocket*>mClientList;     //客户端链表，实现多客户
private slots:
    void on_listen_clicked();//开始监听端口
    void newConnectionSignal();//新连接
    void disconnectedSignal(QTcpSocket*);//断开连接
    void readyReadSignal(qintptr, QByteArray);//接收消息的槽函数
    void on_send_clicked();  //发送消息
    void setCli(QTcpSocket*);
signals:
    void newClient(qintptr socketDescriptor);
};
