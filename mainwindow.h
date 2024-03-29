#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QColorDialog>

#include <iostream>
#include <thread>
#include <QThread>

#include "image.h"
#include "histogram.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void openFile();
    void combineCheck(bool checked);
    void imgreset();
    void imgSave();
    void imgwave();

private slots:
    void on_b_gray_clicked();

    void on_b_colorReduce_clicked();

    void on_b_sharpen_clicked();

    void on_b_thresh_clicked();

    void on_b_fill_clicked();

    void setPoint(int x,int y);

    void on_b_rect_check_clicked(bool checked);

    void on_b_cut_clicked();

    void on_b_skin_clicked();

    void on_b_showHistogram_clicked();

    void on_canny_clicked();

    void on_open_video_clicked();

    void on_play_video_clicked();

protected:

    void resizeEvent(QResizeEvent *event) override;

private:
    Ui::MainWindow *ui;
    QGraphicsScene* sence;

    Image img;
    bool imgOpen;
    QString lastPath;

    bool videoOpen;
    QString videoPath;

    QImage::Format getType(const int type);
    void setToolEnable(bool);

    void createConnect();

    void flashDispaly();

};
#endif // MAINWINDOW_H
