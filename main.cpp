#include <stdlib.h>
#include <portaudio.h>
#include <stdio.h>
#include <iostream>

using namespace std;

static void checkErr(PaError err){
    
    if (err != paNoError){
        printf("PortAudio error: %s\n", Pa_GetErrorText(err));
        exit(EXIT_FAILURE);
    }
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
            std::cout << "Device name: " << deviceInfo->name << std::endl;
            std::cout << "Max input channels: " << deviceInfo->maxInputChannels << std::endl;
            std::cout << "Max output channels: " << deviceInfo->maxOutputChannels << std::endl;
            std::cout << "Default sample rate: " << deviceInfo->defaultSampleRate << std::endl;
            std::cout << std::endl;
        }
    }

    err = Pa_Terminate();
    if (err != paNoError) {
        std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
        return 1;
    }


    return EXIT_SUCCESS;
}

