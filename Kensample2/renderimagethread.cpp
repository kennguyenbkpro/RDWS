#include "renderimagethread.h"
#include <QThread>
#include <math.h>
#include <QDebug>

extern bool rendered;

const int n = 1000;
const int imageSize = 800;

RenderImageThread::RenderImageThread(QObject *parent) : QThread(parent)
{
    p = new int[n];
    for (int i = 0; i < n; i ++){
        p[i] = rand()%20;
    }
    ray = Ray(0, p);
    restart = false;
    abort = false;
    rendered = false;
}

RenderImageThread::~RenderImageThread(){
    qmutex.lock();
    abort = true;
    condition.wakeOne();
    qmutex.unlock();
    wait();
    delete p;
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
    forever {
        QImage pointImage(imageSize,imageSize, QImage::Format_ARGB32);
        pointImage.fill(0x00ffffff);
        QPainter painter;
        painter.begin(&pointImage);
//        painter.setCompositionMode(QPainter::CompositionMode_Source);
//        painter.fillRect(pointImage.rect(), Qt::transparent);
        int count = 0;
        while (true){
            if (ray.alpha >= 1000*360){
                return;
            }
            if (restart){
                break;
            }
            if (abort){
                return;
            }

            QPen pen;
            for (int i = 0; i < n; i ++){
//                int p = ray.p[i];
                int a = rand()%256;
                pen.setWidth(1);
                pen.setColor(QColor(a,a,a,a));
                painter.setPen(pen);
                float sina = sin(ray.alpha * 3.14/180);
                float cosa = cos(ray.alpha * 3.14/180);
                float x = imageSize/2 + ((float) i/ (float) n) * imageSize/2 * sina;
                float y = imageSize/2 - ((float) i/ (float) n) * imageSize/2 * cosa;
                painter.drawPoint((int) x,(int)  y);
            }
            count ++;
            if (rendered){
                int w = bufferImage.width();
                int h = bufferImage.height();
                for (int x = 0; x < w; x ++){
                    for (int y = 0; y < h; y ++){
                        QRgb rgb = bufferImage.pixel(x, y);
                        int a = qAlpha(rgb) - (int) count/4 - 1;
                        if (a < 0) a = 0;
                        QRgb rgbEdit = qRgba(qRed(rgb), qGreen(rgb), qBlue(rgb), a);
                        bufferImage.setPixel(x,y, rgbEdit);
                    }
                }
                qDebug() << "a " + QString::number(count);


//                QImage resultImage = QImage(imageSize, imageSize, QImage::Format_ARGB32_Premultiplied);
                QPainter resultPainter(&bufferImage);
//                resultPainter.setCompositionMode(QPainter::CompositionMode_Source);
//                resultPainter.fillRect(resultImage.rect(), Qt::transparent);
//                resultPainter.setCompositionMode(QPainter::CompositionMode_SourceOver);
//                resultPainter.drawImage(0,0,alphaImage);
//                resultPainter.setCompositionMode(QPainter::CompositionMode_SourceIn);
//                resultPainter.drawImage(0, 0, bufferImage);
//                resultPainter.setCompositionMode(QPainter::CompositionMode_SourceOver);
                resultPainter.drawImage(0, 0, pointImage);
//                resultPainter.end();

                emit renderedImage(bufferImage);
                rendered = false;
//                bufferImage = resultImage;
                break;
            }
            ray.alpha = ray.alpha + 0.3;

            msleep(10);
        }
//        break;
    }
}


