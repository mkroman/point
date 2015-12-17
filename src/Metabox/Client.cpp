#include <QFile>
#include <QDebug>
#include <QBuffer>
#include <QVariant>
#include <QFileInfo>
#include <QVariantMap>
#include <QDataStream>
#include <QNetworkReply>
#include <QNetworkRequest>

#include "Metabox.hpp"
#include "qjson/parser.h"

namespace Metabox {

Client::Client(QObject *object) : QObject(object), m_networkManager() {
}

Upload* Client::upload(const QPixmap& pixmap, const QString& filename) {
  Upload*    upload = new Upload(this);
  QByteArray data;
  QBuffer    buffer(&data);

  pixmap.save(&buffer, "PNG");

  upload->setSize(buffer.size());
  upload->setName(filename);
  upload->setBuffer(data);

  return this->upload(upload);
}

Upload* Client::upload(const QString& path) {
  QFile file(path);
  QFileInfo fileInfo(file);
  Upload* upload = new Upload(this);

  if (!file.open(QIODevice::ReadOnly)) {
    qCritical() << "Could not open file" << path;
  }

  upload->setSize(file.size());
  upload->setName(fileInfo.baseName());
  upload->setBuffer(file.readAll());

  return this->upload(upload);
}

Upload* Client::upload(Upload* upload) {
  QByteArray buffer;
  QNetworkRequest request(QUrl("http://" + kMetaboxHost + "/api/account/upload"));

  request.setHeader(QNetworkRequest::ContentTypeHeader, "multipart/form-data; boundary=" + kMetaboxBoundary);

  buffer += "--" + kMetaboxBoundary + "\r\n";
  buffer += "Content-Disposition: form-data; name=\"file\"; filename=\"" + upload->name() + "\"\r\n\r\n";
  buffer += upload->buffer();
  buffer += "--" + kMetaboxBoundary + "\r\n";

  buffer += "--" + kMetaboxBoundary + "\r\n";
  buffer += "Content-Disposition: form-data; name=\"key\"\r\n\r\n";
  buffer += m_key.toAscii() + "\r\n";
  buffer += "--" + kMetaboxBoundary + "--\r\n";

  QNetworkReply* reply = m_networkManager.post(request, buffer);

  connect(reply, SIGNAL(finished()), upload, SLOT(requestFinished()));
  connect(reply, SIGNAL(uploadProgress(qint64,qint64)), upload, SLOT(requestProgressed(qint64,qint64)));

  return upload;
}

void Client::authenticate(const QString& email, const QString& password) {
  QUrl params;
  QNetworkRequest request(QUrl("http://" + kMetaboxHost + "/api/account/authenticate"));

  m_email = email;

  params.addQueryItem("email", email);
  params.addQueryItem("password", password);
  params.addQueryItem("application", kMetaboxAPIKey);

  QNetworkReply* reply = m_networkManager.post(request, params.encodedQuery());

  connect(reply, SIGNAL(finished()), SLOT(authenticationFinished()));
  connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), SLOT(authenticationFailed(QNetworkReply::NetworkError)));
}

void Client::authenticationFinished() {
  QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
  QJson::Parser parser;

  if (!reply->error()) {
    QVariantMap response = parser.parse(reply->readAll()).toMap();

    if (response["success"].toBool() == true) {
      m_key = response["key"].toString();

      emit authenticated();
    }
    else
      emit this->error(response["message"].toString());
  }
}

void Client::authenticationFailed(const QNetworkReply::NetworkError& error) {
  QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());

  Q_UNUSED(error)
  emit this->error(reply->errorString());
}

} // namespace Metabox
