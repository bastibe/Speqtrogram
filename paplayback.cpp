#include "paplayback.h"

PaPlayback::PaPlayback(QObject *parent) :
    QObject(parent),
    deviceIndex(0),
    hostApiIndex(0)
{
}

void PaPlayback::openSoundFile(std::string filename)
{
    soundFile = SndfileHandle(filename);
}

void PaPlayback::updateDevice(int deviceIdx)
{
    deviceIdx = Pa_HostApiDeviceIndexToDeviceIndex(hostApiIndex, deviceIdx);
}
