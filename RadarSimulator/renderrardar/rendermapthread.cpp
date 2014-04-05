#include "rendermapthread.h"
#include <qgis/qgsapplication.h>
#include <qgis/qgsproviderregistry.h>
#include <qgis/qgssinglesymbolrenderer.h>
#include <qgis/qgsmaplayerregistry.h>
#include <qgis/qgsvectorlayer.h>
#include <qgis/qgsmapcanvas.h>
#include <qgis/qgssinglesymbolrendererv2.h>
#include <qgis/qgssymbolv2.h>
#include <QDebug>


extern bool rendered;

RenderMapThread::RenderMapThread(QObject *parent) : QThread(parent)
{
    restart = false;
    abort = false;

    QString pluginDir = "/usr/lib/qgis/";
    QgsProviderRegistry::instance(pluginDir);

    QString pathDir = "/home/ken/Dev Program/VN shape file/";
    QStringList baseNames;
    baseNames.append("VNM_adm0"); //0
    baseNames.append("VNM_adm1"); //1
    baseNames.append("VNM_adm2"); //2
    baseNames.append("VNM_adm3"); //3
    baseNames.append("VNM_adm4"); //4


    QList<LayerInfo> layers;

//    layers.append(LayerInfo(
//                      pathDir+baseNames.at(0)+".shp",
//                      baseNames.at(0),
//                      QColor(0xaa1415ab),
//                      1.0,
//                      0.6,
//                      false,
//                      Qt::DashDotDotLine));

    layers.append(LayerInfo(
                      pathDir+baseNames.at(1)+".shp",
                      baseNames.at(1),
                      QColor(0xaa44aa44),
                      1.0,
                      1,
                      false));


//    layers.append(LayerInfo(
//                      pathDir+baseNames.at(5)+".shp",
//                      baseNames.at(5),
//                      QColor(0x88ffcc00),
//                      0.4,
//                      0.3));
//    layers.append(LayerInfo(
//                      pathDir+baseNames.at(6)+".shp",
//                      baseNames.at(6),
//                      QColor(0,0,255,150),
//                      1.0,
//                      0.6));







    //    MyWidget widget;
    //    widget.setMinimumSize(500,800);
    //    widget.setMaximumSize(500,800);
    //    widget.show();


    DMapLayerManager::instance()->setLayerList(baseNames);
    //    QgsMapCanvas a;

    // add and visible true
    for (int i=0; i<layers.size(); i++){
        DMapLayerManager::instance()->addLayer(layers.at(i));
    }
}

RenderMapThread::~RenderMapThread(){
    qmutex.lock();
    abort = true;
    condition.wakeOne();
    qmutex.unlock();
    qDebug() << "render map abort";
    wait();
}


void RenderMapThread::renderMap(QgsRectangle expectedRect, QSize resultSize)
{
    QMutexLocker locker(&qmutex);
    this->expectedRect = expectedRect;
    this->resultSize = resultSize;
    if (!isRunning()){
        start();
    } else {
        restart = true;
        condition.wakeOne();
    }
}

void RenderMapThread::run(){
    forever {
        if (abort) return;
        qmutex.lock();
        QgsRectangle eRec = this->expectedRect;
        QSize rSize = this->resultSize;
        qmutex.unlock();

        DMapLayerManager::instance()->setExportInfo(eRec, rSize);

        if (abort) return;
        if (restart){
            restart = false;
            continue;
        }


        emit updateMapToUI(DMapLayerManager::instance()->getImage());
        qDebug() << "emit map";

        qmutex.lock();
        if (!restart){
            condition.wait(&qmutex);
        }
        restart = false;
        qmutex.unlock();
    }
}
