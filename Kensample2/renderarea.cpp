#include "renderarea.h"
#include <flightpoint.h>
#include <QtGui>
#include <QDebug>
#include <QTime>


RenderArea::RenderArea(QWidget *parent) :
    QWidget(parent)
{
//    printlog("Constructor!");
}
void RenderArea::paintEvent(QPaintEvent *){
    QBrush qbrush;
    qbrush.setTexture(QPixmap(":/images/brick.png"));
    QPen qpenPoint, qpenLine;
    qpenPoint.setWidth(5);
    qpenLine.setWidth(2);

    QPainter painter(this);
    painter.setBrush(qbrush);
    painter.setRenderHint(QPainter::Antialiasing, true);

    int n = listFlightPoints.count();
    for (int i = 0; i < n; i ++){
        FlightPoint* flightPoint = listFlightPoints.at(i);
        painter.setPen(qpenPoint);
        painter.drawPoint(*flightPoint->getPoint());
        if (i > 0){
            FlightPoint* prevPoint = listFlightPoints.at(i - 1);
            painter.setPen(qpenLine);
            painter.drawLine(*prevPoint->getPoint(), *flightPoint->getPoint());
        }
    }
//    painter.drawLine(QPoint(0,0), QPoint(100,100+qrand()%100));

//    printlog("Paint!");

}
QSize RenderArea::minimumSizeHint() const
{
    return QSize(200, 200);
}
QSize RenderArea::sizeHint() const
{
    return QSize(400, 400);
}

void RenderArea::drawNextPoint() {
    FlightPoint* flightPoint = generatePoint(0, 0, 400, 400);
    listFlightPoints.append(flightPoint);
//    printlog("Generate" + QString::number(flightPoint->getPoint()->x()));
    update();
}

void RenderArea::clearPoint(){
    listFlightPoints.clear();
    update();
}

FlightPoint* RenderArea::generatePoint(int top, int left, int w, int h)
{
    int x = qrand() % w + left;
    int y = qrand() % h + top;
    FlightPoint* flightPoint = new FlightPoint();
    flightPoint->setXY(x, y);
    return flightPoint;
}

void RenderArea::printlog(QString str){
    qDebug() << str;
}
