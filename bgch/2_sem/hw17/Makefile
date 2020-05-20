WARNINGS = -O3 -fsanitize=leak -mfpmath=sse -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -std=gnu99 -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wold-style-definition -Wdeclaration-after-statement -Wbad-function-cast -Wnested-externs
CFLAGS = $(WARNINGS)
MFLAGS = -lm
all: hw17.o a01.out a02.out a03.out a04.out a05.out a06.out a07.out a08.out a09.out a10.out

hw17.o: hw17.c hw17.h
	gcc -c $(CFLAGS) hw17.c

a01.out: 1_hw17.o hw17.o
	gcc 1_hw17.o hw17.o $(MFLAGS) -o a01.out
1_hw17.o: 1_hw17.c hw17.h
	gcc -c $(CFLAGS) 1_hw17.c
hw17.o: hw17.c hw17.h

a02.out: 2_hw17.o hw17.o
	gcc 2_hw17.o hw17.o $(MFLAGS) -o a02.out
2_hw17.o: 2_hw17.c hw17.h
	gcc -c $(CFLAGS) 2_hw17.c
hw17.o: hw17.c hw17.h

a03.out: 3_hw17.o hw17.o
	gcc 3_hw17.o hw17.o $(MFLAGS) -o a03.out
3_hw17.o: 3_hw17.c hw17.h
	gcc -c $(CFLAGS) 3_hw17.c
hw17.o: hw17.c hw17.h

a04.out: 4_hw17.o hw17.o
	gcc 4_hw17.o hw17.o $(MFLAGS) -o a04.out
4_hw17.o: 4_hw17.c hw17.h
	gcc -c $(CFLAGS) 4_hw17.c
hw17.o: hw17.c hw17.h

a05.out: 5_hw17.o hw17.o
	gcc 5_hw17.o hw17.o $(MFLAGS) -o a05.out
5_hw17.o: 5_hw17.c hw17.h
	gcc -c $(CFLAGS) 5_hw17.c
hw17.o: hw17.c hw17.h

a06.out: 6_hw17.o hw17.o
	gcc 6_hw17.o hw17.o $(MFLAGS) -o a06.out
6_hw17.o: 6_hw17.c hw17.h
	gcc -c $(CFLAGS) 6_hw17.c
hw17.o: hw17.c hw17.h

a07.out: 7_hw17.o hw17.o
	gcc 7_hw17.o hw17.o $(MFLAGS) -o a07.out
7_hw17.o: 7_hw17.c hw17.h
	gcc -c $(CFLAGS) 7_hw17.c
hw17.o: hw17.c hw17.h

a08.out: 8_hw17.o hw17.o
	gcc 8_hw17.o hw17.o $(MFLAGS) -o a08.out
8_hw17.o: 8_hw17.c hw17.h
	gcc -c $(CFLAGS) 8_hw17.c
hw17.o: hw17.c hw17.h

a09.out: 9_hw17.o hw17.o
	gcc 9_hw17.o hw17.o $(MFLAGS) -o a09.out
9_hw17.o: 9_hw17.c hw17.h
	gcc -c $(CFLAGS) 9_hw17.c
hw17.o: hw17.c hw17.h

a10.out: 10_hw17.o hw17.o
	gcc 10_hw17.o hw17.o $(MFLAGS) -o a10.out
10_hw17.o: 10_hw17.c hw17.h
	gcc -c $(CFLAGS) 10_hw17.c
hw17.o: hw17.c hw17.h

clean:
	rm -f *.o *.out
