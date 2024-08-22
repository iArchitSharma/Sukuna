CPP = g++
CFLAGS = -std=c++11 -Iinclude

SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)

all: sukuna

sukuna: $(OBJ)
	$(CPP) $(CFLAGS) -o bin/sukuna $(OBJ)

clean:
	rm -f $(OBJ) bin/sukuna

.PHONY: clean