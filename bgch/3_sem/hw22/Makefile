C++FLAGS = -O3 -mfpmath=sse -fstack-protector-all -g -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual -Wno-suggest-attribute=format
C = -fsanitize=address -lasan
MFLAGS = -lm
M = -lasan
all: student.o sorts.o a01.out a02.out a03.out a04.out a05.out a06.out a07.out a08.out a09.out a10.out


student.o: student.cpp student.h
	g++ -c $(C++FLAGS) student.cpp
sorts.o: sorts.cpp sorts.h
	g++ -c $(C++FLAGS) sorts.cpp

a01.out: 1_hw22.o student.o sorts.o
	g++ 1_hw22.o student.o sorts.o $(MFLAGS) -o a01.out
1_hw22.o: 1_hw22.cpp student.h sorts.h
	g++ -c $(C++FLAGS) 1_hw22.cpp

a02.out: 2_hw22.o student.o sorts.o
	g++ 2_hw22.o student.o sorts.o $(MFLAGS) -o a02.out
2_hw22.o: 2_hw22.cpp student.h sorts.h
	g++ -c $(C++FLAGS) 2_hw22.cpp

a03.out: 3_hw22.o student.o sorts.o
	g++ 3_hw22.o student.o sorts.o $(MFLAGS) -o a03.out
3_hw22.o: 3_hw22.cpp student.h sorts.h
	g++ -c $(C++FLAGS) 3_hw22.cpp

a04.out: 4_hw22.o student.o sorts.o
	g++ 4_hw22.o student.o sorts.o $(MFLAGS) -o a04.out
4_hw22.o: 4_hw22.cpp student.h sorts.h
	g++ -c $(C++FLAGS) 4_hw22.cpp

a05.out: 5_hw22.o student.o sorts.o
	g++ 5_hw22.o student.o sorts.o $(MFLAGS) -o a05.out
5_hw22.o: 5_hw22.cpp student.h sorts.h
	g++ -c $(C++FLAGS) 5_hw22.cpp

a06.out: 6_hw22.o student.o sorts.o
	g++ 6_hw22.o student.o sorts.o $(MFLAGS) -o a06.out
6_hw22.o: 6_hw22.cpp student.h sorts.h
	g++ -c $(C++FLAGS) 6_hw22.cpp

a07.out: 7_hw22.o student.o sorts.o
	g++ 7_hw22.o student.o sorts.o $(MFLAGS) -o a07.out
7_hw22.o: 7_hw22.cpp student.h sorts.h
	g++ -c $(C++FLAGS) 7_hw22.cpp

a08.out: 8_hw22.o student.o sorts.o
	g++ 8_hw22.o student.o sorts.o $(MFLAGS) -o a08.out
8_hw22.o: 8_hw22.cpp student.h sorts.h
	g++ -c $(C++FLAGS) 8_hw22.cpp

a09.out: 9_hw22.o student.o sorts.o
	g++ 9_hw22.o student.o sorts.o $(MFLAGS) -o a09.out
9_hw22.o: 9_hw22.cpp student.h sorts.h
	g++ -c $(C++FLAGS) 9_hw22.cpp

a10.out: 10_hw22.o student.o sorts.o
	g++ 10_hw22.o student.o sorts.o $(MFLAGS) -o a10.out
10_hw22.o: 10_hw22.cpp student.h sorts.h
	g++ -c $(C++FLAGS) 10_hw22.cpp


clean:
	rm -f *.o *.out

