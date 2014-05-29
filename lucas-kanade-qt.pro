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


SOURCES += src/main.cpp \
    src/lk_utils.cpp \
    src/lk_conv.cpp \
    src/lk_vec2f.cpp \
    src/lk_mat22f.cpp \
    src/lk_vec2i.cpp

HEADERS += \
    src/lk_utils.h \
    src/lk_conv.h \
    src/lk_vec2f.h \
    src/lk_mat22f.h \
    src/lk_vec2i.h

#PROFILING WITH GPROG
#QMAKE_CXXFLAGS_DEBUG += -pg
#QMAKE_LFLAGS_DEBUG += -pg
#QMAKE_CXXFLAGS_RELEASE += -pg
#QMAKE_LFLAGS_RELEASE += -pg

OTHER_FILES += \
    gomp.lib
