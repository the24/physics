CC = gcc

NAME = main
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra $(shell sdl2-config --cflags)
LDFLAGS = 
LDLIBS = $(shell sdl2-config --libs) 

all: $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LDFLAGS) $(LDLIBS)
	./$(NAME)

$(OBJS): $(SRCS)
	$(CC) -c $(OBJS) $(CFLAG) 
