#include <QtGui/QApplication>
#include "qmlapplicationviewer.h"
#include <renderarea.h>
#include <window.h>
#include <fullwindow.h>

bool rendered = true;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    FullWindow window;
    window.show();

//    Thread t;
//    QObject::connect(&t, SIGNAL(finished()), &a, SLOT(quit()));

//    QmlApplicationViewer viewer;
//    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
//    viewer.setMainQmlFile(QLatin1String("qml/Kensample2/main.qml"));
//    viewer.showExpanded();

    return app.exec();
}
