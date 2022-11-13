
programa: Programa.o
	$(CXX) Programa.o -o programa -pthread

Programa.o: Programa.cpp
	$(CXX) -c Programa.cpp

clean:
	rm *.o programa
