#pragma once
#ifndef PASSWORDGENERATOR_H
#define PASSWORDGENERATOR_H

#include <QString>
#include <QRandomGenerator>

class PasswordGenerator
{
public:
    PasswordGenerator();
    QString generate(int length, bool useLowercase, bool useUppercase, bool useDigits, bool useSpecialChars);

private:
    QString lowercaseLetters = "abcdefghijklmnopqrstuvwxyz";
    QString uppercaseLetters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    QString digits = "0123456789";
    QString specialChars = "!@#$%^&*()_+-=[]{}|;':,.<>/?";

    QString generateRandomCharacter(const QString& characters);
};

#endif // PASSWORDGENERATOR_H
