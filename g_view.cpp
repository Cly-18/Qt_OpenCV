#include "g_view.h"

G_View::G_View(QWidget* parent)
{
    scaleNum=1.0;
}

void G_View::fillSize()
{
    auto s=this->scene();
    if(s==nullptr)
        return;
    double w=static_cast<double>(width())/s->width();
    double h=static_cast<double>(height())/s->height();
    if(w<h)
    {
        scale(w/scaleNum,w/scaleNum);
        scaleNum=w;
    }
    else
    {
        scale(h/scaleNum,h/scaleNum);
        scaleNum=h;
    }
    barShow(false);
}

void G_View::barShow(bool t)
{
    if(t)
    {
        setDragMode(DragMode::ScrollHandDrag);
        this->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        this->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    }
    else
    {
        setDragMode(DragMode::NoDrag);
        this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    }
}


void G_View::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton
        && this->scene())
    {
        auto s=this->scene();
        double w=static_cast<double>(width())/s->width();
        double h=static_cast<double>(height())/s->height();
        if(scaleNum<=w&&scaleNum<=h)
        {
            scale(1/scaleNum,1/scaleNum);
            scaleNum=1.0;

            barShow(true);
        }
        else
        {
            fillSize();
        }
    }
}

void G_View::wheelEvent(QWheelEvent *event)
{
    if(event->angleDelta().y()>0)
    {
        if(scaleNum<10)
        {
            scale(1.1,1.1);
            scaleNum*=1.1;
        }
        if(scene()->height()*scaleNum>height()
            ||scene()->width()*scaleNum>width())
        {
            barShow(true);
        }
    }
    else
    {
        if(scaleNum>0.1
            ||scene()->height()*scaleNum>height()
            ||scene()->width()*scaleNum>width())
        {
            scale(0.9,0.9);
            scaleNum*=0.9;
        }
        else
        {
            barShow(false);
        }
    }
}
