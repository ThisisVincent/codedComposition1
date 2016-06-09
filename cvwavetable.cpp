#include <vector>
#include <math.h>
#include <iostream>
#include <stdlib.h>
#include "cvwavetable.h"


#define WAVETABLELENGTH 4096


CVWavetable::CVWavetable(){
}

CVWavetable::~CVWavetable(){
}

void CVWavetable::init(int typeCurve){
  std::cout<< "init" << std::endl;
  waveTableArray.reserve(WAVETABLELENGTH);
   if(typeCurve==0){
    for (int i = 0; i < WAVETABLELENGTH; i++){
      waveTableArray[i]=sin(M_PI*2.0*float(i)/float(WAVETABLELENGTH));
      waveTableArray[i]=(waveTableArray[i]>0.) ? waveTableArray[i] : 0.;
    }
  }else if(typeCurve==1){
    for (int i = 0; i < WAVETABLELENGTH; i++){
      waveTableArray[i]=sin(M_PI*float(i)/float(WAVETABLELENGTH));
    }
  }else if(typeCurve==2){
    for (int i = 0; i < WAVETABLELENGTH; i++){
      waveTableArray[i]=sin(M_PI*2.0*float(i)/float(WAVETABLELENGTH));

    }
  }else if(typeCurve==3){
    for (int i = 0; i < WAVETABLELENGTH; i++){
      waveTableArray[i]=pow(sin(M_PI*float(i)/float(WAVETABLELENGTH)),0.5);
    }
  }else if(typeCurve==4){
    for (int i = 0; i < WAVETABLELENGTH; i++){
      if(i<(5*WAVETABLELENGTH/6)){
        waveTableArray[i]=std::min((float)i/480.,1.0);
      }else{
        waveTableArray[i]=std::min(std::max(1.-((i-(5*WAVETABLELENGTH/6))/480.),0.0),1.);
      }

    }
  }
}

float CVWavetable::getValue(int index){
  return waveTableArray[index];
}
