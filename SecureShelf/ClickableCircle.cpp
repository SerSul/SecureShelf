// ClickableCircle.cpp
#include "ClickableCircle.h"
#include <QPainter>

ClickableCircle::ClickableCircle(QWidget* parent) : QWidget(parent) {
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::Tool);
    setAttribute(Qt::WA_TranslucentBackground);
    setFixedSize(100, 100);
}

void ClickableCircle::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(QBrush(Qt::blue));
    painter.drawEllipse(0, 0, width(), height());
}

void ClickableCircle::mousePressEvent(QMouseEvent*) {
    emit clicked();
}
