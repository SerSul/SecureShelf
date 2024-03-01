#include "PasswordModel.h"

PasswordModel::PasswordModel(QObject* parent)
    : QStandardItemModel(parent) {
    setHorizontalHeaderLabels({ "Login", "Password", "Service", "Site", "Note" });
}

void PasswordModel::addPassword(const QString& login, const QString& password, const QString& service, const QString& site, const QString& note) {
    QList<QStandardItem*> rowItems;
    rowItems << new QStandardItem(login)
        << new QStandardItem(password)
        << new QStandardItem(service)
        << new QStandardItem(site)
        << new QStandardItem(note);
    rowItems[1]->setData(false, Qt::UserRole + 1);
    appendRow(rowItems);
}
