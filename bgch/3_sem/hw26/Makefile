C++FLAGS = -O3 -mfpmath=sse -fstack-protector-all -g -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual -Wno-suggest-attribute=format
C = -fsanitize=address -lasan
MFLAGS = -lm
M = -lasan
all: student.o tree.o a.out

%.o: %.cpp
	g++ -c $(C++FLAGS) $<

student.o: student.cpp student.h
tree.o: tree.cpp tree.h tree_node.h

hw26.o: hw26.cpp student.h tree.h tree_node.h
a.out: hw26.o student.o tree.o
	g++ $^ $(MFLAGS) -o $@


clean:
	rm -f *.o *.out

