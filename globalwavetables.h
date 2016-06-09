
#include <vector>

#ifndef _GLOBALWAVETABLES_H

#define _GLOBALWAVETABLES_H

// #pragma once

#define BASEFREQ 110
#define SRATE 48000.0
#define BUFFERSIZE 4096.0
#define TOTALVOICEAMOUNT 4

#include <algorithm>

#include "cvwavetable.h"

// #include "cvoiceseq.h"

extern std::vector<CVWavetable> waveTable;//wavetable

extern std::vector<std::vector<int> > compositionInfo;
//notes per cycle,repetitions per cycle,number of active voices per seq

extern int cycleAmount;//amount of cycles

extern int totalVoiceAmount; // amount of voices

extern int loopLimit;// util to trigger transition

extern int totalLength;

extern int cyclePhase;

extern std::vector<int> addtoSineIWNeedChange;

extern std::vector<int> globalIntensityX;
extern std::vector<int> globalIntensityY;
//intensity, max =30, max vector length is 42.4265

namespace waveTableSpace{
  void initWaveTables();
  float getFromWaveTable(float p,int wt);
  int getCompositionInfo(int typeInfo,int index);

}

#endif
