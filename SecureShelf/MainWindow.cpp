#include "MainWindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    //кнопки боковой панели
    connect(ui.btn_toggle_menu, &QPushButton::clicked, this, &MainWindow::toggleMenu); // бургер меню раздвижение
    connect(ui.btn_passwords, &QPushButton::clicked, this, [this]() { ui.stackedWidget->setCurrentIndex(0); });
    connect(ui.btn_settings, &QPushButton::clicked, this, [this]() { ui.stackedWidget->setCurrentIndex(1); });
    connect(ui.btn_save, &QPushButton::clicked, this, [this]() { ui.stackedWidget->setCurrentIndex(2); });

    //“аблица паролей
    passwordModel = new PasswordModel(this);
    ui.passwords_table->setModel(passwordModel);
    ui.passwords_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //выравнивание по ширине
    passwordModel->addPassword("user1", "pass1", "service1", "site1", "note1");
    passwordModel->addPassword("user2", "pass2", "service2", "site2", "note2");
    auto* delegate = new HighlightDelegate(this);
    ui.passwords_table->setItemDelegate(delegate);


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

