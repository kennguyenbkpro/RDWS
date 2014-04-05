#-------------------------------------------------
#
# Project created by QtCreator 2014-03-26T07:38:31
#
#-------------------------------------------------

QT       += core gui

TARGET = RadarSimulator
TEMPLATE = app

DEFINES += QGISPLUGINDIR=$${QGISPLUGINDIR} CORE_EXPORT= GUI_EXPORT=

SOURCES += main.cpp\
        mainwindow.cpp \
    qgismapper/mywidget.cpp \
    qgismapper/layerinfo.cpp \
    qgismapper/dmaplayermanager.cpp \
    qgismapper/dmaplayer.cpp \
    qgismapper/dcommon.cpp \
    renderrardar/renderimagethread.cpp \
    renderrardar/renderarea.cpp \
    renderrardar/ray.cpp \
    renderrardar/qimagerender.cpp \
    renderrardar/myqpainter.cpp \
    renderrardar/fullwindow.cpp \
    renderrardar/flightpoint.cpp \
    renderrardar/rendermapthread.cpp \
    renderrardar/genraddatathread.cpp \
    config.cpp \
    renderrardar/rayqueue.cpp

HEADERS  += mainwindow.h \
    qgismapper/mywidget.h \
    qgismapper/layerinfo.h \
    qgismapper/dmaplayermanager.h \
    qgismapper/dmaplayer.h \
    qgismapper/dcommon.h \
    renderrardar/renderimagethread.h \
    renderrardar/renderarea.h \
    renderrardar/ray.h \
    renderrardar/qimagerender.h \
    renderrardar/myqpainter.h \
    renderrardar/fullwindow.h \
    renderrardar/flightpoint.h \
    renderrardar/rendermapthread.h \
    renderrardar/genraddatathread.h \
    config.h \
    renderrardar/rayqueue.h

FORMS    += mainwindow.ui

INCLUDEPATH += qgismapper\

OTHER_FILES += \
    qgismapper/qgislayer \
    renderrardar/renderimagethread.o \
    renderrardar/renderarea.o \
    renderrardar/qimagerender.o \
    renderrardar/flightpoint.o

unix:!macx:!symbian: LIBS += -L$$PWD/../../../../usr/lib/ -lqgis_core -lqgis_gui -lqgis_analysis

INCLUDEPATH += $$PWD/../../../../usr/include/qgis
DEPENDPATH += $$PWD/../../../../usr/include/qgis

unix:!macx:!symbian: LIBS += -L$$PWD/../../../../../../../usr/lib/ -lQtXml

INCLUDEPATH += $$PWD/../../../../../../../usr/include/QtXml
DEPENDPATH += $$PWD/../../../../../../../usr/include/QtXml


















