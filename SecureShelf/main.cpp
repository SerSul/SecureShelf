#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include "Cryptor.h"
#include <QDir>
#include <QFile>
#include <QStandardPaths>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include "NameSpaces.cpp"
#include "DialogSecret.h"


QFile logFile;

void messageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
    if (!logFile.isOpen()) {
        logFile.setFileName(AppConfig::logFilePath);
        if (!logFile.open(QIODevice::Append | QIODevice::Text)) {
            qCritical() << "Не удалось открыть файл лога для записи:" << AppConfig::logFilePath;
            return;
        }
    }

    QTextStream out(&logFile);
    QString dateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    QString textType;

    switch (type) {
    case QtDebugMsg:
        textType = "DEBUG";
        break;
    case QtInfoMsg:
        textType = "INFO";
        break;
    case QtWarningMsg:
        textType = "WARNING";
        break;
    case QtCriticalMsg:
        textType = "CRITICAL";
        break;
    case QtFatalMsg:
        textType = "FATAL";
        abort(); 
    }

    out << dateTime << " - " << textType << ": " << msg << "\n";
    out.flush();
}


void ensureAppPropertiesExist() {

    QDir dir(AppConfig::secureShelfDirPath);
    if (!dir.exists()) {
        dir.mkpath(".");
    }
    
    QFile dbFile(AppConfig::dbFilePath);
    if (!dbFile.exists()) {
        if (!dbFile.open(QIODevice::WriteOnly)) {
            qWarning() << "bug" << AppConfig::dbFilePath;
        }
        else {
            dbFile.close();
        }
    }

}



int main(int argc, char* argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    DialogSecret secretDialog;
    QObject::connect(&secretDialog, &DialogSecret::secretAccepted, &w, &MainWindow::setSecret);
    if (secretDialog.exec() == QDialog::Accepted) {
        w.show();
        return a.exec();
    }
    else {
        return 0;
    }
}
