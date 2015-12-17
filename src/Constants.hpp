#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <QString>

static const char* language_name_list[] = {
  "Danish\0",
  "English\0",
  0
};

static const char* language_code_list[] = {
  "da_DK\0",
  "en_US\0",
  0
};

inline static const QString languageCode(const QString& name) {
  const char** ptr;

  for (ptr = language_name_list; *ptr; ptr++) {
    if (strcmp(*ptr, name.toLocal8Bit().data()) == 0)
      return QString(*ptr);
  }

  return QString();
}

inline static const QString languageName(const QString& code) {
  const char** ptr;

  for (ptr = language_code_list; *ptr; ptr++) {
    if (strcmp(*ptr, code.toLocal8Bit().data()) == 0)
      return QString(*ptr);
  }

  return QString();
}

#endif // CONSTANTS_HPP
