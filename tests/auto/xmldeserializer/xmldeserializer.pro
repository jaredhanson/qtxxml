TEMPLATE = app
TARGET = tst_xmldeserializer

QT += testlib
macx:CONFIG -= app_bundle

include(../../../mkspecs/test.pri)

HEADERS += tst_xmldeserializer.h
SOURCES += tst_xmldeserializer.cpp
