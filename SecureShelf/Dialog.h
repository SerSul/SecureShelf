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
        QStringList passwordList;

        bool useDigits = toggleDigits->isChecked();
        bool useLowercase = toggleLowercase->isChecked();
        bool useSpecialChars = toggleSpecialChars->isChecked();
        bool useUppercase = toggleUppercase->isChecked();

        // ��������� �������
        for (int i = 0; i < 9; ++i) {
            QString password = generator.generate(ui->line_count->text().toInt(), useLowercase, useUppercase, useDigits, useSpecialChars); // ������ � ������������� ������ 12
            passwordList.append(password);
            qDebug() << password; // ������� ������ � ������� (��� ���������� ��-�������)
        }
        passwordsListModel->setStringList(passwordList);
    }

public:

    explicit Dialog(QWidget *parent = nullptr) : QDialog(parent), ui(new Ui::Dialog)
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
  
        QRegularExpression rx("[0-9]{1,3}");
        ui->line_count->setValidator(new QRegularExpressionValidator(rx, ui->line_count));
        passwordsListModel = new QStringListModel(this);
        ui->passwordsList->setModel(passwordsListModel);

        ui->passwordsList->setStyleSheet("QListView {"
            "border: none;"
            "}"
            "QListView::item {"
            "border-bottom: 1px solid lightgray;"
            "padding: 5px;"
            "}"
            "QListView::item:selected {"
            "background: lightblue;"
            "color: black;"
            "}");
        ui->passwordsList->setEditTriggers(QAbstractItemView::NoEditTriggers); 
        ui->passwordsList->setSelectionMode(QAbstractItemView::SingleSelection); // ��������� �������� ������ ���� ������� �� ���
        ui->passwordsList->setSelectionBehavior(QAbstractItemView::SelectRows); // �������� ��� ������

    }



    ~Dialog()
    {
        qDebug() << "delete ui";
        delete ui; // ����������� ������� UI
    }

private:
    Ui::Dialog *ui; // ��������� �� ������ ����������
    ToggleSwitch* toggleDigits;
    ToggleSwitch* toggleLowercase;
    ToggleSwitch* toggleSpecialChars;
    ToggleSwitch* toggleUppercase;
    QStringListModel* passwordsListModel;
    
};