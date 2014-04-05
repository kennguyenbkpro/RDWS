#include "myqpainter.h"

MyQPainter::MyQPainter(QPaintDevice *device) :
    QPainter(device)
{
}

void MyQPainter::drawPixmap(int x, int y, int w, int h, const QPixmap &pm,
                                 int sx, int sy, int sw, int sh){

        QPainter::drawPixmap(QRectF(x, y, w, h), pm, QRectF(sx, sy, sw, sh));
//    QPainterPrivate * d = d_ptr.data();
//    d.
}
