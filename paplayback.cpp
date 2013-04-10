#include "paplayback.h"
#include <QDebug>

static int streamCallback(  const void *inputBuffer, void *outputBuffer,
                            unsigned long framesPerBuffer,
                            const PaStreamCallbackTimeInfo* timeInfo,
                            PaStreamCallbackFlags statusFlags,
                            void *userData )
{
    (void)inputBuffer;
    (void)timeInfo;
    return ((PaPlayback*)userData)->playSamples((float*)outputBuffer, framesPerBuffer, statusFlags);
}

PaPlayback::PaPlayback(QObject *parent) :
    QObject(parent),
    stream(NULL),
    soundFile(),
    deviceIndex(0),
    hostApiIndex(0)
{
    Pa_Initialize();
}

PaPlayback::~PaPlayback()
{
    Pa_Terminate();
}

void PaPlayback::openSoundFile(std::string filename)
{
    if (stream) {
        PaError err = Pa_CloseStream(stream);
        if (err) {
            qDebug() << Pa_GetErrorText(err);
        }
        stream = NULL;
    }
    soundFile = SndfileHandle(filename);
    if (soundFile.error()) {
        qDebug() << soundFile.strError();
    }
    emit isPlaying(false);
}

int PaPlayback::playSamples(float *outBuffer, long long numFrames, PaStreamCallbackFlags flags)
{
    (void)flags;
    sf_count_t readFrames = soundFile.readf(outBuffer, numFrames);
    int channels = soundFile.channels();
    if (readFrames < numFrames) {
        for (long long i=readFrames; i < numFrames; i++) {
            for (long long c=0; c < channels; c++) {
                outBuffer[i*channels+c] = 0.f;
            }
        }
        return paComplete;
        emit isPlaying(false);
    } else {
        return paContinue;
    }
}

void PaPlayback::updateDevice(int deviceIdx)
{
    deviceIndex = Pa_HostApiDeviceIndexToDeviceIndex(hostApiIndex, deviceIdx);
}

void PaPlayback::playPause()
{
    if (stream == NULL) {
        PaStreamParameters outputParameters = {
            deviceIndex,
            soundFile.channels(),
            paFloat32,
            0, NULL
        };
        PaError err = Pa_OpenStream(&stream, NULL, &outputParameters, soundFile.samplerate(), 0 , paNoFlag,
                                    streamCallback, (void*)this);
        if (err) {
            qDebug() << Pa_GetErrorText(err);
        }
        err = Pa_StartStream(stream);
        if (err) {
            qDebug() << Pa_GetErrorText(err);
        }
        emit isPlaying(true);
    } else if (Pa_IsStreamStopped(stream)) {
        PaError err = Pa_StartStream(stream);
        if (err) {
            qDebug() << Pa_GetErrorText(err);
        }
        emit isPlaying(true);
    } else {
        PaError err = Pa_StopStream(stream);
        if (err) {
            qDebug() << Pa_GetErrorText(err);
        }
        emit isPlaying(false);
    }
}

void PaPlayback::fastForward()
{

}

void PaPlayback::rewind()
{

}
