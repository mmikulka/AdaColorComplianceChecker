#ifndef COLORSWATCHDELEGATE_H
#define COLORSWATCHDELEGATE_H

#include <QStandardItemModel>
#include <QStyledItemDelegate>
#include <QPainter>

// Custom Delegate to display color swatches
class ColorSwatchDelegate :  public QStyledItemDelegate {
public:
    explicit ColorSwatchDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // COLORSWATCHDELEGATE_H
