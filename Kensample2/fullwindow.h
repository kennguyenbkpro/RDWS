#ifndef FULLWINDOW_H
#define FULLWINDOW_H

#include <QWidget>
#include <QImage>
#include <renderimagethread.h>
#include <qimagerender.h>

class FullWindow : public QWidget
{
    Q_OBJECT
public:
    explicit FullWindow(QWidget *parent = 0);
    QSize minimumSizeHint() const;
    QSize sizeHint() const;

private:
    QImageRender* qImageRender;
    RenderImageThread renderThread;

signals:

public slots:

};

#endif // FULLWINDOW_H
