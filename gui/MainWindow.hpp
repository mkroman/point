#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMenu>
#include <QMainWindow>
#include <QApplication>
#include <QSystemTrayIcon>

#include "Selector.hpp"
#include "LoginDialog.hpp"
#include "SettingsWindow.hpp"
#include "qxtglobalshortcut/qxtglobalshortcut.h"

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget* parent = 0);
  virtual ~MainWindow();

protected:
  void changeEvent(QEvent* event);

private slots:
  void logOut();
  void uploadFailed(const QString& message);
  void uploadFinished();
  void selectorFinished();
  void trayIconActivated(const QSystemTrayIcon::ActivationReason& reason);
  void clientAuthenticationError(const QString& message);
  void trayIconActivatedSettings();
  void clientAuthenticationSuccess();
  void shortcutActivated();
  void updateActiveWindowGlobalShortcut(const QKeySequence& keySequence);
  void updateSelectiveRegionGlobalShortcut(const QKeySequence& keySequence);
  void activeWindowShortcutActivated();
  void selectiveRegionShortcutActivated();

private:
  void readSettings();
  void saveSettings();
  void createTrayIcon();
  void createTrayIconMenu();

  bool    m_rememberLogin;
  QString m_email;
  QString m_password;

  bool             m_authenticated;
  QMenu*           m_trayIconMenu;
  Selector*        m_selector;
  LoginDialog*     m_loginDialog;
  SettingsWindow*  m_settingsWindow;
  QSystemTrayIcon* m_trayIcon;
  Metabox::Client* m_client;

  QxtGlobalShortcut* m_hotkeyActive;
  QxtGlobalShortcut* m_hotkeyRegion;

  QAction* m_exitAction;
  QAction* m_logOutAction;
  QAction* m_settingsAction;
};

#endif // MAINWINDOW_HPP
