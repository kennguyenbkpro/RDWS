#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QBrush>
#include <QPen>
#include <QPixmap>
#include <QWidget>
#include <renderrardar/flightpoint.h>

class RenderArea : public QWidget
{
    Q_OBJECT
public:
    explicit RenderArea(QWidget *parent = 0);
    QSize minimumSizeHint() const;
    QSize sizeHint() const;


protected:
    void paintEvent(QPaintEvent *event);

private :
    QList<FlightPoint*> listFlightPoints;
    void printlog(QString str);
    FlightPoint* generatePoint(int top, int left, int w, int h);

signals:

public slots:
    void drawNextPoint();
    void clearPoint();
};

#endif // RENDERAREA_H
