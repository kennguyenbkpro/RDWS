#include "mywidget.h"
#include <QPainter>
#include "QDebug"
MyWidget::MyWidget()
{
    QgsRectangle extendRect(101, 11, 111, 21);
    DMapLayerManager::instance()->setExportInfo(extendRect, QSize(500, 800));

}

void MyWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    QImage &img = DMapLayerManager::instance()->getImage();

    painter.drawImage(0, 0, img);


}

void MyWidget::mouseMoveEvent(QMouseEvent *e)
{


}

void MyWidget::mousePressEvent(QMouseEvent *e)
{
    int x = e->pos().x();
    int y = e->pos().y();


    qDebug() << "in:" << x << y;

    QgsMapRenderer &mapRender = DMapLayerManager::instance()->getMapRender();

    QgsPoint point00 = mapRender.coordinateTransform()->toMapCoordinates(0, 0);
    qDebug() << "out00:"<< point00.toString();

    QgsPoint point = mapRender.coordinateTransform()->toMapCoordinates(x, y);
    qDebug() << "out1:"<< point.toString();
    double x1, y1;
    x1 = point.x();
    y1 = point.y();
    mapRender.coordinateTransform()->transformInPlace(x1, y1);
    qDebug() << "out2:" << x1 << " " << y1;
//               << mapRender.coordinateTransform()->toMapPoint(point.x(), point.y()).toString();    << mapRender.coordinateTransform()->transformInPlace(point.x(), point.y())


}






