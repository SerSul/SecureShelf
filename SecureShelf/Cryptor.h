// Cryptor.h
#ifndef CRYPTOR_H
#define CRYPTOR_H

#include <QObject>
#include <QByteArray>

class Cryptor : public QObject
{
    Q_OBJECT
public:
    explicit Cryptor(QObject* parent = nullptr);

    QByteArray encrypt(const QByteArray& data, const QString& password);
    QByteArray decrypt(const QByteArray& encryptedData, const QString& password);

private:
    QByteArray hashKey(const QString& password);
    QByteArray generateIV();
};

#endif // CRYPTOR_H
