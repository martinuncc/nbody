CXX = g++
CXXFLAGS = -O3 -Wall -Wextra -std=c++11

TARGET = s

SOURCES = simulation.cpp
HEADERS = particle.h
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

simulation.o: simulation.cpp particle.h
	$(CXX) $(CXXFLAGS) -c simulation.cpp -o simulation.o

clean:
	rm -f $(TARGET) $(OBJECTS) log.tsv

run: $(TARGET)
	echo "log.tsv" | ./$(TARGET) 200 5000000 5000

.PHONY: all clean run