CPP = g++ -g

slisttest: main.o SList.o
	$(CPP) -o slisttest main.o SList.o
main.o: main.cpp
	$(CPP) -c main.cpp
SList.o: SList.cpp SList.h
	$(CPP) -c SList.cpp
clean:
	rm *.o
	rm slisttest
