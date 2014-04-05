#include "rayqueue.h"
#include <QDebug>
#include <QDateTime>

RayQueue * RayQueue::mInstance = NULL;
RayQueue::RayQueue()
{

}

RayQueue * RayQueue::instance(){
    if (!mInstance){
        mInstance = new RayQueue();
        qDebug() << "init";
    }
    return mInstance;
}

RayQueue::~RayQueue(){
    qDebug() << "delete rayqueue";
    emptyCondition.wakeAll();
}

void RayQueue::enqueue(Ray *ray){
    QMutexLocker locker(&mMutex);
    if (mRayQueue.size() > 40){
        Ray * r = mRayQueue.dequeue();
        delete r;
    }
    mRayQueue.enqueue(ray);
    emptyCondition.wakeAll();
}



Ray * RayQueue::dequeue(){
    QMutexLocker locker(&mMutex);
    if (mRayQueue.isEmpty()){
        emptyCondition.wait(&mMutex);
//        qDebug() << QDateTime::currentMSecsSinceEpoch();
    }
    if (mRayQueue.isEmpty()) return 0;
    return mRayQueue.dequeue();
}

bool RayQueue::isEmpty()
{
    QMutexLocker locker(&mMutex);
    return mRayQueue.isEmpty();
}

void RayQueue::wakeAll()
{
    emptyCondition.wakeAll();
}


