#include "PasswordStorage.h"

PasswordStorage::PasswordStorage(const QString& filePath, const QString& password)
    : filePath(filePath), masterPassword(password)
{
}

bool PasswordStorage::savePassword(const QString& password)
{
    QByteArray encryptedData = cryptor.encrypt(password.toUtf8(), masterPassword);
    return writeData(encryptedData);
}

QString PasswordStorage::loadPassword()
{
    QByteArray data = readData();
    QByteArray decryptedData = cryptor.decrypt(data, masterPassword);
    return QString::fromUtf8(decryptedData);
}

bool PasswordStorage::writeData(const QByteArray& data)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }

    QDataStream out(&file);
    out << data;
    file.close();
    return true;
}

QByteArray PasswordStorage::readData()
{
    QFile file(filePath);
    QByteArray data;
    if (file.open(QIODevice::ReadOnly)) {
        QDataStream in(&file);
        in >> data;
    }
    return data;
}
