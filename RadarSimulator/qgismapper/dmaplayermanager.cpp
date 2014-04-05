#include "dmaplayermanager.h"

#include <QPainter>

#include "dcommon.h"

#include <qgspallabeling.h>

#include <QDebug>

DMapLayerManager* DMapLayerManager::_instance = NULL;

DMapLayerManager::DMapLayerManager()
{
    QgsPalLabeling* mPLabel = new QgsPalLabeling();
    mapRender.setLabelingEngine(mPLabel);
}

// khai bao xem thang nao an hien, ban dau tat ca deu hien
void DMapLayerManager::setLayerList(const QStringList &layerList)
{
    // set visible all layer
    for (int i=0; i<layerList.size(); i++){
        layerVisible.insert(layerList.at(i), 1);
    }

}

// them mot thang vao, coi nhu hien
void DMapLayerManager::addLayer(const LayerInfo & layerinfo)
{

    DMapLayer * mapLayer = new DMapLayer(layerinfo);

    baseNameLayerInfoMap.insert(mapLayer->getInfo().baseName, mapLayer);

    updateLayerSet();

    updateImg();
}

void DMapLayerManager::setVisible(const QString& baseName, bool visible)
{
    if (!baseNameLayerInfoMap.contains(baseName)){
        return;
    }

    DMapLayer *layer = baseNameLayerInfoMap.value(baseName);

    if (visible == false && layerVisible.value(baseName) == true){
        layer->removeFromRegistry();
    } else if (visible == true && layerVisible.value(baseName) == false) {
        layer->addToRegistry();
    }

    layerVisible.insert(layer->getInfo().baseName, visible);
    updateLayerSet();
    updateImg();
}

void DMapLayerManager::updateLayerSet()
{
    layerSet.erase(layerSet.begin(), layerSet.end());

    QMapIterator<QString, int> i(layerVisible);
    while (i.hasNext()) {
        i.next();
        if (i.value() == 1){

            if (baseNameLayerInfoMap.contains(i.key())){
                layerSet.append( baseNameLayerInfoMap.value(i.key())->getLayerId());
            }
        }
    }

    mapRender.setLayerSet(layerSet);
    // DCommon::printLayerList(layerSet);
}

QgsMapRenderer & DMapLayerManager::getMapRender()
{
    return mapRender;
}

void DMapLayerManager::updateImg()
{
    img.fill(qRgba(0, 0, 0, 0));
    QPainter painter;
    painter.begin(&img);
//    painter.setRenderHint(QPainter::Antialiasing);

    mapRender.render(&painter);

    painter.end();

}

void DMapLayerManager::setExportInfo(const QgsRectangle & _rect, const QSize& _size)
{
    rect = _rect;
    outputSize = _size;

    img = QImage(_size, QImage::Format_ARGB32);
    img.fill(qRgba(0, 0, 0, 0));

    mapRender.setExtent(_rect);
    mapRender.setOutputSize(_size, img.logicalDpiX());


    updateImg();
}

QImage & DMapLayerManager::getImage()
{
    return img;
}

QPoint DMapLayerManager::longLat2XY(double long_, double lat_)
{
    double x1 = long_;
    double y1 = lat_;
    mapRender.coordinateTransform()->transformInPlace(x1, y1);
    return QPoint(x1, y1);
}

QgsPoint DMapLayerManager::xy2LongLat(int x, int y)
{
    return mapRender.coordinateTransform()->toMapCoordinates(x, y);
}

QgsPoint DMapLayerManager::xy2LongLat(QPoint p)
{
    return mapRender.coordinateTransform()->toMapCoordinates(p.x(), p.y());
}

DMapLayerManager * DMapLayerManager::instance()
{
    if (_instance==NULL){
        _instance = new DMapLayerManager();
    }
    return _instance;
}




