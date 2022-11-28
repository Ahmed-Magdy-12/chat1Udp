#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QHostAddress>
#include <QUdpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class QUdpSocket;
class QAbstractSocket;
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_Connect_clicked();

    void on_send_clicked();
public slots:
    void leerSocket();

private:
    Ui::Widget *ui;
    QHostAddress host;
    QUdpSocket *mSocket;
    quint16 port;
};
#endif // WIDGET_H
