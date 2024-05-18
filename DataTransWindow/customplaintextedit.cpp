#include "CustomPlainTextEdit.h"

CustomPlainTextEdit::CustomPlainTextEdit(QWidget *parent) : QPlainTextEdit(parent)
{
}

void CustomPlainTextEdit::wheelEvent(QWheelEvent *e)
{
    if (e->modifiers() == Qt::ControlModifier) { // 检查Ctrl键是否按下
        if (e->angleDelta().y() > 0) { // 滚轮前推
            emit fontSizeChanged(true); // 发出增加字体大小的信号
        } else if (e->angleDelta().y() < 0) { // 滚轮后推
            emit fontSizeChanged(false); // 发出减少字体大小的信号
        }
        e->accept();
    } else {
        QPlainTextEdit::wheelEvent(e); // 处理默认的滚动事件
    }
}
