#include <QDebug>
#include <portaudio.h>
#include "devicelist.h"

DeviceList::DeviceList(QObject *parent) :
    QAbstractListModel(parent)
{
}

DeviceList::~DeviceList()
{
}

int DeviceList::rowCount(const QModelIndex &parent) const
{
    (void)parent;
    int devCount = Pa_GetDeviceCount();

    if (devCount < 0)
        qWarning() << Pa_GetErrorText(devCount);

    for(int i=0; i<Pa_GetDeviceCount(); i++) {
        const PaDeviceInfo *info = Pa_GetDeviceInfo(i);
        if(info->hostApi != currentHostApi)
            devCount--;
    }

    if (devCount <= 0)
        qWarning() << "No devices for selected API found.";

    return devCount;
}

QVariant DeviceList::data(const QModelIndex &index, int role) const
{
    if(role == Qt::DisplayRole) {
        const PaDeviceIndex devIndex = Pa_HostApiDeviceIndexToDeviceIndex(currentHostApi, index.row());
        const PaDeviceInfo *info = Pa_GetDeviceInfo(devIndex);
        return QVariant(QString("%1").arg(info->name));
    } else
        return QVariant();
}

void DeviceList::updateHostApi(int selectedApi)
{
    beginResetModel();
    currentHostApi = selectedApi;
    endResetModel();
}
