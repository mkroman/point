#ifndef SETTINGSWINDOW_HPP
#define SETTINGSWINDOW_HPP

#include <QSettings>
#include <QtGui/QMainWindow>

namespace Ui {
  class SettingsWindow;
}

class SettingsWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit SettingsWindow(QWidget* parent = 0);
  ~SettingsWindow();

protected:
  void changeEvent(QEvent* event);
  void closeEvent(QCloseEvent* event);

private slots:
  void changedLanguage(const QString& text);

signals:
  void changedActiveWindowHotkey(const QKeySequence& keySequence);
  void changedSelectiveRegionHotkey(const QKeySequence& keySequence);

private:
  void readSettings();
  void saveSettings();

  Ui::SettingsWindow* ui;
};

#endif // SETTINGSWINDOW_HPP
