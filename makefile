
programa: Programa.o
	$(CXX) Programa.o -o programa

Programa.o: Programa.cpp
	$(CXX) -c Programa.cpp

clean:
	rm *.o programa