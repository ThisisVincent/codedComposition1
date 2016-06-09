#include "globalwavetables.h"
#include <math.h>

std::vector<CVWavetable> waveTable;//wavetable

std::vector<std::vector<int> > compositionInfo;
//notes per cycle,repetitions per cycle,number of active voices per seq

int cycleAmount;//amount of cycles

int totalVoiceAmount; // amount of voices

int loopLimit;// util to trigger transition

int totalLength;

std::vector<int> globalIntensityX;
std::vector<int> globalIntensityY;

int cyclePhase;

std::vector<int> addtoSineIWNeedChange;


void waveTableSpace::initWaveTables(){
  waveTable.reserve(5);
  for(int i=0;i<5;i++){
    waveTable[i].init(i);
  }
}

float waveTableSpace::getFromWaveTable(float p,int wt){
  float fv = floor(BUFFERSIZE*p);//floorOfValue
  float fvp = fmod(floor(BUFFERSIZE*p)+1.0,BUFFERSIZE);//floorOfValuePlusOne
  float fpv =(BUFFERSIZE*p)-fv;//floatingPointOfValue

  float sfv = fpv * waveTable[wt].getValue(fv);//scaledFloorOfValue
  float sfvp = (1.0 - fpv) * waveTable[wt].getValue(fvp);//scaledFloorOfValuePlusOne

  return sfv + sfvp;

}

int waveTableSpace::getCompositionInfo(int typeInfo,int index){

  return compositionInfo[typeInfo][index];
}
