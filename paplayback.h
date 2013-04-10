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
    ~PaPlayback();

    void openSoundFile(std::string filename);
    int playSamples(float *outBuffer, long long numFrames, PaStreamCallbackFlags flags);
    
signals:
    void isPlaying(bool yesNo);
    
public slots:
    inline void updateHostApi(int hostApiIdx) {hostApiIndex = hostApiIdx;}
    void updateDevice(int deviceIdx);
    void playPause();
    void fastForward();
    void rewind();

private:
    PaStream *stream;
    SndfileHandle soundFile;
    PaDeviceIndex deviceIndex;
    PaHostApiIndex hostApiIndex;
};

#endif // PAPLAYBACK_H
