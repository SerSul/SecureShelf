#pragma once
#ifndef COLORREPOSITORY_H
#define COLORREPOSITORY_H

#include <QColor>
#include <QPalette>

/**
 * Собраны все цвета, стили, эффекты
 */
namespace ColorRepository
{
    QPalette standardPalette();
    void setDarkMode(bool dark);

    QColor windowBackground();
    QColor baseBackground();
    QColor text();

    QColor pressedTextColor();
    QColor hoverTextColor();

    QColor pressedOutlineColor();
    QBrush hoverOutlineBrush(const QRect& rect);
    QColor buttonOutlineColor();

    QColor buttonPressedBackground();
    QColor buttonHoveredBackground();
    QColor buttonBackground();

    QBrush progressBarOutlineBrush(const QRect& rect);
    QBrush progressBarOutlineFadingBrush(const QRect& rect);
    QBrush progressBarContentsBrush(const QRect& rect);
    QColor progressBarTextColor(bool enabled);

    QColor highlightBackgroundColor();
}

#endif // COLORREPOSITORY_H

