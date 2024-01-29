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
    const QPoint getClick() const;

Q_SIGNALS:
    void setPoint(int x,int y);

protected:

    void mouseDoubleClickEvent(QMouseEvent *event) override;

    void wheelEvent(QWheelEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;
private:
    double scaleNum;
    QPoint click;
    void barShow(bool);
};

#endif // G_VIEW_H
