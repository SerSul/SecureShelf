#pragma once
#include <QStyledItemDelegate>
#include <QPainter>

class HighlightDelegate : public QStyledItemDelegate {
public:
    HighlightDelegate(QObject* parent = nullptr) : QStyledItemDelegate(parent) {}

    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
};
