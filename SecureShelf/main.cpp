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


QFile logFile;
QString homeDir = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
QString secureShelfDirPath = QDir(homeDir).filePath(".SecureShelf");


void messageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
    if (!logFile.isOpen()) {
        QString logFilePath = QDir(secureShelfDirPath).filePath("application.log");
        logFile.setFileName(logFilePath);
        if (!logFile.open(QIODevice::Append | QIODevice::Text)) {
            qCritical() << "Не удалось открыть файл лога для записи:" << logFilePath;
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

    QDir dir(secureShelfDirPath);
    if (!dir.exists()) {
        dir.mkpath(".");
    }
    
    QString dbFilePath = QDir(secureShelfDirPath).filePath("database");
    QFile dbFile(dbFilePath);
    if (!dbFile.exists()) {
        if (!dbFile.open(QIODevice::WriteOnly)) {
            qWarning() << "bug" << dbFilePath;
        }
        else {
            dbFile.close();
        }
    }

}



int main(int argc, char *argv[])
{
    qInstallMessageHandler(messageHandler);
    ensureAppPropertiesExist();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

