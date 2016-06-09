#include <vector>
#include <jack/jack.h>
#include <jack/midiport.h>

#ifndef CVOOCESEQ_H
#define CVOOCESEQ_H

class CVoiceSeq{
public:
    CVoiceSeq();
    ~CVoiceSeq();

    void setParam(int v,float r);
    void fill(int totalLength);

    float process();

  protected:
    int fillAlgorythm(int number,int direction,int multiplier,int min,int modulo,int displace);
    float ratio;
    int length;

    float phaseOfSine;
    int phaseOfEnvelope;

    std::vector<float> sineFreq;
    std::vector<int> sineInfo;

    int voiceNumber;
    int cvsTotalLength;

    int localLoopLimit;
    int localLoopLimitCounter;


    float getSineFreq(int index);
    int getSineInfo(int typeInfo,int index);

    int getSineToneIndex();
    void augmentSineToneIndex();
    void augmentAddToSineToneIndex();

    int localCyclePhase;

    void processSine();
    void processEnvelope();

    int sineToneIndex;//sineIW
    int addToSineToneIndex;//addToSineIW

    int needActivation;

};
#endif
