#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "colorswatchdelegate.h"
#include "adawindow.h"
#include "utilities.h"
#include <QtGui/QPalette>

MainWindow::MainWindow(QWidget *parent)
    :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    currentColor{0, 0, 0}
{
    ui->setupUi(this);

    updateColorTextBoxes();

    this->SlotSetup();

    // Set the model and delegate
    this->ui->listView->setModel(&this->colorListModel);
    this->ui->listView->setItemDelegate(new ColorSwatchDelegate(this->ui->listView));
}

void MainWindow::CalculateADA() {

    this->adaWindow = new AdaWindow (&(this->colorListModel), nullptr);

    this->adaWindow->show();
}


void MainWindow::openColorDialog() {
    QColor color =
        QColorDialog::getColor(
            Qt::white,
            this
            );

    if (color.isValid()) {
        this->currentColor = color;
        updateColorTextBoxes();
        updateColorPreview();
    }
}

void MainWindow::addColorToModel()
{
    QString colorName = this->currentColor.name(QColor::HexRgb);

    if (!this->colorNames.contains(colorName))
    {
        this->colorNames.append(colorName);
        QStandardItem *standardItem = new QStandardItem(colorName);
        standardItem->setData(
            this->currentColor,
            Qt::UserRole
            );

        this->colorListModel.appendRow(standardItem);
    }
}

void MainWindow::updateColorTextBoxes()
{
    this->ui->RedEdit->setText(QString::number(this->currentColor.red()));
    this->ui->GreenEdit->setText(QString::number(this->currentColor.green()));
    this->ui->BlueEdit->setText(QString::number(this->currentColor.blue()));
    this->ui->HexEdit->setText(this->currentColor.name(QColor::HexRgb));
    this->updateColorPreview();
}

void MainWindow::updateCurrentcolor()
{
    bool isnumber = false;
    int blueval = this->ui->BlueEdit->text().toInt(&isnumber);
    if(isnumber)
    {
        if(blueval > 255)
        {
            blueval = 255;
            this->ui->BlueEdit->setText(QString::number(blueval));
        }
        this->currentColor.setBlue(blueval);
    }
    int Redval = this->ui->RedEdit->text().toInt(&isnumber);
    if(isnumber)
    {
        if (Redval > 255)
        {
            Redval = 255;
            this->ui->RedEdit->setText(QString::number(Redval));
        }
        this->currentColor.setRed(Redval);
    }
    int Greenval = this->ui->GreenEdit->text().toInt(&isnumber);
    if(isnumber)
    {
        if (Greenval > 255)
        {
            Greenval = 255;
            this->ui->GreenEdit->setText(QString::number(Greenval));
        }
        this->currentColor.setGreen(Greenval);
    }
    this->ui->HexEdit->setText(this->currentColor.name(QColor::HexRgb));
    this->updateColorPreview();
}

void MainWindow::updateColorPreview()
{
    QPalette pal = this->ui->ColorPreview->palette();
    pal.setColor(QPalette::Window, this->currentColor);
    this->ui->ColorPreview->setAutoFillBackground(true);
    this->ui->ColorPreview->setPalette(pal);
    this->ui->ColorPreview->show();
}

void MainWindow::UpdateRGBFromHex()
{
    if(utilities::isHexString(this->ui->HexEdit->text()))
    {
        this->currentColor = QColor(this->ui->HexEdit->text());
        this->ui->RedEdit->setText(QString::number(this->currentColor.red()));
        this->ui->GreenEdit->setText(QString::number(this->currentColor.green()));
        this->ui->BlueEdit->setText(QString::number(this->currentColor.blue()));
    }
    this->updateColorPreview();
}

void MainWindow::SlotSetup()
{
    // Connect Color Dialog Box
    connect(this->ui->ColorPickerBtn, &QPushButton::clicked, this, &MainWindow::openColorDialog);

    connect(this->ui->AddColorBtn, &QPushButton::clicked, this, &MainWindow::addColorToModel);

    connect(this->ui->RedEdit, &QLineEdit::editingFinished, this, &MainWindow::updateCurrentcolor);

    connect(this->ui->BlueEdit, &QLineEdit::editingFinished, this, &MainWindow::updateCurrentcolor);

    connect(this->ui->GreenEdit, &QLineEdit::editingFinished, this, &MainWindow::updateCurrentcolor);

    connect(this->ui->HexEdit, &QLineEdit::editingFinished, this, &MainWindow::UpdateRGBFromHex);

    connect(this->ui->CalcBtn, &QPushButton::clicked, this, &MainWindow::CalculateADA);
}

MainWindow::~MainWindow()
{
    delete this->ui;

    if (nullptr != this->adaWindow)
        delete this->adaWindow;
}
