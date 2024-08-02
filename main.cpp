#include <stdlib.h>
#include <portaudio.h>
#include <stdio.h>
#include <iostream>
#include <cmath> // Include for std::abs
#include <cstring>
#define SAMPLE_RATE 44100
#define FRAMES_PER_BUFFER 512 // the size of the buffer (captures the amplitude of the waveform based on the sample rate)

using namespace std;

static void checkErr(PaError err){
    if (err != paNoError){
        printf("PortAudio error: %s\n", Pa_GetErrorText(err));
        exit(EXIT_FAILURE);
    }
}

static inline float max(float a, float b){
    return a > b ? a : b;
}

static int testCallback(
    const void* inputBuffer, void* outputBuffer, unsigned long framesPerBuffer,
    const PaStreamCallbackTimeInfo* timeinfo, PaStreamCallbackFlags statusFlags, void* userData)
{
    float* in = (float*)inputBuffer;
    (void)outputBuffer;

    int dispSize = 100;
    cout << "\r";

    float vol_l = 0;
    float vol_r = 0;

    for (unsigned long i = 0; i < framesPerBuffer * 2; i+=2)
    {
        vol_l = max(vol_l, std::abs(in[i]));
        vol_r = max(vol_r, std::abs(in[i+1]));
    }

    for (int i = 0; i < dispSize; i++)
    {
        float barProportion = i / (float)dispSize;

        if(barProportion <= vol_l && barProportion <= vol_r){
            cout << ("█");
        }
        else if(barProportion <= vol_l){
            cout << ("▀");
        }
        else if (barProportion <= vol_r)
        {
            cout << ("▄");
        }
        else{
            cout << " ";
        }
    }
    
    fflush(stdout);

    return 0;
}

int main(){
    PaError err = Pa_Initialize();
    if (err != paNoError) {
        std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
        return 1;
    }

    int numDevices = Pa_GetDeviceCount();
    if (numDevices < 0) {
        std::cerr << "PortAudio error: " << Pa_GetErrorText(numDevices) << std::endl;
        Pa_Terminate();
        return 1;
    }

    for (int i = 0; i < numDevices; ++i) {
        const PaDeviceInfo* deviceInfo = Pa_GetDeviceInfo(i);
        if (deviceInfo) {
            std::cout << "Device No: " << i << std::endl;
            std::cout << "Device name: " << deviceInfo->name << std::endl;
            std::cout << "Max input channels: " << deviceInfo->maxInputChannels << std::endl;
            std::cout << "Max output channels: " << deviceInfo->maxOutputChannels << std::endl;
            std::cout << "Default sample rate: " << deviceInfo->defaultSampleRate << std::endl;
            std::cout << std::endl;
        }
    }

    // choose device input by number
    int device;
    cout << "Enter Device Number: " << endl;
    std::cin >> device;

    PaStreamParameters inputParameters;
    PaStreamParameters outputParameters;

    memset(&inputParameters, 0, sizeof(inputParameters));
    inputParameters.channelCount = 2; // work with stereo input 1,2
    inputParameters.device = device;
    inputParameters.hostApiSpecificStreamInfo = NULL;
    inputParameters.sampleFormat = paFloat32;
    inputParameters.suggestedLatency = Pa_GetDeviceInfo(device)->defaultLowInputLatency;

    memset(&outputParameters, 0, sizeof(outputParameters));
    outputParameters.channelCount = 2; // work with stereo input 1,2
    outputParameters.device = device;
    outputParameters.hostApiSpecificStreamInfo = NULL;
    outputParameters.sampleFormat = paFloat32;
    outputParameters.suggestedLatency = Pa_GetDeviceInfo(device)->defaultHighOutputLatency;

    PaStream* stream;

    err = Pa_OpenStream(
        &stream,
        &inputParameters,
        &outputParameters,
        SAMPLE_RATE,
        FRAMES_PER_BUFFER,
        paNoFlag,
        testCallback,
        NULL
    );

    checkErr(err);

    err = Pa_StartStream(stream);
    checkErr(err);

    Pa_Sleep(10*1000);

    err = Pa_StopStream(stream);
    checkErr(err);

    err = Pa_CloseStream(stream);
    checkErr(err);

    err = Pa_Terminate();
    if (err != paNoError) {
        std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
        return 1;
    }

    return EXIT_SUCCESS;
}
