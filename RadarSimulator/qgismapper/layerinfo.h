#ifndef LAYERINFO_H
#define LAYERINFO_H

#include <QColor>

class LayerInfo
{
public:
    LayerInfo(){}
    LayerInfo(const QString & _path,
              const QString & _baseName,
              const QColor& _color,
              double _alpha,
              double _lineWidth,
              bool _enableLabel = false,
              Qt::PenStyle _penStyle= Qt::SolidLine);

    QString path;
    QString baseName;

    bool enableLabel;
    Qt::PenStyle penStyle;
    QColor color;
    double alpha;
    double lineWidth;

};

#endif // LAYERINFO_H
