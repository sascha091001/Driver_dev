#include "sitemodel.h"
#include <QAbstractItemModel>
#include <QMap>

SiteObject::SiteObject(const int &id, const QString &url, const QString &login, const QString &password)
    :
        m_id(id),
        m_url(url),
        m_login(login),
        m_password(password)
{
}

SiteModel::SiteModel(QObject *parent) : QAbstractListModel(parent)
{
}

int SiteObject::get_id() const{
    return m_id;
}

QString SiteObject::get_url() const{
    return m_url;
}

QString SiteObject::get_login() const{
    return m_login;
}

QString SiteObject::get_password() const{
    return m_password;
}

void SiteModel::addItem(const SiteObject & newItem){
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_items << newItem;
    endInsertRows();
}

int SiteModel::rowCount(const QModelIndex &parent) const{
    Q_UNUSED(parent);
    return m_items.count();
}

QVariant SiteModel::data(const QModelIndex & index, int role) const{
    if (index.row() < 0 || (index.row() >= m_items.count()))
        return QVariant();

    const SiteObject&itemToReturn = m_items[index.row()];

    if (role == SiteID){
        return itemToReturn.get_id();
    }
    else if (role == SiteURL){
        return itemToReturn.get_url();
    }
    else if (role == SiteLogin){
        return itemToReturn.get_login();
    }
    else if (role == SitePassword){
        return itemToReturn.get_password();
    }

    return QVariant();
}

QHash<int, QByteArray> SiteModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[SiteID] = "myID";
    roles[SiteURL] = "myURL";
    roles[SiteLogin] = "myLogin";
    roles[SitePassword] = "myPassword";

    return roles;
}

QVariantMap SiteModel::get(int idx) const
{
    QVariantMap map;
    foreach(int k, roleNames().keys())
    {
        map[roleNames().value(k)] = data(index(idx, 0), k);
    }
    return map;
}

void SiteModel::clear()
{
    beginRemoveRows(QModelIndex(), 0, rowCount()-1);
    m_items.clear();
    endRemoveRows();
}
