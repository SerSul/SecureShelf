#include "Dialog.h"
#include "ToggleSwitch.h"
#include "PasswordGenerator.h"
#include <QDebug>
#include <QRegularExpressionValidator>

Dialog::Dialog(QWidget* parent) : QDialog(parent), ui(new Ui::Dialog) {
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
    ui->line_count->setValidator(new QRegularExpressionValidator(rx, this));
    ui->line_count->setAttribute(Qt::WA_MacShowFocusRect, 0);

    connect(ui->btn_generate, &QPushButton::clicked, this, &Dialog::on_btn_generate_clicked);
}

Dialog::~Dialog() {
    delete ui;
}

void Dialog::on_btn_generate_clicked() {
    PasswordGenerator generator;
    ui->passwordsList->clear();
    bool useDigits = toggleDigits->isChecked();
    bool useLowercase = toggleLowercase->isChecked();
    bool useSpecialChars = toggleSpecialChars->isChecked();
    bool useUppercase = toggleUppercase->isChecked();

    for (int i = 0; i < 9; ++i) {
        QString password = generator.generate(ui->line_count->text().toInt(), useLowercase, useUppercase, useDigits, useSpecialChars);
        if (!password.isEmpty())
            ui->passwordsList->addItem(password);
        qDebug() << password;
    }
}
