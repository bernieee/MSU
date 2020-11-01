C++FLAGS = -O3 -mfpmath=sse -fstack-protector-all -g -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual -Wno-suggest-attribute=format
C = -fsanitize=address -lasan
MFLAGS = -lm
M = -lasan
all: student.o list.o solve_hw23.o a01.out a02.out a03.out a04.out a05.out a06.out a07.out a08.out

%.o: %.cpp
	g++ -c $(C++FLAGS) $<

student.o: student.cpp student.h
list.o: list.cpp list.h
solve_hw23.o: solve_hw23.cpp solve_hw23.h

1_hw23.o: 1_hw23.cpp student.h list.h solve_hw23.h
a01.out: 1_hw23.o student.o list.o solve_hw23.o
	g++ $^ $(MFLAGS) -o $@

2_hw23.o: 2_hw23.cpp student.h list.h solve_hw23.h
a02.out: 2_hw23.o student.o list.o solve_hw23.o
	g++ $^ $(MFLAGS) -o $@

3_hw23.o: 3_hw23.cpp student.h list.h solve_hw23.h
a03.out: 3_hw23.o student.o list.o solve_hw23.o
	g++ $^ $(MFLAGS) -o $@

4_hw23.o: 4_hw23.cpp student.h list.h solve_hw23.h
a04.out: 4_hw23.o student.o list.o solve_hw23.o
	g++ $^ $(MFLAGS) -o $@

5_hw23.o: 5_hw23.cpp student.h list.h solve_hw23.h
a05.out: 5_hw23.o student.o list.o solve_hw23.o
	g++ $^ $(MFLAGS) -o $@

6_hw23.o: 6_hw23.cpp student.h list.h solve_hw23.h
a06.out: 6_hw23.o student.o list.o solve_hw23.o
	g++ $^ $(MFLAGS) -o $@

7_hw23.o: 7_hw23.cpp student.h list.h solve_hw23.h
a07.out: 7_hw23.o student.o list.o solve_hw23.o
	g++ $^ $(MFLAGS) -o $@

8_hw23.o: 8_hw23.cpp student.h list.h solve_hw23.h
a08.out: 8_hw23.o student.o list.o solve_hw23.o
	g++ $^ $(MFLAGS) -o $@


clean:
	rm -f *.o *.out

