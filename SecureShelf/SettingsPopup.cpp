#include "SettingsPopup.h"
#include <QVBoxLayout>
#include <QPushButton>

SettingsPopup::SettingsPopup(QWidget* parent) : QWidget(parent, Qt::Popup) {
    QVBoxLayout* layout = new QVBoxLayout(this);
    // Добавьте в layout ваши элементы управления
    QPushButton* button1 = new QPushButton("Настройка 1", this);
    // Продолжайте добавлять элементы
    layout->addWidget(button1);
    // Установите layout
    setLayout(layout);
}
