#ifndef SELECTOR_HPP
#define SELECTOR_HPP

#include <QDebug>
#include <QPainter>
#include <QtEvents>
#include <QDockWidget>
#include <QApplication>
#include <QDesktopWidget>
#include <QDialog>

class Selector : public QWidget {
  Q_OBJECT

  enum SelectorStage { Selecting, Idle };

public:
  explicit Selector(QWidget* parent = 0);

  void prepare();

  const QPixmap pixmap() const {
    return m_pixmap;
  }

protected:
  void reset();
  bool event(QEvent* event);
  void paintEvent(QPaintEvent* event);
  void closeEvent(QCloseEvent* event);
  void mouseMoveEvent(QMouseEvent* event);

signals:
  void failed();
  void finished();

private:
  QRect   m_region;
  QPoint  m_start;
  QPixmap m_pixmap;
  QPixmap m_desktop;
  SelectorStage m_stage;
};

#endif // SELECTOR_HPP
