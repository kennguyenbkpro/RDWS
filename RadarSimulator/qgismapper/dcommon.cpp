#include "dcommon.h"
#include <QDebug>

DCommon::DCommon()
{
}

void DCommon::printLayerList(const QStringList &list)
{
    qDebug() << "StringList have" << list.size() << "item:";
    for (int i=0; i<list.size(); i++){
        qDebug() << list.at(i) << "; ";
    }
}
