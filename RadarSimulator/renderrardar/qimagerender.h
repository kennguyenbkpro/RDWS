#ifndef QIMAGERENDER_H
#define QIMAGERENDER_H

#include <QWidget>
#include <QDebug>
#include <renderrardar/renderimagethread.h>
#include <renderrardar/myqpainter.h>
#include <math.h>
#include <qgspoint.h>
#include <renderrardar/genraddatathread.h>
#include <renderrardar/rendermapthread.h>

class QImageRender : public QWidget
{
    Q_OBJECT
public:
    explicit QImageRender(QWidget *parent = 0);
    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    ~QImageRender();

protected:
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);


private:
    void printlog(QString mes);
    int angle;
    QPixmap pixmap;
    QPixmap mapPixmap;
    RenderImageThread renderThread;
    GenRadDataThread genThread;
    RenderMapThread mapThread;

    float distanceBetween(float lat1, float lon1, float lat2, float lon2);
    QgsPoint findDestPoint(float lat1, float lon1, float distance, float bearing);
    QPoint pixmapOffset;
    QPoint lastDragPos;
    double centerX;
    double centerY;
    double pixmapScale;
    double curScale;
    void zoom(double zoomFactor);
    void scroll(int deltaX, int deltaY);
//    bool renderedMap;

signals:

public slots:
    void renderQImage(const QImage &image);
    void renderMap(const QImage &image);
};

#endif // QIMAGERENDER_H
