#include <vector>
#include <math.h>
#include <iostream>

#include <stdlib.h>
#include <jack/jack.h>
#include <jack/midiport.h>
#include <time.h>

#include "cvoiceseq.h"
#include "globalwavetables.h"


CVoiceSeq::CVoiceSeq(){
}

CVoiceSeq::~CVoiceSeq(){
}

void CVoiceSeq::setParam(int v,float r){

  voiceNumber=v;

  ratio=r;

}

void CVoiceSeq::fill(int totalLength){

  srand (time(NULL));
  //Variables
  int indexOfIntensity=0;
  int ttLength;
  int localIntensityY=0;
  int localIntensityX=0;
  float param[9];

  sineFreq.reserve(totalLength);
  sineInfo.reserve(totalLength*2);


  for(int i = 0; i < cycleAmount; i++){
    for(int x = 0; x < 3; x++){
      param[x*3]=rand()%2;//direction
      param[(x*3)+1]=rand()%5;//muliplier
      param[(x*3)+2]=rand()%4;//displace
    }
    for(int ii = 0; ii < waveTableSpace::getCompositionInfo(1,i); ii++){

      localIntensityY=globalIntensityY[indexOfIntensity];

      localIntensityX=globalIntensityX[indexOfIntensity];

      ttLength=((30-std::min(localIntensityX,29))/5)+1+((TOTALVOICEAMOUNT-voiceNumber)*2);

      sineFreq[indexOfIntensity]=fillAlgorythm(indexOfIntensity,
        param[0],param[1]+1,1,8,param[2])*ratio*BASEFREQ;
        //freq

      sineInfo[indexOfIntensity*2]=fillAlgorythm(indexOfIntensity,
        param[3],param[4]+1,1,3,param[5]);
        //wavetable types!!!! max 4!!!!!!!!

      sineInfo[(indexOfIntensity*2)+1]=fillAlgorythm(indexOfIntensity,
        param[6],param[7]+1,1,5,param[8])*(SRATE/10)*ttLength;
        //length of envelope

      indexOfIntensity++;

    }
  }

}

int CVoiceSeq::fillAlgorythm (int number,int direction,
  int multiplier,int min,int modulo,int displace) {

    int directionFrag=(direction==1) ? number:(modulo-number);
    int modFrag=(abs(((directionFrag*multiplier)+displace)%modulo)+min);
    return modFrag;

}

float CVoiceSeq::getSineFreq(int index){

  return (float)sineFreq[index]/(float)SRATE;

}

int CVoiceSeq::getSineInfo(int typeInfo,int index){
  //typeInfo = 0 or 1
  return sineInfo[(index*2)+typeInfo];

}

int CVoiceSeq::getSineToneIndex(){

  return std::min(sineToneIndex+addToSineToneIndex,totalLength);

}

void CVoiceSeq::augmentSineToneIndex(){

  int utilModulo=waveTableSpace::getCompositionInfo(1,localCyclePhase);
  sineToneIndex++;
  sineToneIndex=sineToneIndex%utilModulo;

}

void CVoiceSeq::augmentAddToSineToneIndex(){

  int utilAdd=waveTableSpace::getCompositionInfo(1,localCyclePhase);
  addToSineToneIndex+=utilAdd;

}

float CVoiceSeq::process(){


  processSine();

  processEnvelope();


  // checkLoopLimit();

  // checkAddToSineToneNeedChange();

  if(getSineInfo(1,getSineToneIndex())==0){
    std::cout<<"zero"<<std::endl;
  }
  if( voiceNumber <= waveTableSpace::getCompositionInfo(0,localCyclePhase)){
    float scaledEnvelopePhase = (float)phaseOfEnvelope/
      (float)getSineInfo(1,getSineToneIndex());
    float sineVal = waveTableSpace::getFromWaveTable(phaseOfSine,2);
    float envelopeVal = waveTableSpace::getFromWaveTable(
      scaledEnvelopePhase,getSineInfo(0,getSineToneIndex()));
    return sineVal*envelopeVal/4.;
  }
  else{
      return 0.;
  }

}

void CVoiceSeq::processSine(){

  phaseOfSine+=getSineFreq(getSineToneIndex());
  if(phaseOfSine>1.0){
    phaseOfSine=fmod(phaseOfSine,1.0);
  }

}

void CVoiceSeq::processEnvelope(){
  int utilaccum=0;

  phaseOfEnvelope++;

  if(phaseOfEnvelope==getSineInfo(1,getSineToneIndex())){

    augmentSineToneIndex();
    phaseOfEnvelope=0;

    //if((canAdvance==TOTALVOICEAMOUNT)||(addtoSineIWNeedChange[voiceNumber]!=0)){
      addtoSineIWNeedChange[voiceNumber]++;
    //}
    for(int i=0;i<TOTALVOICEAMOUNT;i++){
      utilaccum+=(addtoSineIWNeedChange[i]
        > waveTableSpace::getCompositionInfo(2,localCyclePhase));
    }
    if(utilaccum==TOTALVOICEAMOUNT){
      cyclePhase++;
      std::cout<<"Voices: "<<waveTableSpace::getCompositionInfo(0,localCyclePhase)
      << " cycle: " << cyclePhase   << " / " << cycleAmount <<std::endl;
      localCyclePhase=cyclePhase;
      addtoSineIWNeedChange[voiceNumber]=0;
    }
    if(cyclePhase!=localCyclePhase){
      localCyclePhase=cyclePhase;
      addtoSineIWNeedChange[voiceNumber]=0;
    }
  }

}
