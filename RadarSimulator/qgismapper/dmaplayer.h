#ifndef DMAPLAYER_H
#define DMAPLAYER_H



#include <QString>
#include <QColor>


#include <qgsvectorlayer.h>
#include <qgsmaplayerregistry.h>

#include <layerinfo.h>

class DMapLayer
{
public:
    DMapLayer(const LayerInfo & info);
    ~DMapLayer();

    void addToRegistry();
    void removeFromRegistry();

    void configureLayer();

    QString & getLayerId();

    LayerInfo & getInfo();

    QgsVectorLayer * getVectorLayer();


private:



    QString layerID;

    QgsVectorLayer * vectorLayer;


    LayerInfo layerInfo;

    void createVectorLayer();

    void setLabel();
};

#endif // DMAPLAYER_H
