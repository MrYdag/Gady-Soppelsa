SRC=MarioFCT.c Mario.c
INC=$(wildcard *.h)
BIN=Mario

$(BIN): $(SRC) $(INC)
	gcc -Wall -g -std=c99 $(SRC) `sdl-config --cflags --libs` -lm -o $(BIN)

clean:
	rm -f $(BIN)
