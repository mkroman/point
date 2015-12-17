#ifndef HOTKEYSELECTIONBUTTON_HPP
#define HOTKEYSELECTIONBUTTON_HPP

#include <QtGui/QWidget>
#include <QPushButton>

#include "HotKeySelectionDialog.hpp"

class HotKeySelectionDialogButton : public QPushButton
{
  Q_OBJECT
  
public:
  explicit HotKeySelectionDialogButton(QWidget *parent = 0);

  void setKeySequence(int key, Qt::KeyboardModifiers modifiers);

  int key() const {
    return m_dialog->key();
  }

  Qt::KeyboardModifiers modifiers() const {
    return m_dialog->modifiers();
  }

  QKeySequence toKeySequence() const
  {
    return m_dialog->toKeySequence();
  }

private slots:
  void openDialog();
  void dialogSequenceUpdated(int code);
  
private:
  HotKeySelectionDialog* m_dialog;
};

#endif // HOTKEYSELECTIONBUTTON_HPP
