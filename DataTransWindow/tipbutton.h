#ifndef TIPBUTTON_H
#define TIPBUTTON_H

#include <QPushButton>
#include <QTimer>
#include <QToolTip>

class TipButton : public QPushButton
{
    Q_OBJECT
public:
    explicit TipButton(QWidget *parent = nullptr);
    ~TipButton();
    void setHoverTipText(const QString &text); // 设置悬停提示文本的接口

protected:
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;

private slots:
    void showHoverTip();

private:
    QTimer *timer;
    QString hoverTipText; // 存储悬停时显示的提示信息
};

#endif // TIPBUTTON_H
