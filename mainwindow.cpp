#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    imageProcessing = new ImageProcessing();

    InitializeForm();

    connect(ui->Open_fle, SIGNAL(triggered()), this, SLOT(slotOpenFile()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotOpenFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Open Image", QDir::currentPath(), "Image Files (*.png *.jpg)");

    if(fileName.isNull())
    {
        qDebug() << "Filename is empty";
        return;
    }

    image = QImage(fileName);
    ui->label_Image->setPixmap(QPixmap::fromImage(image));
    ui->label_Size->setText(QString("Size: %1x%2").arg(image.width()).arg(image.height()));

    ui->spinBox_Layer->setValue(0);
    if(image.width() < image.height())
        ui->spinBox_Layer->setMaximum(std::log10(image.width()) / std::log10(2) - 1);
    else
        ui->spinBox_Layer->setMaximum(std::log10(image.height()) / std::log10(2) - 1);
}

void MainWindow::InitializeForm()
{
    QImage whiteImage = QImage(QSize(500, 500), QImage::Format_RGB888);
    whiteImage.fill(QColor(255, 255, 255));
    ui->label_Image->setPixmap(QPixmap::fromImage(whiteImage));
}

void MainWindow::on_spinBox_Layer_valueChanged(int valueSpinBox)
{
    if(image.isNull())
    {
        QMessageBox::warning(this, "Warning!", "You did not select a file");
        return;
    }

    QImage imageLayer;
    QSize size = imageProcessing->GetLayerOfPyramid(image, imageLayer, valueSpinBox);

    ui->label_Image->setPixmap(QPixmap::fromImage(imageLayer));
    ui->label_Size->setText(QString("Size: %1x%2").arg(size.width()).arg(size.height()));
}
