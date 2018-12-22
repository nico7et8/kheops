DOODLE=simple_ellipse

CC=gcc -std=c99
SHELL=bash
ECHO=echo -e
AR=ar cr
CFLAGS=-W -Wall -O3 `(pkg-config --cflags cairo)`
LIBS=`(pkg-config --libs cairo)`

SRC_DIR=src
INCLUDE_DIR=include
LIB_DIR=lib
BIN_DIR=bin
PNG_DIR=png
DOODLE_DIR=doodles

SOURCES=$(wildcard $(SRC_DIR)/*.c)
INCLUDES=$(wildcard $(INCLUDE_DIR)/*.h)
OBJECTS=$(SOURCES:$(SRC_DIR)/%.c=$(LIB_DIR)/%.o)

DOODLE_SRC=$(DOODLE:%=$(DOODLE_DIR)/%.c)
DOODLE_BIN=$(DOODLE_SRC:$(DOODLE_DIR)/%.c=$(BIN_DIR)/%)
DOODLE_PNG=$(DOODLE_SRC:$(DOODLE_DIR)/%.c=$(PNG_DIR)/%.png)

DOODLE_SOURCES=$(wildcard $(DOODLE_DIR)/*.c)
DOODLE_BINS=$(DOODLE_SOURCES:$(DOODLE_DIR)/%.c=$(BIN_DIR)/%)
DOODLE_PNGS=$(DOODLE_BINS:$(BIN_DIR)/%=$(PNG_DIR)/%.png)

all: $(DOODLE_PNG) $(DOODLE_BIN) $(OBJECTS)
	open -a preview $(DOODLE_PNG)

doodles: $(DOODLE_PNGS)  $(DOODLE_BIN) $(OBJECTS)

$(PNG_DIR)/%.png: $(BIN_DIR)/% $(DOODLE_BINS)
	./$<

$(BIN_DIR)/%: $(DOODLE_DIR)/%.c $(OBJECTS)
	$(CC) -o $@ $(CFLAGS) $< -I $(INCLUDE_DIR) $(OBJECTS) $(LIBS)

$(LIB_DIR)/%.o: $(SRC_DIR)/%.c 
	$(CC) -o $@ -c $< $(CFLAGS) -I $(INCLUDE_DIR) 

clean:
	rm -rf $(DOODLE_BIN)
	rm -rf $(DOODLE_PNG)

cleanall:
	rm -rf $(BIN_DIR)/*
	rm -rf $(PNG_DIR)/*

mrproper: cleanall
	rm -rf $(LIB_DIR)/*
