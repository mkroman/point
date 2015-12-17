#include <QDebug>
#include <QSettings>

#include "LoginDialog.hpp"
#include "ui_LoginDialog.h"

using namespace Metabox;

LoginDialog::LoginDialog(QWidget* parent, Client* client) : QMainWindow(parent), m_client(client), ui(new Ui::LoginDialog) {
  ui->setupUi(this);

  ui->errorLabel->clear();
}

void LoginDialog::on_loginButton_clicked() {
  if (ui->emailText->text().isEmpty()) {
    setError("Please type your e-mail.");
  }
  else if (ui->passwordText->text().isEmpty()) {
    setError("Please type your password.");
  }
  else {
    m_settings.setValue("login/email", ui->emailText->text());
    m_settings.setValue("login/password", ui->passwordText->text());
    m_settings.setValue("login/remember", ui->rememberBox->isChecked());

    m_client->authenticate(ui->emailText->text(), ui->passwordText->text());
  }
}

void LoginDialog::updateInputFields() {
  bool remember    = m_settings.value("login/remember", false).toBool();
  QString email    = m_settings.value("login/email").toString();
  QString password = m_settings.value("login/password").toString();

  ui->emailText->setText(email);
  ui->passwordText->setText(password);
  ui->rememberBox->setChecked(remember);
}

void LoginDialog::setError(const QString& text) {
  ui->errorLabel->setText(tr("Error: %1").arg(text));
}

void LoginDialog::changeEvent(QEvent* event) {
  QMainWindow::changeEvent(event);

  if (event->type() == QEvent::LanguageChange) {
    ui->retranslateUi(this);
  }
}

LoginDialog::~LoginDialog() {
  delete ui;
}
