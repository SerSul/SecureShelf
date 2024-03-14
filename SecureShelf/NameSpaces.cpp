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
#pragma once


namespace AppConfig {
    const QString homeDir = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    const QString secureShelfDirPath = QDir(homeDir).filePath(".SecureShelf");
    const QString dbFilePath = QDir(AppConfig::secureShelfDirPath).filePath("database");
    const QString logFilePath = QDir(AppConfig::secureShelfDirPath).filePath("application.log");
}