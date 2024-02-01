#include "histogram.h"
#include "ui_histogram.h"

Histogram::Histogram(QString title,cv::Mat* input,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Histogram)
{
    ui->setupUi(this);
    this->setWindowTitle(title);
    this->setAttribute(Qt::WA_DeleteOnClose);

    img=input;
    showImg();
}

Histogram::~Histogram()
{
    delete img;
    delete ui;
}


void Histogram::showImg()
{
    int zoom=1;
    double maxVal = 0;
    double minVal = 0;
    cv::minMaxLoc(*img, &minVal, &maxVal, 0, 0);
    int histSize = img->rows;
    cv::Mat histImg(histSize*zoom, histSize*zoom,
                    CV_8U, cv::Scalar(255));
    int hpt = static_cast<int>(0.9*histSize);
    for (int h = 0; h < histSize; h++) {
        float binVal = img->at<float>(h);
        if (binVal>0) {
            int intensity = static_cast<int>(binVal*hpt / maxVal);
            cv::line(histImg, cv::Point(h*zoom, histSize*zoom),
                     cv::Point(h*zoom, (histSize - intensity)*zoom),
                     cv::Scalar(0), zoom);
        }
    }

    QImage qimg(
        histImg.data,
        histImg.rows,histImg.cols,
        histImg.step,
        QImage::Format_Indexed8);

    QGraphicsScene* scene;
    if(ui->page_gw->scene())
        scene=ui->page_gw->scene();
    else
        scene=new QGraphicsScene;

    scene->clear();
    scene->setSceneRect(qimg.rect());
    scene->addPixmap(QPixmap::fromImage(qimg));
    ui->page_gw->setScene(scene);
    ui->page_gw->show();
}




