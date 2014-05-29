CXX = g++
CXXFLAGS = -g -Wall `sdl2-config --cflags`
LIBS = -lGL `sdl2-config --libs` -lGLU -lGL -lX11 -lm  -lGLEW
OUT = claw

OBJ = claw.o \
      formas.o \
      junta.o \
      braco.o \
      Load.o

all: $(OUT)

$(OUT): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(OUT) $(LIBS)

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ $<

.PHONY: clean
clean:
	rm -f $(OBJ)
	rm -f $(OUT)
