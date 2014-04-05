#include "flightpoint.h"

FlightPoint::FlightPoint(QObject *parent) :
    QObject(parent)
{

}


void FlightPoint::setXY(float x, float y){
    this->x = x;
    this->y = y;
}

QPoint* FlightPoint::getPoint(){
    return new QPoint(x,y);
}
