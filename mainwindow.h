#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

#include "imageprocessing.h"
#include "image.h"

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
    ImageProcessing *imageProcessing;
    QImage currentQImage;
    std::vector<Image *> vectorImages;

    void SetNewCurrentImage(QImage image);
    void UpdateComboBox();
    void UpdateSpinBox(double coefficient);
    void InitializeForm();
    int GetMaximumLayer(QImage image, double coefficient);

private slots:
    void slotOpenFile();
    void on_spinBox_Layer_valueChanged(int valueSpinBox);
    void on_comboBox_currentIndexChanged(const QString &arg1);
    void on_doubleSpinBox_Coefficient_valueChanged(double arg1);
};

#endif // MAINWINDOW_H
