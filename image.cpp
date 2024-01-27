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

void Image::reset()
{
    img.copyTo(out);
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

void Image::sharpen()
{
    cv::Mat target=getTarget();
    cv::Mat result;
    result.create(target.size(),target.type());

    int nchannels= target.channels();
    // 处理所有行（除了第一行和最后一行）
    for (int j= 1; j<target.rows-1; j++) {
        const uchar* previous= target.ptr<const uchar>(j-1);
        const uchar* current= target.ptr<const uchar>(j);
        const uchar* next= target.ptr<const uchar>(j+1);
        uchar* output= result.ptr<uchar>(j);
        for (int i=nchannels; i<(target.cols-1)*nchannels; i++)
        {
            *output++= cv::saturate_cast<uchar>(
                5*current[i]-current[i-nchannels]-
                current[i+nchannels]-previous[i]-next[i]);
        }
    }

    result.copyTo(out);
}

