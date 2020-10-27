C++FLAGS = -O3 -mfpmath=sse -fstack-protector-all -g -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual -Wno-suggest-attribute=format
C = -fsanitize=address -lasan
MFLAGS = -lm
M = -lasan
all: student.o list.o sorts.o a01.out a02.out a03.out a04.out a05.out

%.o: %.cpp
	g++ -c $(C++FLAGS) $<

student.o: student.cpp student.h
list.o: list.cpp list.h list_node.h
sorts.o: sorts.cpp list.h list_node.h

1_hw25.o: 1_hw25.cpp student.h list.h list_node.h
a01.out: 1_hw25.o student.o list.o sorts.o
	g++ $^ $(MFLAGS) -o $@

2_hw25.o: 2_hw25.cpp student.h list.h list_node.h
a02.out: 2_hw25.o student.o list.o sorts.o
	g++ $^ $(MFLAGS) -o $@

3_hw25.o: 3_hw25.cpp student.h list.h list_node.h
a03.out: 3_hw25.o student.o list.o sorts.o
	g++ $^ $(MFLAGS) -o $@

4_hw25.o: 4_hw25.cpp student.h list.h list_node.h
a04.out: 4_hw25.o student.o list.o sorts.o
	g++ $^ $(MFLAGS) -o $@

5_hw25.o: 5_hw25.cpp student.h list.h list_node.h
a05.out: 5_hw25.o student.o list.o sorts.o
	g++ $^ $(MFLAGS) -o $@

clean:
	rm -f *.o *.out

