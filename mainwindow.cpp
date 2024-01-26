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
    flashDispaly();
}
//信号绑定
void MainWindow::createConnect()
{
    //打开文件
    connect(ui->openfile,SIGNAL(triggered()),this,SLOT(openFile()));
    //设置Tag
    connect(ui->combine,SIGNAL(toggled(bool)),this,SLOT(combineCheck(bool)));
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
        sence->addPixmap(QPixmap::fromImage(qimg));
        ui->gView->setScene(sence);
        ui->gView->show();
    }

    ui->b_gray->setEnabled(imgOpen);
    ui->imgSlider->setEnabled(imgOpen);

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
        flashDispaly();
    }
}
//设置tag
void MainWindow::combineCheck(bool checked)
{
    img.setTag(checked);
}
//灰度按钮事件
void MainWindow::on_b_gray_clicked()
{
    img.gray();
    flashDispaly();
}



