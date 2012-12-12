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
    if(role == Qt::DisplayRole)
        return QVariant(Pa_GetDeviceInfo(index.row())->name);
    else
        return QVariant();
}
