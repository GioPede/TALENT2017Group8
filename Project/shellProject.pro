TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11 -O3

LIBS += -larmadillo -llapack -lblas

SOURCES += src/main.cpp \
    src/utils.cpp \
    src/modelspace.cpp \
    src/system.cpp \
    src/input.cpp

HEADERS += \
    src/utils.h \
    src/modelspace.h \
    src/system.h \
    src/input.h

