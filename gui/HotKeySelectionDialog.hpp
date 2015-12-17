#ifndef HOTKEYSELECTIONDIALOG_HPP
#define HOTKEYSELECTIONDIALOG_HPP

#include <QtGui/QDialog>

namespace Ui {
class HotKeySelectionDialog;
}

class HotKeySelectionDialog : public QDialog
{
  Q_OBJECT
  
public:
  explicit HotKeySelectionDialog(QWidget *parent = 0);
  ~HotKeySelectionDialog();

  int key() const;

  QString printableText();
  QKeySequence toKeySequence();
  Qt::KeyboardModifiers modifiers();

  void setKeySequence(int key, Qt::KeyboardModifiers modifiers = Qt::NoModifier);
  
protected:
  void changeEvent(QEvent *e);
  
private:
  Ui::HotKeySelectionDialog *ui;
};

#endif // HOTKEYSELECTIONDIALOG_HPP
