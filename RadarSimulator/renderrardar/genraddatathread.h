#ifndef GENRADDATATHREAD_H
#define GENRADDATATHREAD_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <renderrardar/ray.h>

class GenRadDataThread : public QThread
{
    Q_OBJECT
public:
    GenRadDataThread(QObject *parent = 0);
    ~GenRadDataThread();
protected:
    void run();

private:
    QMutex qmutex;
    QWaitCondition condition;
    bool restart;
    bool abort;
    float alpha;
};


#endif // GENRADDATATHREAD_H
