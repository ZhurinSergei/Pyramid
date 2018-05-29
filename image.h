#ifndef IMAGE_H
#define IMAGE_H

#include <QImage>
#include <QFileInfo>
#include <QDebug>

#include <memory>

class Image
{
public:
    explicit Image(QString fileName);
    ~Image();
    static bool CompareByDiagonal(const std::shared_ptr<Image> a, const std::shared_ptr<Image> b);

    double GetLengthOfDiagonal() const;
    QString GetFileName() const;
    QImage GetImage() const;

private:
    QImage image;
    QString fileName;
    double lengthOfDiagonal;
};

#endif // IMAGE_H
