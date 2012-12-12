#ifndef DEVICELIST_H
#define DEVICELIST_H

#include <QAbstractListModel>

class DeviceList : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit DeviceList(QObject *parent = 0);
    ~DeviceList();
    
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
signals:
    
public slots:
    
};

#endif // DEVICELIST_H
