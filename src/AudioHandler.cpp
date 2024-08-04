#include "AudioHandler.h"
#include <iostream>
#include <cstring>
#include <cmath>

#define SAMPLE_RATE 44100
#define FRAMES_PER_BUFFER 512

AudioHandler::AudioHandler() : stream(nullptr) {}

AudioHandler::~AudioHandler() {
    Stop();
}

bool AudioHandler::Initialize() {
    PaError err = Pa_Initialize();
    if (err != paNoError) {
        std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
        return false;
    }
    return true;
}

void AudioHandler::Start() {
    PaStreamParameters inputParameters;
    PaStreamParameters outputParameters;

    memset(&inputParameters, 0, sizeof(inputParameters));
    inputParameters.channelCount = 2;
    inputParameters.device = Pa_GetDefaultInputDevice();
    inputParameters.hostApiSpecificStreamInfo = NULL;
    inputParameters.sampleFormat = paFloat32;
    inputParameters.suggestedLatency = Pa_GetDeviceInfo(inputParameters.device)->defaultLowInputLatency;

    memset(&outputParameters, 0, sizeof(outputParameters));
    outputParameters.channelCount = 2;
    outputParameters.device = Pa_GetDefaultOutputDevice();
    outputParameters.hostApiSpecificStreamInfo = NULL;
    outputParameters.sampleFormat = paFloat32;
    outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultHighOutputLatency;

    PaError err = Pa_OpenStream(
        &stream,
        &inputParameters,
        &outputParameters,
        SAMPLE_RATE,
        FRAMES_PER_BUFFER,
        paNoFlag,
        audioCallback,
        NULL
    );
    if (err != paNoError) {
        std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
        return;
    }

    err = Pa_StartStream(stream);
    if (err != paNoError) {
        std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
        return;
    }
}

void AudioHandler::Stop() {
    if (stream) {
        PaError err = Pa_StopStream(stream);
        if (err != paNoError) {
            std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
        }

        err = Pa_CloseStream(stream);
        if (err != paNoError) {
            std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
        }

        Pa_Terminate();
        stream = nullptr;
    }
}

int AudioHandler::audioCallback(
    const void* inputBuffer, void* outputBuffer, unsigned long framesPerBuffer,
    const PaStreamCallbackTimeInfo* timeinfo, PaStreamCallbackFlags statusFlags, void* userData
) {
    float* in = (float*)inputBuffer;
    (void)outputBuffer;

    int dispSize = 100;
    std::cout << "\r";

    float vol_l = 0;
    float vol_r = 0;

    for (unsigned long i = 0; i < framesPerBuffer * 2; i += 2) {
        vol_l = std::max(vol_l, std::abs(in[i]));
        vol_r = std::max(vol_r, std::abs(in[i + 1]));
    }

    for (int i = 0; i < dispSize; i++) {
        float barProportion = i / (float)dispSize;

        if (barProportion <= vol_l && barProportion <= vol_r) {
            std::cout << ("█");
        }
        else if (barProportion <= vol_l) {
            std::cout << ("▀");
        }
        else if (barProportion <= vol_r) {
            std::cout << ("▄");
        }
        else {
            std::cout << " ";
        }
    }

    std::fflush(stdout);

    return 0;
}
