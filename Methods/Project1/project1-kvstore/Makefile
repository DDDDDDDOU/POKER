
LINK.o = $(LINK.cc)
CXXFLAGS = -std=c++17 -Wall

all: correctness persistence

correctness: kvstore.o correctness.o node.o SStable.o

persistence: kvstore.o persistence.o SStable.o node.o

clean:
	-rm -f correctness persistence *.o
