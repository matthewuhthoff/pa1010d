CC      := gcc
LD      := gcc

TARGET_NAME=main
BINDIR=bin
TARGET=$(BINDIR)/$(TARGET_NAME)

SRC=src
INCLUDE=include
SRCS=$(wildcard $(SRC)/*.c)
OBJS=$(patsubst $(SRC)/%.c, $(SRC)/%.o, $(SRCS))

$(SRC)/%.o: $(SRC)/%.c
	$(CC) -I$(INCLUDE) -c $< -o $@

$TARGET: $(OBJS)
	mkdir -p $(BINDIR)
	$(CC) $(OBJS) -o $(TARGET) 

.PHONY: clean
clean:
	rm -f bin/* $(OBJS)
