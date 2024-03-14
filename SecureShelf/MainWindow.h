#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include <QPropertyAnimation>
#include "PasswordModel.h"
#include "HighlightDelegate.h"
#include "ToggleSwitch.h"
#include "dialog.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

private slots:
    void toggleMenu(); 
    void openDialog();
    void on_btn_generate_clicked();


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


public slots:
    void setSecret(const QString& secret) {
        this->secret = secret;
    }


private:
    QString secret;
    Ui::MainWindow ui;
    PasswordModel* passwordModel;
    ToggleSwitch* toggleDigits;
    ToggleSwitch* toggleLowercase;
    ToggleSwitch* toggleSpecialChars;
    ToggleSwitch* toggleUppercase;

};
