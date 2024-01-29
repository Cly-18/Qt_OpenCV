#ifndef G_VIEW_H
#define G_VIEW_H

#include <QGraphicsView>
#include <QWidget>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QGraphicsRectItem>
#include <iostream>


class G_View : public QGraphicsView
{
    Q_OBJECT
public:
    G_View(QWidget*parent = nullptr);
    ~G_View();
    void fillSize();
    const QPoint getBegin() const;
    const QRect getRect() const;
    void setDrawRect(bool newDrawRect);

Q_SIGNALS:
    void setPoint(int x,int y);

protected:

    void mouseDoubleClickEvent(QMouseEvent *event) override;

    void wheelEvent(QWheelEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;
private:
    double scaleNum;
    QPoint begin;
    QPoint end;
    bool move;
    bool drawRect;
    QGraphicsRectItem* rect;
    void barShow(bool);
};

#endif // G_VIEW_H
