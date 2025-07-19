#include "colorswatchdelegate.h"

ColorSwatchDelegate::ColorSwatchDelegate(QObject *parent) : QStyledItemDelegate(parent) {}

void ColorSwatchDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
   QVariant colorData = index.data(Qt::UserRole);
    QVariant textData = index.data(Qt::DisplayRole);

    if (colorData.isValid() && colorData.canConvert<QColor>()) {
        QColor color = colorData.value<QColor>();

        // Draw the color swatch
        QRect swatchRect = option.rect.adjusted(5, 5, -option.rect.width() / 2, -5);
        painter->setRenderHint(QPainter::Antialiasing, true);
        painter->setBrush(color);
        painter->setPen(Qt::NoPen);
        painter->drawRoundedRect(swatchRect, 8, 8); // Rounded corners for modern appearance

        // Draw the border for the swatch
        painter->setPen(Qt::black);
        painter->drawRoundedRect(swatchRect, 8, 8);

        // Draw the label text
        QRect textRect = option.rect.adjusted(option.rect.width() / 2 + 10, 0, -5, 0);
        painter->setPen(Qt::black);
        painter->drawText(textRect, Qt::AlignVCenter | Qt::AlignLeft, textData.toString());
    }
}

QSize ColorSwatchDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    return QSize(150, 40);  // Adjust the size of each item
}
