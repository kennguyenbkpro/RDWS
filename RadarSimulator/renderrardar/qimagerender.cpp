#include "qimagerender.h"
#include <QtGui>
#include <dmaplayermanager.h>
#include <QDebug>
#include <renderrardar/rayqueue.h>

extern bool rendered;

const double DefaultCenterX = -0.637011f;
const double DefaultCenterY = -0.0395159f;
const double DefaultScale = 0.00403897f;

const double ZoomInFactor = 0.8f;
const double ZoomOutFactor = 1 / ZoomInFactor;
const int ScrollStep = 20;
const float defaultCenLon = 105;
const float defaultCenLat = 21;
const float defaultMaxDistance = 500; //km
const float defaultMaxSize = 800; //pixel

QImageRender::QImageRender(QWidget *parent) :
    QWidget(parent)
{
#ifndef QT_NO_CURSOR
    setCursor(Qt::CrossCursor);
#endif

    curScale = 1;
    centerX = 0;
    centerY = 0;
    pixmapOffset = QPoint();
    lastDragPos = QPoint();

    float maxLat = findDestPoint(defaultCenLat, defaultCenLon,defaultMaxDistance/2,0).x();
    float minLat = findDestPoint(defaultCenLat, defaultCenLon,defaultMaxDistance/2,180).x();
    float maxLon = findDestPoint(defaultCenLat, defaultCenLon,defaultMaxDistance/2,90).y();
    float minLon = findDestPoint(defaultCenLat, defaultCenLon,defaultMaxDistance/2,270).y();

    rendered = true;

    QgsRectangle extendRect(minLon, minLat, maxLon, maxLat);
//    DMapLayerManager::instance()->setExportInfo(extendRect, QSize(defaultMaxSize, defaultMaxSize));

    connect(&mapThread, SIGNAL(updateMapToUI(const QImage)), this, SLOT(renderMap(const QImage)));
    mapThread.renderMap(extendRect, QSize(defaultMaxSize, defaultMaxSize));
    genThread.start();
    connect(&renderThread, SIGNAL(renderedImage(const QImage)), this, SLOT(renderQImage(const QImage)));
    renderThread.start();
//    genThread.wait();
//    renderThread.wait();

    qDebug() << distanceBetween(defaultCenLat,defaultCenLon,21,120);
    qDebug() << maxLat;
    qDebug() << maxLon;
    qDebug() << minLat;
    qDebug() << minLon;
}


void QImageRender::paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.fillRect(0,0,800,800, Qt::black);
//    painter.drawImage(QPoint(0, 0), DMapLayerManager::instance()->getImage());

//    if (curScale == pixmapScale) {

    painter.drawPixmap(0,0,mapPixmap);
//    QPoint p = DMapLayerManager::instance()->longLat2XY(defaultCenLon,defaultCenLat);
    painter.drawPixmap(200, 200,800, 800,pixmap,0, 0,800,800);
//    } else {
//        double scaleFactor = pixmapScale / curScale;
//        int newWidth = int(pixmap.width() * scaleFactor);
//        int newHeight = int(pixmap.height() * scaleFactor);
//        int newX = pixmapOffset.x() + (pixmap.width() - newWidth) / 2;
//        int newY = pixmapOffset.y() + (pixmap.height() - newHeight) / 2;

//        painter.save();
//        painter.translate(newX, newY);
//        painter.scale(scaleFactor, scaleFactor);
//        painter.drawPixmap(0, 0, QPixmap::fromImage(DMapLayerManager::instance()->getImage()));

//        QPoint p = DMapLayerManager::instance()->longLat2XY(defaultCenLon,defaultCenLat);
//        painter.drawPixmap(p.x()-200, p.y()-200,800, 800,pixmap,0, 0,800,800);
//        painter.restore();
//    }



    QPen qPenLine;
    qPenLine.setColor("red");
    qPenLine.setWidth(10);
    painter.setPen(qPenLine);

//    painter.drawPoint(DMapLayerManager::instance()->longLat2XY(105,21));
//    painter.drawPoint(DMapLayerManager::instance()->longLat2XY(107.9,21));
}

void QImageRender::renderQImage(const QImage &image){
    rendered = false;
    pixmap = QPixmap::fromImage(image);
//    pixmapScale = scaleFactor;
    update();
    rendered = true;
}

void QImageRender::renderMap(const QImage &image)
{
    mapPixmap = QPixmap::fromImage(image);
    update();
    qDebug() << "render map";
}

QSize QImageRender::minimumSizeHint() const{
    return QSize(800,800);
}
QSize QImageRender::sizeHint() const{
    return QSize(800, 800);
}

void QImageRender::printlog(QString mes){
    qDebug() << mes;
}
QImageRender::~QImageRender(){
}

void QImageRender::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Plus:
        zoom(ZoomInFactor);
        qDebug() << "+";
        break;
    case Qt::Key_Minus:
        zoom(ZoomOutFactor);
        qDebug() << "-";
        break;
    case Qt::Key_Left:
        scroll(-ScrollStep, 0);
        break;
    case Qt::Key_Right:
        scroll(+ScrollStep, 0);
        break;
    case Qt::Key_Down:
        scroll(0, -ScrollStep);
        break;
    case Qt::Key_Up:
        scroll(0, +ScrollStep);
        break;
    default:
        QWidget::keyPressEvent(event);
    }
}

void QImageRender::wheelEvent(QWheelEvent *event)
{
    int numDegrees = event->delta() / 8;
    double numSteps = numDegrees / 15.0f;
    zoom(pow(ZoomInFactor, numSteps));
}

void QImageRender::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        lastDragPos = event->pos();
}


void QImageRender::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        pixmapOffset += event->pos() - lastDragPos;
        lastDragPos = event->pos();
//        update();
    }
}

void QImageRender::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        pixmapOffset += event->pos() - lastDragPos;
        lastDragPos = QPoint();

        int deltaX =  - pixmapOffset.x();
        int deltaY =  - pixmapOffset.y();
        qDebug() << width();
        scroll(deltaX, deltaY);
        pixmapOffset = QPoint();
    }
}

void QImageRender::zoom(double zoomFactor)
{
    curScale *= zoomFactor;
    if (curScale > 10){
        curScale = 10;
    } else if (curScale < 0.1){
        curScale = 0.1;
    } else {

        float currentDistance = defaultMaxDistance * curScale;

        float maxLat = findDestPoint(defaultCenLat, defaultCenLon,currentDistance/2,0).x();
        float minLat = findDestPoint(defaultCenLat, defaultCenLon,currentDistance/2,180).x();
        float maxLon = findDestPoint(defaultCenLat, defaultCenLon,currentDistance/2,90).y();
        float minLon = findDestPoint(defaultCenLat, defaultCenLon,currentDistance/2,270).y();

        QgsRectangle extendRect(minLon, minLat, maxLon, maxLat);
        mapThread.renderMap(extendRect, QSize(defaultMaxSize, defaultMaxSize));
    }

}

void QImageRender::scroll(int deltaX, int deltaY)
{
    float currentDistance = defaultMaxDistance * curScale;
    float ratio = currentDistance / defaultMaxSize;
    centerX += deltaX * ratio;
    centerY += deltaY * ratio;

    //Tinh toan toa do center tu centerX va centerY
    float maxLat = findDestPoint(defaultCenLat, defaultCenLon,currentDistance/2 - centerY,0).x();
    float minLat = findDestPoint(defaultCenLat, defaultCenLon,currentDistance/2 + centerY,180).x();
    float maxLon = findDestPoint(defaultCenLat, defaultCenLon,currentDistance/2 + centerX,90).y();
    float minLon = findDestPoint(defaultCenLat, defaultCenLon,currentDistance/2 - centerX,270).y();

    QgsRectangle extendRect(minLon, minLat, maxLon, maxLat);
    mapThread.renderMap(extendRect, QSize(defaultMaxSize, defaultMaxSize));
}

float QImageRender::distanceBetween(float lat1, float lon1, float lat2, float lon2){
    float R = 6371.0;
    float Pi = 3.1415926;
    float dLat = (lat2 - lat1)*Pi/180.0;
    float dLon = (lon2 - lon1)*Pi/180.0;
    lat1 = lat1*Pi/180.0;
    lat2 = lat2*Pi/180.0;
    float a = sin(dLat/2) * sin(dLat/2) + sin(dLon/2) * sin(dLon/2) * cos(lat1) * cos(lat2);
    float c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return R * c;
}

QgsPoint QImageRender::findDestPoint(float lat1, float lon1, float distance, float bearing){
    float R = 6371.0;
    float Pi = 3.1415926;
    lat1 = lat1*Pi/180.0;
    lon1 = lon1*Pi/180.0;
    bearing = bearing*Pi/180.0;

    float lat2 = asin( sin(lat1) * cos(distance/R) + cos (lat1) * sin(distance/R) * cos(bearing));
    float lon2 = lon1 + atan2(sin(bearing) * sin( distance/R) * cos(lat1), cos(distance/R) - sin(lat1) * sin(lat2));
    return QgsPoint(lat2 * 180/Pi, lon2 * 180/Pi);
}

