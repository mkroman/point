#ifndef METABOX_UPLOAD_HPP
#define METABOX_UPLOAD_HPP

#include <QObject>
#include <QByteArray>
#include <QNetworkReply>

#include "Metabox/Metabox.hpp"

namespace Metabox {
class Upload : public QObject {
  Q_OBJECT

public:
  Upload(QObject* parent = 0);

  QString id() const {
    return m_id;
  }

  const QUrl url() const {
    return QUrl(QString("http://" + kMetaboxHost + "/%2").arg(m_id));
  }

  qint64 size() const {
    return m_size;
  }

  QString name() const {
    return m_name;
  }

  const QByteArray& buffer() const {
    return m_buffer;
  }

  float progress() const {
    return m_progress;
  }

  void setId(const QString& id) {
    m_id = id;
  }

  void setSize(qint64 size) {
    m_size = size;
  }

  void setName(const QString& name) {
    m_name = name;
  }

  void setBuffer(const QByteArray& buffer) {
    m_buffer = buffer;
  }

public slots:
  void requestFinished();
  void requestProgressed(const qint64 received, const qint64 total);

signals:
  void uploadFailed(const QString& message);
  void uploadFinished();
  void uploadProgressed(const double progress);

private:
  QString    m_id;
  qint64     m_size;
  QString    m_name;
  QByteArray m_buffer;
  double     m_progress;

};
} // namespace Metabox

#endif // METABOX_UPLOAD_HPP
