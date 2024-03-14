#include "DialogSecret.h"
#include "PasswordWorker.h"
#include "NameSpaces.cpp"

DialogSecret::DialogSecret(QWidget* parent) : QDialog(parent), ui(new Ui::DialogSecret) {
    ui->setupUi(this);
    connect(ui->btn_enter_secret, &QPushButton::clicked, this, &DialogSecret::onEnterSecret);
}

DialogSecret::~DialogSecret() {
    delete ui;
}

void DialogSecret::onEnterSecret() {
    QString secret = ui->line_secret->text();
    PasswordWorker passwordWorker; // Убедитесь, что PasswordWorker инициализируется с правильным путем к файлу

    QList<QByteArray> dataList = passwordWorker.readData();
    if (dataList.isEmpty()) {
        // Шифруем строку "True"
        Cryptor cryptor; // Предполагается, что Cryptor корректно инициализирован и настроен
        QByteArray encryptedTrue = cryptor.encrypt("True", secret);

        // Записываем зашифрованные данные
        if (passwordWorker.writeData(encryptedTrue)) {
            qDebug() << encryptedTrue;
            emit secretAccepted(secret);
            accept();
        }
        else {
            qDebug() << "Unable to write to file";
        }
    }
    else {
        // Предполагаем, что первый элемент в dataList содержит нашу зашифрованную строку "True"
        Cryptor cryptor; // Предполагается, что Cryptor корректно инициализирован и настроен
        QByteArray decryptedLine = cryptor.decrypt(dataList.first(), secret);
        if (QString::fromUtf8(decryptedLine) == "True") {
            qDebug() << "Secret verified successfully";
            emit secretAccepted(secret);
            accept();
        }
        else {
            qDebug() << "Secret verification failed";
        }
    }
}

