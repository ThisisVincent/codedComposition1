#include <vector>
#include "cvoiceseq.h"
#include "globalwavetables.h"


#pragma once

#ifndef GLOBALVOICESEQ_H

#define GLOBALVOICESEQ_H

// #include "globalwavetables.h"

// #include "cvwavetable.h"

extern std::vector<CVoiceSeq> voiceSeq;//sequences


namespace compositionSpace{
  void createComposition();
}

#endif
