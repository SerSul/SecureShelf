#pragma once
// ClickableCircle.h
#pragma once

#include <QWidget>
#include <QMouseEvent>

class ClickableCircle : public QWidget {
    Q_OBJECT
public:
    explicit ClickableCircle(QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

signals:
    void clicked();
};

