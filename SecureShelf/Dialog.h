#pragma once

#include <qdialog.h>
#include "ui_dialogWindow.h"
#include "ToggleSwitch.h"
#include <QRegularExpressionValidator>
#include "PasswordGenerator.h"
#include <QStringListModel>
class Dialog : public QDialog
{
    Q_OBJECT


private slots:
    void on_btn_generate_clicked()
    {
        PasswordGenerator generator; 
        ui->passwordsList->clear();
        bool useDigits = toggleDigits->isChecked();
        bool useLowercase = toggleLowercase->isChecked();
        bool useSpecialChars = toggleSpecialChars->isChecked();
        bool useUppercase = toggleUppercase->isChecked();

        for (int i = 0; i < 9; ++i) {
            QString password = generator.generate(ui->line_count->text().toInt(), useLowercase, useUppercase, useDigits, useSpecialChars); // Пример с фиксированной длиной 12
            if (!password.isEmpty())
                ui->passwordsList->addItem(password);
            qDebug() << password; 
        }
    }
public:

    explicit Dialog(QWidget* parent = nullptr) : QDialog(parent), ui(new Ui::Dialog)
    {

        ui->setupUi(this);
        toggleDigits = new ToggleSwitch(ui->mainSettings);
        toggleLowercase = new ToggleSwitch(ui->mainSettings);
        toggleSpecialChars = new ToggleSwitch(ui->mainSettings);
        toggleUppercase = new ToggleSwitch(ui->mainSettings);
        ui->buttons_layout->addWidget(toggleUppercase);
        ui->buttons_layout->addWidget(toggleLowercase);
        ui->buttons_layout->addWidget(toggleDigits);
        ui->buttons_layout->addWidget(toggleSpecialChars);
        toggleDigits->setChecked(true);
        toggleLowercase->setChecked(true);
        toggleUppercase->setChecked(true);

        QRegularExpression rx("[0-9]{1,3}");
        ui->line_count->setValidator(new QRegularExpressionValidator(rx, ui->line_count));
        ui->line_count->setAttribute(Qt::WA_MacShowFocusRect, 0);


    }



    ~Dialog()
    {
        qDebug() << "delete ui";
        delete ui; // Освобождаем ресурсы UI
    }

private:
    Ui::Dialog *ui; // Указатель на объект интерфейса
    ToggleSwitch* toggleDigits;
    ToggleSwitch* toggleLowercase;
    ToggleSwitch* toggleSpecialChars;
    ToggleSwitch* toggleUppercase;
    
};