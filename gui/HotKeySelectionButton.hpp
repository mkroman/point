#ifndef HOTKEYSELECTIONBUTTON_HPP
#define HOTKEYSELECTIONBUTTON_HPP

#include <QPushButton>
#include <QtEvents>

class HotKeySelectionButton : public QPushButton
{
  Q_OBJECT

public:
  explicit HotKeySelectionButton(QWidget *parent = 0);

  int key() const {
    return m_key;
  }

  void setKey(int key);
  
protected:
  void mousePressEvent(QMouseEvent *event);
  void keyPressEvent(QKeyEvent *event);

private:
  int  m_key;
  bool m_focused;
};

#endif // HOTKEYSELECTIONBUTTON_HPP
