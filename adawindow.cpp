#include "adawindow.h"
#include "ui_adawindow.h"
#include "adacompliancechecker.h"
#include "colorswatchdelegate.h"
#include <QModelIndex>
#include <QAbstractItemModel>
#include <QList>

AdaWindow::AdaWindow(
    const QStandardItemModel* colors,
    QWidget *parent
    )
    :
    QDialog(parent),
    ui{new Ui::AdaWindow}
{
    ui->setupUi(this);

    // item model for Qlist
    QStandardItemModel* colortableModel = new QStandardItemModel;
    colortableModel->setColumnCount(4);
    colortableModel->setHeaderData(0, Qt::Horizontal, tr("Swatch"), Qt::DisplayRole );
    colortableModel->setHeaderData(1, Qt::Horizontal, tr("Background Color"), Qt::DisplayRole );
    colortableModel->setHeaderData(2, Qt::Horizontal, tr("Text Color"), Qt::DisplayRole );
    colortableModel->setHeaderData(3, Qt::Horizontal, tr("ADA Compliance"), Qt::DisplayRole);

    QList<QColor> ColorList;
    QStringList colorNames;

    for (int i = 0; i < colors->rowCount(); ++i) {
        auto* item = colors->item(i);
        QVariant data = item->data(Qt::UserRole);
        QColor color = data.canConvert<QColor>() ? qvariant_cast<QColor>(data) : QColor(item->text());
        if (color.isValid()) {
            ColorList << color;
            colorNames << item->text();  // store text names for clarity
        }
    }

    // Generate all ordered pairs (i != j)
    for (int i = 0; i < ColorList.size(); ++i) {
        for (int j = 0; j < ColorList.size(); ++j) {
            if (i != j)
            {
                QString name1 = colorNames[i];
                QString name2 = colorNames[j];

                QString label = name1 + " + " + name2;

                QStandardItem *swatchItem = new QStandardItem(label);
                QStandardItem *color1Label = new QStandardItem(name1);
                QStandardItem *color2Label = new QStandardItem(name2);

                auto adaNumber = ADAComplianceChecker::CalculateConstrastRatio(ColorList[i], ColorList[j]);

                QStandardItem *AdaNumberitem = new QStandardItem(QString::number(adaNumber, 'f', 2));

                // Optional: blend the two colors (or just use one as background)
                QColor c1 = ColorList[i];
                QColor c2 = ColorList[j];

                swatchItem->setBackground(c1);

                swatchItem->setForeground(QBrush(QColor(c2)));

                colortableModel->appendRow({swatchItem, color1Label, color2Label, AdaNumberitem});
            }
        }
    }

    this->ui->tableView->setModel(colortableModel);

    this->ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

AdaWindow::~AdaWindow()
{
    delete ui;
}
