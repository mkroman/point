#include <QDebug>

#include "MainWindow.hpp"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
  m_client         = new Metabox::Client(this);
  m_selector       = new Selector;
  m_loginDialog    = new LoginDialog(this, m_client);
  m_settingsWindow = new SettingsWindow(this);
  m_authenticated  = false;

  readSettings();
  createTrayIcon();
  createTrayIconMenu();
  m_trayIcon->show();

  if (m_rememberLogin) {
    m_client->authenticate(m_email, m_password);
  }
  else {
    m_loginDialog->show();
  }

  connect(m_client,         SIGNAL(authenticated()),                            SLOT(clientAuthenticationSuccess()));
  connect(m_client,         SIGNAL(error(QString)),                             SLOT(clientAuthenticationError(QString)));
  connect(m_selector,       SIGNAL(finished()),                                 SLOT(selectorFinished()));
  connect(m_hotkeyActive,   SIGNAL(activated()),                                SLOT(activeWindowShortcutActivated()));
  connect(m_hotkeyRegion,   SIGNAL(activated()),                                SLOT(selectiveRegionShortcutActivated()));
  connect(m_settingsWindow, SIGNAL(changedActiveWindowHotkey(QKeySequence)),    SLOT(updateActiveWindowGlobalShortcut(QKeySequence)));
  connect(m_settingsWindow, SIGNAL(changedSelectiveRegionHotkey(QKeySequence)), SLOT(updateSelectiveRegionGlobalShortcut(QKeySequence)));
}

void MainWindow::readSettings() {
  QSettings settings;

  // Set default global shortcuts
  QKeySequence hotkeySequenceActive(settings.value("hotkeys/active").toString());
  QKeySequence hotkeySequenceRegion(settings.value("hotkeys/region").toString());

  m_hotkeyActive = new QxtGlobalShortcut(hotkeySequenceActive, this);
  m_hotkeyRegion = new QxtGlobalShortcut(hotkeySequenceRegion, this);

  m_email         = settings.value("login/email").toString();
  m_password      = settings.value("login/password").toString();
  m_rememberLogin = settings.value("login/remember", false).toBool();
}

void MainWindow::createTrayIcon() {
  m_trayIcon = new QSystemTrayIcon(QIcon(":/icons/point"), this);

  connect(m_trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), SLOT(trayIconActivated(QSystemTrayIcon::ActivationReason)));
}

void MainWindow::trayIconActivatedSettings() {
  qDebug() << Q_FUNC_INFO << "Settings has been requested";

  m_settingsWindow->show();
}

void MainWindow::logOut() {
  qDebug() << Q_FUNC_INFO << "Logging out";

  m_loginDialog->updateInputFields();
  m_loginDialog->show();

  m_authenticated = false;
}

void MainWindow::trayIconActivated(const QSystemTrayIcon::ActivationReason& reason) {
  if (reason == QSystemTrayIcon::Trigger) {
    qDebug() << Q_FUNC_INFO << "Tray icon was clicked";

    if (m_authenticated) {
      m_selector->prepare();
      m_selector->show();
    }
  }
}

void MainWindow::clientAuthenticationSuccess() {
  qDebug() << Q_FUNC_INFO << "Authenticated as" << m_client->email();

  m_authenticated = true;

  m_trayIcon->showMessage("Point", tr("Successfully authenticated as %1.").arg(m_client->email()));
  m_loginDialog->hide();
}

void MainWindow::clientAuthenticationError(const QString& message) {
  qDebug() << Q_FUNC_INFO << "Error while authenticating" << message;

  m_authenticated = false;

  m_loginDialog->updateInputFields();
  m_loginDialog->setError(message);
  m_loginDialog->show();
}

void MainWindow::selectorFinished() {
  Metabox::Upload* upload;

  m_selector->hide();

  qDebug() << Q_FUNC_INFO << "Uploading a picture of the selected screen region";
  upload = m_client->upload(m_selector->pixmap(), "test screenshot.png");

  connect(upload, SIGNAL(uploadFinished()), SLOT(uploadFinished()));
  connect(upload, SIGNAL(uploadFailed(QString)), SLOT(uploadFailed(QString)));
}

void MainWindow::uploadFinished() {
  Metabox::Upload* upload = qobject_cast<Metabox::Upload*>(sender());

  qDebug() << Q_FUNC_INFO << "Upload finished and is availble at" << upload->url().toString();
}

void MainWindow::uploadFailed(const QString& message) {
  Metabox::Upload* upload = qobject_cast<Metabox::Upload*>(sender());

  qDebug() << "Upload failed!" << message;

  Q_UNUSED(upload)
}

void MainWindow::createTrayIconMenu() {
  m_trayIconMenu = new QMenu(this);

  m_settingsAction = m_trayIconMenu->addAction(tr("&Settings"), this, SLOT(trayIconActivatedSettings()));
  m_trayIconMenu->addSeparator();
  m_logOutAction = m_trayIconMenu->addAction(tr("L&og out"), this, SLOT(logOut()));
  m_exitAction = m_trayIconMenu->addAction(tr("E&xit"), qApp, SLOT(quit()));

  m_trayIcon->setContextMenu(m_trayIconMenu);
}

void MainWindow::changeEvent(QEvent* event) {
  QMainWindow::changeEvent(event);

  if (event->type() == QEvent::LanguageChange) {
    m_settingsAction->setText(tr("&Settings"));
    m_logOutAction->setText(tr("L&og out"));
    m_exitAction->setText(tr("E&xit"));
  }
}

void MainWindow::shortcutActivated() {
  qDebug() << Q_FUNC_INFO << "Shortcut pressed!";

  if (m_authenticated) {
    m_selector->prepare();
    m_selector->show();
  }
}

void MainWindow::updateSelectiveRegionGlobalShortcut(const QKeySequence& keySequence) {
  m_hotkeyRegion->setShortcut(keySequence);
}

void MainWindow::updateActiveWindowGlobalShortcut(const QKeySequence& keySequence) {
  m_hotkeyActive->setShortcut(keySequence);
}

void MainWindow::selectiveRegionShortcutActivated() {
  if (m_authenticated) {
    m_selector->prepare();
    m_selector->show();
  }
}

void MainWindow::activeWindowShortcutActivated() {
  qDebug() << Q_FUNC_INFO << "Not implemented yet";
}

MainWindow::~MainWindow() {
  delete m_selector;
  delete m_hotkeyActive;
  delete m_hotkeyRegion;
}
