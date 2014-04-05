#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QtGui>
#include <renderarea.h>
#include <clockrender.h>
#include <qimagerender.h>

class Window : public QWidget
{
    Q_OBJECT
public:
    explicit Window(QWidget *parent = 0);
    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    ~Window();
private:
    RenderArea* renderArea;
    ClockRender* clockRender;
    QPushButton* randomPointButton;
    QPushButton* clearButton;
    QImageRender* qImageRender;
    RenderImageThread renderThread;

signals:

public slots:

};

#endif // WINDOW_H
