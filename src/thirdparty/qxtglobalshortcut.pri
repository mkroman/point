SOURCES += qxtglobalshortcut/qxtglobalshortcut.cpp \
  qxtglobalshortcut/qxtglobal.cpp

HEADERS += qxtglobalshortcut/qxtglobal.h \
  qxtglobalshortcut/qxtglobalshortcut.h \
  qxtglobalshortcut/qxtglobalshortcut_p.h

win32: {
  DEFINES += BUILD_QXT_GUI
  SOURCES += qxtglobalshortcut/qxtglobalshortcut_win.cpp
}

unix:!mac {
  SOURCES += qxtglobalshortcut/qxtglobalshortcut_x11.cpp
}

mac: {
  SOURCES += qxtglobalshortcut/qxtglobalshortcut_mac.cpp
}
