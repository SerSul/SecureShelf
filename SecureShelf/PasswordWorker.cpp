#include "PasswordWorker.h"

PasswordWorker::PasswordWorker()
{
}

bool PasswordWorker::writeData(const QByteArray& data) {
    QFile file(filePath);
    if (!file.open(QIODevice::Append)) {
        return false;
    }
    QDataStream out(&file);
    out << data;
    file.close();
    return true;
}



QList<QByteArray> PasswordWorker::readData() {
    QFile file(filePath);
    QList<QByteArray> dataList;
    if (file.open(QIODevice::ReadOnly)) {
        QDataStream in(&file);
        QByteArray data;

        while (!in.atEnd()) {
            in >> data; 
            dataList.append(data);
        }
    }
    return dataList;
}

