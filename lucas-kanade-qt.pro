#-------------------------------------------------
#
# Project created by QtCreator 2011-02-20T11:49:12
#
#-------------------------------------------------

QT       += core gui
TARGET = lucaskanade
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    lk_utils.cpp \
    lk_conv.cpp \
    lk_vec2f.cpp \
    lk_mat22f.cpp \
    lk_vec2i.cpp

HEADERS += \
    lk_utils.h \
    lk_conv.h \
    lk_vec2f.h \
    lk_mat22f.h \
    lk_vec2i.h

#PROFILING WITH GPROG
#QMAKE_CXXFLAGS_DEBUG += -pg
#QMAKE_LFLAGS_DEBUG += -pg
#QMAKE_CXXFLAGS_RELEASE += -pg
#QMAKE_LFLAGS_RELEASE += -pg

OTHER_FILES += \
    gomp.lib
