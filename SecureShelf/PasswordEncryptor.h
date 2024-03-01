#ifndef PASSWORDENCRYPTOR_H
#define PASSWORDENCRYPTOR_H

#include <QString>
#include <QByteArray>

class PasswordEncryptor
{
public:
    PasswordEncryptor(const QString& secretWord);
    QByteArray encrypt(const QString& plaintext);
    QString decrypt(const QByteArray& ciphertext);

private:
    QString secretWord;
    bool generateKeyAndIV(unsigned char* key, unsigned char* iv);
    QByteArray encryptAES(const QString& plaintext);
    QString decryptAES(const QByteArray& ciphertext);
};

#endif // PASSWORDENCRYPTOR_H
