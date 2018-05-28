#include "imageprocessing.h"

ImageProcessing::ImageProcessing()
{

}

QSize ImageProcessing::GetLayerOfPyramid(QImage inputImage, QImage &outputImage, int layer, double coefficient)
{
    outputImage = inputImage.copy();

    if(layer == 0 || coefficient == 0)
        return QSize(outputImage.width(), outputImage.height());

    for(int i = 0; i < layer; i++)
    {
        cv::Mat mat = GetMatFromQImage(outputImage);
        cv::GaussianBlur(mat, mat, cv::Size(5, 5), 3);
        outputImage = GetQImageFromMat(mat);

        outputImage = outputImage.scaled(QSize(outputImage.width() / coefficient,
                                               outputImage.height() / coefficient));
    }

    QSize size = QSize(outputImage.width(), outputImage.height());
    outputImage = outputImage.scaled(QSize(inputImage.width(), inputImage.height()));

    return size;
}

QImage ImageProcessing::GetQImageFromMat(cv::Mat imageMat)
{
    cv::Mat temp;
    cv::cvtColor(imageMat, temp, CV_BGR2RGB);
    QImage dest((const uchar *) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
    dest.bits();

    return dest;
}

cv::Mat ImageProcessing::GetMatFromQImage(QImage qImage)
{
    qImage = qImage.convertToFormat(QImage::Format_RGB888);
    cv::Mat tmp(qImage.height(), qImage.width(), CV_8UC3, (uchar*)qImage.bits(), qImage.bytesPerLine());
    cv::Mat result;
    cv::cvtColor(tmp, result, CV_BGR2RGB);

    return result;
}
