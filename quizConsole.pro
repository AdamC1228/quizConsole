QT += core
QT -= gui

CONFIG += c++11

TARGET = quizConsole
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    filehelper.cpp \
    question.cpp \
    quiz.cpp \
    console.cpp \
    threader.cpp

HEADERS += \
    filehelper.h \
    question.h \
    quiz.h \
    main.h \
    console.h \
    threader.h
