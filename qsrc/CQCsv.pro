TEMPLATE = lib

TARGET = CQCsv

DEPENDPATH += .

QT += widgets

CONFIG += staticlib

QMAKE_CXXFLAGS += -std=c++14

MOC_DIR = .moc

SOURCES += \
CQCsvModel.cpp \
CQCsvTable.cpp \

HEADERS += \
../qinclude/CQCsvModel.h \
../qinclude/CQCsvTable.h \

OBJECTS_DIR = ../obj

DESTDIR = ../lib

INCLUDEPATH += \
../qinclude \
../include \
