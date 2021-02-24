C++FLAGS = -O3 -mfpmath=sse -fstack-protector-all -g -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual -Wno-suggest-attribute=format -fsanitize=address -lasan
MFLAGS = -lm -lasan
all: student.o a.out

%.o: %.cpp
	g++ -c $(C++FLAGS) $<

student.o: student.cpp student.h

hw30.o: hw30.cpp student.h b_tree.h b_tree_node.h
a.out: hw30.o student.o
	g++ $^ $(MFLAGS) -o $@


clean:
	rm -f *.o *.out

