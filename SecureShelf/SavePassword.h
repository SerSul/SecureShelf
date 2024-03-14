#pragma once
#include <qdialog.h>
#include "ui_SavePassword.h"
#include "ToggleSwitch.h"
#include <QRegularExpressionValidator>
#include "PasswordGenerator.h"
#include <QStringListModel>

class SavePassword : public QDialog
{
    Q_OBJECT

public:

    explicit SavePassword(QWidget* parent = nullptr) : QDialog(parent), ui(new Ui::Dialog)
    {

       


    }



    ~SavePassword()
    {
        qDebug() << "delete ui";
        delete ui; // ����������� ������� UI
    }

private:
    Ui::Dialog* ui; // ��������� �� ������ ����������
};

