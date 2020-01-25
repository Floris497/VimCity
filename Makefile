# Make file for VimCity

BUILD_DIR := build/generic

NAME=$(BUILD_DIR)/vimcity

CFLAGS = -I/usr/local/include/SDL2 -D_THREAD_SAFE -Wall -Wextra -g # -Werror

LPATH = -L/usr/local/lib -lSDL2 -lSDL2_ttf

HEADERS = $(wildcard *.h)

SRCS = $(wildcard *.c)
OBJS := $(addprefix $(BUILD_DIR)/,$(patsubst %.c,%.o,$(SRCS)))

.PHONY: all bundle clean fclean re run

all: $(NAME)

bundle:
	@xcodebuild -scheme VimCity-app SYMROOT=./build/macos build

$(NAME): $(OBJS)
	@mkdir -p $(@D)
	$(CC) -o $(NAME) $(OBJS) $(CFLAGS) $(LPATH)

$(BUILD_DIR)/%.o: %.c $(HEADERS)
	@mkdir -p $(@D)
	@$(CC) -o $@ -c $< $(CFLAGS)
	@echo CC: $<

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

run:
	./$(NAME)
	
sign:
	codesign -s - ./$(NAME)

re: fclean all
