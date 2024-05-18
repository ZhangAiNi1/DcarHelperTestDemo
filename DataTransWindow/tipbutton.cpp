#include "TipButton.h"

TipButton::TipButton(QWidget *parent) : QPushButton(parent)
{
    timer = new QTimer(this);
    timer->setInterval(300); // 设置计时器为300毫秒，达到0.3秒后显示提示
    timer->setSingleShot(true); // 设置计时器只触发一次
    connect(timer, &QTimer::timeout, this, &TipButton::showHoverTip);
}

TipButton::~TipButton()
{
    delete timer;
}

void TipButton::enterEvent(QEvent *event)
{
    QPushButton::enterEvent(event);
    timer->start(); // 鼠标进入时开始计时
}

void TipButton::leaveEvent(QEvent *event)
{
    QPushButton::leaveEvent(event);
    timer->stop(); // 鼠标离开时停止计时并取消提示显示
}

void TipButton::showHoverTip()
{
    // 使用存储的提示信息显示提示
    QToolTip::showText(cursor().pos(), hoverTipText, this);
}



void TipButton::setHoverTipText(const QString &text)
{
    hoverTipText = text; // 存储自定义的提示信息
}
