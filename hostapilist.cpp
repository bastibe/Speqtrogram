#include <QDebug>
#include <portaudio.h>
#include "hostapilist.h"

HostApiList::HostApiList(QObject *parent) :
    QAbstractListModel(parent)
{
}

HostApiList::~HostApiList()
{
}

int HostApiList::rowCount(const QModelIndex &parent) const
{
    (void)parent;
    int apiCount = Pa_GetHostApiCount();

    if (apiCount < 0)
        qWarning() << Pa_GetErrorText(apiCount);

    return apiCount;
}

QVariant HostApiList::data(const QModelIndex &index, int role) const
{
    if(role == Qt::DisplayRole) {
        const PaHostApiInfo *info = Pa_GetHostApiInfo(index.row());
        return QVariant(QString("%1").arg(info->name));
    } else
        return QVariant();
}
