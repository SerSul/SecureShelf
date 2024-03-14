#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent) {
    ui.setupUi(this);

    setupSideMenuButtons();
    setupPasswordTable();
    setupToggleSwitches();
    setupPasswordGeneratorInput();

}

MainWindow::~MainWindow() {}

void MainWindow::setupSideMenuButtons() {
    // Настройка кнопок бокового меню
    connect(ui.btn_toggle_menu, &QPushButton::clicked, this, &MainWindow::toggleMenu);
    connect(ui.btn_passwords, &QPushButton::clicked, this, [this]() { ui.stackedWidget->setCurrentIndex(0); });
    connect(ui.btn_settings, &QPushButton::clicked, this, [this]() { ui.stackedWidget->setCurrentIndex(1); });
    connect(ui.btn_utils, &QPushButton::clicked, this, [this]() { ui.stackedWidget->setCurrentIndex(3); });
    connect(ui.btn_test, &QPushButton::clicked, this, &MainWindow::openDialog);
}



void MainWindow::setupPasswordTable() {
    // Настройка таблицы паролей
    passwordModel = new PasswordModel(this);
    ui.passwords_table->setModel(passwordModel);
    ui.passwords_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    auto* delegate = new HighlightDelegate(this);
    ui.passwords_table->setItemDelegate(delegate);
}

void MainWindow::setPasswords() {
    QList<QByteArray> encryptedPasswords = passwordworker.readData();
    qDebug() << "Secret: " << secret << "\n";
    for (const QByteArray& encryptedData : encryptedPasswords) {
        qDebug() << "crypted data: " + encryptedData+ "\n";
        QByteArray decryptedData = cryptor.decrypt(encryptedData, this->secret);
        QString dataString = QString::fromUtf8(decryptedData);
        qDebug() << "decrypted: " << decryptedData << "\n";
        QStringList dataParts = dataString.split(';');
        if (dataParts.size() >= 5) { 
            passwordModel->addPassword(dataParts.at(0), dataParts.at(1), dataParts.at(2), dataParts.at(3), dataParts.at(4));
        }
    }
}


void MainWindow::setupToggleSwitches() {
    // Настройка переключателей
    toggleDigits = new ToggleSwitch(ui.mainSettings);
    toggleLowercase = new ToggleSwitch(ui.mainSettings);
    toggleSpecialChars = new ToggleSwitch(ui.mainSettings);
    toggleUppercase = new ToggleSwitch(ui.mainSettings);

    // Установка начального состояния переключателей
    toggleDigits->setChecked(true);
    toggleLowercase->setChecked(true);
    toggleUppercase->setChecked(true);

    // Добавление переключателей в интерфейс
    ui.buttons_layout->addSpacing(20);
    ui.buttons_layout->addWidget(toggleUppercase);
    ui.buttons_layout->addSpacing(20);
    ui.buttons_layout->addWidget(toggleLowercase);
    ui.buttons_layout->addSpacing(20);
    ui.buttons_layout->addWidget(toggleDigits);
    ui.buttons_layout->addSpacing(20);
    ui.buttons_layout->addWidget(toggleSpecialChars);
    ui.buttons_layout->addSpacing(20);
}

void MainWindow::setupPasswordGeneratorInput() {
    // Настройка ввода для генератора паролей
    QRegularExpression rx("[0-9]{1,3}");
    ui.line_count->setValidator(new QRegularExpressionValidator(rx, ui.line_count));
    ui.line_count->setAttribute(Qt::WA_MacShowFocusRect, 0);
}

void MainWindow::toggleMenu() {
    int endWidth = ui.frame_left_menu->width() == 70 ? 150 : 70;

    QPropertyAnimation* animation = new QPropertyAnimation(ui.frame_left_menu, "maximumWidth");
    animation->setDuration(200);
    animation->setStartValue(ui.frame_left_menu->width());
    animation->setEndValue(endWidth);
    animation->setEasingCurve(QEasingCurve::InOutQuad);
    animation->start(QPropertyAnimation::DeleteWhenStopped);
}

void MainWindow::openDialog() {
    Dialog dialog(this);
    dialog.exec();
}

void MainWindow::on_btn_generate_clicked() {
    PasswordGenerator generator;
    ui.passwordsList->clear();
    bool useDigits = toggleDigits->isChecked();
    bool useLowercase = toggleLowercase->isChecked();
    bool useSpecialChars = toggleSpecialChars->isChecked();
    bool useUppercase = toggleUppercase->isChecked();

    for (int i = 0; i < 9; ++i) {
        QString password = generator.generate(ui.line_count->text().toInt(), useLowercase, useUppercase, useDigits, useSpecialChars);
        if (!password.isEmpty()) ui.passwordsList->addItem(password);
        qDebug() << password;
    }
}
