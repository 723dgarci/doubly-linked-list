CFLAGS = -std=c++11 -Wall -pedantic 

all: proj2.x 

proj2.x: test_list.o 
	g++ $(CFLAGS) -o $@ $^

test_list.o: List.h test_list.cpp
	g++ $(CFLAGS) -c $^

clean:
	rm *.o *.gch
