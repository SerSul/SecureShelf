#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include "Cryptor.h"
#include <QDir>
#include <QFile>
#include <QStandardPaths>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>


void ensureAppPropertiesExist() {
    QString homeDir = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    QString secureShelfDirPath = QDir(homeDir).filePath(".SecureShelf");

    QDir dir(secureShelfDirPath);
    if (!dir.exists()) {
        dir.mkpath(".");
    }
    

}



int main(int argc, char *argv[])
{
    ensureAppPropertiesExist();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

