QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = futebol
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
        glwidget.cpp

HEADERS  += mainwindow.h \
            glwidget.h

FORMS    += mainwindow.ui

LIBS += -lglut -lGLU
