C++FLAGS = -O3 -mfpmath=sse -fstack-protector-all -g -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual -Wno-suggest-attribute=format -fsanitize=address -lasan
MFLAGS = -lm -lasan
all: query.o a01.out a02.out a03.out a04.out a05.out a06.out

%.o: %.cpp
	g++ -c $(C++FLAGS) $<

query.o: query.cpp query.h

1_hw33.o: 1_hw33.cpp query.h
a01.out: 1_hw33.o query.o
	g++ $^ $(MFLAGS) -o $@

2_hw33.o: 2_hw33.cpp query.h
a02.out: 2_hw33.o query.o
	g++ $^ $(MFLAGS) -o $@

3_hw33.o: 3_hw33.cpp query.h
a03.out: 3_hw33.o query.o
	g++ $^ $(MFLAGS) -o $@

4_hw33.o: 4_hw33.cpp query.h
a04.out: 4_hw33.o query.o
	g++ $^ $(MFLAGS) -o $@

5_hw33.o: 5_hw33.cpp query.h
a05.out: 5_hw33.o query.o
	g++ $^ $(MFLAGS) -o $@

6_hw33.o: 6_hw33.cpp query.h
a06.out: 6_hw33.o query.o
	g++ $^ $(MFLAGS) -o $@

clean:
	rm -f *.o *.out

