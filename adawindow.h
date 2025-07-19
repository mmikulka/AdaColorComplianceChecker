#ifndef ADAWINDOW_H
#define ADAWINDOW_H

#include <QDialog>
#include <QStandardItemModel>

namespace Ui {
class AdaWindow;
}

class AdaWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AdaWindow(
        const QStandardItemModel* colors,
        QWidget *parent = nullptr
        );

    ~AdaWindow();

private:
    Ui::AdaWindow *ui;
};

#endif // ADAWINDOW_H
