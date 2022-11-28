#include "widget.h"
#include "ui_widget.h"

// dfines
#define local QHostAddress::LocalHost
#define portlocal 1234
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("Chat 1");

    mSocket = new QUdpSocket(this);
    mSocket->bind(local,portlocal);
    connect(mSocket, SIGNAL(readyRead()), this, SLOT(leerSocket()));

    // PlainTextEdit
    ui->plainTextEdit->setReadOnly(true);
    ui->plainTextEdit->appendPlainText("My port is:" + QHostAddress(local).toString());
    ui->plainTextEdit->appendPlainText("My port Loacal is :" + QString("%1").arg(portlocal));

    connect(ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(on_send_clicked()));
}

Widget::~Widget()
{
    delete ui;
    mSocket->close();
}

void Widget::leerSocket()
{
    while(mSocket->hasPendingDatagrams()){
        QByteArray datagram;
        datagram.resize(mSocket->pendingDatagramSize());

        QHostAddress sender;
        quint16 senderport;

        mSocket->readDatagram(datagram.data(), datagram.size(),
                              &sender, &senderport);
        ui->plainTextEdit->appendPlainText(QString(datagram) +"( ip: " + sender.toString()
                                           + "port: " +  QString("%1").arg(senderport));
      }

}
void Widget::on_Connect_clicked()
{
    ui->lcdNumber->setDigitCount(11);

    host = ui->lineEdit->text().section(',', 0, 0);
    port = ui->lineEdit->text().section(',', 1, 1).toInt();

    ui->lcdNumber_2->display(host.toString());
    ui->lcdNumber->display(port);

    ui->lineEdit->clear();
    ui->plainTextEdit->clear();

}


void Widget::on_send_clicked()
{
    mSocket->writeDatagram(ui->lineEdit->text().toLatin1(), host, port);
    ui->lineEdit->clear();
}



