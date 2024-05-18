#include "HLine.h"

HLine::HLine(QWidget *parent) : QWidget(parent) {
    setFixedHeight(2); // 设置分隔线高度
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    setStyleSheet("background-color: #c0c0c0;"); // 设置分隔线颜色
}
