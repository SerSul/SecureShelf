#pragma once
#ifndef PASSWORDMODEL_H
#define PASSWORDMODEL_H

#include <QStandardItemModel>

class PasswordModel : public QStandardItemModel {
    Q_OBJECT

public:
    PasswordModel(QObject* parent = nullptr);

    void addPassword(const QString& login, const QString& password, const QString& service, const QString& site, const QString& note);
};

#endif // PASSWORDMODEL_H
