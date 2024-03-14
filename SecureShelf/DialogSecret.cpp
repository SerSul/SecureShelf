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
    PasswordWorker passwordWorker; // ���������, ��� PasswordWorker ���������������� � ���������� ����� � �����

    QList<QByteArray> dataList = passwordWorker.readData();
    if (dataList.isEmpty()) {
        // ������� ������ "True"
        Cryptor cryptor; // ��������������, ��� Cryptor ��������� ��������������� � ��������
        QByteArray encryptedTrue = cryptor.encrypt("True", secret);

        // ���������� ������������� ������
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
        // ������������, ��� ������ ������� � dataList �������� ���� ������������� ������ "True"
        Cryptor cryptor; // ��������������, ��� Cryptor ��������� ��������������� � ��������
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

