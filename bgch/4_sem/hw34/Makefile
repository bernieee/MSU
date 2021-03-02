C++FLAGS = -O3 -mfpmath=sse -fstack-protector-all -g -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual -Wno-suggest-attribute=format -fsanitize=address -lasan
MFLAGS = -lm -lasan
all: record.o command.o a.out

%.o: %.cpp
	g++ -c $(C++FLAGS) $<

record.o: record.cpp record.h condition.h
command.o: command.cpp command.h condition.h

hw34.o: hw34.cpp record.h command.h list2_node.h list2.h condition.h
a.out: hw34.o record.o command.o
	g++ $^ $(MFLAGS) -o $@

clean:
	rm -f *.o *.out

