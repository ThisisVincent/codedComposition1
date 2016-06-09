CPP = g++
CFLAGS = -I/usr/local/include -Wall -I../include

main: main.o cvwavetable.o cvoiceseq.o globalvoiceseq.o globalwavetables.o
	$(CPP) -o $@ $(CFLAGS) main.o globalwavetables.o cvwavetable.o cvoiceseq.o globalvoiceseq.o -lpthread -ljack



.cpp.o:
	$(CPP) -c $< $(CFLAGS)

clean:
	rm -f *.o
	rm -f `find . -perm +111 -type f`
