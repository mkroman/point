#include <QDebug>

#include "HotKeySelectionDialogButton.hpp"
#include "ui_HotKeySelectionButton.h"

HotKeySelectionDialogButton::HotKeySelectionDialogButton(QWidget *parent) :
  QPushButton(parent)
{
  m_dialog = new HotKeySelectionDialog(this);

  connect(this    , SIGNAL(clicked())    , SLOT(openDialog()));
  connect(m_dialog, SIGNAL(finished(int)), SLOT(dialogSequenceUpdated(int)));
}

void HotKeySelectionDialogButton::dialogSequenceUpdated(int code)
{
  setText(m_dialog->toKeySequence().toString());

  Q_UNUSED(code)
}

void HotKeySelectionDialogButton::setKeySequence(int key, Qt::KeyboardModifiers modifiers)
{
  m_dialog->setKeySequence(key, modifiers);

  setText(m_dialog->toKeySequence().toString());
}

void HotKeySelectionDialogButton::openDialog()
{
  m_dialog->exec();
}
