#include "HighlightDelegate.h"

#include "ColorRepository.h" // ���������, ��� ���������� ������������ ����

void HighlightDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const {
    QStyleOptionViewItem opt(option);
    if (option.state & QStyle::State_MouseOver) {
        QColor backgroundColor = ColorRepository::highlightBackgroundColor(); // ������������� ������ ��� ��������� �����
        painter->fillRect(option.rect, backgroundColor);
    }
    QStyledItemDelegate::paint(painter, opt, index);
}
