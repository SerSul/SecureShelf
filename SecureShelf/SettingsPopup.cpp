#include "SettingsPopup.h"
#include <QVBoxLayout>
#include <QPushButton>

SettingsPopup::SettingsPopup(QWidget* parent) : QWidget(parent, Qt::Popup) {
    QVBoxLayout* layout = new QVBoxLayout(this);
    // �������� � layout ���� �������� ����������
    QPushButton* button1 = new QPushButton("��������� 1", this);
    // ����������� ��������� ��������
    layout->addWidget(button1);
    // ���������� layout
    setLayout(layout);
}
