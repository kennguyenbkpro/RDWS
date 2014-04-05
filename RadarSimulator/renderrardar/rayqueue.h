#ifndef RAYQUEUE_H
#define RAYQUEUE_H
#include <QQueue>
#include <renderrardar/ray.h>
#include <QMutex>
#include <QWaitCondition>

class RayQueue
{
public:
    static RayQueue * instance();
    void enqueue(Ray * ray);
    Ray * dequeue();
    bool isEmpty();
    void wakeAll();
    ~RayQueue();
private:
    RayQueue();
    QQueue<Ray*> mRayQueue;
    static RayQueue* mInstance;
    QMutex mMutex;
    QWaitCondition emptyCondition;
};

#endif // RAYQUEUE_H
