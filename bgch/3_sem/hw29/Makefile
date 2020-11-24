C++FLAGS = -O3 -mfpmath=sse -fstack-protector-all -g -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual -Wno-suggest-attribute=format -fsanitize=address -lasan
MFLAGS = -lm -lasan
all: student.o list2.o a.out

%.o: %.cpp
	g++ -c $(C++FLAGS) $<

student.o: student.cpp student.h
list2.o: list2.cpp list2_node.h

hw29.o: hw29.cpp student.h list2.h list2_node.h tree.h tree_node.h
a.out: hw29.o student.o list2.o
	g++ $^ $(MFLAGS) -o $@


clean:
	rm -f *.o *.out

