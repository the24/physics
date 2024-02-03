CC = gcc

BIN  = bin
NAME = main
SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:%.c=$(BIN)/%.o)

CFLAGS  = -g -Wall -Wextra -I include
LDFLAGS = -Llib 
LDLIBS  = -lSDL2main -lSDL2

ifeq ($(OS),Windows_NT)
	LDLIBS  += -lmingw32 
else
	LDLIBS += -lm
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
