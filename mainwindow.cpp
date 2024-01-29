#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    imgOpen=false;
    lastPath="D:/Other/img";
    sence=new QGraphicsScene;
    createConnect();
    setToolEnable(false);
    flashDispaly();
}
//信号绑定
void MainWindow::createConnect()
{
    //打开文件
    connect(ui->openfile,SIGNAL(triggered()),this,SLOT(openFile()));
    //设置Tag
    connect(ui->combine,SIGNAL(toggled(bool)),this,SLOT(combineCheck(bool)));
    //reset
    connect(ui->imgreset,SIGNAL(triggered()),this,SLOT(imgreset()));
    //wave
    connect(ui->h_x,SIGNAL(valueChanged(int)),this,SLOT(imgwave()));
    connect(ui->h_y,SIGNAL(valueChanged(int)),this,SLOT(imgwave()));
    //point
    connect(ui->gView,SIGNAL(setPoint(int,int)),this,SLOT(setPoint(int,int)));
}

void MainWindow::resizeEvent(QResizeEvent* e)
{
    if(ui->gView)
        ui->gView->fillSize();
}


MainWindow::~MainWindow()
{
    delete sence;
    delete ui;
}

QImage::Format MainWindow::getType(const int type)
{
    switch (type) {
        //彩色
    case CV_8UC3:
        return QImage::Format_BGR888;
        break;
        //灰度
    case CV_8UC1:
        return QImage::Format_Indexed8;
        break;
    default:
        return QImage::Format_BGR888;
        break;
    }
}

void MainWindow::setToolEnable(bool t)
{
    ui->b_gray->setEnabled(t);
    ui->imgSlider->setEnabled(t);
    ui->in_colorReduce->setEnabled(t);
    ui->b_colorReduce->setEnabled(t);
    ui->b_sharpen->setEnabled(t);
    ui->h_x->setEnabled(t);
    ui->h_y->setEnabled(t);
    ui->in_thresh->setEnabled(t);
    ui->b_thresh->setEnabled(t);
}

//刷新控件状态  显示图像
void MainWindow::flashDispaly()
{
    if(imgOpen)
    {
        const cv::Mat* cvimg=img.getOut();
        QImage qimg(
            (const unsigned char*)cvimg->data,
            cvimg->cols,
            cvimg->rows,
            cvimg->step,
            getType(cvimg->type()));
        sence->clear();
        sence->setSceneRect(qimg.rect());
        sence->addPixmap(QPixmap::fromImage(qimg));
        ui->gView->setScene(sence);
        ui->gView->show();
    }
}
//打开文件
void MainWindow::openFile()
{
    QString path=QFileDialog::getOpenFileName(
        this,
        "选择文件",
        lastPath,
        "images(*jpg* *bmp *png)");

    if(!path.isEmpty())
    {
        lastPath=path;
        img.openImg(path.toLocal8Bit().data());
        imgOpen=true;
        ui->gView->resetTransform();
        flashDispaly();
    }
    setToolEnable(true);
}
//设置tag
void MainWindow::combineCheck(bool checked)
{
    img.setTag(checked);
}
//重置输出
void MainWindow::imgreset()
{
    img.reset();
    flashDispaly();
}

//灰度按钮事件
void MainWindow::on_b_gray_clicked()
{
    img.gray();
    flashDispaly();
}
//减色按钮事件
void MainWindow::on_b_colorReduce_clicked()
{
    img.colorReduce(ui->in_colorReduce->value());
    flashDispaly();
}

//锐化
void MainWindow::on_b_sharpen_clicked()
{
    cv::Mat kernel(3,3,CV_32F,cv::Scalar(0));
    kernel.at<float>(1,1)=5;
    kernel.at<float>(0,1)=-1;
    kernel.at<float>(1,0)=-1;
    kernel.at<float>(1,2)=-1;
    kernel.at<float>(2,1)=-1;

    img.imgfilter(kernel);
    flashDispaly();
}
//扭曲
void MainWindow::imgwave()
{
    if(!ui->h_x->value())
        return;
    img.wave(ui->h_x->value()/10.0,ui->h_y->value()/10.0);
    flashDispaly();
}

//阈值化
void MainWindow::on_b_thresh_clicked()
{
    QColor color= QColorDialog::getColor("选择颜色");
    if(!color.isValid())
        return;
    int r,g,b;
    color.getRgb(&r,&g,&b);
    img.thresh({b,g,r},ui->in_thresh->value());
    flashDispaly();
}

void MainWindow::setPoint(int x,int y)
{
    QString str("位置:(%1,%2)");
    ui->l_point->setText(str.arg(x,0).arg(y,0));
}

//区域提取
void MainWindow::on_b_fill_clicked()
{
    QColor color= QColorDialog::getColor("选择填充颜色");
    if(!color.isValid())
        return;
    int r,g,b;
    color.getRgb(&r,&g,&b);
    int x,y;
    x=ui->gView->getClick().x();
    y=ui->gView->getClick().y();
    img.fill({x,y},{b,g,r});
    flashDispaly();
}

