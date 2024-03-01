#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include <QPropertyAnimation>
#include "PasswordModel.h"
#include "HighlightDelegate.h"
#include "ClickableCircle.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

private slots:
    void toggleMenu(); 
    void onCircleClicked(); 

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


protected:
    void changeEvent(QEvent* event) override; 


private:
    Ui::MainWindow ui;
    PasswordModel* passwordModel;
    ClickableCircle* circle = nullptr;
};
