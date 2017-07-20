TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11 -O3

LIBS += -larmadillo -llapack -lblas

SOURCES += main.cpp \
    utils.cpp \
    input.cpp \
	modelspace.cpp \
    system.cpp

HEADERS += \
    Slater.hpp \
    BitsetSlater.hpp \
    input.h \
    utils.h \
    system.h \
    modelspace.h

