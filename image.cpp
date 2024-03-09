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

void Image::imgsave(std::string path)
{
    cv::imwrite(path+"/output.jpg",out);
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

void Image::imgfilter(cv::Mat kernel)
{
    if(kernel.empty())
        return;
    cv::Mat target=getTarget();
    cv::Mat result;
    cv::filter2D(target,result,target.depth(),kernel);
    result.copyTo(out);

}

void Image::wave(float x,float y)
{
    cv::Mat target=getTarget();
    cv::Mat px(target.size(),CV_32F);
    cv::Mat py(target.size(),CV_32F);

    for(int i=0;i<target.rows;i++)
    {
        for(int j=0;j<target.cols;j++)
        {
            px.at<float>(i,j)=j;
            py.at<float>(i,j)=i+x*sin(j/y);
        }
    }
    cv::remap(target,out,px,py,cv::INTER_LINEAR);
}


void Image::thresh(cv::Vec3i color,int distance)
{
    if(distance<0)
        distance=0;
    else if(distance>255)
        distance=255;
    cv::absdiff(getTarget(),cv::Scalar(color),out);
    std::vector<cv::Mat> outs;
    cv::split(out,outs);
    if(outs.size()>1)
        out=outs[0]+outs[1]+outs[2];
    else
        out=outs[0];
    cv::threshold(out,out,distance,255,cv::THRESH_BINARY);
}


void Image::fill(cv::Point p,cv::Vec3i color)
{
    cv::Mat temp=getTarget().clone();
    cv::floodFill(
        temp,
        p,
        cv::Scalar(color),
        (cv::Rect*)0,
        cv::Scalar(35,35,35),
        cv::Scalar(35,35,35),
        cv::FLOODFILL_FIXED_RANGE);
    temp.copyTo(out);
}

void Image::cut(cv::Rect rect)
{
    cv::Mat input=getTarget();
    cv::Mat result;
    cv::Mat bgM,fgM;
    cv::grabCut(
        input,
        result,
        rect,
        bgM,fgM,
        5,
        cv::GC_INIT_WITH_RECT);
    cv::compare(result,cv::GC_PR_FGD,result,cv::CMP_EQ);
    cv::Mat foreground(input.size(),CV_8UC3,cv::Scalar(255,255,255));
    input.copyTo(foreground, result);
    foreground.copyTo(out);
}

void Image::skinColor()
{
    //160 10 25 166
    cv::Mat hsv;
    cv::cvtColor(getTarget(),hsv,cv::COLOR_BGR2HSV);
    std::vector<cv::Mat> channels;
    cv::split(hsv,channels);
    cv::Mat mask1;
    cv::threshold(channels[0],mask1,10,255,cv::THRESH_BINARY_INV);
    cv::Mat mask2;
    cv::threshold(channels[0],mask2,160,255,cv::THRESH_BINARY);
    cv::Mat hueMask;
    hueMask = mask1 | mask2;
    cv::Mat satMask;
    cv::inRange(channels[1], 25, 166, satMask);
    cv::Mat mask = hueMask & satMask;
    cv::Mat detected(getTarget().size(), CV_8UC3, cv::Scalar(0, 0, 0));
    getTarget().copyTo(detected,mask);
    detected.copyTo(out);
}

const cv::Mat* Image::getHistogram(int c)
{
    auto target=getTarget();

    if(target.channels()<=c)
        return nullptr;

    float hranges[2]={0.0,256.0};
    int histSize[]={256};
    const float* ranges[1]={hranges};
    int channels[]={c};

    cv::Mat* ret=new cv::Mat;
    cv::calcHist(
        &target,
        1,
        channels,
        cv::Mat(),
        *ret,
        1,
        histSize,
        ranges);

    return ret;
}
