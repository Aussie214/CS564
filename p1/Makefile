#Makefile
#Requires that the object defenitions be in wl.cpp and wl.h

CXX = g++
CXXFLAGS = -o2 -g -Wall

all: wl

wl: wl.cpp
	$(CXX) $(CXXFLAGS) wl.cpp -o $@

clean: 
	rm -f core *.o wl
