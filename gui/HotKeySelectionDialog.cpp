#include "HotKeySelectionDialog.hpp"
#include "ui_HotKeySelectionDialog.h"

HotKeySelectionDialog::HotKeySelectionDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::HotKeySelectionDialog)
{
  ui->setupUi(this);

  setFixedSize(size());
}

HotKeySelectionDialog::~HotKeySelectionDialog()
{
  delete ui;
}

int HotKeySelectionDialog::key() const
{
  return ui->keyButton->key();
}

Qt::KeyboardModifiers HotKeySelectionDialog::modifiers()
{
  Qt::KeyboardModifiers modifier;

  if (ui->shiftModifierButton->isChecked())
    modifier ^= Qt::ShiftModifier;

  if (ui->controlModifierButton->isChecked())
    modifier ^= Qt::ControlModifier;

  if (ui->altModifierButton->isChecked())
    modifier ^= Qt::AltModifier;

  if (ui->metaModifierButton->isChecked())
    modifier ^= Qt::MetaModifier;

  return modifier;
}

QKeySequence HotKeySelectionDialog::toKeySequence()
{
  return QKeySequence(ui->keyButton->key() + modifiers());
}

void HotKeySelectionDialog::setKeySequence(int key, Qt::KeyboardModifiers modifiers)
{
  ui->keyButton->setKey(key);

  if (modifiers & Qt::ShiftModifier)
    ui->shiftModifierButton->setChecked(true);

  if (modifiers & Qt::ControlModifier)
    ui->controlModifierButton->setChecked(true);

  if (modifiers & Qt::AltModifier)
    ui->altModifierButton->setChecked(true);

  if (modifiers & Qt::MetaModifier)
    ui->metaModifierButton->setChecked(true);
}

void HotKeySelectionDialog::changeEvent(QEvent *e)
{
  QDialog::changeEvent(e);
  switch (e->type()) {
  case QEvent::LanguageChange:
    ui->retranslateUi(this);
    break;
  default:
    break;
  }
}
