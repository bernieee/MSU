C++FLAGS = -O3 -mfpmath=sse -fstack-protector-all -g -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual -Wno-suggest-attribute=format
C = -fsanitize=address -lasan
MFLAGS = -lm
M = -lasan
all: student.o list.o a01.out a02.out a03.out a04.out a05.out a06.out a07.out a08.out

%.o: %.cpp
	g++ -c $(C++FLAGS) $<

student.o: student.cpp student.h
list.o: list.cpp list.h list_node.h

1_hw24.o: 1_hw24.cpp student.h list.h list_node.h
a01.out: 1_hw24.o student.o list.o
	g++ $^ $(MFLAGS) -o $@

2_hw24.o: 2_hw24.cpp student.h list.h list_node.h
a02.out: 2_hw24.o student.o list.o
	g++ $^ $(MFLAGS) -o $@

3_hw24.o: 3_hw24.cpp student.h list.h list_node.h
a03.out: 3_hw24.o student.o list.o
	g++ $^ $(MFLAGS) -o $@

4_hw24.o: 4_hw24.cpp student.h list.h list_node.h
a04.out: 4_hw24.o student.o list.o
	g++ $^ $(MFLAGS) -o $@

5_hw24.o: 5_hw24.cpp student.h list.h list_node.h
a05.out: 5_hw24.o student.o list.o
	g++ $^ $(MFLAGS) -o $@

6_hw24.o: 6_hw24.cpp student.h list.h list_node.h
a06.out: 6_hw24.o student.o list.o
	g++ $^ $(MFLAGS) -o $@

7_hw24.o: 7_hw24.cpp student.h list.h list_node.h
a07.out: 7_hw24.o student.o list.o
	g++ $^ $(MFLAGS) -o $@

8_hw24.o: 8_hw24.cpp student.h list.h list_node.h
a08.out: 8_hw24.o student.o list.o
	g++ $^ $(MFLAGS) -o $@


clean:
	rm -f *.o *.out

