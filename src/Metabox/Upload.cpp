#include <QDebug>

#include "Upload.hpp"
#include "Metabox.hpp"
#include "qjson/parser.h"

namespace Metabox {

Upload::Upload(QObject* parent) : QObject(parent) {

}

void Upload::requestProgressed(const qint64 received, const qint64 total) {
  double percentage = 100.0f * received / total;

  if (percentage > m_progress) {
    m_progress = percentage;

    emit uploadProgressed(percentage);
  }
}

void Upload::requestFinished() {
  QJson::Parser parser;
  QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());

  if (reply->error() != QNetworkReply::NoError) {
    emit uploadFailed(reply->errorString());
  }
  else {
    QVariantMap response = parser.parse(reply->readAll()).toMap();

    if (response["success"].toBool()) {
      QVariantMap upload = response["upload"].toMap();
      m_id = upload["base_id"].toString();

      emit uploadFinished();
    }
    else {    
      emit uploadFailed(response["message"].toString());
    }
  }
}

} // namespace Metabox
