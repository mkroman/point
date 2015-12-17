#ifndef METABOX_CLIENT_HPP
#define METABOX_CLIENT_HPP

#include <QObject>
#include <QPixmap>
#include <QNetworkReply>
#include <QNetworkAccessManager>

namespace Metabox {

class Upload;

class Client : public QObject {
  Q_OBJECT

public:
  Client(QObject *object = 0);

  void authenticate(const QString& email,
                    const QString& password);

  const QString& email() {
    return m_email;
  }

  void setEmail(const QString& email) {
    m_email = email;
  }

  Upload* upload(Upload* upload);
  Upload* upload(const QString& path);
  Upload* upload(const QPixmap& pixmap, const QString& filename = QString());

private slots:
  void authenticationFailed(const QNetworkReply::NetworkError& error);
  void authenticationFinished();

signals:
  void error(const QString& message);
  void authenticated();

private:
  QString m_key;
  QString m_email;
  QNetworkAccessManager m_networkManager;
};
} // namespace Metabox

#endif // METABOX_CLIENT_HPP
