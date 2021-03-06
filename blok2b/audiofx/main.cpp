#include "audio_io.h"
#include "amplifier.hpp"
#include "tremolo.hpp"
#include "distortion.hpp"
#include "delay.hpp"
#include "biquad.hpp"
#include <signal.h>

Audio_IO audioStream;
bool quit = false;

void startAudio() {
    int input_device = 0;
    int output_device = 1;
    audioStream.set_mode(AUDIO_IO_READWRITE);
    audioStream.set_samplerate(SAMPLERATE);
    audioStream.set_nrofchannels(CHANNELS);
    audioStream.set_framesperbuffer(FRAMES);
    audioStream.initialise();
    audioStream.list_devices();
    // std::cout << "\nGive input device number: ";
    // std::cin >> input_device;
    audioStream.set_input_device(input_device);
    // std::cout << "Give output device number: ";
    // std::cin >> output_device;
    audioStream.set_output_device(output_device);
    audioStream.start_server();
}


void intHandler(int s) {
    quit = true;
    std::cout << "\n" << "quit" << std::endl;
}

int main (int argc, char* argv[]) {
    const int N = FRAMES * CHANNELS;
    float buffer[N];
    for (int n=0; n<N; n++) buffer[n] = 0.0;

    signal (SIGINT, intHandler);

    Amplifier amplifier;
    amplifier.setGain(1.0);

    Tremolo tremolo;
    tremolo.setModFreq(7.0);
    tremolo.setModDepth(0.25);

    Distortion distortion;
    distortion.setGain(20.0);

    Delay delay(1000);
    delay.setDelayTimeMs(500);
    delay.setFeedback(0.9);
    delay.setMix(0.5);

    Biquad biquad(LOWPASS, 5000, 0.9, 1.0);

    startAudio();

    while (!quit) {
        audioStream.read(buffer);
        amplifier.process(buffer);
        distortion.process(buffer);
        tremolo.process(buffer);
        delay.process(buffer);
        audioStream.write(buffer);
    }
    audioStream.finalise();

    return 0;
}
