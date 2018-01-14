main: main.cpp Executive.o ConvertOperation.o NfaNode.o DfaNode.o 
	g++ -o main main.cpp Executive.o ConvertOperation.o NfaNode.o DfaNode.o -std=c++11

Executive.o: Executive.cpp
	g++ -c Executive.cpp -std=c++11

ConvertOperation.o: ConvertOperation.cpp
	g++ -c ConvertOperation.cpp -std=c++11

NfaNode.o: NfaNode.cpp
	g++ -c NfaNode.cpp -std=c++11

DfaNode.o: DfaNode.cpp
	g++ -c DfaNode.cpp -std=c++11

clean:
	rm *.o main 

