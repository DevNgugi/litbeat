#ifndef AUDIOHANDLER_H
#define AUDIOHANDLER_H

#include <portaudio.h>

class AudioHandler {
public:
    AudioHandler();
    ~AudioHandler();

    bool Initialize();
    void Start();
    void Stop();

private:
    static int audioCallback(
        const void* inputBuffer, void* outputBuffer, unsigned long framesPerBuffer,
        const PaStreamCallbackTimeInfo* timeinfo, PaStreamCallbackFlags statusFlags, void* userData
    );
    PaStream* stream;
};

#endif // AUDIOHANDLER_H
