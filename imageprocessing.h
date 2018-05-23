#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <qdebug.h>
#include <QImage>

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

class ImageProcessing
{
public:
    explicit ImageProcessing();

    QSize GetLayerOfPyramid(QImage inputImage, QImage &outputImage, int layer);

private:
    QImage GetQImageFromMat(cv::Mat imageMat);
    cv::Mat GetMatFromQImage(QImage qImage);
};

#endif // IMAGEPROCESSING_H
