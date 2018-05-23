#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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

    ui->label_Image->setPixmap(QPixmap::fromImage(QImage(fileName)));
}

void MainWindow::InitializeForm()
{
    QImage whiteImage = QImage(QSize(500, 500), QImage::Format_RGB888);
    whiteImage.fill(QColor(255, 255, 255));
    ui->label_Image->setPixmap(QPixmap::fromImage(whiteImage));
}
