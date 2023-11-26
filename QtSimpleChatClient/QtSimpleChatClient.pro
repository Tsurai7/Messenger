QT += core network gui widgets

TARGET = QtSimpleChatClient
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS


CONFIG += debug_and_release

SOURCES += \
    baseentity.cpp \
    clientmain.cpp \
    chatwindow.cpp \
    chatclient.cpp \
    dbmanager.cpp \
    signup.cpp \
    user.cpp

FORMS += \
    chatwindow.ui \
    signup.ui

HEADERS += \
    baseentity.h \
    chatwindow.h \
    chatclient.h \
    dbmanager.h \
    signup.h \
    user.h
