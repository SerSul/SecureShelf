#ifndef DATAENCRYPTORANDSAVER_H
#define DATAENCRYPTORANDSAVER_H

#include <QVector>
#include <QString>
#include <QByteArray>
#include "Cryptor.h"

class DataEncryptorAndSaver
{
public:
    DataEncryptorAndSaver(const QString& password, const QString& filePath);
    void encryptAndSave(const QVector<QByteArray>& data);

private:
    Cryptor cryptor;
    QString password;
    QString filePath;
};

#endif // DATAENCRYPTORANDSAVER_H
