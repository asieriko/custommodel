#include "stringproxymodel.h"
#include <QDebug>

StringProxyModel::StringProxyModel(QObject *parent) : QAbstractProxyModel(parent)
{
    qDebug() << "Created";

}

void StringProxyModel::setSourceModel(QAbstractTableModel *sourceModel)
{
    qDebug() << "sSM";
    QAbstractProxyModel::setSourceModel(sourceModel);
    sourceModel1 = sourceModel;
}

QModelIndex StringProxyModel::mapFromSource(const QModelIndex& sourceIndex) const
{
    qDebug() << "mfs";
    if(sourceIndex.isValid())
    return createIndex(sourceIndex.row(), sourceIndex.column());
    else
    return QModelIndex();

}

QModelIndex StringProxyModel::mapToSource(const QModelIndex& proxyIndex) const
{
    qDebug() << "m2s";
    qDebug()<< sourceModel1->index(proxyIndex.row(), proxyIndex.column());
  return sourceModel1->index(proxyIndex.row(), proxyIndex.column());
}

QModelIndex StringProxyModel::index(int row, int column, const QModelIndex& parent) const
{
    qDebug() << "index";
  Q_UNUSED(parent);
//  return createIndex(row, column);
    return sourceModel1->index(row, column, parent);
}
QModelIndex StringProxyModel::parent(const QModelIndex& index) const
{
    qDebug() << "parent";
  Q_UNUSED(index);
  return QModelIndex();
}
int StringProxyModel::rowCount(const QModelIndex& parent) const
{
    qDebug() << "row";
    qDebug()<< sourceModel1->rowCount();
    qDebug()<< "data8: row =" << parent.row() << " col=" << parent.column();
    if (!parent.isValid()) return -1;

return sourceModel1->rowCount();
}

int StringProxyModel::columnCount(const QModelIndex& parent) const
{
    qDebug() << "1";
  return 1;//sourceModel()->rowCount(parent);
}
QVariant StringProxyModel::data(const QModelIndex& index, int role) const
{
  if (!index.isValid()) return QVariant();
  qDebug()<< "data: row =" << index.row() << " col=" << index.column();
  qDebug() << sourceModel()->data(index, role);
  qDebug() << sourceModel1->data(index, role);
  QVariant r = sourceModel1->data(createIndex(index.row(),3),role);
  QVariant s = sourceModel1->data(createIndex(index.row(),4),role);
  return "a";//sourceModel()->data(index, role);
}
QVariant StringProxyModel::headerData(int section,Qt::Orientation orientation, int role) const
{
    qDebug() << "Exercise";
    return "Exercise";
}

