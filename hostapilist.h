#ifndef HOSTAPILIST_H
#define HOSTAPILIST_H

#include <QAbstractListModel>

class HostApiList : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit HostApiList(QObject *parent = 0);
    ~HostApiList();

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
signals:

public slots:

};
#endif // HOSTAPILIST_H
