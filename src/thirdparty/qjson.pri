SOURCES += \
  qjson/json_parser.cc \
  qjson/json_scanner.cpp \
  qjson/parser.cpp \
  qjson/parserrunnable.cpp \
  qjson/qobjecthelper.cpp \
  qjson/serializer.cpp \
  qjson/serializerrunnable.cpp

HEADERS += \
  qjson/json_parser.hh \
  qjson/json_scanner.h \
  qjson/location.hh \
  qjson/parser_p.h  \
  qjson/position.hh \
  qjson/qjson_debug.h  \
  qjson/stack.hh \
  qjson/parser.h \
  qjson/parserrunnable.h \
  qjson/qobjecthelper.h \
  qjson/serializer.h \
  qjson/serializerrunnable.h \
  qjson/qjson_export.h

win32 {
    DEFINES += QJSON_MAKEDLL
}
