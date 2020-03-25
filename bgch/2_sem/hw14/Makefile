CFLAGS = -O3 -W -Wall -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -fstack-protector-all -Wfloat-equal -Wpointer-arith -Wwrite-strings -Wcast-align -Wno-long-long -Wmissing-declarations -Werror=declaration-after-statement
MFLAGS = -lm
all: a01.out a02.out a03.out a04.out a05.out a06.out a07.out a08.out a09.out a10.out

a01.out: 1_hw14.o hw14.o
	gcc 1_hw14.o hw14.o $(MFLAGS) -o a01.out
1_hw14.o: 1_hw14.c hw14.h
	gcc -c $(CFLAGS) 1_hw14.c
hw14.o: hw14.c hw14.h
	gcc -c $(CFLAGS) hw14.c

a02.out: 2_hw14.o hw14.o
	gcc 2_hw14.o hw14.o $(MFLAGS) -o a02.out
2_hw14.o: 2_hw14.c hw14.h
	gcc -c $(CFLAGS) 2_hw14.c
hw14.o: hw14.c hw14.h

a03.out: 3_hw14.o hw14.o
	gcc 3_hw14.o hw14.o $(MFLAGS) -o a03.out
3_hw14.o: 3_hw14.c hw14.h
	gcc -c $(CFLAGS) 3_hw14.c
hw14.o: hw14.c hw14.h

a04.out: 4_hw14.o hw14.o
	gcc 4_hw14.o hw14.o $(MFLAGS) -o a04.out
4_hw14.o: 4_hw14.c hw14.h
	gcc -c $(CFLAGS) 4_hw14.c
hw14.o: hw14.c hw14.h

a05.out: 5_hw14.o hw14.o
	gcc 5_hw14.o hw14.o $(MFLAGS) -o a05.out
5_hw14.o: 5_hw14.c hw14.h
	gcc -c $(CFLAGS) 5_hw14.c
hw14.o: hw14.c hw14.h

a06.out: 6_hw14.o hw14.o
	gcc 6_hw14.o hw14.o $(MFLAGS) -o a06.out
6_hw14.o: 6_hw14.c hw14.h
	gcc -c $(CFLAGS) 6_hw14.c
hw14.o: hw14.c hw14.h

a07.out: 7_hw14.o hw14.o
	gcc 7_hw14.o hw14.o $(MFLAGS) -o a07.out
7_hw14.o: 7_hw14.c hw14.h
	gcc -c $(CFLAGS) 7_hw14.c
hw14.o: hw14.c hw14.h

a08.out: 8_hw14.o hw14.o
	gcc 8_hw14.o hw14.o $(MFLAGS) -o a08.out
8_hw14.o: 8_hw14.c hw14.h
	gcc -c $(CFLAGS) 8_hw14.c
hw14.o: hw14.c hw14.h

a09.out: 9_hw14.o hw14.o
	gcc 9_hw14.o hw14.o $(MFLAGS) -o a09.out
9_hw14.o: 9_hw14.c hw14.h
	gcc -c $(CFLAGS) 9_hw14.c
hw14.o: hw14.c hw14.h

a10.out: 10_hw14.o hw14.o
	gcc 10_hw14.o hw14.o $(MFLAGS) -o a10.out
10_hw14.o: 10_hw14.c hw14.h
	gcc -c $(CFLAGS) 10_hw14.c
hw14.o: hw14.c hw14.h
clean:
	rm -f *.o *.out
