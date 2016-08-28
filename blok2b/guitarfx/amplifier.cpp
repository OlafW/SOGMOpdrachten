#include "amplifier.hpp"

Amplifier::Amplifier() {
    gain = 1.0;
}

void Amplifier::process(float* buffer) {
    for (unsigned long n=0; n<FRAMES; n++) {
        for (int k=0; k<CHANNELS; k++) {
            buffer[n*CHANNELS+k] = clip(buffer[n*CHANNELS+k] * gain, -1.0, 1.0);
        }
    }
}

void Amplifier::setGain(float gain) {
    this->gain = gain;
}

float Amplifier::clip(float x, float min, float max) {
    if (x > max) return 1.0;
    else if (x < min) return -1.0;
    else return x;
}
