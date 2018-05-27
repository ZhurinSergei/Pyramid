#ifndef IMAGE_H
#define IMAGE_H

#include <QImage>
#include <QFileInfo>

class Image
{
public:
    explicit Image(QString fileName);
    static bool SortByDiagonal(Image *a, Image *b);

    double GetLengthOfDiagonal() const;
    QString GetFileName() const;
    QImage GetImage() const;

private:
    QImage image;
    QString fileName;
    double lengthOfDiagonal;
};

#endif // IMAGE_H
