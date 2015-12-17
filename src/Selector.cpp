#include "Selector.hpp"

Selector::Selector(QWidget* parent) : QWidget(parent) {
  setCursor(Qt::CrossCursor);
  setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Window);
}

bool Selector::event(QEvent* event) {
  if (event->type() == QEvent::MouseButtonPress) {
    QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);

    m_stage = Selecting;
    m_start = mouseEvent->pos();
  }
  else if (event->type() == QEvent::MouseButtonRelease) {
    m_stage = Idle;
    m_pixmap = m_desktop.copy(m_region);

    reset();
    emit finished();
  }

  return QWidget::event(event);
}

void Selector::mouseMoveEvent(QMouseEvent* event) {
  if (m_stage != Selecting)
    return;

  m_region = QRect(m_start, event->pos()).normalized();
  update();
}

void Selector::closeEvent(QCloseEvent* event) {
  hide();
  event->ignore();
}

void Selector::paintEvent(QPaintEvent* event) {
  QBrush   overlayBrush(QColor(0, 0, 0, 125));
  QRegion  overlayRegion(rect());
  QPainter painter(this);

  overlayRegion = overlayRegion.subtracted(m_region);

  painter.drawPixmap(m_desktop.rect(), m_desktop);
  painter.setBrush(overlayBrush);
  painter.setClipRegion(overlayRegion);
  painter.drawRect(-1, -1, rect().width() + 1, rect().height() + 1);

  Q_UNUSED(event)
}

void Selector::reset() {
  m_stage = Idle;
  m_region = QRect();
  m_desktop = QPixmap();
}

void Selector::prepare() {
  m_stage = Idle;
  m_desktop = QPixmap::grabWindow(QApplication::desktop()->winId());

  update(); // Force a repainting to show the new pixmap.
  setWindowState(windowState() | Qt::WindowFullScreen); // Set the window state to full-screen in case it isn't already.
}
