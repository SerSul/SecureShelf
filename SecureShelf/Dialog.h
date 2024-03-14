#pragma once

#include <QDialog>
#include "ui_DialogWindow.h" // Предполагается, что у вас есть ui файл с именем DialogWindow.ui
#include "PasswordGenerator.h"
#include "ToggleSwitch.h"

class Dialog : public QDialog {
    Q_OBJECT

public:
    Dialog(QWidget* parent = nullptr);
    ~Dialog();

private slots:
    void on_btn_generate_clicked();

private:
    Ui::Dialog* ui;
    ToggleSwitch* toggleDigits;
    ToggleSwitch* toggleLowercase;
    ToggleSwitch* toggleSpecialChars;
    ToggleSwitch* toggleUppercase;
};
