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
    vectorImages.clear();
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

    vectorImages.push_back(new Image(fileName));
    SetNewCurrentImage(vectorImages.back()->GetImage());

    std::sort(vectorImages.begin(), vectorImages.end(), Image::SortByDiagonal);
    UpdateComboBox();
}

void MainWindow::InitializeForm()
{
    QImage whiteImage = QImage(QSize(500, 500), QImage::Format_RGB888);
    whiteImage.fill(QColor(255, 255, 255));
    ui->label_Image->setPixmap(QPixmap::fromImage(whiteImage));
}

void MainWindow::on_spinBox_Layer_valueChanged(int valueSpinBox)
{
    QImage imageLayer;
    QSize size = imageProcessing->GetLayerOfPyramid(currentQImage,
                 imageLayer, valueSpinBox, 2);

    ui->label_Image->setPixmap(QPixmap::fromImage(imageLayer));
    ui->label_Size->setText(QString("Size: %1x%2").arg(size.width()).arg(size.height()));
}

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    auto itr = std::find_if(vectorImages.begin(), vectorImages.end(),
                            [&](Image* el){ return el->GetFileName() == arg1; });
    if(itr != vectorImages.end())
        SetNewCurrentImage((*itr)->GetImage());
}

void MainWindow::UpdateComboBox()
{
    ui->comboBox->clear();
    for(int i = 0; i < vectorImages.size(); i++)
        ui->comboBox->addItem(vectorImages.at(i)->GetFileName());
}

void MainWindow::UpdateSpinBox()
{
    ui->spinBox_Layer->setValue(0);
    if(currentQImage.width() < currentQImage.height())
        ui->spinBox_Layer->setMaximum(std::log10(currentQImage.width()) / std::log10(2) - 1);
    else
        ui->spinBox_Layer->setMaximum(std::log10(currentQImage.height()) / std::log10(2) - 1);
}

void MainWindow::SetNewCurrentImage(QImage image)
{
    currentQImage = image;
    ui->label_Image->setPixmap(QPixmap::fromImage(currentQImage));
    ui->label_Size->setText(QString("Size: %1x%2").arg(currentQImage.width()).arg(currentQImage.height()));
    UpdateSpinBox();
}
