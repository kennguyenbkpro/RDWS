#ifndef FLIGHTPOINT_H
#define FLIGHTPOINT_H

#include <QObject>
#include <QtGui>

class FlightPoint : public QObject
{
    Q_OBJECT
public:
    explicit FlightPoint(QObject *parent = 0);
    void setXY(float x, float y);
    QPoint* getPoint();

private:
    float x, y;

signals:

public slots:

};

#endif // FLIGHTPOINT_H
