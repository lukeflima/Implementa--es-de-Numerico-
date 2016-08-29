#-------------------------------------------------
#
# Project created by QtCreator 2016-08-18T14:52:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = numerico
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    fparser/fparser.cc \
    fparser/fpoptimizer.cc \
    methods.cpp \
    form.cpp

HEADERS  += mainwindow.h \
    fparser/fparser.hh \
    fparser/fpconfig.hh \
    form.h

FORMS    += mainwindow.ui \
    form.ui

DISTFILES += \
    fparser/docs/style.css \
    fparser/docs/fparser.html \
    fparser/docs/gpl.txt \
    fparser/docs/lgpl.txt \
    fparser/extrasrc/fp_identifier_parser.inc \
    fparser/extrasrc/fp_opcode_add.inc
