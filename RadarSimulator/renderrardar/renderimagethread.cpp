#include "renderimagethread.h"
#include <QThread>
#include <math.h>
#include <QDebug>
#include <QQueue>
#include <renderrardar/rayqueue.h>

//extern QQueue<Ray*> queueRay;
extern bool rendered;

const int realRaySize = 3000;
const int realDistance = 360;
const int imageSize = 800;

RenderImageThread::RenderImageThread(QObject *parent) : QThread(parent)
{

    restart = false;
    abort = false;
    rendered = false;
}

RenderImageThread::~RenderImageThread(){
    qmutex.lock();
    abort = true;
    condition.wakeOne();
    qmutex.unlock();
    RayQueue::instance()->wakeAll();
    wait();
}

void RenderImageThread::render(){
    if (!isRunning()){
        start(LowPriority);
    } else {
        restart = true;
        condition.wakeOne();
    }
}

void RenderImageThread::renderable() {
    rendered = true;
}

void RenderImageThread::run(){
    QImage bufferImage(imageSize,imageSize, QImage::Format_ARGB32);
    bufferImage.fill(0x00ffffff);
    int count = 0;
    forever {
        QImage pointImage(imageSize,imageSize, QImage::Format_ARGB32);
        pointImage.fill(0x00ffffff);
        QPainter painter;
        painter.begin(&pointImage);
//        painter.setCompositionMode(QPainter::CompositionMode_Source);
//        painter.fillRect(pointImage.rect(), Qt::transparent);
        while (true){
            if (restart){
                break;
            }
            if (abort){
                return;
            }

            Ray* ray = RayQueue::instance()->dequeue();
            if (abort){
                return;
            }
            if (ray->alpha >= 1000*360){
                delete ray;
                return;
            }
//            qDebug() << ray->alpha;
            QPen pen;
            int n = ray->size;
            int * p = convertRay(ray->p, n, imageSize/2);
            for (int i = 0; i < imageSize/2; i ++){
//                pen.setWidth(1);
//                pen.setColor(QColor(p[i], p[i], p[i], 255));
//                painter.setPen(pen);
                float sina = sin(ray->alpha * 3.1415926/180);
                float cosa = cos(ray->alpha * 3.1415926/180);
                float x = imageSize/2 + (float) i * sina;
                float y = imageSize/2 - (float) i * cosa;
//                painter.drawPoint((int) x,(int)  y);
                QRgb rgbEdit = qRgba(p[i], p[i], p[i], p[i]);
                pointImage.setPixel(x,y, rgbEdit);
            }
            delete ray;
            delete [] p;
            count ++;

            if (rendered){
                if (count > 50){
                    count = 0;
                    int w = bufferImage.width();
                    int h = bufferImage.height();
                    for (int x = 0; x < w; x ++){
                        for (int y = 0; y < h; y ++){
                            QRgb rgb = bufferImage.pixel(x, y);
                            int a = qAlpha(rgb) - 5;
                            if (a < 0) a = 0;
                            QRgb rgbEdit = qRgba(qRed(rgb), qGreen(rgb), qBlue(rgb), a);
                            bufferImage.setPixel(x,y, rgbEdit);
                        }
                    }
                }
//                qDebug() << "rendered";
                QPainter resultPainter(&bufferImage);
                resultPainter.drawImage(0, 0, pointImage);
                resultPainter.end();
                emit renderedImage(bufferImage);
                break;
            }
            msleep(2);
        }
        painter.end();
    }
}

int * RenderImageThread::convertRay(const int source[], const int sourceSize, const int destSize){
    int *p = new int[destSize];
    for (int i = 0; i < sourceSize; i ++){
        int j = i * destSize / sourceSize;
        if (source[i] > p[j]){
            p[j] = source[i];
        }
    }
    return p;
}


