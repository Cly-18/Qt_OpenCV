#include "image.h"

Image::Image()
{
    tag=false;
}

Image::~Image()
{

}

cv::Mat& Image::getTarget()
{
    if(tag)
        return out;
    else
        return img;
}


void Image::setTag(bool t)
{
    tag=t;
}

void Image::openImg(char* path)
{
    img=cv::imread(path);
    img.copyTo(out);
}

const cv::Mat* Image::getImg()
{
    if(!img.empty())
        return &img;
    return nullptr;
}

const cv::Mat* Image::getOut()
{
    if(!out.empty())
        return &out;
    return nullptr;
}

void Image::gray()
{
    if(getTarget().type()==CV_8UC3)
        cv::cvtColor(getTarget(),out,cv::COLOR_BGR2GRAY);
}
