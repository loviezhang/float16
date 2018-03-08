CPPFLAGS = -g -std=c++11
LIBS = -lm

main : test.o
	g++ ${CPPFLAGS} -o main test.o ${LIBS}

test.o : test.cpp
	g++ ${CPPFLAGS} -c test.cpp

clean :
	rm -rf *.o main
