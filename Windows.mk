# Make file for VimCity

NAME=vimcity.exe

WINFLAGS = \
	-target x86_64-pc-win32 \
	-fms-compatibility-version=19 \
	-fdelayed-template-parsing \
	-fexceptions \
	-mthread-model posix \
	-fno-threadsafe-statics \
	-Wno-msvc-not-found \
	-DWIN32 \
	-D_WIN32 \
	-D_MT \
	-D_DLL \
	-Xclang \
	-disable-llvm-verifier \
	-Xclang '--dependent-lib=msvcrt' \
	-Xclang '--dependent-lib=ucrt' \
	-Xclang '--dependent-lib=oldnames' \
	-Xclang '--dependent-lib=vcruntime' \
	-D_CRT_SECURE_NO_WARNINGS \
	-D_CRT_NONSTDC_NO_DEPRECATE \
	-U__GNUC__ \
	-U__gnu_linux__ \
	-U__GNUC_MINOR__ \
	-U__GNUC_PATCHLEVEL__ \
	-U__GNUC_STDC_INLINE__   \
	-I/usr/local/Cellar/llvm/9.0.0_1/include \
	-I/Users/floris/Documents/WinLibs/Microsoft\ Visual\ Studio/2019/Community/VC/Tools/MSVC/14.24.28314/include  \
	-I/Users/floris/Documents/WinLibs/Windows\ Kits/10/Include/10.0.18362.0/ucrt  \
	-I/Users/floris/Documents/WinLibs/Windows\ Kits/10/Include/10.0.18362.0/shared  \
	-I/Users/floris/Documents/WinLibs/Windows\ Kits/10/Include/10.0.18362.0/winrt \
	-Wno-ignored-attributes
	
W_LINK_FLAGS = -fuse-ld=lld -target x86_64-pc-win32 -Wl,-machine:x64 -fmsc-version=1924 \
    -L/Users/floris/Documents/WinLibs/Microsoft\ Visual\ Studio/2019/Community/VC/Tools/MSVC/14.24.28314/lib/x64/ \
    -L/Users/floris/Documents/WinLibs/Windows\ Kits/10/Lib/10.0.18362.0/um/x64/ \
    -L/Users/floris/Documents/WinLibs/Windows\ Kits/10/Lib/10.0.18362.0/ucrt/x64/ \
    -nostdlib -lmsvcrt -Wno-msvc-not-found

W_CFLAGS = \
	-I/Users/floris/Documents/WinLibs/SDL2-2.0.10/include/ \
	-I/Users/floris/Documents/WinLibs/SDL2_ttf-2.0.15/include/

CFLAGS = -D_THREAD_SAFE -Wall -Wextra -g $(W_CFLAGS)

W_LPATH = \
	-L/Users/floris/Documents/WinLibs/SDL2-2.0.10/lib/x64/ \
	-L/Users/floris/Documents/WinLibs/SDL2_ttf-2.0.15/lib/x64/ \
	-Xlinker /subsystem:windows
	
LPATH = $(W_LPATH) -lSDL2main -lSDL2 -lSDL2_ttf

HEADERS = $(wildcard *.h)

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(CFLAGS)  $(W_LINK_FLAGS) $(LPATH)

%.o: %.c $(HEADERS)
	@$(CC) -o $@ -c $< $(CFLAGS) $(WINFLAGS)
	@echo CC: $<

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
