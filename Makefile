CC = gcc

BIN  = bin
NAME = main
SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:%.c=$(BIN)/%.o)

CFLAGS  = -g -Wall -Wextra -I include
LDFLAGS = 
LDLIBS  = 

ifeq ($(OS),Windows_NT)
	LDFLAGS += -L lib
	LDLIBS  += -lmingw32 -lSDL2main -lSDL2
else
	LDLIBS += $(shell sdl2-config --libs) -lm
endif

.PHONY: all dirs

all: $(NAME)
	$(BIN)/$(NAME)

dirs:
	mkdir -p $(BIN)/src

$(OBJS): $(BIN)/%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): dirs $(OBJS)
	$(CC) -o $(BIN)/$(NAME) $(OBJS) $(LDFLAGS) $(LDLIBS)
