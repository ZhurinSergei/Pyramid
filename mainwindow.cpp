#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QImage whiteImage = QImage(QSize(500, 500), QImage::Format_RGB888);
    whiteImage.fill(QColor(255, 255, 255));
    ui->label_Image->setPixmap(QPixmap::fromImage(whiteImage));
}

MainWindow::~MainWindow()
{
    delete ui;
}
