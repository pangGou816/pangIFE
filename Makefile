CC = gcc
OPT = -O0
DEBUG = -g

BIN = main
SRC = ./src/
INC = ./src/inc/ ./third_party/toml-c-master/
CFILES = $(foreach C,$(SRC),$(wildcard $(C)*.c))
OBJS = $(patsubst %.c,%.o,$(CFILES))

CFLAGS = -Wall -Wextra $(foreach I,$(INC),-I $(I))
LIBS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -L ./third_party/toml-c-master/ -ltoml

default:$(BIN)

$(BIN):$(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o:%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(BIN) $(OBJS)

git:
	@git status
	@git diff --stat
