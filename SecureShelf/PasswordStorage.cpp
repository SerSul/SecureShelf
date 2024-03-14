#include "PasswordStorage.h"

PasswordStorage::PasswordStorage(const QString& filePath, const QString& password)
    : filePath(filePath), masterPassword(password)
{
}

bool PasswordStorage::writeData(const QByteArray& data) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }

    QByteArray existingData = file.readAll();
    file.close();

    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }

    QDataStream out(&file);
    if (!existingData.isEmpty()) {
        out.writeRawData(existingData.constData(), existingData.size());
    }
    out << data; 
    file.close();
    return true;
}

QByteArray PasswordStorage::readData() {
    QFile file(filePath);
    QByteArray data;
    if (file.open(QIODevice::ReadOnly)) {
        QDataStream in(&file);
        QByteArray firstLine;
        in >> firstLine; 

        while (!in.atEnd()) {
            QByteArray line;
            in >> line;
            data.append(line); 
        }
    }
    return data;
}

