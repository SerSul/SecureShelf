#include "MainWindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    //������ ������� ������
    connect(ui.btn_toggle_menu, &QPushButton::clicked, this, &MainWindow::toggleMenu); // ������ ���� �����������
    connect(ui.btn_passwords, &QPushButton::clicked, this, [this]() { ui.stackedWidget->setCurrentIndex(0); });
    connect(ui.btn_settings, &QPushButton::clicked, this, [this]() { ui.stackedWidget->setCurrentIndex(1); });
    connect(ui.btn_save, &QPushButton::clicked, this, [this]() { ui.stackedWidget->setCurrentIndex(2); });
    connect(ui.btn_utils, &QPushButton::clicked, this, [this]() { ui.stackedWidget->setCurrentIndex(3); });
    connect(ui.btn_test, &QPushButton::clicked, this, &MainWindow::openDialog);


    //������� �������
    passwordModel = new PasswordModel(this);
    ui.passwords_table->setModel(passwordModel);
    ui.passwords_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //������������ �� ������
    passwordModel->addPassword("user1", "pass1", "service1", "site1", "note1");
    passwordModel->addPassword("user2", "pass2", "service2", "site2", "note2");
    auto* delegate = new HighlightDelegate(this);
    ui.passwords_table->setItemDelegate(delegate);

    ToggleSwitch* toggleDigits = new ToggleSwitch(ui.page_utils);
    ToggleSwitch* toggleLowercase = new ToggleSwitch(ui.page_utils);
    ToggleSwitch* toggleSpecialChars = new ToggleSwitch(ui.page_utils);
    ToggleSwitch* toggleUppercase = new ToggleSwitch(ui.page_utils);
    ui.layoutForToggles->addWidget(toggleDigits);
    ui.layoutForToggles->addWidget(toggleLowercase);
    ui.layoutForToggles->addWidget(toggleSpecialChars);
    ui.layoutForToggles->addWidget(toggleUppercase);
    //������ � utils ��� �������


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
    Dialog dialog(this); // ������ ���������� ����
    dialog.exec(); // ���������� ��� ��� ��������� ����
}