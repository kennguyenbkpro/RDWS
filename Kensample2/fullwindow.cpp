#include "fullwindow.h"
#include <qimagerender.h>

extern bool rendered;

FullWindow::FullWindow(QWidget *parent) :
    QWidget(parent)
{
    rendered = true;
    qImageRender = new QImageRender();

    connect(&renderThread, SIGNAL(renderedImage(const QImage)), qImageRender, SLOT(renderQImage(const QImage)));
    renderThread.start();


    QGridLayout *layout = new QGridLayout(this);


    layout->addWidget(qImageRender);
    setLayout(layout);

    QLineEdit* editText = new QLineEdit(this);
    layout->addWidget(editText);
}

QSize FullWindow::minimumSizeHint() const
{
    return QSize(800, 800);
}
QSize FullWindow::sizeHint() const
{
    return QSize(1600, 1080);
}
