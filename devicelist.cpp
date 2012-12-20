#include <QDebug>
#include "devicelist.h"
#include "portaudio.h"

DeviceList::DeviceList(QObject *parent) :
    QAbstractListModel(parent)
{
    Pa_Initialize();
}

DeviceList::~DeviceList()
{
    Pa_Terminate();
}

int DeviceList::rowCount(const QModelIndex &parent) const
{
    (void)parent;
    int devCount = Pa_GetDeviceCount();

    if (devCount < 0)
        qWarning() << Pa_GetErrorText(devCount);

    return devCount;
}

QVariant DeviceList::data(const QModelIndex &index, int role) const
{
    if(role == Qt::DisplayRole) {
        const PaDeviceInfo *info = Pa_GetDeviceInfo(index.row());
        return QVariant(QString("%2: %1").arg(info->name).arg(Pa_GetHostApiInfo(info->hostApi)->name));
    } else
        return QVariant();
}
