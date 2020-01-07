# Make file for VimCity

NAME=vimcity

CFLAGS = $(shell sdl2-config --cflags) -Wall -Wextra -g

LPATH = $(shell sdl2-config --libs)

HEADERS = $(wildcard *.h)

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(CFLAGS) $(LPATH)

%.o: %.c $(HEADERS)
	$(CC) -o $@ -c $< $(CFLAGS)
	@echo CC: $<

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)