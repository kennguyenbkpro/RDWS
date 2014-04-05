#include "fullwindow.h"
#include <renderrardar/qimagerender.h>
#include <qgsrectangle.h>
#include <dmaplayermanager.h>

extern bool rendered;

FullWindow::FullWindow(QWidget *parent) :
    QWidget(parent)
{



    qImageRender = new QImageRender();
    qImageRender->setFocusPolicy(Qt::StrongFocus);

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
    return QSize(1000, 1080);
}
