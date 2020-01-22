# Make file for VimCity

NAME=vimcity

CFLAGS = -I/usr/local/include/SDL2 -D_THREAD_SAFE -Wall -Wextra -g # -Werror

LPATH = -L/usr/local/lib -lSDL2 -lSDL2_ttf

HEADERS = $(wildcard *.h)

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

.PHONY: xcode

all: $(NAME)

xcode:
	@xcodebuild -scheme VimCity-app SYMROOT=./build/macos build

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(CFLAGS) $(LPATH)

%.o: %.c $(HEADERS)
	@$(CC) -o $@ -c $< $(CFLAGS)
	@echo CC: $<

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
