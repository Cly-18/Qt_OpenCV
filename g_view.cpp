#include "g_view.h"

G_View::G_View(QWidget* parent)
{
    scaleNum=1.0;
    begin={0,0};
    move=false;
    rect=nullptr;
    drawRect=false;

}
G_View::~G_View()
{
    delete rect;
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

const QPoint G_View::getBegin() const
{
    return begin;
}
const QRect G_View::getRect() const
{
    return QRect(begin,end);
}
void G_View::setDrawRect(bool newDrawRect)
{
    drawRect = newDrawRect;
    if(!newDrawRect)
    {
        scene()->removeItem(rect);
        delete rect;
        rect=nullptr;
    }
}


void G_View::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton
        && this->scene())
    {
        QPoint temp=mapToScene(event->pos()).toPoint();
        double x=temp.x();
        double y=temp.y();
        if(!x)
            x=x/scaleNum;
        if(!y)
            y=y/scaleNum;

        if(x>=0&&y>=0
            && x<=scene()->width()&&y<=scene()->height())
        {
            emit setPoint(x,y);
            begin.setX(x);
            begin.setY(y);
            move=true;
        }
    }
    QGraphicsView::mousePressEvent(event);
}

void G_View::mouseMoveEvent(QMouseEvent *event)
{
    if(move&& drawRect)
    {
        QPoint temp=mapToScene(event->pos()).toPoint();
        double x=temp.x();
        double y=temp.y();
        if(!x)
            x=x/scaleNum;
        if(!y)
            y=y/scaleNum;

        if(x<0)
            x=0;
        else if(x>scene()->width())
            x=scene()->width();

        if(y<0)
            y=0;
        else if(y>scene()->height())
            y=scene()->height();

        if(rect)
        {
            rect->setRect(begin.x(),begin.y(),x-begin.x(),y-begin.y());
        }
        else
        {
            rect=new QGraphicsRectItem(begin.x(),begin.y(),x-begin.x(),y-begin.y());
            rect->setPen({Qt::black,2});
            scene()->addItem(rect);
        }
        end.setX(x);
        end.setY(y);
    }
    else
    {
        QGraphicsView::mouseMoveEvent(event);
    }

}
void G_View::mouseReleaseEvent(QMouseEvent *event)
{
    if(!move)
        return;
    move=false;
    QGraphicsView::mouseReleaseEvent(event);
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
            resetTransform();
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
