#ifndef PAPLAYBACK_H
#define PAPLAYBACK_H

#include <QObject>
#include "sndfile.hh"
#include "portaudio.h"

class PaPlayback : public QObject
{
    Q_OBJECT
public:
    explicit PaPlayback(QObject *parent = 0);

    void openSoundFile(std::string filename);
    
signals:
    
public slots:
    inline void updateHostApi(int hostApiIdx) {hostApiIndex = hostApiIdx;}
    void updateDevice(int deviceIdx);

private:
    SndfileHandle soundFile;
    PaDeviceIndex deviceIndex;
    PaHostApiIndex hostApiIndex;
    
};

#endif // PAPLAYBACK_H
