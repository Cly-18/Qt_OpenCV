#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QGraphicsScene>

#include <iostream>

#include "image.h"

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

private slots:
    void on_b_gray_clicked();

    void on_b_colorReduce_clicked();

protected:

    void resizeEvent(QResizeEvent *event) override;

private:
    Ui::MainWindow *ui;
    QGraphicsScene* sence;

    Image img;
    bool imgOpen;
    QString lastPath;

    QImage::Format getType(const int type);

    void createConnect();

    void flashDispaly();

};
#endif // MAINWINDOW_H
