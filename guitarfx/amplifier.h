#ifndef _AMPLIFIER_H_
#define _AMPLIFIER_H_

#include <iostream>

using namespace std;


#define BUFFERSIZE 10

class Amplifier {

public:
  void setLevel(float level);
  float showLevel();
  void readSamples(float buffer[]);
  void processSamples();
  float* writeSamples();

private:
  float level;
  float* buffer;

}; //Amplifier class

#endif
