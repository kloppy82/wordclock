CFLAGS = -O -Wall -Wextra -Werror

all: wc.exe wc24h-tables-de.txt wc24h-tables-pl.txt wc12h-tables-ch1.txt wc12h-tables-ch2.txt wc12h-tables-de.txt wc12h-tables-en1.txt \
     wc12h-tables-en2.txt wc12h-tables-fr.txt wc12h-tables-se.txt

wc.exe: wc.c tables-gen.h
	cc $(CFLAGS) wc.c -o wc.exe

wc24h-tables-de.txt: make-tables24h-de
	./make-tables24h-de

wc24h-tables-pl.txt: make-tables24h-pl
	./make-tables24h-pl

wc12h-tables-ch1.txt: make-tables12h-ch1
	./make-tables12h-ch1

wc12h-tables-ch2.txt: make-tables12h-ch2
	./make-tables12h-ch2

wc12h-tables-de.txt: make-tables12h-de
	./make-tables12h-de

wc12h-tables-en1.txt: make-tables12h-en1
	./make-tables12h-en1

wc12h-tables-en2.txt: make-tables12h-en2
	./make-tables12h-en2

wc12h-tables-fr.txt: make-tables12h-fr
	./make-tables12h-fr

wc12h-tables-se.txt: make-tables12h-se
	./make-tables12h-se

make-tables24h-de: make-tables24h-de.o tables24h-de.o
	cc make-tables24h-de.o tables24h-de.o -o make-tables24h-de

make-tables24h-de.o: make-tables.c tables24h-de.h tables-gen.h
	cc $(CFLAGS) -DWCLOCK24H_DE=1 -c make-tables.c -o make-tables24h-de.o

tables24h-de.o: tables24h-de.c tables24h-de.h tables-gen.h
	cc $(CFLAGS) -DWCLOCK24H_DE=1 -c tables24h-de.c

make-tables24h-pl: make-tables24h-pl.o tables24h-pl.o
	cc make-tables24h-pl.o tables24h-pl.o -o make-tables24h-pl

make-tables24h-pl.o: make-tables.c tables24h-pl.h tables-gen.h
	cc $(CFLAGS) -DWCLOCK24H_PL=1 -c make-tables.c -o make-tables24h-pl.o

tables24h-pl.o: tables24h-pl.c tables24h-pl.h tables-gen.h
	cc $(CFLAGS) -DWCLOCK24H_PL=1 -c tables24h-pl.c

make-tables12h-ch1: make-tables12h-ch1.o tables12h-ch1.o
	cc make-tables12h-ch1.o tables12h-ch1.o -o make-tables12h-ch1

make-tables12h-ch1.o: make-tables.c tables12h-ch1.h tables-gen.h
	cc $(CFLAGS) -DWCLOCK24H=0 -DWCLOCK12H_CH1 -c make-tables.c -o make-tables12h-ch1.o

tables12h-ch1.o: tables12h-ch1.c tables12h-ch1.h tables-gen.h
	cc $(CFLAGS) -DWCLOCK24H=0 -c tables12h-ch1.c

make-tables12h-ch2: make-tables12h-ch2.o tables12h-ch2.o
	cc make-tables12h-ch2.o tables12h-ch2.o -o make-tables12h-ch2

make-tables12h-ch2.o: make-tables.c tables12h-ch2.h tables-gen.h
	cc $(CFLAGS) -DWCLOCK24H=0 -DWCLOCK12H_CH2 -c make-tables.c -o make-tables12h-ch2.o

tables12h-ch2.o: tables12h-ch2.c tables12h-ch2.h tables-gen.h
	cc $(CFLAGS) -DWCLOCK24H=0 -c tables12h-ch2.c

make-tables12h-de: make-tables12h-de.o tables12h-de.o
	cc make-tables12h-de.o tables12h-de.o -o make-tables12h-de

make-tables12h-de.o: make-tables.c tables12h-de.h tables-gen.h
	cc $(CFLAGS) -DWCLOCK24H=0 -DWCLOCK12H_DE -c make-tables.c -o make-tables12h-de.o

tables12h-de.o: tables12h-de.c tables12h-de.h tables-gen.h
	cc $(CFLAGS) -DWCLOCK24H=0 -c tables12h-de.c

make-tables12h-en1: make-tables12h-en1.o tables12h-en1.o
	cc make-tables12h-en1.o tables12h-en1.o -o make-tables12h-en1

make-tables12h-en1.o: make-tables.c tables12h-en1.h tables-gen.h
	cc $(CFLAGS) -DWCLOCK24H=0 -DWCLOCK12H_EN1 -c make-tables.c -o make-tables12h-en1.o

tables12h-en1.o: tables12h-en1.c tables12h-en1.h tables-gen.h
	cc $(CFLAGS) -DWCLOCK24H=0 -c tables12h-en1.c

make-tables12h-en2: make-tables12h-en2.o tables12h-en2.o
	cc make-tables12h-en2.o tables12h-en2.o -o make-tables12h-en2

make-tables12h-en2.o: make-tables.c tables12h-en2.h tables-gen.h
	cc $(CFLAGS) -DWCLOCK24H=0 -DWCLOCK12H_EN2 -c make-tables.c -o make-tables12h-en2.o

tables12h-en2.o: tables12h-en2.c tables12h-en2.h tables-gen.h
	cc $(CFLAGS) -DWCLOCK24H=0 -c tables12h-en2.c

make-tables12h-fr: make-tables12h-fr.o tables12h-fr.o
	cc make-tables12h-fr.o tables12h-fr.o -o make-tables12h-fr

make-tables12h-fr.o: make-tables.c tables12h-fr.h tables-gen.h
	cc $(CFLAGS) -DWCLOCK24H=0 -DWCLOCK12H_FR -c make-tables.c -o make-tables12h-fr.o

tables12h-fr.o: tables12h-fr.c tables12h-fr.h tables-gen.h
	cc $(CFLAGS) -DWCLOCK24H=0 -c tables12h-fr.c

make-tables12h-se: make-tables12h-se.o tables12h-se.o
	cc make-tables12h-se.o tables12h-se.o -o make-tables12h-se

make-tables12h-se.o: make-tables.c tables12h-se.h tables-gen.h
	cc $(CFLAGS) -DWCLOCK24H=0 -DWCLOCK12H_SE -c make-tables.c -o make-tables12h-se.o

tables12h-se.o: tables12h-se.c tables12h-se.h tables-gen.h
	cc $(CFLAGS) -DWCLOCK24H=0 -c tables12h-se.c

clean:
	rm -f *.o make-tables12h-ch1 make-tables12h-ch2 make-tables12h-de make-tables12h-en1 make-tables12h-en2 make-tables12h-fr make-tables12h-se make-tables24h-de make-tables24h-pl wc.exe
