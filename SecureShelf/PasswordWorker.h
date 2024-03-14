#pragma once
#ifndef PASSWORDWORKER_H
#define PASSWORDWORKER_H

#include <QString>
#include <QFile>
#include <QDataStream>
#include "Cryptor.h"
#include "NameSpaces.cpp"

class PasswordWorker
{
public:
    PasswordWorker();
    bool writeData(const QByteArray& data);
    QList<QByteArray> readData();
private:
    QString filePath = AppConfig::dbFilePath;
    Cryptor cryptor;
    QString masterPassword;


};

#endif 
