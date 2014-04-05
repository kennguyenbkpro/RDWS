#ifndef MYQPAINTER_H
#define MYQPAINTER_H

#include <qpainter.h>
#include <qpaintdevice.h>

class MyQPainter : public QPainter
{
public:
    explicit MyQPainter(QPaintDevice *);
    void drawPixmap(int x, int y, int w, int h, const QPixmap &pm,
                                     int sx, int sy, int sw, int sh);

signals:

public slots:

};

#endif // MYQPAINTER_H
