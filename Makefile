
UTaste: main.o Utaste.o District.o Restaurant.o Readfiles.o User.o Reserve.o
	g++ --std=c++20 main.o Utaste.o District.o Restaurant.o Readfiles.o User.o Reserve.o -o UTaste
main.o: main.cpp Utaste.h District.h Restaurant.h Readfiles.h User.h Reserve.h
	g++ -c --std=c++20 main.cpp
Utaste.o: Utaste.cpp Utaste.h User.h Restaurant.h District.h Reserve.h
	g++ -c --std=c++20 Utaste.cpp
District.o: District.cpp District.h 
	g++ -c --std=c++20 District.cpp
Restaurant.o: Restaurant.cpp Restaurant.h District.h
	g++ -c --std=c++20 Restaurant.cpp
Readfiles.o: Readfiles.cpp Readfiles.h District.h Restaurant.h
	g++ -c --std=c++20 Readfiles.cpp
User.o: User.cpp User.h
	g++ -c --std=c++20 User.cpp
Reserve.o: Reserve.cpp Reserve.h User.h Restaurant.h District.h
	g++ -c --std=c++20 Reserve.cpp
clean:
	rm *.o UTaste
