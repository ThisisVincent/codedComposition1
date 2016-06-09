# codedComposition1

--------------------------------------------------------------------
Coded Composition                             [Vincent Pruijn Perez]
--------------------------------------------------------------------
--------------------------------------------------------------------
Build:
--------------------------------------------------------------------
  The makefile of this project contains only one target.
  Running 'make' will build the main program.
  This program needs JackAudio to run.
--------------------------------------------------------------------
--------------------------------------------------------------------
Concept:
--------------------------------------------------------------------
  The idea behind this project was to compose a multimedia
  (audiovisual) piece that would resemble life in the sense that it
  would be generated algorithmically, and develop its own world thru
  the development of the algorithm itself.
  The piece would be  constructed of cycles,  a structure where the
  material would be transformed in new iterations. The overall
  intensity would have a development in time similar to the golden
  ratio, where it would increase during the first 2/3 of the piece
  and then decrease in the last third. The intensity would be seen
  as a position in a two dimensional plane, having the form of a
  spiral that grows and then cringes while it moves in the space.
--------------------------------------------------------------------
--------------------------------------------------------------------
Aesthetic:
--------------------------------------------------------------------
  The aesthetics of this project would be references  to cellular
  growth. Being this represented by fractals in the video and by
  cellar variation in the audio. The audio is constructed of
  'voices' that play sine tones relating to a ratio assigned to
  the voice. The video would have transformations in the position
  with the help of feedback to emphasize the changes of cycle
--------------------------------------------------------------------
--------------------------------------------------------------------
Working:
--------------------------------------------------------------------
  Due to the lack of time to further develop this project, the
  current version of the composition consists only of audio. The
  generation is different from the concept, being the influence of
  the intensity not prominent enough to be notorious and with the
  cellar development being not as clear as it should be.
  Still, in this current state, it showcases the potential of the
  concept for further development.
--------------------------------------------------------------------
--------------------------------------------------------------------
System:
--------------------------------------------------------------------
  The code consists of 9 files:
    - main.cpp:Calls the initialization, generation and reproducing
      functions.
    - cvwavetable.h: declares the class cvwavetable (wavetables)
    - cvwavetable.cpp: defines the class cvwavetable and  the way
      wavetables can be initialized.
    - cvoiceseq.h: declares the  class cvoiceseq, this class includes
      the information over one voice, its generation on individual
      level and functions to allow the information to be traduced to
      audio
    - cvoiceseq.cpp: defines the class cvoiceseq and all its functions
    - globalvoiceseq.h: declares some global variables and the
      composition generating function.
    - globalvoiceseq.cpp: defines the composition generating function,
      which initializes most global variables and generates the overal
      structure and coordinates the generation inside the cvoiceseqs
    - globalwavetables.h: declares most global variables
    - globalwavetables.cpp: defines most global variables and the
      function that initializes the wavetable array that is used

--------------------------------------------------------------------
--------------------------------------------------------------------
