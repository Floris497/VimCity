# Make file for VimCity

# export PATH := $(shell brew --prefix llvm)/bin:$(PATH)
export PATH := /usr/local/opt/llvm/bin:$(PATH)

BUILD_DIR := build/windows
NAME=$(BUILD_DIR)/vimcity.exe

WINFLAGS = \
	-target x86_64-pc-win32 -fms-compatibility-version=19 -fdelayed-template-parsing \
	-fexceptions -mthread-model posix -fno-threadsafe-statics \
	-Wno-msvc-not-found -DWIN32 -D_WIN32 -D_MT -D_DLL -Xclang -disable-llvm-verifier \
	-Xclang '--dependent-lib=msvcrt' -Xclang '--dependent-lib=ucrt' \
	-Xclang '--dependent-lib=oldnames' -Xclang '--dependent-lib=vcruntime' \
	-D_CRT_SECURE_NO_WARNINGS -D_CRT_NONSTDC_NO_DEPRECATE \
	-U__GNUC__ -U__gnu_linux__ -U__GNUC_MINOR__ -U__GNUC_PATCHLEVEL__ -U__GNUC_STDC_INLINE__  \
	-I/usr/local/Cellar/llvm/9.0.0_1/include -I./.windows/MSVC/include  -I./.windows/ucrt/include  \
	-I./.windows/shared/include  -I./.windows/winrt/include \
	-Wno-ignored-attributes
	
W_LINK_FLAGS = \
	-fuse-ld=lld -target x86_64-pc-win32 -Wl,-machine:x64 -fmsc-version=1924 \
	-L./.windows/MSVC/lib/x64 -L./.windows/um/lib/x64 -L./.windows/ucrt/lib/x64 \
	-nostdlib -lmsvcrt -Wno-msvc-not-found

W_CFLAGS = \
	-I./.windows/SDL2/include \
	-I./.windows/SDL2_ttf/include

CFLAGS = -D_THREAD_SAFE -Wall -Wextra -g $(W_CFLAGS)
	
W_LPATH = \
	-L./.windows/SDL2/lib/x64 \
	-L./.windows/SDL2_ttf/lib/x64 \
	-Xlinker /subsystem:windows
	
LPATH = $(W_LPATH) -lSDL2main -lSDL2 -lSDL2_ttf

HEADERS = $(wildcard *.h)

SRCS = $(wildcard *.c)
OBJS := $(addprefix $(BUILD_DIR)/,$(patsubst %.c,%.o,$(SRCS)))

all: $(NAME)

$(BUILD_DIR)/%.o: %.c $(HEADERS)
	@mkdir -p $(@D)
	@echo CC: $<
	@$(CC) -o $@ -c $< $(CFLAGS) $(WINFLAGS)

$(NAME): $(OBJS)
	@mkdir -p $(@D)
	$(CC) -o $(NAME) $(OBJS) $(CFLAGS) $(W_LINK_FLAGS) $(LPATH)

zip: $(BUILD_DIR)/vimcity.zip

$(BUILD_DIR)/vimcity.zip: $(NAME)
	rm -rf $(BUILD_DIR)/bundle
	@mkdir -p $(@D)
	@mkdir -p $(BUILD_DIR)/bundle
	cp ./.windows/SDL2/lib/x64/*.dll $(BUILD_DIR)/bundle/
	cp ./.windows/SDL2_ttf/lib/x64/*.dll $(BUILD_DIR)/bundle/
	cp $(NAME) $(BUILD_DIR)/bundle/
	zip -rj $(BUILD_DIR)/vimcity.zip $(BUILD_DIR)/bundle/*
	rm -rf $(BUILD_DIR)/bundle/

clean:
	rm -rf $(OBJS)
	rm -rf $(BUILD_DIR)/vimcity.pdb
	rm -rf $(BUILD_DIR)/bundle/

fclean: clean
	rm -rf $(BUILD_DIR)

re: fclean all
