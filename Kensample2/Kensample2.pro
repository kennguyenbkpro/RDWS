# Add more folders to ship with the application, here
folder_01.source = qml/Kensample2
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

symbian:TARGET.UID3 = 0xE5BFF01B

# Smart Installer package's UID
# This UID is from the protected range and therefore the package will
# fail to install if self-signed. By default qmake uses the unprotected
# range value if unprotected UID is defined for the application and
# 0x2002CCCF value if protected UID is given to the application
#symbian:DEPLOYMENT.installer_header = 0x2002CCCF

# Allow network access on Symbian
symbian:TARGET.CAPABILITY += NetworkServices

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

# Add dependency to symbian components
# CONFIG += qtquickcomponents

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    window.cpp \
    renderarea.cpp \
    flightpoint.cpp \
    clockrender.cpp \
    qimagerender.cpp \
    renderimagethread.cpp \
    ray.cpp \
    fullwindow.cpp

# Please do not modify the following two lines. Required for deployment.
include(qmlapplicationviewer/qmlapplicationviewer.pri)
qtcAddDeployment()

HEADERS += \
    window.h \
    renderarea.h \
    flightpoint.h \
    clockrender.h \
    qimagerender.h \
    renderimagethread.h \
    ray.h \
    fullwindow.h

QT += core gui

DEFINES += QTCORELIB_LIBRARY

OTHER_FILES += \
    brick.png

RESOURCES += \
    images/Resource.qrc
























