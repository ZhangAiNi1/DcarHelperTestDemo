#include "connectwindow.h"
#include "ui_connectwindow.h"
#include "IndexWindow/mainwindow.h"

QSerialPort *mySerialport2=new QSerialPort;  //创建串口对象
//全局范围内串口接收数组
QByteArray recBuf;
//uint16_t recvbytes; //BUG？没用到

ConnectWindow::ConnectWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConnectWindow)
{
    ui->setupUi(this);  //这段代码以上都是默认生成的，这个setupUI指的是初始化UI画的界面，后面是在这个UI界面上添加东西
    this->setWindowTitle("连接设置");

    setFont(&(ui->title_label),":/new/prefix1/Image/Furore-2.otf"); //这个和Qwigit的setFont实现应该类似
    ui->title_label->setText("DF_HELPER V1.0 ");

    ui->okButton->setText("打开串口");
    ui->concellButton->setText("取消");

    //BUG？这行本意是将窗口设置为无边窗模式，但是没起作用
    this->setWindowFlags(Qt::FramelessWindowHint);


    QString baudrate;
    ReadInit("baudrate",baudrate);
    ui->BaudEdit->setText(baudrate);
    ui->okButton->setStyleSheet("QPushButton{border-image:url(:/new/prefix1/newImg/按键.png);}"
                                          "QPushButton:hover{border-image:url(:/new/prefix1/newImg/按键2.png);}");
    ui->concellButton->setStyleSheet("QPushButton{border-image:url(:/new/prefix1/newImg/按键.png);}"
                                          "QPushButton:hover{border-image:url(:/new/prefix1/newImg/按键2.png);}");
    QFont ft1;
    ft1.setFamily("微软雅黑");
    ft1.setPointSize(11);
    ui->okButton->setFont(ft1);
    ui->concellButton->setFont(ft1);

    QPalette color1=QColor(255,0,0);
    ui->okButton->setPalette(color1);
    QPalette color2=QColor(0,255,0);
    ui->concellButton->setPalette(color2);

    //这段代码很奇怪，他读取了工程目录下的baud.txt的最后一行字，给到了BaudEdit这个框里，实际上没有这个文件根本
    QDir dir = QDir::current();
    QFile data(dir.absolutePath() + "/baud.txt");
    //打开并读取
    if (data.open(QFile::ReadOnly)) {
       QTextStream s(&data);
       QString content = s.readAll();
       ui->BaudEdit->setText(content);
    }
    //这是手动关联来一个信号，这个信号如果被使用emit触发，那么就会执行一次后面这个函数，相当于事件的机制？，也就是if else的感觉
    connect(mySerialport2,&QSerialPort::readyRead,this,&ConnectWindow::Get_Serialdata);//这是一个手动关联一个实例。一般UI界面中没有的实例需要在cpp初始化并且手动关联
}

ConnectWindow::~ConnectWindow()
{
    delete ui;
}

QSerialPort *ConnectWindow::getMySerialport2() const
{
    return mySerialport2;
}

void ConnectWindow::Get_Serialdata()
{
    // qDebug() << "recieveall doing";
    recBuf=mySerialport2->readAll();
//    recvbytes=mySerialport2->bytesAvailable();        //BUG？
}

//void ConnectWindow::mousePressEvent(QMouseEvent *event)
//{
//    QWidget::mousePressEvent(event);

//    QPoint x = this->geometry().topLeft();
//    QPoint y = event->globalPos();
//    z = y - x;
//}

// //BUG？ 这里重写了鼠标的事件，我认为没有必要重写，就是由于重写了，下面的j造成了不适感当鼠标靠近脑袋顶30距离的时候，窗口自动移动到鼠标位置，很不适
//void ConnectWindow::mouseMoveEvent(QMouseEvent *event)
//{
//    QWidget::mouseMoveEvent(event);
//    QPoint y = event->globalPos();
//    QPoint x = y - z;
//    int j=event->y();
//    if(j<30)
//    {
//      this->move(x);
//    }
//}

//void ConnectWindow::mouseReleaseEvent(QMouseEvent *event)
//{
//    QWidget::mouseReleaseEvent(event);
//}

void ConnectWindow::setFont(QLabel **label, QString fontPath)
{

    int loadedFontId = QFontDatabase::addApplicationFont(fontPath);
        QStringList loadedFontFamilies = QFontDatabase::applicationFontFamilies(loadedFontId);
        for(int i =0 ; i < loadedFontFamilies.size() ; i++){
            QString sansCNFamily = loadedFontFamilies.at(i);
            if(i == 0 ){
                QFont defaultFont = (*label)->font();
                //设置字体大小格式为pixel，字体占用固定像素。相同像素的大小屏，不会发生字体遮挡现象
                defaultFont.setFamily(sansCNFamily);
                defaultFont.setPixelSize(20);
                (*label)->setFont(defaultFont);
            }      }
}

void ConnectWindow::on_okButton_clicked()
{
    QString baudrate=ui->BaudEdit->toPlainText();
    QSerialPort::DataBits dataBits;
    QSerialPort::StopBits stopBits;
    QSerialPort::Parity   checkBits;

    mySerialport2->setBaudRate(baudrate.toInt());
    WriteInit("baudrate",ui->BaudEdit->toPlainText());  //这个是将输入的波特率保存在ini文件中，这个文件就会建立在当前的文件夹

    if(ui->comboBox_Stopbit->currentText() == "1"){
         stopBits = QSerialPort::OneStop;
     }else if(ui->comboBox_Stopbit->currentText() == "1.5"){
         stopBits = QSerialPort::OneAndHalfStop;
     }else if(ui->comboBox_Stopbit->currentText() == "2"){
         stopBits = QSerialPort::TwoStop;
     }

    if(ui->comboBox_Databit->currentText() == "5"){
           dataBits = QSerialPort::Data5;
       }else if(ui->comboBox_Databit->currentText() == "6"){
           dataBits = QSerialPort::Data6;
       }else if(ui->comboBox_Databit->currentText() == "7"){
           dataBits = QSerialPort::Data7;
       }else if(ui->comboBox_Databit->currentText() == "8"){
           dataBits = QSerialPort::Data8;
       }else{

       }
    if(ui->comboBox_Paritycheck->currentText() == "无"){
        checkBits = QSerialPort::NoParity;
    }else if(ui->comboBox_Paritycheck->currentText() == "奇校验"){
        checkBits = QSerialPort::OddParity;
    }else if(ui->comboBox_Paritycheck->currentText() == "偶校验"){
        checkBits = QSerialPort::EvenParity;
    }else{

    }
    mySerialport2->setDataBits(dataBits);
    mySerialport2->setStopBits(stopBits);
    mySerialport2->setParity(checkBits);
    mySerialport2->setPortName(ui->comboBox_aviports->currentText()); // 不匹配带有串口设备信息的文本
    // 根据初始化好的串口属性，打开串口
    // 如果打开成功，反转打开按钮显示和功能。打开失败，无变化，并且弹出错误对话框。
    if(ui->okButton->text() == "打开串口"){
        if(mySerialport2->open(QIODevice::ReadWrite) == true){
            //QMessageBox::
            ui->okButton->setText("关闭串口");
            // 让端口号下拉框不可选，避免误操作（选择功能不可用，控件背景为灰色）
            ui->comboBox_aviports->setEnabled(false);
            ui->BaudEdit->setEnabled(false);
            emit stateSignalOpen();
            this->close();
        }else{
            QMessageBox::critical(this, "错误提示", "串口打开失败！！！\r\n该串口可能被占用\r\n请选择正确的串口");
        }

    }else{
        mySerialport2->close();
        ui->okButton->setText("打开串口");
        // 端口号下拉框恢复可选，避免误操作
        ui->comboBox_aviports->setEnabled(true);
        ui->BaudEdit->setEnabled(true);
        emit stateSignalClose();
        this->close();
    }

    QDir dir1 = QDir::current();
    //定位文件
    QFile data(dir1.absolutePath() + "/baud.txt");
    //打开并写入内容
    QString content = ui->BaudEdit->toPlainText();
    if (data.open(QFile::WriteOnly)) {
       QTextStream s(&data);
       s << content;
    }
}

void ConnectWindow::on_concellButton_clicked()
{
    this->close();
}

void ConnectWindow::WriteInit(QString key, QString value)
{
    QString path = "baudrate.ini";

    //创建配置文件操作对象
    QSettings *config = new QSettings(path, QSettings::IniFormat);

    //将信息写入配置文件
    config->beginGroup("baud");
    config->setValue(key, value);
    config->endGroup();
    delete config;
}

void ConnectWindow::ReadInit(QString key, QString &value)
{
    value = QString("");
    QString path = "baud.ini";

   //创建配置文件操作对象
   QSettings *config = new QSettings(path, QSettings::IniFormat);

    //读取配置信息
   value = config->value(QString("config/") + key).toString();
   delete config;
}
