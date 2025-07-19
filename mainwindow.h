#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColorDialog>
#include <QColor>
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class AdaWindow;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void openColorDialog();

    void addColorToModel();

    void updateCurrentcolor();

    void UpdateRGBFromHex();

    void CalculateADA();

private:
    void SlotSetup();

    void updateColorTextBoxes();

    void updateColorPreview();

    Ui::MainWindow *ui;

    AdaWindow *adaWindow;

    // Color Being edited
    QColor currentColor;

    // item model for Qlist
    QStandardItemModel colorListModel;

    // list of colors
    QList<QString> colorNames;
};
#endif // MAINWINDOW_H
