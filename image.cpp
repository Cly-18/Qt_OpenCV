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

void Image::colorReduce(int div)
{
    if(div<0||div>8)
        return;
    cv::Mat target=out;
    if(!tag)
    {
        img.copyTo(out);
    }

    int nl=target.rows;
    int nc=target.cols*target.channels();
    unsigned char mask=0xFF<<div;
    for(int i=0;i<nl;i++)
    {
        unsigned char * data=target.ptr<unsigned char>(i);
        for(int j=0;j<nc;j++)
        {
            *data &=mask;
            *data++ += 0x01<<(div-1);
        }
    }
}

