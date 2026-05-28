CC = gcc
CFLAGS = -g -std=c11 -Wno-incompatible-pointer-types
LDFLAGS = -lm -lcurl

BIN=test

BUILD_DIR = ./bin
SOURCE_DIR = ./src
SOURCE_DIRS = $(shell find $(SOURCE_DIR) -type d)

SOURCES := $(shell find $(SOURCE_DIR) -name '*.c') cJSON.c
OBJECTS := $(SOURCES:%.c=%.o)

# Adăugăm '.' (folderul curent) ca path de căutare pentru fișiere .c
vpath %.c $(SOURCE_DIRS) .

all: $(BIN)

$(BIN): $(notdir $(OBJECTS))
	$(CC) $(CFLAGS) $(addprefix -I, $(SOURCE_DIRS)) $(addprefix $(BUILD_DIR)/, $^) -o $(BIN) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(addprefix -I, $(SOURCE_DIRS)) -c $< -o $(BUILD_DIR)/$@ 

clean:
	@rm -f $(BUILD_DIR)/*.o $(BIN)

show:
	@echo $(notdir $(OBJECTS))