#ifndef CUSTOMPLAINTEXTEDIT_H
#define CUSTOMPLAINTEXTEDIT_H

#include <QPlainTextEdit>
#include <QWheelEvent>
#include <QFont>

class CustomPlainTextEdit : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit CustomPlainTextEdit(QWidget *parent = nullptr);

protected:
    void wheelEvent(QWheelEvent *e) override;

signals:
    void fontSizeChanged(bool increase); // 发出字体大小变化的信号
};

#endif // CUSTOMPLAINTEXTEDIT_H
