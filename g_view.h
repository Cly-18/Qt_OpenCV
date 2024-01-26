#ifndef G_VIEW_H
#define G_VIEW_H

#include <QGraphicsView>
#include <QWidget>
#include <QMouseEvent>
#include <QWheelEvent>
#include <iostream>

class G_View : public QGraphicsView
{
    Q_OBJECT
public:
    G_View(QWidget*parent = nullptr);
    void fillSize();

protected:

    void mouseDoubleClickEvent(QMouseEvent *event) override;

    void wheelEvent(QWheelEvent *event) override;

private:
    double scaleNum;

    void barShow(bool);
};

#endif // G_VIEW_H
