CFLAGS = -O3 -mfpmath=sse -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -std=gnu99 -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wold-style-definition -Wdeclaration-after-statement -Wbad-function-cast -Wnested-externs
MFLAGS = -lm
all: solve_hw20.o a01.out a02.out a03.out a04.out a05.out a06.out a07.out a08.out a09.out a10.out

io_hw20.o: io_hw20.c io_hw20.h
	gcc -c $(CFLAGS) io_hw20.c
solve_hw20.o: solve_hw20.c solve_hw20.h
	gcc -c $(CFLAGS) solve_hw20.c

a01.out: 1_hw20.o io_hw20.o solve_hw20.o
	gcc 1_hw20.o io_hw20.o solve_hw20.o $(MFLAGS) -o a01.out
1_hw20.o: 1_hw20.c io_hw20.h solve_hw20.h
	gcc -c $(CFLAGS) 1_hw20.c

a02.out: 2_hw20.o io_hw20.o solve_hw20.o
	gcc 2_hw20.o io_hw20.o solve_hw20.o $(MFLAGS) -o a02.out
2_hw20.o: 2_hw20.c io_hw20.h solve_hw20.h
	gcc -c $(CFLAGS) 2_hw20.c

a03.out: 3_hw20.o io_hw20.o solve_hw20.o
	gcc 3_hw20.o io_hw20.o solve_hw20.o $(MFLAGS) -o a03.out
3_hw20.o: 3_hw20.c io_hw20.h solve_hw20.h
	gcc -c $(CFLAGS) 3_hw20.c

a04.out: 4_hw20.o io_hw20.o solve_hw20.o
	gcc 4_hw20.o io_hw20.o solve_hw20.o $(MFLAGS) -o a04.out
4_hw20.o: 4_hw20.c io_hw20.h solve_hw20.h
	gcc -c $(CFLAGS) 4_hw20.c

a05.out: 5_hw20.o io_hw20.o solve_hw20.o
	gcc 5_hw20.o io_hw20.o solve_hw20.o $(MFLAGS) -o a05.out
5_hw20.o: 5_hw20.c io_hw20.h solve_hw20.h
	gcc -c $(CFLAGS) 5_hw20.c

a06.out: 6_hw20.o io_hw20.o solve_hw20.o
	gcc 6_hw20.o io_hw20.o solve_hw20.o $(MFLAGS) -o a06.out
6_hw20.o: 6_hw20.c io_hw20.h solve_hw20.h
	gcc -c $(CFLAGS) 6_hw20.c

a07.out: 7_hw20.o io_hw20.o solve_hw20.o
	gcc 7_hw20.o io_hw20.o solve_hw20.o $(MFLAGS) -o a07.out
7_hw20.o: 7_hw20.c io_hw20.h solve_hw20.h
	gcc -c $(CFLAGS) 7_hw20.c

a08.out: 8_hw20.o io_hw20.o solve_hw20.o
	gcc 8_hw20.o io_hw20.o solve_hw20.o $(MFLAGS) -o a08.out
8_hw20.o: 8_hw20.c io_hw20.h solve_hw20.h
	gcc -c $(CFLAGS) 8_hw20.c

a09.out: 9_hw20.o io_hw20.o solve_hw20.o
	gcc 9_hw20.o io_hw20.o solve_hw20.o $(MFLAGS) -o a09.out
9_hw20.o: 9_hw20.c io_hw20.h solve_hw20.h
	gcc -c $(CFLAGS) 9_hw20.c

a10.out: 10_hw20.o io_hw20.o solve_hw20.o
	gcc 10_hw20.o io_hw20.o solve_hw20.o $(MFLAGS) -o a10.out
10_hw20.o: 10_hw20.c io_hw20.h solve_hw20.h
	gcc -c $(CFLAGS) 10_hw20.c

clean:
	rm -f *.o *.out
