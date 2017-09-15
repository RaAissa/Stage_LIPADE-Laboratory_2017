# Add more folders to ship with the application, here
#folder_01.source = qml/Stage
#folder_01.target = qml
#DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
#QML_IMPORT_PATH =

#symbian:TARGET.UID3 = 0xE06AA024

# Smart Installer package's UID
# This UID is from the protected range and therefore the package will
# fail to install if self-signed. By default qmake uses the unprotected
# range value if unprotected UID is defined for the application and
# 0x2002CCCF value if protected UID is given to the application
#symbian:DEPLOYMENT.installer_header = 0x2002CCCF

# Allow network access on Symbian
#symbian:TARGET.CAPABILITY += NetworkServices

QT+=widgets

QT       += core gui
QT += qml quick
greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

TARGET = stage
TEMPLATE = app

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

# Speed up launching on MeeGo/Harmattan when using applauncherd daemon
# CONFIG += qdeclarative-boostable

# Add dependency to Symbian components
# CONFIG += qt-components

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    mafenetre.cpp \
    tool.cpp \
    graphcut.cpp \
    inpainting.cpp \
    dossier.cpp \
    video.cpp \
    traitement.cpp \
    inpainter.cpp \
    inpaintingimage.cpp \
    lucaskanade.cpp \
    lucaskanadedirection.cpp \
    lucaskanadecartedechaleur.cpp \
    lucaskanadedirectionsintensite.cpp \
    inpaintinginverser.cpp \
    analyseletk.cpp \
    Etoile.cpp \
    MeanShift.cpp \
    etoile_k.cpp \
    evaluation_class.cpp

# Please do not modify the following two lines. Required for deployment.
#include(Other files/qmlapplicationviewer/qmlapplicationviewer.pri)
#qtcAddDeployment()
#QT += declarative
#QMAKE_LFLAGS += -static

INCLUDEPATH += -I/usr/local/include

INCLUDEPATH += -I/usr/local/include/opencv2
INCLUDEPATH += -I/usr/local/include/ITK-4.10

LIBS += -L/usr/local/lib
LIBS += -lopencv_core
LIBS += -lopencv_highgui
LIBS += -lopencv_imgproc
LIBS += -lopencv_features2d
LIBS += -lopencv_photo
LIBS += -lopencv_video


#LIBS += -L/home/poos/Bureau/opencv-2.4.9/lib/
#LIBS += -lopencv_core
#LIBS += -lopencv_highgui
#LIBS += -lopencv_imgproc
#LIBS += -lopencv_features2d
#LIBS += -lopencv_photo
#LIBS += -lopencv_video

HEADERS += \
    mafenetre.h \
    tool.h \
    graphcut.h \
    dossier.h \
    video.h \
    traitement.h \
    inpainter.h \
    inpainting.h \
    inpaintingimage.h \
    lucaskanade.h \
    lucaskanadedirection.h \
    lucaskanadecartedechaleur.h \
    lucaskanadedirectionsintensite.h \
    inpaintinginverser.h \
    analyseletk.h \
    Etoile.h \
    Bibliotheque.h \
    MeanShift.h \
    Clustering.h \
    etoile_k.h \
    kmean.h \
    evaluation_class.h

QMAKE_LFLAGS += -Wl,-rpath=./lib
