#include "audio_io.h"
#include "sndfile_io.h"
#include "beattracking.h"

#define SAMPLERATE	44100
#define CHANNELS	1
#define N  1024     // Framesize


int main(int argc, char** argv) {
    float* buffer = new float[N];
    float peakThreshold = 0.968;
    int step = 64;

    // //Start audiostream
    // Audio_IO audioStream(SAMPLERATE, CHANNELS);
    // int input_device;
    // audioStream.set_mode(AUDIO_IO_READONLY);
    // audioStream.set_framesperbuffer(N);
    // audioStream.initialise();
    // audioStream.list_devices();
    // std::cout << "\nGive input device number: ";
    // std::cin >> input_device;
    // audioStream.set_input_device(input_device);
    // audioStream.start_server();
    // audioStream.read(buffer);   //Blocking I/O

    SNDFile sndfile;
    sndfile.readFile("./testsig.wav");
    unsigned long bufSize = sndfile.getBufferSize();

    float* x_norm = normalize(sndfile.getBuffer(), bufSize);
    float* y = autoCorrelate(x_norm, bufSize, step);
    float period = findPeriod(y, bufSize, peakThreshold);
    float bpm = 1.0 / (period / SAMPLERATE) * 60;
    std::cout << "BPM: " << bpm << std::endl;

    //audioStream.finalise();
    delete[] buffer;
    delete[] x_norm;
    delete[] y;
    return 0;
}

/*
make
beatTracker
gnuplot
plot "peaks.txt" with lines
*/
