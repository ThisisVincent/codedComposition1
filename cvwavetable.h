#include <vector>

#ifndef CVWAVETABLE_H
#define CVWAVETABLE_H

class CVWavetable{
public:
  CVWavetable();
  ~CVWavetable();
  void init(int typeCurve);
  float getValue(int index);
protected:
  std::vector <float> waveTableArray;
  //std::vector<std::vector<float> > waveTableArray(5 ,std::vector<float>(4096));
};
#endif
