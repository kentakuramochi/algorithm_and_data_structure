# Makefile
# usage
#   make SRC=(main source file path)
CC      = gcc
CFLAGS  = -Wall -std=c11
LDFLAGS =
INCDIR  = ./include
SRCDIR  = ./src
OBJDIR  = ./obj
BINDIR  = ./bin
HDRS    = $(wildcard $(INCDIR)/*)
SRC     =
SRCS    = $(SRC) $(wildcard $(SRCDIR)/*)
OBJS    = $(SRCS:.c=.o)
TARGET  ?= $(SRC:.c=)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	if [ ! -d $(BINDIR) ]; then mkdir $(BINDIR); fi
	if [ ! -d $(OBJDIR) ]; then mkdir $(OBJDIR); fi
	$(CC) $^ $(CFLAGS) $(OUTPUT_OPTION)
	mv $(OBJS) $(OBJDIR)
	mv $@ $(BINDIR)

.c.o: $(HDRS)
	$(CC) $< $(CFLAGS) -c -I$(INCDIR) -o $@

clean:
	rm -rf $(OBJDIR) $(BINDIR)
