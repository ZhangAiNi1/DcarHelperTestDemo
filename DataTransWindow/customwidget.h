#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include <QWidget>

namespace Ui {
class CustomWidget;
}

class CustomWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CustomWidget(QWidget *parent = 0);
    ~CustomWidget();

private:
    Ui::CustomWidget *ui;
};

#endif // CUSTOMWIDGET_H
