#ifndef MyWidget_H
#define MyWidget_H

#include <QWidget>
#include "dmaplayermanager.h"
#include <QMouseEvent>

class MyWidget : public QWidget
{
public:
    MyWidget();
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);

private:


    QImage img;
};

#endif // MyWidget_H
