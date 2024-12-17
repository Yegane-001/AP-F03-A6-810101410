Test: main.o Utaste.o 
	g++ --std=c++20 main.o Utaste.o 
main.o: main.cpp Utaste.h 
	g++ -c --std=c++20 main.cpp
Utaste.o: Utaste.cpp Utaste.h
	g++ -c --std=c++20 Utaste.cpp
clean:
	rm *.o Test.out