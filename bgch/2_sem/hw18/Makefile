WARNINGS = -O3 -fsanitize=leak -mfpmath=sse -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -std=gnu99 -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wold-style-definition -Wdeclaration-after-statement -Wbad-function-cast -Wnested-externs
CFLAGS = $(WARNINGS)
MFLAGS = -lm
all: hw18.o a.out

hw18.o: hw18.c hw18.h
	gcc -c $(CFLAGS) hw18.c

a01.out: main_hw18.o hw18.o
	gcc main_hw18.o hw18.o $(MFLAGS) -o a01.out
main_hw18.o: 1_hw18.c hw18.h
	gcc -c $(CFLAGS) main_hw18.c
hw18.o: hw18.c hw18.h

clean:
	rm -f *.o *.out
