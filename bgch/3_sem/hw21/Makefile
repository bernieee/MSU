CFLAGS = -O3 -mfpmath=sse -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Wmissing-declarations
C++FLAGS = -mfpmath=sse -fstack-protector-all -g -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual -Wno-suggest-attribute=format
all: a.out

student.o: student.cpp student.h
	g++ -c $(C++FLAGS) student.cpp
main.o: main.cpp student.h
	g++ -c $(C++FLAGS) main.cpp
a.out: main.o student.o
	g++ main.o student.o -o a.out

clean:
	rm -f *.o *.out

