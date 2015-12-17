#include <QDebug>
#include <QLocale>
#include <QTranslator>
#include <QtGui/QApplication>

#include "MainWindow.hpp"

int main(int argc, char *argv[]) {
  QSettings settings;
  QTranslator translator;
  QApplication app(argc, argv);

  app.setApplicationName("point");
  app.setOrganizationName("point");
  app.setApplicationVersion("0.0.1");
  app.setOrganizationDomain("uplink.io");

  if (settings.contains("language")) {
    if (translator.load("translations/point_" + settings.value("language").toString())) {
      app.installTranslator(&translator);
    }
  }

  MainWindow mainWindow;
  Q_UNUSED(mainWindow)
  return app.exec();
}
