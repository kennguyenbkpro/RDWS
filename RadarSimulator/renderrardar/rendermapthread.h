#ifndef RENDERMAPTHREAD_H
#define RENDERMAPTHREAD_H
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <qgsrectangle.h>
#include <QSize>
#include <qgismapper/dmaplayermanager.h>

class RenderMapThread : public QThread
{
    Q_OBJECT

public:
    RenderMapThread(QObject * parent = 0);
    ~RenderMapThread();
    void renderMap(QgsRectangle expectedRect, QSize resultSize);
signals:
    void updateMapToUI(const QImage &image);

protected:
    void run();

private:
    QMutex qmutex;
    QWaitCondition condition;
    bool restart;
    bool abort;
    QgsRectangle expectedRect;
    QSize resultSize;

};

#endif // RENDERMAPTHREAD_H
