CPPFLAGS = -g -std=c++11
LIBS =

main : test.o float16.o
	g++ ${CPPFLAGS} -o main test.o float16.o ${LIBS}

test.o : test.cpp
	g++ ${CPPFLAGS} -c test.cpp

float16.o : float16.cpp
	g++ ${CPPFLAGS} -c float16.cpp

clean :
	rm -rf *.o main
