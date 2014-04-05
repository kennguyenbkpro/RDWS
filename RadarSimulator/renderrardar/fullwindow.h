#ifndef FULLWINDOW_H
#define FULLWINDOW_H

#include <QWidget>
#include <QImage>
#include <renderrardar/renderimagethread.h>
#include <renderrardar/qimagerender.h>

class FullWindow : public QWidget
{
    Q_OBJECT
public:
    explicit FullWindow(QWidget *parent = 0);
    QSize minimumSizeHint() const;
    QSize sizeHint() const;

private:
    QImageRender* qImageRender;


signals:

public slots:

};

#endif // FULLWINDOW_H
