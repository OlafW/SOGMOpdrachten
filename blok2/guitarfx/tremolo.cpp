#include "tremolo.h"
#include <math.h>


Tremolo::Tremolo() //Constructor
{
    Amplifier();
    this->modDepth = 0.75;
    this->modFreq = 0.5;
}

void Tremolo::setModFreq(float modFreq) {
  this->modFreq = modFreq;
}



void Tremolo::setModDepth(float modDepth) {
  this->modDepth = modDepth;
}



void Tremolo::process()
{
  tremBuffer = getBuffer();
  for (int i = 0; i < BUFFERSIZE; i++) {
    tremBuffer[i] = tremBuffer[i] *sin(modFreq) * modDepth;
  }
  
  cout << "Tremolo: " << "modDepth = " << modDepth << endl;
  cout << "Tremolo: " << "modFreq = " << modFreq << endl;
  cout << "Tremolo: " << "processing...." << endl;

}