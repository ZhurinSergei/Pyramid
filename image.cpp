#include "image.h"

Image::~Image()
{
    qDebug() << "delete Image";
}

bool Image::CompareByDiagonal(const std::shared_ptr<Image> a, const std::shared_ptr<Image> b)
{
    return (a->GetLengthOfDiagonal() < b->GetLengthOfDiagonal());
}

Image::Image(QString fileName)
    : fileName(fileName)
{
    this->image = QImage(fileName);

    QFileInfo qFileInfo(fileName);
    this->fileName = qFileInfo.fileName();

    this->lengthOfDiagonal =
            std::sqrt(image.width() * image.width() + image.height() * image.height());
}

double Image::GetLengthOfDiagonal() const
{
    return lengthOfDiagonal;
}

QString Image::GetFileName() const
{
    return fileName;
}

QImage Image::GetImage() const
{
    return image;
}
