#include "DialogSecret.h"
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
    Cryptor cryptor;
    QString filePath = AppConfig::dbFilePath;
    QFile file(filePath);

    if (file.open(QIODevice::ReadWrite)) {
        QByteArray line = file.readLine();
        if (line.isEmpty()) {
            QByteArray encryptedTrue = cryptor.encrypt("True", secret);
            qDebug() << encryptedTrue;
            file.write(encryptedTrue);
            emit secretAccepted(secret);
            accept();
        }
        else {
            QByteArray decryptedLine = cryptor.decrypt(line, secret);
            qDebug() << "\n" + decryptedLine;
            if (QString::fromUtf8(decryptedLine) == "True") {
                qDebug() << "Secret verified successfully";
                emit secretAccepted(secret);
                accept();
            }
            else {
                qDebug() << "Secret verification failed";
            }
        }
        file.close();
    }
    else {
        qDebug() << "Unable to open file for reading/writing";
    }
}
