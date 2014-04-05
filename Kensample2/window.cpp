#include "window.h"
#include <renderarea.h>
#include <QtGui>
#include <math.h>

extern bool rendered;

Window::Window(QWidget *parent) :
    QWidget(parent)
{
    rendered = true;
    renderArea = new RenderArea();
    clockRender = new ClockRender();
    qImageRender = new QImageRender();
    randomPointButton = new QPushButton(tr("&Next"), this);
    clearButton = new QPushButton(tr("&Clear"), this);

    QTimer* qTimer = new QTimer();
    connect(qTimer, SIGNAL(timeout()), clockRender, SLOT(renderClock()));
//    connect(qTimer, SIGNAL(timeout()), qImageRender, SLOT(renderQImage()));
    qTimer->start(30);

    connect(&renderThread, SIGNAL(renderedImage(const QImage)), qImageRender, SLOT(renderQImage(const QImage)));
    renderThread.start();

    connect(randomPointButton,SIGNAL(clicked(bool)), renderArea, SLOT(drawNextPoint()));
    connect(clearButton, SIGNAL(clicked(bool)), renderArea, SLOT(clearPoint()));

    QGridLayout *layout = new QGridLayout(this);

    QBoxLayout *leftLayout = new QBoxLayout(QBoxLayout::TopToBottom);
    leftLayout-> addWidget(renderArea);
    leftLayout-> addWidget(randomPointButton);
    leftLayout-> addWidget(clearButton);
    leftLayout-> setSpacing(0);

    layout->addLayout(leftLayout, 0, 0);
    layout->addWidget(clockRender, 0, 1);
    layout->addWidget(qImageRender, 0, 2);
    setLayout(layout);
}
Window::~Window(){
  qDebug() << "destructor called";
}

QSize Window::minimumSizeHint() const
{
    return QSize(400, 600);
}
QSize Window::sizeHint() const
{
    return QSize(1400, 600);
}
