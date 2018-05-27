#include "image.h"

bool Image::SortByDiagonal(Image *a, Image *b)
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

double Image::GetLengthOfDiagonal()
{
    return lengthOfDiagonal;
}

QString Image::GetFileName()
{
    return fileName;
}

QImage Image::GetImage()
{
    return  image;
}
