.RECIPEPREFIX = >

CC      = gcc
CFLAGS  = -Wall -std=c99
PROGS   = desafio1 desafio2 desafio3 desafio4 desafio5 desafio6 desafio7 desafio8

ifeq ($(OS),Windows_NT)
    RAYLIB ?= C:/raylib/raylib/src
    CFLAGS += -I$(RAYLIB)
    LDLIBS  = -L$(RAYLIB) -lraylib -lopengl32 -lgdi32 -lwinmm -lshcore
else ifeq ($(shell uname -s),Darwin)
    CFLAGS += $(shell pkg-config --cflags raylib)
    LDLIBS  = $(shell pkg-config --libs raylib)
else
    LDLIBS  = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
endif

all: $(PROGS)

%: %.c
> $(CC) $(CFLAGS) $< -o $@ $(LDLIBS)

clean:
> rm -f $(PROGS) *.exe

.PHONY: all clean
