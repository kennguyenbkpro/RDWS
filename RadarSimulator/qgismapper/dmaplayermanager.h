#ifndef DMAPLAYERMANAGER_H
#define DMAPLAYERMANAGER_H

#include <QString>
#include <QStringList>
#include <QMap>

#include "dmaplayer.h"
#include "layerinfo.h"

class DMapLayerManager
{
public:
    DMapLayerManager();

    void setLayerList(const QStringList& layerList);

    void addLayer(const LayerInfo & layerinfo);

    void setVisible(const QString& baseName, bool visible);

    QgsMapRenderer & getMapRender();

    void updateImg();

    void setExportInfo(const QgsRectangle &rect, const QSize&);

    QPoint longLat2XY(double long_, double lat_);
    QgsPoint xy2LongLat(int x, int y);
    QgsPoint xy2LongLat(QPoint);

    QImage & getImage();

    static DMapLayerManager * instance();
private:
    QMap<QString, int> layerVisible;
    QMap<QString, DMapLayer *> baseNameLayerInfoMap;

    QgsMapRenderer mapRender;
    QStringList layerSet;
    QImage img;

    void updateLayerSet();


    QgsRectangle rect;
    QSize outputSize;

    static DMapLayerManager * _instance;

};

#endif // DMAPLAYERMANAGER_H
