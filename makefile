CC=g++
CXXFLAGS=-std=c++11 -Wall -I/usr/include
LDFLAGS=-losg -losgViewer -losgDB -losgGA -losgUtil -lGL -lGLU -lglfw -lGLEW

SOURCES=spinningcubeosg.cpp
EXECUTABLE=spinningcubeosg

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CC) $(CXXFLAGS) -o $(EXECUTABLE) $(SOURCES) $(LDFLAGS)

clean:
	rm -f $(EXECUTABLE)
