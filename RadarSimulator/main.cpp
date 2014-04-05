#include <QtGui/QApplication>
#include "mainwindow.h"
#include <renderrardar/fullwindow.h>

#include <qgismapper/layerinfo.h>
#include <qgismapper/mywidget.h>
#include <qgismapper/dmaplayer.h>
#include <qgismapper/dmaplayermanager.h>
#include <qgismapper/dcommon.h>
#include <QQueue>

//QQueue<Ray*> queueRay;
bool rendered = true;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    QString pluginDir = "/usr/lib/qgis/";
//    QgsProviderRegistry::instance(pluginDir);

//    QString pathDir = "/home/khanhnq/Dev Program/data/MapLayers/";
//    QStringList baseNames;
//    baseNames.append("BorderLines"); //0
//    baseNames.append("CoastLines"); //1
//    baseNames.append("AirRoutes"); //2
//    baseNames.append("WaterLine"); //3
//    baseNames.append("Neighbor"); //4
//    baseNames.append("District"); // 5
//    baseNames.append("Airport"); // 6


//    QList<LayerInfo> layers;

//    layers.append(LayerInfo(
//                      pathDir+baseNames.at(0)+".shp",
//                      baseNames.at(0),
//                      QColor(0xaaffffff),
//                      1.0,
//                      0.6,
//                      false,
//                      Qt::DashDotDotLine));

//    layers.append(LayerInfo(
//                      pathDir+baseNames.at(1)+".shp",
//                      baseNames.at(1),
//                      QColor(0xaaffffff),
//                      1.0,
//                      1,
//                      false));

//        layers.append(LayerInfo(
//                          pathDir+baseNames.at(3)+".shp",
//                          baseNames.at(3),
//                          QColor(0xaa00ffff),
//                          1.0,
//                          0.3));
//            layers.append(LayerInfo(
//                              pathDir+baseNames.at(4)+".shp",
//                              baseNames.at(4),
//                              QColor(0x8800ff55),
//                              1.0,
//                              0.3));
//                layers.append(LayerInfo(
//                                  pathDir+baseNames.at(5)+".shp",
//                                  baseNames.at(5),
//                                  QColor(0x88ffcc00),
//                                  0.4,
//                                  0.3));
//    layers.append(LayerInfo(
//                      pathDir+baseNames.at(6)+".shp",
//                      baseNames.at(6),
//                      QColor(0,0,255,150),
//                      1.0,
//                      0.6));


//    layers.append(LayerInfo(
//                      pathDir+baseNames.at(2)+".shp",
//                      baseNames.at(2),
//                      QColor(0xbbffff00),
//                      1.0,
//                      0.3,
//                      true));




////    MyWidget widget;
////    widget.setMinimumSize(500,800);
////    widget.setMaximumSize(500,800);
////    widget.show();


//    DMapLayerManager::instance()->setLayerList(baseNames);
////    QgsMapCanvas a;

//    // add and visible true
//    for (int i=0; i<layers.size(); i++){
//        DMapLayerManager::instance()->addLayer(layers.at(i));
//    }

    FullWindow window;
    window.show();


    return a.exec();
}
