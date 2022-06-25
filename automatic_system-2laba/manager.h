#ifndef MANAGER_H
#define MANAGER_H

#include <QTime>
#include <QDateTime>
#include <QObject>
#include <QFile>
#include <QRegularExpression>
#include <QTemporaryFile>
#include <QDebug>
#include <QByteArray>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "evp.h"
#include <openssl/conf.h>
#include <openssl/err.h>
#include <openssl/aes.h>
#include <QBuffer>
#include "sitemodel.h"
#include <QClipboard>
#include <QPrinter>
#include <QtWebView>
#include <QTextCursor>

class Manager : public QObject
{
    Q_OBJECT
public:
    explicit Manager(QObject *parent = nullptr);
    SiteModel *siteModel;
    QString soursefile;
    unsigned char * iv = (unsigned char *)("77411230141456889873614547987324");

    int lastID;

public slots:

    void readFile(QString text = "");
    void addNewSite(QString url, QString login, QString password);
    void deleteSite(int id);
    void makeBackUp(QJsonObject root);
    void pdf(QString filename);


    bool encriptFile(const QString & mkey, const QString &in_file = "E:/qtproj/PasswordManager/sites_begin.json");

    //СМЕНА ПУТИ декрипта В readfile() !!!!
    QString decriptFile(const QString & mkey, const QString &in_file = "E:/qtproj/PasswordManager/sites_begin_crypt.json");

    QString decriptParam(const QString & mkey, const QString &in_file);
    QString encriptParam(const QString & mkey, const QString &in_file);
    QString currDate();

  private:
      unsigned char * m_iv = (unsigned char *)("32101230123456789873874547898765"); //32 символа
      QString PseudoKey;

  signals:

  };

  #endif // MANAGER_H
