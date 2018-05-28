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
    delete imageProcessing;
    delete ui;
}

void MainWindow::slotOpenFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Open Image",
                                                    QDir::currentPath(),
                                                    "Image Files (*.png *.jpg)"
                                                    );
    if(fileName.isNull())
    {
        qDebug() << "Filename is empty";
        return;
    }

    vectorImages.push_back(new Image(fileName));
    SetNewCurrentImage(vectorImages.back()->GetImage());

    std::sort(vectorImages.begin(), vectorImages.end(), Image::CompareByDiagonal);
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
                                                    imageLayer,
                                                    valueSpinBox,
                                                    ui->doubleSpinBox_Coefficient->text().replace(',', '.').toDouble()
                                                    );

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

void MainWindow::UpdateSpinBox(double coefficient)
{
    if(vectorImages.empty())
        return;

    ui->spinBox_Layer->setValue(0);
    ui->spinBox_Layer->setMaximum(GetMaximumLayer(currentQImage, coefficient));
}

void MainWindow::SetNewCurrentImage(QImage image)
{
    currentQImage = image;
    ui->label_Image->setPixmap(QPixmap::fromImage(currentQImage));
    ui->label_Size->setText(QString("Size: %1x%2").arg(currentQImage.width()).arg(currentQImage.height()));
    UpdateSpinBox(ui->doubleSpinBox_Coefficient->text().replace(',', '.').toDouble());
}

void MainWindow::on_doubleSpinBox_Coefficient_valueChanged(double arg1)
{
    double minimumCoefficient = 1.1;
    if(arg1 < minimumCoefficient)
        ui->doubleSpinBox_Coefficient->setValue(minimumCoefficient);
    UpdateSpinBox(arg1);
}

int MainWindow::GetMaximumLayer(QImage image, double coefficient)
{
    int maximumLayer = 0;
    int minimumLength = image.width() < image.height() ? image.width() : image.height();

    while(minimumLength >= 2)
    {
        maximumLayer++;
        minimumLength = std::floor(minimumLength / coefficient);
    }

    return --maximumLayer;
}
