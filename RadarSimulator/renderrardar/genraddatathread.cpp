#include "genraddatathread.h"
#include <config.h>
#include <QQueue>
#include <QDebug>
#include <renderrardar/rayqueue.h>

//extern QQueue<Ray*> queueRay;

GenRadDataThread::GenRadDataThread(QObject *parent) : QThread(parent)
{
    abort = false;
    alpha = 0;
}

GenRadDataThread::~GenRadDataThread(){
    qmutex.lock();
    abort = true;
    condition.wakeOne();
    qmutex.unlock();
    wait();
}

void GenRadDataThread::run(){
    forever {
        int time = QDateTime::currentMSecsSinceEpoch();
        if (abort) {
            return;
        }
//        if (queueRay.size() > 5){
//            qmutex.lock();
//            Ray* ray = queueRay.dequeue();
//            delete ray;
//            qmutex.unlock();
//        }
        int *p = new int[Config::realRaySize];
        for (int i = 0; i < Config::realRaySize; i ++){
            int a = rand()%150;
            if (a > 147) {
                a += 100;
            }
            p[i] = a;
        }
        Ray* ray = new Ray();
        ray->size = Config::realRaySize;
        ray->p = p;
        alpha += 0.1;
        ray->alpha = alpha;
//        qDebug() << "gen " + QString::number(alpha);
        RayQueue::instance()->enqueue(ray);

        time = QDateTime::currentMSecsSinceEpoch() - time;
        msleep(5);
//        qDebug() << alpha;
    }
}
