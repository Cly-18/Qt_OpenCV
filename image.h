#ifndef IMAGE_H
#define IMAGE_H
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

class Image
{
    cv::Mat img;
    cv::Mat out;
    bool tag;
public:
    Image();
    ~Image();
    cv::Mat& getTarget();

    void setTag(bool t);
    void openImg(char* path);
    const cv::Mat* getImg();
    const cv::Mat* getOut();
    void reset();

    void gray();

    void colorReduce(int div=4);

    void sharpen();


};

#endif // IMAGE_H
