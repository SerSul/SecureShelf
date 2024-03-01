// Cryptor.cpp
#include "Cryptor.h"
#include <QCryptographicHash>
#include <QRandomGenerator>
#include <openssl/evp.h>

Cryptor::Cryptor(QObject* parent) : QObject(parent)
{
}

QByteArray Cryptor::encrypt(const QByteArray& data, const QString& password)
{
    QByteArray key = hashKey(password);
    QByteArray iv = generateIV();
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();

    if (!ctx) return QByteArray();

    if (EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, (unsigned char*)key.data(), (unsigned char*)iv.data()) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        return QByteArray();
    }

    QByteArray encryptedData;
    int len = 0;
    int plaintextLen = data.size();
    int ciphertextLen = 0;
    encryptedData.resize(plaintextLen + EVP_CIPHER_block_size(EVP_aes_256_cbc()));

    if (EVP_EncryptUpdate(ctx, (unsigned char*)encryptedData.data(), &len, (const unsigned char*)data.data(), plaintextLen) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        return QByteArray();
    }
    ciphertextLen += len;

    if (EVP_EncryptFinal_ex(ctx, (unsigned char*)encryptedData.data() + len, &len) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        return QByteArray();
    }
    ciphertextLen += len;
    encryptedData.resize(ciphertextLen);

    EVP_CIPHER_CTX_free(ctx);

    return iv + encryptedData; // Включаем IV в начало зашифрованных данных
}

QByteArray Cryptor::decrypt(const QByteArray& encryptedData, const QString& password)
{
    QByteArray key = hashKey(password);
    QByteArray iv = encryptedData.left(EVP_MAX_IV_LENGTH); // Извлекаем IV из начала данных
    QByteArray actualEncryptedData = encryptedData.mid(EVP_MAX_IV_LENGTH);
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();

    if (!ctx) return QByteArray();

    if (EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, (unsigned char*)key.data(), (unsigned char*)iv.data()) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        return QByteArray();
    }

    QByteArray decryptedData;
    int len = 0;
    int plaintextLen = 0;
    decryptedData.resize(actualEncryptedData.size());

    if (EVP_DecryptUpdate(ctx, (unsigned char*)decryptedData.data(), &len, (const unsigned char*)actualEncryptedData.data(), actualEncryptedData.size()) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        return QByteArray();
    }
    plaintextLen += len;

    if (EVP_DecryptFinal_ex(ctx, (unsigned char*)decryptedData.data() + len, &len) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        return QByteArray();
    }
    plaintextLen += len;
    decryptedData.resize(plaintextLen);

    EVP_CIPHER_CTX_free(ctx);

    return decryptedData;
}

QByteArray Cryptor::hashKey(const QString& password)
{
    return QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
}

QByteArray Cryptor::generateIV() {
    QByteArray iv(EVP_MAX_IV_LENGTH, 0); // Инициализируем массив нулями
    for (int i = 0; i < iv.size(); ++i) {
        // Заполняем каждый байт случайным числом от 0 до 255
        iv[i] = static_cast<char>(QRandomGenerator::global()->bounded(256));
    }
    return iv;
}

