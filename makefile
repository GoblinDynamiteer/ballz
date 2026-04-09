TARGET  := ballz_demo
CC      := gcc
SUBDIR  := game

SRC     := $(wildcard *.$(SRC_EXT)) $(wildcard $(SUBDIR)/*.$(SRC_EXT))
# (or just hardcode SRC_EXT = c)
SRC_EXT := c
OBJ_EXT := o

SRC     := $(wildcard *.$(SRC_EXT)) $(wildcard $(SUBDIR)/*.$(SRC_EXT))
OBJ     := $(SRC:.$(SRC_EXT)=.$(OBJ_EXT))

CFLAGS  := -g -Wall -I. $(shell sdl2-config --cflags)
LDLIBS  := -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lm
LDFLAGS := $(shell sdl2-config --libs)

.PHONY: all clean run cleantarget link

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS) $(LDLIBS)

# Compile .c -> .o
%.o: %.c def.h
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)

cleantarget:
	rm -f $(TARGET)

# optional: keep "link" target if you want the old name
link: $(TARGET)
