WARNINGS = -O3 -W -Wall -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -fstack-protector-all -Wfloat-equal -Wpointer-arith -Wwrite-strings -Wno-long-long -Wmissing-declarations -Werror=float-equal -Werror=unused-variable -Werror=unused-parameter -Werror=declaration-after-statement -Werror=missing-prototypes -Werror=return-type -Werror=maybe-uninitialized -Wimplicit
WARNINGS_C_ONLY = -Wc++-compat -Wbad-function-cast
CFLAGS = $(WARNINGS) $(WARNINGS_C_ONLY)
MFLAGS = -lm
all: a01.out a02.out a03.out a04.out a05.out a06.out a07.out a08.out a09.out a10.out a11.out

a01.out: 1_hw15.o hw15.o
	gcc 1_hw15.o hw15.o $(MFLAGS) -o a01.out
1_hw15.o: 1_hw15.c hw15.h
	gcc -c $(CFLAGS) 1_hw15.c
hw15.o: hw15.c hw15.h
	gcc -c $(CFLAGS) hw15.c

a02.out: 2_hw15.o hw15.o
	gcc 2_hw15.o hw15.o $(MFLAGS) -o a02.out
2_hw15.o: 2_hw15.c hw15.h
	gcc -c $(CFLAGS) 2_hw15.c
hw15.o: hw15.c hw15.h

a03.out: 3_hw15.o hw15.o
	gcc 3_hw15.o hw15.o $(MFLAGS) -o a03.out
3_hw15.o: 3_hw15.c hw15.h
	gcc -c $(CFLAGS) 3_hw15.c
hw15.o: hw15.c hw15.h

a04.out: 4_hw15.o hw15.o
	gcc 4_hw15.o hw15.o $(MFLAGS) -o a04.out
4_hw15.o: 4_hw15.c hw15.h
	gcc -c $(CFLAGS) 4_hw15.c
hw15.o: hw15.c hw15.h

a05.out: 5_hw15.o hw15.o
	gcc 5_hw15.o hw15.o $(MFLAGS) -o a05.out
5_hw15.o: 5_hw15.c hw15.h
	gcc -c $(CFLAGS) 5_hw15.c
hw15.o: hw15.c hw15.h

a06.out: 6_hw15.o hw15.o
	gcc 6_hw15.o hw15.o $(MFLAGS) -o a06.out
6_hw15.o: 6_hw15.c hw15.h
	gcc -c $(CFLAGS) 6_hw15.c
hw15.o: hw15.c hw15.h

a07.out: 7_hw15.o hw15.o
	gcc 7_hw15.o hw15.o $(MFLAGS) -o a07.out
7_hw15.o: 7_hw15.c hw15.h
	gcc -c $(CFLAGS) 7_hw15.c
hw15.o: hw15.c hw15.h

a08.out: 8_hw15.o hw15.o
	gcc 8_hw15.o hw15.o $(MFLAGS) -o a08.out
8_hw15.o: 8_hw15.c hw15.h
	gcc -c $(CFLAGS) 8_hw15.c
hw15.o: hw15.c hw15.h

a09.out: 9_hw15.o hw15.o
	gcc 9_hw15.o hw15.o $(MFLAGS) -o a09.out
9_hw15.o: 9_hw15.c hw15.h
	gcc -c $(CFLAGS) 9_hw15.c
hw15.o: hw15.c hw15.h

a10.out: 10_hw15.o hw15.o
	gcc 10_hw15.o hw15.o $(MFLAGS) -o a10.out
10_hw15.o: 10_hw15.c hw15.h
	gcc -c $(CFLAGS) 10_hw15.c
hw15.o: hw15.c hw15.h

a11.out: 11_hw15.o hw15.o
	gcc 11_hw15.o hw15.o $(MFLAGS) -o a11.out
11_hw15.o: 11_hw15.c hw15.h
	gcc -c $(CFLAGS) 11_hw15.c
hw15.o: hw15.c hw15.h

clean:
	rm -f *.o *.out
