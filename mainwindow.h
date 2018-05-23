#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

#include "imageprocessing.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QImage image;
    ImageProcessing *imageProcessing;

    void InitializeForm();

private slots:
    void slotOpenFile();
    void on_spinBox_Layer_valueChanged(int valueSpinBox);
};

#endif // MAINWINDOW_H
