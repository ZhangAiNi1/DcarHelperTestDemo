#ifndef CONNECTWINDOW_H
#define CONNECTWINDOW_H

#include <QWidget>
#include <QtSerialPort/QSerialPort>        //提供访问串口的功能
#include <QtSerialPort/QSerialPortInfo>    //提供串口信息
#include <QString>
#include <QSettings>
#include <QDir>
#include <QPoint>
#include <QFontDatabase>
#include <QPixmap>
#include <QLabel>

namespace Ui {
class ConnectWindow;
}

class ConnectWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ConnectWindow(QWidget *parent = 0);
    ~ConnectWindow();               //以上都是通用写法，不需要关心
    QSerialPort *getMySerialport2() const;
    void Get_Serialdata();          //这是手动关联的函数，当串口有数据来了，就执行

//    void mousePressEvent(QMouseEvent *event);
//    void mouseMoveEvent(QMouseEvent *event);
//    void mouseReleaseEvent(QMouseEvent *event);

    void setFont(QLabel **label,QString fontPath);

signals:
    void stateSignalOpen();
    void stateSignalClose();

private slots:
    void on_okButton_clicked();

    void on_concellButton_clicked();
    //用于记忆上次输入的函数
    void WriteInit(QString key, QString value);
    void ReadInit(QString key, QString &value);

private:
    Ui::ConnectWindow *ui;      //自动生成的
    QPoint z;
};

extern QSerialPort *mySerialport2;
extern QByteArray recBuf;
//extern uint16_t recvbytes;

#endif // CONNECTWINDOW_H
