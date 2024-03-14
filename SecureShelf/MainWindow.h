#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include <QPropertyAnimation>
#include "PasswordModel.h"
#include "HighlightDelegate.h"
#include "ToggleSwitch.h"
#include "dialog.h"
#include "PasswordWorker.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

private slots:
    void toggleMenu(); 
    void setupPasswordTable();
    void setPasswords();
    void setupToggleSwitches();
    void setupPasswordGeneratorInput();
    void openDialog();
    void on_btn_generate_clicked();


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setupSideMenuButtons();


public slots:
    void setSecret(const QString& secret) {
        this->secret = secret;
        PasswordWorker passwordworker;
        Cryptor cryptor;
        QByteArray data1 = cryptor.encrypt("1;2;3;4;5", this->secret);
        passwordworker.writeData(data1);
        passwordworker.writeData(data1);
        passwordworker.writeData(data1);
        setPasswords();
    }


private:
    QString secret;
    PasswordWorker passwordworker;
    QList<QByteArray> encryptedPasswords;
    Cryptor cryptor;
    Ui::MainWindow ui;
    PasswordModel* passwordModel;
    ToggleSwitch* toggleDigits;
    ToggleSwitch* toggleLowercase;
    ToggleSwitch* toggleSpecialChars;
    ToggleSwitch* toggleUppercase;

};
