#include <QStyledItemDelegate>
#include <QPainter>

class HighlightDelegate : public QStyledItemDelegate {
public:
    HighlightDelegate(QObject* parent = nullptr) : QStyledItemDelegate(parent) {}

    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override {
        QStyleOptionViewItem opt(option);
        if (option.state & QStyle::State_MouseOver) {
            QColor backgroundColor = QColor(255, 255, 255, 30); // Белая дымка
            painter->fillRect(option.rect, backgroundColor);
        }
        QStyledItemDelegate::paint(painter, opt, index);
    }
};
