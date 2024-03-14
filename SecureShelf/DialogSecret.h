#pragma once

#include <QDialog>
#include "Cryptor.h"
#include "ui_DialogSecret.h"
#include <QPushButton>
#include <QLineEdit>
#include <QDebug>
#include <QFile>

class DialogSecret : public QDialog {
    Q_OBJECT

public:
    explicit DialogSecret(QWidget* parent = nullptr);
    ~DialogSecret();

signals:
    void secretAccepted(const QString& secret);

private slots:
    void onEnterSecret();

private:
    Ui::DialogSecret* ui;
};
