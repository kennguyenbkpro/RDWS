#include "layerinfo.h"

LayerInfo::LayerInfo(const QString & _path,
                     const QString & _baseName,
                     const QColor& _color,
                     double _alpha,
                     double _lineWidth,
                     bool _enableLabel,
                     Qt::PenStyle _penStyle){

    path = _path;
    baseName = _baseName;

    enableLabel = _enableLabel;
    penStyle = _penStyle;
    color = _color;
    alpha = _alpha;
    lineWidth = _lineWidth;
}
