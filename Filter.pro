#-------------------------------------------------
#
# Project created by QtCreator 2015-10-04T04:30:37
#
#-------------------------------------------------

QT       += core gui multimedia multimediawidgets


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Filter
TEMPLATE = app


SOURCES += main.cpp\
        filterdemo.cpp \
    videoframesurface.cpp \
    glwidget.cpp

HEADERS  += filterdemo.h \
    videoframesurface.h \
    glwidget.h

FORMS    +=

CONFIG += c++11

DISTFILES +=

RESOURCES     = textures.qrc \
    glsl.qrc
