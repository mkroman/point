#ifndef LOGINDIALOG_HPP
#define LOGINDIALOG_HPP

#include <QSettings>
#include <QMainWindow>
#include <QVBoxLayout>

#include "Metabox/Metabox.hpp"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QMainWindow {
  Q_OBJECT

public:
  explicit LoginDialog(QWidget* parent = 0, Metabox::Client* client = 0);
  ~LoginDialog();

  // Destructive functions
  void setError(const QString& text);
  void setClient(Metabox::Client* client) {
    m_client = client;
  }
  void updateInputFields();

protected:
  void changeEvent(QEvent* event);

private slots:
  void on_loginButton_clicked();

private:
  // Member variables
  bool m_remember;
  QSettings m_settings;
  QVBoxLayout m_layout;
  Metabox::Client* m_client;
  Ui::LoginDialog* ui;
};

#endif // LOGINDIALOG_HPP
