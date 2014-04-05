#include "qimagerender.h"
#include <QtGui>

extern bool rendered;

QImageRender::QImageRender(QWidget *parent) :
    QWidget(parent)
{
    painter = 0;
}

void QImageRender::paintEvent(QPaintEvent *){
    if (painter == 0){
        painter = new QPainter(this);
//        QPen qPenLine;
//        qPenLine.setColor("red");
//        qPenLine.setWidth(2);
//        painter->setPen(qPenLine);

        printlog(QString::number(painter == 0));
    }
    painter->setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter->fillRect(0,0,800,800, Qt::blue);

    painter->drawPixmap(0, 0, pixmap);

}

void QImageRender::renderQImage(){
    angle ++;
    update();
}

void QImageRender::renderQImage(const QImage &image){
    pixmap = QPixmap::fromImage(image);
    update();
    rendered = true;
}


QSize QImageRender::minimumSizeHint() const{
    return QSize(800,800);
}
QSize QImageRender::sizeHint() const{
    return QSize(800, 800);
}

void QImageRender::printlog(QString mes){
    qDebug() << mes;
}
QImageRender::~QImageRender(){
    delete painter;
}
