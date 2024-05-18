#include "datatranswindow.h"
#include "ui_datatranswindow.h"
#include "HLine.h"


DataTransWindow::DataTransWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataTransWindow)
{

    ui->setupUi(this);
    //设置数据收发区域的边框
    ui->Transfer->setObjectName("Transfer");
    ui->Transfer->setStyleSheet("#Transfer {"
                            "border-radius: 10px; "
                            "border: 1px solid #E8F0F0; "
                            "background-color: #FFFFFF; "
                            "}");

    //设置命令区域边框
    ui->Commend->setObjectName("Commend");
    ui->Commend->setStyleSheet("#Commend {"
                            "border-radius: 10px; "
                            "border: 1px solid #E8F0F0; "
                            "background-color: #FFFFFF; "
                            "}");



    connect(mySerialport2, &QSerialPort::readyRead, this, &DataTransWindow::DataReceived_1);

    // 创建一个等宽字体对象
    timestampFont = QFont("PingFang SC Regular", 12); // 为时间戳设置等宽字体，粗体
    dataFont = QFont("PingFang SC Regular", 12); // 为数据包设置等宽字体，正常字体权重

    // 设置时间戳的格式
    timestampFormat.setFont(timestampFont);
    timestampFormat.setForeground(QColor(0, 103, 192)); // 天空蓝

//    timestampFormat.setForeground(QColor(135, 183, 250)); // 天空蓝
////    dataFormat.setForeground(QColor(21, 244, 238)); // 荧光蓝
////    timestampFormat.setForeground(QColor(3, 37, 76)); // 深海蓝

    // 设置数据包的格式
    dataFormat.setFont(dataFont);
    dataFormat.setForeground(QColor(51, 168, 98)); // 高级绿
//    dataFormat.setForeground(QColor(34, 177, 76)); // 高级绿
////    dataFormat.setForeground(QColor(190, 200, 215)); // 柔和灰色

////    timestampFormat.setForeground(QColor(57, 255, 20)); // 荧光绿
////    dataFormat.setForeground(QColor(106, 226, 106)); // 透亮的绿

    //非常好看的背景
    ui->receive_plain->setStyleSheet(
        "QPlainTextEdit {"
            "border: 1px solid #E8F0F0;" // 浅蓝色边框
            "background-color: #FFFFFF;" // 背景色设为白色
        "}"
        "QScrollBar:vertical {"
            "border: none;"
            "background: transparent;"
            "width: 6px;"
            "border-radius: 5px;" // 圆弧末端
        "}"
        "QScrollBar::handle:vertical {"
            "background: #E8F0F0;" // 浅蓝色滚动条
            "min-height: 20px;"
            "border-radius: 5px;" // 圆弧末端
        "}"
        "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {"
            "height: 0px;" // 取消滚动条最上面的挡块
        "}"
        "QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical {"
            "width: 0px;" // 取消滚动条箭头
            "height: 0px;"
        "}"
        "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {"
            "background: none;"
        "}"
        "QScrollBar:horizontal {"
            "border: none;"
            "background: transparent;"
            "height: 10px;"
            "border-radius: 5px;" // 圆弧末端
        "}"
        "QScrollBar::handle:horizontal {"
            "background: #E8F0F0;" // 浅蓝色滚动条
            "min-width: 20px;"
            "border-radius: 5px;" // 圆弧末端
        "}"
        "QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal {"
            "width: 0px;" // 取消滚动条最两侧的挡块
        "}"
        "QScrollBar::left-arrow:horizontal, QScrollBar::right-arrow:horizontal {"
            "width: 0px;" // 取消滚动条箭头
            "height: 0px;"
        "}"
        "QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal {"
            "background: none;"
        "}"
    );

    // 设置字体
    QFont sendBoxFont("微软雅黑", 12, QFont::Bold);
    ui->transmit_plain->setFont(sendBoxFont);

    ui->transmit_plain->setStyleSheet(
        "QPlainTextEdit {"
            "border-top: none;" // 浅蓝色边框
            "border-left: 1px solid #E8F0F0;"
            "border-right: 1px solid #E8F0F0;"
            "border-bottom: none;" // 移除下边框
            "background-color: #FFFFFF;" // 背景色设为白色
        "}"
        "QScrollBar:vertical {"
            "border: none;"
            "background: transparent;"
            "width: 6px;"
            "border-radius: 5px;" // 圆弧末端
        "}"
        "QScrollBar::handle:vertical {"
            "background: #E8F0F0;" // 浅蓝色滚动条
            "min-height: 20px;"
            "border-radius: 5px;" // 圆弧末端
        "}"
        "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {"
            "height: 0px;" // 取消滚动条最上面的挡块
        "}"
        "QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical {"
            "width: 0px;" // 取消滚动条箭头
            "height: 0px;"
        "}"
        "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {"
            "background: none;"
        "}"
        "QScrollBar:horizontal {"
            "border: none;"
            "background: transparent;"
            "height: 10px;"
            "border-radius: 5px;" // 圆弧末端
        "}"
        "QScrollBar::handle:horizontal {"
            "background: #E8F0F0;" // 浅蓝色滚动条
            "min-width: 20px;"
            "border-radius: 5px;" // 圆弧末端
        "}"
        "QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal {"
            "width: 0px;" // 取消滚动条最两侧的挡块
        "}"
        "QScrollBar::left-arrow:horizontal, QScrollBar::right-arrow:horizontal {"
            "width: 0px;" // 取消滚动条箭头
            "height: 0px;"
        "}"
        "QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal {"
            "background: none;"
        "}"
    );




    // 时间戳按钮
    ui->time_view_btn->setCheckable(true);
    QPixmap pixmap_time_view_btn(":/icon/DataTransWindowIcon/time_view_btn.png");
    ui->time_view_btn->resize(pixmap_time_view_btn.size());
    ui->time_view_btn->setStyleSheet(R"(
        QPushButton{
            border-image: url(:/icon/DataTransWindowIcon/time_view_btn.png);
        }
        QPushButton:hover {
            border-image: url(:/icon/DataTransWindowIcon/time_view_btnHover.png);
        }
       QPushButton:checked {
               border-image: url(:/icon/DataTransWindowIcon/time_view_btnCheck.png);
           }

    )");
    ui->time_view_btn->setFixedSize(44,38);

    // 发送是否可见按钮
    ui->transmit_view_btn->setCheckable(true);
    QPixmap pixmap_transmit_view_btn(":/icon/DataTransWindowIcon/transmit_view_btn.png");
    ui->transmit_view_btn->resize(pixmap_transmit_view_btn.size());
    ui->transmit_view_btn->setStyleSheet(R"(
        QPushButton{
            border-image: url(:/icon/DataTransWindowIcon/transmit_view_btn.png);
        }
        QPushButton:hover {
            border-image: url(:/icon/DataTransWindowIcon/transmit_view_btnHover.png);
        }
       QPushButton:checked {
               border-image: url(:/icon/DataTransWindowIcon/transmit_view_btnCheck.png);
           }

    )");
    ui->transmit_view_btn->setFixedSize(44,38);


    // 发送窗口文本样式设置
    ui->txt_setting_btn->setCheckable(true);
    QPixmap pixmap_txt_setting_btn(":/icon/DataTransWindowIcon/txt_setting_btn.png");
    ui->txt_setting_btn->resize(pixmap_txt_setting_btn.size());
    ui->txt_setting_btn->setStyleSheet(R"(
        QPushButton{
            border-image: url(:/icon/DataTransWindowIcon/txt_setting_btn.png);
        }
        QPushButton:hover {
            border-image: url(:/icon/DataTransWindowIcon/txt_setting_btnHover.png);
        }
       QPushButton:pressed {
           border-image: url(:/icon/DataTransWindowIcon/txt_setting_btnCheck.png);
       }

    )");
    ui->txt_setting_btn->setFixedSize(44,38);

    // 发送窗口文本清空
    ui->clear_btn->setCheckable(true);
    QPixmap pixmap_clear_btn(":/icon/DataTransWindowIcon/clear_btn.png");
    ui->clear_btn->resize(pixmap_clear_btn.size());
    ui->clear_btn->setStyleSheet(R"(
        QPushButton{
            border-image: url(:/icon/DataTransWindowIcon/clear_btn.png);
        }
        QPushButton:hover {
            border-image: url(:/icon/DataTransWindowIcon/clear_btnHover.png);
        }
       QPushButton:pressed {
           border-image: url(:/icon/DataTransWindowIcon/clear_btnPress.png);
       }

    )");
    ui->clear_btn->setFixedSize(44,38);

    // 发送窗口文本显示类型
    ui->receive_type_btn->setCheckable(true);
    QPixmap pixmap_receive_type_btn(":/icon/DataTransWindowIcon/Hex.png");
    ui->receive_type_btn->resize(pixmap_receive_type_btn.size());
    ui->receive_type_btn->setStyleSheet(R"(
        QPushButton{
            border-image: url(:/icon/DataTransWindowIcon/Hex.png);
        }
        QPushButton:hover {
            border-image: url(:/icon/DataTransWindowIcon/HexHover.png);
        }
       QPushButton:pressed {
           border-image: url(:/icon/DataTransWindowIcon/HexPress.png);
       }

    )");
    ui->receive_type_btn->setFixedSize(44,44);

    // 接收窗口文本清除按钮
    ui->clear_txtbtn->setCheckable(true);
    QPixmap pixmap_clear_txtbtn(":/icon/DataTransWindowIcon/clear_txtbtn.png");
    ui->clear_txtbtn->resize(pixmap_clear_txtbtn.size());
    ui->clear_txtbtn->setStyleSheet(R"(
        QPushButton{
            border-image: url(:/icon/DataTransWindowIcon/clear_txtbtn.png);
        }
        QPushButton:hover {
            border-image: url(:/icon/DataTransWindowIcon/clear_txtbtnHover.png);
        }
       QPushButton:pressed {
           border-image: url(:/icon/DataTransWindowIcon/clear_txtbtnPress.png);
       }

    )");
    ui->clear_txtbtn->setFixedSize(44,38);


    // 发送窗口文本类型转换
    ui->send_type_switch->setCheckable(true);
    QPixmap pixmap_send_type_switch(":/icon/DataTransWindowIcon/sendHex.png");
    ui->send_type_switch->resize(pixmap_send_type_switch.size());
    ui->send_type_switch->setStyleSheet(R"(
        QPushButton{
            border-image: url(:/icon/DataTransWindowIcon/sendHex.png);
        }
        QPushButton:hover {
            border-image: url(:/icon/DataTransWindowIcon/sendHexHover.png);
        }
       QPushButton:pressed {
           border-image: url(:/icon/DataTransWindowIcon/sendHexPress.png);
       }

    )");
    ui->send_type_switch->setFixedSize(44,44);

    // 发送窗口文本类型转换
    ui->send_btn->setCheckable(true);
    QPixmap pixmap_send_btn(":/icon/DataTransWindowIcon/sendbtn.png");
    ui->send_btn->resize(pixmap_send_btn.size());
    ui->send_btn->setStyleSheet(R"(
        QPushButton{
            border-image: url(:/icon/DataTransWindowIcon/sendbtn.png);
        }
        QPushButton:hover {
            border-image: url(:/icon/DataTransWindowIcon/sendbtnHover.png);
        }
       QPushButton:pressed {
           border-image: url(:/icon/DataTransWindowIcon/sendbtnPress.png);
       }

    )");
    ui->send_btn->setFixedSize(90,44);



    CMDtableWidget_Init();


    // 添加命令按钮
    ui->add_cmd_btn->setCheckable(true);
    QPixmap pixmap_add_cmd_btn(":/icon/DataTransWindowIcon/add_cmd_btn.png");
    ui->add_cmd_btn->resize(pixmap_add_cmd_btn.size());
    ui->add_cmd_btn->setStyleSheet(R"(
        QPushButton{
            border-image: url(:/icon/DataTransWindowIcon/add_cmd_btn.png);
        }
       QPushButton:hover {
           border-image: url(:/icon/DataTransWindowIcon/add_cmd_btnHover.png);
       }
      QPushButton:pressed {
          border-image: url(:/icon/DataTransWindowIcon/add_cmd_btnPress.png);
      }

    )");
    ui->add_cmd_btn->setFixedSize(104,36);

    // 删除所有命令按钮
    ui->clear_cmd_btn->setCheckable(true);
    QPixmap pixmap_clear_cmd_btn(":/icon/DataTransWindowIcon/clear_cmd_btn.png");
    ui->clear_cmd_btn->resize(pixmap_clear_cmd_btn.size());
    ui->clear_cmd_btn->setStyleSheet(R"(
        QPushButton{
            border-image: url(:/icon/DataTransWindowIcon/clear_cmd_btn.png);
        }
       QPushButton:hover {
           border-image: url(:/icon/DataTransWindowIcon/clear_cmd_btnHover.png);
       }
      QPushButton:pressed {
          border-image: url(:/icon/DataTransWindowIcon/clear_cmd_btnPress.png);
      }

    )");
    ui->clear_cmd_btn->setFixedSize(104,36);





    connect(ui->receive_plain, &CustomPlainTextEdit::fontSizeChanged,
            this, &DataTransWindow::handleFontSizeChanged);

    ui->receive_type_btn->setHoverTipText("转为HEX接收");
    ui->time_view_btn->setHoverTipText("开启时间戳");
    ui->receive_view_btn->setHoverTipText("关闭接收显示");
    ui->transmit_view_btn->setHoverTipText("关闭发送显示");
    ui->txt_setting_btn->setHoverTipText("字体设置");
    ui->clear_txtbtn->setHoverTipText("清空接收窗口");





}

DataTransWindow::~DataTransWindow()
{
    delete ui;
}

void DataTransWindow::CMDtableWidget_Init()
{

    //让tableWidget内容中的每个元素居中
    ui->commend_table->setSelectionBehavior(QAbstractItemView::SelectRows);//设置整行选中
    ui->commend_table->verticalHeader()->hide(); // 隐藏表头
    ui->commend_table->horizontalHeader()->hide(); //隐藏左侧表inedx
    ui->commend_table->setShowGrid(false);          //隐藏单元格线
    ui->commend_table->setStyleSheet("QTableWidget { border: none; }");    //隐藏边框
    ui->commend_table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //取消滑条

    ui->commend_table->setColumnCount(3);                 // 设置表格列数

    ui->commend_table->verticalHeader()->setDefaultSectionSize(60);     //设置默认行高是60

    QStringList labelList;
    labelList.append(QString("setbtn"));
    labelList.append(QString("cmd"));
    labelList.append(QString("send"));
    ui->commend_table->setHorizontalHeaderLabels(labelList);          // 设置表头

    add_row_item();
    add_row_item();
    add_row_item();
    add_row_item();
    add_row_item();
    add_row_item();
    add_row_item();
    add_row_item();


    adjustTableColumnWidths();


    ui->commend_table->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置所有单元格不可编辑
    ui->commend_table->setSelectionMode(QAbstractItemView::NoSelection);    //设置单元格不可被选中
    ui->commend_table->setFocusPolicy(Qt::NoFocus);     //防止被选中出现虚线
}

void DataTransWindow::adjustTableColumnWidths() {
    int totalWidth = ui->commend_table->viewport()->width(); // 使用viewport的宽度而不是整个tableWidget的宽度，以避免滚动条影响
    int width1 = totalWidth * 2 / 11;
    int width2 = totalWidth * 6 / 11;
    int width3 = totalWidth  - width1 - width2;




    ui->commend_table->setColumnWidth(0, width1);
    ui->commend_table->setColumnWidth(1, width2);
    ui->commend_table->setColumnWidth(2, width3);


}

void DataTransWindow::add_row_item()
{
//   qDebug() << "Adding new row item:" << name << value << dataSource;

    int totalRows = ui->commend_table->rowCount();

    ui->commend_table->setRowCount(totalRows + 1); // 增加一行

    //CMDbtn
    QPushButton * CMDbtn = add_cmd_button(totalRows,0);

    add_text_label("cmd", Qt::AlignLeft, totalRows, 1); // 传递颜色到函数


    //发送按钮
    QPushButton * cmdsendButton = add_send_button(totalRows,2);


}

void DataTransWindow::add_text_label(QString str,Qt::Alignment Align,int row,int column)
{
    QLabel *name = new QLabel(); // 设置parentWidget为label的父窗口部件

    // 设置要显示的文本
    name->setText(str);

    // 创建一个QFont对象并设置字体样式和大小
    QFont font("Arial", 12); // 使用Arial字体，字号大小为9
    font.setBold(true); // 设置字体为粗体
    font.setItalic(true); // 设置字体为斜体

    // 将字体应用到label上
    name->setFont(font);

    // 调整label的大小以适应文本内容
    name->adjustSize();



    //增加widget+布局巧妙实现居中
    QWidget *widget = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout();
    layout->setMargin(0);//一定要有
    layout->addWidget(name);
    layout->setAlignment(name, Align);//控件在布局中居中显示
    widget->setLayout(layout);

    ui->commend_table->setCellWidget(row,column,widget);

}

QPushButton * DataTransWindow::add_cmd_button(int row,int column)
{
        // add button to the last column
        QPushButton *button = new QPushButton();

        // 波形显示界面按钮
        QPixmap pixmap_shapeViewButton(":/icon/DataTransWindowIcon/commendbtn.png");
        button->resize(pixmap_shapeViewButton.size());
        button->setStyleSheet(R"(
            QPushButton{
                border-image: url(:/icon/DataTransWindowIcon/commendbtn.png);
            }

        )");
        button->setFixedSize(24,24);


        //增加widget+布局巧妙实现居中
        QWidget *widget = new QWidget();
        QHBoxLayout *layout = new QHBoxLayout();
        layout->setMargin(0);//一定要有
        layout->addWidget(button);
        layout->setAlignment(button, Qt::AlignCenter);//控件在布局中居中显示
        widget->setLayout(layout);

        button->setProperty("rowIndex", row);//设置当前的索引，用于删除
        ui->commend_table->setCellWidget(row,column,widget);

        return button;
}


QPushButton * DataTransWindow::add_send_button(int row,int column)
{
        // add button to the last column
        QPushButton *button = new QPushButton();

        // 波形显示界面按钮
        QPixmap pixmap_cmdsendButton(":/icon/DataTransWindowIcon/cmdsendbtn.png");
        button->resize(pixmap_cmdsendButton.size());
        button->setStyleSheet(R"(
            QPushButton {
                border-image: url(:/icon/DataTransWindowIcon/cmdsendbtn.png);
            }
            QPushButton:hover {
                border-image: url(:/icon/DataTransWindowIcon/cmdsendbtnHover.png);
            }
            QPushButton:pressed {
                border-image: url(:/icon/DataTransWindowIcon/cmdsendbtnPress.png);
            }
        )");

        button->setFixedSize(68,36);


        //增加widget+布局巧妙实现居中
        QWidget *widget = new QWidget();
        QHBoxLayout *layout = new QHBoxLayout();
        layout->setMargin(0);//一定要有
        layout->addWidget(button);
        layout->setAlignment(button, Qt::AlignCenter);//控件在布局中居中显示
        widget->setLayout(layout);

        button->setProperty("rowIndex", row);//设置当前的索引，用于删除
        ui->commend_table->setCellWidget(row,column,widget);

        return button;
}

void DataTransWindow::on_clearSendButton_clicked()
{
//    ui->receive_plain->clear();
}

void DataTransWindow::on_transButton_clicked()
{
   //  QByteArray sendData;
   //      // 判断是否为16进制发送，将发送区全部的asc2转换为16进制字符串显示，发送的时候转换为16进制发送
   //  if(ui->checkBox_send->checkState() == false){
   //          // 字符串形式发送
   //     sendData = ui->plainTextEdit_send->toPlainText().toLocal8Bit().data();
   //  }else{
   //          // 16进制发送
   //     sendData = QByteArray::fromHex(ui->plainTextEdit_send->toPlainText().toUtf8()).data();
   //  }
   // mySerialport2->write(sendData);
}



void DataTransWindow::DataReceived_1()
{
    static QString incompletePacket; // 用于存储不完整的数据包

        incompletePacket += QString::fromUtf8(recBuf); // 累积接收的数据

        // 检查是否包含完整的数据包（以\r\n结尾）
        int endIndex;
        while ((endIndex = incompletePacket.indexOf("\r\n")) != -1) {
            QString completePacket = incompletePacket.left(endIndex + 2); // 提取完整的数据包（包括\r\n）
            incompletePacket.remove(0, endIndex + 2); // 从累积数据中移除已处理的数据包

            DataPacket packet;
            packet.timestamp = QDateTime::currentDateTime().toString("[yyyy-MM-dd HH:mm:ss]");
            packet.data = completePacket; // 包含\r\n的完整数据包
            packet.showTimestamp = this->showTimestamp; // 使用当前全局标志位的值

            dataPackets.append(packet); // 将数据包添加到列表
        }

        updateDisplay(); // 更新显示

  //   parseData();   //解析客制化printf数据包，之后会移动到波形显示那里


}

void DataTransWindow::parseData()
{
    static QString buffer;
    buffer += QString::fromUtf8(recBuf);

    // 支持多种行结束符
    QRegExp lineEndRegExp("(\r\n|\n\r|\n)");
    int frameEndIndex;
    while ((frameEndIndex = buffer.indexOf(lineEndRegExp)) != -1) {
        QString frame = buffer.left(frameEndIndex);
        int lengthOfLineEnd = lineEndRegExp.matchedLength(); // 匹配到的行结束符长度
        buffer.remove(0, frameEndIndex + lengthOfLineEnd);

        // 移除帧头
        if (frame.startsWith("data:")) {
            frame.remove(0, frame.indexOf(":") + 1);
        }

        // 标准化数据帧
        frame = frame.trimmed(); // 去除首尾空白字符
        parseFrame(frame);
    }
}

void DataTransWindow::parseFrame(const QString& frame) {
    // 使用正则表达式匹配浮点数，考虑了空格和逗号的不确定性
    QRegExp numRegExp("\\s*([+-]?\\d*\\.?\\d+)\\s*,?");
    int pos = 0;
    QList<float> numbers;

    while ((pos = numRegExp.indexIn(frame, pos)) != -1) {
        bool ok;
        float num = numRegExp.cap(1).toFloat(&ok);
        if (ok) {
            numbers.append(num);
        }
        pos += numRegExp.matchedLength();
    }

    // 处理解析出的浮点数
    // if (numbers.size() >= 3) { // 确保至少有3个数据
//        qDebug() << "Parsed data:" << numbers;
    // }
}


void DataTransWindow::onSettingBtnClicked()
{
//    // 创建QMenu
//    QMenu *menu = new QMenu(this);

//    // 创建QWidgetAction
//    QWidgetAction *action = new QWidgetAction(menu);

//    // 使用你的自定义QWidget
//    CustomWidget *customWidget = new CustomWidget(); // 假设CustomWidget是你的自定义QWidget
//    action->setDefaultWidget(customWidget);

//    // 将QWidgetAction添加到QMenu中
//    menu->addAction(action);

//    // 在当前鼠标位置显示菜单
//    menu->exec(QCursor::pos());

}



void DataTransWindow::on_receive_view_btn_clicked()
{
    recieve_view_flag = !recieve_view_flag;

    //如果不想显示就关掉
    if(recieve_view_flag == false)
    {
        disconnect(mySerialport2,&QSerialPort::readyRead,this,&DataTransWindow::DataReceived_1);
    }
    else if(recieve_view_flag == true)
    {
        connect(mySerialport2, &QSerialPort::readyRead, this, &DataTransWindow::DataReceived_1);
    }

}

void DataTransWindow::updateDisplay()
{
    ui->receive_plain->clear();
    QTextCursor cursor(ui->receive_plain->document());

    for (const DataPacket& packet : dataPackets) {
        // 应用时间戳格式
        if (packet.showTimestamp) {
            QTextCharFormat timestampFormat;
            timestampFormat.setFont(timestampFont); // 使用更新后的字体
            timestampFormat.setForeground(QColor(0, 103, 192)); // 天空蓝
            cursor.insertText(packet.timestamp + " ", timestampFormat);
        }

        // 根据接收类型，转换数据包内容
        QString content;
        if (recieve_type_flag == HEX) {
            // HEX模式：将packet.data转换为HEX格式
            content = packet.data.toUtf8().toHex().toUpper();
            // 分割HEX字符串，以提高可读性
            QString formattedHex;
            for(int i = 0; i < content.length(); i += 2) {
                formattedHex += content.mid(i, 2) + " ";
            }
            content = formattedHex.trimmed();
        } else {
            // CHAR模式：直接使用packet.data
            content = packet.data;
        }

        // 应用数据包格式并插入内容
        QTextCharFormat dataFormat;
        dataFormat.setFont(dataFont); // 使用更新后的字体
        dataFormat.setForeground(QColor(51, 168, 98)); // 高级绿
        cursor.insertText(content + "\n", dataFormat);
    }

    ui->receive_plain->moveCursor(QTextCursor::End);
}


//QString DataTransWindow::processAndDisplayHex(const QString &content) {
//    QString hexContent;
//    QByteArray contentBytes = content.toUtf8(); // 将QString转换为QByteArray
//    for (int i = 0; i < contentBytes.size(); ++i) {
//        if (i > 0) hexContent += " "; // 在字节之间添加空格
//        hexContent += QString::number(contentBytes[i] & 0xFF, 16).rightJustified(2, '0').toUpper();
//    }
//    return hexContent; // 返回包含十六进制表示的字符串
//}

//QString DataTransWindow::removeTimestamp(const QString &packet) {
//    // 假设时间戳总是位于数据包的开始，并且格式是[yyyy-MM-dd HH:mm:ss]
//    int timestampEnd = packet.indexOf(']') + 1;
//    return packet.mid(timestampEnd).trimmed(); // 移除时间戳并返回剩余的字符串
//}

void DataTransWindow::on_receive_type_btn_clicked()
{
    // 切换显示模式
        recieve_type_flag = (recieve_type_flag == CHAR) ? HEX : CHAR;
        // 更新显示
        updateDisplay();
}

void DataTransWindow::on_time_view_btn_clicked()
{
    showTimestamp = !showTimestamp; // 切换时间戳显示开关
}




void DataTransWindow::handleFontSizeChanged(bool increase)
{
    if (increase) {
        timestampFont.setPointSizeF(timestampFont.pointSizeF() * 1.10);
        dataFont.setPointSizeF(dataFont.pointSizeF() * 1.10);
    } else {
        timestampFont.setPointSizeF(timestampFont.pointSizeF() * 0.90);
        dataFont.setPointSizeF(dataFont.pointSizeF() * 0.90);
    }
    updateDisplay(); // 确保重新应用字体设置并更新显示
}



void DataTransWindow::on_send_btn_clicked()
{
//    QString textToSend = ui->transmit_plain->toPlainText(); // 获取发送框的文本

//        mySerialport2->write(textToSend.toUtf8());

//        ui->transmit_plain->clear(); // 发送后清空发送框
}

void DataTransWindow::on_clear_btn_clicked()
{
    ui->transmit_plain->clear(); // 发送后清空发送框
}

void DataTransWindow::on_clear_txtbtn_clicked()
{
    // 清空屏幕显示
    ui->receive_plain->clear();
    // 清空存储的数据
    dataPackets.clear();
}
