#include "globalvoiceseq.h"
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>

std::vector<CVoiceSeq> voiceSeq;//sequences

void compositionSpace::createComposition()
{
  //Variables

  /*util*/       int   util2ThirdOfCycleAmount;
  /*util*/       int   utilCCInt;

  //Init

  /*inten*/      float phaseOfIntensitySine=0.;
  /*inten*/      int   intensityAureanProg=0;
  /*inten*/      int   intenHistoryX=0;
  /*inten*/      int   intenHistoryY=0;
  /*counter*/    int   createCompositionUtilCounter=0;//Global index

  /*GlobalParam*/      cyclePhase=0;
  /*GlobalParam*/      addtoSineIWNeedChange.reserve(TOTALVOICEAMOUNT);
  /*GlobalParam*/      totalLength=0;

  for(int i=0;i<TOTALVOICEAMOUNT;i++){
  /*GlobalParam*/      addtoSineIWNeedChange[i] = 0;
  }

  /*GlobalParam*/      loopLimit = 0;

  /*GlobalParam*/      totalVoiceAmount = TOTALVOICEAMOUNT;


  /*GlobalParam*/      globalIntensityX.reserve(2000);
  /*GlobalParam*/      globalIntensityY.reserve(2000);//dummy

  /*GlobalParam*/      compositionInfo.reserve(3);
                       //reserve seq



  //Generation

  cycleAmount=(3+(rand()%4))*2; //amount of cycles
  std::cout << "cycles " << cycleAmount << std::endl;

  //This needs to be initialized after the number of cycles has been decided
  /*GlobalParam*/      compositionInfo[0].reserve(cycleAmount);
                       //[0] is the amount of voices
  /*GlobalParam*/      compositionInfo[1].reserve(cycleAmount);
                       //[1] is the length of the cycle in notes
  /*GlobalParam*/      compositionInfo[2].reserve(cycleAmount);
                       //[2] is the length of the cycle in repetitions

  /*GlobalParam2*/     voiceSeq.reserve(totalVoiceAmount);

  /*util*/ util2ThirdOfCycleAmount=(int)(2*cycleAmount/3);

  for(int i=0;i<cycleAmount;i++){

    compositionInfo[0][i]=std::min((int)(intensityAureanProg/8),3)+1;//voices
    std::cout << "voices " << compositionInfo[0][i] << std::endl;

    /*util*/utilCCInt=rand()%(((intensityAureanProg%3)+2)+2);
    compositionInfo[1][i]=2+utilCCInt;//notes
    /*length*/totalLength+=compositionInfo[1][i];//add notes to total length

    /*util*/utilCCInt=rand()%3;
    compositionInfo[2][i]=2+utilCCInt;//repetitions

    // golden ratio * sine + random

    for(int ii=0;ii<compositionInfo[1][i];ii++){

      //Golden ratio

      //The intensity grows for the first 2/3 parts of the piece and then
      //decreases twice as fast until the end.
      //As the amount of notes per cycle is not allways the same there is
      //still some variation in such a predcitable pattern

      /*util*/utilCCInt=i>util2ThirdOfCycleAmount;
      /*util*/utilCCInt=utilCCInt==1 ?
        intensityAureanProg-2 : intensityAureanProg+1;
      intensityAureanProg=std::min(std::max(utilCCInt,0),40);//clamp

      // sine

      //the frequency of the phase is actually the amount of cycles

      phaseOfIntensitySine=fmod(phaseOfIntensitySine+(1./cycleAmount),1.0);

      //random offset

      //brownian motion limited to a certain area
      //X
      /*util*/utilCCInt=rand()%5;
      /*util*/utilCCInt=intenHistoryX-2+rand()%5;
      intenHistoryX=std::min(std::max(utilCCInt,-20),20);

      //Y
      /*util*/utilCCInt=rand()%5;
      /*util*/utilCCInt=intenHistoryY-2+rand()%5;
      intenHistoryY=std::min(std::max(utilCCInt,-20),20);


      //Absolute Global Intensity
      /*util*/utilCCInt=(int)(intensityAureanProg*3*sin(phaseOfIntensitySine));
      /*util*/utilCCInt=intenHistoryX+utilCCInt;
      /*util*/utilCCInt=std::max(std::min(utilCCInt,30),-30);
      globalIntensityX[createCompositionUtilCounter]=utilCCInt;

      /*util*/utilCCInt=(int)(intensityAureanProg*3*sin(phaseOfIntensitySine));
      /*util*/utilCCInt=intenHistoryY+utilCCInt;
      /*util*/utilCCInt=std::max(std::min(utilCCInt,30),-30);
      globalIntensityY[createCompositionUtilCounter]=utilCCInt;

      /*counter*/createCompositionUtilCounter++;//Global index

    }//end for notes per cycle

  }//end for cycleAmount

  //Fill those voiceSeqs
  for(int i=0;i<totalVoiceAmount;i++){
    voiceSeq[i].setParam(i,1.0+((float)i/2.0));
    voiceSeq[i].fill(totalLength);
  }
}
