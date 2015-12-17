#-------------------------------------------------
#
# Project created by QtCreator 2011-10-14T08:31:35
#
#-------------------------------------------------

QT += core gui network

TARGET = point
TEMPLATE = app

DEPENDPATH  += src gui
INCLUDEPATH += src gui

RESOURCES = gui/point.qrc

SOURCES += src/main.cpp \
    src/Metabox/Client.cpp \
    src/Metabox/Upload.cpp \
    src/Selector.cpp \
    gui/LoginDialog.cpp \
    gui/MainWindow.cpp \
    gui/SettingsWindow.cpp \
    gui/HotKeySelectionDialog.cpp \
    gui/HotKeySelectionDialogButton.cpp \
    gui/HotKeySelectionButton.cpp

HEADERS += \
    src/Metabox/Client.hpp \
    src/Metabox/Upload.hpp \
    src/Selector.hpp \
    src/Metabox/Metabox.hpp \
    gui/LoginDialog.hpp \
    gui/MainWindow.hpp \
    gui/SettingsWindow.hpp \
    src/Constants.hpp \
    gui/HotKeySelectionDialog.hpp \
    gui/HotKeySelectionDialogButton.hpp \
    gui/HotKeySelectionButton.hpp

FORMS += \
    gui/LoginDialog.ui \
    gui/SettingsWindow.ui \
    gui/HotKeySelectionDialog.ui

TRANSLATIONS += translations/point_da_DK.ts

DEPENDPATH += src/thirdparty
INCLUDEPATH += src/thirdparty

include (src/thirdparty/qjson.pri)
include (src/thirdparty/qxtglobalshortcut.pri)
