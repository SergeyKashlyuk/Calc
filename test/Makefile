CXX = gcc -std=c++11
CXXFLAGS = -g -L/usr/lib -lgtest -lpthread -lstdc++
INCS = -I./ -I../ -I/usr/include
OBJS = ../calc.o calc_test.o 

testAll: $(OBJS)
	$(CXX) $(INCS) -o testAll  main_testall.cpp $(OBJS) $(CXXFLAGS) 

.cpp.o:
	$(CXX) -c $< -o $@ $(INCS) $(CXXFLAGS) 

clean:
	rm testAll *.o testAll.xml
