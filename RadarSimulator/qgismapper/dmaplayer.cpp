#include "dmaplayer.h"
#include <qgssymbolv2.h>
#include <qgssinglesymbolrendererv2.h>
#include <qgslinesymbollayerv2.h>
#include <qgspallabeling.h>

#include <QDebug>

DMapLayer::DMapLayer(const LayerInfo & info)
{
    layerInfo = info;

    vectorLayer = NULL;
    addToRegistry();

}
DMapLayer::~DMapLayer(){
    qDebug() << "~DMapLayer()";
    removeFromRegistry();
}

void DMapLayer::createVectorLayer()
{
    if (vectorLayer==NULL){
        vectorLayer = new QgsVectorLayer(layerInfo.path, layerInfo.baseName, "ogr");
        if (vectorLayer==NULL || !vectorLayer->isValid()){
            qDebug() << "Create vectorlayer fail";
            return;
        }

        layerID = vectorLayer->getLayerID();
        setLabel();
        vectorLayer->enableLabels(true);

    }
}

void DMapLayer::setLabel()
{
    QgsPalLayerSettings lyr;
    lyr.readFromLayer(vectorLayer);

    lyr.enabled = layerInfo.enableLabel;
    lyr.fieldName = "name";
    lyr.dist = 0;
    lyr.placement = QgsPalLayerSettings::Line;
    lyr.placementFlags = 10;
    // lyr.placementFlags |= QgsPalLayerSettings::AboveLine;
    // lyr.placementFlags |= QgsPalLayerSettings::BelowLine;

    //if(layerName == "AirRoutes"){
        lyr.textColor = QColor(166,166,166,255);
        lyr.bufferColor = QColor(166,166,166,100);
//    }else{
//	lyr.textColor = QColor(0,0,0);
//	lyr.bufferColor = QColor(0,0,0,100);
//    }
    lyr.textFont = QFont("Sans Serif",9);

    lyr.bufferSize = 0;
    lyr.obstacle = true;
    lyr.labelPerPart = false;
    lyr.mergeLines = false;
//    lyr.multiLineLabels = false;
    lyr.writeToLayer(vectorLayer);
}

void DMapLayer::addToRegistry()
{
    createVectorLayer();
    QgsMapLayerRegistry::instance()->addMapLayer(vectorLayer, TRUE);
    configureLayer();
}

void DMapLayer::removeFromRegistry()
{
    QgsMapLayerRegistry::instance()->removeMapLayer(layerID);
    vectorLayer = NULL;
}

void DMapLayer::configureLayer()
{

    QgsSymbolV2 * symbol = QgsSymbolV2::defaultSymbol(vectorLayer->geometryType());

    if (vectorLayer->geometryType() == QGis::Line)
    {
        QgsSimpleLineSymbolLayerV2 *simpleSymbol = new QgsSimpleLineSymbolLayerV2();
        simpleSymbol->setPenStyle(layerInfo.penStyle);
        symbol->changeSymbolLayer(0, simpleSymbol);

        QgsLineSymbolV2 *lineSymbol = (QgsLineSymbolV2*)symbol;
        lineSymbol->setWidth(layerInfo.lineWidth);
        lineSymbol->setColor(layerInfo.color);
        lineSymbol->setAlpha(layerInfo.alpha);


    }
    if (vectorLayer->geometryType() == QGis::Polygon)
    {
        QgsFillSymbolV2* fillSymbol = (QgsFillSymbolV2*) symbol;
        fillSymbol->setAlpha(layerInfo.alpha);
        fillSymbol->setColor(layerInfo.color);
    }
    QgsSingleSymbolRendererV2 *mypRenderer = new QgsSingleSymbolRendererV2(symbol);
    vectorLayer->setRendererV2(mypRenderer);

}

QString & DMapLayer::getLayerId()
{
    return layerID;
}

QgsVectorLayer * DMapLayer::getVectorLayer()
{
    return vectorLayer;
}

LayerInfo & DMapLayer::getInfo()
{
    return layerInfo;
}




