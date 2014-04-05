#include "clockrender.h"
#include <QtGui>
#include <QTime>
#include <QDebug>

ClockRender::ClockRender(QWidget *parent) :
    QWidget(parent)
{

//    printlog("Clock render!");

}
void ClockRender::paintEvent(QPaintEvent *){
    QBrush qbrush;
//    qbrush.setTexture(QPixmap(":/images/brick.png"));
    qbrush.setColor("red");
    QPen qpenPoint, qpenLine;
    qpenPoint.setWidth(20);
    qpenLine.setWidth(2);

    QPainter painter(this);
    painter.setBrush(qbrush);
    painter.setPen(qpenLine);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.drawPie(0, 0, 400, 400, angle *16, 30);

    painter.setPen(qpenPoint);
    painter.drawPoint(QPoint(100,100));

}
QSize ClockRender::minimumSizeHint() const
{
    return QSize(200, 200);
}
QSize ClockRender::sizeHint() const
{
    return QSize(400, 400);
}

void ClockRender::renderClock(){
//    printlog("Clock run!");
    angle ++;
    update();
}


void ClockRender::printlog(QString str){
    qDebug() << str;
}
