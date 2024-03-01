#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include <QPropertyAnimation>
#include "PasswordModel.h"
#include "HighlightDelegate.h"



class MainWindow : public QMainWindow
{
    Q_OBJECT

private slots:
    void toggleMenu(); 


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();





private:
    Ui::MainWindow ui;
    PasswordModel* passwordModel;

};
