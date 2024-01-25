#ifndef IMAGE_H
#define IMAGE_H
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <qstring.h>

class Image
{
    cv::Mat img;
    bool tag;
public:
    Image();
    ~Image();

    void setTag(bool t);
    void setImage(QString path);
    cv::Mat* getIamge();

};

#endif // IMAGE_H
