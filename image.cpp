#include "image.h"

Image::Image()
{
    tag=false;
}

Image::~Image()
{

}

void Image::setTag(bool t)
{
    tag=t;
}

void Image::setImage(QString path)
{
    img=cv::imread(path.toStdString().c_str());
}

cv::Mat* Image::getIamge()
{
    if(!img.empty())
        return &img;
    return nullptr;
}
