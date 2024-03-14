#include "MainWindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    //кнопки боковой панели
    connect(ui.btn_toggle_menu, &QPushButton::clicked, this, &MainWindow::toggleMenu); // бургер меню раздвижение
    connect(ui.btn_passwords, &QPushButton::clicked, this, [this]() { ui.stackedWidget->setCurrentIndex(0); });
    connect(ui.btn_settings, &QPushButton::clicked, this, [this]() { ui.stackedWidget->setCurrentIndex(1); });
    connect(ui.btn_utils, &QPushButton::clicked, this, [this]() { ui.stackedWidget->setCurrentIndex(3); });
    connect(ui.btn_test, &QPushButton::clicked, this, &MainWindow::openDialog);


    //“аблица паролей
    passwordModel = new PasswordModel(this);
    ui.passwords_table->setModel(passwordModel);
    ui.passwords_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //выравнивание по ширине
    passwordModel->addPassword("user1", "pass1", "service1", "site1", "note1");
    passwordModel->addPassword("user2", "pass2", "service2", "site2", "note2");
    auto* delegate = new HighlightDelegate(this);
    ui.passwords_table->setItemDelegate(delegate);

    toggleDigits = new ToggleSwitch(ui.mainSettings);
    toggleLowercase = new ToggleSwitch(ui.mainSettings);
    toggleSpecialChars = new ToggleSwitch(ui.mainSettings);
    toggleUppercase = new ToggleSwitch(ui.mainSettings);
    toggleDigits->setChecked(true);
    toggleLowercase->setChecked(true);
    toggleUppercase->setChecked(true);
    ui.buttons_layout->addSpacing(20);
    ui.buttons_layout->addWidget(toggleUppercase);
    ui.buttons_layout->addSpacing(20);
    ui.buttons_layout->addWidget(toggleLowercase);
    ui.buttons_layout->addSpacing(20);
    ui.buttons_layout->addWidget(toggleDigits);
    ui.buttons_layout->addSpacing(20);
    ui.buttons_layout->addWidget(toggleSpecialChars);
    ui.buttons_layout->addSpacing(20);

    QRegularExpression rx("[0-9]{1,3}");
    ui.line_count->setValidator(new QRegularExpressionValidator(rx, ui.line_count));
    ui.line_count->setAttribute(Qt::WA_MacShowFocusRect, 0);



}

MainWindow::~MainWindow()
{}


void MainWindow::toggleMenu() {
    int endWidth = ui.frame_left_menu->width() == 70 ? 150 : 70; 

    QPropertyAnimation* animation = new QPropertyAnimation(ui.frame_left_menu, "maximumWidth");
    animation->setDuration(200);
    animation->setStartValue(ui.frame_left_menu->width()); 
    animation->setEndValue(endWidth); 
    animation->setEasingCurve(QEasingCurve::InOutQuad); 
    animation->start(QPropertyAnimation::DeleteWhenStopped); 

}

void MainWindow::openDialog()
{
    Dialog dialog(this); 
    dialog.exec(); 
}

void MainWindow::on_btn_generate_clicked()
{
    PasswordGenerator generator;
    ui.passwordsList->clear();
    bool useDigits = toggleDigits->isChecked();
    bool useLowercase = toggleLowercase->isChecked();
    bool useSpecialChars = toggleSpecialChars->isChecked();
    bool useUppercase = toggleUppercase->isChecked();

    for (int i = 0; i < 9; ++i) {
        QString password = generator.generate(ui.line_count->text().toInt(), useLowercase, useUppercase, useDigits, useSpecialChars); // ѕример с фиксированной длиной 12
        if (!password.isEmpty())
            ui.passwordsList->addItem(password);
        qDebug() << password;
    }
}