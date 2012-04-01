#ifndef STRINGPROXYMODEL_H
#define STRINGPROXYMODEL_H


#include <QAbstractProxyModel>

class StringProxyModel : public QAbstractProxyModel {
    Q_OBJECT
public:
    StringProxyModel(QObject *parent = 0);

    void setSourceModel(QAbstractTableModel *sourceModel);

    QAbstractTableModel *sourceModel1;

    virtual QModelIndex	mapFromSource(const QModelIndex& sourceIndex) const;
    virtual QModelIndex mapToSource(const QModelIndex& proxyIndex) const;

    virtual QModelIndex index(int, int,const QModelIndex& parent = QModelIndex()) const;
    virtual QModelIndex parent(const QModelIndex& index) const;
    virtual int rowCount(const QModelIndex& parent) const;
    virtual int columnCount(const QModelIndex& parent) const;
    virtual QVariant data(const QModelIndex& index,int role = Qt::DisplayRole) const;

    virtual QVariant headerData(int section,Qt::Orientation orientation,int role = Qt::DisplayRole) const;
};

#endif // STRINGPROXYMODEL_H
