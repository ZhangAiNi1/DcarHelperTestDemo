#ifndef DATATRANSWINDOW_H
#define DATATRANSWINDOW_H

#include <QWidget>
#include <QtSerialPort/QSerialPort>        //提供访问串口的功能
#include <QtSerialPort/QSerialPortInfo>    //提供串口信息
#include <ConnectWindow/connectwindow.h>
#include <QDebug>

#include <QMessageBox>
#include <QSerialPort>
#include <QIODevice>
#include <QFont>


#include <QTableView>
#include <QHeaderView>
#include <QStandardItemModel>
#include <QStringList>
#include <QString>
#include <QPushButton>

#include <QTableWidget> // 对于QTableWidget
#include <QLabel> // 如果你要添加QLabel作为单元格的窗口部件

#include <QMenu>
#include <QAction>
#include <QCursor>
#include <QWidgetAction>

#include"DataTransWindow/customwidget.h"
#include "DataTransWindow/customplaintextedit.h"

#include <QDateTime>

#include <QTextCharFormat>
namespace Ui {
class DataTransWindow;
}

class DataTransWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DataTransWindow(QWidget *parent = 0);

    ~DataTransWindow();

    QSerialPort *mySerialPort;

    void parseFrame(const QString& frame);

    void parseData();

    void add_text_label(QString str,Qt::Alignment Align,int row,int column);

    QPushButton * add_cmd_button(int row,int column);

    QPushButton * add_send_button(int row,int column);

    void updateDisplay();       //刷新接受框，如有数据接收或者字体放大等设置可调用

    void adjustTableColumnWidths();
    void add_row_item();

    void CMDtableWidget_Init();

    enum RxTxType {
            CHAR,
            HEX
        };

    struct DataPacket {
        QString timestamp;
        QString data;
        bool showTimestamp; // 标记此数据包接收时时间戳是否应该显示
    };

private slots:

    void on_clearSendButton_clicked();

    void on_transButton_clicked();

    void DataReceived_1();


    void onSettingBtnClicked();

    void on_receive_view_btn_clicked();

    void on_receive_type_btn_clicked();

    void on_time_view_btn_clicked();

//    void on_clear_txt_btn_clicked();

//    void on_enlarge_btn_clicked();

//    void on_smaller_btn_clicked();

//    void on_reset_text_size_btn_clicked();

    void on_send_btn_clicked();

    void on_clear_btn_clicked();

    void on_clear_txtbtn_clicked();

    void handleFontSizeChanged(bool increase);

private:
    Ui::DataTransWindow *ui;
    ConnectWindow *conWin;
    int tnum = 0;
    unsigned char chrtmp[100];  //用于缓存串口数据

    RxTxType recieve_type_flag = RxTxType::CHAR ;   //默认是char类型接收
    QString currentData; // 存储当前接收到的数据，以便在不同模式间切换
    bool recieve_view_flag = true;    //默认显示接收
    bool showTimestamp = true; // 时间戳显示开关，默认打开
    QList<DataPacket> dataPackets;

    // 类成员变量定义
    QTextCharFormat timestampFormat;
    QTextCharFormat dataFormat;

    QFont timestampFont;
    QFont dataFont;

//    QString processAndDisplayHex(const QString &content);
//    QString removeTimestamp(const QString &packet);
};

#endif // DATATRANSWINDOW_H
