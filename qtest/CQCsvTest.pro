TEMPLATE = app

QT += widgets

TARGET = CQCsvTest

DEPENDPATH += .

MOC_DIR = .moc

QMAKE_CXXFLAGS += -std=c++14

CONFIG += debug

SOURCES += \
CQCsvTest.cpp \

HEADERS += \
CQCsvTest.h \

DESTDIR     = ../bin
OBJECTS_DIR = ../obj
LIB_DIR     = ../lib

PRE_TARGETDEPS = \
$(LIB_DIR)/libCQCsv.a \

INCLUDEPATH = \
. \
../include \
../qinclude \

unix:LIBS += \
-L$$LIB_DIR \
-L../../CQCsv/lib \
\
-lCQCsv \
