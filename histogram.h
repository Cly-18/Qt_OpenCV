#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <QWidget>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <QPixmap>


namespace Ui {
class Histogram;
}

class Histogram : public QWidget
{
    Q_OBJECT

public:
    explicit Histogram(
        QString title="",
        cv::Mat* input=nullptr,
        QWidget *parent = nullptr);
    ~Histogram();

private:
    Ui::Histogram *ui;
    cv::Mat* img;

    void showImg();
};

#endif // HISTOGRAM_H
