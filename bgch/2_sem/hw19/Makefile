WARNINGS = -O3 -fsanitize=leak -mfpmath=sse -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -std=gnu99 -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wold-style-definition -Wdeclaration-after-statement -Wbad-function-cast -Wnested-externs
CFLAGS = $(WARNINGS)
MFLAGS = -lm
all: hw19.o a01.out a02.out a03.out a04.out a05.out a06.out a07.out a08.out a09.out a10.out a11.out a12.out

hw19.o: hw19.c hw19.h
	gcc -c $(CFLAGS) hw19.c

a01.out: 1_hw19.o hw19.o
	gcc 1_hw19.o hw19.o $(MFLAGS) -o a01.out
1_hw19.o: 1_hw19.c hw19.h
	gcc -c $(CFLAGS) 1_hw19.c
hw19.o: hw19.c hw19.h

a02.out: 2_hw19.o hw19.o
	gcc 2_hw19.o hw19.o $(MFLAGS) -o a02.out
2_hw19.o: 2_hw19.c hw19.h
	gcc -c $(CFLAGS) 2_hw19.c
hw19.o: hw19.c hw19.h

a03.out: 3_hw19.o hw19.o
	gcc 3_hw19.o hw19.o $(MFLAGS) -o a03.out
3_hw19.o: 3_hw19.c hw19.h
	gcc -c $(CFLAGS) 3_hw19.c
hw19.o: hw19.c hw19.h

a04.out: 4_hw19.o hw19.o
	gcc 4_hw19.o hw19.o $(MFLAGS) -o a04.out
4_hw19.o: 4_hw19.c hw19.h
	gcc -c $(CFLAGS) 4_hw19.c
hw19.o: hw19.c hw19.h

a05.out: 5_hw19.o hw19.o
	gcc 5_hw19.o hw19.o $(MFLAGS) -o a05.out
5_hw19.o: 5_hw19.c hw19.h
	gcc -c $(CFLAGS) 5_hw19.c
hw19.o: hw19.c hw19.h

a06.out: 6_hw19.o hw19.o
	gcc 6_hw19.o hw19.o $(MFLAGS) -o a06.out
6_hw19.o: 6_hw19.c hw19.h
	gcc -c $(CFLAGS) 6_hw19.c
hw19.o: hw19.c hw19.h

a07.out: 7_hw19.o hw19.o
	gcc 7_hw19.o hw19.o $(MFLAGS) -o a07.out
7_hw19.o: 7_hw19.c hw19.h
	gcc -c $(CFLAGS) 7_hw19.c
hw19.o: hw19.c hw19.h

a08.out: 8_hw19.o hw19.o
	gcc 8_hw19.o hw19.o $(MFLAGS) -o a08.out
8_hw19.o: 8_hw19.c hw19.h
	gcc -c $(CFLAGS) 8_hw19.c
hw19.o: hw19.c hw19.h

a09.out: 9_hw19.o hw19.o
	gcc 9_hw19.o hw19.o $(MFLAGS) -o a09.out
9_hw19.o: 9_hw19.c hw19.h
	gcc -c $(CFLAGS) 9_hw19.c
hw19.o: hw19.c hw19.h

a10.out: 10_hw19.o hw19.o
	gcc 10_hw19.o hw19.o $(MFLAGS) -o a10.out
10_hw19.o: 10_hw19.c hw19.h
	gcc -c $(CFLAGS) 10_hw19.c
hw19.o: hw19.c hw19.h

a11.out: 11_hw19.o hw19.o
	gcc 11_hw19.o hw19.o $(MFLAGS) -o a11.out
11_hw19.o: 11_hw19.c hw19.h
	gcc -c $(CFLAGS) 11_hw19.c
hw19.o: hw19.c hw19.h

a12.out: 12_hw19.o hw19.o
	gcc 12_hw19.o hw19.o $(MFLAGS) -o a12.out
12_hw19.o: 12_hw19.c hw19.h
	gcc -c $(CFLAGS) 12_hw19.c
hw19.o: hw19.c hw19.h

clean:
	rm -f *.o *.out
