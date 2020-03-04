#-------------------------------------------------
#
# Project created by QtCreator 2019-08-15T14:41:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CameraCalibratorTool
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
# DEFINES += QT_DEPRECATED_WARNINGS
# DESTDIR = $$PWD/../builds
# MOC_DIR = $$PWD/../bin/mocs
# OBJECTS_DIR = $$PWD/../bin/objs
RC_ICONS = $$PWD/assets/app.ico

VLC_PATH = ../packages/libvlc-2.2.2
OPENCV_PATH = ../packages/opencv347
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
include(CameraCalibratorTool.pri)

INCLUDEPATH += $${VLC_PATH}/include \
               $${OPENCV_PATH}/include \
               ./src

win32 {
    QMAKE_CXXFLAGS += /Zi
    contains(QMAKE_TARGET.arch, x86_64) {
        QMAKE_LFLAGS += /MACHINE:X64
        LIBS += -L$${VLC_PATH}/lib -llibvlc -llibvlccore

        CONFIG(debug, debug|release) {
            DESTDIR = ./bin/x64/Debug
            LIBS += -L$${OPENCV_PATH}/lib -lopencv_world347d
            QMAKE_LFLAGS_WINDOWS += /LARGEADDRESSAWARE
        }
        else {
            DESTDIR = ./bin/x64/Release
            LIBS += -L$${OPENCV_PATH}/lib -lopencv_world347
            QMAKE_LFLAGS_WINDOWS += /debug /opt:ref /MAP /MAPINFO:EXPORTS /LARGEADDRESSAWARE
        }
    }
    else {
        QMAKE_LFLAGS += /MACHINE:X86
        #Require x86 lib
        LIBS += -L$${VLC_PATH}/lib -llibvlc -llibvlccore

                CONFIG(debug, debug|release) {
            DESTDIR = ./bin/win32/Debug
            QMAKE_LFLAGS_WINDOWS += /LARGEADDRESSAWARE
        }
        else {
            DESTDIR = ./bin/win32/Release
            QMAKE_LFLAGS_WINDOWS += /debug /opt:ref /MAP /MAPINFO:EXPORTS /LARGEADDRESSAWARE
        }
    }
}

