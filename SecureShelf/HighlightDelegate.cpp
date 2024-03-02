#include "HighlightDelegate.h"

#include "ColorRepository.h" // Убедитесь, что подключили заголовочный файл

void HighlightDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const {
    QStyleOptionViewItem opt(option);
    if (option.state & QStyle::State_MouseOver) {
        QColor backgroundColor = ColorRepository::highlightBackgroundColor(); // Использование метода для получения цвета
        painter->fillRect(option.rect, backgroundColor);
    }
    QStyledItemDelegate::paint(painter, opt, index);
}
