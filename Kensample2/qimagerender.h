#ifndef QIMAGERENDER_H
#define QIMAGERENDER_H

#include <QWidget>
#include <QDebug>
#include <renderimagethread.h>

class QImageRender : public QWidget
{
    Q_OBJECT
public:
    explicit QImageRender(QWidget *parent = 0);
    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    ~QImageRender();

protected:
    void paintEvent(QPaintEvent *);

private:
    void printlog(QString mes);
    QPainter* painter;
    int angle;
    QPixmap pixmap;

signals:

public slots:
    void renderQImage(const QImage &image);
    void renderQImage();
};

#endif // QIMAGERENDER_H
