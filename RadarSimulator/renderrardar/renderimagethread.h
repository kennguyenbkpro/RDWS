#ifndef RENDERTHREAD_H
#define RENDERTHREAD_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QImage>
#include <QSize>
#include <renderrardar/ray.h>

class RenderImageThread : public QThread
{
    Q_OBJECT
public:
    RenderImageThread(QObject *parent = 0);
    ~RenderImageThread();
    void render();
    void renderable() ;

signals:
    void renderedImage(const QImage &image);


protected:
    void run();

private:
    QMutex qmutex;
    QWaitCondition condition;
    bool restart;
    bool abort;
//    bool rendered;
//    Ray ray;
//    int *p;

    int * convertRay(const int source[], const int sourceSize, const int destSize);

public slots:

};

#endif // RENDERTHREAD_H
