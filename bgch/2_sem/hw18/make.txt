WARNINGS = -O3 -fsanitize=leak -mfpmath=sse -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -std=gnu99 -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wold-style-definition -Wdeclaration-after-statement -Wbad-function-cast -Wnested-externs
CFLAGS = $(WARNINGS)
MFLAGS = -lm
all: a.out

hw18.o: hw18.c hw18.h
	gcc -c $(CFLAGS) hw18.c

a.out: main_hw18.o io_hw18.o solve_hw18.o
	gcc main_hw18.o io_hw18.o solve_hw18.o $(MFLAGS) -o a.out
main_hw18.o: main_hw18.c io_hw18.h solve_hw18.h
	gcc -c $(CFLAGS) main_hw18.c

io_hw18.o: io_hw18.c io_hw18.h
	gcc -c $(CFLAGS) io_hw18.c
solve_hw18.o: solve_hw18.c solve_hw18.h
	gcc -c $(CFLAGS) solve_hw18.c


clean:
	rm -f *.o *.out
