#include <QList>
#include <QDebug>
#include <QCloseEvent>
#include <QTranslator>
#include <QApplication>
#include <QScopedPointer>

#include "SettingsWindow.hpp"
#include "ui_SettingsWindow.h"
#include "Constants.hpp"

SettingsWindow::SettingsWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::SettingsWindow) {

  ui->setupUi(this);
  setFixedSize(size());

  // Insert languages into combobox.
  ui->languageComboBox->addItem(QIcon(":/flags/dk"), "Danish");
  ui->languageComboBox->addItem(QIcon(":/flags/en"), "English");

  readSettings();

  ui->regionHotKey->setKeySequence(Qt::Key_4, Qt::ShiftModifier | Qt::MetaModifier);
  qDebug() << Q_FUNC_INFO << 0;


/*
  // Set default values for the hotkey widgets.
  QKeySequence activeWindowKeySequence = qvariant_cast<QKeySequence>(m_settings.value("hotkeys/active"));
  QKeySequence selectiveRegionKeySequence = qvariant_cast<QKeySequence>(m_settings.value("hotkeys/region"));

  ui->activeWindowHotkey->setKeySequence(activeWindowKeySequence);
  ui->selectiveRegionHotkey->setKeySequence(selectiveRegionKeySequence);

  // Connect ALL the things.
  connect(ui->languageComboBox, SIGNAL(activated(QString)), SLOT(changedLanguage(QString)));
  connect(ui->activeWindowHotkey, SIGNAL(gotKeySequence(QKeySequence)), SLOT(activeWindowKeySequenceChanged(QKeySequence)));
  connect(ui->selectiveRegionHotkey, SIGNAL(gotKeySequence(QKeySequence)), SLOT(selectiveRegionKeySequenceChanged(QKeySequence)));
  */
}

void SettingsWindow::readSettings() {
  QSettings settings;
  int index;

  index = ui->languageComboBox->findText(languageName(settings.value("language").toString()));

  if (index != -1)
      ui->languageComboBox->setCurrentIndex(index);

  int key = settings.value("hotkeys/region/key", Qt::Key_4).toInt();

  //ui->regionHotKey->setKeySequence(key, modifiers);
}

void SettingsWindow::saveSettings() {
  QSettings settings;

  settings.setValue("language", ui->languageComboBox->currentText());
  settings.setValue("hotkeys/region/key", ui->regionHotKey->key());
  //settings.setValue("hotkeys/region/modifiers", ui->regionHotKey->modifiers());
}

void SettingsWindow::changedLanguage(const QString& text) {
  const QList<QTranslator*> translators(findChildren<QTranslator*>());
  QScopedPointer<QTranslator> translator(new QTranslator(this));

  if (text == "English") {
    qDebug() << Q_FUNC_INFO << "Wiping all translators";

    qDeleteAll(translators);
    qApp->installTranslator(translator.take());
  }
  else {
    QString translationCode = languageCode(text);
    qDebug() << Q_FUNC_INFO << "Installing new translator for language" << text;

    if (!translationCode.isEmpty() && translator->load("translations/point_" + translationCode)) {
      qDeleteAll(translators);
      qApp->installTranslator(translator.take());
    }
    else {
      qCritical() << Q_FUNC_INFO << "Invalid translation file returned";
    }
  }
}

void SettingsWindow::closeEvent(QCloseEvent* event) {
  hide();
  saveSettings();
  event->ignore();
}

void SettingsWindow::changeEvent(QEvent* event) {
  QMainWindow::changeEvent(event);

  if (event->type() == QEvent::LanguageChange) {
    ui->retranslateUi(this);
  }
}

SettingsWindow::~SettingsWindow() {
  saveSettings();

  delete ui;
}
