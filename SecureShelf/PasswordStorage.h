#pragma once
#ifndef PASSWORDSTORAGE_H
#define PASSWORDSTORAGE_H

#include <QString>
#include <QFile>
#include <QDataStream>
#include "Cryptor.h"

class PasswordStorage
{
public:
    PasswordStorage(const QString& filePath, const QString& password);
    bool writeData(const QByteArray& data);
    QByteArray readData();
private:
    QString filePath;
    Cryptor cryptor;
    QString masterPassword;


};

#endif 
