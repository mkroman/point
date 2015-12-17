#include <QDebug>
#include "HotKeySelectionButton.hpp"

HotKeySelectionButton::HotKeySelectionButton(QWidget *parent) :
  QPushButton(parent)
{
}

void HotKeySelectionButton::keyPressEvent(QKeyEvent *event)
{
  if (m_focused)
  {
    int key = event->key();

    if ((key >= Qt::Key_A && key <= Qt::Key_Z) ||
        (key >= Qt::Key_0 && key <= Qt::Key_9) ||
        (key >= Qt::Key_F1 && key <= Qt::Key_F35))
    {
      setText(QKeySequence(key).toString());
      releaseKeyboard();

      m_key = key;
      m_focused = false;
    }
    else if (key == Qt::Key_Escape)
    {
      setText(QKeySequence(m_key).toString());
      releaseKeyboard();

      m_focused = false;

      return;
    }
  }

  QPushButton::keyPressEvent(event);
}

void HotKeySelectionButton::setKey(int key)
{
  m_key = key;

  setText(QKeySequence(key).toString());
}

void HotKeySelectionButton::mousePressEvent(QMouseEvent *event)
{
  if (!m_focused)
  {
    setCheckable(true);
    setChecked(true);

    setText("...");
    grabKeyboard();

    m_focused = true;
  }

  QPushButton::mousePressEvent(event);
}
