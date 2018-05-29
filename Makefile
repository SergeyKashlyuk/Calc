CXX = gcc -std=gnu++11
CXXFLAGS = -g -lstdc++
INCS = -I./
OBJS = calc.o

calc: $(OBJS)
	$(CXX) -o calc main.cpp $(OBJS) $(CXXFLAGS)

.cpp.o:
	$(CXX) -c $< -o $@ $(INCS) $(CXXFLAGS)

clean:
	rm *.o calc
