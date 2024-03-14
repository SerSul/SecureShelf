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

    bool savePassword(const QString& password);
    QString loadPassword();

private:
    QString filePath;
    Cryptor cryptor;
    QString masterPassword;

    bool writeData(const QByteArray& data);
    QByteArray readData();
};

#endif // PASSWORDSTORAGE_H
