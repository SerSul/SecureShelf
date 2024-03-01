#include "PasswordGenerator.h"

PasswordGenerator::PasswordGenerator()
{
}

QString PasswordGenerator::generate(int length, bool useLowercase, bool useUppercase, bool useDigits, bool useSpecialChars)
{
    QString allowedChars;
    if (useLowercase) {
        allowedChars += lowercaseLetters;
    }
    if (useUppercase) {
        allowedChars += uppercaseLetters;
    }
    if (useDigits) {
        allowedChars += digits;
    }
    if (useSpecialChars) {
        allowedChars += specialChars;
    }

    QString password;
    for (int i = 0; i < length; ++i) {
        password += generateRandomCharacter(allowedChars);
    }
    return password;
}

QString PasswordGenerator::generateRandomCharacter(const QString& characters)
{
    if (characters.isEmpty()) {
        return QString();
    }
    int index = QRandomGenerator::global()->bounded(characters.length());
    return characters.at(index);
}
