#ifndef SITEMODEL_H
#define SITEMODEL_H

#include <QObject>
#include <QAbstractItemModel>
#include<QAbstractListModel>
#include <QList>
#include <QModelIndex>
#include <QVariant>
#include <QUrl>

class SiteObject
{
public:

    SiteObject(const int &id, const QString &url, const QString &login, const QString &password);
    //
    int get_id() const;
    QString get_url() const;
    QString get_login() const;
    QString get_password() const;
    // прочие get-методы для выдачи ID, URL фотографии и др.
private:
    int m_id;
    QString m_url;
    QString m_login;
    QString m_password;
    // прочие свойства для хранения ID, URL фотографии и др.
};


class SiteModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum enmRoles {
        SiteID,
        SiteURL,
        SiteLogin,
        SitePassword
    };

    SiteModel(QObject *parent = nullptr);

    void addItem(const SiteObject & newItem);

    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const; // возвращает по индексу переменную (импользуется в ЛР 8)

    QVariantMap get(int idx) const;

    void clear();

protected:
    QHash<int, QByteArray> roleNames() const;
    // ключ - значение
    // нужен, чтобы строковые имена приводить в соответствие к полям френда

private:
    QList<SiteObject> m_items;
};

#endif // SITEMODEL_H
